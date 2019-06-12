#pragma once
//#include "TILETYPE.h"
//#include "Element.h"
#include <SFML\Graphics.hpp>
#include <SFML\Window.hpp>
#include <SFML\Config.hpp>
#include <SFML\System\Export.hpp>

#define mapWidth 20 //�� ũ��� �����̿�
#define mapHeight 20

/*
�� Ŭ������ Ÿ�Ϸ� �� ���� �並 ����ϴ� Ŭ����.
TileMapŬ������ getNumArray()�� �迭�� ������,
�迭�� ������ 0, 1, 2, 3������ �Ǵ��ϰ�
�׿� �´� �並 ȭ�鿡 �׷��ش�.
*/

class TileMapView : public sf::Drawable, public sf::Transformable {
private:
	sf::VertexArray m_vertices; //������ ����
	sf::Texture m_tileset; //tileset.png �ʿ�

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const {
		//apply the transform
		states.transform *= getTransform();

		//apply the tileset texture 
		states.texture = &m_tileset;

		//draw the vertex array
		target.draw(m_vertices, states);
	}

public:
	bool loadView(const std::string& tileset, sf::Vector2u tileSize, int(*tiles)[mapHeight]) {
		// load the tileset texture
		if (!m_tileset.loadFromFile(tileset))
			return false;

		// resize the vertex array to fit the level size
		m_vertices.setPrimitiveType(sf::Quads);
		m_vertices.resize(mapWidth * mapHeight * 4);

		// populate the vertex array, with one quad per tile
		for (unsigned int i = 0; i < mapWidth; ++i)
			for (unsigned int j = 0; j < mapHeight; ++j)
			{
				// get the current tile number
				int tileNumber = tiles[i][j];

				// find its position in the tileset texture
				int tu = tileNumber % (m_tileset.getSize().x / tileSize.x);
				int tv = tileNumber / (m_tileset.getSize().x / tileSize.x);

				// get a pointer to the current tile's quad
				sf::Vertex* quad = &m_vertices[(i + j * mapWidth) * 4];

				// define its 4 corners
				quad[0].position = sf::Vector2f(i * tileSize.x, j * tileSize.y);
				quad[1].position = sf::Vector2f((i + 1) * tileSize.x, j * tileSize.y);
				quad[2].position = sf::Vector2f((i + 1) * tileSize.x, (j + 1) * tileSize.y);
				quad[3].position = sf::Vector2f(i * tileSize.x, (j + 1) * tileSize.y);

				// define its 4 texture coordinates
				quad[0].texCoords = sf::Vector2f(tu * tileSize.x, tv * tileSize.y);
				quad[1].texCoords = sf::Vector2f((tu + 1) * tileSize.x, tv * tileSize.y);
				quad[2].texCoords = sf::Vector2f((tu + 1) * tileSize.x, (tv + 1) * tileSize.y);
				quad[3].texCoords = sf::Vector2f(tu * tileSize.x, (tv + 1) * tileSize.y);
			}
		return true;
	}

	bool updateView(sf::Vector2u tilePos, sf::Vector2u tileSize, int(*tiles)[mapHeight]) {
		// get the current tile number
		int tileNumber = tiles[tilePos.x][tilePos.y];

		// find its position in the tileset texture
		int tu = tileNumber % (m_tileset.getSize().x / tileSize.x);
		int tv = tileNumber / (m_tileset.getSize().x / tileSize.x);

		// get a pointer to the current tile's quad
		sf::Vertex* quad = &m_vertices[(tilePos.x + tilePos.y * mapWidth) * 4];

		// define its 4 corners
		quad[0].position = sf::Vector2f(tilePos.x * tileSize.x, tilePos.y * tileSize.y);
		quad[1].position = sf::Vector2f((tilePos.x + 1) * tileSize.x, tilePos.y * tileSize.y);
		quad[2].position = sf::Vector2f((tilePos.x + 1) * tileSize.x, (tilePos.y + 1) * tileSize.y);
		quad[3].position = sf::Vector2f(tilePos.x * tileSize.x, (tilePos.y + 1) * tileSize.y);

		// define its 4 texture coordinates
		quad[0].texCoords = sf::Vector2f(tu * tileSize.x, tv * tileSize.y);
		quad[1].texCoords = sf::Vector2f((tu + 1) * tileSize.x, tv * tileSize.y);
		quad[2].texCoords = sf::Vector2f((tu + 1) * tileSize.x, (tv + 1) * tileSize.y);
		quad[3].texCoords = sf::Vector2f(tu * tileSize.x, (tv + 1) * tileSize.y);
		return true;
	}
};