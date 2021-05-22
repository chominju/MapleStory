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
	if(!strcmp(m_itemInfo.itemName, "NONE"))																								// 이름 없음(걍 네모칸)
		Rectangle(hDC, m_rect.left, m_rect.top, m_rect.right, m_rect.bottom);
	else
	{
		UpdateRect_GameObject();
		int scrollX = 0;
		int scrollY = 0;
		if (!m_isFieldOut)																													// 필드에 있을 떄
		{
			scrollX = CScroll_Manager::Get_ScrollX();
			scrollY = CScroll_Manager::Get_ScrollY();
			GdiTransparentBlt(hDC, // 그림을 복사하고자 하는 대상. 
				m_rect.left + scrollX,//위치 x,y
				m_rect.top + scrollY,
				m_info.sizeX,// 크기 xy
				m_info.sizeY,
				m_hdc,// 복사 할 대상
				m_info.sizeX * m_selectImageX, m_info.sizeY * m_selectImageY,// 그림의 시작 위치 x,y
				m_info.sizeX,// 그리고자 하는 영역의 크기 x,y
				m_info.sizeY,
				RGB(255, 0, 255));
		}
		else
		{
			if (m_itemPlace != Item_Place::EQUIPMENT_ITEM)
			{
				if (dynamic_cast<CPlayer*>(CGameObject_Manager::Get_Instance()->GetPlayer())->Get_IsInventoryOpen())
				{
					if (m_itemPlace == Item_Place::INVENTORY_ITEM)
					{
						GdiTransparentBlt(hDC, // 그림을 복사하고자 하는 대상. 
							m_rect.left + scrollX,//위치 x,y
							m_rect.top + scrollY,
							m_info.sizeX,// 크기 xy
							m_info.sizeY,
							m_hdc,// 복사 할 대상
							m_info.sizeX * m_selectImageX, m_info.sizeY * m_selectImageY,// 그림의 시작 위치 x,y
							m_info.sizeX,// 그리고자 하는 영역의 크기 x,y
							m_info.sizeY,
							RGB(255, 0, 255));

						if (m_itemInfo.quantity != 1)
						{
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
								GdiTransparentBlt(hDC, // 그림을 복사하고자 하는 대상. 
									m_rect.right - 5 - i * 7,//위치 x,y+ i) * 7,//위치 x,y
									m_rect.bottom - 10,
									7,// 크기 xy
									10,
									m_State_Num_hdc,// 복사 할 대상
									7 * temp2, 0,// 그림의 시작 위치 x,y
									7,// 그리고자 하는 영역의 크기 x,y
									10,
									RGB(255, 0, 255));
								temp /= 10;
								if (temp == 0)
									break;
							}
						}
					}
				}


				m_shopRect.left = static_cast<LONG>(m_shopPos.x - (m_info.sizeX / 2));
				m_shopRect.top = static_cast<LONG>(m_shopPos.y - (m_info.sizeY / 2));
				m_shopRect.right = static_cast<LONG>(m_shopPos.x + (m_info.sizeX / 2));
				m_shopRect.bottom = static_cast<LONG>(m_shopPos.y + (m_info.sizeY / 2));

				if (dynamic_cast<CPlayer*>(CGameObject_Manager::Get_Instance()->GetPlayer())->Get_IsShopClick())
				{
					GdiTransparentBlt(hDC, // 그림을 복사하고자 하는 대상. 
						m_shopRect.left + scrollX,//위치 x,y
						m_shopRect.top + scrollY,
						m_info.sizeX,// 크기 xy
						m_info.sizeY,
						m_hdc,// 복사 할 대상
						m_info.sizeX * m_selectImageX, m_info.sizeY * m_selectImageY,// 그림의 시작 위치 x,y
						m_info.sizeX,// 그리고자 하는 영역의 크기 x,y
						m_info.sizeY,
						RGB(255, 0, 255));

					int temp;
					int num;
					int temp3;
					if (m_itemPlace == Item_Place::INVENTORY_ITEM)
					{
						if (m_itemInfo.quantity != 1)
						{
							temp = m_itemInfo.quantity;
							num = 0;
							temp3 = m_itemInfo.quantity;
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
								GdiTransparentBlt(hDC, // 그림을 복사하고자 하는 대상. 
									m_shopRect.right - 5 - i * 7,//위치 x,y+ i) * 7,//위치 x,y
									m_shopRect.bottom - 10,
									7,// 크기 xy
									10,
									m_State_Num_hdc,// 복사 할 대상
									7 * temp2, 0,// 그림의 시작 위치 x,y
									7,// 그리고자 하는 영역의 크기 x,y
									10,
									RGB(255, 0, 255));
								temp /= 10;
								if (temp == 0)
									break;
							}
						}

						temp = m_itemInfo.sellMoney;
						num = 0;
						temp3 = m_itemInfo.sellMoney;
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
							GdiTransparentBlt(hDC, // 그림을 복사하고자 하는 대상. 
								m_shopRect.right + 100 - 5 - i * 7,//위치 x,y+ i) * 7,//위치 x,y
								m_shopRect.bottom - 10,
								7,// 크기 xy
								10,
								m_State_Num_hdc,// 복사 할 대상
								7 * temp2, 0,// 그림의 시작 위치 x,y
								7,// 그리고자 하는 영역의 크기 x,y
								10,
								RGB(255, 0, 255));
							temp /= 10;
							if (temp == 0)
								break;
						}
					}
					else if (m_itemPlace == Item_Place::SHOP_ITEM)
					{
						temp = m_itemInfo.buyMoney;
						num = 0;
						temp3 = m_itemInfo.buyMoney;
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
							GdiTransparentBlt(hDC, // 그림을 복사하고자 하는 대상. 
								m_shopRect.right + 100 - 5 - i * 7,//위치 x,y+ i) * 7,//위치 x,y
								m_shopRect.bottom - 10,
								7,// 크기 xy
								10,
								m_State_Num_hdc,// 복사 할 대상
								7 * temp2, 0,// 그림의 시작 위치 x,y
								7,// 그리고자 하는 영역의 크기 x,y
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
