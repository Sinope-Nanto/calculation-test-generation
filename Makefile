.PHONY : clean all
all: basestruct test
	rm -f /obj/*.o
test: basestruct
	g++ obj/test.o -o obj/test
basestruct:
	g++ -c test.cpp -o obj/test.o -I lib/
clean:
	rm -f obj/*