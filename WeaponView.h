#pragma once
#include <string>
#include <iostream>
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/System.hpp"
#include "Player.h"

using namespace std;

void drawWeapon(sf::RenderWindow &target, Player &P) {
	sf::Font font;
	if (!font.loadFromFile("res/fonts/FontFile.ttf"))
	{
		std::cout << "Error loading file" << std::endl;

		system("pause");
	}

	sf::Text Name;
	sf::Text Mag;

	sf::String n;
	n = " ";
	n += P.getWName();
	
	sf::String m;
	m = " ";
	m += to_string(P.getMag(1));
	m += "  /  ";
	m += to_string(P.getMag(0));

	Name.setFont(font);
	Name.setString(n);
	Name.setPosition(target.getSize().x - 150, target.getSize().y - 120);
	Name.setCharacterSize(50);

	Mag.setFont(font);
	Mag.setString(m);
	Mag.setPosition(target.getSize().x - 150, target.getSize().y - 70);
	Mag.setCharacterSize(50);
	//text.setColor(sf::Color::White);
	//text.setFillColor(sf::Color::White);
	//text.setOutlineColor(sf::Color::White);

	target.draw(Name);
	target.draw(Mag);
}