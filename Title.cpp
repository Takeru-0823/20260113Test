#include "Variable.h"
#include "Color.h"

SCENE title(INFO* info)
{
	SetFontSize(90);
	DrawString(370, 200, "GAME", WHITE, TRUE);

	info->timer++;

	if (info->timer % 60 > 30)
	{
		SetFontSize(70);
		DrawString(300, 400, "PUSH SPACE", YELLOW, TRUE);
	}

	if (CheckHitKey(KEY_INPUT_SPACE) == 1)
	{
		info->timer = 600;
		return PLAY;
	}
	
	return TITLE;
}