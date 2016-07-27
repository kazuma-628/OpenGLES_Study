#ifndef MAIN_H
#define MAIN_H

#include "Common.h"
#include "MainDraw.h"
#include "DeviceManager.h"
#include "WindowManager.h"
#include "ModelManager.h"

//define
#define RotateSpeedWeight		2.0f		//回転速度の重み（値が大きいほど回転速度は遅くなる）
#define InertiaRotateWeight		0.3f		//惰性回転量の重み（値が大きいほど惰性移動量は多くなる）
#define InertiaTranslateWeight	0.3f		//惰性移動量の重み（値が小さいほど惰性回転量は多くなる）

//構造体
typedef struct
{
	Vec2 OldPosition;				//【1イベント前】マウスのカーソル座標
	Vec2 OldScrollAmount;			//【1イベント前】スクロールの合計量、初期状態は[x:0（横[左右]スクロール）][y:0（縦[上下]スクロール）]で、
									//　スクロールした分だけ値が蓄積（加算/減算）されていく
	int	OldLeftState;				//【1イベント前】マウスの左クリックの状態
	int	OldRightState;				//【1イベント前】マウスの右クリックの状態
	Vec3 InertiaTranslate;			// 惰性に伴う1イベント分の移動量（フリックするとフリック速度に応じた値が入り徐々に[0]になる、マウスを動かさなければ[0]）
	Vec3 InertiaRotate;				// 惰性に伴う1イベント分の回転量（フリックするとフリック速度に応じた値が入り徐々に[0]になる、マウスを動かさなければ[0]）
}TmpGlobalData;

/*-------------------------------------------------------------------------------
*	関数説明
*	　描画に必要な各種情報を設定/更新する
*	引数
*	　p_WindowManager		：[I/ ]　ウィンドウ管理オブジェクト
*	　p_DeviceManager		：[I/ ]　デバイス管理オブジェクト
*	　p_Global				：[ /O]　グローバルデータ
*	戻り値
*	　なし
*-------------------------------------------------------------------------------*/
void SetVarietyOfInformation(WindowManager *p_WindowManager, DeviceManager *p_DeviceManager, GlobalData *p_Global);

#endif