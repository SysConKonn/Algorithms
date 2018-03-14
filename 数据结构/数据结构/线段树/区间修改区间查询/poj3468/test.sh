#!/bin/bash
g++ -g dtmkr.cpp -o d
g++ -g ASPI.cpp -o a
g++ -g std.cpp -o b
while true; do
    ./d
    ./a < p.in > a.out
    ./b < p.in > b.out
    diff b.out a.out
    if [ $? -ne 0 ] ; then break; fi
done
