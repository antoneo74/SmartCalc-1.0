CC = gcc
CFLAGS = -Wall -Wextra -Werror
PROFILE_FLAGS = -fprofile-arcs -ftest-coverage
OS := $(shell uname -s)

ifeq ($(OS), Darwin)
	CC += -D OS_MAC
else
	CC += -D OS_LINUX
endif

all: clean test gcov_report

default: all

clean:
	-rm -rf test *.out *.o *.a *.cfg fizz *.gc* *.info report build test RESULT_VALGRIND.txt

rebuild: clean all

valgrind:
	valgrind --leak-check=full --show-reachable=no --show-leak-kinds=all --track-origins=yes --verbose --log-file=RESULT_VALGRIND.txt ./test
	
check:
	cp ../materials/linters/.clang-format ./
	clang-format -i *.h *.c
	clang-format -n --verbose *.h *.c
	rm -rf ".clang-format"
	@ echo "Google style check is Done"

test: calc.a
ifeq ($(OS), Darwin)
	$(CC) $(CFLAGS) -o test test.c calc.a -lcheck -coverage
	./test
else
	$(CC) $(CFLAGS) -o test test.c calc.a -lcheck -lsubunit -lrt -lpthread -lm -coverage
	./test
endif


calc.a: calc.o
	ar rcs calc.a calc.o
	ranlib calc.a

calc.o:  calc.c calc.h
	$(CC) -c calc.c


gcov_report:
ifeq ($(OS), Darwin)
	$(CC) --coverage $(PROFILE_FLAGS) test.c calc.c -o test -lcheck
else 
	$(CC) --coverage $(PROFILE_FLAGS) test.c calc.c -o test -lcheck -lsubunit -lrt -lpthread -lm
endif
	./test
	lcov -t "test" -o test.info -c -d ./
	genhtml -o report test.info
ifeq ($(OS), Darwin)
	open ./report/index-sort-f.html
else
	xdg-open ./report/index-sort-f.html
endif
	rm -rf ./*.gcno ./*.gcda ./GcovReport.* 


###################
# Building QT app #
###################

QT_PROJECT_NAME = SmartCalc
QT_PROJECT_FOLDER = ./$(QT_PROJECT_NAME)
QT_PRO = $(QT_PROJECT_NAME).pro
QT_MAKEFILE = $(QT_PROJECT_NAME)_Makefile
QT_BUILD_FOLDER = Build
QT_APP_FOLDER = ../App
DIST_FOLDER_NAME = SmartCalc-1.0

generate_make:
	@qmake $(QT_PROJECT_FOLDER)/$(QT_PRO) -o ./$(QT_BUILD_FOLDER)/$(QT_MAKEFILE)
	@rm -rf .qmake.stash

install: generate_make
	@echo "Building application..."
	@cd ./$(QT_BUILD_FOLDER) && make -sf $(QT_MAKEFILE)
	@echo "Application builded."
	@echo -n "Moving application to folder \"$(QT_APP_FOLDER)\"..."
	@mkdir ./$(QT_APP_FOLDER)
ifeq ($(OS), Darwin)
	@mv ./$(QT_BUILD_FOLDER)/$(QT_PROJECT_NAME).app/Contents/MacOS/SmartCalc ./$(QT_APP_FOLDER)/$(QT_PROJECT_NAME).app
else
	@mv ./$(QT_BUILD_FOLDER)/$(QT_PROJECT_NAME) ./$(QT_APP_FOLDER)/$(QT_PROJECT_NAME)
endif
	@echo " Done."
	@echo -n "Deleting build folder..."
	@rm -rf $(QT_BUILD_FOLDER)
	@echo " Done."
	@echo "Installation complete!"

uninstall:
	@echo -n "Uninstalling application..."
	@rm -rf $(QT_APP_FOLDER)
	@echo " Done."

dist:
	@echo -n "Creating \"$(DIST_FOLDER_NAME).tar.gz\"..."
	@rm -rf $(DIST_FOLDER_NAME)
	@mkdir ./$(DIST_FOLDER_NAME)
	@cp *.c ./$(DIST_FOLDER_NAME)/
	@cp *.h ./$(DIST_FOLDER_NAME)/
	@cp Makefile ./$(DIST_FOLDER_NAME)/
	@cp *.md ./$(DIST_FOLDER_NAME)/
	@cp -r SmartCalc ./$(DIST_FOLDER_NAME)/
	@tar -cf $(DIST_FOLDER_NAME).tar.gz ./$(DIST_FOLDER_NAME)
	@rm -rf $(DIST_FOLDER_NAME)
	@echo " Done."

dvi:
ifeq ($(OS), Darwin)
	@markdown documentation.md > documentation.html
	@open documentation.md
else
	@markdown documentation.md > documentation.html
	@xdg-open documentation.html
endif
