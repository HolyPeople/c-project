#pragma once
#include <fstream>
#include <string>
#include <iostream>
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/System.hpp"
//#include "Element.h"
//#include "Empty.h"
//#include "Obstacle.h"
//#include "Trap.h"
//#include "Item.h"

#define mapWidth 20
#define mapHeight 20

using namespace std;

class TileMap {
private:
	int arrMap[mapWidth][mapHeight]; //맵의 정보(숫자)를 담고있는 배열
	//Element* mapData[mapWidth][mapHeight]; //숫자에 맞게 객체 생성해줌. 0 -> 빈 타일(Empty), 1 -> 장애물(Obstacle), 2 -> 함정(Trap), 3-> 아이템(Item)

	//파일 열고 txt파일 로드, txt파일에 있는 숫자 정보 그대로 arrMap을 초기화시킴
	void fileLoad(const string& fileLocation) {
		int tileNumber;
		string fileName = fileLocation;
		ifstream ifs;

		ifs.open(fileLocation.c_str());

		if (!ifs) {
			std::cout << "맵 파일을 열 수 없습니다." << std::endl;
			exit(0);
		}
		int indexI = 0;
		int indexJ = 0;

		while (ifs >> tileNumber) {
			if (indexJ == mapHeight) {
				indexJ = 0;
				indexI++;
			}

			this->arrMap[indexI][indexJ] = tileNumber; //txt파일에서 숫자 읽고 arrMap에 숫자들 다 전달
		/*
			switch (this->arrMap[indexI][indexJ]) { //숫자들이 0? 1? 2? 3? 인지에 따라 mapData배열에 Empty 객체/Obstacle 객체...등등 생성해줌
			case 0:
				this->mapData[indexI][indexJ] = new Empty;
				break;
			case 1:
				this->mapData[indexI][indexJ] = new Obstacle;
				break;
			case 2:
				this->mapData[indexI][indexJ] = new Trap;
				break;
			case 3:
				this->mapData[indexI][indexJ] = new Item;
				break;
			}
			*/

			indexJ++;
		}
		ifs.close();
	}



public:
	TileMap(int mapNum = 1) { //생성할 때 
		//string fileLocation = "Levels\\" + to_string(mapNum) + ".txt"; //Levels라는 폴더에 있는 txt파일 로드. 
		fileLoad("1.txt");
	}

	void printAll() { //맵 원소 콘솔 출력. 그냥 디버그용. 
		for (int i = 0; i < mapWidth; ++i) {
			for (int j = 0; j < mapHeight; ++j) {
				cout << this->arrMap[i][j] << " ";
			}
			cout << '\n' << endl;
		}
	}

	int(*getNumArray())[mapWidth] { //맵의 정보를 리턴하는 함수. 사용할 때는 int arr[너비][높이] = getArray();
		return this->arrMap;
	}

	int getElement(int x, int y) {
		return this->arrMap[x][y];
	}

	bool updateNumTile(sf::Vector2u mapPos, int num) {
		if (0 <= num || num <= 3) {
			this->arrMap[mapPos.x][mapPos.y] = num;
			return true;
		}
		return false;
	}

	/*  Element*(*getElementArray())[mapWidth] { // Element* 배열 리턴.
			return this->mapData;
		}*/
};