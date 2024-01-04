#pragma once

#include "RenderObject.h"

enum E_TETRIMINO_TYPE
{
	TETRIMINO_I = 0,
	TETRIMINO_O,
	TETRIMINO_J,
	TETRIMINO_L,
	TETRIMINO_S,
	TETRIMINO_Z,
	TETRIMINO_T,
	TETRIMINO_COUNT
};

class CTetrimino : public CRenderObject
{
	friend class CMap;
	friend class CTetris;

	char m_szBlock[4][4][4 + 1];
	int m_nRotation;

public:
	void Reset(int nType);
	void OnDraw(CRenderer* pRenderer);
};

