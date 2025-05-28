#!/bin/bash

# Script to run Orbis in Docker with X11 support

# Allow X server connection from Docker
xhost +local:docker 2>/dev/null || true

# Run the game
docker run --rm -it \
    -e DISPLAY=$DISPLAY \
    -v /tmp/.X11-unix:/tmp/.X11-unix:rw \
    -v "$HOME/.Xauthority:/root/.Xauthority:rw" \
    --network host \
    orbis-game

# Revoke X server access
xhost -local:docker 2>/dev/null || true