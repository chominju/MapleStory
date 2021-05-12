#pragma once
class CGameObject;
class CCollision_Manager
{
private:
	CCollision_Manager();
	~CCollision_Manager();
public:
	static void Collision_Rect(list<CGameObject*>* listDest, list<CGameObject*>* listSrc);
	static void Collision_Portal(list<CGameObject*>* player, list<CGameObject*>* portal);

private:

};

