#!/bin/bash
if ! command -v brew &> /dev/null
then
    echo "Could no found brew"
    exit
fi
brew install boost
echo "Do not forget to provide include paths for compiler and IDE"