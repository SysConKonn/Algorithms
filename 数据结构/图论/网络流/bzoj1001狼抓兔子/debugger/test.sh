#!/bin/bash
g++ -g dtmkr.cpp -o d -O2
clear
g++ -g s.cpp -o s -O2
clear
g++ -g t.cpp -o t -O2
clear
mv d data
mv s data
mv t data
cd data
while true; do
    ./d > d.in
    ./s < d.in > s.out
    ./t < d.in > t.out
    diff s.out t.out
    if [ $? -ne 0 ] ;
    then 
	echo "Wrong Answer";
	emacs d.in;
	break;
    else
	echo "Accept";
    fi
done
