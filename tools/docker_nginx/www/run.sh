#!/usr/bin/env bash

if [ $# -ne 1 ]; then
	echo "Usage: $0 <copy/dest>"
	exit 1
fi

# rm $1/$0
chmod 444 $1/o_r_rights.html
chmod 222 $1/o_w_rights.html
