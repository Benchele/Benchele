#!/bin/bash

nombre=$1
dig=$2
for archivo in ${nombre}[0-9]*;
do
	num=${archivo#$nombre}
	#Archivo = nombre12
	
	#A nombre quitale el la cadena "nombre" para tener el numero
	#Funcion-> num = nombre12 - nombre = 12
	
	p=$(printf "%0${dig}d" "$num")

	nuevo="${nombre}_$p"

	mv "$archivo" "$nuevo"
done
