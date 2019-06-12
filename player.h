#pragma once
#include <string>
#include <iostream>
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/System.hpp"
#include "TileMap.h"

#define tileSizeX 32
#define tileSizeY 32
using namespace std;

class Player {
private:
	//ĳ���� ����
	sf::String Name;//ĳ���� �̸�-�ʱ⿡ �޾���� ��
	int MaxHP;
	int PlayerHP;
	int Fast;//�̵��ӵ�
	sf::Vector2f playerWorldPos = { 128.0f, 96.0f };
	sf::Vector2i playerMapPos = { (int)playerWorldPos.x / tileSizeX, (int)playerWorldPos.y / tileSizeY };
	
	//���� ����
	int weapontype;
	sf::String wName[3] = { "Revolver", "Sniper", "AK-47" };
	int damage[3] = { 5, 20, 7 };
	int Mag[3] = { 6, 5, 30 };//��ź
	int OriginMag[3] = { 6, 5, 30 };//�ִ� ź��

public:
	Player() {
		MaxHP = PlayerHP = 100;
		Fast = 4;

		weapontype = 0;
	}
	Player(int Charactor) {
		MaxHP = PlayerHP = 80 + Charactor * 20;
		Fast = 4 - Charactor;
		weapontype = Charactor;
	}

	//ĳ���� ���� �Լ���
	int ChangePlayerHP(int changeHP) {//changeHP�� ���� ȸ�� �������� ��� ���, �ѿ� �ǰݴ������� ���� ��
		if (PlayerHP + changeHP <= 100 && PlayerHP + changeHP >= 0) {//�Ϲ����� ���
			PlayerHP += changeHP;
		}

		else if (PlayerHP + changeHP > 100) {//�ִ�ü�� �̻����� ���Ϸ��� �Ұ���
			PlayerHP = 100;
		}

		else if (PlayerHP + changeHP < 0) {
			PlayerHP = 0;
			//���⼭ �ı��� ����
		}

		return PlayerHP;//���ϰ���0�̸� �ı��ڽ��� ��
	}
	int getHP(int i) {//ü�� ��ȯ, 0�̸� �ִ�ü�� 1�̸� ����ü��
		if (i == 0) {
			return MaxHP;
		}
		else {
			return PlayerHP;
		}
	}
	sf::Vector2f getLoc() {
		return playerWorldPos;
	}

	//���� ���� �Լ���
	int setWeapon(int n) {
		if (n >= sizeof(damage)) {
			weapontype = sizeof(damage);
		}
		else if (n <= 0) {
			weapontype = 0;
		}
		else {
			weapontype = n;
		}

		return weapontype;
	}
	int getWeapon() {
		return weapontype;
	}
	sf::String getWName() {
		return wName[weapontype];
	}
	int Fire() {

		if (Mag[weapontype] == 0) {
			reload();
		}
		else {
			Mag[weapontype]--;
		}

		return damage[weapontype];
	}
	int getMag(int i) {//źâ ��ȯ, 0�̸� �ִ� 1�̸� ����
		if (i == 0) {
			return OriginMag[weapontype];
		}
		else {
			return Mag[weapontype];
		}
	}
	void reload() {
		Mag[weapontype] = OriginMag[weapontype];
		//������ �Լ�, ������ �ϴ� ���� fire �Լ��� �۵����� �ʴ� ��Ŀ���� �߰� �ʿ�
	}

	//ĳ���� �ൿ ���� �Լ�
	void Move(TileMap TM) {//�÷��̾��� ��ǥ�� �����ϴ� �Լ�

		int a1 = TM.getElement(playerMapPos.x - 1, playerMapPos.y);
		int a2 = TM.getElement(playerMapPos.x - 1, playerMapPos.y + 1);

		int d1 = TM.getElement(playerMapPos.x + 1, playerMapPos.y);
		int d2 = TM.getElement(playerMapPos.x + 1, playerMapPos.y + 1);
			   		 	  
		int w1 = TM.getElement(playerMapPos.x, playerMapPos.y - 1);
		int w2 = TM.getElement(playerMapPos.x + 1, playerMapPos.y - 1);

		int s1 = TM.getElement(playerMapPos.x, playerMapPos.y + 1);
		int s2 = TM.getElement(playerMapPos.x + 1, playerMapPos.y + 1);

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
			if (playerWorldPos.y == playerMapPos.y * tileSizeY && TM.getElement(playerMapPos.x - 1, playerMapPos.y) == 0) {
				playerWorldPos.x -= 4.f / 8 * (4 + Fast);
			}
			else {
				if (a1 == 1 || a2 == 1) {
					if (playerWorldPos.x == playerMapPos.x * tileSizeX) {
						playerWorldPos.x = playerMapPos.x * tileSizeX;
					}
					else {
						playerWorldPos.x -= 4.f / 8 * (4 + Fast);
					}
				}
				else {
					playerWorldPos.x -= 4.f / 8 * (4 + Fast);
				}
			}
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
			if (playerWorldPos.y == playerMapPos.y * tileSizeY && TM.getElement(playerMapPos.x + 1, playerMapPos.y) == 0) {
				playerWorldPos.x = playerWorldPos.x + 4.f / 8 * (4 + Fast);
			}
			else {
				if (d1 == 1 || d2 == 1) {
					playerWorldPos.x = playerMapPos.x * tileSizeX;
				}
				else {
					playerWorldPos.x = playerWorldPos.x + 4.f / 8 * (4 + Fast);
				}
			}
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
			if (playerWorldPos.x == playerMapPos.x * tileSizeX && TM.getElement(playerMapPos.x, playerMapPos.y - 1) == 0) {
				playerWorldPos.y -= 4.f / 8 * (4 + Fast);
			}
			else {				
				if (w1 == 1 || w2 == 1) {
					if (playerWorldPos.y == playerMapPos.y * tileSizeY) {
						playerWorldPos.y = playerMapPos.y * tileSizeY;
					}
					else {
						playerWorldPos.y -= 4.f / 8 * (4 + Fast);
					}
				}
				else {
					playerWorldPos.y -= 4.f / 8 * (4 + Fast);
				}
			}
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
			if (playerWorldPos.x == playerMapPos.x * tileSizeX && TM.getElement(playerMapPos.x, playerMapPos.y + 1) == 0) {
				playerWorldPos.y += 4.f / 8 * (4 + Fast);
			}
			else {
				if (s1 == 1 || s2 == 1) {
					playerWorldPos.y = playerMapPos.y * tileSizeY;
				}
				else {
					playerWorldPos.y += 4.f / 8 * (4 + Fast);
				}
			}
		}

		if (playerWorldPos.x < 0) {
			playerWorldPos.x = 0;
		}
		if (playerWorldPos.y < 0) {
			playerWorldPos.y = 0;
		}
		if (playerWorldPos.x > 608) {
			playerWorldPos.x = 608;
		}
		if (playerWorldPos.y > 608) {
			playerWorldPos.y = 608;
		}

		playerMapPos = { (int)playerWorldPos.x / tileSizeX, (int)playerWorldPos.y / tileSizeY };
	}


	
	void Erase() {
		//�̹��� ���� ȭ�鿡�� ����°� �ֱ�
	}

	~Player() {//����ٰ��� ������ �÷��̾� �׾����� �����ϴ°ǵ�
		printf("Game Over!");

	}

	sf::Vector2f gP = (sf::Vector2f)sf::Mouse::getPosition(); //���콺 ��ǥ �޾ƿ���, ���� �ƹ� �ǹ� ����
};