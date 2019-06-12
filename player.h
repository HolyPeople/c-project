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
	//캐릭터 정보
	sf::String Name;//캐릭터 이름-초기에 받아줘야 함
	int MaxHP;
	int PlayerHP;
	int Fast;//이동속도
	sf::Vector2f playerWorldPos = { 128.0f, 96.0f };
	sf::Vector2i playerMapPos = { (int)playerWorldPos.x / tileSizeX, (int)playerWorldPos.y / tileSizeY };
	
	//무기 정보
	int weapontype;
	sf::String wName[3] = { "Revolver", "Sniper", "AK-47" };
	int damage[3] = { 5, 20, 7 };
	int Mag[3] = { 6, 5, 30 };//잔탄
	int OriginMag[3] = { 6, 5, 30 };//최대 탄수

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

	//캐릭터 관련 함수들
	int ChangePlayerHP(int changeHP) {//changeHP의 값은 회복 아이템일 경우 양수, 총에 피격당했을시 음수 값
		if (PlayerHP + changeHP <= 100 && PlayerHP + changeHP >= 0) {//일반적인 경우
			PlayerHP += changeHP;
		}

		else if (PlayerHP + changeHP > 100) {//최대체력 이상으로 힐하려면 불가능
			PlayerHP = 100;
		}

		else if (PlayerHP + changeHP < 0) {
			PlayerHP = 0;
			//여기서 파괴자 실행
		}

		return PlayerHP;//리턴값이0이면 파괴자실행 ㄱ
	}
	int getHP(int i) {//체력 반환, 0이면 최대체력 1이면 현재체력
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

	//무기 관련 함수들
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
	int getMag(int i) {//탄창 반환, 0이면 최대 1이면 현재
		if (i == 0) {
			return OriginMag[weapontype];
		}
		else {
			return Mag[weapontype];
		}
	}
	void reload() {
		Mag[weapontype] = OriginMag[weapontype];
		//재장전 함수, 재장전 하는 동안 fire 함수가 작동하지 않는 매커니즘 추가 필요
	}

	//캐릭터 행동 제어 함수
	void Move(TileMap TM) {//플레이어의 좌표를 조정하는 함수

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
		//이미지 파일 화면에서 지우는거 넣기
	}

	~Player() {//여기다가는 뭐넣지 플레이어 죽었을때 실행하는건데
		printf("Game Over!");

	}

	sf::Vector2f gP = (sf::Vector2f)sf::Mouse::getPosition(); //마우스 좌표 받아오기, 현재 아무 의미 없음
};