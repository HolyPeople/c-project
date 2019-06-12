#pragma once
#include <string>
#include <iostream>
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/System.hpp"
#include "PlayerView.h"
#include "WeaponView.h"
#include "MouseView.h"

using namespace std;

void drawHP(sf::RenderWindow &target, Player &P);

void UI(sf::RenderWindow &window, Player &P) {
	drawHP(window, P);
	drawPlayer(window, P);
	drawWeapon(window, P);
	drawMousePoint(window);
}

void drawHP(sf::RenderWindow &target, Player &P) {//ü�� ��ü�� ǥ��

	sf::RectangleShape MaxHP(sf::Vector2f(P.getHP(0) * 2, 50.f)); // �ִ� ü�¹�
	MaxHP.setFillColor(sf::Color::White); //���
	MaxHP.setPosition(0, target.getSize().y - 50); //���ϱͿ� ��ġ

	sf::RectangleShape NowHP(sf::Vector2f(P.getHP(1) * 2, 50.f)); // ���� ü�¹�
	NowHP.setFillColor(sf::Color::Green); //���
	NowHP.setPosition(0, target.getSize().y - 50); //���ϱͿ� ��ġ

	NowHP.setSize(sf::Vector2f(P.getHP(1) * 2, 50.f));

	target.draw(MaxHP);
	target.draw(NowHP);
}