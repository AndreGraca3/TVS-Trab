#!/bin/bash

if [ "$(id -u)" -ne 0 ]; then
	echo "Only an admin can do that."
	exit 1
fi

INSTANCES_TO_ADD=${1:-1} #Delta
NGINX_CONF=/etc/nginx/sites-available/tvsapp

for (( i = 1; i <= $INSTANCES_TO_ADD; i++ ))
do
	LAST_PORT=$(./get-ports.sh -l 1)
	NEW_PORT=$(($LAST_PORT + 1))
	sed -i "/$LAST_PORT/a\\\tserver 127.0.0.1:$NEW_PORT;" $NGINX_CONF

	systemctl start tvsapp@"$NEW_PORT".service
done

systemctl reload nginx
