all: traffic

traffic: main.cpp Lane.cpp TrafficLight.cpp Controller.cpp InputHandler.cpp Logger.cpp
	g++ -std=c++17 -pthread main.cpp Lane.cpp TrafficLight.cpp Controller.cpp InputHandler.cpp Logger.cpp -o traffic

clean:
	rm -f traffic *.o
