#include <iostream>
#include <conio.h>
#include <windows.h>

using namespace std;

int spikeX = 18;
int spikeY = 4;

char spike[3][11] = {
                   {' ', ' ', ' ', '.', '-', '`', '-', '.', ' ', ' ', ' '},
                   {'.', '-', '=', '`', '=', ' ', '=', '`', '=', '-', '.'},
                   {'(', 'O', '_', 'o', '_', '-', '_', 'o', '_', 'O', ')'}};

int steelThunderX = 4;
int steelThunderY = 4;

char steelThunder[3][7] = {
                       {' ', '_', '[', '`', ']', '_', ' '},
                       {'|', '_', '_', '_', '_', '_', '|'},
                       {'(', 'O', '_', 'o', '_', 'O', ')'}};
string steelThunderDirection = "Down";

int crusherX = 23;
int crusherY = 12;

char crusher[3][9] = {
                  {' ', ' ', '/', '"', '"', '"', '"', '\\', ' '},
                  {'/', '"', '"', '"', '"', '"', '"', '"', '\\'},
                  {'\\', '_', '@', '_', '@', '_', '@', '_', '/'}}; 
string crusherDirection = "Down";

int blazeX = 15;
int blazeY = 24;

char blaze[3][9] = {
                {' ', '_', '(', '`', '`', ')', '=', '>', ' '},
                {'/', '~', '~', '~', '~', '~', '~', '~', '\\'},
                {'\\', 'O', '.', 'O', '.', 'O', '.', 'O', '/'}};
string blazeDirection = "Right";

int bulletX[1000];
int bulletY[1000];
int bulletCount = 0;
int timer1 = 0;
int timer2 = 0;
int timer3 = 0;

int score = 0;
int crusher_Health = 7;
int steelThunder_Health = 5;
int blaze_Health = 9;
int spike_Health = 19;

int blazeBulletX = blazeX;
int blazeBulletY = blazeY - 1;

void welcomeScreen();
int menu();
void keys();
void showMaze();

void showSpike();
void eraseSpike();
void moveSpikeLeft();
void moveSpikeRight();
void moveSpikeUp();
void moveSpikeDown();

void showBlaze();
void eraseBlaze();
void moveBlaze();

void showSteelThunder();
void eraseSteelThunder();
void moveSteelThunder();

void showCrusher();
void eraseCrusher();
void moveCrusher();

void generateBullet();
void moveBullet();
void displayBullet(int x, int y);
void eraseBullet(int x, int y);
void removeBulletFromArray(int idx);
void blazeBullet();

void bulletCollisionWithBlaze();
void bulletCollisionWithSteelThunder();
void bulletCollisionWithCrusher();

void crusherCollisionWithSpike();
void steelThunderCollisionWithSpike();
void blazeCollisionWithSpike();
void blazeBulletCollisionWithSpike();

void addScore();
void crusherHealth();
void steelThunderHealth();
void blazeHealth();
void spikeHealth();
void displayScoreAndHealth();

void winning();
void losing();
void clearScreen();
void gotoxy(int x, int y);
char getCharAtxy(short int x, short int y);

