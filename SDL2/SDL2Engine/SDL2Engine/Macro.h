#pragma once

#pragma region system include
#include <iostream>
#pragma endregion

#pragma region value macro
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720
#define COLLISION_CHECK_TIME 0.01f
#define COLLISION_RANGE 1024.0f
#pragma endregion
	
#pragma region function macro
#define LOG(TEXT)				\
std::cout << TEXT << std::endl;

#define LOG_ERROR(ERROR, ID)		\
std::cout << ERROR << std::endl;	\
return ID;

#define LOG_SDL_ERROR(CHECK, ID)				\
if(CHECK)										\
{												\
	std::cout << SDL_GetError() << std::endl;	\
	return ID;									\
}
#pragma endregion