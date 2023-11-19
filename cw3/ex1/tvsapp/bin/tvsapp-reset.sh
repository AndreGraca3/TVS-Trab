#!/bin/bash

SCALE=${1:-1}
BASE=${2:-39000}
NGINX_CONF=/etc/nginx/sites-available/tvsapp

if [ "$(id -u)" -ne 0 ]; then
   echo "Only an admin can do that."
   exit 1
fi

./tvsapp-stop.sh

echo upstream tvsapp_backend { > "$NGINX_CONF"
for index in $(seq 0 $SCALE);
do
	sum=$(( "$BASE" + "$index" ))
	echo -e '\t'server 127.0.0.1:$sum';' >> "$NGINX_CONF"
done
echo } >> "$NGINX_CONF"

echo server {  >> "$NGINX_CONF"
echo -e '\t'listen 12021 default_server';' >> "$NGINX_CONF"
echo -e '\t'location / { >> "$NGINX_CONF"
echo -e '\t\t'proxy_pass http://tvsapp_backend/';' >> "$NGINX_CONF"
echo -e '\t'} >> "$NGINX_CONF"
echo } >> "$NGINX_CONF"
exit 0








