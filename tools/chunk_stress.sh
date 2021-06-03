#!/bin/bash

echo "- existing file deletion -"

printf "DELETE /my_ego.db HTTP/1.1\r\n"  > /tmp/delete
printf "Host: example.com\r\n\r\n"          >> /tmp/delete

cat /tmp/delete | nc localhost 8080

echo "- chunk creation -"
# CHUNK CREATION
rm -f /tmp/chunk
j=0
while (( $j < 5000 ))
do
    echo -n "zzzzzzzzzz" >> /tmp/chunk
    ((j++))
done

echo "- header creation -"
# HEADER CREATION
printf "POST /directory/youpi.bla HTTP/1.1\r\n"     > /tmp/my_ego.db
printf "Host: example.com\r\n"          >> /tmp/my_ego.db
printf "Transfer-Encoding: chunked\r\n" >> /tmp/my_ego.db
printf "\r\n"                           >> /tmp/my_ego.db

echo "- body creation -"
# BODY CREATION
i=0
while (( $i < 2000 ))
do
    printf "C350\r\n" >> /tmp/my_ego.db
    cat /tmp/chunk >> /tmp/my_ego.db
    printf "\r\n" >> /tmp/my_ego.db
    ((i++))
done
printf "0\r\n" >> /tmp/my_ego.db
printf "\r\n" >> /tmp/my_ego.db

echo "- request sending creation -"
cat /tmp/my_ego.db | nc localhost 8080 | head
