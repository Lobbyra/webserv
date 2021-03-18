#!/bin/bash

compile() {
    clang++ -Wall -Wextra -o strtime main.cpp
    echo "Compilation done !"
}

clean () {
    rm strtime
    echo "Cleaning done !"
}

if [[ $1 == "--clean" ]];
then
    clean
else
    compile
fi
