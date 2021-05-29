#pragma once

#pragma region system include
#include <list>
#pragma endregion

#pragma region project include
#include "Entity.h"
#pragma endregion

#pragma region forward decleration
class CMoveEntity;
#pragma endregion

#pragma region using
using namespace std;
#pragma endregion

/// <summary>
/// content management class
/// </summary>
class CContentManagement : public CEntity
{
public:
#pragma region constructor
	/// <summary>
	/// constructor
	/// </summary>
	CContentManagement() {}
#pragma endregion

#pragma region destructor
	/// <summary>
	/// destructor
	/// </summary>
	~CContentManagement();
#pragma endregion

#pragma region public override function
	/// <summary>
	/// update every frame
	/// </summary>
	/// <param name="_deltaSeconds">time since last frame</param>
	virtual void Update(float _deltaSeconds) override;

	/// <summary>
	/// render every frame
	/// </summary>
	virtual void Render() override;
#pragma endregion

#pragma region public inline function
	/// <summary>
	/// get scene object list
	/// </summary>
	/// <returns>list of scene objects</returns>
	inline list<CEntity*> GetSceneObjects() { return m_pSceneObjects; }

	/// <summary>
	/// add object to scene list
	/// </summary>
	/// <param name="_pObject">object</param>
	inline void AddSceneObject(CEntity* _pObject) { AddObject(_pObject, m_pSceneObjects); }

	/// <summary>
	/// get persistant object list
	/// </summary>
	/// <returns>list of persistant objects</returns>
	inline list<CEntity*> GetPersistantObjects() { return m_pPersistantObjects; }

	/// <summary>
	/// add object to persistant list
	/// </summary>
	/// <param name="_pObject">object</param>
	inline void AddPersistantObject(CEntity* _pObject) { AddObject(_pObject, m_pPersistantObjects); }

	/// <summary>
	/// get ui object list
	/// </summary>
	/// <returns>list of ui objects</returns>
	inline list<CEntity*> GetUIObjects() { return m_pUIObjects; }

	/// <summary>
	/// add object to ui list
	/// </summary>
	/// <param name="_pObject">object</param>
	inline void AddUIObject(CEntity* _pObject) { AddObject(_pObject, m_pUIObjects); }

	/// <summary>
	/// clean all scene objects
	/// </summary>
	inline void CleanSceneObjects() { CleanObjects(m_pSceneObjects); }

	/// <summary>
	/// clean all persistant objects
	/// </summary>
	inline void CleanPersistantObjects() { CleanObjects(m_pPersistantObjects); }

	/// <summary>
	/// clean all UI objects
	/// </summary>
	inline void CleanUIObjects() { CleanObjects(m_pUIObjects); }
#pragma endregion

#pragma region public function
	/// <summary>
	/// remove object from game
	/// </summary>
	/// <param name="_pObject">object</param>
	void RemoveObject(CEntity* _pObject);

	/// <summary>
	/// sort list by layer
	/// </summary>
	/// <param name="_pList">list</param>
	void SortList(list<CEntity*> &_pList);
#pragma endregion

private:
#pragma region private primitive variable
	/// <summary>
	/// time until collision check
	/// </summary>
	float m_collisionTime = 0.0f;

	/// <summary>
	/// current collision check time
	/// </summary>
	float m_currentColTime = 0.0f;
#pragma endregion

#pragma region private pointer
	/// <summary>
	/// list of all scene objects
	/// </summary>
	list<CEntity*> m_pSceneObjects;

	/// <summary>
	/// list of all persistant objects
	/// </summary>
	list<CEntity*> m_pPersistantObjects;

	/// <summary>
	/// list of all ui objects
	/// </summary>
	list<CEntity*> m_pUIObjects;

	/// <summary>
	/// list of all move objects
	/// </summary>
	list<CMoveEntity*> m_pMoveObjects;

	/// <summary>
	/// list of objects to remove
	/// </summary>
	list<CEntity*> m_pRemoveObjects;
#pragma endregion

#pragma region private function
	/// <summary>
	/// add object to list
	/// </summary>
	/// <param name="_pObject">object</param>
	/// <param name="_pList">list</param>
	void AddObject(CEntity* _pObject, list<CEntity*> &_pList);

	/// <summary>
	/// clean all objects in list
	/// </summary>
	/// <param name="_list">list</param>
	void CleanObjects(list<CEntity*> &_list);
#pragma endregion
};