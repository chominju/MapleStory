#include "stdafx.h"
#include "Ui.h"

CUi::CUi()
{
}


CUi::~CUi()
{
}

int CUi::Ready_GameObject()
{

	return S_OK;
}

int CUi::Update_GameObject()
{
	return 0;
}

void CUi::Late_Update_GameObject()
{
}

void CUi::Render_GameObject(HDC hDC)
{

}

void CUi::Release_GameObject()
{
}

void CUi::UpdateRect_GameObject()
{
	m_rect.left = static_cast<LONG>(m_info.x - (m_info.sizeX / 2));
	m_rect.top = static_cast<LONG>(m_info.y - (m_info.sizeY / 2));
	m_rect.right = static_cast<LONG>(m_info.x + (m_info.sizeX / 2));
	m_rect.bottom = static_cast<LONG>(m_info.y + (m_info.sizeY / 2));
}
