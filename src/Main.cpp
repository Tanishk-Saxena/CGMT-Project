#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <stdio.h>
#include <time.h>
using namespace sf;

//To run ctrl + Shift + B, then select build and run: debug

int main()
{

reset: //reset label to reset the game

	char waste;
	scanf("%c", &waste);

	srand(time(0)); //to seed the rand() function with a random variable depending on system time to avoid predicatbility

	RenderWindow app(VideoMode(520, 470), "Arkanoid!"); //creates app and within it creates video mode window
	app.setFramerateLimit(60);							//sets fps using sleep function of sf namespace, which is dependent on OS

	Texture t1, t2, t3, t4, t5, t6, t7, t8, t9; //images to be used, live on graphics card
	t1.loadFromFile("images/block01.png");
	t2.loadFromFile("images/block02.png");
	t3.loadFromFile("images/block03.png");
	t4.loadFromFile("images/block04.png");
	t5.loadFromFile("images/block05.png");
	t6.loadFromFile("images/background2.jpg");
	t7.loadFromFile("images/ball.png");
	t8.loadFromFile("images/paddle.png");
	t9.loadFromFile("images/heart.png");

	Sprite sBackground(t6), sBall(t7), sPaddle(t8), sGameOver(t9); //textures are applied to these, these are game objects
	sPaddle.setPosition(211, 460);								   //set paddle position
	Sprite healthbar[11];										   //health bar at the top

	Sprite block1[200], block2[200], block3[200], block4[200], block5[200]; //array of blocks (200 can be ignored as array declaration needs a number)

	SoundBuffer buffer1, buffer2, buffer3, buffer4, buffer5, buffer6; //sound effects are loaded like textures
	buffer1.loadFromFile("music/collision-with-bricks.wav");
	buffer2.loadFromFile("music/collision-with-paddle.wav");
	buffer3.loadFromFile("music/collision-with-wall.wav");
	buffer4.loadFromFile("music/lose-a-life.wav");
	buffer5.loadFromFile("music/game-over.wav");
	buffer6.loadFromFile("music/game-won.wav");

	Sound sound1, sound2, sound3, sound4, sound5, sound6; //sound is to sound buffer what sprite is to a texture
	sound1.setBuffer(buffer1);
	sound2.setBuffer(buffer2);
	sound3.setBuffer(buffer3);
	sound3.setVolume(50); //set volume low cause it was too loud
	sound4.setBuffer(buffer4);
	sound4.setVolume(30); //set volume low cause it was too loud
	sound5.setBuffer(buffer5);
	sound6.setBuffer(buffer6);

	Music bgm; //background music is set using music variable bgm
	bgm.openFromFile("music/bgm.ogg");
	bgm.setVolume(20); //volume is adjusted so that it doesn't become distracting
	bgm.setLoop(true); //bgm is looped once it reaches its end

	int n = 0;					 //variable to track number of blocks initialised
	for (int j = 1; j <= 2; j++) //setting brick grid
	{
		for (int i = 1; i <= 10; i++)
		{
			block1[n].setTexture(t1);
			block1[n].setPosition(50 + ((i - 1) * 43), 40 + ((j - 1) * 20)); //every level of brick is plotted on top of lower level ones, so essentially, 5 bricks at one place
			block2[n].setTexture(t2);
			block2[n].setPosition(50 + ((i - 1) * 43), 40 + ((j - 1) * 20)); //which are removed one-by-one
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

	int life = 5;  //number of balls alloted
	int score = 0; //score of the player

	for (int i = 0; i < life; i++) //sprite to display the life indicator at the top-right
	{
		healthbar[i].setTexture(t9);
		healthbar[i].setPosition(500 - (i * 17), 10);
	}

	float dx = 0, dy = 2;	//ball position increment
	float x = 250, y = 300; //ball position

	bgm.play(); //play bgm

	while (app.isOpen()) //loop till the app is closed. Note that a window is miinimized but isOpen() will still return true
	{
		Event e;				 //Event is a class and e its object. e is basically storing events like a key press in a queue
		while (app.pollEvent(e)) //pollEvent pops the recent event in the queue. Must be called in loop as there may be multiple events at once.
		{
			if (e.type == Event::Closed)
				return 0; //if event is clicking red-cross button, then app will be closed.
		}

		x += dx;
		for (int i = 0; i < n; i++) //n is from displaying the block grid
		{
			if (FloatRect(x, y, 12, 12).intersects(block5[i].getGlobalBounds()) && i < 20) //check each block for collision
			{
				sound1.play();
				score += 5;
				block5[i].setPosition(-100, 0);
				dx = -dx; //reflection
			}
			else if (FloatRect(x, y, 12, 12).intersects(block4[i].getGlobalBounds()) && i < 40) //check each block for collision
			{
				sound1.play();
				score += 4;
				block4[i].setPosition(-100, 0);
				dx = -dx; //reflection
			}
			else if (FloatRect(x, y, 12, 12).intersects(block3[i].getGlobalBounds()) && i < 60) //check each block for collision
			{
				sound1.play();
				score += 3;
				block3[i].setPosition(-100, 0);
				dx = -dx; //reflection
			}
			else if (FloatRect(x, y, 12, 12).intersects(block2[i].getGlobalBounds()) && i < 80) //check each block for collision
			{
				sound1.play();
				score += 2;
				block2[i].setPosition(-100, 0);
				dx = -dx; //reflection
			}
			else if (FloatRect(x, y, 12, 12).intersects(block1[i].getGlobalBounds()) && i < 100) //check each block for collision
			{
				sound1.play();
				score++;
				block1[i].setPosition(-100, 0);
				dx = -dx; //reflection
			}
		}

		y += dy;
		for (int i = 0; i < n; i++) //n is from displaying the block grid
		{
			if (FloatRect(x, y, 12, 12).intersects(block5[i].getGlobalBounds()) && i < 20) //check each block for collision
			{
				sound1.play();
				score += 5;
				block5[i].setPosition(-100, 0);
				dy = -dy; //reflection
			}
			else if (FloatRect(x, y, 12, 12).intersects(block4[i].getGlobalBounds()) && i < 40) //check each block for collision
			{
				sound1.play();
				score += 4;
				block4[i].setPosition(-100, 0);
				dy = -dy; //reflection
			}
			else if (FloatRect(x, y, 12, 12).intersects(block3[i].getGlobalBounds()) && i < 60) //check each block for collision
			{
				sound1.play();
				score += 3;
				block3[i].setPosition(-100, 0);
				dy = -dy; //reflection
			}
			else if (FloatRect(x, y, 12, 12).intersects(block2[i].getGlobalBounds()) && i < 80) //check each block for collision
			{
				sound1.play();
				score += 2;
				block2[i].setPosition(-100, 0);
				dy = -dy; //reflection
			}
			else if (FloatRect(x, y, 12, 12).intersects(block1[i].getGlobalBounds()) && i < 100) //check each block for collision
			{
				sound1.play();
				score++;
				block1[i].setPosition(-100, 0);
				dy = -dy; //reflection
			}
		}

		if (x < 0 || x > 504)
		{
			sound3.play();
			dx = -dx; //bouncing
		}
		if (y < 0)
		{
			sound3.play();
			dy = -dy; //bouncing
		}
		if (y > 470) //if ball drops below paddle, life decreases by one
		{
			if (life > 1)
				sound4.play(); //the sound of losing a life plays only when there is atleast a life left after losing one

			life--;
			x = 250, y = 300; //resets the ball
			dx = 0, dy = 2;
		}

		if (life < 1) //if lives get over, game gets over, and the score is displayed
		{
			bgm.stop();
			sound5.play(); //sound of game over is played instead of sound of losing a life
			printf("Game Over.\nYour Score: %d\n", score);
		}

		if (score == 700) //if game is won, that is, maximum score of 700 is reached, then victory song is played and score is displayed
		{
			bgm.stop();
			sound6.play();
			printf("You have won!\nYour Score: %d\n", score);
		}

		int pdx = 0, bdx = dx; //pdx is for paddle's displacement, bdx is for ball's displacement because of paddle
		if (Keyboard::isKeyPressed(Keyboard::Right))
		{
			pdx = 7;
			bdx = pdx - 1; //bdx is in the same direction, but one less in magnitude
		}
		if (Keyboard::isKeyPressed(Keyboard::Left))
		{
			pdx = -7;
			bdx = pdx + 1; //bdx is in the same direction, but one less in magnitude
		}
		if (sPaddle.getPosition().x + pdx >= 0 && sPaddle.getPosition().x + pdx <= 430)
			sPaddle.move(pdx, 0); //to move paddle left or right as per pdx (paddle dx)

		if (FloatRect(x, y, 12, 12).intersects(sPaddle.getGlobalBounds()))
		{
			sound2.play();
			dx = bdx;				//ball on hitting the paddle will move in direction of the paddle
			dy = -(rand() % 5 + 2); //if paddle intersects ball, bounce back at a random rate
		}

		sBall.setPosition(x, y); //put ball sprite at the position x and y, which was till now using a floating rectangle

		app.clear();		   //clear the previous frame
		app.draw(sBackground); //render the sprite and its texture
		app.draw(sBall);	   //render the sprite and its texture
		app.draw(sPaddle);	   //render the sprite and its texture

		for (int i = 0; i < 20; i++) //render the brick grid
		{
			app.draw(block1[i]); //these sub-loops are so that the block arrays are fully displayed till the index they store bricks in
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

		for (int i = 0; i < life; i++) // render the health bar sprite array and its texture, till uindex of as many lives are remaining
		{
			app.draw(healthbar[i]);
		}

		app.display(); //display what has been rendered for the current frame in the game window

		if (life < 1 || score == 700)
		{
			break; //breaks out of the while loop
		}
	}
	char retry;								  //retry variable
	printf("Do you wanna go again? (y/n)  "); //asking for a re-run
	scanf("%c", &retry);
	if (retry == 'y')
		goto reset; //follows the label of reset if asked to retry, otherwise returns.
	return 0;
}
