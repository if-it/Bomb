#include "Controller.h"

Controller::Controller()
{
}


Controller::~Controller()
{
}

void Controller::Init()
{

	for (int i = 0;i < 15;++i)
	{
		botton[i] = false;
		flame[i] = 0;
	}
	LTrigger = false;
	RTrigger = false;
	stickLY = false;
	stickLX = false;
	stickRY = false;
	stickRX = false;
	shake_On = true;
}
//�Ă΂Ȃ��Ǝg���Ȃ��I
void Controller::Input(bool XorD)
{
	this->XorD = XorD;
	if (XorD)GetJoypadDirectInputState(DX_INPUT_PAD1, &DInput);
	else GetJoypadXInputState(DX_INPUT_PAD1, &XInput);
}
int Controller::Set()
{

	if (GetJoypadNum() <= 0)
	{
		return -1;
	}

	return 0;
}

bool Controller::TrlggerBotton(Botton bot)
{
	if (XInput.Buttons[(int)bot] == 0)
	{
		// ������Ă��Ȃ� 
		botton[(int)bot] = false;
	}
	else if (!botton[(int)bot])
	{
		// ������Ă���
		botton[(int)bot] = true;
		return true;
	}
	return false;
}
int Controller::FlameBotton(Botton bot)
{
	if (XInput.Buttons[bot] == 0)
	{
		// ������Ă��Ȃ� 
		flame[bot] = 0;
		botton[bot] = false;
	}
	else
	{
		// ������Ă���
		botton[bot] = true;
		flame[bot]++;
		return flame[bot];
	}
	return flame[bot];
}

vector::Vector2 Controller::StickL()
{
	return Vector2(XInput.ThumbLX, XInput.ThumbLY);
}

int Controller::StickLTriggerX()
{
	if (XInput.ThumbLX == 0)
	{
		stickLX = true;
	}
	if (XInput.ThumbLX > 0 && stickLX)
	{
		stickLX = false;
		return 1;
	}
	if (XInput.ThumbLX < 0 && stickLX)
	{
		stickLX = false;
		return -1;
	}
	return 0;
}

int Controller::StickLTriggerY()
{
	if (XInput.ThumbLY == 0)
	{
		stickLY = true;
	}
	if (XInput.ThumbLY < 0 && stickLY)
	{
		stickLY = false;
		return 1;
	}
	if (XInput.ThumbLY > 0 && stickLY)
	{
		stickLY = false;
		return -1;
	}
	return 0;
}



vector::Vector2 Controller::StickR()
{

	return Vector2(XInput.ThumbRX, XInput.ThumbRY);
}

int Controller::StickRTriggerX()
{
	if (XInput.ThumbRX == 0)
	{
		stickRX = true;
	}
	if (XInput.ThumbRX > 0 && stickRX)
	{
		stickRX = false;
		return 1;
	}
	if (XInput.ThumbRX < 0 && stickRX)
	{
		stickRX = false;
		return -1;
	}
	return 0;
}

int Controller::StickRTriggerY()
{
	if (XInput.ThumbRY == 0)
	{
		stickRY = true;
	}
	if (XInput.ThumbRY > 0 && stickRY)
	{
		stickRY = false;
		return 1;
	}
	if (XInput.ThumbRY < 0 && stickRY)
	{
		stickRY = false;
		return -1;
	}
	return 0;
}



int Controller::LTriggerF()
{
	if (XInput.LeftTrigger == 0)
	{
		LFlame = 0;
		LTrigger = false;
	}
	else
	{
		LTrigger = true;
		LFlame++;
	}
	return LFlame;
}

int Controller::RTriggerF()
{
	if (XInput.RightTrigger == 0)
	{
		RFlame = 0;
		RTrigger = false;
	}
	else
	{
		RTrigger = true;
		RFlame++;
	}
	return RFlame;
}

bool Controller::LTriggerT()
{
	if (XInput.LeftTrigger == 0)
	{
		LTrigger = false;
	}
	else if (!LTrigger)
	{
		LTrigger = true;
		return true;
	}
	return false;
}

bool Controller::RTriggerT()
{
	if (XInput.RightTrigger == 0)
	{
		RTrigger = false;
	}
	else if (!RTrigger)
	{
		RTrigger = true;
		return true;
	}
	return false;
}

int Controller::CheckHitAllBotton()
{
	int i;
	for (i = 0; i < 16; i++)
	{
		if (XInput.Buttons[i] == 0)
		{
			botton[i] = false;
		}
		else if (!botton[i])
		{
			botton[i] = true;
			return true;
		}
	}
	return false;
}

void Controller::Shake(int power, int time)
{
	if(shake_On)StartJoypadVibration(DX_INPUT_PAD1, power, time);
}

void Controller::StopShake()
{
	StopJoypadVibration(DX_INPUT_PAD1);
}