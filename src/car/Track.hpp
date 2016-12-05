#ifndef QLEARNING_TRACK_H
#define QLEARNING_TRACK_H
#define DEGTORAD 0.0174532925199432957f
#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include <iostream>
#include <vector>
#include <tuple>

class Track {
public:
	Track(b2World* world);
	~Track();

	void GUI(std::vector<sf::VertexArray>);
	sf::VertexArray newSector(float width, float height, float angle, b2Vec2 middlePoint);

private:
	std::vector<b2Body*> circuit;
	b2World* world;
};

#endif
