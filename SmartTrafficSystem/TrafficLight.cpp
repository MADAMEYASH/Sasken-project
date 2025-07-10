#include "TrafficLight.h"

TrafficLight::TrafficLight() : state(RED) {}

void TrafficLight::changeToGreen() {
    state = GREEN;
}

void TrafficLight::changeToRed() {
    state = RED;
}

void TrafficLight::changeToYellow() {
    state = YELLOW;
}

LightState TrafficLight::getState() const {
    return state;
}
