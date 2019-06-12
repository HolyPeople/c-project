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
	sf::RenderWindow window(sf::VideoMode(640, 640), "Character View Test"); //â ������ ����
	window.setFramerateLimit(60); //������ ����

	// create the tilemap from the level definition
	TileMapView map;
	TileMap mapData(1);
	if (!map.loadView("tileset.png", sf::Vector2u(32, 32), mapData.getNumArray()))
		return -1;

	Player *P = new Player();
	
	///////////////////////////////////////////////////////////////////////�Ѿ� ǥ�ø� �ذ��ϸ� ��////////////////////////////////////////////////////////////////////////////////
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

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1)) {//1�� ����� ��ü
			P->setWeapon(0);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2)) {//2�� ����� ��ü
			P->setWeapon(1);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3)) {//3�� ����� ��ü
			P->setWeapon(2);
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {//������
			P->reload();
		}

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {//�߻�
			if (P->getMag(1) != 0) {
				P->Fire();
			}
		}

		UI(window, *P); // = Draw
		//BulletView(window, B1->getHitLines());

		window.display();
	}

	//��Ʈ�ѷ��� �÷��̾��� ��ġ�� �ٲپ��� �ʿ䰡 ����-main�� ��Ʈ�ѷ� ����

	return 0;
}