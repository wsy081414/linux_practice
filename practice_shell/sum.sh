#!/bin/bash

n=$1
function add()
{
    local tmp
    local tmp1
    tmp="$1"
    if [ ${tmp} -eq 1 ]; then
        echo -n "1 "
        r=1
    else
        echo -n "${tmp} +"
        tmp1=$(( ${tmp}-1 ))
        add $tmp1
        r=$(( ${tmp}+${r} ))
    fi
}
read val
add "$val"
echo "res : $r"

