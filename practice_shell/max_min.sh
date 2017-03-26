#!/bin/bash -x

if [ $# -eq 0 ] ; then
    echo "$(basename$0) [argv[0] ...]"
    exit 1
fi


#max=$1
#min=$1
#num=0
#conut=$#
#for j in @#
#do
#for((  i=$j; i<$@; i++ ))
#do
#    if [ max < $i ] ; then
#        echo $i
#        max=$i
#    fi
#    printf "\n"
#    if [ min > $i ] ; then
#        min=$i
#    fi
#    num+=$i
#done
#done
#echo $max
#echo $min
#echo "ibase=10; scale=2; $num/$#" | bc


max=$1
min=$1
num=0
for i in $@
do
    if [ $max -lt $i ] ; then
        max=$i
    fi

    if [ $min -gt $i ] ; then
        min=$i
    fi

    let    num+=$i
done

echo "$max"
echo "$min"
echo "ibase=10; scale=2; $num/$#" | bc


