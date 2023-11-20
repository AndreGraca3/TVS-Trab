#!/bin/bash

if [ "$(id -u)" -ne 0 ]; then
        echo "Only an admin can do that."
        exit 1
fi

if [ "$1" == "-db" ]; then
	systemctl stop elasticsearch
fi

NGINX_CONF=/etc/nginx/sites-available/tvsapp

PORTS=$( cat "$NGINX_CONF" | grep ":[0-9]\+;" | cut -d: -f2 | tr -d ';' )

for PORT in $PORTS;
do 
        systemctl stop tvsapp@"$PORT".service
done

rm /etc/nginx/sites-enabled/tvsapp
