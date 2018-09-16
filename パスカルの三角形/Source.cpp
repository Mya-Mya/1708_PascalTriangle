#include"DxLib.h"
#include<Windows.h>

#define WEIGHT 800
#define HEIGHT WEIGHT
#define ARRAYSIZE 257
#define POINTSIZE 3

class FONTHANDLE {
protected:
	int FontHandle;
public:
	FONTHANDLE() {
		FontHandle = (CreateFontToHandle("メイリオ", POINTSIZE, 2, DX_FONTTYPE_ANTIALIASING_EDGE_8X8));
	}
	int GiveFontHandle() { return FontHandle; }
};

class DRAW {
protected:
	int FontHandle;
	double x, y;
	FONTHANDLE *c_FONTHANDLE=NULL;
public:
	DRAW() { ; }
	void TellFONTHANDLE(FONTHANDLE *in) { c_FONTHANDLE = in, FontHandle = c_FONTHANDLE->GiveFontHandle(); }
	void SetPos(double inx, double iny) { x = inx, y = iny; }
	void Draw(){
		DrawStringToHandle(x, y, "■", GetColor(255, 255, 255), FontHandle);
	}
};

class ARRAYER {
protected:
	int Array[ARRAYSIZE + 2][ARRAYSIZE + 2];
	DRAW *c_DRAW=NULL;
	FONTHANDLE *c_FONTHANDLE = NULL;

public:
	ARRAYER();
	void Connect() {
		c_DRAW = new DRAW, c_FONTHANDLE = new FONTHANDLE;
		c_DRAW->TellFONTHANDLE(c_FONTHANDLE);
	}
	void Draw();
};
ARRAYER::ARRAYER() {
	//変数初期化
	for (int x = 0; x < ARRAYSIZE + 2; x++) {
		for (int y = 0; y < ARRAYSIZE + 2; y++) {
			Array[x][y] = 0;
		}
	}

	//1を定義
	Array[1][1] = 1;

	//順に計算
	for (int x = 1; x < ARRAYSIZE; x++) {
		for (int y = 2; y < ARRAYSIZE; y++) {
			Array[x][y] = Array[x-1][y-1]+Array[x][y-1];
		}
	}
}
void ARRAYER::Draw() {
	for (int x = 1; x < ARRAYSIZE; x++) {
		for (int y = 1; y < ARRAYSIZE; y++) {
			if (Array[x][y] % 2 == 0) continue;
			Sleep(1);
			c_DRAW->SetPos(((WEIGHT / 2) - ((y*POINTSIZE)/2)+x*POINTSIZE), (y*POINTSIZE));
			c_DRAW->Draw();
		}
	}
}

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	SetGraphMode(WEIGHT, HEIGHT, 16);
	ChangeWindowMode(TRUE), DxLib_Init();

	ARRAYER *c_ARRAYER = new ARRAYER;
	c_ARRAYER->Connect();
	c_ARRAYER->Draw();

	WaitKey();
	return 0;
}