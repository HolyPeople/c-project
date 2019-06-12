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
	int arrMap[mapWidth][mapHeight]; //���� ����(����)�� ����ִ� �迭
	//Element* mapData[mapWidth][mapHeight]; //���ڿ� �°� ��ü ��������. 0 -> �� Ÿ��(Empty), 1 -> ��ֹ�(Obstacle), 2 -> ����(Trap), 3-> ������(Item)

	//���� ���� txt���� �ε�, txt���Ͽ� �ִ� ���� ���� �״�� arrMap�� �ʱ�ȭ��Ŵ
	void fileLoad(const string& fileLocation) {
		int tileNumber;
		string fileName = fileLocation;
		ifstream ifs;

		ifs.open(fileLocation.c_str());

		if (!ifs) {
			std::cout << "�� ������ �� �� �����ϴ�." << std::endl;
			exit(0);
		}
		int indexI = 0;
		int indexJ = 0;

		while (ifs >> tileNumber) {
			if (indexJ == mapHeight) {
				indexJ = 0;
				indexI++;
			}

			this->arrMap[indexI][indexJ] = tileNumber; //txt���Ͽ��� ���� �а� arrMap�� ���ڵ� �� ����
		/*
			switch (this->arrMap[indexI][indexJ]) { //���ڵ��� 0? 1? 2? 3? ������ ���� mapData�迭�� Empty ��ü/Obstacle ��ü...��� ��������
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
	TileMap(int mapNum = 1) { //������ �� 
		//string fileLocation = "Levels\\" + to_string(mapNum) + ".txt"; //Levels��� ������ �ִ� txt���� �ε�. 
		fileLoad("1.txt");
	}

	void printAll() { //�� ���� �ܼ� ���. �׳� ����׿�. 
		for (int i = 0; i < mapWidth; ++i) {
			for (int j = 0; j < mapHeight; ++j) {
				cout << this->arrMap[i][j] << " ";
			}
			cout << '\n' << endl;
		}
	}

	int(*getNumArray())[mapWidth] { //���� ������ �����ϴ� �Լ�. ����� ���� int arr[�ʺ�][����] = getArray();
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

	/*  Element*(*getElementArray())[mapWidth] { // Element* �迭 ����.
			return this->mapData;
		}*/
};