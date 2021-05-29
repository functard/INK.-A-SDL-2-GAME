#pragma once

#pragma region system include
#include <string>  
#pragma endregion

#pragma region project include
#include "TexturedEntity.h" 
#pragma endregion

#pragma region using
using namespace std;
#pragma endregion

/// <summary>
/// world class
/// </summary>
class GWorld : public CTexturedEntity
{
public:
#pragma region constructor
	/// <summary>
	/// constructor
	/// </summary>
	/// <param name="_pRenderer">renderer</param>
	/// <param name="_pFileName">absolute file path name</param>
	GWorld(const char* _pFileName)
		: CTexturedEntity(SVector2(), SVector2(), _pFileName) {}

	/// <summary>
	/// destructor
	/// </summary>
	~GWorld() {}
#pragma endregion

#pragma region public function
	/// <summary>
	/// initialize world
	/// </summary>
	void Init();
#pragma endregion

#pragma region private function
	/// <summary>
	/// load world as string from bmp file
	/// </summary>
	/// <param name="_pFile">file to load from</param>
	/// <returns>world as string</returns>
	string LoadWorldFromBmp(const char* _pFile);
#pragma endregion
};