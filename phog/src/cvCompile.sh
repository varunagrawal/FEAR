g++ `pkg-config opencv --cflags` $@ -o ${1:0:${#1}-4} `pkg-config opencv --libs`

