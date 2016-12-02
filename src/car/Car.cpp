#include "Car.hpp"




Car::Car()
{
	//physics = new Physics(); TODO: CHECK THIS
	world = physics.getWorld();
	//Create definition for car body
	b2BodyDef carBodyDef;
	carBodyDef.type = b2_dynamicBody;

	//Set the initial position and angle and then create the body
	carBodyDef.position.Set(0, 0);
	carBodyDef.angle = 0; //set the starting angle
	carBody = world->CreateBody(&carBodyDef);
	carBody->SetAngularDamping(3);

	b2PolygonShape carShape;
	// Car is somewhat long and a bit wide
	carShape.SetAsBox(2.5f, 1.5f);

	b2FixtureDef carFixtureDef;
	carFixtureDef.shape = &carShape;
	// Density controls the mass of the car
	carFixtureDef.density = 1;
	// Restitution is how bouncy it is, eg. 0 no bounce and 1 all kinetic energy is conserved in collisions
	carFixtureDef.restitution = 0.25;
	// Well, friction
	carFixtureDef.friction = 0.5;
	carBody = world->CreateBody(&carBodyDef);
	carBody->CreateFixture(&carFixtureDef);
}


Car::~Car()
{
	carBody->GetWorld()->DestroyBody(carBody);
	
}

b2Vec2 Car::getForwardVelocity() const {
	b2Vec2 currentForwardNormal = carBody->GetWorldVector(b2Vec2(1, 0));
	return b2Dot(currentForwardNormal, carBody->GetLinearVelocity()) * currentForwardNormal;
}

b2Vec2 Car::getLateralVelocity() const {
	b2Vec2 currentRightNormal = carBody->GetWorldVector(b2Vec2(0, 1));
	return b2Dot(currentRightNormal, carBody->GetLinearVelocity()) * currentRightNormal;
}

void Car::updateDistances()
{
	distances = physics.updateRays(*carBody);
}





void Car::accelerate(int direction)
{
	// Get current forward speed and set force
	b2Vec2 currentForwardNormal = getForwardVelocity();
	force = 0;

	// Set desired speed in relation to if we are reversing or going forward
	if (direction > 0) {
		desiredSpeed = maxSpeed;
	}
	else {
		desiredSpeed = maxReverse;
	}


	currentForwardNormal = carBody->GetWorldVector(b2Vec2(1, 0));

	currentSpeed = b2Dot(getForwardVelocity(), currentForwardNormal);

	//Depending on current speed the amount of force is determined
	if (desiredSpeed > currentSpeed) {
		force = maxDriveForce;
	}
	else if (desiredSpeed < currentSpeed) {
		force = -maxReverseForce;
	}
	else {
		return;
	}

	// Apply the force
	if (direction > 0) {
		carBody->ApplyForce(force * currentForwardNormal, carBody->GetWorldCenter(), false);
	}
	else {
		carBody->ApplyForce(-force * currentForwardNormal, carBody->GetWorldCenter(), false);
	}

}


void Car::turn(int direction)
{
	if (direction > 0) {
		carBody->ApplyTorque(MaxTurningForce, true);
	}
	else {
		carBody->ApplyTorque(-MaxTurningForce, true);
	}
}




// function for returning just the distances to walls
std::vector<float> Car::getDistances() const {
	return distances;
}
NeuralNetwork & Car::getNetwork()
{
	return network;
}
std::vector<float> Car::getPosition() const
{
	b2Vec2 pos = carBody->GetPosition();
	std::vector<float> position;
	position.push_back(pos.x);
	position.push_back(pos.y);
	return position;
}

float Car::getVelocity() const
{
	return getForwardVelocity().Length();
}

b2Body * Car::getCarBody() const
{
	return carBody;
}