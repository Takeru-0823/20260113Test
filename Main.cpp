#include "Variable.h"
#include "Color.h"
#include "Title.h"
#include "Play.h"
#include "End.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	SetWindowText("プリミティブキャッチャー");
	SetGraphMode(WIDTH, HEIGHT, 32);
	ChangeWindowMode(TRUE);
	if (DxLib_Init() == -1) return -1;
	SetBackgroundColor(0, 0, 0);
	SetDrawScreen(DX_SCREEN_BACK);

	SCENE scene = TITLE;

	PLAYINFO catcher = { 0, 0, true };

	DROP drop = { 200, 0, true, 10, YELLOW, 20, };

	INFO info = { 0, 0, 0 };

	while (1)
	{
		ClearDrawScreen();

		switch (scene)
		{
		case TITLE:
			scene = title(&info);
			break;

		case PLAY:
			scene = play(&catcher, &drop, &info);
			break;

		case END:
			scene = end(&info);
			break;
		}

		ScreenFlip();
		WaitTimer(16);
		if (ProcessMessage() == -1) break;
		if (CheckHitKey(KEY_INPUT_ESCAPE) == 1) break;
	}

	DxLib_End();
	return 0;
}