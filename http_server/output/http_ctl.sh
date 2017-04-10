#! /bin/bash

ROOT_PATH=$(pwd)
BIN=${ROOT_PATH}/httpd
CONF=${ROOT_PATH}/conf/ip_port
PID=${ROOT_PATH}/httpd.pid

function usage()
{
    printf "%s [start(-s)|stop(-t)|restart(-rt)]\n" "$(basename $0)"

}

function http_start()
{
    [[ -f $PID ]] && {
        printf "httpd.pid is exist! pid is $(cat $PID)\n"
        return
    }
    
    ip=$(grep -E '^IP:' $CONF | awk -F: '{print $2}')
    port=$(grep -E '^PORT:' $CONF |awk -F: '{print $2}')
    printf "ip:${ip} port:${port},bin: ${BIN}\n"
    return 
    $BIN $ip $port
    pidof $(basename $BIN) > $PID
    printf "start done, pid is : $(cat $pid)...\n"

}

function http_stop()
{
    [[ ! -f $PID ]] && {
        printf "httpd is not exist\n"
        return
    }
    pid=$(cat $PID)
    kill -9 $PID
    rm -f $PID
    printf "stop done ... \n"
}

[[ $# -ne 1 ]] &&{
    usage
    exit 1
}

case $1 in
    start | -s )
        printf "http_start ...\n" 
        http_start
        ;;
    stop | -t )
        http_stop
        ;;
    restart | -rt )
        http_stop
        http_start
        ;;
    * )
        usage
        exit 2
esac
