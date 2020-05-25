all: a.exe

a.exe: main.cpp Makefile
	g++ main.cpp -O2 -std=c++11
	@echo "==== Build successful ===="

debug: 
	g++ main.cpp -O0 -g -std=c++11

assembly:
	g++ main.cpp -O2 -std=c++11 -S -g

run: all
	./a.exe

clean:
	rm a.exe

