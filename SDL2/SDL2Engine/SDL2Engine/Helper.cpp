#pragma region system include
#include <SDL.h>
#include <fstream>
#pragma endregion

#pragma region project include
#include "Helper.h"
#pragma endregion

// get parent directory of given path
string GetParentDirectory(string _path, int _depth)
{
	// depth higher 1
	if (_depth > 1)
		// get parent directory recursive
		_path = GetParentDirectory(_path, _depth - 1);

	// position of last sub
	size_t pos = _path.find_last_of("\\/");

	// return parent
	return (string::npos == pos)
		? ""
		: _path.substr(0, pos);
}

// get directory from asset by given path
string GetAssetPath(const char* _pPath, int _depth)
{
	// get parent directory
	string path = GetParentDirectory(SDL_GetBasePath(), _depth);

	// append sub path
	path.append("/Assets/").append(_pPath);

	// return complete asset path
	return path;
}

// load string from file
string LoadStringFromFile(const char* _pFile)
{
	// string to return
	string text = "";

	// open file
	ifstream file;
	file.open(GetAssetPath(_pFile, 4));

	// if file not opened return empty string
	if (!file.is_open())
		return text;

	// single line in file
	string line = "";

	// as long as there is a line add line to text
	while (getline(file, line))
		text.append(line).append("\n");

	// close file
	file.close();

	// return text
	return text;
}

// save string to file
void SaveStringToFile(string _text, const char* _pFile)
{
	// open file
	ofstream file;
	file.open(GetAssetPath(_pFile, 4));

	// if file are not opened
	if (!file.is_open())
		return;

	// write char* into file
	file << _text;

	// close file
	file.close();
}