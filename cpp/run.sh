#!/bin/sh

g++ $(find . -name "*.cpp") -o main
./main
rm main

