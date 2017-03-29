#!/bin/bash


cat file
while read line
do
    a=$(echo $line|cut -c 1-3)
    b=$(echo $line|cut -c 4-6)
    c=$(echo $line|cut -c 7-9)

    tmp=$a
    a=$c
    c=$tmp
    b=$(echo $b|tr '[a-z]' '[A-Z]')

    n=$a$b$c
    echo $n 
done < file


#val="hello world!"
#
#echo ${val}|cut -d "w" -f2 


#echo ${val:0-7:3}


#echo ${val#*o}
#echo ${val##*o}
#echo ${val%o*}
#echo ${val%%o*}



#
#val="hello world"
#echo ${val#* }
#
