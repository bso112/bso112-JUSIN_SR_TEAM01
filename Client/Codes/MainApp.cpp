#include "stdafx.h"
#include "..\Headers\MainApp.h"

#include "BackGround.h"
#include "Scene_Loading.h"
#include "Camera_Free.h"
#include "Brick.h"
#include "MyButton.h"
#include "Wall.h"
#include "Field.h"
#include "Goal.h"
#include "MyImage.h"
#include "GameEndPanel.h"
#include "Image3D.h"
USING(Client)

CMainApp::CMainApp()
	: m_pManagement(CManagement::Get_Instance())
{
	Safe_AddRef(m_pManagement);

}

HRESULT CMainApp::Ready_MainApp()
{
	if (FAILED(Ready_Default_Setting()))
		return E_FAIL;

	if (FAILED(Ready_Default_Component()))
		return E_FAIL;

	if (FAILED(Ready_Default_GameObject()))
		return E_FAIL;

	if (FAILED(Ready_Start_Scene(SCENE_STAGE)))
		return E_FAIL;

	return S_OK;
}

_int CMainApp::Update_MainApp(_double TimeDelta)
{
	if (0x8000 & GetKeyState(VK_LBUTTON))
	{
		int a = 10;
	}

	if (nullptr == m_pManagement)
		return -1;

	CGameManager::Get_Instance()->Set_PickObject(false);
	return m_pManagement->Update_Engine(TimeDelta);
}

HRESULT CMainApp::Render_MainApp()
{
	if (nullptr == m_pGraphic_Device ||
		nullptr == m_pManagement ||
		nullptr == m_pRenderer)
		return E_FAIL;



	m_pGraphic_Device->Clear(0, nullptr, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL, D3DXCOLOR(0.f, 0.f, 1.f, 1.f), 1.f, 0);

	m_pGraphic_Device->BeginScene();

	if (FAILED(m_pRenderer->Draw_RenderGroup()))
		return E_FAIL;

	if (FAILED(m_pManagement->Render_Engine()))
		return E_FAIL;

	m_pGraphic_Device->EndScene();

	m_pGraphic_Device->Present(nullptr, nullptr, 0, nullptr);

	return S_OK;
}

HRESULT CMainApp::Ready_Default_Setting()
{
	if (nullptr == m_pManagement)
		return E_FAIL;

	// 엔진 초기화.
	if (FAILED(m_pManagement->Ready_Engine(SCENE_END)))
		return E_FAIL;

	// 장치 초기화.
	if (FAILED(m_pManagement->Ready_Graphic_Device(g_hWnd, CGraphic_Device::TYPE_WIN, g_iWinSizeX, g_iWinSizeY, &m_pGraphic_Device)))
		return E_FAIL;

	return S_OK;
}

HRESULT CMainApp::Ready_Start_Scene(SCENEID eNextSceneID)
{
	if (nullptr == m_pManagement)
		return E_FAIL;

	if (FAILED(m_pManagement->SetUp_CurrentScene(CScene_Loading::Create(m_pGraphic_Device, eNextSceneID), eNextSceneID)))
		return E_FAIL;

	return S_OK;
}

HRESULT CMainApp::Ready_Default_GameObject()
{
	if (nullptr == m_pManagement)
		return E_FAIL;

	if (FAILED(m_pManagement->Add_GameObject_Prototype(SCENE_STATIC, L"GameObject_BackGround", CBackGround::Create(m_pGraphic_Device))))
		return E_FAIL;

	if (FAILED(m_pManagement->Add_GameObject_Prototype(SCENE_STATIC, L"GameObject_Camera_Free", CCamera_Free::Create(m_pGraphic_Device))))
		return E_FAIL;

	if (FAILED(m_pManagement->Add_GameObject_Prototype(SCENE_STATIC, L"GameObject_Brick", CBrick::Create(m_pGraphic_Device))))
		return E_FAIL;
	if (FAILED(m_pManagement->Add_GameObject_Prototype(SCENE_STATIC, L"GameObject_MyButton", CMyButton::Create(m_pGraphic_Device))))
		return E_FAIL;

	if (FAILED(m_pManagement->Add_GameObject_Prototype(SCENE_STATIC, L"GameObject_MyImage", CMyImage::Create(m_pGraphic_Device))))
		return E_FAIL;

	if (FAILED(m_pManagement->Add_GameObject_Prototype(SCENE_STATIC, L"GameObject_Field", CField::Create(m_pGraphic_Device))))
		return E_FAIL;

	if (FAILED(m_pManagement->Add_GameObject_Prototype(SCENE_STATIC, L"GameObject_Wall", CWall::Create(m_pGraphic_Device))))
		return E_FAIL;
	if (FAILED(m_pManagement->Add_GameObject_Prototype(SCENE_STATIC, L"GameObject_Background", CBackGround::Create(m_pGraphic_Device))))
		return E_FAIL;

	if (FAILED(m_pManagement->Add_GameObject_Prototype(SCENE_STATIC, L"GameObject_Goal", CGoal::Create(m_pGraphic_Device))))
		return E_FAIL;

	if (FAILED(m_pManagement->Add_GameObject_Prototype(SCENE_STATIC, L"GameObject_GameEndPanel", CGameEndPanel::Create(m_pGraphic_Device))))
		return E_FAIL;

	if (FAILED(m_pManagement->Add_GameObject_Prototype(SCENE_STATIC, L"GameObject_Image3D", CImage3D::Create(m_pGraphic_Device))))
		return E_FAIL;







	return S_OK;
}

