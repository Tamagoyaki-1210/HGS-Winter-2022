//=============================================================================
//
// object2D.cpp
// Author : Tanimoto Kosuke
//
//=============================================================================
#include "object2D.h"
#include "renderer.h"
#include "application.h"

//=====================================
// デフォルトコンストラクタ
//=====================================
CObject_2D::CObject_2D() : CObject(), m_pVtxBuff(nullptr)
{

}

//=====================================
// コンストラクタ
//=====================================
CObject_2D::CObject_2D(const int nPriority) : CObject(nPriority), m_pVtxBuff(nullptr)
{

}

//=====================================
// デストラクタ
//=====================================
CObject_2D::~CObject_2D()
{

}

//=====================================
// 初期化処理
//=====================================
HRESULT CObject_2D::Init()
{
    m_pos = Vec3Null;
	m_posOld = Vec3Null;
    m_rot = Vec3Null;
    m_size = Vec2Null;

    m_fAngle = 0.0f;
    m_nAnimColumn = 0;
    m_nAnimLine = 0;
    m_nAnimControl = 0;

	m_bCollision = false;
	m_bGround = false;

    // アニメーションの区分の初期化(1 * 1)
    m_nAnimColumnDiv = 1;
    m_nAnimLineDiv = 1;

    LPDIRECT3DDEVICE9 pDevice = CApplication::GetInstance()->GetRenderer()->GetDevice();

    // 頂点バッファの生成
    pDevice->CreateVertexBuffer(
        sizeof(VERTEX_2D) * 4,
        D3DUSAGE_WRITEONLY,
        FVF_VERTEX_2D,
        D3DPOOL_MANAGED,
        &m_pVtxBuff,
        NULL);

    VERTEX_2D* pVtx;	//頂点情報へのポインタ

    // 頂点バッファをロックし、頂点情報へのポインタを取得
    m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

    // 頂点カラーの設定
    pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
    pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
    pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
    pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

    pVtx[0].rhw = 1.0f;
    pVtx[1].rhw = 1.0f;
    pVtx[2].rhw = 1.0f;
    pVtx[3].rhw = 1.0f;

    // テクスチャ座標の設定
    pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
    pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
    pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
    pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

    // 頂点バッファをアンロックする
    m_pVtxBuff->Unlock();

    // テクスチャの初期化
    SetTexture(CTexture::TEXTURE_NULL);

    return S_OK;
}

//=====================================
// 終了処理
//=====================================
void CObject_2D::Uninit()
{
    // 頂点バッファの破棄
    if (m_pVtxBuff != nullptr)
    {
        m_pVtxBuff->Release();
        m_pVtxBuff = nullptr;
    }
    // オブジェクトの破棄
    Release();
}

//=====================================
// 更新処理
//=====================================
void CObject_2D::Update()
{
	// 前回位置の取得
	m_posOld = m_pos;
}

//=====================================
// 描画処理
//=====================================
void CObject_2D::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetInstance()->GetRenderer()->GetDevice();

	// 頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	CTexture::GetTextureType(m_textType);

	// ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	// テクスチャの解放処理
	CTexture::TextureClear();
}

//=====================================
// 当たり判定処理
//=====================================
D3DXVECTOR3 CObject_2D::Collision(CObject* obj)
{
	D3DXVECTOR3 flipPos = Vec3Null;

	// 当たり判定が使用中の場合
	if (obj != nullptr)
	{
		// 現在位置ポインタに先頭ポインタを代入
		CObject* pObject = obj;

		D3DXVECTOR3 pos = CObject_2D::GetPos();
		D3DXVECTOR3 posOld = CObject_2D::GetPosOld();
		D3DXVECTOR2 size = (CObject_2D::GetSize() / 2);

		float fLeft = pos.x - size.x;				// P四角形左側
		float fRight = pos.x + size.x;			// P四角形右側
		float fUpp = pos.y - size.y;				// P四角形上側
		float fLow = pos.y + size.y;				// P四角形下側

		float fLeftOld = posOld.x - size.x;			// P前回四角形左側
		float fRightOld = posOld.x + size.x;			// P前回四角形右側
		float fUppOld = posOld.y - size.y;			// P前回四角形上側
		float fLowOld = posOld.y + size.y;			// P前回四角形下側

		D3DXVECTOR3 posSub = pObject->GetPos();
		D3DXVECTOR3 posOldSub = pObject->GetPosOld();
		D3DXVECTOR2 sizeSub = (pObject->GetSize() / 2);

		float fLeftObst = posSub.x - sizeSub.x;			// O四角形左側
		float fRightObst = posSub.x + sizeSub.x;			// O四角形右側
		float fUppObst = posSub.y - sizeSub.y;			// O四角形上側
		float fLowObst = posSub.y + sizeSub.y;			// O四角形下側

		float fLeftObstOld = posOldSub.x - sizeSub.x;		// O前回四角形左側
		float fRightObstOld = posOldSub.x + sizeSub.x;	// O前回四角形右側
		float fUppObstOld = posOldSub.y - sizeSub.y;		// O前回四角形上側
		float fLowObstOld = posOldSub.y + sizeSub.y;		// O前回四角形下側

		//P左側当たり判定　P左側がO右側より左に在る場合
		if (fLeft < fRightObst && fLeftOld >= fRightObstOld)
		{
			flipPos = D3DXVECTOR3(fRightObst + size.x, pos.y, 0.0f);
		}
		//P右側当たり判定 P右側がO左側より右に在る場合
		if (fRight > fLeftObst && fRightOld <= fLeftObstOld)
		{
			flipPos = D3DXVECTOR3(fLeftObst - size.x, pos.y, 0.0f);
		}
		//P上側当たり判定 P上側がO下側より上に在る場合
		if (fUpp < fLowObst && fUppOld >= fLowObstOld)
		{
			flipPos = D3DXVECTOR3(pos.x, fLowObst + size.y, 0.0f);
			m_bGround = true;
		}
		//P下側当たり判定 P下側がO上側より下に在る場合
		if (fLow > fUppObst && fLowOld <= fUppObstOld)
		{
			flipPos = D3DXVECTOR3(pos.x, fUppObst - size.y, 0.0f);
			m_bGround = true;
		}
	}

	return flipPos;
}

