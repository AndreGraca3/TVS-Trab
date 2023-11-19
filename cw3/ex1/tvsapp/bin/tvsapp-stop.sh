#!/bin/bash

if [ "$1" == "-db" ]; then
	sudo systemctl stop elasticsearch
fi

NGINX_CONF=/etc/nginx/sites-available/tvsapp

PORTS=$( cat "$NGINX_CONF" | grep ":[0-9]\+;" | cut -d: -f2 | tr -d ';' )

for PORT in $PORTS;
do 
        sudo systemctl stop tvsapp@"$PORT".service
done

sudo rm /etc/nginx/sites-enabled/tvsapp
