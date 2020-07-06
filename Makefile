all: main.o log.o
	g++ --std=c++11 ./src/main.o ./lib/log/log.o -o ./bin/main

main.o: ./src/main.cpp ./lib/headers.hpp ./lib/linkedlist/linkedlist.hpp
	g++ --std=c++11 -c ./src/main.cpp -o ./src/main.o

log.o: ./lib/log/log.cpp ./lib/log/log.hpp
	g++ --std=c++11 -c ./lib/log/log.cpp -o ./lib/log/log.o

#linkedlist.o: ./lib/linkedlist/linkedlist.hpp 
#	g++ --std=c++11 -c ./lib/linkedlist/linkedlist.hpp -o ./lib/linkedlist/linkedlist.o

run:
	./bin/main

clean: 
	rm -f -v -i ./src/*.o