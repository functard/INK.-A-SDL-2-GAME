#include "Collectable.h"
#include "Engine.h"
#include "ContentManagement.h"
#include "MoveEntity.h"

void GCollectable::Update(float _deltaSeconds)
{
	if (m_pColTarget)
	{
		

		// if collision target is enemy delete
		if (m_pColTarget->GetTag() == "Player")
			CTM->RemoveObject(this);


	}
}

void GCollectable::Render()
{
}
