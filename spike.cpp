#include <iostream>
#include <windows.h>
using namespace std;

int spikeX = 18;
int spikeY = 4;

char spike[3][11] = {
                   {' ', ' ', ' ', '.', '-', '`', '-', '.', ' ', ' ', ' '},
                   {'.', '-', '=', '`', '=', ' ', '=', '`', '=', '-', '.'},
                   {'(', 'O', '_', 'o', '_', '-', '_', 'o', '_', 'O', ')'}};

void showSpike();
void gotoxy(int x, int y);
main()
{
    showSpike();
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

void gotoxy(int x, int y)
{
  COORD coordinates;
  coordinates.X = x;
  coordinates.Y = y;
  SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coordinates);
}

