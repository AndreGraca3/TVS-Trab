#!/bin/bash

if [ "$(id -u)" -ne 0 ]; then
        echo "Only an admin can do that."
        exit 1
fi

systemctl start elasticsearch

NGINX_CONF=/etc/nginx/sites-available/tvsapp

PORTS=$( cat "$NGINX_CONF" | grep ":[0-9]\+;" | cut -d: -f2 | tr -d ';')

for PORT in $PORTS;
do
	systemctl start tvsapp@"$PORT".service
done

ln -s /etc/nginx/sites-available/tvsapp /etc/nginx/sites-enabled/

systemctl reload nginx
