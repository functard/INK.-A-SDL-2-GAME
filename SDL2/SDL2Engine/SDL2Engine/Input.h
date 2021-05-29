#pragma once

#pragma region sdl include
#include <SDL.h>
#pragma endregion

#pragma region project include
#include "Vector2.h"
#pragma endregion

/// <summary>
/// input handling class
/// </summary>
class CInput
{
public:
#pragma region public inline function
	/// <summary>
	/// get position of mouse
	/// </summary>
	/// <returns>position of mouse</returns>
	static inline SVector2 GetMousePosition() { return s_mousePosition; }
#pragma endregion

#pragma region public function
	/// <summary>
	/// handle sdl events
	/// </summary>
	/// <param name="_event">sdl event</param>
	static void ParseEvent(SDL_Event _event);

	/// <summary>
	/// handle mouse events
	/// </summary>
	/// <param name="_event">sdl event</param>
	static void ParseMouseEvent(SDL_Event _event);

	/// <summary>
	/// refresh state
	/// </summary>
	static void RefreshState();

	/// <summary>
	/// get key pressed
	/// </summary>
	/// <param name="_key">key scancode</param>
	/// <returns>key is pressed</returns>
	static bool GetKey(SDL_Scancode _key);

	/// <summary>
	/// key pressed down this frame
	/// </summary>
	/// <param name="_key">key scancode</param>
	/// <returns>key is pressed this frame</returns>
	static bool GetKeyDown(SDL_Scancode _key);

	/// <summary>
	/// key pressed up this frame
	/// </summary>
	/// <param name="_key">key scancode</param>
	/// <returns>key is pressed up this frame</returns>
	static bool GetKeyUp(SDL_Scancode _key);

	/// <summary>
	/// get mouse button pressed
	/// </summary>
	/// <param name="_number">number of mouse button</param>
	/// <returns>mouse button is pressed</returns>
	static bool GetMouseButton(int _number);

	/// <summary>
	/// mouse button pressed down this frame
	/// </summary>
	/// <param name="_number">number of mouse button</param>
	/// <returns>mouse button is pressed</returns>
	static bool GetMouseButtonDown(int _number);

	/// <summary>
	/// mouse button pressed up this frame
	/// </summary>
	/// <param name="_number">number of mouse button</param>
	/// <returns>mouse button is pressed</returns>
	static bool GetMouseButtonUp(int _number);
#pragma endregion

private:
#pragma region private primitive variable
	/// <summary>
	/// 256 keys was down last frame
	/// </summary>
	static bool s_keyWasDown[256];

	/// <summary>
	/// 256 keys is down this frame
	/// </summary>
	static bool s_keyIsDown[256];

	/// <summary>
	/// 3 mouse buttons was down this frame
	/// </summary>
	static bool s_mouseButtonWasDown[3];

	/// <summary>
	/// 3 mouse buttons is down this frame
	/// </summary>
	static bool s_mouseButtonIsDown[3];
#pragma endregion

#pragma region private variable
	/// <summary>
	/// position of mouse
	/// </summary>
	static SVector2 s_mousePosition;
#pragma endregion
};