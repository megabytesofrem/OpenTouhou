#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#define PACK_BEGIN __attribute__((packed))
#define PACK_END

// code rip from the thtk
typedef struct {
PACK_BEGIN
    uint32_t count;
    uint32_t offset;
    uint32_t size;
PACK_END
} th07_header_t;

#define ERROR_INVALID_MAGIC 10
#define ERROR_BUFFER_OVERFLOW 11

#define TH07_HEADER_LEN sizeof(th07_header_t)

typedef struct {
    unsigned char *data;
    size_t len;
    size_t index;
} file_t;

int file_read_bytes(file_t *file, unsigned char *buf, size_t bytes) {
    if (file->index+bytes > file->len)
        return ERROR_BUFFER_OVERFLOW;
    memcpy(buf, file->data+file->index, bytes);
    file->index += bytes;
    return 0;
}

int file_decode(file_t *file) {
    int index = 0;
    char buf[256];
    int e;
    // 1. get 4 bytes into buf
    if ((e = file_read_bytes(file, &buf, 4)) != 0)
        return e;
    
    // 2. compare the 4 bytes with the static magic
    if (strncmp(&buf, "PBG4", 4) != 0) {
        fprintf(stderr, "[error] not pbg4 file format\n");
        return ERROR_INVALID_MAGIC;
    }

    // 3. malloc a new header struct
    th07_header_t *header = malloc(TH07_HEADER_LEN);
    // 4. copy the bytes from the file into the header via pointer
    if ((e = file_read_bytes(file, header, TH07_HEADER_LEN)) != 0) {
        free(header);
        return e;
    }
    // 5. access each property of the header struct
    printf("header - entries count: %d, offset: %d, size: %d\n", header->count, header->offset, header->size);
    return 0;
}

file_t *file_open(char *filename) {
    FILE *file = fopen(filename, "rb");
    if (file == NULL) {
        printf("Error opening file %s\n", filename);
        exit(1);
    }

    // read the file length
    fseek(file, 0, SEEK_END);
    size_t size = ftell(file);
    rewind(file);
    unsigned char *buffer = malloc(size);
    fread(buffer, 1, size, file);
    fclose(file);

    file_t *file_struct = malloc(sizeof(file_t));
    file_struct->data = buffer;
    file_struct->index = 0;
    file_struct->len = size;
    return file_struct;
}

int main() {
    // read the file
    file_t *file = file_open("th07.dat");
    // decode the buffer
    int e = file_decode(file);
    if (e != 0) {
        fprintf(stderr, "[error] error code: %d\n", e);
    }

    // todo: clean

    return 0;
}
