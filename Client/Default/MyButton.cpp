#include "stdafx.h"
#include "MyButton.h"
#include "Management.h"
#include "VIBuffer.h"
#include "KeyMgr.h"
USING(Client)

CMyButton::CMyButton(CMyButton & _rhs)
	: CGameObject(_rhs)
{

}


HRESULT CMyButton::Ready_GameObject_Prototype()
{
	return S_OK;
}

HRESULT CMyButton::Ready_GameObject(void* pArg)
{
	if (nullptr != pArg)
		memcpy(&m_tDesc, pArg, sizeof(STATEDESC));


	if (FAILED(Add_Component(SCENE_STATIC, L"Transform", L"Transform", (CComponent**)&m_pTransform)))
		return E_FAIL;
	if (FAILED(Add_Component(SCENE_STATIC, L"VIBuffer_Rect", L"VIBuffer_Rect", (CComponent**)&m_pVIBuffer)))
		return E_FAIL;
	if (FAILED(Add_Component(m_tDesc.m_iTextureSceneID, m_tDesc.m_pTextureTag, L"Texture", (CComponent**)&m_pTexture)))
		return E_FAIL;
	if (FAILED(Add_Component(SCENE_STATIC, L"Shader_Rect", L"Shader_Rect", (CComponent**)&m_pShader)))
		return E_FAIL;
	if (FAILED(Add_Component(SCENE_STATIC, L"Renderer", L"Renderer", (CComponent**)&m_pRenderer)))
		return E_FAIL;


	CKeyMgr::Get_Instance()->RegisterObserver(m_tDesc.m_eSceneID, this);

	m_pTransform->SetUp_Position(m_tDesc.m_tBaseDesc.vPos);
	m_pTransform->SetUp_Scale(m_tDesc.m_tBaseDesc.vSize);
	return S_OK;
}




_int CMyButton::Update_GameObject(_double _timeDelta)
{




	return 0;
}


_int CMyButton::Late_Update_GameObject(_double _timeDelta)
{
	if (!m_bActive)
		return 0;

	if (nullptr == m_pRenderer)
		return -1;

	if (FAILED(m_pRenderer->Add_RenderGroup(CRenderer::RENDER_UI, this)))
		return -1;

	return 0;
}

HRESULT CMyButton::Render_GameObject()
{
	if (!m_bActive)
		return 0;

	if (nullptr == m_pVIBuffer ||
		nullptr == m_pTransform)
		return E_FAIL;


	//if (FAILED(m_pVIBuffer->Set_Transform(m_pTransform->Get_WorldMatrix())))
	//	return E_FAIL;

	ALPHATEST;

	if (FAILED(m_pTexture->Set_TextureOnShader(m_pShader, "g_BaseTexture", 0)))
		return E_FAIL;

	if (FAILED(m_pShader->Begin_Shader()))
		return E_FAIL;
	if (FAILED(m_pShader->Begin_Pass(0)))
		return E_FAIL;


	if (FAILED(m_pVIBuffer->Render_VIBuffer()))
		return E_FAIL;


	if (FAILED(m_pShader->End_Pass()))
		return E_FAIL;

	if (FAILED(m_pShader->End_Shader()))
		return E_FAIL;


	ALPHATEST_END;

	return S_OK;
}





CMyButton * CMyButton::Create(PDIRECT3DDEVICE9 _pGraphic_Device)
{
	CMyButton* pInstance = new CMyButton(_pGraphic_Device);
	if (FAILED(pInstance->Ready_GameObject_Prototype()))
	{
		MSG_BOX("Fail to create CMyButton");
		Safe_Release(pInstance);

	}
	return pInstance;
}

CGameObject * CMyButton::Clone_GameObject(void * pArg)
{
	CMyButton* pInstance = new CMyButton(*this);
	if (FAILED(pInstance->Ready_GameObject(pArg)))
	{
		MSG_BOX("Fail to clone CMyButton");
		Safe_Release(pInstance);

	}
	return pInstance;
}



void CMyButton::Free()
{

	CKeyMgr::Get_Instance()->UnRegisterObserver(m_tDesc.m_eSceneID, this);
	Safe_Release(m_pShader);
	Safe_Release(m_pVIBuffer);
	Safe_Release(m_pTransform);
	Safe_Release(m_pTexture);
	Safe_Release(m_pRcCollider);

	CGameObject::Free();

}

HRESULT CMyButton::OnKeyDown(_int KeyCode)
{
	if (!m_bActive)
		return S_OK;

	POINT cursorPos;
	GetCursorPos(&cursorPos);
	ScreenToClient(g_hWnd, &cursorPos);

	if (PtInRect(&m_pRcCollider->Get_Rect(), cursorPos))
	{
		//리스너 목록을 호출한다.
		for (auto& listener : m_vecOnListener)
		{
			if (listener)
				listener();
		}
		//싱글 리스너를 호출한다.
		if (m_Listener)
			m_Listener();

	}

	return S_OK;
}

_uint CMyButton::Get_Depth()
{
	return m_tDesc.m_iDepth;
}


