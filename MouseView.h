#pragma once
#include <string>
#include <iostream>
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/System.hpp"

using namespace std;

void drawMousePoint(sf::RenderWindow &target) {
	float sr = 5.f;

	sf::CircleShape MP(sr);
	MP.setFillColor(sf::Color::Magenta); //마우스 색상
	MP.setPosition((sf::Vector2f)sf::Mouse::getPosition(target)); //마우스 위치
	MP.move(- sr, - sr);//조정

	//sf::Vector2f gP = (sf::Vector2f)sf::Mouse::getPosition();

	target.draw(MP);
}