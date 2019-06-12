#pragma once
#include <string>
#include <iostream>
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/System.hpp"
#include <thread>
#include "Bullet.h"

//using namespace std;
using namespace sf;

void BulletView(RenderWindow &window, VertexArray hitlines) {

	//t1.join();

	while (window.isOpen()) {

		window.draw(hitlines);

	}
}