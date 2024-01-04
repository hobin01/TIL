#include "stdafx.h"
#include "Map.h"
#include <vector>

void CMap::Clear(void)
{
	m_nPosX = 0;
	m_nPosY = 0;

	memcpy(m_szMapData[0], "**            **", 16 + 1);
	memcpy(m_szMapData[1], "**            **", 16 + 1);
	memcpy(m_szMapData[2], "**            **", 16 + 1);
	memcpy(m_szMapData[3], "**            **", 16 + 1);
	memcpy(m_szMapData[4], "**            **", 16 + 1);
	memcpy(m_szMapData[5], "**            **", 16 + 1);
	memcpy(m_szMapData[6], "**            **", 16 + 1);
	memcpy(m_szMapData[7], "**            **", 16 + 1);
	memcpy(m_szMapData[8], "**            **", 16 + 1);
	memcpy(m_szMapData[9], "**            **", 16 + 1);
	memcpy(m_szMapData[10], "**            **", 16 + 1);
	memcpy(m_szMapData[11], "**            **", 16 + 1);
	memcpy(m_szMapData[12], "**            **", 16 + 1);
	memcpy(m_szMapData[13], "**            **", 16 + 1);
	memcpy(m_szMapData[14], "**            **", 16 + 1);
	memcpy(m_szMapData[15], "**            **", 16 + 1);
	memcpy(m_szMapData[16], "**            **", 16 + 1);
	memcpy(m_szMapData[17], "**            **", 16 + 1);
	memcpy(m_szMapData[18], "****************", 16 + 1);
	memcpy(m_szMapData[19], "****************", 16 + 1);
}

bool CMap::IsCollide(CTetrimino* pTetrimino)
{
	for (int y = 0; y < 4; y++)
	{
		for (int x = 0; x < 4; x++)
		{
			int nPosX = pTetrimino->m_nPosX + x;
			int nPosY = pTetrimino->m_nPosY + y;
			if (m_szMapData[nPosY][nPosX] == ' ')
				continue;

			int nRotate = pTetrimino->m_nRotation;
			if (pTetrimino->m_szBlock[nRotate][y][x] == ' ')
				continue;

			return true;
		}
	}
	return false;
}

void CMap::Pile(CTetrimino* pTetrimino)
{
	for (int y = 0; y < 4; y++)
	{
		for (int x = 0; x < 4; x++)
		{
			int nPosX = pTetrimino->m_nPosX + x;
			int nPosY = pTetrimino->m_nPosY + y;
			int nRotate = pTetrimino->m_nRotation;
			if (pTetrimino->m_szBlock[nRotate][y][x] == ' ')
				continue;

			m_szMapData[nPosY][nPosX] = pTetrimino->m_szBlock[nRotate][y][x];
		}
	}
}

void CMap::OnDraw(CRenderer* pRender)
{
	for (int i = 0; i < g_nMapHeight; i++)
		pRender->Draw(m_nPosX, m_nPosY + i, m_szMapData[i], g_nMapWidth);
}

void CMap::DeleteLine(void)
{
	// 맵에서 다 찬 줄 제거 및 맵 업데이트

	std::vector<int>line;
	bool isFull = true;
	for (int i = g_nMapHeight - 3; i >= 0; i--) {

		isFull = true;

		for (int j = 0; j < g_nMapWidth; j++) {
			if (m_szMapData[i][j] == ' ') {
				isFull = false;
				break;
			}
		}

		if (isFull) {
			line.push_back(i);
		}
	}

	for (auto Lineidx : line) {
		if (Lineidx == 0) {
			memcpy(m_szMapData[0], "**            **", 16 + 1);
		}
		else {
			for (int idx = Lineidx; idx > 0; idx--) {
				memcpy(m_szMapData[idx], m_szMapData[idx - 1], 16 + 1);
			}
			memcpy(m_szMapData[0], "**            **", 16 + 1);
		}
	}

	// line 메모리 해제
	std::vector<int>().swap(line);

	return;
}