main()
{

  while (true)
  {
    system("cls");
    welcomeScreen();
    int choice = menu();
    if (choice == 1)
    {
      bool game = true;
      system("cls");
      showMaze();
      showSpike();

      while (game == true)
      {
        displayScoreAndHealth();
        if (GetAsyncKeyState(VK_LEFT))
        {
          moveSpikeLeft();
        }
        else if (GetAsyncKeyState(VK_RIGHT))
        {
          moveSpikeRight();
        }
        else if (GetAsyncKeyState(VK_UP))
        {
          moveSpikeUp();
        }
        else if (GetAsyncKeyState(VK_DOWN))
        {
          moveSpikeDown();
        }
        else if (GetAsyncKeyState(VK_ESCAPE))
        {
          game = false;
        }
        else if (GetAsyncKeyState(VK_SPACE))
        {
          generateBullet();
        }
        if (crusher_Health != 0 && timer1 == 3)
        {
          showCrusher();
          moveCrusher();
          timer1 = 0;
        }
        if (steelThunder_Health != 0 && timer2 == 3)
        {
          showSteelThunder();
          moveSteelThunder();
          timer2 = 0;
        }
        if (blaze_Health != 0 && timer3 == 3)
        {
          showBlaze();
          moveBlaze();
          blazeBullet();
          blazeBullet();

          timer3 = 0;
        }
        if (crusher_Health == 0)
        {
          eraseCrusher();
        }
        if (steelThunder_Health == 0)
        {
          eraseSteelThunder();
        }
        if (blaze_Health == 0)
        {
          eraseBlaze();
          eraseBullet(blazeBulletX, blazeBulletY);
        }
        if (crusher_Health == 0 && blaze_Health == 0 && steelThunder_Health == 0 && spike_Health > 0)
        {
          system("cls");
          winning();
          game = false;
        }
        if (spike_Health == 0)
        {
          system("cls");
          losing();
          game = false;
        }
        moveBullet();
        bulletCollisionWithBlaze();
        bulletCollisionWithSteelThunder();
        bulletCollisionWithCrusher();
        crusherCollisionWithSpike();
        blazeCollisionWithSpike();
        steelThunderCollisionWithSpike();
        blazeBulletCollisionWithSpike();
        timer1++;
        timer2++;
        timer3++;
        Sleep(90);
      }
    }
    if (choice == 2)
    {
      clearScreen();
      keys();
      clearScreen();
    }
    if (choice == 3)
    {
      clearScreen();
      cout << "THANK YOU FOR PLAYING THIS GAME!!!" << endl;
      break;
    }
  }
}

void welcomeScreen()
{
  cout << " _                   _                                                                    " << endl;
  cout << "| |_ _ __ _   _  ___| | _____             __ _       _     _                              " << endl;
  cout << "| __| '__| | | |/ __| |/ / __|           / _(_)     | |   | |                             " << endl;
  cout << "| |_| |  | |_| | (__|   <\\__ \\          | |_ _  __ _| |__ | |_                          " << endl;
  cout << " \\__|_|   \\__,_|\\___|_|\\_\\___/          | |_| |/ _` | '_ \\| __|       .--._____,    " << endl;
  cout << "                                        | | | | (_| | | | | |_     .-='=='==-, "
          "         "
       << endl;
  cout << "                                        |_| |_|\\__, |_| |_|\\__|   (O_o_o_o_o_O)         " << endl;
  cout << "                                                __/ |                                     " << endl;
  cout << "                                               |___/                                      " << endl;
}

void winning()
{
  cout << endl
       << endl
       << endl;
  cout << "                  ___________________ " << endl;
  cout << "                 |   YOU WON!!       |" << endl;
  cout << "                 ---------------------" << endl;
  cout << endl
       << endl;
}

void losing()
{
  cout << endl
       << endl
       << endl;
  cout << "                  ___________________ " << endl;
  cout << "                 |   YOU LOSE!!      |" << endl;
  cout << "                 ---------------------" << endl;
  cout << endl
       << endl;
}

int menu()
{
  int option;
  cout << "MENU" << endl;
  cout << "____________________" << endl;
  cout << "1. START" << endl;
  cout << "2. KEYS" << endl;
  cout << "3. Exit" << endl;
  cout << endl;
  cout << "Enter your Choice: " << endl;
  cin >> option;
  return option;
}

void keys()
{
  cout << " KEYS" << endl;
  cout << " _____________________" << endl;
  cout << "  UP                Go Up" << endl;
  cout << "  DOWN              Go Down" << endl;
  cout << "  RIGHT             Go Right" << endl;
  cout << "  LEFT              Go Left" << endl;
  cout << "  SPACE             Fire Bullets" << endl;
  cout << "  Esc.              Back to Main Menu" << endl;
}

