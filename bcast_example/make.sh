#!/usr/bin/env bash

cmake -H/work/ -B/build -DCMAKE_BUILD_TYPE=Debug
cmake --build /build/
/build/bcast
