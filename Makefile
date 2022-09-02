.PHONY : clean all
all: dir lib test
dir:
	mkdir obj
test: dir lib
	g++ -g obj/test.o obj/tree.o obj/expression.o -o obj/test
lib: dir
	g++ -g -c test.cpp -o obj/test.o -I lib/
	g++ -g -c src/tree.cpp -o obj/tree.o -I lib/
	g++ -g -c src/gen_expression.cpp -o obj/expression.o -I lib/
clean:
	rm -rf obj