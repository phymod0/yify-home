#!/bin/bash

git submodule update --init && cd backend/transmission && git checkout label-search && mkdir build && git submodule update --init && cd build && cmake .. && make
