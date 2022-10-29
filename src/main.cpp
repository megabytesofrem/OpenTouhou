#include "parser/PBG3.hpp"

using namespace OpenTouhou;

int main() {
    PBG3 *pbg = new PBG3();
    pbg->load("紅魔郷ED.DAT");

    delete pbg;
}