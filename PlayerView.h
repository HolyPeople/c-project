#pragma once
#include <string>
#include <iostream>
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/System.hpp"
#include "Player.h"

using namespace std;

void drawPlayer(sf::RenderWindow &target, Player &P) {

	float sr = 200.f;

	sf::CircleShape Site(100);
	Site.setFillColor(sf::Color::White);
	Site.setPosition(sf::Vector2f(P.getLoc().x - sr / 2, P.getLoc().y - sr / 2));

	float cx = 32.f;
	float cy = 32.f;

	sf::RectangleShape character(sf::Vector2f(cx, cy)); // ĳ���� ������
	character.setFillColor(sf::Color::Blue); //ĳ���� ����
	character.setPosition(sf::Vector2f(P.getLoc().x, P.getLoc().y)); //ĳ���� ��ġ-player ��ü���� �޾ƿ�
	//character.setPosition(sf::Vector2f(P.getLoc().x - cx / 2, P.getLoc().y - cy / 2)); //ĳ���� ��ġ-player ��ü���� �޾ƿ�

	//target.draw(Site);
	target.draw(character);
}