#!/bin/bash


read d
function fun()
{
    local i=$1
    for (( j=0; j<i; j++  ))
    do
        echo hello
    done
}

fun d

#read n
#until [ $n -eq 0 ]
#do
#    if [ $n -eq 2 ] ; then
#        continue
#    fi
#    echo "hello world!"
#    let n--
#done

#while [ 1 -ne 2 ]
#do
#    :
#done

#for(( ; ; ))
#do
#    :
#done

#read i
#while [ $i -gt 0 ]
#do
#    echo "hello world"
#    let i--
#
#done>file

#n=$1
#function add()
#{
#    local n=$1
#    local m=$(($n-1))
#    
#    if [ m -gt 0 ]; then  
#        
#    fi
#
#}

#add $n
