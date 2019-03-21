/*
 * mygame.h: 本檔案儲遊戲本身的class的interface
 * Copyright (C) 2002-2008 Woei-Kae Chen <wkc@csie.ntut.edu.tw>
 *
 * This file is part of game, a free game development framework for windows.
 *
 * game is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * game is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 *	 2004-03-02 V4.0
 *      1. Add CGameStateInit, CGameStateRun, and CGameStateOver to
 *         demonstrate the use of states.
 *   2005-09-13
 *      Rewrite the codes for CBall and CEraser.
 *   2005-09-20 V4.2Beta1.
 *   2005-09-29 V4.2Beta2.
 *   2006-02-08 V4.2
 *      1. Rename OnInitialUpdate() -> OnInit().
 *      2. Replace AUDIO_CANYON as AUDIO_NTUT.
 *      3. Add help bitmap to CGameStateRun.
 *   2006-09-09 V4.3
 *      1. Rename Move() and Show() as OnMove and OnShow() to emphasize that they are
 *         event driven.
 *   2008-02-15 V4.4
 *      1. Add namespace game_framework.
 *      2. Replace the demonstration of animation as a new bouncing ball.
 *      3. Use ShowInitProgress(percent) to display loading progress. 
*/

/////////////////////////////////////////////////////////////////////////////
// Constants
/////////////////////////////////////////////////////////////////////////////

enum AUDIO_ID {				// 定義各種音效的編號
	AUDIO_DING,				// 0
	AUDIO_LAKE,				// 1
	AUDIO_NTUT				// 2
};

namespace game_framework {
/////////////////////////////////////////////////////////////////////////////
// 這個class提供可以用鍵盤或滑鼠控制的擦子
// 看懂就可以改寫成自己的程式了
/////////////////////////////////////////////////////////////////////////////



/////////////////////////////////////////////////////////////////////////////
// 這個class提供繞圈圈的球
// 看懂就可以改寫成自己的程式了
/////////////////////////////////////////////////////////////////////////////

class CBall
{
public:
	CBall();
	bool IsAlive();											// 是否活著
	void LoadBitmap();										// 載入圖形
	void OnMove();											// 移動
	void OnShow();											// 將圖形貼到畫面
	void SetXY(int nx, int ny);								// 設定圓心的座標
	void SetIsAlive(bool alive);							// 設定是否活著
	void SetDelay(int d);									// 設定旋轉的速度
protected:
	CMovingBitmap bmp;			// 球的圖
	CMovingBitmap bmp_center;	// 圓心的圖			
	int x, y;					// 圓心的座標
	int dx, dy;					// 球距離圓心的位移量
	int index;					// 球的「角度」，0-17表示0-360度
	int delay_counter;			// 調整旋轉速度的計數器
	int delay;					// 旋轉的速度
	bool is_alive;				// 是否活著
private:
	bool HitRectangle(int tx1, int ty1, int tx2, int ty2);	// 是否碰到參數範圍的矩形
};

/////////////////////////////////////////////////////////////////////////////
// 這個class提供會一直彈跳的球
// 看懂就可以改寫成自己的程式了
/////////////////////////////////////////////////////////////////////////////

class CBouncingBall
{
public:
	CBouncingBall();
	void LoadBitmap();		// 載入圖形
	void OnMove();			// 移動
	void OnShow();			// 將圖形貼到畫面
private:
	int x, y;				// 圖形座標
	int floor;				// 地板的Y座標
	bool rising;			// true表上升、false表下降
	int initial_velocity;	// 初始速度
	int velocity;			// 目前的速度(點/次)
	CAnimation animation;	// 利用動畫作圖形
};


//MAP
class CGameMap {
public:
	CGameMap();
	void LoadBitmap();
	void OnShow();
	bool IsEmpty(int x, int y);
	void SetSXSY(int changeX,int changeY);
	int ScreenX(int x);
	int ScreenY(int y);
private:
	CMovingBitmap floor, dark;
	int map[25][25];
	int sx, sy;
	const int MW, MH;
};

//PLAYER
class Player {
public:
	Player();
	int  GetX1();					
	int  GetY1();					
	int  GetX2();					
	int  GetY2();					
	void Initialize();				
	void LoadBitmap();				
	void OnMove(CGameMap* m);					
	void OnShow(CGameMap *m);					
	void SetMovingDown(bool flag);	
	void SetMovingLeft(bool flag);	
	void SetMovingRight(bool flag); 
	void SetMovingUp(bool flag);	
	void SetXY(int nx, int ny);		
private:
	CAnimation animation;		
	int x, y;					
	bool isMovingDown;			
	bool isMovingLeft;			
	bool isMovingRight;			
	bool isMovingUp;			
};




/////////////////////////////////////////////////////////////////////////////
// 這個class為遊戲的遊戲開頭畫面物件
// 每個Member function的Implementation都要弄懂
/////////////////////////////////////////////////////////////////////////////

class CGameStateInit : public CGameState {
public:
	CGameStateInit(CGame *g);
	void OnInit();  								// 遊戲的初值及圖形設定
	void OnBeginState();							// 設定每次重玩所需的變數
	void OnKeyUp(UINT, UINT, UINT); 				// 處理鍵盤Up的動作
	void OnLButtonDown(UINT nFlags, CPoint point);  // 處理滑鼠的動作
protected:
	void OnShow();									// 顯示這個狀態的遊戲畫面
private:
	CMovingBitmap logo;								// csie的logo
};

/////////////////////////////////////////////////////////////////////////////
// 這個class為遊戲的遊戲執行物件，主要的遊戲程式都在這裡
// 每個Member function的Implementation都要弄懂
/////////////////////////////////////////////////////////////////////////////

class CGameStateRun : public CGameState {
public:

	CGameStateRun(CGame *g);
	~CGameStateRun();
	void OnBeginState();							// 設定每次重玩所需的變數
	void OnInit();  								// 遊戲的初值及圖形設定
	void OnKeyDown(UINT, UINT, UINT);
	void OnKeyUp(UINT, UINT, UINT);
	void OnLButtonDown(UINT nFlags, CPoint point);  // 處理滑鼠的動作
	void OnLButtonUp(UINT nFlags, CPoint point);	// 處理滑鼠的動作
	void OnMouseMove(UINT nFlags, CPoint point);	// 處理滑鼠的動作 
	void OnRButtonDown(UINT nFlags, CPoint point);  // 處理滑鼠的動作
	void OnRButtonUp(UINT nFlags, CPoint point);	// 處理滑鼠的動作
protected:
	void OnMove();									// 移動遊戲元素
	void OnShow();									// 顯示這個狀態的遊戲畫面
private:
	CGameMap gamemap;

	const int		NUMBALLS;	// 球的總數
	CMovingBitmap	background;	// 背景圖
	CMovingBitmap	help;		// 說明圖
	CBall			*ball;		// 球的陣列
	CMovingBitmap	corner;		// 角落圖
	CInteger		hits_left;	// 剩下的撞擊數
	CBouncingBall   bball;		// 反覆彈跳的球


	Player          player;      //角色
};

/////////////////////////////////////////////////////////////////////////////
// 這個class為遊戲的結束狀態(Game Over)
// 每個Member function的Implementation都要弄懂
/////////////////////////////////////////////////////////////////////////////

class CGameStateOver : public CGameState {
public:
	CGameStateOver(CGame *g);
	void OnBeginState();							// 設定每次重玩所需的變數
	void OnInit();
protected:
	void OnMove();									// 移動遊戲元素
	void OnShow();									// 顯示這個狀態的遊戲畫面
private:
	int counter;	// 倒數之計數器

};

}