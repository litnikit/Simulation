#include "Object.hpp"



Object::Object(const sf::Vector2f& pos, const sf::Vector2f& vel,
			   const sf::Vector2f& acc, const std::string& name, 
			   const sf::CircleShape& shape, const float& rad,
			   const float& mass) :
			   pos(pos), vel(vel), acc(acc), name(name), shape(shape), rad(rad), mass(mass) {}

ObjectBuilder Object::builder() {
	return ObjectBuilder();
}

Object::Object() {
	shape.setRadius(0);
	shape.setOrigin(0, 0);
	shape.setFillColor(sf::Color::Red);
	pos = sf::Vector2f(0, 0);
	vel = sf::Vector2f(0, 0);
	mass = 0;
	rad = 0;
}

sf::Vector2f Object::next_pos(const float& dt) {
	return pos + vel * dt + acc * dt * dt / 2.f;
}

void Object::move_obj(const float& dt) {
	pos = next_pos(dt);
	vel += acc * dt;
	shape.setPosition(pos);
}

void Object::draw_obj(sf::RenderWindow& window) {
	window.draw(shape);
}

ObjectBuilder::ObjectBuilder() {
	this->_name = "Object";
	this->_mass = 1.;
	_acc = sf::Vector2f(0, 9.81f);
}

ObjectBuilder ObjectBuilder::name(const std::string& name) {
	this->_name = name;
	return *this;
}

ObjectBuilder ObjectBuilder::shape(const sf::Color& col, const float& rad, const sf::Vector2f& pos) {
	_shape.setFillColor(col);
	_shape.setRadius(rad);
	_shape.setOrigin(rad, rad);
	_shape.setPosition(pos);
	return *this;
}

ObjectBuilder ObjectBuilder::vel(const sf::Vector2f& vel) {
	this->_vel = vel;
	return *this;
}

ObjectBuilder ObjectBuilder::acc(const sf::Vector2f& acc) {
	this->_acc = acc;
	return *this;
}

ObjectBuilder ObjectBuilder::mass(const float& mass) {
	this->_mass = mass;
	return *this;
}

Object ObjectBuilder::build() {
	return Object(this->_shape.getPosition(), this->_vel, this->_acc, this->_name, this->_shape, this->_shape.getRadius(), this->_mass);
}
