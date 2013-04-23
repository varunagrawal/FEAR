g++ `pkg-config opencv --cflags` $1 -o ${1:0:${#1}-4} `pkg-config opencv --libs`
