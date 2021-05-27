#pragma once
#include <stdio.h>
#include <malloc.h>

#include"Parent.h"
class Load
{
public:
	Load();
	~Load();
	void LoadTex(const TCHAR *name, int &tex);
	int LoadAnimeTex(const TCHAR *name, int AllNum,
		int XNum, int YNum, int XSize, int YSize, int tex[]);
	void LoadSound(const TCHAR *name, int&sound);
	
};

