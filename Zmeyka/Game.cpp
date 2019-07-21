#include "SFML/Graphics.hpp"

class yammy{
public:
	int x;
	int y;
	yammy() {};
	void getXY(int b)
	{
		x = rand() % 50 * b - b / 2;
		y = rand() % 50 * b - b / 2;
	}	
};
struct snake {
	int x;
	int y;
};

void keys(int &key) {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) key = 0;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) key = 1;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) key = 2;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) key = 3;
}

void Lick(int &snakesize, snake *s, int &key, int b, bool &go, int square, int &speed, yammy *eat) {
	if(key>=0 && key<=3)
		for (int i(snakesize); i > 0; i--) {
			s[i].x = s[i - 1].x;
			s[i].y = s[i - 1].y;
			}
	switch (key) {
	case 0: s->y -= b; break;
	case 1: s->y += b; break;
	case 2: s->x -= b; break;
	case 3: s->x += b; break;
	}
	for (int i(0); i < 10; i++) {
		if (s->x == eat[i].x && s->y == eat[i].y) {
			snakesize++;
			eat[i].getXY(b);
			speed -= 20000;
		}
	}		
	if ((s->x < 0 || s->x > b*square) || (s->y <0 || s->y > b*square)) go = true;
}

int main()
{		srand(time(NULL)); 
		int size(800);
		int Count(50);
		int b = size / Count;
		int key;
		int speed(200000);
		bool isGameOver(false);
		int countGreen = 0;
		int countRed = 0;
		snake s[1000];
		yammy eat[100];
		int snakesize(3);
		sf::RenderWindow window(sf::VideoMode(size, size), "Snake!");
		sf::RectangleShape rect(sf::Vector2f(b, b));
		rect.setOutlineColor(sf::Color::Black);
		rect.setOutlineThickness(1);
		sf::Clock clock;
				
		for (int i(0); i < snakesize; i++)
		{
			s[i].x = b * (Count / 2)  -(b / 2);
			s[i].y = b * (Count / 2) - (b / 2)+ i*b;
		}

		for (int i(0); i < 100; i++)
			eat[i].getXY(b);
		
	while (window.isOpen())
	{
		keys(key);
		float time = clock.getElapsedTime().asMicroseconds();
		if (time > speed && !isGameOver) {
			Lick(snakesize,s,key,b,isGameOver,Count,speed,eat);
			clock.restart();
		}

		sf::Event event;
		
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		sf::Texture t;
		t.loadFromFile("2.png");
		
		window.clear();
		for (int i(0); i < Count; i++)
			for (int j(0); j < Count; j++)
			{
				for (int k(0); k < snakesize; k++)
					if (s[k].x == i * b - (b / 2) && s[k].y == j * b - (b / 2))
						countGreen++;
				for (int p(0); p < 10; p++)
					if (eat[p].x == i * b - (b / 2) && eat[p].y == j * b - (b / 2))
						countRed++;
				if (countGreen > 0) {
					rect.setFillColor(sf::Color::Black); 
				
				}
				else if (countRed > 0) { rect.setFillColor(sf::Color::Magenta); rect.setTexture(&t); }
			else rect.setFillColor(sf::Color::White);
			rect.setPosition(i*b, j*b);
		window.draw(rect);
		countGreen = 0;
		countRed = 0;
			}
		window.display();
	}

	return 0;
}