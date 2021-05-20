PREREQUISITE_FILE=.prerequisite
PREREQUISITE_SCRIPT=.prerequisite.sh
CONFIG_PATH=./config_files

touch $PREREQUISITE_FILE

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
