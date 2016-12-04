#ifndef QLEARNING_CAR_H
#define QLEARNING_CAR_H
#include <Box2D/Box2D.h>
#include "Physics.hpp"
#include <vector>
#include "../network/NeuralNetwork.hpp" // TODO: Shouldn't this go through the Controller?

class Car
{
public:
	// Constructors
	Car(b2World* world);
	~Car();

	// Getters
	float getVelocity() const;
	int getCheckpoints() const;
	NeuralNetwork& getNetwork();
	std::vector<float> getPosition() const;
	std::vector<float> getDistances();
	

	void update(); //Call this function to have car update its location speed etc
	void accelerate(int direction);
	void turn(int direction);
	
	// Variables for desired speed, current speed, current force applied and maximun force that can be applied
	float desiredSpeed = 0;
	float currentSpeed = 0;
	float force = 0;
	
	

private:
	// Variables for the body amd maximum speeds
	b2Body* carBody = nullptr;
	float maxSpeed = 100;
	float maxReverse = 50;
	float maxDriveForce = 500;
	float maxReverseForce = 250;
	float MaxTurningForce = 500;
	std::vector<float> distances;
	int checkpoints = 0;
	bool collision = false;
	
	b2World* world;
	Physics physics = Physics(world);

	NeuralNetwork network;
};



#endif
