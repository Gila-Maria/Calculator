GCC_C= gcc -c
GCC_G= gcc -g
FLAGS= -Wall -Werror -Wextra -std=c11
LDFLAGS= $(shell pkg-config --cflags --libs check) -lm
LIBRARY = SmartCalc_v1.a
TEST = TEST.c

ifeq (${OS}, Linux)
      TEST_FLAGS = -lcheck -lm -lpthread -lrt -lsubunit
else
      TEST_FLAGS = -lcheck -lm
endif


all: install

$(LIBRARY): clean
	$(GCC_C) -g *.c
	ar rc $(LIBRARY) *.o
	ranlib $(LIBRARY) 
	rm -f *.o
	
test : $(LIBRARY)
	${GCC_G} ${FLAGS} ${TEST} ${LIBRARY} -o st ${LDFLAGS}
	./st

install:
	cd Calculator && qmake && make && make clean
	cp -r Calculator/Calc.app ~/Desktop

uninstall:
	rm -rf Calculator/Calc.app 
	rm -rf ~/Desktop/Calc.app
	rm -rf Calculator/Makefile

dvi:
	doxygen Doxyfile.txt

ifeq (${OS}, Linux)
     firefox ./html/index.html
else
	open ./html/index.html
endif
	
dist: install
	mkdir archiv
	cp -r *.c *.h Makefile Calculator/ archiv
	tar -cvzf Calculator.tar.gz archiv
	rm -rf archiv

gcov_report: $(LIBRARY)
	 ${GCC_G} ${FLAGS} --coverage TEST.c SmartCalc.c  ${LDFLAGS} -o run_test
	./run_test
	lcov -t "test" --no-external -o test.info -c -d .
	genhtml -o report test.info
	open report/index.html

check_style:
	clang-format -style=google -n *.c *.h

correct_style:
	clang-format -style=google -i *.c *.h

leaks: test
	leaks -atExit -- ./st

clean:
	rm -rf *.o *.a st* *.g* *.info *.out* run* report* latex html 
	rm -rf Calculator.tar.gz
	cd Calculator && rm -rf Calc.app

rebuild: clean all
