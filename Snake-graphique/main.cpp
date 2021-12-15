#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <time.h>
using namespace sf;

int N = 60, M = 50;
int size = 16;
int w = size * N;
int h = size * M;

int dir, num = 1;

struct Snake
{
	int x, y;
}  s[900];

struct Fruct
{
	int x, y;
} f;



void Tick()
{
	for (int i = num; i > 0; --i)
	{
		s[i].x = s[i - 1].x;
		s[i].y = s[i - 1].y;
	}

	if (dir == 0) s[0].y += 1;
	if (dir == 1) s[0].x -= 1;
	if (dir == 2) s[0].x += 1;
	if (dir == 3) s[0].y -= 1;

	if ((s[0].x == f.x) && (s[0].y == f.y))
	{
		num++;
		f.x = rand() % N;
		f.y = rand() % M;
	}

	if (s[0].x > N) s[0].x = 0;  if (s[0].x < 0) s[0].x = N;
	if (s[0].y > M) s[0].y = 0;  if (s[0].y < 0) s[0].y = M;

	for (int i = 1; i < num; i++)
		if (s[0].x == s[i].x && s[0].y == s[i].y) {
			num = 0;
		}
}

int main()
{
	srand(time(0));

	RenderWindow window(VideoMode(w, h), "Snake Game!");

	//test1

	/*sf::Texture t1;
	sf::Image image1;
	image1.loadFromFile("white.png");
	t1.loadFromImage("white.png");

	sf::Texture t2;
	sf::Image image2;
	image2.loadFromFile("red.png");
	t2.loadFromImage("image2");*/

	//test2

	// Load a texture from a file
	sf::Texture t1;
	if (!t1.loadFromFile("white.png"))
		return -1;

	// Assign it to a sprite
	sf::Sprite sprite1;
	sprite1.setTexture(t1);

	// Load a texture from a file
	sf::Texture t2;
	if (!t2.loadFromFile("red.png"))
		return -1;

	// Assign it to a sprite
	sf::Sprite sprite2;
	sprite2.setTexture(t2);

	sf::Texture t3;
	if (!t3.loadFromFile("green.png"))
		return -1;

	sf::Sprite sprite3;
	sprite3.setTexture(t3);

	//test3

	/*Texture t1, t2;
	t1.loadFromFile("white.png");
	t2.loadFromFile("red.png");

	Sprite sprite1(t1);
	Sprite sprite2(t2);*/

	Clock clock;
	float timer = 0, delay = 0.1;

	f.x = 10;
	f.y = 10;

	while (window.isOpen())
	{
		float time = clock.getElapsedTime().asSeconds();
		clock.restart();
		timer += time;

		Event e;
		while (window.pollEvent(e))
		{
			if (e.type == Event::Closed)
				window.close();
		}

		if (Keyboard::isKeyPressed(Keyboard::Left)) dir = 1;
		if (Keyboard::isKeyPressed(Keyboard::Right))  dir = 2;
		if (Keyboard::isKeyPressed(Keyboard::Up)) dir = 3;
		if (Keyboard::isKeyPressed(Keyboard::Down)) dir = 0;
		if (num == 0)
			window.close();

		if (timer > delay) { timer = 0; Tick(); }

		////// draw  ///////
		window.clear();

		for (int i = 0; i < N; i++)
			for (int j = 0; j < M; j++)
			{
				sprite1.setPosition(i * size, j * size);  window.draw(sprite1);
			}

		for (int i = 0; i < num; i++)
		{
			sprite2.setPosition(s[i].x * size, s[i].y * size);  window.draw(sprite2);
		}

		sprite3.setPosition(f.x * size, f.y * size);  window.draw(sprite3);

		window.display();
	}

	return 0;
}