all: main.o log.o graph.o Timer.o AlgLog.o
	g++ --std=c++17 ./src/main.o ./lib/log/log.o ./lib/graph/graph.o ./lib/Timer/Timer.o ./lib/AlgLog/AlgLog.o -lsfml-graphics -lsfml-window -lsfml-system -pthread -o ./bin/main


main.o: ./src/main.cpp ./lib/headers.hpp ./lib/linkedlist/linkedlist.hpp ./lib/graph/graph.hpp ./lib/MyVec/MyVec.hpp
	g++ --std=c++17 -c ./src/main.cpp -o ./src/main.o


log.o: ./lib/log/log.cpp ./lib/log/log.hpp
	g++ --std=c++17 -c ./lib/log/log.cpp -o ./lib/log/log.o


graph.o: ./lib/graph/graph.cpp ./lib/graph/graph.hpp
	g++ --std=c++17 -c ./lib/graph/graph.cpp -o ./lib/graph/graph.o

#linkedlist.o: ./lib/linkedlist/linkedlist.hpp 
#	g++ --std=c++17 -c ./lib/linkedlist/linkedlist.hpp -o ./lib/linkedlist/linkedlist.o


Timer.o: ./lib/Timer/Timer.cpp ./lib/Timer/Timer.hpp
	g++ --std=c++17 -c ./lib/Timer/Timer.cpp -o ./lib/Timer/Timer.o


AlgLog.o: ./lib/AlgLog/AlgLog.hpp ./lib/AlgLog/AlgLog.cpp
	g++ --std=c++17 -c ./lib/AlgLog/AlgLog.cpp -o ./lib/AlgLog/AlgLog.o


run_log:
	./bin/main > ./bin/output_main.txt


run:
	./bin/main


clean: 
	rm -f -v ./src/*.o ./lib/*/*.o ./bin/main


valg: main.o log.o graph.o
	g++ --std=c++17 -O0 ./src/main.o ./lib/log/log.o ./lib/graph/graph.o -o ./bin/main
	valgrind ./bin/main --leak-check=yes --track-origins=yes --show-mismatched-frees=yes 