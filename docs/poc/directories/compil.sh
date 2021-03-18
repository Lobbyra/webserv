#!/bin/bash

compile () {
    clang++ -Wall -Wextra -Werror -o ft_mkdir ft_mkdir.cpp
    ./ft_mkdir
    echo

    clang++ -Wall -Wextra -Werror -o ft_rmdir ft_rmdir.cpp
    ./ft_rmdir
    echo

    clang++ -Wall -Wextra -Werror -o ft_opendir ft_opendir.cpp
    ./ft_opendir
    echo "Compilation done !"
}

clean () {
    rm ft_opendir ft_mkdir ft_rmdir
    echo "Cleaning done !"
}

if [[ $1 == "-clean" ]];
then
    clean
else
    compile
fi
