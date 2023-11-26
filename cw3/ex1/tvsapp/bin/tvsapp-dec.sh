#!/bin/bash

if [ "$(id -u)" -ne 0 ]; then
	echo "Only an admin can do that."
	exit 1
fi

INSTANCES_TO_REMOVE=${1:-1} #Delta

NGINX_CONF=/etc/nginx/sites-available/tvsapp

NUMBER_OF_PORTS=$( /opt/isel/tvs/tvsapp/bin/get-ports.sh | wc -l )

if [ $NUMBER_OF_PORTS -le $INSTANCES_TO_REMOVE ]; then
	INSTANCES_TO_REMOVE=$(($NUMBER_OF_PORTS-1))
fi

PORTS_TO_REMOVE=$( /opt/isel/tvs/tvsapp/bin/get-ports.sh -l $INSTANCES_TO_REMOVE )

for PORT in $PORTS_TO_REMOVE;
do
	sed -i /$PORT/d "$NGINX_CONF" # remove from configuration
	systemctl stop tvsapp@"$PORT".service # stop service
done

systemctl reload nginx