void showMaze()
{
  cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << endl;
  cout << "?                                                                                                                                                            ?" << endl;
  cout << "?    _____                                                                                                                                         _____     ?" << endl;
  cout << "?   |     |                                                                                                                                       |     |    ?" << endl;
  cout << "?                                                                                                                                                            ?" << endl;
  cout << "?                                                                                                                                                            ?" << endl;
  cout << "?                                                                                                                                                            ?" << endl;
  cout << "?                                                                                                                                                            ?" << endl;
  cout << "?                                                                                                                                                            ?" << endl;
  cout << "?                                                                                                                                                            ?" << endl;
  cout << "?                                                                                                                                                            ?" << endl;
  cout << "?                                                                                                                                                            ?" << endl;
  cout << "?                                                                                                                                                            ?" << endl;
  cout << "?                                                                                                                                                            ?" << endl;
  cout << "?                                                                                                                                                            ?" << endl;
  cout << "?                                                                                                                                                            ?" << endl;
  cout << "?                                                                                                                                                            ?" << endl;
  cout << "?                                                                                                                                                            ?" << endl;
  cout << "?                                                                                                                                                            ?" << endl;
  cout << "?                                                                                                                                                            ?" << endl;
  cout << "?                                                                                                                                                            ?" << endl;
  cout << "?                                                                                                                                                            ?" << endl;
  cout << "?                                                                                                                                                            ?" << endl;
  cout << "?                                                                                                                                                            ?" << endl;
  cout << "?   |_____|                                                                                                                                       |_____|    ?" << endl;
  cout << "?                                                                                                                                                            ?" << endl;
  cout << "?                                                                                                                                                            ?" << endl;
  cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << endl;
}

void showSpike()
{

  gotoxy(spikeX, spikeY);
  for (int i = 0; i < 3; i++)
  {
    for (int j = 0; j < 11; j++)
    {
      cout << spike[i][j];
    }
    gotoxy(spikeX, spikeY+1);
  }

}
void eraseSpike()
{
  gotoxy(spikeX, spikeY);
  for (int i = 0; i < 3; i++)
  {
    for (int j = 0; j < 11; j++)
    {
      cout << " ";
    }
    gotoxy(spikeX, spikeY+1);
  }
}

void moveSpikeLeft()
{
  char nextlocation1 = getCharAtxy(spikeX - 1, spikeY);
  char nextlocation2 = getCharAtxy(spikeX - 1, spikeY+1);
  char nextlocation3 = getCharAtxy(spikeX - 1, spikeY+2);
  if (nextlocation1 == ' ' && nextlocation2 == ' ' && nextlocation3 == ' ')
  {
    eraseSpike();
    spikeX = spikeX - 1;
    showSpike();
  }
}

void moveSpikeRight()
{
  char nextlocation1 = getCharAtxy(spikeX + 11, spikeY);
  char nextlocation2 = getCharAtxy(spikeX + 11, spikeY+1);
  char nextlocation3 = getCharAtxy(spikeX + 11, spikeY+2);
  if (nextlocation1 == ' ' && nextlocation2 == ' ' && nextlocation3 == ' ')
  {
    eraseSpike();
    spikeX = spikeX + 1;
    showSpike();
  }
}

void moveSpikeUp()
{
  char nextlocation1 = getCharAtxy(spikeX, spikeY - 1);
  char nextlocation2 = getCharAtxy(spikeX + 1, spikeY - 1);
  char nextlocation3 = getCharAtxy(spikeX + 2, spikeY - 1);
  char nextlocation4 = getCharAtxy(spikeX + 3, spikeY - 1);
  char nextlocation5 = getCharAtxy(spikeX + 4, spikeY - 1);
  char nextlocation6 = getCharAtxy(spikeX + 5, spikeY - 1);
  char nextlocation7 = getCharAtxy(spikeX + 6, spikeY - 1);
  char nextlocation8 = getCharAtxy(spikeX + 7, spikeY - 1);
  char nextlocation9 = getCharAtxy(spikeX + 8, spikeY - 1);
  char nextlocation10 = getCharAtxy(spikeX + 9, spikeY - 1);
  char nextlocation11 = getCharAtxy(spikeX + 10, spikeY - 1);
  if (nextlocation1 == ' ' && nextlocation2 == ' ' && nextlocation3 == ' ' && nextlocation4 == ' ' && nextlocation5 == ' ' && nextlocation6 == ' ' && nextlocation7 == ' ' && nextlocation8 == ' ' && nextlocation9 == ' ' && nextlocation10 == ' ' && nextlocation11 == ' ' )
  {
    eraseSpike();
    spikeY = spikeY - 1;
    showSpike();
  }
}

