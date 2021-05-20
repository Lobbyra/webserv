#!/usr/bin/env bash

CONFIG_PATH=./config_files

if [ "$OSTYPE" = "linux-gnu" ]; then
	function sedreplace () {
		sed s/$1/$2/g $3 -i
	}
else
	function sedreplace () {
		sed -i "" s/$1/$2/g $3
	}
fi

FILES=($(ls $CONFIG_PATH))
PWD=$(echo $PWD | sed s/\\//\\\\\\//g)
for file in ${FILES[@]}; do
	sedreplace __PWD__ "$PWD" "$CONFIG_PATH/$file"
done
