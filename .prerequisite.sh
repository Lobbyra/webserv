#!/usr/bin/env bash

CONFIG_PATH=./config_files
PHPCGI_TARGET=./tools/php-cgi/
PHPCGI_RES=php-8.0.2

if [ "$OSTYPE" = "linux-gnu" ]; then
	function sedreplace () {
		sed s/$1/$2/g $3 -i
	}
	PHPCGI_SRC="./tools/.compressed_phpcgi/linux_phpcgi.tar"
else
	function sedreplace () {
		sed -i "" s/$1/$2/g $3
	}
	PHPCGI_SRC="./tools/.compressed_phpcgi/darwin_phpcgi.tar"
fi

# un-tar phpcgi
# Archive created by: tar -czf .compressed_phpcgi/darwin_phpcgi.tar php-8.0.2
if ! [ -e "$PHPCGI_TARGET" ]; then
	echo "Unpacking php-cgi ..."
	tar -xzf $PHPCGI_SRC
	mv $PHPCGI_RES $PHPCGI_TARGET
fi

# Replace __PWD__ by actual PWD in every config files
FILES=($(ls $CONFIG_PATH))
PWD=$(echo $PWD | sed s/\\//\\\\\\//g)
for file in ${FILES[@]}; do
	sedreplace __PWD__ "$PWD" "$CONFIG_PATH/$file"
done
