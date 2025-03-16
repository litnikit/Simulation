#include "System.hpp"
#include <cmath>
#include <iostream>

System::System(sf::Vector2i border) : objects(std::vector<Object>()), border(border) {}

float dot(const sf::Vector2f& v1, const sf::Vector2f& v2) {
	return v1.x * v2.x + v1.y * v2.y;
}

bool System::is_collide(const Object& o1, const Object& o2) {
	sf::Vector2f r = o1.pos - o2.pos;
	return (std::sqrt(dot(r, r)) < o1.rad + o2.rad);
}

sf::Vector2f System::is_collide_border(const Object& obj) {
	if (obj.pos.x <= obj.rad) return sf::Vector2f(1, 0);
	if (obj.pos.y <= obj.rad) return sf::Vector2f(0, 1);
	if (obj.pos.x + obj.rad >= border.x) return sf::Vector2f(-1, 0);
	if (obj.pos.y + obj.rad >= border.y) return sf::Vector2f(0, -1);
	return sf::Vector2f(0, 0);
}



void System::add_obj(const Object& obj) {
	this->objects.push_back(obj);
}

void System::calc_vel(const float& dt) {
	for (int i = 0; i < objects.size(); i++) {

		auto& obj_1 = objects[i];

		sf::Vector2f n = is_collide_border(obj_1);

		if (n != sf::Vector2f(0, 0)) {

			int sgn = n.x + n.y;
			float c = -(sgn - 1) / 2 * (n.x * border.x + n.y * border.y);
			float v = dot(obj_1.vel, n), a = dot(obj_1.acc, n), x = dot(obj_1.pos, n);
			float border_distance = -x + obj_1.rad + c;
			float t_collide = (a != 0.f) ? 
				(-v - std::sqrt(v * v + 2 * a * border_distance)) / a :
				border_distance / v;

			obj_1.move_obj(t_collide);
			obj_1.vel -= 2 * dot(obj_1.vel, n) * n;
			if(t_collide < 0) obj_1.move_obj(dt + t_collide);
		}

		for (int j = i + 1; j < objects.size(); j++) {

			auto& obj_2 = objects[j];

			if (is_collide(obj_1, obj_2)) {

				float massDiff = obj_1.mass - obj_2.mass, massSum = obj_1.mass + obj_2.mass;
				sf::Vector2f old_1 = obj_1.vel, old_2 = obj_2.vel;

				obj_1.vel = (massDiff * old_1 + 2 * obj_2.mass * old_2) / massSum;

				obj_2.vel = (-massDiff * old_2 + 2 * obj_1.mass * old_1) / massSum;
			}
		}
	}
}


void System::step(sf::Int32 dt) {
	
	float ms_dt = dt / 100.;

	for (auto& obj : objects) {
		obj.move_obj(ms_dt);
	}

	calc_vel(ms_dt);
}

void System::draw_sys(sf::RenderWindow& window) {
	for (auto& obj : objects) {
		window.draw(obj.shape);
	}
}
