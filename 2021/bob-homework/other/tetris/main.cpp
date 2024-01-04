#include "stdafx.h"
#include "Tetris.h"

int main()
{
	CTetris tetris;

	int nFPS = 10;
	int nSleepTime = 1000 / nFPS;
	while (!tetris.IsGameOver())
	{
		ST_KEY_STATE stKeyState;
		stKeyState.Clear();

		tetris.Input(&stKeyState);
		tetris.Update(stKeyState);
		tetris.Render();

		Sleep(nSleepTime);
	}
	printf("Game over!!!!\n");
	return 0;
}
