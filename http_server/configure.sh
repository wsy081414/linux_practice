
SRC=$(echo *.c)
OBJ=$(echo ${SRC} | sed 's/\.c/\.o/g')
SERVER_NAME=httpd
CC=gcc
OPTION=lpthread
cat << EOF > Makefile

${SERVER_NAME} :${OBJ}
    ${CC} -o \$@ \$^ -${OPTION}
%.o :%.c 
    ${CC} -c \$<

.PHONY :clean
clean:
    rm -rf ${SERVER_NAME} ${OBJ}
EOF
