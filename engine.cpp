#include "engine.h"
engine::engine(sf::String _file) {
	window.create(sf::VideoMode(576, 576), "Base GO game By AleksandrVititnev", sf::Style::Titlebar | sf::Style::Close);

	map_image.loadFromFile("images\\" + _file);
	map.loadFromImage(map_image);
	s_map.setTexture(map);

	field = new gameField(9, 9);
	rule = new gameLogic();
	AI = new compLogic(rule);
	turn = new id_node(0, 0);
}

void engine::start() {
	bool wasTurn = false;
	while (window.isOpen()) {
		
		sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
		sf::Vector2f pos = window.mapPixelToCoords(pixelPos);

		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
				window.close();

			if (event.type == sf::Event::MouseButtonPressed) {
				try {
					if (event.key.code == sf::Mouse::Left) {
						std::cout << "IsClicked!\n";
						turn->place_wid = pos.x / 64;
						turn->place_hei = pos.y / 64;
						if (rule->can_make_turn(field, turn, 'b')) {
							field->make_turn(turn, 'b');
							wasTurn = true;
						}
						if (wasTurn) {
							turn = AI->get_next_turn(field);
							field->make_turn(turn, 'w');
							wasTurn = false;
						}
					}
					if (event.key.code == sf::Mouse::Right) {
						std::cout << "IsClicked!\n";
						turn->place_wid = pos.x / 64;
						turn->place_hei = pos.y / 64;
						if (rule->can_make_turn(field, turn, 'w')) {
							field->make_turn(turn, 'w');
						}
					}
				}
				catch (std::logic_error e) {
					std::cout << e.what() << '\n';
				}
			}
		}

		window.clear();

		for (int i{}; i < field->get_height(); ++i) {
			for (int j{}; j < field->get_width(); ++j) {
				turn->place_hei = i;
				turn->place_wid = j;
				if (field->who_is(turn) == 'n') s_map.setTextureRect(sf::IntRect(0, 0, 64, 64));
				if (field->who_is(turn) == 'w') s_map.setTextureRect(sf::IntRect(64, 0, 128, 64));
				if (field->who_is(turn) == 'b') s_map.setTextureRect(sf::IntRect(128, 0, 192, 64));

				s_map.setPosition(j * 64, i * 64);

				window.draw(s_map);
			}
		}
		window.display();
	}
}