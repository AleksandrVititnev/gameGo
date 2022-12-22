#include "engine.h"
engine::engine(sf::String _file, sf::String _fileFont) {
	window.create(sf::VideoMode(576, 576), "Base GO game By AleksandrVititnev", sf::Style::Titlebar | sf::Style::Close);
	window.setFramerateLimit(15);

	map_image.loadFromFile("images\\" + _file);
	map.loadFromImage(map_image);
	s_map.setTexture(map);

	font.loadFromFile("fonts\\" + _fileFont);
	textWin.setFont(font);
	textWin.setCharacterSize(200);
	textWin.setFillColor(sf::Color::Magenta);
	textWin.setStyle(sf::Text::Bold | sf::Text::Underlined);

	srand(time(NULL));

	field = new gameField(9, 9);
	rule = new gameLogic();
	AI = new compLogic(rule);
	turn = new id_node(0, 0);
	aiTurn = new id_node(0,0);

	showTerr = false;
	aiOn = false;
	secret = true;

	passFirst = false;
	passSecond = false;
	end = false;
}

void engine::comp_turn(bool& _wasTurn) {
	try {
		if (_wasTurn) {
			_wasTurn = false;
			if (!secret) {
				aiTurn = AI->get_next_turn(field);
				if (aiTurn) {
					if (aiTurn->place_hei < 0) passFirst = true;
					else {
						field->make_turn(aiTurn, 'w');
						rule->apply_turn(field, aiTurn);
						passSecond = false;
					}
				}
			}
			else {
				aiTurn->place_hei = rand() % 8;
				aiTurn->place_wid = rand() % 8;
				if (rule->can_make_turn(field, aiTurn, 'w')) {
					field->make_turn(aiTurn, 'w');
					rule->apply_turn(field, aiTurn);
					passSecond = false;
				}
				else passFirst = true;
			}
		}
	}
	catch (std::logic_error e) {
		std::cout << e.what() << '\n';
	}

	return;
}

void engine::start() {
	bool wasTurn = false;
	while (window.isOpen()) {
		
		sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
		sf::Vector2f pos = window.mapPixelToCoords(pixelPos);

		if (passFirst && passSecond) {
			end = true;
			if (get_mark_field2(field) >= 0) textWin.setString("LOSE");
			else textWin.setString("WIN");
		}
		if (aiOn && !end) comp_turn(wasTurn);

		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) || sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
				window.close();
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::F1)) {
				showTerr = !showTerr;
				std::cout << "showTerr: " << showTerr << '\n';
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::F2)) {
				aiOn = !aiOn;
				std::cout << "aiOn: " << aiOn << '\n';
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
				field->restore_default_all();
				passFirst = false;
				passSecond = false;
				end = false;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::F7)) {
				secret = !secret;
				std::cout << "secret: " << secret << '\n';
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::P)) {
				passSecond = true;
				wasTurn = true;
			}

			if (event.type == sf::Event::MouseButtonPressed && !end) {
				try {
					if (event.key.code == sf::Mouse::Left) {
						std::cout << "IsClicked!\n";
						turn->place_wid = pos.x / 64;
						turn->place_hei = pos.y / 64;
						if (rule->can_make_turn(field, turn, 'b')) {
							field->make_turn(turn, 'b');
							rule->apply_turn(field, turn);
							wasTurn = true;
							passFirst = false;
							passSecond = false;
						}
					}
					if (event.key.code == sf::Mouse::Right) {
						std::cout << "IsClicked!\n";
						turn->place_wid = pos.x / 64;
						turn->place_hei = pos.y / 64;
						if (rule->can_make_turn(field, turn, 'w')) {
							field->make_turn(turn, 'w');
							std::cout << "engine ";
							rule->apply_turn(field, turn);
							//wasTurn = true;
							passFirst = false;
							passSecond = false;
						}
					}
				}
				catch (std::logic_error e) {
					std::cout << e.what() << '\n';
				}
				std::cout << get_mark_field2(field) << '\n';
			}
		}

		window.clear();
		if (!showTerr) {
			for (int i{}; i < field->get_height(); ++i) {
				for (int j{}; j < field->get_width(); ++j) {
					turn->place_hei = i;
					turn->place_wid = j;
					if (field->who_is(turn) == 'n') s_map.setTextureRect(sf::IntRect(0, 0, 64, 64));
					if (field->who_is(turn) == 'w') s_map.setTextureRect(sf::IntRect(448, 0, 512, 64));
					if (field->who_is(turn) == 'b') s_map.setTextureRect(sf::IntRect(512, 0, 576, 64));

					s_map.setPosition(j * 64, i * 64);

					window.draw(s_map);
				}
			}
		}
		else {
			for (int i{}; i < field->get_height(); ++i) {
				for (int j{}; j < field->get_width(); ++j) {
					turn->place_hei = i;
					turn->place_wid = j;
					if (field->who_is(turn) == 'n') {
						if (field->own_by(i, j) == 'n') s_map.setTextureRect(sf::IntRect(0, 0, 64, 64));
						if (field->own_by(i, j) == 'w') s_map.setTextureRect(sf::IntRect(64, 0, 128, 64));
						if (field->own_by(i, j) == 'b') s_map.setTextureRect(sf::IntRect(128, 0, 192, 64));
					}
					if (field->who_is(turn) == 'w') {
						if (field->own_by(i, j) == 'w') s_map.setTextureRect(sf::IntRect(192, 0, 256, 64));
						if (field->own_by(i, j) == 'b') s_map.setTextureRect(sf::IntRect(256, 0, 320, 64));
					}
					if (field->who_is(turn) == 'b') {
						if (field->own_by(i, j) == 'w') s_map.setTextureRect(sf::IntRect(320, 0, 384, 64));
						if (field->own_by(i, j) == 'b') s_map.setTextureRect(sf::IntRect(384, 0, 448, 64));
					}

					s_map.setPosition(j * 64, i * 64);

					window.draw(s_map);
				}
			}
		}
		if (end) {
			textWin.setPosition(0, 144);
			window.draw(textWin);
		}
		window.display();
	}
}