#!/bin/bash

PORTS=$( /opt/isel/tvs/tvsapp/bin/get-ports.sh )

if [ -z "$PORTS" ]; then
	echo "No ports found."
	exit 1
fi

for PORT in $PORTS;
do
	status=$(systemctl status tvsapp@"$PORT".service)
	name=$(echo "$status" | grep -i 'TVS Web' | head -n 1)
	active_status=$(echo "$status" | grep -i "Active:" | cut -d':' -f 2)
	pid=$(echo "$status" | awk '/Main PID:/ {print $3}')

	if [ -n "$pid" ]; then
		echo "$name is $active_status with PID $pid"
	else
		echo "$name is $active_status"
	fi
done
