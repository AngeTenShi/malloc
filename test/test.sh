set -e

#/bin/sh

echo "\n\n### SCALE (test0.c):"
gcc  -o ./test/test0.out ./test/scale/test0.c -L. -lft_malloc && ./test/run.sh /usr/bin/time -v ./test/test0.out

echo "\n\n### SCALE (test1.c):"
gcc -o ./test/test1.out ./test/scale/test1.c -L. -lft_malloc && ./test/run.sh /usr/bin/time -v ./test/test1.out

echo "\n\n### SCALE (test2.c):"
gcc -o ./test/test2.out ./test/scale/test2.c -L. -lft_malloc && ./test/run.sh /usr/bin/time -v ./test/test2.out

echo "\n\n### SCALE (test3.c):"
gcc -o ./test/test3.out ./test/scale/test3.c -L. -lft_malloc && ./test/run.sh /usr/bin/time -v ./test/test3.out

OPT="-Wno-unused-result -Wno-implicit-function-declaration"
gcc  -o ./test/test4.out ./test/scale/test4.c $OPT -L. -lft_malloc && ./test/run.sh /usr/bin/time -v ./test/test4.out

echo "\n\n### SCALE (test5.c):"
gcc -o ./test/test5.out ./test/scale/test5.c -L. -lft_malloc && ./test/run.sh /usr/bin/time -v ./test/test5.out
