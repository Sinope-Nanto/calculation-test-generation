.PHONY : clean all
all: dir basestruct test
dir:
	mkdir obj
test: dir basestruct
	g++ -g obj/test.o -o obj/test
basestruct: dir
	g++ -g -c test.cpp -o obj/test.o -I lib/
clean:
	rm -rf obj