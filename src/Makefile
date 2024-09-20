CC=g++
CCFLGS=-Wall -Werror -Wextra -std=c++17
GTESTFLAGS=-lgtest_main -lgtest -lm

MODEL=Model/Model_3DViewer.cc

install: uninstall
	cd View && qmake ViewerFrontend.pro && make && make clean && rm Makefile && mkdir ../build && mv ViewerFrontend.app/$(UI_BIN) ../build
	cd build && open  ViewerFrontend.app

uninstall:
	rm -rf build
