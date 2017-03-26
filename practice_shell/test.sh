#!bin/bash


if [ $# -eq 0 ] ; then
    echo "${basename$0} [argv[0] ...]"

max=$1
min=$1
num=0
for i in $@
do
    if [ max -lt $i ] ; then
        max=$i
    fi
    if [ min -gt $i ] ; then
        min=$i
    num+=i
    fi
done

echo "$max"
echo "$min"
echo "obase=10 scale=2 $num" | bc


#a=$1
#b=$2
#c=$3
#max=0
#if [ $1 -lt $2 ] ;then
#    if [ $3 -lt $2 ] ;then
#        max=$2
#    else
#        max=$3 
#    fi
#else
#    if [ $1 -lt $3 ] ; then
#        max=$3
#    else
#        max=$1
#fi
#
#aver=$1+$2+$3
#echo $aver

#
#i=100
#function add()
#{
#    if [ i -gt 0 ] ;then
#        local num
#        let num=i+add i--
#    echo num
#}
#


#num=0;
#
#for i in {1..100}
#do
#    let num+=i
#done
#
#echo $num


##echo "please enter op:"
#
##read op
#
#case $1 in
#    star[tT] )
#        echo "hello start"
#    ;;
#    stop | -s | -t )
#        echo "hello stop"
#    ;;
#    'continue' )
#        echo "hello continue"
#    ;;
#    * )
#        echo "hello *"
#    ;;
#esac


#read tmp
#[ "X$tmp" == "Xhello" ] || {
#    echo "hello"
#}

#
#if : ;then
#    echo "hello"
#fiu


#read val
#if [ $val == 100 ]; then
#    echo "hello"
#elif [ $val -lt 100 ]; then
#    echo "xiaole $val"
#else
#    echo "dale $val"
#fi


#
#read tmp
#[ ! \( -f "test.sh" -a "X$tmp" == "Xhello" \) ]
#echo $?

#
#read tmp
#[ -d $tmp ]
#echo $?
#
#[ -f $tmp ]
#echo $?
#
#[ -c $tmp ]
#echo $?
#
#[ -b $tmp ]
#echo $?
###read val
###[ -z $val  ]
##echo $?
#[ "X$val" != "X" ]
#echo $?
##
#
