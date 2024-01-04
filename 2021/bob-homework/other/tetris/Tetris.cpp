#include "stdafx.h"
#include "Tetris.h"

CTetris::CTetris(void)
{
    m_Tetrimino.Reset(rand() % TETRIMINO_COUNT);
    m_Map.Clear();

    m_bGameOver = false;
}

CTetris::~CTetris(void)
{
}

bool CTetris::IsGameOver(void)
{
    return m_bGameOver;
}

void CTetris::Input(ST_KEY_STATE* pKeyState)
{
    char cKeyDown = 0;
    while (_kbhit())
        cKeyDown = _getch();

    if ('A' == cKeyDown || 'a' == cKeyDown)
        pKeyState->bLeftKeyDown = true;
    if ('D' == cKeyDown || 'd' == cKeyDown)
        pKeyState->bRightKeyDown = true;
    if ('W' == cKeyDown || 'w' == cKeyDown)
        pKeyState->bRotateKeyDown = true;
}

void CTetris::Update(ST_KEY_STATE stKeyState)
{
    CTetrimino preTetrimino = m_Tetrimino;
    if (stKeyState.bLeftKeyDown)
        m_Tetrimino.m_nPosX--;

    if (stKeyState.bRightKeyDown)
        m_Tetrimino.m_nPosX++;

    if (stKeyState.bRotateKeyDown)
        m_Tetrimino.m_nRotation = (m_Tetrimino.m_nRotation + 1) % 4;

    if (m_Map.IsCollide(&m_Tetrimino))
        m_Tetrimino = preTetrimino;

    m_Tetrimino.m_nPosY++;

    // 블럭이 바닥에 닿았다.
    if (m_Map.IsCollide(&m_Tetrimino))
    {
        m_Tetrimino.m_nPosY--;
        m_Map.Pile(&m_Tetrimino);
        m_Map.DeleteLine();
        m_Tetrimino.Reset(rand() & TETRIMINO_COUNT);

        // 게임오버 조건
        if (m_Map.IsCollide(&m_Tetrimino))
            m_bGameOver = true;
    }
}

void CTetris::Render(void)
{
    m_Render.Clear();
    m_Map.OnDraw(&m_Render);
    m_Tetrimino.OnDraw(&m_Render);
    m_Render.Render();
}