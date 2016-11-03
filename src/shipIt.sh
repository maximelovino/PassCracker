#!/usr/bin/env bash

if [[ -f groupe5.tar.gz ]]; then
	rm groupe5.tar.gz
fi

mkdir groupe5

cp bruteforce.c groupe5/bruteforce.c
cp bruteforce.h groupe5/bruteforce.h
cp crack.c groupe5/crack.c
cp makefile groupe5/makefile
cp range.txt groupe5/range.txt
if [[ -f groupe5.pdf ]]; then
	cp groupe5.pdf groupe5/groupe5.pdf
fi

tar -cvzf groupe5.tar.gz groupe5

rm -rf groupe5
