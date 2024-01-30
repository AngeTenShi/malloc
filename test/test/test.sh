set -e

#/bin/sh

echo "\n\n### MY TEST:"
gcc -L. -lft_malloc -o ./test/test.out ./test/test.c && ./test/run.sh ./test/test.out

echo "\n\n### SCALE (test0.c):"
gcc -L. -lft_malloc -o ./test/test0.out ./test/scale/test0.c && ./test/run.sh /usr/bin/time -l ./test/test0.out

echo "\n\n### SCALE (test1.c):"
gcc -L. -lft_malloc -o ./test/test1.out ./test/scale/test1.c && ./test/run.sh /usr/bin/time -l ./test/test1.out

echo "\n\n### SCALE (test2.c):"
gcc -L. -lft_malloc -o ./test/test2.out ./test/scale/test2.c && ./test/run.sh /usr/bin/time -l ./test/test2.out

echo "\n\n### SCALE (test3.c):"
gcc -L. -lft_malloc -o ./test/test3.out ./test/scale/test3.c && ./test/run.sh /usr/bin/time -l ./test/test3.out

echo "\n\n### SCALE (test4.c):"
OPT="-Wno-unused-result -Wno-implicit-function-declaration"
gcc -L. -lft_malloc -o ./test/test4.out ./test/scale/test4.c $OPT && ./test/run.sh /usr/bin/time -l ./test/test4.out

echo "\n\n### SCALE (test5.c):"
gcc -L. -lft_malloc -o ./test/test5.out ./test/scale/test5.c && ./test/run.sh /usr/bin/time -l ./test/test5.out
