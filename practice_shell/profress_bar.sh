#!/bin/bash

str=""
arr=("-" "/" "|" "\\")

for(( i=0; i<=100; i++ ))
do
    let s=$i%4
    printf "[%-100s][%c]%d%%\r" "$str" "${arr[$s]}" "$i"
    str=$str#
    sleep 0.1
done

printf "\n"
