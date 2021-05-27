#pragma once
#include"Parent.h"
class Key
{
public:
	Key();
	~Key();
	void Init();
	void Input();
	bool KeyTrigger(int keyNum);
	int keyFlame(int keyNum);
private:
	char key[256];
	bool trigger[256];
	int flame[256];
};

