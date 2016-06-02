g++ -Wall -std=c++11 -c Common.cpp -o ../obj/Common.o
g++ -Wall -std=c++11 -c Queue/Queue.cpp -o ../obj/Queue.o
g++ -Wall -std=c++11 -c Queue/PingQueue/PingQueue.cpp -o ../obj/PingQueue.o
g++ -Wall -std=c++11 -c main.cpp -o ../obj/main.o
g++ -Wall -o ../bin/Test ../obj/*.o
