#include"Common.h"
#include"GameMaster.h"

// プログラムは WinMain から始まります
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	ChangeWindowMode(TRUE);	//ウィンドウモードにする
	SetGraphMode(WINDOW_X, WINDOW_Y, 32, FPS);	//ウィンドウサイズを設定する

	if (DxLib_Init() == DX_ERROR)	return DX_ERROR;	//エラーで強制終了

	SetDrawScreen(DX_SCREEN_BACK);	//裏画面を描画対象へ

	GameMaster* GM = new GameMaster;	//GMを生成
	
	//メイン処理
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0) {
		ScreenFlip();		//裏画面と表画面の入替
		ClearDrawScreen();	//裏画面の描画を全て消去
		GM->Update();
	}

	DxLib_End();			// ＤＸライブラリ使用の終了処理
	return 0;				// ソフトの終了 
}