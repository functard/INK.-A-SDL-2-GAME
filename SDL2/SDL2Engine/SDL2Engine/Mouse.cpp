#pragma region project include
#include "Mouse.h"
#include "Input.h"
#pragma endregion

#pragma region public override function
// update every frame
void CMouse::Update(float _deltaSeconds)
{
	// set mouse position
	m_position.X = CInput::GetMousePosition().X - m_center.X * m_rect.w;
	m_position.Y = CInput::GetMousePosition().Y - m_center.Y * m_rect.h;

	// update parent
	CTexturedEntity::Update(_deltaSeconds);
}

// render every frame
void CMouse::Render()
{
	// if mouse visible render
	if (m_visible)
		CTexturedEntity::Render();
}
#pragma endregion

#pragma region public function
// set texture of mouse
void CMouse::SetTexture(CTexture* _pTexture)
{
	// if texture valid delete
	if (m_pTexture)
		delete m_pTexture;

	// set new texture
	m_pTexture = _pTexture;
}
#pragma endregion