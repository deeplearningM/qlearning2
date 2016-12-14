#ifndef QLEARNING_CONTROLLER_H
#define QLEARNING_CONTROLLER_H
#include <Box2D/Box2D.h>
#include <vector>
#include <tuple>
#include <iostream>
#include <fstream>
#include "network/NeuralNetwork.hpp"
#include "car/Car.hpp"
class Learning;
#include "network/Learning.hpp"
class Track;
#include "car/Track.hpp"


class Controller {
	friend class Learning;
public:
	Controller();
	void initializeRun(/*params?*/); // Application launched or previous car's run completely over, so start new run
	
	//---Generic getters
	const Car& getCar() const;
    	const Track& getTrack() const;

	//std::vector<double>& getActionForCar(Car& car, NeuralNetwork& nn) const;

	//---Getters for car
	const std::vector<float> getCarPosition() const;
	const std::vector<float> getSightVector(int size, int degrees);
	float getCarDistanceFromMiddle() const;
	float getCarDistanceTraveled() const;
	float getCarRotation() const;
	float getCarVelocity() const;

	//---Car actions and NN interraction
	std::vector<float> getCarAction(NeuralNetwork& nn);
	float getFitness() const;
	float getFitness(double time) const;

	//---Controller actions
    	void stepForward(); //Moves simulation; make call to NN and then ask physics to parse action
    
private:
	
	/***** General settings *****/
	const bool debugging = true;
	const bool carDebug = false;
	const bool writeActionsToFile = true; // car driving history; overwrites existing history files
	const int numberOfVisionLines = 5;
	const int fieldOfView = 90; // TODO: FoV slider
	
	/***** Simulation constants *****/
	const float32 timeStep = 1.0 / 60.0;
	const int32 velocityIterations = 8;   //how strongly to correct velocity
	const int32 positionIterations = 3;   //how strongly to correct position
	
	/***** Network building related constants *****/
	const std::vector<unsigned int> hiddenLayerSizes = std::vector<unsigned int> {4, 6}; 	// Adjust network node topology with this.
	const unsigned int layerCount = 2 + hiddenLayerSizes.size(); 							// Don't touch.
	const float nodeInitLow = -0.4;						// Randomized initial node weights are between these
	const float nodeInitHigh = 0.4;
	const int stateSize = numberOfVisionLines + 1;		// Don't touch. Add current velocity into state input vector.
	
	/***** Action-space search and learning-related constants *****/
	const int learningMode = 1;							// Which weight adjustment algorithm to use. Supported modes: 0 (no learning), 1 (racist gradient descent).
	const bool useSig = false;							// Whether to use sigmoid functions in network evaluation.
	const float defaultStepSize = 0.00001; 				// Learning rate; multiplies learned outcome's impact on network node weights
	const float actionDepth = 5; 						// How many variations of acceleration/turning values to test. Primary performance impact in network eval. Up to ~200 should be manageable.
	const float discountFactor = 0.1; 					// [0.0f, 1.0f); importance of "later" vs "now", with higher values increasing the impact of "now"
	float explorationCoefficient = 3; 					// Weighs exploration over exploitation in Q-search; decreases on each step until minimum
	const float minExplorationCoefficient = 0.05;
	const float explorationCoefficientDecrease = 0.001;
	const float prevWeightCoefficient = 0.2;			// How large impact the previous weight's magnitude has in learning
	const float prevValueCoefficient = 0.97;			// How important the previous value of a node is. Closer to 1 means "keep it the same" and closer to  0 means "discard old value; make radical changes into the targets"
	const float rewardMultiplier = 0.9;				// Multiplier on reward values to prevent crashing from overflows.
	const float qvalueMultiplier = 1.0;					// Don't adjust until the program crashes. Might make learning very buggy. Seek guidance from Esa and Simo first. You can not parse HTML with regex.
	Learning* trainer;
	
	/***** Reward function coefficients, see reward in Controller::takeStep() *****/
	const float timeToFitnessMultiplier = 1.2;			// Unused. Fitness function balancing multiplier.
	const float wallPenalty = -10000.0;			// Reward penalty for hitting a wall.
	const float prevVelocityCoefficient = 0.9;	// Reward multiplier for increasing speed vs going fast. Higher value means that increasing car speed is good. Only [0.0f, 1.0f] are sensible.

	/***** Controller variables *****/
	b2World* m_world;
	Car* currentCar;
	Track* currentTrack;
	NeuralNetwork currentNetwork;
	std::ofstream carActionFile;
	int runCounter;
	int stepCounter;
	float qvalue;
	
};

#endif
