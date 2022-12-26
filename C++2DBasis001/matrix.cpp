//=============================================================================
//
// 計算用マトリクス
// Author : Tanimoto Kosuke
//
//=============================================================================
#include <stdio.h>
#include "matrix.h"

//=====================================
// 正規化計算処理
//=====================================
float Normalize(float val)
{
	float valNormalize = val * (1 / sqrtf(val * val));
	return valNormalize;
}

//=====================================
// 正規化計算処理
//=====================================
D3DXVECTOR3 NormalizeLength(float valX, float valY)
{
	float valNormalize = 1 / sqrtf((valX * valX) + (valY * valY));

	D3DXVECTOR3 Length(valX * valNormalize, valY * valNormalize, 0.0f);

	return Length;
}
