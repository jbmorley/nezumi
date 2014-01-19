#!/bin/bash

tools/addimages resources/images/ appinfo-template.json .
tools/makestruct src/types.json src/data.json src/animation.h || exit 1
pebble clean || exit 1
pebble build || exit 1
pebble install --phone $1