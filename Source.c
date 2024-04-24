#define _CRT_SECURE_NO_DEPRECATE
#include<stdio.h>
#include<stdlib.h>
#include<raylib.h>
#include<raymath.h>
#include<string.h>
#include<time.h>
//

void AddScore(int);
# define player_shots 1
const int width = 800;
const int height = 450;
const int boySpeed = 5;
const int gravity = 1;

//const int groundYPos = 450;//Adjust boy Height
typedef struct shoot {
	Vector2 speed;
	bool active;
	Color color;
	Vector2 position;
	int lifespan;
	float radius;
}shoot;
static shoot shot[player_shots] = { 0 };

bool isBoyOnGround(Texture2D*boy, Vector2* boyPosition)
{  
	if (boyPosition->y+boy->height >= height)
	{
		return true;
	}
	else
		return false;
}
bool right;
void AddFile(int);
int main()
{	
	/*FILE* ptr;
	char str[50];
	char highscore[50];*/



	srand(time(NULL));
	InitWindow(width, height, "Abdullah's End Semester Project");
	InitAudioDevice();
	Texture2D boy = LoadTexture("../End semister project/character2.png");//To load images
	Texture2D badboy = LoadTexture("../End semister project/scarfy2.png");
	Texture2D bird = LoadTexture("../End semister project/bird2.png");
	Texture2D background = LoadTexture("../End semister project/cyberpunk_street_background.png");
	Texture2D midground = LoadTexture("../End semister project/cyberpunk_street_midground.png");
	Texture2D foreground = LoadTexture("../End semister project/cyberpunk_street_foreground.png");
	Texture2D back = LoadTexture("C:/Users/abdul/OneDrive/Desktop/c/End semister project/gameback.png");

	Texture2D logo = LoadTexture("C:/Users/abdul/OneDrive/Desktop/c/End semister project/logo.png");
	Texture2D control = LoadTexture("C:/Users/abdul/OneDrive/Desktop/c/End semister project/ct2.png");

	Music gamesound = LoadMusicStream("C:/Users/abdul/OneDrive/Desktop/c/End semister project/gamesound.wav");
	Sound gunsound = LoadSound("C:/Users/abdul/OneDrive/Desktop/c/End semister project/gun.wav");
	Sound losesound = LoadSound("C:/Users/abdul/OneDrive/Desktop/c/End semister project/lose.wav");
	Sound dead = LoadSound("C:/Users/abdul/OneDrive/Desktop/c/End semister project/dead.wav");

	float scrollingBack = 0.0f;
	float scrollingMid = 0.0f;
	float scrollingFore = 0.0f;
	int speed = 5;
	int speedcounter = 0;
	int counter = 0;
	

	unsigned frameNum = 8;//For boy
	unsigned frameNum2 = 6;//For badboy
	unsigned frameNum3 = 4;
	int frameWidth = boy.width / frameNum;
	int frameWidth2 = badboy.width / frameNum2;
	int frameWidth3 = bird.width/frameNum3;
	Rectangle frameRec = { 0.0f,0.0f,(float)frameWidth,(float)boy.height };
	Rectangle frameRec2 = { 0.0f,0.0f,(float)frameWidth2,(float)badboy.height };
	Rectangle frameRec3 = { 0.0f,0.0f,(float)frameWidth3,(float)bird.height };

	Vector2 boyPosition = {height-350,height-boy.height };
	Vector2 badboyPosition = { 1000,height - badboy.height };
	Vector2 birdPosition = { 1200,100};
	Vector3 CyPosition = { height-150,height - boy.height };
	Vector3 CyPosition2 = { height-150,height - badboy.height };
	Vector3 CyPosition3 = { 300,height - bird.height };
	Vector2 boyVelocity = { 0.0f,0.0f };
	Vector2 badboyVelocity = { 0.0f,0.0f };
	Vector2 birdVelocity = { 0.0f,0.0f };

	Rectangle boyHitbox = (Rectangle){ boyPosition.x, boyPosition.y, 75, 50 };
	Rectangle badBoyHitbox = (Rectangle){ badboyPosition.x, badboyPosition.y, 50, 91 };
	Rectangle birdHitbox = (Rectangle){ birdPosition.x,birdPosition.y,75,50 };

	unsigned frameIndex = 0;//For boy
	unsigned frameIndex2 = 0;//For Bad boy
	unsigned frameIndex3 = 0;
	unsigned frameDelay = 4;
	unsigned frameDelayCounter = 0;
	bool boyMoving = false;
	bool BackGroundMoving = false;
	bool gameover = false;
	bool start = false;
	for (int i = 0; i < player_shots; i++)
	{
		shot[i].position = (Vector2){ boyPosition.x + 30,boyPosition.y + 30 };
		shot[i].speed.x = 3;
		shot[i].radius = 10;
		shot[i].active = false;
		shot[i].color = WHITE;
		shot[i].lifespan = 0;
	}

	int menu = 1, game = 0,ctscreen=0;

	int hover1 = 0, hover2 = 0, hover3 = 0,hover4=0;


	//ToggleFullscreen();
	SetTargetFPS(60);
	printf("%d", badboy.height);
	while (!WindowShouldClose())

	{
		UpdateMusicStream(gamesound);
		if (ctscreen)
		{
			if (CheckCollisionPointRec(GetMousePosition(), (Rectangle) { 30, 30, 100, 40 }))
			{
				hover4 = 1;
				if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
				{
					menu = 1;
					ctscreen = 0;
				}
			}
			else hover4 = 0;
		}
		if (menu)
		{
			if (CheckCollisionPointRec(GetMousePosition(), (Rectangle) { GetScreenWidth() / 2 - 110, 240, 200, 40 }))
			{
				hover1 = 1;
				if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
				{
					menu = 0;
					game = 1;
					PlayMusicStream(gamesound);
				}

			}
			else hover1 = 0;
			if (CheckCollisionPointRec(GetMousePosition(), (Rectangle) { GetScreenWidth() / 2 - 110, 300, 200, 40 }))
			{
				hover2 = 1;
				if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
				{
					menu = 0;
					ctscreen = 1;
				}
			}
			else hover2 = 0;
			if (CheckCollisionPointRec(GetMousePosition(), (Rectangle) { GetScreenWidth() / 2 - 110, 365, 200, 40 }))
			{
				hover3 = 1;
				if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
				{
					
					CloseWindow();
					return 0;''
				}
			}
			else hover3 = 0;
		}
		//if(start)
		
		if (game) {
			if (!gameover)
			{
				
				if (IsKeyPressed(KEY_RIGHT))
				{
					BackGroundMoving = true;
				}
				if (BackGroundMoving)
				{
					scrollingBack -= 0.4f;/*For Background Movement*/
					scrollingMid -= 0.8f;
					scrollingFore -= 4.0f;


					// Texture is scaled twice its size, so it should be considered on scrolling
					if (scrollingBack <= -background.width * 2) scrollingBack = 0;
					if (scrollingMid <= -midground.width * 2) scrollingMid = 0;
					if (scrollingFore <= -foreground.width * 2) scrollingFore = 0;
				}
				if (isBoyOnGround(&boy, &boyPosition) && (IsKeyDown(KEY_UP)) || (IsKeyPressed(KEY_J)))

				{
					boyVelocity.y = -4 * boySpeed;			//Adjust height of jump here
				}
				if (IsKeyDown(KEY_RIGHT))// Moves Forwrad
				{
					boyMoving = true;
					right = true;
					//boyVelocity.x = boySpeed; //This will move the character along x axis
					badboyVelocity.x = -speed;
					birdVelocity.x = -speed;
					if (frameRec.width < 0)
					{
						frameRec.width = -frameRec.width;//This will reverse the direction of the characer
					}
					if (frameRec2.width > 0)
					{
						frameRec2.width = -frameRec2.width;//This is used to reverse the direction of badboy
					}
					if (frameRec3.width < 0)
					{
						frameRec3.width = -frameRec3.width;//This is used to reverse the direction of badboy
					}
				}
				else if (IsKeyDown(KEY_LEFT))
				{

					boyMoving = true;
					right = false;
					//boyVelocity.x = -boySpeed;//This will move the character along x axis in reverse direction
					//badboyVelocity.x = boySpeed;
					if (frameRec.width > 0)
					{
						frameRec.width = +frameRec.width;//This will reverse the direction of the characer 
					}

				}
				else
				{
					boyVelocity.x = 0;
					boyMoving = false;
				}
				bool badboyMoving = badboyVelocity.x != 0.0f || badboyVelocity.y != 0.0f;
				//bool boyMoving = boyVelocity.x != 0.0f || boyVelocity.y != 0.0f;


				boyPosition = Vector2Add(boyPosition, boyVelocity);//This will move the frames forward
				badboyPosition = Vector2Add(badboyPosition, badboyVelocity);
				birdPosition = Vector2Add(birdPosition, birdVelocity);
				if (isBoyOnGround(&boy, &boyPosition))
				{
					boyVelocity.y = 0;
					boyPosition.y = height - boy.height;
				}
				else
				{
					boyVelocity.y += gravity;
				}


				++frameDelayCounter;									//Controlls frame Rate
				if (frameDelayCounter > frameDelay)
				{
					frameDelayCounter = 0;
					if (boyMoving || badboyMoving)						//Boy will only move if the condition is true
					{
						++frameIndex;										//Boy Movement
						frameIndex = frameIndex % frameNum;
						frameRec.x = (float)frameWidth * frameIndex;

						++frameIndex2;
						frameIndex2 %= frameNum2;						//For Badboy index
						frameRec2.x = (float)frameWidth2 * frameIndex2;


						++frameIndex3;
						frameIndex3 %= frameNum3;						//For Badboy index
						frameRec3.x = (float)frameWidth3 * frameIndex3;
						counter++;

					}

				}


				if (badboyPosition.x < -badboy.width)
				{
					badboyPosition.x = width + rand() % 1000 + 1;
				}
				if (birdPosition.x < -bird.width)
				{
					birdPosition.x = width + rand() % 3000 + 2;
				}

				boyHitbox = (Rectangle){ boyPosition.x, boyPosition.y, 75, 50 };
				badBoyHitbox = (Rectangle){ badboyPosition.x, badboyPosition.y, 50, 91 };
				birdHitbox = (Rectangle){ birdPosition.x + 100,birdPosition.y + 100,50,50 };
				if (CheckCollisionRecs(boyHitbox, badBoyHitbox) || CheckCollisionRecs(boyHitbox, birdHitbox))
				{
					badboyPosition.x = width + rand() % 1000 + 1;
					birdPosition.x = width + rand() % 3000 + 2;

					PlaySound(losesound);
					StopMusicStream(gamesound);
					gameover = true;
					//AddScore(counter);
				}
				
				/*if (CheckCollisionCircleRec(shot[i].position, shot[i].radius, boyHitbox))
				{
					badboyPosition.x = width + rand() % 1000 + 1;
					birdPosition.x = width + rand() % 3000 + 2;
				}*/
				speedcounter++;
				if (speedcounter > 300)
				{
					speed += 2;
					speedcounter = 0;
				
				}



			}
			if (gameover)
			{
				/*ptr = fopen("test.txt", "a+");
				while (fgets(str, 50, ptr) != NULL) {
					strcat(highscore, str);
				}
				fclose(ptr);
				ptr = fopen("test.txt", "w");
				if (atoi(highscore) < counter)
				{
					fprintf(ptr, "%s", _itoa(counter,highscore,10));
					
				}
				fclose(ptr);
				*/
				if (IsKeyPressed(KEY_SPACE))
				{
					menu = 1;
					game = 0;
					gameover = 0;
					counter = 0;
					speed = 5;
				}
			}
		}
			BeginDrawing();

			if (ctscreen)
			{
				DrawTextureV(back, (Vector2) { 0, 0 }, WHITE);
				DrawTextureV(control, (Vector2) { 180, 280 }, WHITE);

				DrawRectangleRounded((Rectangle) { 30, 30, 100, 40 }, 3, 1, hover4 ? DARKPURPLE : GetColor(0x052c46ff));
				DrawRectangleRoundedLines((Rectangle) { 30, 30, 100, 40 }, 3, 1, 2, GRAY);
				DrawText("Back", 40, 35, 30, ORANGE);
			}

			if (menu)
			{
				DrawTextureV(back, (Vector2) { 0, 0 }, WHITE);
				DrawTextureV(logo, (Vector2) { GetScreenWidth() / 2 - 250, 40 }, WHITE);
				DrawRectangleRounded((Rectangle) { GetScreenWidth() / 2 - 110, 240, 200, 40 }, 3, 1, hover1 ? DARKPURPLE : GetColor(0x052c46ff));
				DrawRectangleRoundedLines((Rectangle) { GetScreenWidth() / 2 - 110, 240, 200, 40 }, 3, 1, 2, GRAY);
				DrawText("Play game", GetScreenWidth() / 2 - 80, 245, 30, ORANGE);

				DrawRectangleRounded((Rectangle) { GetScreenWidth() / 2 - 110, 300, 200, 40 }, 3, 1, hover2 ? DARKPURPLE : GetColor(0x052c46ff));
				DrawRectangleRoundedLines((Rectangle) { GetScreenWidth() / 2 - 110, 300, 200, 40 }, 3, 1, 2, GRAY);
				DrawText("Controls", GetScreenWidth() / 2 - 80, 305, 30, ORANGE);

				DrawRectangleRounded((Rectangle) { GetScreenWidth() / 2 - 110, 360, 200, 40 }, 3, 1, hover3 ? DARKPURPLE : GetColor(0x052c46ff));
				DrawRectangleRoundedLines((Rectangle) { GetScreenWidth() / 2 - 110, 360, 200, 40 }, 3, 1, 2, GRAY);
				DrawText("Exit Game", GetScreenWidth() / 2 - 80, 365, 30, ORANGE);

			}

			if (game)
			{
				ClearBackground(GetColor(0x052c46ff));
				// Draw background image twice
					// NOTE: Texture is scaled twice its size
				DrawTextureEx(background, (Vector2) { scrollingBack, 20 }, 0.0f, 2.0f, WHITE);
				DrawTextureEx(background, (Vector2) { background.width * 2 + scrollingBack, 20 }, 0.0f, 2.0f, WHITE);

				// Draw midground image twice
				DrawTextureEx(midground, (Vector2) { scrollingMid, 20 }, 0.0f, 2.0f, WHITE);
				DrawTextureEx(midground, (Vector2) { midground.width * 2 + scrollingMid, 20 }, 0.0f, 2.0f, WHITE);

				// Draw foreground image twice
				DrawTextureEx(foreground, (Vector2) { scrollingFore, 70 }, 0.0f, 2.0f, WHITE);
				DrawTextureEx(foreground, (Vector2) { foreground.width * 2 + scrollingFore, 70 }, 0.0f, 2.0f, WHITE);
				DrawText("(c) Abdullah's Background", width - 150, height - 20, 10, RAYWHITE);
				DrawText(TextFormat("%d Feet", counter), width - 200, 30, 40, RAYWHITE);

				DrawTextureRec(boy, frameRec, boyPosition, RAYWHITE);
				DrawTextureRec(badboy, frameRec2, badboyPosition, RAYWHITE);
				DrawTextureRec(bird, frameRec3, birdPosition, RAYWHITE);

				if (gameover)
				{
					DrawText(TextFormat("GAME OVER!!!"), GetScreenWidth() / 3.5, width / 10, height / 9, YELLOW);
					DrawText("Press Space to return to main menu", GetScreenWidth() / 4.5, 200, 25, YELLOW);
				}
				/*DrawRectangleLinesEx(badBoyHitbox, 10, GREEN);
				DrawRectangleLinesEx(boyHitbox, 10, RED);
				DrawRectangleLinesEx(birdHitbox, 10, RED);*/
				if (IsKeyPressed(KEY_F))
				{
					PlaySound(gunsound);
					for (int i = 0; i < player_shots; i++)
						if (!shot[i].active)
						{
							shot[i].position = (Vector2){ boyPosition.x + 30,boyPosition.y + 80 };
							shot[i].active = true;
							break;
						}
				}
				for (int i = 0; i < player_shots; i++)
				{
					if (shot[i].active)
					{
						if (CheckCollisionCircleRec(shot[i].position, shot[i].radius, badBoyHitbox)) {
							badboyPosition.x = width + rand() % 1000 + 1;
							shot[i].active = false;
							PlaySound(dead);
						}
						if (CheckCollisionCircleRec(shot[i].position, shot[i].radius, birdHitbox)) {
							birdPosition.x = width + rand() % 3000 + 1;
							shot[i].active = false;
							PlaySound(dead);
						}

						shot[i].position.x += 3;
						shot[i].lifespan++;

						if (shot[i].position.x > 800)
						{
							shot[i].active = false;
						}
						if (shot[i].active)
						{
							DrawCircleV(shot[i].position, shot[i].radius, YELLOW);
						
						}
						if (shot[i].lifespan >= 800)
						{
							shot[i].position = (Vector2){ boyPosition.x + 30,boyPosition.y + 30 };
							shot[i].speed = (Vector2){ 0,0 };
							shot[i].lifespan = 0;
							shot[i].active = false;
						}
					}
				}
			}

		EndDrawing();


	}

	UnloadMusicStream(gamesound);
	UnloadSound(gunsound);
	UnloadSound(losesound);
	UnloadSound(dead);
	CloseAudioDevice();
	CloseWindow ();

	return 0 ;
}
/*void AddScore(int score)
{
	FILE* FileScore = fopen("C:\\Users\\abdul\\OneDrive\\Desktop\\c\\Project1\\highscores.txt", "w");
	if (FileScore == NULL)
		perror("Error is: ");
	else {
		fputs(score, FileScore);
		fputs("\n", FileScore);
	}
	fclose(FileScore);

}*/