#!/bin/bash

./generate_resources.py src/nezumi.json appinfo-template.json . || exit 1
pebble clean || exit 1
pebble build || exit 1
pebble install --phone $1