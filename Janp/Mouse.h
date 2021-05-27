#pragma once
#include"Parent.h"
class Mouse
{
	using Vector2 = vector::Vector2;

public:
	Mouse();
	~Mouse();
	enum MouseBotton
	{
		LEFT = MOUSE_INPUT_LEFT,
		RIGHT = MOUSE_INPUT_RIGHT,
	};
	void Init();
	bool TriggerMouseBotton(MouseBotton bot);
	int FlameMouseBotton(MouseBotton bot);
	int WheelTrigger();
	int WheelFleame();
	Vector2 GetPoint();

private:
	bool botton[3];
	int flame[3];
	int wheelFlame;
	int reWheel;
	bool wheelTriggr;
	int x, y;
};

