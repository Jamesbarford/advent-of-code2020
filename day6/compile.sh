#!/bin/bash

if [[ $1 == "b" ]]; then
    clang++ --std=c++11 solveb.cpp -o solveb.out && ./solveb.out rm ./solveb.out

    else
        clang++ --std=c++11 solve.cpp -o solve.out && ./solve.out && rm ./solve.out
fi
