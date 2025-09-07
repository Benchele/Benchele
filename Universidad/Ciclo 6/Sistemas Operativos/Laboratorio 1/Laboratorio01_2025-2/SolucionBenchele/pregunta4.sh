#!/bin/bash


nombre_usu=$1
#echo "Grupo | Usuarios"
#
#cat group | tr ":" " " | awk -F 1, 3 | grep "$nombre_usu"
##awk -F: -v user="$nombre_usu" '$4 ~ user {print $1, $3}' group
#  -F:  Indica que esta separado por ":"
# -v: Indica que se esta usando una variable
# $4 ~ user = indicca si el patron de user esta dentro del tercer campo
# {print $1, $3}: Imprimen las columnas 1 y 3
echo "Grupos: "
echo "-------------------" 
awk -F: -v user="$nombre_usu" '$4 ~ user {print $1}' group
