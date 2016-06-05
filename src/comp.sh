g++ -g -Wall -std=c++11 -c Common.cpp -o ../obj/Common.o >> log

g++ -g -Wall -std=c++11 -c Queue/Queue.cpp -o ../obj/Queue.o >> log 
g++ -g -Wall -std=c++11 -c Queue/PingQueue/PingQueue.cpp -o ../obj/PingQueue.o >> log

g++ -g -Wall -std=c++11 -c Requester/Requester.cpp -o ../obj/Requester.o >> log
g++ -g -Wall -std=c++11 -c Requester/TimedRequester/TimedRequester.cpp -o ../obj/TimedRequester.o >> log 

g++ -g -Wall -std=c++11 -c main.cpp -o ../obj/main.o >> log
g++ -g -Wall -o ../bin/Test ../obj/*.o >> log
