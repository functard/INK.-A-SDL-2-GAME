#pragma once

#pragma region system include
#include <string>
#pragma endregion

#pragma region using
using namespace std;
#pragma endregion

/// <summary>
/// get parent directory of path
/// </summary>
/// <param name="_path">path</param>
/// <param name="_depth">depth to get into</param>
/// <returns>parent path</returns>
string GetParentDirectory(string _path, int _depth = 1);

/// <summary>
/// get complete asset path
/// </summary>
/// <param name="_pPath">relative path</param>
/// <param name="_depth">depth to get into</param>
/// <returns>complete path</returns>
string GetAssetPath(const char* _pPath, int _depth);

/// <summary>
/// load string from file
/// </summary>
/// <param name="_pFile">file name</param>
/// <returns>value string from file</returns>
string LoadStringFromFile(const char* _pFile);

/// <summary>
/// save string to file
/// </summary>
/// <param name="_text">text to save</param>
/// <param name="_pFile">file name</param>
void SaveStringToFile(string _text, const char* _pFile);