#!/bin/bash

(trap 'kill 0' SIGINT; \
    (cd frontend/ && node server.js) & \
    ./backend/transmission/build/daemon/transmission-daemon -f -p 9091 \
)
