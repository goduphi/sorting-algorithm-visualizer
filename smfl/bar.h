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
	Bar(int height, int width)
		: _height{ height }, _width{ width }
	{
		this->_bar = new sf::RectangleShape(sf::Vector2f(this->_height, this->_width));
	}
	~Bar()
	{
		delete this->_bar;
	}
private:
	sf::RectangleShape* _bar;
	int _height;
	int _width;
};

#endif