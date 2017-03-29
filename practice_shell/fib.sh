#/bin/bash

a=1
b=2

read n
if [ $n -eq 1 ] ; then
    c=$a
fi
if [ $n -eq 2 ] ; then
    c=$b
fi
for(( i=2; i<n; i++ ))
do
    let c=$a+$b;
    a=$b
    b=$c
done

echo $c

#arr[0]=1
#arr[1]=1
#i=0
#read n
#
#while [ $i -le $n ]
#do
#    arr[$i+2]=arr[$i]+arr[$i+1]
#    let i++
#done
#
#echo ${arr[$i]}
