g++ `pkg-config opencv --cflags` $@ svm.cpp -o ${1:0:${#1}-4} `pkg-config opencv --libs`

