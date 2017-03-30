#!bin/bash +x


arr=(12 324 435 457)
for i in ${arr[*]}
do
    echo $i
done


#read n
#sum=0
#for(( i=0; i<=n; i++ ))
#do
#    let sum+=i
#done
#echo $sum

#read a
#case $a in
#    '1' )
#        echo hello
#        ;;
#    '2')
#        echo world
#        ;;
#    '3')
#        echo wond
#        ;;
#esac



#read a
#if [ $a -gt 10 ] ; then
#    echo "hello"
#elif [ $a -eq 10 ] ; then
#    echo "wond"
#else
#    echo "world"
#fi



#echo $(ls;pwd)
#
#
#val='a.bash'
#
#a=50
#b=100
#echo $/$
#echo $((a+b))


