#include "stdafx.h"
#include "Item.h"
#include "Scroll_Manager.h"

CItem::CItem()
{
	ZeroMemory(&m_itemInfo, sizeof(Item_Info));
	strcpy_s(m_itemInfo.itemName, "NONE");
}


CItem::~CItem()
{
}

int CItem::Ready_GameObject()
{
	return 0;
}

int CItem::Update_GameObject()
{
	if (m_isDead)
		return OBJ_DEAD;
	if (m_isFieldOut)
		return OBJ_FIELD_OUT;
	Play_Animation();
	return 0;
}

void CItem::Late_Update_GameObject()
{

}

void CItem::Render_GameObject(HDC hDC)
{
	UpdateRect_GameObject();
	Rectangle(hDC, m_rect.left, m_rect.top, m_rect.right, m_rect.bottom);


}

void CItem::Release_GameObject()
{
}

void CItem::UpdateRect_GameObject()
{
	m_rect.left = static_cast<LONG>(m_info.x - (m_info.sizeX / 2));
	m_rect.top = static_cast<LONG>(m_info.y - (m_info.sizeY / 2));
	m_rect.right = static_cast<LONG>(m_info.x + (m_info.sizeX / 2));
	m_rect.bottom = static_cast<LONG>(m_info.y + (m_info.sizeY / 2));
}
