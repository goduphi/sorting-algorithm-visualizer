/*
	This header file will be used in the future.
	The implementations of the constructor and destructor have been included here temporarily.
*/

#include <SFML/Graphics.hpp>

#pragma once
#ifndef BAR_H
#define BAR_H

class Bar
{
public:
	Bar(int width, int height)
		: _width{ width }, _height{ height }
	{
		this->_bar = sf::RectangleShape(sf::Vector2f(this->_width, this->_height));
	}
private:
	sf::RectangleShape _bar;
	int _width;
	int _height;
};

#endif