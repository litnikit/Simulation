#include <iostream>
#include <string>
#include <vector>
#include <SFML/Graphics.hpp>
#include "Object.hpp"

class System {
private:
	std::vector<Object> objects;
	sf::Vector2i border;
public:
	System(sf::Vector2i border);

	void add_obj(const Object& obj);

	void calc_vel(const float& dt);

	bool is_collide(const Object& o1, const Object& o2);

	sf::Vector2f is_collide_border(const Object& obj);

	void step(sf::Int32 dt);

	void draw_sys(sf::RenderWindow& window);
};