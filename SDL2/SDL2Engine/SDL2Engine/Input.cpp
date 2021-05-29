#pragma region project include
#include "Input.h"
#pragma endregion

// variable has to be initialized
#pragma region variable
bool CInput::s_keyWasDown[];
bool CInput::s_keyIsDown[];
bool CInput::s_mouseButtonWasDown[];
bool CInput::s_mouseButtonIsDown[];
SVector2 CInput::s_mousePosition;
#pragma endregion

#pragma region public function
// handle sdl events
void CInput::ParseEvent(SDL_Event _event)
{
	// if key is in range set to true or false depending on sdl event
	if (_event.key.keysym.scancode < 256)
		s_keyIsDown[_event.key.keysym.scancode] = _event.type == SDL_KEYDOWN;
}

// handle mouse events
void CInput::ParseMouseEvent(SDL_Event _event)
{
	// mouse moved
	if (_event.type == SDL_MOUSEMOTION)
	{
		// set mouse position
		s_mousePosition.X = _event.motion.x;
		s_mousePosition.Y = _event.motion.y;
	}

	// mouse clicked
	else
	{
		// set mouse button down
		s_mouseButtonIsDown[_event.button.button - 1] = _event.type == SDL_MOUSEBUTTONDOWN;
	}
}

// refresh state
void CInput::RefreshState()
{
	// set key was down
	for (int i = 0; i < 256; i++)
		s_keyWasDown[i] = s_keyIsDown[i];

	// set mouse button was down
	for (int i = 0; i < 3; i++)
		s_mouseButtonWasDown[i] = s_mouseButtonIsDown[i];
}

// get key pressed
bool CInput::GetKey(SDL_Scancode _key)
{
	return s_keyIsDown[_key];
}

// key pressed down this frame
bool CInput::GetKeyDown(SDL_Scancode _key)
{
	return s_keyIsDown[_key] && !s_keyWasDown[_key];
}

// key pressed up this frame
bool CInput::GetKeyUp(SDL_Scancode _key)
{
	return !s_keyIsDown[_key] && s_keyWasDown[_key];
}

// get mouse button pressed
bool CInput::GetMouseButton(int _number)
{
	return s_mouseButtonIsDown[_number];
}

// mouse button pressed down this frame
bool CInput::GetMouseButtonDown(int _number)
{
	return s_mouseButtonIsDown[_number] && !s_mouseButtonWasDown[_number];
}

// mouse button pressed up this frame
bool CInput::GetMouseButtonUp(int _number)
{
	return !s_mouseButtonIsDown[_number] && s_mouseButtonWasDown[_number];
}
#pragma endregion