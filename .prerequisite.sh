#!/usr/bin/env zsh

CONFIG_PATH=config_files
TEMPLATE_CONF_PATH=$CONFIG_PATH/.template
SIEGE_CONF="$HOME/.siege/siege.conf"
SERVER_TARGET="/tmp/www"
SERVER_SOURCE="tools/docker_nginx/www"

function ft_escape_backslash () {
	echo $* | sed s/\\//\\\\\\//g
}

function copy_server () {
	mkdir -p $SERVER_TARGET
	cp -rf $SERVER_SOURCE/* $SERVER_TARGET
	$SERVER_TARGET/run.sh $SERVER_TARGET
}

if [ "$OSTYPE" = "linux-gnu" ]; then
	PHPBIN_PATH="tools/other_cgi/linux_phpcgi"
	CGI42="tools/42_testers/ubuntu_cgi_tester"

	function sedreplace () {
		2="$(ft_escape_backslash $2)"
		sed s/"$1"/"$2"/g $3 -i
	}
else # On macOS
	PHPBIN_PATH="tools/other_cgi/darwin_phpcgi"
	CGI42="tools/42_testers/cgi_tester"

	function sedreplace () {
		2="$(ft_escape_backslash $2)"
		sed -i "" s/"$1"/"$2"/g $3
	}
	if [ -e $SIEGE_CONF ]; then
		sedreplace "^connection \= close" "connection \= keep-alive" $SIEGE_CONF
	fi
fi

copy_server

# Replace __PWD__ by actual PWD in every config files
FILES=($(ls $TEMPLATE_CONF_PATH))
for file in ${FILES[@]}; do
	if ! [ -e "$CONFIG_PATH/$file" ]; then
		cp "$TEMPLATE_CONF_PATH/$file" "$CONFIG_PATH/$file"
	fi

	sedreplace __PWD__ "$PWD" "$CONFIG_PATH/$file"
	sedreplace __PHP__ "$PHPBIN_PATH" "$CONFIG_PATH/$file"
	sedreplace __42CGI__ "$CGI42" "$CONFIG_PATH/$file"
done