//=====================================
// UV設定処理
//=====================================
void CObject_2D::SetUV()
{
    VERTEX_2D* pVtx;	// 頂点情報へのポインタ

    // 頂点バッファをロックし、頂点情報へのポインタを取得
    m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

    float fLength = sqrtf((powf(m_size.x, 2) + powf(m_size.y, 2))) / 2;

    // 頂点情報を設定
    pVtx[0].pos.x = m_pos.x - sinf(m_fAngle + m_rot.x) * fLength;
    pVtx[0].pos.y = m_pos.y - cosf(m_fAngle + m_rot.y) * fLength;
    pVtx[0].pos.z = m_pos.z;

    pVtx[1].pos.x = m_pos.x + sinf(m_fAngle - m_rot.x) * fLength;
    pVtx[1].pos.y = m_pos.y - cosf(m_fAngle - m_rot.y) * fLength;
    pVtx[1].pos.z = m_pos.z;

    pVtx[2].pos.x = m_pos.x - sinf(m_fAngle - m_rot.x) * fLength;
    pVtx[2].pos.y = m_pos.y + cosf(m_fAngle - m_rot.y) * fLength;
    pVtx[2].pos.z = m_pos.z;

    pVtx[3].pos.x = m_pos.x + sinf(m_fAngle + m_rot.x) * fLength;
    pVtx[3].pos.y = m_pos.y + cosf(m_fAngle + m_rot.y) * fLength;
    pVtx[3].pos.z = m_pos.z;

    // 頂点バッファをアンロックする
    m_pVtxBuff->Unlock();
}

//=========================================================
// 自動的な頂点テクスチャ設定処理　(画像速度)
//=========================================================
void CObject_2D::SetAnimAuto(int nSpeed)
{
    VERTEX_2D* pVtx;	// 頂点情報へのポインタ

    // 頂点バッファをロックし、頂点情報へのポインタを取得
    m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

    // テクスチャ座標の設定
    pVtx[0].tex = D3DXVECTOR2((1.0f / m_nAnimColumnDiv) * m_nAnimColumn, (1.0f / m_nAnimLineDiv) * m_nAnimLine);
    pVtx[1].tex = D3DXVECTOR2((1.0f / m_nAnimColumnDiv) * (m_nAnimColumn + 1), (1.0f / m_nAnimLineDiv) * m_nAnimLine);
    pVtx[2].tex = D3DXVECTOR2((1.0f / m_nAnimColumnDiv) * m_nAnimColumn, (1.0f / m_nAnimLineDiv) * (m_nAnimLine + 1));
    pVtx[3].tex = D3DXVECTOR2((1.0f / m_nAnimColumnDiv) * (m_nAnimColumn + 1), (1.0f / m_nAnimLineDiv) * (m_nAnimLine + 1));

    // アニメーションの秒数を数える
    m_nAnimControl++;

    // 指定の秒数でアニメーションする処理
    if (nSpeed <= m_nAnimControl)
    {
        // １列横にアニメーションする
        m_nAnimColumn++;

        // アニメーション秒数の初期化
        m_nAnimControl = 0;

        // 列が横の最大数を超えた場合
        if (m_nAnimColumnDiv <= m_nAnimColumn)
        {
            // 左端に戻す
            m_nAnimColumn = 0;

            // １行縦にアニメーションする
            m_nAnimLine++;

            // 行が縦の最大数を超えた場合
            if (m_nAnimLineDiv <= m_nAnimLine)
            {
                // 一番上に戻す
                m_nAnimLine = 0;
            }
        }
    }

    // 頂点バッファをアンロックする
    m_pVtxBuff->Unlock();
}

