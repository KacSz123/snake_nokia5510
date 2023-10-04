# Snake game



compilation of snake_ADT.o:

gcc -pedantic -Wall -c snake_ADT.c -o snake_ADT.o



compilation of example:

gcc -pedantic -Wall  snake_ADT.o example.c -o ex.out

debugger:

gcc -g snake_ADT.o example.c -o ex_deb.out

gdb ex_deb.out
