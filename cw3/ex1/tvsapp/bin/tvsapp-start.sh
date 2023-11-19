#!/bin/bash

sudo systemctl start elasticsearch

NGINX_CONF=/etc/nginx/sites-available/tvsapp

PORTS=$( cat "$NGINX_CONF" | grep ":[0-9]\+;" | cut -d: -f2 | tr -d ';')

for PORT in $PORTS;
do
	sudo systemctl start tvsapp@"$PORT".service
done

sudo ln -s /etc/nginx/sites-available/tvsapp /etc/nginx/sites-enabled/

