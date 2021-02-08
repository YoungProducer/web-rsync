#!/bin/sh
if [[ "$OSTYPE" == "darwin"* ]]; then
    exit
fi

if ! command -v apk &> /dev/null
then
    echo "Could no found apk"
else
    apk add python3 make gcc g++
    exit
fi

if ! command -v apt &> /dev/null
then
    echo "Could no found apt"
else
    apt update
    apt install python3 make gcc g++
    exit
fi
