#!bin/sh
gcc -pg *.[ch]
rm *.gch
./a.out
