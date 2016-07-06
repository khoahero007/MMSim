g++ -g -Wall -std=c++11 -c Common.cpp -o ../obj/Common.o >> log

g++ -g -Wall -std=c++11 -c Queue/Queue.cpp -o ../obj/Queue.o 
g++ -g -Wall -std=c++11 -c Queue/PingQueue/PingQueue.cpp -o ../obj/PingQueue.o 

g++ -g -Wall -std=c++11 -c Requester/Requester.cpp -o ../obj/Requester.o
g++ -g -Wall -std=c++11 -c Requester/TimedRequester/TimedRequester.cpp -o ../obj/TimedRequester.o 
g++ -g -Wall -std=c++11 -c Requester/FillRequester/FillRequester.cpp -o ../obj/FillRequester.o

g++ -g -Wall -std=c++11 -c Arbiter/Arbiter.cpp -o ../obj/Arbiter.o
g++ -g -Wall -std=c++11 -c Arbiter/PriorityArbiter/PriorityArbiter.cpp -o ../obj/PriorityArbiter.o
g++ -g -Wall -std=c++11 -c Arbiter/RRArbiter/RRArbiter.cpp -o ../obj/RRArbiter.o

g++ -g -Wall -std=c++11 -c Mapping/Mapping.cpp -o ../obj/Mapping.o
g++ -g -Wall -std=c++11 -c AddressMap/AddressMap.cpp -o ../obj/AddressMap.o

g++ -g -Wall -std=c++11 -c MemDevice/DRAMDevice/DRAMDevice.cpp -o ../obj/DRAMMemDevice.o
g++ -g -Wall -std=c++11 -c MemDevice/MemDevice.cpp -o ../obj/MemDevice.o

g++ -g -Wall -std=c++11 -c CommandIssue/CommandIssue.cpp -o ../obj/CommandIssue.o
g++ -g -Wall -std=c++11 -c CommandIssue/DRAMCommandIssue/DRAMCommandIssue.cpp -o ../obj/DRAMCommandIssue.o

g++ -g -Wall -std=c++11 -c main.cpp -o ../obj/main.o >> log
g++ -g -Wall -o ../bin/Test ../obj/*.o >> log
