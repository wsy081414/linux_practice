#! /bin/bash

ROOT_PATH=$(pwd)

SRC=$(echo *.c)
OBJ=$(echo ${SRC} | sed 's/\.c/\.o/g')
SERVER_NAME=httpd
CC=gcc
OPTION=lpthread


#cgi 
CGI_PATH=${ROOT_PATH}/cgi/cgi_bin
MATH_SRC=$(ls $CGI_PATH | grep 'math' | grep -E '.c$')
MATH_CGI_BIN=cgi_math

#cgi Makefile
cat << EOF >$CGI_PATH/Makefile

${MATH_CGI_BIN}:${MATH_SRC}
    $CC -o \$@ \$^

.PHONY:clean
clean:
    rm -f $MATH_CGI_BIN

.PHONY:output
output:
    cp $MATH_CGI_BIN ./../..
EOF

#http Makefile
cat << EOF > Makefile
.PHONY:all
all:${SERVER_NAME} cgi


${SERVER_NAME} :${OBJ}
    ${CC} -o \$@ \$^ -${OPTION}
%.o :%.c 
    ${CC} -c \$<

.PHONY:cgi
cgi:
    cd cgi;cd cgi_bin;make;make output;cd -;cd ..;
    cp -rf ${ROOT_PATH}/cgi/cgi_bin ${ROOT_PATH}/wwwroot

.PHONY :clean
clean:
    rm -rf ${SERVER_NAME} ${OBJ} output cgi_math; cd cgi;cd cgi_bin;make clean;cd -;cd .. 
    rm -rf ${ROOT_PATH}/wwwroot/cgi_bin
.PHONY :output
output:all
    mkdir output
    cp -rf log output/
    cp -rf conf output/
    cp -rf wwwroot output/
    cp -r http_ctl.sh output/
    cp -r ${SERVER_NAME} output/

EOF
