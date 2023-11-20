#!/bin/bash

if [ "$(id -u)" -ne 0 ]; then
	echo "Only an admin can do that."
	exit 1
fi

INSTANCES_TO_REMOVE=${1:-1} #Delta

NGINX_CONF=/etc/nginx/sites-available/tvsapp

PORTS=$( cat "$NGINX_CONF" | grep ":[0-9]\+;" | cut -d: -f2 | tr -d ';' )

NUMBER_OF_PORTS=$( cat "$NGINX_CONF" | grep ":[0-9]\+;" | cut -d: -f2 | tr -d ';' | wc -l )

if [ $NUMBER_OF_PORTS -le $INSTANCES_TO_REMOVE ]; then
	INSTANCES_TO_REMOVE=$(($NUMBER_OF_PORTS-1))
fi

PORTS_TO_REMOVE=$(cat "$NGINX_CONF" | grep ":[0-9]\+;" | cut -d: -f2 | tr -d ';' | sort -r | head -n $INSTANCES_TO_REMOVE)

for PORT in $PORTS_TO_REMOVE;
do
	sed -i /$PORT/d "$NGINX_CONF" # remove from configuration
	systemctl stop tvsapp@"$PORT".service # stop service
done

systemctl reload nginx
