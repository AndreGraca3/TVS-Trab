## ISEL - System Virtualization Techniques
### Coursework Assignment 3

Commands:
    Install the web application as a service:
        $ cp /opt/isel/tvs/tvsapp/app/tvsapp@.service /etc/systemd/system/tvsapp@.service

    Reload the system:
        $ sudo systemctl daemon-reload

    start:
        $ systemctl start tvsapp@"NODE_PORT".service 

    status:
        $ systemctl status tvsapp@"NODE_PORT".service 

    add configuration:
        $ sudo nano /etc/nginx/sites-available/tvsapp

    enable configuration:
        $ sudo ln -s /etc/nginx/sites-available/tvsapp /etc/nginx/sites-enabled/

    test configuration:
        $ sudo nginx -t 

    restart nginx:
        $ sudo systemctl reload nginx
