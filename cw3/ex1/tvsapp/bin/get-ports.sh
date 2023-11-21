#!/bin/bash

NGINX_CONF=/etc/nginx/sites-available/tvsapp

first_n=""
last_n=""

while getopts ":f:l:" opt; do
    case $opt in
        f)
            first_n="$OPTARG"
            ;;
        l)
            last_n="$OPTARG"
            ;;
    esac
done

result=$(cat "$NGINX_CONF" | grep ":[0-9]\+;" | cut -d: -f2 | tr -d ';' | sort)

if [ -n "$first_n" ]; then
    echo "$result" | head -n "$first_n"
elif [ -n "$last_n" ]; then
    echo "$result" | tail -n "$last_n"
else
    echo "$result"
fi
