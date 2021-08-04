#include"Game.h"
int WINAPI WinMain(
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR lpCmdLine,
	_In_ int nCmdShow
)
{
	const char WINDOW_NAME[] = "ボンボンバーン";
	//ウィンドウモードに設定
	ChangeWindowMode(TRUE);
	//ウィンドウサイズを手動では変更できず、
	//かつウィンドウサイズに合わせて拡大できないようにする
	SetWindowSizeChangeEnableFlag(FALSE, FALSE);
	SetMainWindowText(WINDOW_NAME);
	SetGraphMode(WIDTH, HEIGHT, 32);
	SetWindowSizeExtendRate(1.0);
	SetBackgroundColor(0, 0, 0);
	int FrameStartTime;
	Game* game = new Game();
	//Dxライブラリを初期化
	if (DxLib_Init() == -1)
	{
		//エラーが出たらマイナス値を返して終了
		return -1;
	}
	game->SystemInit();
	//コントローラーが接続されているか？
	if (game->ConCheck() == -1)
	{
		MessageBox(NULL, "Controllerを接続してください", "Controllerのエラー", MB_OK);
		//されてないなら終了
		delete game;
		//Dxライブラリ終了処理
		DxLib_End();
		return 0;
	}

	SetDrawScreen(DX_SCREEN_BACK);
	FrameStartTime = GetNowCount();
	game->FirstInit();

	
	while (1)
	{
		//画面クリア
		ClearDrawScreen();

		while (GetNowCount() - FrameStartTime < 1000 / 60) {}
		FrameStartTime = GetNowCount();

	
		game->Update();
		game->Draw();

		//裏画面の描画を表画面に反映させる
		ScreenFlip();

		if (game->game_end_flg)break;
		if (ProcessMessage() == -1)break;
		if (CheckHitKey(KEY_INPUT_ESCAPE) == 1)break;
	}

	delete game;

	//Dxライブラリ終了処理
	DxLib_End();
	return 0;
}