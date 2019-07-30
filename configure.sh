#!/bin/bash

git submodule update --init --recursive --progress \
    && cd backend/transmission \
    && git checkout label-search \
    && mkdir build && cd build \
    && cmake .. && make
