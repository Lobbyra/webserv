#!/usr/bin/env zsh

# ============================================================================ #
#                             Global variables                                 #
# ============================================================================ #

EOC="\033[0m"
BOLD="\033[1m"
RED="\033[91m"
GREEN="\033[92m"
YELLOW="\033[93m"
DBLUE="\033[94m"
PURPLE="\033[95m"
CYAN="\033[96m"

HTTPD_IMG="fresh-httpd"

# ============================================================================ #
#                       Default file and Directory managment                   #
# ============================================================================ #

#
# --- Create default website directory and its index
#
ROOT_DIR="/tmp/www"
rm -rf $ROOT_DIR;
cp -r ../docker_nginx/www $ROOT_DIR

# ============================================================================ #
#                       Docker verif and port select                           #
# ============================================================================ #

TRUE=0
FALSE=1

#
# --- Choose a port to expose for httpd
#
function is_port_in_use () {
    nc -z 127.0.0.1 $1 &> /dev/null
    if [[ "$?" == "1" ]]
    then
        return $FALSE
    else
        return $TRUE
    fi
}

PORT=8080
while is_port_in_use $PORT; do
    PORT=$(($RANDOM % 60000))
done

#
# --- Check if docker cli is installed
#
docker -v &> /dev/null
if [[ "$?" == "127" ]]; then
    echo "Docker CLI isn't installed on your computer."
    exit 1
fi

#
# --- Check if docker daemon is up
#
docker ps &> /dev/null
if [[ $? != 0 ]]; then
    echo "Docker daemon isn't ready, containers cannot be run."
    exit 1
fi

# ============================================================================ #
#                         SET CONFIG FILE PATH                                 #
# ============================================================================ #

if [ -z "$1" ]; then
    1="./config_files/allow_all.conf"
fi

if [ -f $1 ]; then
    HTTPD_CONFIG_PATH=$1
else
    echo "$1 does not exist !"
    exit 1
fi

echo "Using: ${YELLOW}${1}${EOC}. Which contains:"
echo "___________________________________________\n"

# ============================================================================ #
#                    Cleaning possibly running httpd container                 #
# ============================================================================ #

docker stop $HTTPD_IMG &> /dev/null
docker rm $HTTPD_IMG &> /dev/null

# ============================================================================ #
#                                   BUILD                                      #
# ============================================================================ #

echo "${BOLD}Building httpd container...${EOC}\n"

cp $HTTPD_CONFIG_PATH temp.conf

docker build . -t $HTTPD_IMG > /dev/null

rm temp.conf

# ============================================================================ #
#                                   RUN                                        #
# ============================================================================ #

echo "${BOLD}Container starting...${EOC}\n"

docker run --name $HTTPD_IMG -d -p $PORT:80 \
    -v $ROOT_DIR:/usr/local/apache2/htdocs $HTTPD_IMG > /dev/null
sleep 1.25

echo "Container launched and listening at port ${GREEN}${PORT}${EOC}\n"

# ============================================================================ #
#                                   INSPECT                                    #
# ============================================================================ #

#
# --- Print startup logs
#
echo "${BOLD}==== HTTPD STARTUP LOGS ====${EOC}"
docker logs $HTTPD_IMG
echo "${BOLD}==== ------------------ ====${EOC}\n"

#
# --- Check if container is running
#
if [[ "$( docker container inspect -f '{{.State.Running}}' ${HTTPD_IMG} )" == "false" ]]
then
    echo "❌ : httpd crashed at startup."
    exit 1
fi

echo "✅ : Container running ! stdout are linked to your terminal...\n"

#
# --- Display live logs
#
docker attach $HTTPD_IMG
