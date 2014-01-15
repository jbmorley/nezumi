#!/bin/bash

./generate_resources.py src/nezumi.json appinfo-template.json . || exit 1
pebble clean
pebble build