void moveSpikeDown()
{
  char nextlocation1 = getCharAtxy(spikeX, spikeY + 3);
  char nextlocation2 = getCharAtxy(spikeX + 1, spikeY + 3);
  char nextlocation3 = getCharAtxy(spikeX + 2, spikeY + 3);
  char nextlocation4 = getCharAtxy(spikeX + 3, spikeY + 3);
  char nextlocation5 = getCharAtxy(spikeX + 4, spikeY + 3);
  char nextlocation6 = getCharAtxy(spikeX + 5, spikeY + 3);
  char nextlocation7 = getCharAtxy(spikeX + 6, spikeY + 3);
  char nextlocation8 = getCharAtxy(spikeX + 7, spikeY + 3);
  char nextlocation9 = getCharAtxy(spikeX + 8, spikeY + 3);
  char nextlocation10 = getCharAtxy(spikeX + 9, spikeY + 3);
  char nextlocation11 = getCharAtxy(spikeX + 10, spikeY + 3);
  if (nextlocation1 == ' ' && nextlocation2 == ' ' && nextlocation3 == ' ' && nextlocation4 == ' ' && nextlocation5 == ' ' && nextlocation6 == ' ' && nextlocation7 == ' ' && nextlocation8 == ' ' && nextlocation9 == ' ' && nextlocation10 == ' ' && nextlocation11 == ' ' )
  {
    eraseSpike();
    spikeY = spikeY + 1;
    showSpike();
  }
}

void generateBullet()
{
  bulletX[bulletCount] = spikeX + 12;
  bulletY[bulletCount] = spikeY;
  gotoxy(spikeX + 14, spikeY);
  cout << ".";
  bulletCount++;
}

void moveBullet()
{
  for (int j = 0; j < bulletCount; j++)
  {
    char nextLocation = getCharAtxy(bulletX[j] + 1, bulletY[j] + 1);
    if (nextLocation != ' ' || nextLocation == '|')
    {
      eraseBullet(bulletX[j], bulletY[j]);
      removeBulletFromArray(j);
    }
    else if (nextLocation == ' ')
    {
      eraseBullet(bulletX[j], bulletY[j]);
      bulletX[j] = bulletX[j] + 1;
      displayBullet(bulletX[j], bulletY[j]);
    }
  }
}

void displayBullet(int x, int y)
{
  gotoxy(x, y);
  cout << ".";
}

void eraseBullet(int x, int y)
{
  gotoxy(x, y);
  cout << " ";
}

void blazeBullet()
{
  displayBullet(blazeBulletX, blazeBulletY);
  char next = getCharAtxy(blazeBulletX, blazeBulletY - 1);
  if (next == ' ')
  {
    eraseBullet(blazeBulletX, blazeBulletY);
    blazeBulletY = blazeBulletY - 1;
    displayBullet(blazeBulletX, blazeBulletY);
  }
  if (next != ' ')
  {
    eraseBullet(blazeBulletX, blazeBulletY);
    blazeBulletX = blazeX;
    blazeBulletY = blazeY;
    displayBullet(blazeBulletX, blazeBulletY);
  }
}

void removeBulletFromArray(int idx)
{
  for (int x = idx; x < bulletCount - 1; x++)
  {
    bulletX[x] = bulletX[x + 1];
    bulletY[x] = bulletY[x + 1];
  }
  bulletCount--;
}

void showCrusher()
{
  gotoxy(crusherX, crusherY);
  for (int i = 0; i < 3; i++)
  {
    for(int j = 0; j < 9; j++)
    {
      cout << crusher[i][j];
    }
    gotoxy(crusherX, crusherY + 1);
  }
}

void eraseCrusher()
{
 gotoxy(crusherX, crusherY);
  for (int i = 0; i < 3; i++)
  {
    for(int j = 0; j < 9; j++)
    {
      cout << " ";
    }
    gotoxy(crusherX, crusherY + 1);
  }
}

