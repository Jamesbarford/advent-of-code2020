#!/bin/bash

source ./config/token.sh

FOLDER=day$1
OUTPUT=output
PART=part

mkdir ./$FOLDER

for part in {1..2}; do
    DAY_PART=$PART$part

    mkdir ./$FOLDER/$DAY_PART ./$FOLDER/$DAY_PART/$OUTPUT

    cat >./$FOLDER/$DAY_PART/solve.cpp \
        <<-EOCPP
#include <iostream>
#include <fstream>
#include <string>

int main(void)
{
    std::ifstream infile("../input.txt");
    std::string line;

    while (std::getline(infile, line))
    {
    }
}
EOCPP

    cp ./makefile_template ./$FOLDER/$DAY_PART/makefile
done

curl --cookie $TOKEN https://adventofcode.com/2020/day/$1/input -o ./$FOLDER/input.txt

echo "Happy coding!!! 🎅🏻🎄❄️"
