#!/bin/bash

./generate_resources.py src/nezumi.json . || exit 1
./waf build
