#include <iostream>
#include <string>
#include <vector>
#include <SFML/Graphics.hpp>
#include "Simulation.hpp"

class ObjectBuilder {
private:
	std::string _name;
	sf::CircleShape _shape;
	sf::Vector2f _vel;
	sf::Vector2f _acc;
	float _mass;
public:
	ObjectBuilder();

	ObjectBuilder name(const std::string& name);
	ObjectBuilder shape(const sf::Color& col, const float& rad, const sf::Vector2f& pos);
	ObjectBuilder vel(const sf::Vector2f& vel);
	ObjectBuilder acc(const sf::Vector2f& acc);
	ObjectBuilder mass(const float& mass);

	Object build();

};

class Object {
private:
	const std::string name; 
	sf::CircleShape shape;
	sf::Vector2f pos;
	sf::Vector2f vel;
	sf::Vector2f acc;
	float rad;
	float mass;

	Object(const sf::Vector2f& pos, const sf::Vector2f& vel,
		   const sf::Vector2f& acc, const std::string& name, 
		   const sf::CircleShape& shape, const float& rad,
		   const float& mass);
public:
	friend class ObjectBuilder;
	friend class System;

	static ObjectBuilder builder();

	Object();

	sf::Vector2f next_pos(const float& dt);

	void move_obj(const float& dt);

	void draw_obj(sf::RenderWindow& window);
};

class Collision {
private:

public:
	void move(const float& dt) {
		
	}

};