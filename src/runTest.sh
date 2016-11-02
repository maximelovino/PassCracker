#!/usr/bin/env bash
make

file="out.txt"

hashGenSource="../test.c"

# compile test.c beforehand

hashGenProgram="../a.out"
crackProgram="./crack"

SALT=43

declare -a PASSWORDS=("q" "lo" "mon" "gege" "hello" "manger")

for pass in ${PASSWORDS[@]}
do
	hash="$($hashGenProgram $pass $SALT)"
	echo $hash
	for (( i = 1; i <= 1024; i*=2 )); do
		echo $crackProgram
	 	echo $hash
	 	echo $SALT
	 	echo $i
 		$crackProgram $hash $SALT $i >> $file
	done
done

#length;threadCount;time
