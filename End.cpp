#include "Variable.h"
#include "Color.h"

SCENE end(INFO* info)
{
	info->timer--;

	SetFontSize(90);
	DrawString(300, 200, "GAME END", YELLOW, TRUE);

	if (info->timer <= 0)
	{
		info->timer = 0;
		return TITLE;
	}

	return END;
}