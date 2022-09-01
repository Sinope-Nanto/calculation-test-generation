.PHONY : clean all
all: dir lib test
dir:
	mkdir obj
test: dir lib
	g++ -g obj/test.o obj/lib.o -o obj/test
lib: dir
	g++ -g -c test.cpp -o obj/test.o -I lib/
	g++ -g -c src/tree.cpp -o obj/lib.o -I lib/
clean:
	rm -rf obj