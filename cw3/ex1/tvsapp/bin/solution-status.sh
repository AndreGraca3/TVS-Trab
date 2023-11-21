#!/bin/bash

NGINX_CONF="/etc/nginx/sites-enabled/tvsapp"

if [ -e $NGINX_CONF ]; then
	echo "active"
else
	echo "inactive"
fi
