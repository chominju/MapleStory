#pragma once
#include "GameObject.h"

class CSkill :
	public CGameObject
{
public:
	explicit CSkill();
	virtual ~CSkill();

public:
	// CGameObject��(��) ���� ��ӵ�
	virtual int Ready_GameObject() override;
	virtual int Update_GameObject() override;
	virtual void Late_Update_GameObject() override;
	virtual void Render_GameObject(HDC hDC) override;
	virtual void Release_GameObject() override;
	virtual void UpdateRect_GameObject() override;

	virtual void Play_Animation() override;

	int Get_Damage()
	{
		return m_damage;
	}

	int Get_hitNum()
	{
		return m_hitNum;
	}

	bool isHitMonsterNum()
	{
		if (m_hitMonsterNum > 0)
		{
			m_hitMonsterNum--;
			return true;
		}
		else
			return false;
	}

protected:
	int m_damage;				// ������
	int m_hitMonsterNum;		// �ִ� ���� ������ ���� ��
	int m_hitNum;				// Ÿ��
};