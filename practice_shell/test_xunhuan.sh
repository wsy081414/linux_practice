#!/bin/bash


for i in $@
do
    echo $i
done

#for (( i=1; i<=$#; i++ ))
#do
#    echo $@[$i]
#done


#count=3
#while [ $count -gt 0 ]
#do
#    printf "please enter your name\n"
#    read name
#    if [ "X$name" == "Xadmin"  ];then
#        echo "welcome"
#        break
#    else
#        let count--
#        echo "try again : times->$count"
#    fi
#done
#
#if [ $count -eq 0 ] ; then
#    echo "failed"
#else
#    echo 'success'
#fi

#i=100
#until [ $i -eq 1 ]
#do
#    echo "$i"
#    
#done



#i=100
#while [ $i -eq 100 ]
#do
#    echo "hello world!" 
#done

#for i in {a..z}
#do
#    rm file$i
#done

#sum=0
#str=0
#for(( i=1; i<100; i++ ))
#do
#    let sum+=i
#    str=$str+$i
#done
#echo $str=$sum
