g++ `pkg-config opencv gtk+-2.0 --cflags` $1 -o ${1:0:${#1}-4} `pkg-config opencv gtk+-2.0 --libs`

