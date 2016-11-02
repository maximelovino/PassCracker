#!/usr/bin/env bash
make

file=out.txt

hashGenSource=../test.c

gcc $hashGenSource -lcrypt

hashGenProgram=../a.out
crackProgram=./crack

SALT=43

PASSWORDS=(q,lo,mon,gege,hello,manger)

for pass in ${PASSWORDS[@]}
do
	hash=$hashGenProgram $pass $SALT
	for (( i = 1; i <= 1024; i*=2 )); do
		$crackProgram $hash $SALT $i >> $file
	done
done

#length;threadCount;time
