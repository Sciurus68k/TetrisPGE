#pragma once
#include <string>

// Simple class to represent a tetromino
class Tetrominos
{
private:
	std::wstring tetromino[7];
public:
	
	Tetrominos() {
		tetromino[0].append(L"..X...X...X...X."); // Tetronimos 4x4
		tetromino[1].append(L"..X..XX...X.....");
		tetromino[2].append(L".....XX..XX.....");
		tetromino[3].append(L"..X..XX..X......");
		tetromino[4].append(L".X...XX...X.....");
		tetromino[5].append(L".X...X...XX.....");
		tetromino[6].append(L"..X...X..XX.....");
	}

	std::wstring& operator[](int idx) {
		return tetromino[idx];
	}
};

