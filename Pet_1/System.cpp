#include "System.hpp"
#include <cmath>
#include <iostream>

System::System(sf::Vector2i border) : objects(std::vector<Object>()), border(border) {
	border_ns[0] = sf::Vector2f(0, 1);
	border_ns[1] = sf::Vector2f(-1, 0);
	border_ns[2] = sf::Vector2f(0, -1);
	border_ns[3] = sf::Vector2f(1, 0);
}

float dot(const sf::Vector2f& v1, const sf::Vector2f& v2) {
	return v1.x * v2.x + v1.y * v2.y;
}

float norm(const sf::Vector2f& v1) {
	return std::sqrt(dot(v1, v1));
}

float System::is_collide(const Object& o1, const Object& o2, const float& dt) {
	sf::Vector2f x = o1.pos - o2.pos, v = o1.vel - o2.vel;
	float R = o1.rad + o2.rad;
	float c = (x.x * v.y - x.y * v.x) / (R * norm(v));
	if (std::fabs(c) > 1) return dt + 1;

	float angle_1 = std::acos(c) - std::acos(v.y / norm(v)),
		  angle_2 = std::acos(c) + std::acos(v.y / norm(v));

	float t_1 = R / v.x * std::cos(angle_1) - x.x / v.x,
		  t_2 = R / v.x * std::cos(angle_2) - x.x / v.x;
	if (t_1 < 0 || t_2 < 0) return dt + 1;
	return std::fmin(t_1, t_2);
}

float System::is_collide_border(const Object& obj, const sf::Vector2f& n, const float& dt) {
	int sgn = n.x + n.y;
	float c = -(sgn - 1) / 2 * (n.x * border.x + n.y * border.y);
	float v = dot(obj.vel, n), a = dot(obj.acc, n), x = dot(obj.pos, n);
	float border_distance = -x + obj.rad + c;
	float t_collide;

	if (a != 0.f) {
		float D = v * v + 2 * a * border_distance;
		t_collide = D >= 0 ? (-v - std::sqrt(D)) / a : dt + 1;
	}
	else t_collide = border_distance / v;

	return (t_collide >= dt || t_collide <= 0) ? dt + 1: t_collide;
}



void System::add_obj(const Object& obj) {
	this->objects.push_back(obj);
}

void System::calc_vel(const float& dt) {

	std::vector<std::vector<float>> t_collide_ball(objects.size(), std::vector<float>(objects.size()));
	std::vector<std::vector<float>> t_collide_border(objects.size(), std::vector<float>(4));

	float t_min = dt;
	for (int i = 0; i < objects.size(); i++) {
		for (int j = 0; j < 4; j++) {
			t_collide_border[i][j] = is_collide_border(objects[i], border_ns[j], dt);
			t_min = t_collide_border[i][j] < t_min ? t_collide_border[i][j] : t_min;
		}

		for (int j = i + 1; j < objects.size(); j++) {
			t_collide_ball[i][j] = is_collide(objects[i], objects[j], dt);
			t_min = t_collide_ball[i][j] < t_min ? t_collide_ball[i][j] : t_min;
		}
	}

	for (auto& obj : objects) obj.move_obj(t_min);

	for (int i = 0; i < objects.size(); i++) {
		for (int j = 0; j < 4; j++) {
			auto& n = border_ns[j];
			if (t_collide_border[i][j] == t_min) objects[i].vel -= 2 * dot(objects[i].vel, n) * n;
		}

		for (int j = i + 1; j < objects.size(); j++) {
			if(t_collide_ball[i][j] == t_min) {
				auto& obj_1 = objects[i], & obj_2 = objects[j];
				sf::Vector2f x = obj_2.pos - obj_1.pos, n = x / norm(x);
				float mass_ratio = obj_2.mass / obj_1.mass, u = dot(obj_1.vel, n), v = dot(obj_2.vel, n),
					  c = 2 * (u - v) / (mass_ratio + 1);

				obj_1.vel -= mass_ratio * c * n;
				obj_2.vel += c * n;
			}
		}
	}

	if (dt - t_min > 0) { 
		calc_vel(dt - t_min); 
	}
}


void System::step(sf::Int32 dt) {
	
	float ms_dt = dt / 100.;

	calc_vel(ms_dt);
}

void System::draw_sys(sf::RenderWindow& window) {
	for (auto& obj : objects) {
		window.draw(obj.shape);
	}
}