HRESULT CMainApp::Ready_Default_Component()
{
	if (nullptr == m_pManagement)
		return E_FAIL;

	if (FAILED(m_pManagement->Add_Component_Prototype(SCENE_STATIC, L"Component_Renderer", m_pRenderer = CRenderer::Create(m_pGraphic_Device))))
		return E_FAIL;

	Safe_AddRef(m_pRenderer);

	if (FAILED(m_pManagement->Add_Component_Prototype(SCENE_STATIC, L"Component_Transform", CTransform::Create(m_pGraphic_Device))))
		return E_FAIL;

	if (FAILED(m_pManagement->Add_Component_Prototype(SCENE_STATIC, L"Component_VIBuffer_Rect", CVIBuffer_Rect::Create(m_pGraphic_Device))))
		return E_FAIL;


	if (FAILED(m_pManagement->Add_Component_Prototype(SCENE_STATIC, L"Component_VIBuffer_Cube", CVIBuffer_Cube::Create(m_pGraphic_Device))))
		return E_FAIL;

	if (FAILED(m_pManagement->Add_Component_Prototype(SCENE_STATIC, L"Component_VIBuffer_ViewPort", CVIBuffer_ViewPort::Create(m_pGraphic_Device))))
		return E_FAIL;


	if (FAILED(m_pManagement->Add_Component_Prototype(SCENE_STATIC, L"Component_Shader_Rect", CShader::Create(m_pGraphic_Device, L"../Bin/ShaderFiles/Shader_Rect.fx"))))
		return E_FAIL;

	if (FAILED(m_pManagement->Add_Component_Prototype(SCENE_STATIC, L"Component_Shader_ViewPort", CShader::Create(m_pGraphic_Device, L"../Bin/ShaderFiles/Shader_ViewPort.fx"))))
		return E_FAIL;


	if (FAILED(m_pManagement->Add_Component_Prototype(SCENE_STATIC, L"Component_Collider_Rect", CCollider_Rect::Create(m_pGraphic_Device))))
		return E_FAIL;

	if (FAILED(m_pManagement->Add_Component_Prototype(SCENE_STATIC, L"Component_Texture_Wall", CTexture::Create(m_pGraphic_Device, L"../Bin/Resources/Textures/Wall/Wall%d.png", 1))))
		return E_FAIL;

	if (FAILED(m_pManagement->Add_Component_Prototype(SCENE_STATIC, L"Component_Texture_Background", CTexture::Create(m_pGraphic_Device, L"../Bin/Resources/Textures/Background/background%d.jpg", 3))))
		return E_FAIL;

	if (FAILED(m_pManagement->Add_Component_Prototype(SCENE_STATIC, L"Component_Texture_Brick", CTexture::Create(m_pGraphic_Device, L"../Bin/Resources/Textures/Brick/brick%d.jpg", 5))))
		return E_FAIL;

	if (FAILED(m_pManagement->Add_Component_Prototype(SCENE_STATIC, L"Component_Texture_Btn", CTexture::Create(m_pGraphic_Device, L"../../Client/Bin/Resources/Textures/Button/btn%d.png", 2))))
		return E_FAIL;


	if (FAILED(m_pManagement->Add_Component_Prototype(SCENE_STATIC, L"Component_Texture_Goal", CTexture::Create(m_pGraphic_Device, L"../../Client/Bin/Resources/Textures/Goal/goal%d.png", 2))))
		return E_FAIL;

	if (FAILED(m_pManagement->Add_Component_Prototype(SCENE_STATIC, L"Component_Texture_Banner", CTexture::Create(m_pGraphic_Device, L"../../Client/Bin/Resources/Textures/Banner/banner%d.png", 1))))
		return E_FAIL;

	if (FAILED(m_pManagement->Add_Component_Prototype(SCENE_STATIC, L"Component_BoxCollider", CCollider_Box::Create(m_pGraphic_Device))))
		return E_FAIL;
	return S_OK;
}

CMainApp * CMainApp::Create()
{
	CMainApp*	pInstance = new CMainApp();

	if (FAILED(pInstance->Ready_MainApp()))
	{
		MSG_BOX("Failed To Create CMainApp");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CMainApp::Free()
{
	Safe_Release(m_pRenderer);

	Safe_Release(m_pGraphic_Device);

	Safe_Release(m_pManagement);

	CGameManager::Get_Instance()->Destroy_Instance();

	CManagement::Release_Engine();
}