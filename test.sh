#!/bin/sh
set -eux

DEST=${DIR:-/tmp}

# print the mount points
findmnt

# compile
cd /code
gcc -Wall -o empty-dir empty-dir.c

# run the test
./empty-dir "${DEST}"
