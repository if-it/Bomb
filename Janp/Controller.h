#pragma once
#include"Parent.h"
#define XINPUT_MAX  32767
class Controller
{

	using Vector2 = vector::Vector2;
public:
	Controller();
	~Controller();
	void Input(bool XorD = false);
	void Init();
	enum Botton
	{
		UP, DOWN, LEFT, RIGHT, START, BACK, L3, R3, LB, RB,
		A = XINPUT_BUTTON_A,
		B = XINPUT_BUTTON_B,
		X = XINPUT_BUTTON_X,
		Y = XINPUT_BUTTON_Y,
	};
	int Set();
	bool TrlggerBotton(Botton bot);
	int FlameBotton(Botton bot);
	Vector2 StickL();
	int StickLTriggerX();
	int StickLTriggerY();
	Vector2 StickR();
	int StickRTriggerX();
	int StickRTriggerY();
	int LTriggerF();
	int RTriggerF();
	bool LTriggerT();
	bool RTriggerT();
	int CheckHitAllBotton();
	void Shake(int power, int time);
	void StopShake();
	bool Get_Shake_On() { return shake_On;}
	bool Set_Shake_On(bool shakeon) { shake_On = shakeon;}

private:
	bool XorD;
	int PadInput;
	DINPUT_JOYSTATE DInput;
	XINPUT_STATE XInput;
	bool botton[15];
	int flame[15];
	bool LTrigger;
	int LFlame;
	bool RTrigger;
	int RFlame;
	int bufX;
	int bufY;
	bool stickLY;
	bool stickLX;
	bool stickRY;
	bool stickRX;
	bool shake_On;
};

