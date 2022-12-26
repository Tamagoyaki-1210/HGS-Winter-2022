//=============================================================================
//
// �v�Z�p�}�g���N�X
// Author : Tanimoto Kosuke
//
//=============================================================================
#include <stdio.h>
#include "matrix.h"

//=====================================
// ���K���v�Z����
//=====================================
float Normalize(float val)
{
	float valNormalize = val * (1 / sqrtf(val * val));
	return valNormalize;
}

//=====================================
// ���K���v�Z����
//=====================================
D3DXVECTOR3 NormalizeLength(float valX, float valY)
{
	float valNormalize = 1 / sqrtf((valX * valX) + (valY * valY));

	D3DXVECTOR3 Length(valX * valNormalize, valY * valNormalize, 0.0f);

	return Length;
}
