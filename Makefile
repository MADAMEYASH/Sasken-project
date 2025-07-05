all:
	g++ -std=c++14 -Wall -pthread -c main.cpp
	g++ -std=c++14 -Wall -pthread -c TrafficLight.cpp
	g++ -std=c++14 -Wall -pthread -c Sensor.cpp
	g++ -std=c++14 -Wall -pthread -c Lane.cpp
	g++ -std=c++14 -Wall -pthread -c TrafficController.cpp
	g++ -std=c++14 -Wall -pthread -c PedestrianSignal.cpp
	g++ -std=c++14 -Wall -pthread -o traffic_sim main.o TrafficLight.o Sensor.o Lane.o TrafficController.o PedestrianSignal.o

clean:
	rm -f *.o traffic_sim
