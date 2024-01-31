
#include "main.h"
#include "input.h"
#include "cursor.h"

CursorMode Cursor::m_CursorMode = CURSOR_NORMAL;
D3DXVECTOR2 Cursor::m_Sens = D3DXVECTOR2(0.01f,0.005f);
POINT Cursor::m_CursorPos{};

void Cursor::Update()
{
    GetCursorPos(&m_CursorPos);

    switch (m_CursorMode)
    {
    case CURSOR_NORMAL:
        if (Input::GetKeyTrigger('P'))
        {
            ShowCursor(FALSE);
            m_CursorMode = CURSOR_FIRSTPERSON;
        }
        break;
    case CURSOR_FIRSTPERSON:         
            LimitCursor();
            if (Input::GetKeyTrigger('O'))
            {
            ShowCursor(TRUE);
            m_CursorMode = CURSOR_NORMAL;
            }
        break;
    }

    
}

void Cursor::LimitCursor()
{
    if (m_CursorPos.x > SCREEN_WIDTH / 2.0f + 314.0f)
        SetCursorPos(SCREEN_WIDTH / 2.0f - 314.0f, m_CursorPos.y);

    if (m_CursorPos.x < SCREEN_WIDTH / 2.0f - 314.0f)
        SetCursorPos(SCREEN_WIDTH / 2.0f + 314.0f, m_CursorPos.y);

    if (m_CursorPos.y > SCREEN_HEIGHT / 2.0f + 250.0f)
        SetCursorPos(m_CursorPos.x, SCREEN_HEIGHT / 2.0f + 250.0f);

    if (m_CursorPos.y < SCREEN_HEIGHT / 2.0f - 250.0f)
        SetCursorPos(m_CursorPos.x, SCREEN_HEIGHT / 2.0f - 250.0f);
}

D3DXVECTOR2 Cursor::GetCursorPosition()
{
    return D3DXVECTOR2((m_CursorPos.x - SCREEN_WIDTH / 2) * 0.01f, (-(m_CursorPos.y - SCREEN_HEIGHT / 2)) * 0.005f);
}