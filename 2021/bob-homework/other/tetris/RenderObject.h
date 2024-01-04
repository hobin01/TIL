#pragma once

#include "Renderer.h"

class CRenderObject
{
protected:
	int m_nPosX;
	int m_nPosY;

public:
	virtual void OnDraw(CRenderer* pRenderer) = 0;
};
