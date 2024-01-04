#include "stdafx.h"
#include "Tetrimino.h"

void CTetrimino::Reset(int nType)
{
	m_nPosX = 5;
	m_nPosY = 0;
	m_nRotation = 0;
	switch (nType)
	{
	case TETRIMINO_I:
		memcpy(m_szBlock[0][0], "I   ", 5);
		memcpy(m_szBlock[0][1], "I   ", 5);
		memcpy(m_szBlock[0][2], "I   ", 5);
		memcpy(m_szBlock[0][3], "I   ", 5);

		memcpy(m_szBlock[1][0], "IIII", 5);
		memcpy(m_szBlock[1][1], "    ", 5);
		memcpy(m_szBlock[1][2], "    ", 5);
		memcpy(m_szBlock[1][3], "    ", 5);

		memcpy(m_szBlock[2][0], "I   ", 5);
		memcpy(m_szBlock[2][1], "I   ", 5);
		memcpy(m_szBlock[2][2], "I   ", 5);
		memcpy(m_szBlock[2][3], "I   ", 5);

		memcpy(m_szBlock[3][0], "IIII", 5);
		memcpy(m_szBlock[3][1], "    ", 5);
		memcpy(m_szBlock[3][2], "    ", 5);
		memcpy(m_szBlock[3][3], "    ", 5);
		break;

	case TETRIMINO_O:
		memcpy(m_szBlock[0][0], "OO  ", 5);
		memcpy(m_szBlock[0][1], "OO  ", 5);
		memcpy(m_szBlock[0][2], "    ", 5);
		memcpy(m_szBlock[0][3], "    ", 5);

		memcpy(m_szBlock[1][0], "OO  ", 5);
		memcpy(m_szBlock[1][1], "OO  ", 5);
		memcpy(m_szBlock[1][2], "    ", 5);
		memcpy(m_szBlock[1][3], "    ", 5);

		memcpy(m_szBlock[2][0], "OO  ", 5);
		memcpy(m_szBlock[2][1], "OO  ", 5);
		memcpy(m_szBlock[2][2], "    ", 5);
		memcpy(m_szBlock[2][3], "    ", 5);

		memcpy(m_szBlock[3][0], "OO  ", 5);
		memcpy(m_szBlock[3][1], "OO  ", 5);
		memcpy(m_szBlock[3][2], "    ", 5);
		memcpy(m_szBlock[3][3], "    ", 5);
		break;

	case TETRIMINO_J:
		memcpy(m_szBlock[0][0], "JJJ ", 5);
		memcpy(m_szBlock[0][1], "  J ", 5);
		memcpy(m_szBlock[0][2], "    ", 5);
		memcpy(m_szBlock[0][3], "    ", 5);

		memcpy(m_szBlock[1][0], "JJ  ", 5);
		memcpy(m_szBlock[1][1], "J   ", 5);
		memcpy(m_szBlock[1][2], "J   ", 5);
		memcpy(m_szBlock[1][3], "    ", 5);

		memcpy(m_szBlock[2][0], "J   ", 5);
		memcpy(m_szBlock[2][1], "JJJ ", 5);
		memcpy(m_szBlock[2][2], "    ", 5);
		memcpy(m_szBlock[2][3], "    ", 5);

		memcpy(m_szBlock[3][0], " J  ", 5);
		memcpy(m_szBlock[3][1], " J  ", 5);
		memcpy(m_szBlock[3][2], "JJ  ", 5);
		memcpy(m_szBlock[3][3], "    ", 5);
		break;

	case TETRIMINO_L:
		memcpy(m_szBlock[0][0], "L   ", 5);
		memcpy(m_szBlock[0][1], "LLL ", 5);
		memcpy(m_szBlock[0][2], "    ", 5);
		memcpy(m_szBlock[0][3], "    ", 5);

		memcpy(m_szBlock[1][0], " L  ", 5);
		memcpy(m_szBlock[1][1], " L  ", 5);
		memcpy(m_szBlock[1][2], "LL  ", 5);
		memcpy(m_szBlock[1][3], "    ", 5);

		memcpy(m_szBlock[2][0], "LLL ", 5);
		memcpy(m_szBlock[2][1], "  L ", 5);
		memcpy(m_szBlock[2][2], "    ", 5);
		memcpy(m_szBlock[2][3], "    ", 5);

		memcpy(m_szBlock[3][0], "LL  ", 5);
		memcpy(m_szBlock[3][1], "L   ", 5);
		memcpy(m_szBlock[3][2], "L   ", 5);
		memcpy(m_szBlock[3][3], "    ", 5);
		break;

	case TETRIMINO_S:
		memcpy(m_szBlock[0][0], " SS ", 5);
		memcpy(m_szBlock[0][1], "SS  ", 5);
		memcpy(m_szBlock[0][2], "    ", 5);
		memcpy(m_szBlock[0][3], "    ", 5);

		memcpy(m_szBlock[1][0], "S   ", 5);
		memcpy(m_szBlock[1][1], "SS  ", 5);
		memcpy(m_szBlock[1][2], " S  ", 5);
		memcpy(m_szBlock[1][3], "    ", 5);

		memcpy(m_szBlock[2][0], " SS ", 5);
		memcpy(m_szBlock[2][1], "SS  ", 5);
		memcpy(m_szBlock[2][2], "    ", 5);
		memcpy(m_szBlock[2][3], "    ", 5);

		memcpy(m_szBlock[3][0], "S   ", 5);
		memcpy(m_szBlock[3][1], "SS  ", 5);
		memcpy(m_szBlock[3][2], " S  ", 5);
		memcpy(m_szBlock[3][3], "    ", 5);
		break;

	case TETRIMINO_Z:
		memcpy(m_szBlock[0][0], "ZZ  ", 5);
		memcpy(m_szBlock[0][1], " ZZ ", 5);
		memcpy(m_szBlock[0][2], "    ", 5);
		memcpy(m_szBlock[0][3], "    ", 5);

		memcpy(m_szBlock[1][0], " Z  ", 5);
		memcpy(m_szBlock[1][1], "ZZ  ", 5);
		memcpy(m_szBlock[1][2], "Z   ", 5);
		memcpy(m_szBlock[1][3], "    ", 5);

		memcpy(m_szBlock[2][0], "ZZ  ", 5);
		memcpy(m_szBlock[2][1], " ZZ ", 5);
		memcpy(m_szBlock[2][2], "    ", 5);
		memcpy(m_szBlock[2][3], "    ", 5);

		memcpy(m_szBlock[3][0], " Z  ", 5);
		memcpy(m_szBlock[3][1], "ZZ  ", 5);
		memcpy(m_szBlock[3][2], "Z   ", 5);
		memcpy(m_szBlock[3][3], "    ", 5);
		break;

	case TETRIMINO_T:
		memcpy(m_szBlock[0][0], " T  ", 5);
		memcpy(m_szBlock[0][1], "TTT ", 5);
		memcpy(m_szBlock[0][2], "    ", 5);
		memcpy(m_szBlock[0][3], "    ", 5);

		memcpy(m_szBlock[1][0], " T  ", 5);
		memcpy(m_szBlock[1][1], "TT  ", 5);
		memcpy(m_szBlock[1][2], " T  ", 5);
		memcpy(m_szBlock[1][3], "    ", 5);

		memcpy(m_szBlock[2][0], "TTT ", 5);
		memcpy(m_szBlock[2][1], " T  ", 5);
		memcpy(m_szBlock[2][2], "    ", 5);
		memcpy(m_szBlock[2][3], "    ", 5);

		memcpy(m_szBlock[3][0], "T   ", 5);
		memcpy(m_szBlock[3][1], "TT  ", 5);
		memcpy(m_szBlock[3][2], "T   ", 5);
		memcpy(m_szBlock[3][3], "    ", 5);
		break;
	}
}

void CTetrimino::OnDraw(CRenderer* pRenderer)
{
	pRenderer->Draw(m_nPosX, m_nPosY + 0, m_szBlock[m_nRotation][0], 4);
	pRenderer->Draw(m_nPosX, m_nPosY + 1, m_szBlock[m_nRotation][1], 4);
	pRenderer->Draw(m_nPosX, m_nPosY + 2, m_szBlock[m_nRotation][2], 4);
	pRenderer->Draw(m_nPosX, m_nPosY + 3, m_szBlock[m_nRotation][3], 4);
}