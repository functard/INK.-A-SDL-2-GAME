#pragma region project include
#include "ContentManagement.h"
#include "MoveEntity.h"
#include "Macro.h"
#pragma endregion

#pragma region destructor
// destructor
CContentManagement::~CContentManagement()
{
	// as long as there is a scene object left remove first object in list
	while (m_pSceneObjects.size() > 0)
		m_pSceneObjects.pop_front();

	// as long as there is a persistant object left remove first object in list
	while (m_pPersistantObjects.size() > 0)
		m_pPersistantObjects.pop_front();

	// as long as there is a ui object left remove first object in list
	while (m_pUIObjects.size() > 0)
		m_pUIObjects.pop_front();
}
#pragma endregion

#pragma region public override function
// update every frame
void CContentManagement::Update(float _deltaSeconds)
{
	// remove objects in remove list
	while (m_pRemoveObjects.size() > 0)
	{
		// object to remove
		CEntity* pObject = m_pRemoveObjects.front();

		// remove object from scene list
		m_pSceneObjects.remove(pObject);

		// remove object from persistant list
 		m_pPersistantObjects.remove(pObject);

		// remove object from ui list
		m_pUIObjects.remove(pObject);

		// if object to remove is move object
		if (dynamic_cast<CMoveEntity*>(pObject))
		{
			// remove object from move object list
			m_pMoveObjects.remove((CMoveEntity*)pObject);

			// set collision timer
			m_collisionTime = COLLISION_CHECK_TIME / m_pMoveObjects.size();
		}

		// delete object
		m_pRemoveObjects.pop_front();
	}

	// update each scene object
	for (CEntity* pObj : m_pSceneObjects)
		pObj->Update(_deltaSeconds);

	// update each persistant object
	for (CEntity* pObj : m_pPersistantObjects)
		pObj->Update(_deltaSeconds);

	// update each ui object
	for (CEntity* pObj : m_pUIObjects)
		pObj->Update(_deltaSeconds);

	// decrease collision check time
	m_currentColTime -= _deltaSeconds;

	// if collision check time over 0 return
	if (m_currentColTime > 0 || m_pMoveObjects.size() == 0)
		return;

	// check collision of first move object in list
	m_pMoveObjects.front()->SetCollisionList();

	// set first element to last
	CMoveEntity* pMoveObj = m_pMoveObjects.front();
	m_pMoveObjects.remove(pMoveObj);
	m_pMoveObjects.push_back(pMoveObj);

	// reset collision timer
	m_currentColTime = m_collisionTime;
}

// render every frame
void CContentManagement::Render()
{
	// order of rendering is important
	// first list first rendered

	// render each scene object
	for (CEntity* pObj : m_pSceneObjects)
		pObj->Render();

	// render each persistant object
	for (CEntity* pObj : m_pPersistantObjects)
		pObj->Render();

	// render each ui object
	for (CEntity* pObj : m_pUIObjects)
		pObj->Render();
}
#pragma endregion

#pragma region public function
/// <summary>
/// remove object from game
/// </summary>
/// <param name="_pObject">object</param>
void CContentManagement::RemoveObject(CEntity* _pObject)
{
	// add object to remove list
	m_pRemoveObjects.push_back(_pObject);
}

/// <summary>
/// sort list by layer
/// </summary>
/// <param name="_pList">list</param>
void CContentManagement::SortList(list<CEntity*> &_pList)
{

}
#pragma endregion

#pragma region private function
// add object to list
void CContentManagement::AddObject(CEntity* _pObject, list<CEntity*> &_pList)
{
	// add object to list
	_pList.push_back(_pObject);

	// if object is a move object
	if (dynamic_cast<CMoveEntity*>(_pObject))
	{
		// add to move object list
		m_pMoveObjects.push_front((CMoveEntity*)_pObject);

		// set collision time
		m_collisionTime = COLLISION_CHECK_TIME / m_pMoveObjects.size();
	}

	// sort list
	SortList(_pList);
}

// clean all objects in list
void CContentManagement::CleanObjects(list<CEntity*>& _list)
{
	// add each object in list to objects to remove
	for (CEntity* pObj : _list)
		m_pRemoveObjects.push_front(pObj);
}
#pragma endregion