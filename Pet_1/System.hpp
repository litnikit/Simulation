#include <iostream>
#include <string>
#include <vector>
#include <SFML/Graphics.hpp>
#include "Object.hpp"

class System {
private:
	std::vector<Object> objects;
	sf::Vector2i border;
	sf::Vector2f border_ns[4];
public:
	System(sf::Vector2i border);

	void add_obj(const Object& obj);

	void calc_vel(const float& dt);

	float is_collide(const Object& o1, const Object& o2, const float& dt);

	float is_collide_border(const Object& obj, const sf::Vector2f& n, const float& dt);

	void step(sf::Int32 dt);

	void draw_sys(sf::RenderWindow& window);
};