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

void SwapHeight(sf::RenderWindow& w, std::vector<sf::RectangleShape>& v, int i, int j)
{
	v[i].setFillColor(sf::Color::Blue);
	v[j].setFillColor(sf::Color::Green);

	// clear the window with black color
	w.clear(sf::Color::Black);

	// draw everything here...
	for (int i = 0; i < v.size(); i++)
		w.draw(v[i]);

	// end the current frame
	w.display();

	// f: first bar
	// s: second bar
	const sf::Vector2f f = v[i].getSize();
	const sf::Vector2f s = v[j].getSize();

	auto height = f.y;
	v[i].setSize({ f.x, s.y });
	v[j].setSize({ s.x, height });

	v[i].setFillColor(sf::Color(100, 250, 250));
	v[j].setFillColor(sf::Color(100, 250, 250));
}

void selectionSort(sf::RenderWindow& window, std::vector<sf::RectangleShape>& rects, std::vector<int>& nums)
{
	for (int loopCounter = 0; loopCounter < nums.size() - 1; loopCounter++)
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
	}
}

int partition(sf::RenderWindow& w, std::vector<sf::RectangleShape>& r, std::vector<int>& v, int low, int high)
{
	int pivot = v[high];
	
	// Paint the pivot magenta
	r[high].setFillColor(sf::Color::Magenta);

	int i = low - 1;
	for (int j = low; j <= high - 1; j++)
	{
		r[j].setFillColor(sf::Color::Red);

		// clear the window with black color
		w.clear(sf::Color::Black);

		// draw everything here...
		for (int i = 0; i < v.size(); i++)
			w.draw(r[i]);

		// end the current frame
		w.display();

		if (v[j] < pivot)
		{
			i++;

			SwapHeight(w, r, i, j);
			std::swap(v[i], v[j]);
		}
		else 
			r[j].setFillColor(sf::Color(100, 250, 250));
	}

	SwapHeight(w, r, i + 1, high);
	std::swap(v[i + 1], v[high]);
	return i + 1;
}

void qsort(sf::RenderWindow& w, std::vector<sf::RectangleShape>& r, std::vector<int>& v, int low, int high)
{
	if (low < high)
	{
		int pivot = partition(w, r, v, low, high);
		qsort(w, r, v, low, pivot - 1);
		qsort(w, r, v, pivot + 1, high);
	}

	// clear the window with black color
	w.clear(sf::Color::Black);

	// draw everything here...
	for (int i = 0; i < v.size(); i++)
		w.draw(r[i]);

	// end the current frame
	w.display();
}

int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "Sorting algorithm Visualizer", sf::Style::Titlebar | sf::Style::Close);
	window.setFramerateLimit(60);

	// Obtain a seed from the system clock
	unsigned int seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::minstd_rand0 randomNumber(seed);

	int winWidth = window.getSize().x;
	int winHeight = window.getSize().y;
	int barWidth = 5;
	int numberOfElements = winWidth / (barWidth + 1);

	std::vector<int> nums(numberOfElements);
	for (int i = 0; i < numberOfElements; i++)
		nums[i] = randomNumber() % (winHeight / 12) + 1;

	std::vector<sf::RectangleShape> rects = InitializeVector(nums, barWidth);

	bool called = false;
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
		if (!called)
		{
			qsort(window, rects, nums, 0, nums.size() - 1);
			//selectionSort(window, rects, nums);
			called = true;
		}
		
		std::cout << nums << std::endl;
	}
	return 0;
}