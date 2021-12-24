#include <SFML/Graphics.hpp>
#include <stdio.h>
#include <time.h>
using namespace sf;

//To run ctrl + Shift + B

//TODO:
//1. Background music
//2. Background Image--------done
//3. Score Counter at corner--------done
//4. Game Over Screen (Score, Restart)--------semi-done
//5. Life Counter--------done
//6. Lose one life on border touch--------done
//7. Extra: Color Changing blocks--------done

int main()
{

reset:

	srand(time(0));

	RenderWindow app(VideoMode(520, 470), "Arkanoid!"); //creates app and within it creates video mode window
	app.setFramerateLimit(60);							//sets fps using sleep function of sf namespace, which is dependent on OS

	Texture t1, t2, t3, t4, t5, t6, t7, t8; //images to be used, live on graphics card
	t1.loadFromFile("images/block01.png");
	t2.loadFromFile("images/block02.png");
	t3.loadFromFile("images/block03.png");
	t4.loadFromFile("images/block04.png");
	t5.loadFromFile("images/block05.png");
	t6.loadFromFile("images/background.jpg");
	t7.loadFromFile("images/ball.png");
	t8.loadFromFile("images/paddle.png");

	Sprite sBackground(t6), sBall(t7), sPaddle(t8); //textures are applied to these, these are game objects
	sPaddle.setPosition(215, 460);					//set paddle position
	Sprite healthbar[11];							//health bar at the top

	Sprite block1[200], block2[200], block3[200], block4[200], block5[200]; //array of blocks (200 can be ignored as array declaration needs a number)

	int n = 0;
	for (int j = 1; j <= 2; j++)
	{
		for (int i = 1; i <= 10; i++)
		{
			block1[n].setTexture(t1);
			block1[n].setPosition(50 + ((i - 1) * 43), 40 + ((j - 1) * 20));
			block2[n].setTexture(t2);
			block2[n].setPosition(50 + ((i - 1) * 43), 40 + ((j - 1) * 20));
			block3[n].setTexture(t3);
			block3[n].setPosition(50 + ((i - 1) * 43), 40 + ((j - 1) * 20));
			block4[n].setTexture(t4);
			block4[n].setPosition(50 + ((i - 1) * 43), 40 + ((j - 1) * 20));
			block5[n].setTexture(t5);
			block5[n].setPosition(50 + ((i - 1) * 43), 40 + ((j - 1) * 20));
			n++;
		}
	}
	for (int j = 3; j <= 4; j++)
	{
		for (int i = 1; i <= 10; i++)
		{
			block1[n].setTexture(t1);
			block1[n].setPosition(50 + ((i - 1) * 43), 40 + ((j - 1) * 20));
			block2[n].setTexture(t2);
			block2[n].setPosition(50 + ((i - 1) * 43), 40 + ((j - 1) * 20));
			block3[n].setTexture(t3);
			block3[n].setPosition(50 + ((i - 1) * 43), 40 + ((j - 1) * 20));
			block4[n].setTexture(t4);
			block4[n].setPosition(50 + ((i - 1) * 43), 40 + ((j - 1) * 20));
			n++;
		}
	}
	for (int j = 5; j <= 6; j++)
	{
		for (int i = 1; i <= 10; i++)
		{
			block1[n].setTexture(t1);
			block1[n].setPosition(50 + ((i - 1) * 43), 40 + ((j - 1) * 20));
			block2[n].setTexture(t2);
			block2[n].setPosition(50 + ((i - 1) * 43), 40 + ((j - 1) * 20));
			block3[n].setTexture(t3);
			block3[n].setPosition(50 + ((i - 1) * 43), 40 + ((j - 1) * 20));
			n++;
		}
	}
	for (int j = 7; j <= 8; j++)
	{
		for (int i = 1; i <= 10; i++)
		{
			block1[n].setTexture(t1);
			block1[n].setPosition(50 + ((i - 1) * 43), 40 + ((j - 1) * 20));
			block2[n].setTexture(t2);
			block2[n].setPosition(50 + ((i - 1) * 43), 40 + ((j - 1) * 20));
			n++;
		}
	}
	for (int j = 9; j <= 10; j++)
	{
		for (int i = 1; i <= 10; i++)
		{
			block1[n].setTexture(t1);
			block1[n].setPosition(50 + ((i - 1) * 43), 40 + ((j - 1) * 20));
			n++;
		}
	}

	int life = 5;
	int score = 0;

	for (int i = 0; i < life; i++)
	{
		healthbar[i].setTexture(t7);
		healthbar[i].setPosition(500 - (i * 17), 10);
	}

	float dx = 0, dy = 2;	//ball position increment
	float x = 254, y = 300; //ball position

	while (app.isOpen()) //loop till the app is closed. Note that a window is miinimized but isOpen() will still return true
	{
		Event e;				 //Event is a class and e its object. e is basically storing events like a key press in a queue
		while (app.pollEvent(e)) //pollEvent pops the recent event in the queue. Must be called in loop as there may be multiple events at once.
		{
			if (e.type == Event::Closed)
				app.close(); //if event is clicking red-cross button, then app will be closed.
		}

		x += dx;
		for (int i = 0; i < n; i++) //n is from displaying the block grid
		{
			if (FloatRect(x - 6, y - 6, 12, 12).intersects(block5[i].getGlobalBounds()) && i < 20) //check each block for collision
			{
				score += 5;
				block5[i].setPosition(-100, 0);
				dx = -dx; //reflection
			}
			else if (FloatRect(x - 6, y - 6, 12, 12).intersects(block4[i].getGlobalBounds()) && i < 40) //check each block for collision
			{
				score += 4;
				block4[i].setPosition(-100, 0);
				dx = -dx; //reflection
			}
			else if (FloatRect(x - 6, y - 6, 12, 12).intersects(block3[i].getGlobalBounds()) && i < 60) //check each block for collision
			{
				score += 3;
				block3[i].setPosition(-100, 0);
				dx = -dx; //reflection
			}
			else if (FloatRect(x - 6, y - 6, 12, 12).intersects(block2[i].getGlobalBounds()) && i < 80) //check each block for collision
			{
				score += 2;
				block2[i].setPosition(-100, 0);
				dx = -dx; //reflection
			}
			else if (FloatRect(x - 6, y - 6, 12, 12).intersects(block1[i].getGlobalBounds()) && i < 100) //check each block for collision
			{
				score++;
				block1[i].setPosition(-100, 0);
				dx = -dx; //reflection
			}
		}

		y += dy;
		for (int i = 0; i < n; i++) //n is from displaying the block grid
		{
			if (FloatRect(x - 6, y - 6, 12, 12).intersects(block5[i].getGlobalBounds()) && i < 20) //check each block for collision
			{
				score += 5;
				block5[i].setPosition(-100, 0);
				dy = -dy; //reflection
			}
			else if (FloatRect(x - 6, y - 6, 12, 12).intersects(block4[i].getGlobalBounds()) && i < 40) //check each block for collision
			{
				score += 4;
				block4[i].setPosition(-100, 0);
				dy = -dy; //reflection
			}
			else if (FloatRect(x - 6, y - 6, 12, 12).intersects(block3[i].getGlobalBounds()) && i < 60) //check each block for collision
			{
				score += 3;
				block3[i].setPosition(-100, 0);
				dy = -dy; //reflection
			}
			else if (FloatRect(x - 6, y - 6, 12, 12).intersects(block2[i].getGlobalBounds()) && i < 80) //check each block for collision
			{
				score += 2;
				block2[i].setPosition(-100, 0);
				dy = -dy; //reflection
			}
			else if (FloatRect(x - 6, y - 6, 12, 12).intersects(block1[i].getGlobalBounds()) && i < 100) //check each block for collision
			{
				score++;
				block1[i].setPosition(-100, 0);
				dy = -dy; //reflection
			}
		}

		if (x < 0 || x > 520)
			dx = -dx; //bouncing
		if (y < 0)
			dy = -dy; //bouncing
		if (y > 470)
		{
			life--;
			x = 260, y = 300;
			dx = 0, dy = 2;
		}

		if (life < 1)
		{
			printf("Game Over.\nYour Score: %d\n", score);
			break;
		}

		int pdx = 0, bdx = dx;
		if (Keyboard::isKeyPressed(Keyboard::Right))
		{
			pdx = 7;
			bdx = pdx - 1;
		}
		if (Keyboard::isKeyPressed(Keyboard::Left))
		{
			pdx = -7;
			bdx = pdx + 1;
		}
		sPaddle.move(pdx, 0); //to move paddle left or right as per pdx (paddle dx)

		if (FloatRect(x, y, 12, 12).intersects(sPaddle.getGlobalBounds()))
		{
			dx = bdx;				//ball on hitting the paddle will move in direction of the paddle
			dy = -(rand() % 5 + 2); //if paddle intersects ball, bounce back at a random rate
		}

		sBall.setPosition(x, y); //put ball sprite at the position x and y, which was till now using a floating rectangle

		app.clear();		   //clear the previous frame
		app.draw(sBackground); //render the sprite and its texture
		app.draw(sBall);	   //render the sprite and its texture
		app.draw(sPaddle);	   //render the sprite and its texture

		for (int i = 0; i < 20; i++)
		{
			app.draw(block1[i]);
			app.draw(block2[i]);
			app.draw(block3[i]);
			app.draw(block4[i]);
			app.draw(block5[i]);
		}
		for (int i = 20; i < 40; i++)
		{
			app.draw(block1[i]);
			app.draw(block2[i]);
			app.draw(block3[i]);
			app.draw(block4[i]);
		}
		for (int i = 40; i < 60; i++)
		{
			app.draw(block1[i]);
			app.draw(block2[i]);
			app.draw(block3[i]);
		}
		for (int i = 60; i < 80; i++)
		{
			app.draw(block1[i]);
			app.draw(block2[i]);
		}
		for (int i = 80; i < 100; i++)
		{
			app.draw(block1[i]);
		}

		for (int i = 0; i < life; i++)
		{
			app.draw(healthbar[i]);
		}

		app.display(); //display what has been rendered for the current frame in the game window
	}
	char retry;
	printf("Do you wanna go again? (y/n)  ");
	scanf("%c", &retry);
	if (retry == 'y')
		goto reset;
	return 0;
}
