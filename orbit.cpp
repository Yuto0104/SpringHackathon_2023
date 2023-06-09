//=============================================================================
//
// OΥNX(orbit.cpp)
// Author : ϊ±l
// Tv : OΥΆ¬πs€
//
//=============================================================================

//*****************************************************************************
// CN[h
//*****************************************************************************
#include <assert.h>

#include "orbit.h"
#include "calculation.h"
#include "renderer.h"
#include "application.h"

//=============================================================================
// CX^XΆ¬
// Author : ϊ±l
// Tv : OΥπΆ¬·ι
//=============================================================================
COrbit * COrbit::Create(void)
{
	// OΥCX^X
	COrbit *pOrbit = nullptr;

	// Μπϊ
	pOrbit = new COrbit;

	// ΜmΫͺΕ«Θ©Α½
	assert(pOrbit != nullptr);

	// lΜϊ»
	pOrbit->Init();

	// CX^XπΤ·
	return pOrbit;
}

//=============================================================================
// RXgN^
// Author : ϊ±l
// Tv : CX^XΆ¬Ιs€
//=============================================================================
COrbit::COrbit()
{
	m_pParentMtx = nullptr;							// eΜ}gbNX
	m_offset = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// ΚuΜ·ͺ
	m_EBlendMode = BLEND_MODE::MODE_NORMAL;			// ΏuhΜϋ@
	m_nDivision = 0;								// ͺ
}

//=============================================================================
// fXgN^
// Author : ϊ±l
// Tv : CX^XIΉΙs€
//=============================================================================
COrbit::~COrbit()
{

}

//=============================================================================
// ϊ»
// Author : ϊ±l
// Tv : Έ_obt@πΆ¬΅AoΟΜϊlπέθ
//=============================================================================
HRESULT COrbit::Init()
{
	// ϊ»
	CMesh3D::Init();

	// eNX`Μέθ
	LoadTex(-1);

	// ΚuΜ·ͺ
	m_offset = D3DXVECTOR3(0.0f, 100.0f, 0.0f);		

	// ͺ
	m_nDivision = 1;				

	// ubNΜέθ
	SetBlock(CMesh3D::DOUBLE_INT(m_nDivision, 1));						

	return S_OK;
}

//=============================================================================
// IΉ
// Author : ϊ±l
// Tv : eNX`Μ|C^ΖΈ_obt@Μπϊ
//=============================================================================
void COrbit::Uninit()
{// IΉ
	CMesh3D::Uninit();
}

//=============================================================================
// XV
// Author : ϊ±l
// Tv : 2DXVπs€
//=============================================================================
void COrbit::Update()
{// XV
	CMesh3D::Update();

	// Έ_ΐWΜZo
	SetVtx();
}

//=============================================================================
// `ζ
// Author : ϊ±l
// Tv : 2D`ζπs€
//=============================================================================
void COrbit::Draw()
{// foCXΦΜ|C^ΜζΎ
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();

	// Cgπ³ψ
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	// JOΝ΅Θ’
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	switch (m_EBlendMode)
	{
	case BLEND_MODE::MODE_NORMAL:
		break;

	case BLEND_MODE::MODE_ADD:
		// ΏufBOπΑZ¬Ιέθ
		pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
		pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
		break;

	case BLEND_MODE::MODE_SUB:
		// ΏufBOπΈZ¬Ιέθ
		pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_REVSUBTRACT);
		pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
		break;

	default:
		break;
	}

	// `ζ
	CMesh3D::Draw();

	// ΏufBOπ³Ιί·
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	// JOέθπ³Ιί·
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);

	// CgπLψ
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}

//=============================================================================
// Έ_ΐWΘΗΜέθ
// Author : ϊ±l
// Tv : 3DΈ_ΐWAnorAΈ_J[πέθ·ι
//=============================================================================
void COrbit::SetVtx()
{
	// ξρΜζΎ
	DOUBLE_INT block = GetBlock();
	DOUBLE_INT line = GetLine();
	D3DXVECTOR3 offset = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXCOLOR col = GetCol();
	int nMaxVtx = GetVtx();
	int nDivision = GetVtx() / 2;

	// Έ_ξρΜζΎ
	VERTEX_3D *pVtx = NULL;

	// Έ_obt@πbN
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	if (m_pParentMtx != nullptr)
	{
		for (int nCntDivision = nDivision - 1; nCntDivision >= 0; nCntDivision--)
		{
			if (nCntDivision <= 0)
			{// e}gbNX©η»έΚuπZo
				D3DXVec3TransformCoord(&pVtx[nCntDivision].pos, &offset, m_pParentMtx);
				D3DXVec3TransformCoord(&pVtx[nDivision + nCntDivision].pos, &m_offset, m_pParentMtx);
			}
			else
			{// ΠΖΒOΜΈ_Κuπγό
				pVtx[nCntDivision].pos = pVtx[nCntDivision - 1].pos;
				pVtx[nDivision + nCntDivision].pos = pVtx[nDivision + nCntDivision - 1].pos;
			}
		}
	}
	else
	{
		for (int nCntVtx = 0; nCntVtx < nMaxVtx; nCntVtx++)
		{// ϊ»
			pVtx[nCntVtx].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		}
	}

	// Έ_obt@ΜAbN
	m_pVtxBuff->Unlock();
}

//=============================================================================
// eNX`ΐWΜέθ
// Author : ϊ±l
// Tv : 3DbVΜeNX`ΐWπέθ·ι
//=============================================================================
void COrbit::SetTex()
{
	// ξρΜζΎ
	DOUBLE_INT block = GetBlock();
	DOUBLE_INT line = GetLine();
	D3DXVECTOR2 tex = GetTex();

	// Έ_ξρΜζΎ
	VERTEX_3D *pVtx = NULL;

	// Έ_obt@πbN
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntZ = 0; nCntZ < line.y; nCntZ++)
	{
		for (int nCntX = 0; nCntX < line.x; nCntX++)
		{// ΟιΎ
			int nCntVtx = nCntX + (nCntZ *  line.x);

			if (GetSplitTex())
			{// eNX`ΐWΜέθ
				pVtx[nCntVtx].tex = D3DXVECTOR2(1.0f * nCntX + tex.x, 1.0f * (line.y - nCntZ) + tex.y);
			}
			else
			{// eNX`ΐWΜέθ
				pVtx[nCntVtx].tex = D3DXVECTOR2(1.0f / block.x * nCntX + tex.x, 1.0f / block.y * (line.y - nCntZ) + tex.y);
			}
		}
	}

	// Έ_obt@ΜAbN
	m_pVtxBuff->Unlock();
}

//=============================================================================
// ͺΜέθ
// Author : ϊ±l
// Tv : 3DbVΜͺπέθ·ι
//=============================================================================
void COrbit::SetDivision(const int nDivision)
{
	// ͺΜέθ
	m_nDivision = nDivision;

	// ubNΜέθ
	SetBlock(CMesh3D::DOUBLE_INT(m_nDivision, 1));
}
