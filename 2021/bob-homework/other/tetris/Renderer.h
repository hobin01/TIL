#pragma once

const int g_nScreenWidth = 30;
const int g_nScreenHeight = 25;

class CRenderer
{
	char m_szScreenBuffer[g_nScreenHeight][g_nScreenWidth + 1];

public:
	void Clear(void);
	void Draw(int x, int y, const char* pszBuffer, int nBufferSize);
	void Render(void);
};

