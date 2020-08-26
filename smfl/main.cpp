#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <chrono>
#include <random>

std::vector<sf::RectangleShape> InitializeVector(std::vector<int> nums, unsigned int barWidth)
{
	std::vector<sf::RectangleShape> res;
	for (int i = 0; i < nums.size(); i++)
	{
		sf::RectangleShape rect(sf::RectangleShape(sf::Vector2f(barWidth, nums[i] * 10)));
		rect.setFillColor(sf::Color(100, 250, 250));
		rect.setPosition(i * (barWidth + 1), 0);
		res.emplace_back(rect);
	}
	return res;
}

template <typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& v)
{
	for (int i = 0; i < v.size(); i++)
		os << v[i] << " ";
	return os;
}

int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "Sorting algorithm Visualizer", sf::Style::Titlebar | sf::Style::Close);
	window.setFramerateLimit(120);

	// Obtain a seed from the system clock
	unsigned int seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::minstd_rand0 randomNumber(seed);

	int winWidth = window.getSize().x;
	int winHeight = window.getSize().y;
	int barWidth = 10;
	int numberOfElements = winWidth / (barWidth + 1);

	std::vector<int> nums(numberOfElements);
	for (int i = 0; i < numberOfElements; i++)
		nums[i] = randomNumber() % (winHeight / 15) + 1;

	std::vector<sf::RectangleShape> rects = InitializeVector(nums, barWidth);

	int loopCounter = 0;
	// Run the program as long as the window is open
	while (window.isOpen())
	{
		// Check all the window's events that were triggered since the last iteration of the loop
		sf::Event event;
		while (window.pollEvent(event))
		{
			// Close event requested, so close the window
			if (event.type == sf::Event::Closed)
				window.close();
		}
		// Selection sort
		if (loopCounter < nums.size() - 1)
		{
			rects[loopCounter].setFillColor(sf::Color::Red);
			int minIdx = loopCounter;
			/*
			 * Keeps track of what the previous minimum index was
			 * This will be used to set the color of the bar at the previous minimum index
			 * to the default color.
			 */
			int prevMinIdx = loopCounter;
			for (int j = loopCounter + 1; j < nums.size(); j++)
			{	
				rects[j].setFillColor(sf::Color(160, 160, 255));

				// clear the window with black color
				window.clear(sf::Color::Black);

				// draw everything here...
				for (int i = 0; i < nums.size(); i++)
					window.draw(rects[i]);

				// end the current frame
				window.display();

				if (nums[j] < nums[minIdx])
				{
					prevMinIdx = minIdx;
					minIdx = j;
					if(prevMinIdx != loopCounter)
						rects[prevMinIdx].setFillColor(sf::Color(100, 250, 250));
					rects[j].setFillColor(sf::Color(255, 0, 255));
				}
				else
					rects[j].setFillColor(sf::Color(100, 250, 250));
			}

			// Sorts the array
			std::swap(nums[loopCounter], nums[minIdx]);

			// f: first
			// s: second
			const sf::Vector2f f = rects[loopCounter].getSize();
			const sf::Vector2f s = rects[minIdx].getSize();

			auto height = f.y;
			rects[loopCounter].setSize({ f.x, s.y });
			rects[minIdx].setSize({ s.x, height });

			for (int i = loopCounter; i < nums.size(); i++)
			{
				sf::Color c(100, 250, 250);
				if (i != loopCounter)
					rects[i].setFillColor(c);
				else
					rects[i].setFillColor(sf::Color(255, 167, 0));
			}
			loopCounter++;
		}
		std::cout << nums << std::endl;
	}
	return 0;
}