#include "Controller.hpp"
#include <vector>

Controller::Controller() {
	// TODO: Esa: Does the constructor need any functionality?
}

const Track Controller::getTrack() const {
	return currentTrack; //this.currentTrack must have a class type
}
const Car Controller::getCar() const {
	return currentCar; //this.currentCar must have a class type
}

const std::vector<float> Controller::getSightVector(int amount, int degrees) const {
	// TODO: Olli/Jussi: Distances to walls in various directions, spanning a vision width of specified degrees.
	return currentCar.getDistances();
}

const std::vector<float> Controller::getCarPosition() const {
	// x and y-coordinates in that order
	return currentCar.getPosition();
}

float Controller::getCarDistanceFromMiddle() const {
	// TODO: Jussi: Implement function to get car middle point's distance from center of track
	return 0.0f;
}

float Controller::getCarVelocity() const {
	// TODO: Olli/Jussi: Return the car's current speed.
	return currentCar.getVelocity();
}

float Controller::getCarDistanceTraveled() const {
	// TODO Olli/Jussi Return how far the car has gone on the track
	//				   ie how many checkpoints it has reached
	return 0.0f;
}

// Ask neural network to provide a set of actions.
std::vector<float> Controller::getCarAction(NeuralNetwork& nn) {
	std::vector<float> params = getSightVector(numberOfVisionLines, fieldOfView); // TODO: Use some external constants?
	params.push_back(getCarVelocity());
	return currentCar.getNetwork().getOutputValuesFromInputs(params);
}

float Controller::getFitness() const {
	// TODO Jussi/Esa/Simo
	return getCarVelocity();
}

float Controller::getFitness(double time) const {
	// TODO Jussi/Esa/Simo
	return getCarDistanceTraveled() / time;
}

//Ask physics where the car would end up with actions in param
std::vector<float> Controller::simulateStepForward(Car& car, float steer, float accelerate) const {
	// TODO: Return vector such that:
	// vector[0] is 1 if the car has hit a wall, 0 otherwise
	// vector[1] vector[2] are the x,y coordinates ???
	// vector[3] is the velocity
	// vector[4] is the angle at which the car is facing maybe (???)
	std::vector<float> asd;
	return asd;
}

void Controller::stepForward() {
	// TODO: Esa: implement the main logic
}