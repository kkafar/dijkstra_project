all: ./src/main.o ./lib/log/log.o 
	g++ --std=c++11 -o ./bin/main ./src/main.o ./lib/log/log.o

./src/main.o: ./src/main.cpp ./lib/headers.hpp
	g++ --std=c++11 -c ./src/main.cpp -o ./src/main.o

log.o: ./lib/log/log.cpp ./lib/log/log.hpp
	g++ --std=c++11 -c -o ./lib/log/log.o ./lib/log/log.cpp ./lib/log/log.hpp


run:
	./bin/main

clean: 
	rm -f -v -i ./src/*.o