void moveCrusher()
{
  if (crusherDirection == "Down")
  {
    char next = getCharAtxy(crusherX, crusherY + 3);
    if (next == ' ')
    {
      eraseCrusher();
      crusherY = crusherY + 1;
      showCrusher();
    }
    else
    {
      crusherDirection = "Up";
    }
  }
  if (crusherDirection == "Up")
  {
    char next = getCharAtxy(crusherX, crusherY - 1);
    if (next == ' ')
    {
      eraseCrusher();
      crusherY = crusherY - 1;
      showCrusher();
    }
    else
    {
      crusherDirection = "Down";
    }
  }
}

void showSteelThunder()
{
  gotoxy(steelThunderX, steelThunderY);
  for (int i = 0; i < 3; i++)
  {
    for (int j = 0; j < 7; j++)
    {
      cout << steelThunder[i][j];
    }
    gotoxy(steelThunderX, steelThunderY+1);
  }
}

void eraseSteelThunder()
{
  gotoxy(steelThunderX, steelThunderY);
  for (int i = 0; i < 3; i++)
  {
    for (int j = 0; j < 7; j++)
    {
      cout << " ";
    }
    gotoxy(steelThunderX, steelThunderY+1);
  }

}

void moveSteelThunder()
{
  if (steelThunderDirection == "Down")
  {
    char next = getCharAtxy(steelThunderX, steelThunderY + 3);
    if (next == ' ')
    {
      eraseSteelThunder();
      steelThunderY = steelThunderY + 1;
      showSteelThunder();
    }
    if (next == '|')
    {
      eraseSteelThunder();
      steelThunderX = 146;
      steelThunderY = 21;
      steelThunderDirection = "Up";
    }
  }
  if (steelThunderDirection == "Up")
  {
    char next = getCharAtxy(steelThunderX, steelThunderY - 1);
    if (next == ' ')
    {
      eraseSteelThunder();
      steelThunderY = steelThunderY - 1;
      showSteelThunder();
    }
    if (next == '|')
    {
      eraseSteelThunder();
      steelThunderX = 4;
      steelThunderY = 4;
      steelThunderDirection = "Down";
    }
  }
}

void showBlaze()
{
  gotoxy(blazeX, blazeY);
  for (int i = 0; i < 3; i++)
  {
    for (int j = 0; j < 9; j++)
    {
      cout << blaze[i][j];
    }
    gotoxy(blazeX, blazeY+1);
  }
}

void eraseBlaze()
{
  gotoxy(blazeX, blazeY);
  for (int i = 0; i < 3; i++)
  {
    for (int j = 0; j < 9; j++)
    {
      cout << " ";
    }
    gotoxy(blazeX, blazeY+1);
  }

}

void moveBlaze()
{

  if (blazeDirection == "Right")
  {
    char next = getCharAtxy(blazeX + 9, blazeY);
    if (next == ' ')
    {
      eraseBlaze();
      blazeX = blazeX + 1;
      showBlaze();
    }
    else
    {
      blazeDirection = "Left";
    }
  }
  if (blazeDirection == "Left")
  {
    char next = getCharAtxy(blazeX - 1, blazeY);
    if (next == ' ')
    {
      eraseBlaze();
      blazeX = blazeX - 1;
      showBlaze();
    }
    else
    {
      blazeDirection = "Right";
    }
  }
}

void bulletCollisionWithBlaze()
{
  for (int x = 0; x < bulletCount; x++)
  {
    if (bulletX[x] + 1 == blazeX && (bulletY[x] == blazeY || bulletY[x] == blazeY + 1 || bulletY[x] == blazeY + 2))
    {
      if (blaze_Health > 0)
      {
        addScore();
        blazeHealth();
        eraseBullet(bulletX[x], bulletY[x]);
        removeBulletFromArray(x);
      }
    }
  }
}

void bulletCollisionWithSteelThunder()
{
  for (int x = 0; x < bulletCount; x++)
  {
    if (bulletX[x] + 1 == steelThunderX && (bulletY[x] == steelThunderY || bulletY[x] == steelThunderY + 1 || bulletY[x] == steelThunderY + 2))
    {
      addScore();
      steelThunderHealth();
      eraseBullet(bulletX[x], bulletY[x]);
      removeBulletFromArray(x);
    }
  }
}

