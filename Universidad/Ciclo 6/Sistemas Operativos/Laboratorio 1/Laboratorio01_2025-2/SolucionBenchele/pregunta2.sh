#!/bin/bash

for (( i=1; i<12; i++ )) 
do
	if (( i < 9 )); then
		p="0$i"
	else
		p=$i
	fi
	mv temp$i temp_$p

done
