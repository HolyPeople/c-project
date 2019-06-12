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

void drawHP(sf::RenderWindow &target, Player &P) {//체력 전체를 표시

	sf::RectangleShape MaxHP(sf::Vector2f(P.getHP(0) * 2, 50.f)); // 최대 체력바
	MaxHP.setFillColor(sf::Color::White); //흰색
	MaxHP.setPosition(0, target.getSize().y - 50); //좌하귀에 위치

	sf::RectangleShape NowHP(sf::Vector2f(P.getHP(1) * 2, 50.f)); // 현재 체력바
	NowHP.setFillColor(sf::Color::Green); //녹색
	NowHP.setPosition(0, target.getSize().y - 50); //좌하귀에 위치

	NowHP.setSize(sf::Vector2f(P.getHP(1) * 2, 50.f));

	target.draw(MaxHP);
	target.draw(NowHP);
}