void bulletCollisionWithCrusher()
{
  for (int x = 0; x < bulletCount; x++)
  {
    if (bulletX[x] + 1 == crusherX && (bulletY[x] == crusherY || bulletY[x] == crusherY + 1 || bulletY[x] == crusherY + 2))
    {
      addScore();
      crusherHealth();
      eraseBullet(bulletX[x], bulletY[x]);
      removeBulletFromArray(x);
    }
  }
}

void crusherCollisionWithSpike()
{
  if ((spikeX == crusherX || spikeX + 11 == crusherX || crusherX + 9 == spikeX || crusherX + 9 == spikeX + 11) && (spikeY == crusherY || spikeY == crusherY + 1 || spikeY == crusherY + 2 || spikeY + 1 == crusherY || spikeY + 2 == crusherY))
  {
    spikeHealth();
  }
}

void steelThunderCollisionWithSpike()
{
  if ((spikeX == steelThunderX || spikeX + 11 == steelThunderX || steelThunderX + 7 == spikeX || spikeX + 11 == steelThunderX + 7) && (spikeY == steelThunderY || spikeY == steelThunderY + 1 || spikeY == steelThunderY + 2 || spikeY + 1 == steelThunderY || spikeY + 2 == steelThunderY))
  {
    spikeHealth();
  }
}

void blazeCollisionWithSpike()
{
  if ((spikeX == blazeX || spikeX + 11 == blazeX || blazeX + 9 == spikeX || spikeX + 11 == blazeX + 9) && (spikeY == blazeY || spikeY + 1 == blazeY || spikeY + 2 == blazeY || spikeY == blazeY + 1 || spikeY == blazeY + 2))
  {
    spikeHealth();
  }
}

void blazeBulletCollisionWithSpike()
{
  if ((blazeBulletX == spikeX || blazeBulletX == spikeX + 1 || blazeBulletX == spikeX + 2 || blazeBulletX == spikeX + 3 || blazeBulletX == spikeX + 4 || blazeBulletX == spikeX + 5 || blazeBulletX == spikeX + 6 || blazeBulletX == spikeX + 7 || blazeBulletX == spikeX + 8 || blazeBulletX == spikeX + 9 || blazeBulletX == spikeX + 10) && blazeBulletY == spikeY + 3)
  {
    eraseBullet(blazeBulletX, blazeBulletY);
    spikeHealth();
  }
}

void addScore()
{
  score = score + 1;
}

void crusherHealth()
{
  if (crusher_Health > 0)
  {
    crusher_Health--;
  }
}

void steelThunderHealth()
{
  if (steelThunder_Health > 0)
  {
    steelThunder_Health = steelThunder_Health - 1;
  }
}

void blazeHealth()
{
  if (blaze_Health > 0)
  {
    blaze_Health = blaze_Health - 1;
  }
}

void spikeHealth()
{
  if (spike_Health > 0)
  {
    spike_Health--;
  }
}

void displayScoreAndHealth()
{
  gotoxy(10, 30);
  cout << "Score = " << score << " ";
  gotoxy(10, 31);
  cout << "Spike Health = " << spike_Health << " ";
  gotoxy(10, 32);
  cout << "Crusher Health = " << crusher_Health << " ";
  gotoxy(10, 33);
  cout << "Steel Thunder Health = " << steelThunder_Health << " ";
  gotoxy(10, 34);
  cout << "Blaze Health = " << blaze_Health << " ";
}

void clearScreen()
{
  cout << endl;
  cout << "Press Any key to continue: ";
  getch();
  system("cls");
}

void gotoxy(int x, int y)
{
  COORD coordinates;
  coordinates.X = x;
  coordinates.Y = y;
  SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coordinates);
}

char getCharAtxy(short int x, short int y)
{
  CHAR_INFO ci;
  COORD xy = {0, 0};
  SMALL_RECT rect = {x, y, x, y};
  COORD coordBufSize;
  coordBufSize.X = 1;
  coordBufSize.Y = 1;
  return ReadConsoleOutput(GetStdHandle(STD_OUTPUT_HANDLE), &ci, coordBufSize, xy, &rect) ? ci.Char.AsciiChar : ' ';
}