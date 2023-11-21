#!/bin/bash

if [ "$(id -u)" -ne 0 ]; then
	echo "Only an admin can do that."
	exit 1
fi

INSTANCES_TO_REMOVE=${1:-1} #Delta

NGINX_CONF=/etc/nginx/sites-available/tvsapp

PORTS_TO_REMOVE=$( ./get-ports.sh -l $INSTANCES_TO_REMOVE )

NUMBER_OF_PORTS=$(./get-ports.sh | wc -l )

if [ $NUMBER_OF_PORTS -le $INSTANCES_TO_REMOVE ]; then
	INSTANCES_TO_REMOVE=$(($NUMBER_OF_PORTS-1))
fi

for PORT in $PORTS_TO_REMOVE;
do
	sed -i /$PORT/d "$NGINX_CONF" # remove from configuration
	systemctl stop tvsapp@"$PORT".service # stop service
done

systemctl reload nginx
