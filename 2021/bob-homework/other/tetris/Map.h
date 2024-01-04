#pragma once

#include "RenderObject.h"
#include "Tetrimino.h"

const int g_nMapWidth = 16;
const int g_nMapHeight = 20;

class CMap : public CRenderObject
{
	char m_szMapData[g_nMapHeight][g_nMapWidth + 1];

public:
	void Clear(void);
	bool IsCollide(CTetrimino* pTetrimino);
	void Pile(CTetrimino* pTetrimino);
	void OnDraw(CRenderer* pRender);
	void DeleteLine(void);
};

