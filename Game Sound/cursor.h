#pragma once

enum CursorMode
{
    CURSOR_NORMAL,
    CURSOR_FIRSTPERSON
};

class Cursor
{
private:
    static CursorMode m_CursorMode;
    static D3DXVECTOR2 m_Sens;
    static POINT m_CursorPos;

    static void LimitCursor();
public:
    static void Update();
    static D3DXVECTOR2 GetCursorPosition();
};