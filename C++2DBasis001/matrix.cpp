//=============================================================================
//
// 計算用マトリクス
// Author : tanimoto kosuke
//
//=============================================================================
#include <stdio.h>
#include "matrix.h"

//=====================================
//正規化計算処理
//=====================================
float Normalize(float val)
{
	float valNormalize = val * (1 / sqrtf(val * val));
	return valNormalize;
}

//=====================================
//正規化計算処理
//=====================================
D3DXVECTOR3 NormalizeLength(float valX, float valY)
{
	float valNormalize = 1 / sqrtf((valX * valX) + (valY * valY));

	D3DXVECTOR3 Length(valX * valNormalize, valY * valNormalize, 0.0f);

	return Length;
}

//=====================================
////円型当たり判定計算処理
//=====================================
bool CollisionCircle(D3DXVECTOR3 pos, float fLength, D3DXVECTOR3 posSub, float fLengthSub)
{
	float fSumLengthRad = (fLength + fLengthSub) / 2;				//円の半径同士の和

	float fSubX = pos.x - posSub.x;									//X座標の差分
	float fSubY = pos.y - posSub.y;									//Y座標の差分
	float fSubLength = sqrtf((fSubX * fSubX) + (fSubY * fSubY));	//現在の2点の距離

	return fSumLengthRad >= fSubLength;
}

//=====================================
//四角形当たり判定計算処理
//=====================================
bool CollisionSquare(D3DXVECTOR3 pos, D3DXVECTOR3 posSub, float fWidth, float fHeight, float fWidthSub, float fHeightSub)
{
	float fLeft = pos.x - (fWidth / 2);		//四角形左側
	float fRight = pos.x + (fWidth / 2);		//四角形右側
	float fUpp = pos.y - (fHeight / 2);		//四角形上側
	float fLow = pos.y + (fHeight / 2);		//四角形下側

	float fLeftSub = posSub.x - (fWidthSub / 2);		//四角形左側
	float fRightSub = posSub.x + (fWidthSub / 2);		//四角形右側
	float fUppSub = posSub.y - (fHeightSub / 2);		//四角形上側
	float fLowSub = posSub.y + (fHeightSub / 2);		//四角形下側

	if (fLeft < fRightSub && fRight > fLeftSub
		&& fUpp < fLowSub && fLow > fUppSub)
	{
		return true;
	}
	else
	{
		return false;
	}
}
