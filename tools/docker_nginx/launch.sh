#!/bin/bash

# ============================================================================ #
#                       Default file and Directory managment                   #
# ============================================================================ #

#
# --- Create default website directory and its index
#
if [ ! -d "./www/" ]
then
    mkdir www
    echo "! Default website !" > www/index.html
fi

# ============================================================================ #
#                       Docker verif and port select                           #
# ============================================================================ #

TRUE=0
FALSE=1

#
# --- Choose a port to expose for nginx
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

PORT=($RANDOM % 60000)
while is_port_in_use $PORT
do
    PORT=($RANDOM % 60000)
done

#
# --- Check if docker cli is installed
#
docker -v &> /dev/null
if [[ "$?" == "127" ]]
then
    echo "Docker CLI isn't installed on your computer."
    exit 1
fi

#
# --- Check if docker daemon is up
#
docker ps &> /dev/null
if [[ $? != 0 ]]
then
    echo "Docker daemon isn't ready, containers cannot be run."
    exit 1
fi

# ============================================================================ #
#                         SET CONFIG FILE PATH                                 #
# ============================================================================ #

NGINX_CONFIG_PATH="./config_files/basic.conf"

if [ $# -ne 0 ]
then
    if [ -f $1 ]
    then
        NGINX_CONFIG_PATH=$1
        NGINX_CONFIG_PATH=$(pwd)/$1
    else
        echo "$1 does not exist !"
        exit 1
    fi
fi

echo $NGINX_CONFIG_PATH
cat $NGINX_CONFIG_PATH

# ============================================================================ #
#                    Cleaning possibly running nginx container                 #
# ============================================================================ #

docker stop fresh-nginx &> /dev/null
docker rm fresh-nginx &> /dev/null

# ============================================================================ #
#                                   BUILD                                      #
# ============================================================================ #

echo "Building Nginx container...\n"

cp $NGINX_CONFIG_PATH temp.conf

docker build . -t fresh-nginx > /dev/null

rm temp.conf

# ============================================================================ #
#                                   RUN                                        #
# ============================================================================ #

docker run --name fresh-nginx -d -p $PORT:80 fresh-nginx

echo "Container launched and listening at port $PORT"
