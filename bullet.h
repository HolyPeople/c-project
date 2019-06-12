#pragma once
#include <string>
#include <iostream>
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/System.hpp"
#include <cassert>
#include <math.h>
#include <vector>
#include "Player.h"
#include "TileMap.h"

using namespace sf;

class Bullet {
private:

	TileMap *T;
	VertexArray hitLines; //궤적
	int setDelay[3] = { 3,5,1 }; //발사간격. 3, 5, 1초마다 발사
	int delay = 0; //발사하고 흐른 시간


public:
	Bullet() {
		this->setDelay[0] = 3;
		this->setDelay[1] = 5;
		this->setDelay[2] = 1;
		this->delay = 0;
		T = new TileMap();
	}

	Bullet(int weapontype) {
		//Weapon weapon(weapontype);
		this->setDelay[0] = 3;
		this->setDelay[1] = 5;
		this->setDelay[2] = 1;
		this->delay = 0;
		T = new TileMap();
	}

	//가까운 히트위치 찾기
	sf::Vector2f getDistToClosestHitPoint(float angle, sf::Vector2i rayMapPos, sf::Vector2f rayWorldPos)
	{
		sf::Vector2u tileSize(32, 32);/////////////////////////////////
		sf::Vector2f rayDir = { cos(angle), sin(angle) };
		float dyh = 0; //dist y to next horizontal tile
		float dxh = 0; //dist x to next horizontal tile
		if (rayWorldPos.y == rayMapPos.y * tileSize.y)
		{
			dyh = tileSize.y;
		}
		else
		{
			if (rayDir.y < 0) dyh = rayWorldPos.y - (rayMapPos.y * tileSize.y);
			else           dyh = (rayMapPos.y + 1) * tileSize.y - rayWorldPos.y;
		}
		dxh = dyh / tan(angle);
		if (rayDir.y < 0) //invert distances values when pointing upwards
		{
			dxh = -dxh;
			dyh = -dyh;
		}
		float dyv = 0; //dist y to next vertical tile
		float dxv = 0; //dist x to next vertical tile
		if (rayWorldPos.x == rayMapPos.x * tileSize.x)
		{
			dxv = tileSize.x;
		}
		else
		{
			if (rayDir.x < 0) dxv = rayWorldPos.x - (rayMapPos.x * tileSize.x);
			else           dxv = (rayMapPos.x + 1) * tileSize.x - rayWorldPos.x;
		}
		dyv = dxv * tan(angle);
		if (rayDir.x < 0) //invert distances values when pointing upwards
		{
			dxv = -dxv;
			dyv = -dyv;
		}

		//calc squares and compare them
		float sqrLenHor = dxh * dxh + dyh * dyh;
		float sqrLenVer = dxv * dxv + dyv * dyv;

		//select distances which squares are lower
		float dx = sqrLenHor < sqrLenVer ? dxh : dxv;
		float dy = sqrLenHor < sqrLenVer ? dyh : dyv;

		return { dx, dy };
	}

	bool setActive(bool visualization, RenderWindow & gameWindow, Player &P) {

		sf::Vector2u tileSize(32, 32);/////////////////////////////////

		if (visualization == true)
		{
			//draw line going from player position to next hit positions
			VertexArray hitLines(LinesStrip);
			hitLines.append({ P.getLoc(), Color::Red });

			//get mouse pos
			auto mousePos = Mouse::getPosition(gameWindow);

			//get player rotation angle and direction vector
			float angle = atan2(mousePos.y - P.getLoc().y, mousePos.x - P.getLoc().x);
			sf::Vector2f dir = { cos(angle), sin(angle) };

			//get distance to first hit point
			sf::Vector2f dist = getDistToClosestHitPoint(angle, (Vector2i)P.getLoc(), P.getLoc());

			//first ray hit position coordinates
			sf::Vector2f rayWorldPos = { P.getLoc().x + dist.x, P.getLoc().y + dist.y };
			sf::Vector2i rayPosMap = { int(rayWorldPos.x / tileSize.x), int(rayWorldPos.y / tileSize.y) }; //just divide world coordinates by tile size

			bool hit = false;

			//raycast loop
			while (!hit)
			{
				//drawing ray hit lines
				hitLines.append({ { rayWorldPos.x, rayWorldPos.y }, sf::Color::Red });

				//drawing hit point circles
				CircleShape hitPoint(5);
				hitPoint.setOrigin({ 5, 5 });
				hitPoint.setPosition({ rayWorldPos.x, rayWorldPos.y });
				hitPoint.setFillColor(sf::Color::Red);
				//   gameWindow.draw(hitPoint);

				   //out of array range exceptions handling
				if (rayPosMap.x < 0 || rayPosMap.x >= gameWindow.getSize().x || rayPosMap.y < 0 || rayPosMap.y >= gameWindow.getSize().y) break;

				//checking that actually hit side is wall side
				int hitTileX = rayPosMap.x;
				int hitTileY = rayPosMap.y;

				//fix checking walls when hit them on their right or bottom side, check walls earlier them
				if (rayWorldPos.x == rayPosMap.x * tileSize.x && dir.x < 0) //hit wall left side
				{
					hitTileX--;
				}

				if (rayWorldPos.y == rayPosMap.y * tileSize.y && dir.y < 0) //hit wall up side
				{
					hitTileY--;
				}

				if (T->getElement(hitTileX, hitTileY) == 1)
				{
					hit = true; //end raycasting loop
				}
				else
				{
					//move ray to next closest horizontal or vertical side
					sf::Vector2f dist = getDistToClosestHitPoint(angle, { rayPosMap.x, rayPosMap.y }, { rayWorldPos.x, rayWorldPos.y });

					//draw triangle for better visualization of distance
					sf::VertexArray triangleVisual(LinesStrip);
					triangleVisual.append({ { rayWorldPos.x, rayWorldPos.y }, Color::Magenta });
					triangleVisual.append({ { rayWorldPos.x + dist.x, rayWorldPos.y }, Color::Magenta });
					triangleVisual.append({ { rayWorldPos.x + dist.x, rayWorldPos.y + dist.y }, Color::Magenta });
					//   gameWindow.draw(triangleVisual);

					   //apply new move 
					rayWorldPos.x += dist.x;
					rayWorldPos.y += dist.y;

					//update map positions
					rayPosMap.x = rayWorldPos.x / tileSize.x;
					rayPosMap.y = rayWorldPos.y / tileSize.y;
				}
			}

			this->setHitLines(hitLines);
			gameWindow.draw(this->getHitLines());
			sleep(milliseconds(setDelay[1]));
		}
		else {
			sleep(milliseconds(setDelay[1]));
		}

		return visualization;
	}

	// Update
	void FixedUpdate(RenderWindow& gameWindow, Player &P) {
		if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
			if (delay <= 0) //딜레이가 걸려있지 않을 때만 발사
			{
				delay = setDelay[1];
				setActive(true, gameWindow, P);
				sleep(milliseconds(setDelay[1]));
				setActive(false, gameWindow, P);
				delay -= setDelay[1];

			}
		}

	}

	void setHitLines(VertexArray hitLines) {
		this->hitLines = hitLines;
	}

	VertexArray getHitLines() {
		return hitLines;
	}

	//총알 소멸
	~Bullet() {

	}


};