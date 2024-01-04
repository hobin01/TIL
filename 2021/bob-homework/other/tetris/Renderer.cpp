#include "stdafx.h"
#include "Renderer.h"

void CRenderer::Clear(void)
{
	for (int y = 0; y < g_nScreenHeight; y++)
	{
		memset(m_szScreenBuffer[y], ' ', g_nScreenWidth);
		m_szScreenBuffer[y][g_nScreenWidth] = 0;
	}
}

void CRenderer::Draw(int x, int y, const char* pszBuffer, int nBufferSize)
{
	for (int i = 0; i < nBufferSize; i++)
	{
		int nPosX = x + i;
		if (' ' != pszBuffer[i])
			m_szScreenBuffer[y][nPosX] = pszBuffer[i];
	}
}

void CRenderer::Render(void)
{
	system("cls");

	for (int y = 0; y < g_nScreenHeight; y++)
		printf("%s\n", m_szScreenBuffer[y]);
}
