#!/bin/bash

for ip in 10.2.0.41 10.2.0.42 10.2.0.69; do
    echo $ip;
    ssh control@$ip 'cd qt-client/; git pull; make -j$(nproc)'
done;

