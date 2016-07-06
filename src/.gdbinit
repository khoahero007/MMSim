b main
r
b DRAMCommandIssue::tick if (timeStamp>=138)
#b DRAMCommandIssue::tick
#b DRAMDevice::isAvai
#b DRAMDevice::CR
#b CommandIssue/DRAMCommandIssue/DRAMCommandIssue.cpp:40
#b Mapping::map_port
#command
#print mapProp
#print in
#end

#b RRArbiter::isAvai if (in.size()!=3)
#b RRArbiter::sendPackage
#b FillRequester::tick
#b RRArbiter::isAvai
#b Mapping::isAvai
#b Mapping::map_port
#b Mapping::sendPackage
#b RRArbiter::tick
#b Arbiter/RRArbiter/RRArbiter.cpp:24
