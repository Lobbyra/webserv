#!/usr/bin/env bash

CONFIG_PATH=./config_files
PHPCGI_TARGET=tools/php-cgi
PHPCGI_RES=php-8.0.2
PHPBIN_PATH="$PHPCGI_TARGET/sapi/cgi/php-cgi"
SIEGE_CONF="$HOME/.siege/siege.conf"

function ft_escape_backslash () {
	echo $* | sed s/\\//\\\\\\//g
}

if [ "$OSTYPE" = "linux-gnu" ]; then
	function sedreplace () {
		sed s/"$1"/"$2"/g $3 -i
	}
	PHPCGI_SRC="./tools/.compressed_phpcgi/linux_phpcgi.tar"
else # On macOS
	function sedreplace () {
		sed -i "" s/"$1"/"$2"/g $3
	}
	PHPCGI_SRC="./tools/.compressed_phpcgi/darwin_phpcgi.tar"
	if [ -e $SIEGE_CONF ]; then
		sedreplace "^connection \= close" "connection \= keep-alive" $SIEGE_CONF
	fi
fi

# un-tar phpcgi
# Archive created by: tar -czf .compressed_phpcgi/darwin_phpcgi.tar php-8.0.2
# if ! [ -e "$PHPCGI_TARGET" ]; then
# 	echo "Unpacking php-cgi ..."
# 	tar -xzf $PHPCGI_SRC
# 	mv $PHPCGI_RES $PHPCGI_TARGET
# fi

# Replace __PWD__ by actual PWD in every config files
FILES=($(ls $CONFIG_PATH))
NEWPWD=$(ft_escape_backslash $PWD)
NEWPHPBIN=$(ft_escape_backslash "$PWD/$PHPBIN_PATH")
for file in ${FILES[@]}; do
	sedreplace __PWD__ "$NEWPWD" "$CONFIG_PATH/$file"
	sedreplace __PHP__ "$NEWPHPBIN" "$CONFIG_PATH/$file"
done
