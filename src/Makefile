CC = gcc
CFLAGS = -Wall -Werror -Wextra -g -std=c11

all: clean d3_string.a test gcov_report

test:
	$(CC) $(CFLAGS) --coverage tests/*.c *.c -o test -lcheck -lm
	./test

d3_string.a:
	$(CC) $(CFLAGS) *.c -c
	ar rc d3_string.a *.o
	ranlib d3_string.a

gcov_report:
	lcov -t "d3_string_test" -o fizzbuzz.info -c -d .
	genhtml -o report fizzbuzz.info
	open -a "Google Chrome" report/src/index.html

style: clean
	cp ../materials/linters/.clang-format ../src/.clang-format
	clang-format -style=Google -n *.c *.h tests/*.c tests/*.h
	rm .clang-format

clean:
	-rm -rf *.o && rm -rf *.gcno
	-rm -rf *.a && rm -rf *.gcda
	-rm -rf *.info && rm -rf *.gcov
	-rm -rf ./test && rm -rf ./gcov_report
	-rm -rf ./report/
	-rm -rf d3_test