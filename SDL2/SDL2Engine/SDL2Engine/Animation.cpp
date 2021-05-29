#pragma region project include
#include "Animation.h"  
#pragma endregion

#pragma region public function
// update every frame
void CAnimation::Update(float _deltaSeconds)
{
	// increase time
	m_time += _deltaSeconds;

	// if time higher than animation time / count
	if (m_time > m_animationTime / m_count)
	{
		// increase current frame number
		m_current++;

		// if current is higher than count reset
		if (m_current > m_count)
			m_current = 1;

		// reset time
		m_time = 0.0f;
	}
}

// get current position in texture
SVector2 CAnimation::GetCurrentTexturePosition()
{
	// return vector 2
	SVector2 v;

	// set x and y
	v.X = m_startPos.X + m_size.X * (m_current - 1);
	v.Y = m_startPos.Y;

	return v;
}
#pragma endregion