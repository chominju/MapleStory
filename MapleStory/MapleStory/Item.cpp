#include "stdafx.h"
#include "Item.h"
#include "Scroll_Manager.h"
#include "Player.h"
#include "GameObject_Manager.h"

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
	if(!strcmp(m_itemInfo.itemName, "NONE"))
		Rectangle(hDC, m_rect.left, m_rect.top, m_rect.right, m_rect.bottom);
	else
	{
		UpdateRect_GameObject();
		int scrollX = 0;
		int scrollY = 0;
		if (!m_isFieldOut)
		{
			scrollX = CScroll_Manager::Get_ScrollX();
			scrollY = CScroll_Manager::Get_ScrollY();
			GdiTransparentBlt(hDC, // �׸��� �����ϰ��� �ϴ� ���. 
				m_rect.left + scrollX,//��ġ x,y
				m_rect.top + scrollY,
				m_info.sizeX,// ũ�� xy
				m_info.sizeY,
				m_hdc,// ���� �� ���
				m_info.sizeX * m_selectImageX, m_info.sizeY * m_selectImageY,// �׸��� ���� ��ġ x,y
				m_info.sizeX,// �׸����� �ϴ� ������ ũ�� x,y
				m_info.sizeY,
				RGB(255, 0, 255));
		}
		else
		{
			if (dynamic_cast<CPlayer*>(CGameObject_Manager::Get_Instance()->GetPlayer())->Get_IsInventoryOpen())
			{
				GdiTransparentBlt(hDC, // �׸��� �����ϰ��� �ϴ� ���. 
					m_rect.left + scrollX,//��ġ x,y
					m_rect.top + scrollY,
					m_info.sizeX,// ũ�� xy
					m_info.sizeY,
					m_hdc,// ���� �� ���
					m_info.sizeX * m_selectImageX, m_info.sizeY * m_selectImageY,// �׸��� ���� ��ġ x,y
					m_info.sizeX,// �׸����� �ϴ� ������ ũ�� x,y
					m_info.sizeY,
					RGB(255, 0, 255));

				int temp = m_itemInfo.quantity;
				int num = 0;
				int temp3 = m_itemInfo.quantity;
				while (true)
				{
					num++;
					temp3 /= 10;
					if (temp3 == 0)
						break;
				}

				for (int i = 0; i < num; i++)
				{
					int temp2 = temp % 10;
					GdiTransparentBlt(hDC, // �׸��� �����ϰ��� �ϴ� ���. 
						m_rect.right - 5 - i * 7,//��ġ x,y+ i) * 7,//��ġ x,y
						m_rect.bottom - 10,
						7,// ũ�� xy
						10,
						m_State_Num_hdc,// ���� �� ���
						7 * temp2, 0,// �׸��� ���� ��ġ x,y
						7,// �׸����� �ϴ� ������ ũ�� x,y
						10,
						RGB(255, 0, 255));
					temp /= 10;
					if (temp == 0)
						break;
				}
			}

			RECT shop;
			shop.left = static_cast<LONG>(m_shopPos.x - (m_info.sizeX / 2));
			shop.top = static_cast<LONG>(m_shopPos.y - (m_info.sizeY / 2));
			shop.right = static_cast<LONG>(m_shopPos.x + (m_info.sizeX / 2));
			shop.bottom = static_cast<LONG>(m_shopPos.y + (m_info.sizeY / 2));

			if (dynamic_cast<CPlayer*>(CGameObject_Manager::Get_Instance()->GetPlayer())->Get_IsShopClick())
			{
				GdiTransparentBlt(hDC, // �׸��� �����ϰ��� �ϴ� ���. 
					shop.left + scrollX,//��ġ x,y
					shop.top + scrollY,
					m_info.sizeX,// ũ�� xy
					m_info.sizeY,
					m_hdc,// ���� �� ���
					m_info.sizeX * m_selectImageX, m_info.sizeY * m_selectImageY,// �׸��� ���� ��ġ x,y
					m_info.sizeX,// �׸����� �ϴ� ������ ũ�� x,y
					m_info.sizeY,
					RGB(255, 0, 255));

				int temp = m_itemInfo.quantity;
				int num = 0;
				int temp3 = m_itemInfo.quantity;
				while (true)
				{
					num++;
					temp3 /= 10;
					if (temp3 == 0)
						break;
				}

				for (int i = 0; i < num; i++)
				{
					int temp2 = temp % 10;
					GdiTransparentBlt(hDC, // �׸��� �����ϰ��� �ϴ� ���. 
						shop.right - 5 - i * 7,//��ġ x,y+ i) * 7,//��ġ x,y
						shop.bottom - 10,
						7,// ũ�� xy
						10,
						m_State_Num_hdc,// ���� �� ���
						7 * temp2, 0,// �׸��� ���� ��ġ x,y
						7,// �׸����� �ϴ� ������ ũ�� x,y
						10,
						RGB(255, 0, 255));
					temp /= 10;
					if (temp == 0)
						break;
				}
			}
		}
	}
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
