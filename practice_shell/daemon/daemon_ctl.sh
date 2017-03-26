#!bin/bash

#进行命令替换，
bin_path=$(pwd)
bin=mydaemon
pid=bin.pid
if [ -z "$1" ];then
    echo "$bin [start(-s)|stop(-t)|restart(-r)]"
    exit 1
fi

case "$1" in
    start | -s )
        ${bin_path}/${bin} > $bin_path/$pid
    ;;
    stop | -t )
        id=$(cat $bin_path/$pid)
        kill -9 $id
        >$bin_path/$pid
    ;;
    restart | -r )
        :
    ;;
    * )
    ;;
esac
