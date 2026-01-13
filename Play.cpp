#include "Variable.h"
#include "Color.h"

// 図形の設定
void dropInit(DROP* drop)
{
	drop->info.pos.x = rand() % 80 * 10 + 50;
	drop->info.pos.y = 0;
	drop->dropSpeed = rand() % 5 + 10;
	drop->color = GetColor(rand() % 256, rand() % 256, rand() % 256);
	drop->size = rand() % 5 * 2 + 50;
	drop->info.circleFlag = rand() % 2;
}

// 図形の描写
void drawDrop(DROP* drop)
{
	if (drop->info.circleFlag)
	{
		DrawCircle(drop->info.pos.x, drop->info.pos.y, drop->size, drop->color, TRUE);
	}
	else
	{
		DrawBox(drop->info.pos.x - drop->size, drop->info.pos.y - drop->size, drop->info.pos.x + drop->size, drop->info.pos.y + drop->size, drop->color, TRUE);
	}
}

// ヒットチェック
void hitCheck(PLAYINFO* catcher, DROP* drop, INFO* info)
{
	if (catcher->circleFlag && drop->info.circleFlag)
	{
		int distance = (unsigned int)pow((catcher->pos.x - drop->info.pos.x), 2) + (unsigned int)pow((catcher->pos.y - drop->info.pos.y), 2);
		distance = (unsigned int)sqrt(distance);

		if (distance <= CATCHER_SIZE + drop->size)
		{
			info->combo++;
			dropInit(drop);
		}

	}
	else if (!catcher->circleFlag && !drop->info.circleFlag)
	{
		int disX = abs(catcher->pos.x - drop->info.pos.x);
		int disY = abs(catcher->pos.y - drop->info.pos.y);

		if (disX <= CATCHER_SIZE + drop->size && disY <= CATCHER_SIZE + drop->size)
		{
			info->combo++;
			dropInit(drop);
		}
	}
	else
	{
		int disX = abs(catcher->pos.x - drop->info.pos.x);
		int disY = abs(catcher->pos.y - drop->info.pos.y);

		if (disX <= CATCHER_SIZE + drop->size && disY <= CATCHER_SIZE + drop->size)
		{
			info->combo = 0;
			dropInit(drop);
		}
	}

}

SCENE play(PLAYINFO* catcher, DROP* drop, INFO* info)
{
	info->timer--;

	// キャッチャー
	static int beforeSpace = 0;
	int nowSpace = CheckHitKey(KEY_INPUT_SPACE);

	GetMousePoint(&catcher->pos.x, &catcher->pos.y);
	if (catcher->circleFlag)
	{
		DrawCircle(catcher->pos.x, catcher->pos.y, CATCHER_SIZE, WHITE, TRUE);
		if (nowSpace == 1 && beforeSpace == 0)
		{
			catcher->circleFlag = false;
		}
	}
	else
	{
		DrawBox(catcher->pos.x - CATCHER_SIZE, catcher->pos.y - CATCHER_SIZE, catcher->pos.x + CATCHER_SIZE, catcher->pos.y + CATCHER_SIZE, WHITE, TRUE);
		if (nowSpace == 1 && beforeSpace == 0)
		{
			catcher->circleFlag = true;
		}
	}
	beforeSpace = nowSpace;

	// 図形
	drop->info.pos.y += drop->dropSpeed;
	if (drop->info.pos.y + drop->size >= 550)
	{
		info->combo = 0;
		dropInit(drop);
	}
	drawDrop(drop);

	hitCheck(catcher, drop, info);

	// 赤ライン
	DrawBox(0, 550, WIDTH + 1, 580, RED, TRUE);

	// コンボ表示
	if (info->combo >= info->highCombo)
	{
		info->highCombo = info->combo;
	}

	DrawBox(700, 450, WIDTH + 1, 540, WHITE, TRUE);

	SetFontSize(30);
	DrawFormatString(710, 460, BLACK, "コンボ数：%d", info->combo);

	SetFontSize(30);
	DrawFormatString(710, 500, BLACK, "最高コンボ数：%d", info->highCombo);

	// 残り時間
	SetFontSize(20);
	DrawFormatString(0, 0, WHITE, "残り%d秒", info->timer / 100);

	if (info->timer <= 0)
	{
		info->combo = 0;
		info->timer = 180;
		return END;
	}

	return PLAY;
}