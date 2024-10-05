CC = gcc
CPPFLAGS = -ggdb -Wall -Wextra -std=c++17 -lstdc++
TEST_FLAGS = -lgtest -fprofile-arcs -ftest-coverage
LCOV_FLAGS = --ignore-errors inconsistent --exclude '/Applications/Xcode.app/*' --exclude '/usr/local/include/gtest/*'
GENHTML_FLAGS = --ignore-errors inconsistent --ignore-errors corrupt
GTESTFLAGS=-lgtest_main -lgtest -lm

MODEL=model/Model_3DViewer.cc
MODEL_TEST=tests/test.cc

all: clean install

install: uninstall
	cd view && qmake ViewerFrontend.pro && make && make clean && rm Makefile && mkdir ../build && mv ViewerFrontend.app 3D_Viewer.app && mv 3D_Viewer.app/$(UI_BIN) ../build
	open build/3D_Viewer.app
	
uninstall:
	rm -rf build

tests: clean 
	$(CC) --coverage $(MODEL) $(MODEL_TEST) -o test_model $(GTESTFLAGS) $(CPPFLAGS) 
	./test_model

lcov:
	brew install lcov

brew:
	cd
	curl -fsSL https://rawgit.com/kube/42homebrew/master/install.sh | zsh

gcov_report: clean tests
	lcov -t "test_model" -o test_model.info --ignore-errors inconsistent --no-external -c -d .
	genhtml ./test_model.info --output-directory ./report/ $(GENHTML_FLAGS)
	open ./report/index.html

clean:
	rm -rf a.out test_model *.o  *.gc* *.gcno *.info report vertex*.txt face.txt test_model.dSYM
