#include <string>
#include <iostream>
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/System.hpp"
#include "PlayerView.h"
#include "UI.h"
#include "BulletView.h"
#include "TileMapView.h"

using namespace std;
//using namespace sf;

int main()
{
	sf::RenderWindow window(sf::VideoMode(640, 640), "Character View Test"); //창 사이즈 고정
	window.setFramerateLimit(60); //프레임 제한

	// create the tilemap from the level definition
	TileMapView map;
	TileMap mapData(1);
	if (!map.loadView("tileset.png", sf::Vector2u(32, 32), mapData.getNumArray()))
		return -1;

	Player *P = new Player();
	
	///////////////////////////////////////////////////////////////////////총알 표시만 해결하면 됨////////////////////////////////////////////////////////////////////////////////
	Bullet *B1 = new Bullet();
	//thread t1(Bullet setActive);
	
	//BulletView(window, B1->getHitLines());
	//BulletView(window, B1->getHitLines(), t1(B1->setActive(true, window, *P)));

	while (window.isOpen()) {
		//sf::Color::White
		window.clear();
		window.draw(map);

		P->Move(mapData);

		sf::Event eve;
		while (window.pollEvent(eve)) {

			if (eve.type == sf::Event::Closed)
				window.close();

			if (eve.type == sf::Event::KeyPressed && eve.key.code == sf::Keyboard::Escape)
				window.close();

		}
		
		//sf::Mouse::isButtonPressed(sf::Mouse::Left)
		//eve.type == sf::Event::MouseButtonReleased
		//sf::Keyboard::isKeyPressed(sf::Keyboard::Space)

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1)) {//1번 무기로 교체
			P->setWeapon(0);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2)) {//2번 무기로 교체
			P->setWeapon(1);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3)) {//3번 무기로 교체
			P->setWeapon(2);
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {//재장전
			P->reload();
		}

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {//발사
			if (P->getMag(1) != 0) {
				P->Fire();
			}
		}

		UI(window, *P); // = Draw
		//BulletView(window, B1->getHitLines());

		window.display();
	}

	//컨트롤러로 플레이어의 위치를 바꾸어줄 필요가 있음-main이 컨트롤러 역할

	return 0;
}