//=========================================================
// 手動用の頂点テクスチャ設定処理　(画像列, 画像行)
//=========================================================
void CObject_2D::SetAnimControl(int nAnimColumn, int nAnimLine)
{
    VERTEX_2D* pVtx;	// 頂点情報へのポインタ

    // 頂点バッファをロックし、頂点情報へのポインタを取得
    m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

    // テクスチャ座標の設定
    pVtx[0].tex = D3DXVECTOR2((1.0f / m_nAnimColumnDiv) * nAnimColumn, (1.0f / m_nAnimLineDiv) * nAnimLine);
    pVtx[1].tex = D3DXVECTOR2((1.0f / m_nAnimColumnDiv) * (nAnimColumn + 1), (1.0f / m_nAnimLineDiv) * nAnimLine);
    pVtx[2].tex = D3DXVECTOR2((1.0f / m_nAnimColumnDiv) * nAnimColumn, (1.0f / m_nAnimLineDiv) * (nAnimLine + 1));
    pVtx[3].tex = D3DXVECTOR2((1.0f / m_nAnimColumnDiv) * (nAnimColumn + 1), (1.0f / m_nAnimLineDiv) * (nAnimLine + 1));

    // 頂点バッファをアンロックする
    m_pVtxBuff->Unlock();
}


//=========================================================
// 手動用の頂点テクスチャ設定処理　(画像番号)
//=========================================================
void CObject_2D::SetAnimControl(int nAnimCounter)
{
    VERTEX_2D* pVtx;	// 頂点情報へのポインタ

    // 頂点バッファをロックし、頂点情報へのポインタを取得
    m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

    // 指定されたアニメ番号を変数に格納する
    int nCounter = nAnimCounter;

    // 横の最大数が指定された値より大きい場合ループする
    while (m_nAnimColumnDiv <= nCounter)
    {
        // 値を区分数だけ減らす
        nCounter -= m_nAnimColumnDiv;

        // １行縦にアニメーションする
        m_nAnimLine++;

        // 縦の最大数が指定された値より大きい場合
        if (m_nAnimLine >= m_nAnimLineDiv)
        {
            // 縦アニメーションの初期化
            m_nAnimLine = 0;
        }
    }

    // 列アニメーションの代入
    m_nAnimColumn = nCounter;

    // テクスチャ座標の設定
    pVtx[0].tex = D3DXVECTOR2((1.0f / m_nAnimColumnDiv) * m_nAnimColumn, (1.0f / m_nAnimLineDiv) * m_nAnimLine);
    pVtx[1].tex = D3DXVECTOR2((1.0f / m_nAnimColumnDiv) * (m_nAnimColumn + 1), (1.0f / m_nAnimLineDiv) * m_nAnimLine);
    pVtx[2].tex = D3DXVECTOR2((1.0f / m_nAnimColumnDiv) * m_nAnimColumn, (1.0f / m_nAnimLineDiv) * (m_nAnimLine + 1));
    pVtx[3].tex = D3DXVECTOR2((1.0f / m_nAnimColumnDiv) * (m_nAnimColumn + 1), (1.0f / m_nAnimLineDiv) * (m_nAnimLine + 1));

    // 頂点バッファをアンロックする
    m_pVtxBuff->Unlock();
}

//=====================================
// 色設定処理(頂点別)
//=====================================
void CObject_2D::SetColor(D3DXCOLOR col0, D3DXCOLOR col1, D3DXCOLOR col2, D3DXCOLOR col3)
{
    VERTEX_2D* pVtx;	// 頂点情報へのポインタ

    // 頂点バッファをロックし、頂点情報へのポインタを取得
    m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

    pVtx[0].col = col0;
    pVtx[1].col = col1;
    pVtx[2].col = col2;
    pVtx[3].col = col3;

    // 頂点バッファをアンロックする
    m_pVtxBuff->Unlock();
}

//=====================================
// 色設定処理(全体)
//=====================================
void CObject_2D::SetColor(D3DXCOLOR col)
{
    VERTEX_2D* pVtx;	// 頂点情報へのポインタ

    // 頂点バッファをロックし、頂点情報へのポインタを取得
    m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

    pVtx[0].col = col;
    pVtx[1].col = col;
    pVtx[2].col = col;
    pVtx[3].col = col;

    // 頂点バッファをアンロックする
    m_pVtxBuff->Unlock();
}

//=====================================
// 拡大量の設定処理
//=====================================
void CObject_2D::SetSize(const D3DXVECTOR2 size)
{
    m_size = size;
    m_fAngle = atan2f(m_size.x, m_size.y);

    SetUV();			// UVの設定処理
}

//=====================================
// 画像アニメーションの区分設定処理
//=====================================
void CObject_2D::SetAnimDiv(int nDivX, int nDivY)
{
    m_nAnimColumnDiv = nDivX;
    m_nAnimLineDiv = nDivY;

	SetAnimControl(0, 0);
}

//=====================================
// オブジェクト2D生成処理
//=====================================
CObject_2D* CObject_2D::Create(D3DXVECTOR3 pos, D3DXVECTOR2 size)
{
    CObject_2D* pObject2D = new CObject_2D;

    if (FAILED(pObject2D->Init()))
    {
        return nullptr;
    }

    pObject2D->SetPos(pos);
    pObject2D->SetSize(size);

    return pObject2D;
}