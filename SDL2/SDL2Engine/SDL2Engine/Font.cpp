#pragma region project include
#include "Font.h"
#include "Helper.h"
#pragma endregion

#pragma region constructor
// constructor
CFont::CFont(const char* _pFileName, int _size)
{
	// get asset path
	std::string file = GetAssetPath(_pFileName, 4);

	// set file name
	m_pFile = file.c_str();

	// open font
	m_pFont = TTF_OpenFont(m_pFile, _size);
}
#pragma endregion

#pragma region destructor
// destructor
CFont::~CFont()
{
	// close font
	TTF_CloseFont(m_pFont);
}
#pragma endregion