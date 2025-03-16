#include "System.hpp"

int main() {

    int height = 800, width = 800;

	sf::ContextSettings settings;
	settings.antialiasingLevel = 6;
	sf::RenderWindow window(sf::VideoMode(width, height), "Simulation", sf::Style::Default, settings);

    System system(sf::Vector2i(width, height));
    Object obj_1 = Object::builder()
        .name("É")
        .vel(sf::Vector2f(13.f, 0.f))
        .acc(sf::Vector2f(0.f, 9.81f))
        .mass(100.f)
        .shape(sf::Color::Blue, 60.f, sf::Vector2f(200.f, 400.f)).build();
    system.add_obj(obj_1);

    Object obj_2 = Object::builder()
        .name("É")
        .vel(sf::Vector2f(10.f, 0.f))
        .acc(sf::Vector2f(0.f, 9.81f))
        .mass(10.f)
        .shape(sf::Color::Red, 30.f, sf::Vector2f(20.f, 200.f)).build();
    system.add_obj(obj_2);

    Object obj_3 = Object::builder()
        .name("É")
        .vel(sf::Vector2f(7.f, -10.f))
        .acc(sf::Vector2f(0.f, 9.81f))
        .mass(10.f)
        .shape(sf::Color::Green, 30.f, sf::Vector2f(100.f, 200.f)).build();
    system.add_obj(obj_3);

    Object obj_4 = Object::builder()
        .name("É")
        .vel(sf::Vector2f(-2.f, -2.f))
        .acc(sf::Vector2f(0.f, 9.81f))
        .mass(10.f)
        .shape(sf::Color::Yellow, 30.f, sf::Vector2f(200.f, 200.f)).build();
    system.add_obj(obj_4);

    Object obj_5 = Object::builder()
        .name("É")
        .vel(sf::Vector2f(-9.f, 5.f))
        .acc(sf::Vector2f(0.f, 9.81f))
        .mass(10.f)
        .shape(sf::Color::Magenta, 30.f, sf::Vector2f(300.f, 200.f)).build();
    system.add_obj(obj_5);

    Object obj_6 = Object::builder()
        .name("É")
        .vel(sf::Vector2f(20.f, 10.f))
        .acc(sf::Vector2f(0.f, 9.81f))
        .mass(10.f)
        .shape(sf::Color::Black, 30.f, sf::Vector2f(400.f, 200.f)).build();
    system.add_obj(obj_6);

    sf::Clock fps_clock;
    sf::Clock step_clock;

    const int fps = 30;
    const double interval = 1000. / fps;
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        sf::Int32 step_time = step_clock.getElapsedTime().asMilliseconds();

        if (step_time > 30) {
            system.step(step_time);
            step_clock.restart();
        }

        if (fps_clock.getElapsedTime().asMilliseconds() < interval) continue;
        fps_clock.restart();
        window.clear(sf::Color::White);

        system.draw_sys(window);
        window.display();
    }



	return 0;
}