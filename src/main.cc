#include <iostream>

#include "level/level.hh"

int main(int argc, char* argv[])
{
    interpretor::Level level = interpretor::Level();

    level.load("file.mlg");
    level.play();

    return 0;
}
