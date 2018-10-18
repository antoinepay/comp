cat $1 | ./compilateur > main.s
as -o main.o main.s
gcc -o main main.o
