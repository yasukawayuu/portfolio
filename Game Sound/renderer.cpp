
#include "main.h"
#include "renderer.h"
#include <io.h>

Renderer* Renderer::m_pInstance{};




void Renderer::Init()
{
	HRESULT hr = S_OK;




	// �f�o�C�X�A�X���b�v�`�F�[���쐬
	DXGI_SWAP_CHAIN_DESC swapChainDesc{};
	swapChainDesc.BufferCount = 1;
	swapChainDesc.BufferDesc.Width = SCREEN_WIDTH;
	swapChainDesc.BufferDesc.Height = SCREEN_HEIGHT;
	swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	swapChainDesc.BufferDesc.RefreshRate.Numerator = 60;
	swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainDesc.OutputWindow = GetWindow();
	swapChainDesc.SampleDesc.Count = 4;
	swapChainDesc.SampleDesc.Quality = 0;
	swapChainDesc.Windowed = TRUE;

	hr = D3D11CreateDeviceAndSwapChain(NULL,
		D3D_DRIVER_TYPE_HARDWARE,
		NULL,
		0,
		NULL,
		0,
		D3D11_SDK_VERSION,
		&swapChainDesc,
		&m_SwapChain,
		&m_Device,
		&m_FeatureLevel,
		&m_DeviceContext);



	// �����_�[�^�[�Q�b�g�r���[�쐬
	ID3D11Texture2D* renderTarget{};
	m_SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&renderTarget);
	m_Device->CreateRenderTargetView(renderTarget, NULL, &m_RenderTargetView);
	renderTarget->Release();


	// �f�v�X�X�e���V���o�b�t�@�쐬
	ID3D11Texture2D* depthStencile{};
	D3D11_TEXTURE2D_DESC textureDesc{};
	textureDesc.Width = swapChainDesc.BufferDesc.Width;
	textureDesc.Height = swapChainDesc.BufferDesc.Height;
	textureDesc.MipLevels = 1;
	textureDesc.ArraySize = 1;
	textureDesc.Format = DXGI_FORMAT_D16_UNORM;
	textureDesc.SampleDesc = swapChainDesc.SampleDesc;
	textureDesc.Usage = D3D11_USAGE_DEFAULT;
	textureDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	textureDesc.CPUAccessFlags = 0;
	textureDesc.MiscFlags = 0;
	m_Device->CreateTexture2D(&textureDesc, NULL, &depthStencile);

	// �f�v�X�X�e���V���r���[�쐬
	D3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc{};
	depthStencilViewDesc.Format = textureDesc.Format;
	depthStencilViewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2DMS;
	depthStencilViewDesc.Flags = 0;
	m_Device->CreateDepthStencilView(depthStencile, &depthStencilViewDesc, &m_DepthStencilView);
	depthStencile->Release();


	m_DeviceContext->OMSetRenderTargets(1, &m_RenderTargetView, m_DepthStencilView);

	// �r���[�|�[�g�ݒ�
	D3D11_VIEWPORT viewport;
	viewport.Width = (FLOAT)SCREEN_WIDTH;
	viewport.Height = (FLOAT)SCREEN_HEIGHT;
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;
	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	m_DeviceContext->RSSetViewports(1, &viewport);



	// ���X�^���C�U�X�e�[�g�ݒ�
	D3D11_RASTERIZER_DESC rasterizerDesc{};
	rasterizerDesc.FillMode = D3D11_FILL_SOLID;
	rasterizerDesc.CullMode = D3D11_CULL_BACK;
	rasterizerDesc.DepthClipEnable = TRUE;
	rasterizerDesc.MultisampleEnable = FALSE;

	ID3D11RasterizerState* rs;
	m_Device->CreateRasterizerState(&rasterizerDesc, &rs);

	m_DeviceContext->RSSetState(rs);

	// �u�����h�X�e�[�g�ݒ�
	D3D11_BLEND_DESC blendDesc{};
	blendDesc.AlphaToCoverageEnable = FALSE;
	blendDesc.IndependentBlendEnable = FALSE;
	blendDesc.RenderTarget[0].BlendEnable = TRUE;
	blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	blendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	blendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	blendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
	blendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	blendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

	m_Device->CreateBlendState(&blendDesc, &m_BlendState);

	blendDesc.AlphaToCoverageEnable = TRUE;
	m_Device->CreateBlendState(&blendDesc, &m_BlendStateATC);

	float blendFactor[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
	m_DeviceContext->OMSetBlendState(m_BlendState, blendFactor, 0xffffffff);





	// �f�v�X�X�e���V���X�e�[�g�ݒ�
	D3D11_DEPTH_STENCIL_DESC depthStencilDesc{};
	depthStencilDesc.DepthEnable = TRUE;
	depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	depthStencilDesc.DepthFunc = D3D11_COMPARISON_LESS_EQUAL;
	depthStencilDesc.StencilEnable = FALSE;

	m_Device->CreateDepthStencilState(&depthStencilDesc, &m_DepthStateEnable);//�[�x�L���X�e�[�g

	//depthStencilDesc.DepthEnable = FALSE;
	depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ZERO;
	m_Device->CreateDepthStencilState(&depthStencilDesc, &m_DepthStateDisable);//�[�x�����X�e�[�g

	m_DeviceContext->OMSetDepthStencilState(m_DepthStateEnable, NULL);




	// �T���v���[�X�e�[�g�ݒ�
	D3D11_SAMPLER_DESC samplerDesc{};
	samplerDesc.Filter = D3D11_FILTER_ANISOTROPIC;
	samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.MaxAnisotropy = 4;
	samplerDesc.MaxLOD = D3D11_FLOAT32_MAX;

	ID3D11SamplerState* samplerState{};
	m_Device->CreateSamplerState(&samplerDesc, &samplerState);

	m_DeviceContext->PSSetSamplers(0, 1, &samplerState);



	// �萔�o�b�t�@����
	D3D11_BUFFER_DESC bufferDesc{};
	bufferDesc.ByteWidth = sizeof(D3DXMATRIX);
	bufferDesc.Usage = D3D11_USAGE_DEFAULT;
	bufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bufferDesc.CPUAccessFlags = 0;
	bufferDesc.MiscFlags = 0;
	bufferDesc.StructureByteStride = sizeof(float);

	m_Device->CreateBuffer(&bufferDesc, NULL, &m_WorldBuffer);
	m_DeviceContext->VSSetConstantBuffers(0, 1, &m_WorldBuffer);

	m_Device->CreateBuffer(&bufferDesc, NULL, &m_ViewBuffer);
	m_DeviceContext->VSSetConstantBuffers(1, 1, &m_ViewBuffer);

	m_Device->CreateBuffer(&bufferDesc, NULL, &m_ProjectionBuffer);
	m_DeviceContext->VSSetConstantBuffers(2, 1, &m_ProjectionBuffer);


	bufferDesc.ByteWidth = sizeof(MATERIAL);

	m_Device->CreateBuffer(&bufferDesc, NULL, &m_MaterialBuffer);
	m_DeviceContext->VSSetConstantBuffers(3, 1, &m_MaterialBuffer);
	m_DeviceContext->PSSetConstantBuffers(3, 1, &m_MaterialBuffer);


	bufferDesc.ByteWidth = sizeof(LIGHT);

	m_Device->CreateBuffer(&bufferDesc, NULL, &m_LightBuffer);
	m_DeviceContext->VSSetConstantBuffers(4, 1, &m_LightBuffer);
	m_DeviceContext->PSSetConstantBuffers(4, 1, &m_LightBuffer);

	bufferDesc.ByteWidth = sizeof(POINTLIGHT);

	m_Device->CreateBuffer(&bufferDesc, NULL, &m_PointLightBuffer);
	m_DeviceContext->VSSetConstantBuffers(8, 1, &m_PointLightBuffer);
	m_DeviceContext->PSSetConstantBuffers(8, 1, &m_PointLightBuffer);

	bufferDesc.ByteWidth = sizeof(SPOTLIGHT);

	m_Device->CreateBuffer(&bufferDesc, NULL, &m_SpotLightBuffer);
	m_DeviceContext->VSSetConstantBuffers(9, 1, &m_SpotLightBuffer);
	m_DeviceContext->PSSetConstantBuffers(9, 1, &m_SpotLightBuffer);

	bufferDesc.ByteWidth = sizeof(D3DXVECTOR4);

	m_Device->CreateBuffer(&bufferDesc, NULL, &m_CameraBuffer);
	m_DeviceContext->PSSetConstantBuffers(5, 1, &m_CameraBuffer);

	bufferDesc.ByteWidth = sizeof(PARAMETER);

	m_Device->CreateBuffer(&bufferDesc, NULL, &m_ParameterBuffer);
	m_DeviceContext->VSSetConstantBuffers(6, 1, &m_ParameterBuffer);
	m_DeviceContext->PSSetConstantBuffers(6, 1, &m_ParameterBuffer);

	bufferDesc.ByteWidth = sizeof(FOG);

	m_Device->CreateBuffer(&bufferDesc, NULL, &m_FogBuffer);
	m_DeviceContext->PSSetConstantBuffers(7, 1, &m_FogBuffer);




	// �}�e���A��������
	MATERIAL material{};
	material.Diffuse = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
	material.Ambient = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
	material.Emission = D3DXCOLOR(0.0f, 0.0f, 0.0f,1.0f);
	SetMaterial(material);

	m_ShadoSize = 960.0f;
	{
		// �f�v�X�X�e���V���o�b�t�@�쐬
		ID3D11Texture2D* depthStencile{};
		D3D11_TEXTURE2D_DESC textureDesc{};
		textureDesc.Width = (FLOAT)SCREEN_WIDTH * 2;
		textureDesc.Height = (FLOAT)SCREEN_HEIGHT * 2;
		textureDesc.MipLevels = 1;
		textureDesc.ArraySize = 1;
		textureDesc.Format = DXGI_FORMAT_R32_TYPELESS;
		textureDesc.SampleDesc.Count = 1;
		textureDesc.SampleDesc.Quality = 0;
		textureDesc.Usage = D3D11_USAGE_DEFAULT;
		textureDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL | D3D11_BIND_SHADER_RESOURCE;;
		textureDesc.CPUAccessFlags = 0;
		textureDesc.MiscFlags = 0;
		m_Device->CreateTexture2D(&textureDesc, NULL, &depthStencile);

		// �f�v�X�X�e���V���r���[�쐬
		D3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc{};
		depthStencilViewDesc.Format = DXGI_FORMAT_D32_FLOAT;
		depthStencilViewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2DMS;
		depthStencilViewDesc.Texture2D.MipSlice = 0;
		m_Device->CreateDepthStencilView(depthStencile, &depthStencilViewDesc, &m_DepthShadowDepthStencilView);

		D3D11_SHADER_RESOURCE_VIEW_DESC shaderResourceViewDesc{};
		shaderResourceViewDesc.Format = DXGI_FORMAT_R32_FLOAT;
		shaderResourceViewDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2DMS;
		shaderResourceViewDesc.Texture2D.MipLevels = 1;
		m_Device->CreateShaderResourceView(depthStencile, &shaderResourceViewDesc, &m_DepthShadowShaderResourceView);


		depthStencile->Release();
	}

	{
		for (int i = 0; i < 6; i++)
		{
			// �f�v�X�X�e���V���o�b�t�@�쐬
			ID3D11Texture2D* depthStencile{};
			D3D11_TEXTURE2D_DESC textureDesc{};
			textureDesc.Width = (FLOAT)SCREEN_WIDTH * 2;
			textureDesc.Height = (FLOAT)SCREEN_HEIGHT * 2;
			textureDesc.MipLevels = 1;
			textureDesc.ArraySize = 1;
			textureDesc.Format = DXGI_FORMAT_R32_TYPELESS;
			textureDesc.SampleDesc.Count = 1;
			textureDesc.SampleDesc.Quality = 0;
			textureDesc.Usage = D3D11_USAGE_DEFAULT;
			textureDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL | D3D11_BIND_SHADER_RESOURCE;;
			textureDesc.CPUAccessFlags = 0;
			textureDesc.MiscFlags = 0;
			m_Device->CreateTexture2D(&textureDesc, NULL, &depthStencile);

			// �f�v�X�X�e���V���r���[�쐬
			D3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc{};
			depthStencilViewDesc.Format = DXGI_FORMAT_D32_FLOAT;
			depthStencilViewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2DMS;
			depthStencilViewDesc.Texture2D.MipSlice = 0;
			m_Device->CreateDepthStencilView(depthStencile, &depthStencilViewDesc, &m_DepthPointShadowDepthStencilView[i]);

			D3D11_SHADER_RESOURCE_VIEW_DESC shaderResourceViewDesc{};
			shaderResourceViewDesc.Format = DXGI_FORMAT_R32_FLOAT;
			shaderResourceViewDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2DMS;
			shaderResourceViewDesc.Texture2D.MipLevels = 1;
			m_Device->CreateShaderResourceView(depthStencile, &shaderResourceViewDesc, &m_DepthPointShadowShaderResourceView[i]);


			depthStencile->Release();
		}
		

		
	}

	{
		// �f�v�X�X�e���V���o�b�t�@�쐬
		ID3D11Texture2D* depthStencile{};
		D3D11_TEXTURE2D_DESC textureDesc{};
		textureDesc.Width = (FLOAT)SCREEN_WIDTH * 2;
		textureDesc.Height = (FLOAT)SCREEN_HEIGHT * 2;
		textureDesc.MipLevels = 1;
		textureDesc.ArraySize = 1;
		textureDesc.Format = DXGI_FORMAT_R32_TYPELESS;
		textureDesc.SampleDesc.Count = 1;
		textureDesc.SampleDesc.Quality = 0;
		textureDesc.Usage = D3D11_USAGE_DEFAULT;
		textureDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL | D3D11_BIND_SHADER_RESOURCE;;
		textureDesc.CPUAccessFlags = 0;
		textureDesc.MiscFlags = 0;
		m_Device->CreateTexture2D(&textureDesc, NULL, &depthStencile);

		// �f�v�X�X�e���V���r���[�쐬
		D3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc{};
		depthStencilViewDesc.Format = DXGI_FORMAT_D32_FLOAT;
		depthStencilViewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2DMS;
		depthStencilViewDesc.Texture2D.MipSlice = 0;
		m_Device->CreateDepthStencilView(depthStencile, &depthStencilViewDesc, &m_DepthSpotShadowDepthStencilView);

		D3D11_SHADER_RESOURCE_VIEW_DESC shaderResourceViewDesc{};
		shaderResourceViewDesc.Format = DXGI_FORMAT_R32_FLOAT;
		shaderResourceViewDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2DMS;
		shaderResourceViewDesc.Texture2D.MipLevels = 1;
		m_Device->CreateShaderResourceView(depthStencile, &shaderResourceViewDesc, &m_DepthSpotShadowShaderResourceView);


		depthStencile->Release();
	}

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	ImGui::StyleColorsDark();
	ImGui_ImplWin32_Init(GetWindow());
	ImGui_ImplDX11_Init(m_Device, m_DeviceContext);
}



void Renderer::Uninit()
{
	ImGui_ImplDX11_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();

	if (m_WorldBuffer != NULL)
	{
		m_WorldBuffer->Release();
		m_WorldBuffer = NULL;
	}

	if (m_ViewBuffer != NULL)
	{
		m_ViewBuffer->Release();
		m_ViewBuffer = NULL;
	}

	if (m_ProjectionBuffer != NULL)
	{
		m_ProjectionBuffer->Release();
		m_ProjectionBuffer = NULL;
	}

	if (m_LightBuffer != NULL)
	{
		m_LightBuffer->Release();
		m_LightBuffer = NULL;
	}

	if (m_PointLightBuffer != NULL)
	{
		m_ParameterBuffer->Release();
		m_PointLightBuffer = NULL;
	}

	if (m_SpotLightBuffer != NULL)
	{
		m_SpotLightBuffer->Release();
		m_SpotLightBuffer = NULL;
	}

	if (m_MaterialBuffer != NULL)
	{
		m_MaterialBuffer->Release();
		m_MaterialBuffer = NULL;
	}

	if (m_CameraBuffer != NULL)
	{
		m_CameraBuffer->Release();
		m_CameraBuffer = NULL;
	}

	if (m_ParameterBuffer != NULL)
	{
		m_ParameterBuffer->Release();
		m_MaterialBuffer = NULL;
	}

	if (m_FogBuffer != NULL)
	{
		m_FogBuffer->Release();
		m_FogBuffer = NULL;
	}

	if (m_DeviceContext != NULL)
	{
		m_DeviceContext->ClearState();
		m_DeviceContext = NULL;
	}

	if (m_RenderTargetView != NULL)
	{
		m_RenderTargetView->Release();
		m_RenderTargetView = NULL;
	}

	if (m_SwapChain != NULL)
	{
		m_SwapChain->Release();
		m_SwapChain = NULL;
	}

	if (m_DeviceContext != NULL)
	{
		m_DeviceContext->Release();
		m_DeviceContext = NULL;
	}

	if (m_Device != NULL)
	{
		m_Device->Release();
		m_Device = NULL;
	}

	m_DepthShadowDepthStencilView->Release();
	m_DepthShadowShaderResourceView->Release();

	for (int i = 0; i < 6; i++)
	{
		m_DepthPointShadowDepthStencilView[i]->Release();
		m_DepthPointShadowShaderResourceView[i]->Release();
	}

	m_DepthSpotShadowDepthStencilView->Release();
	m_DepthSpotShadowShaderResourceView->Release();
}




void Renderer::Begin()
{
	m_DeviceContext->OMSetRenderTargets(1, &m_RenderTargetView, m_DepthStencilView);

	float clearColor[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
	m_DeviceContext->ClearRenderTargetView(m_RenderTargetView, clearColor);
	m_DeviceContext->ClearDepthStencilView(m_DepthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);
}

void Renderer::BeginDepth()
{
	m_DeviceContext->OMSetRenderTargets(0, NULL, m_DepthShadowDepthStencilView);
	m_DeviceContext->ClearDepthStencilView(m_DepthShadowDepthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);
}

void Renderer::BeginDepthPoint(int index)
{

	m_DeviceContext->OMSetRenderTargets(0, NULL, m_DepthPointShadowDepthStencilView[index]);
	m_DeviceContext->ClearDepthStencilView(m_DepthPointShadowDepthStencilView[index], D3D11_CLEAR_DEPTH, 1.0f, 0);
}

void Renderer::BeginDepthSpot()
{
	m_DeviceContext->OMSetRenderTargets(0, NULL, m_DepthSpotShadowDepthStencilView);
	m_DeviceContext->ClearDepthStencilView(m_DepthSpotShadowDepthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);
}


void Renderer::End()
{
	m_SwapChain->Present(1, 0);
}




void Renderer::SetDepthEnable(bool Enable)
{
	if (Enable)
		m_DeviceContext->OMSetDepthStencilState(m_DepthStateEnable, NULL);
	else
		m_DeviceContext->OMSetDepthStencilState(m_DepthStateDisable, NULL);

}



void Renderer::SetATCEnable(bool Enable)
{
	float blendFactor[4] = { 0.0f, 0.0f, 0.0f, 0.0f };

	if (Enable)
		m_DeviceContext->OMSetBlendState(m_BlendStateATC, blendFactor, 0xffffffff);
	else
		m_DeviceContext->OMSetBlendState(m_BlendState, blendFactor, 0xffffffff);

}

void Renderer::SetWorldViewProjection2D()
{
	D3DXMATRIX world;
	D3DXMatrixIdentity(&world);
	D3DXMatrixTranspose(&world, &world);

	m_DeviceContext->UpdateSubresource(m_WorldBuffer, 0, NULL, &world, 0, 0);

	D3DXMATRIX view;
	D3DXMatrixIdentity(&view);
	D3DXMatrixTranspose(&view, &view);
	m_DeviceContext->UpdateSubresource(m_ViewBuffer, 0, NULL, &view, 0, 0);

	D3DXMATRIX projection;
	D3DXMatrixOrthoOffCenterLH(&projection, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f, 0.0f, 1.0f);
	D3DXMatrixTranspose(&projection, &projection);
	m_DeviceContext->UpdateSubresource(m_ProjectionBuffer, 0, NULL, &projection, 0, 0);

}


void Renderer::SetWorldMatrix(D3DXMATRIX* WorldMatrix)
{
	D3DXMATRIX world;
	D3DXMatrixTranspose(&world, WorldMatrix);
	m_DeviceContext->UpdateSubresource(m_WorldBuffer, 0, NULL, &world, 0, 0);
}

void Renderer::SetViewMatrix(D3DXMATRIX* ViewMatrix)
{
	D3DXMATRIX view;
	D3DXMatrixTranspose(&view, ViewMatrix);
	m_DeviceContext->UpdateSubresource(m_ViewBuffer, 0, NULL, &view, 0, 0);
}

void Renderer::SetProjectionMatrix(D3DXMATRIX* ProjectionMatrix)
{
	D3DXMATRIX projection;
	D3DXMatrixTranspose(&projection, ProjectionMatrix);
	m_DeviceContext->UpdateSubresource(m_ProjectionBuffer, 0, NULL, &projection, 0, 0);
}



void Renderer::SetMaterial(MATERIAL Material)
{
	m_DeviceContext->UpdateSubresource(m_MaterialBuffer, 0, NULL, &Material, 0, 0);
}

void Renderer::SetLight(LIGHT Light)
{
	D3DXMatrixTranspose(&Light.ViewMatrix, &Light.ViewMatrix);
	D3DXMatrixTranspose(&Light.ProjectionMatrix, &Light.ProjectionMatrix);

	m_DeviceContext->UpdateSubresource(m_LightBuffer, 0, NULL, &Light, 0, 0);
}

void Renderer::SetPointLight(POINTLIGHT PointLight)
{
	for(int i = 0; i < 6 ; i++)
	D3DXMatrixTranspose(&PointLight.ViewMatrix[i], &PointLight.ViewMatrix[i]);
	D3DXMatrixTranspose(&PointLight.ProjectionMatrix, &PointLight.ProjectionMatrix);

	m_DeviceContext->UpdateSubresource(m_PointLightBuffer, 0, NULL, &PointLight, 0, 0);
}

void Renderer::SetSpotLight(SPOTLIGHT SpotLight)
{
	D3DXMatrixTranspose(&SpotLight.ViewMatrix, &SpotLight.ViewMatrix);
	D3DXMatrixTranspose(&SpotLight.ProjectionMatrix, &SpotLight.ProjectionMatrix);

	m_DeviceContext->UpdateSubresource(m_SpotLightBuffer, 0, NULL, &SpotLight, 0, 0);
}

void Renderer::SetCameraPosition(D3DXVECTOR3 CameraPosition)
{
	D3DXVECTOR4 cpos(CameraPosition.x, CameraPosition.y, CameraPosition.z, 1.0f);
	m_DeviceContext->UpdateSubresource(m_CameraBuffer, 0, NULL, &cpos, 0, 0);
}

void Renderer::SetParameter(PARAMETER param)
{
	m_DeviceContext->UpdateSubresource(m_ParameterBuffer, 0, NULL, &param, 0, 0);
}


void Renderer::SetFog(FOG Fog)
{
	m_DeviceContext->UpdateSubresource(m_FogBuffer, 0, NULL, &Fog, 0, 0);
}





void Renderer::CreateVertexShader(ID3D11VertexShader** VertexShader, ID3D11InputLayout** VertexLayout, const char* FileName)
{

	FILE* file;
	long int fsize;

	file = fopen(FileName, "rb");
	assert(file);

	fsize = _filelength(_fileno(file));
	unsigned char* buffer = new unsigned char[fsize];
	fread(buffer, fsize, 1, file);
	fclose(file);

	m_Device->CreateVertexShader(buffer, fsize, NULL, VertexShader);


	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "NORMAL",   0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 4 * 3, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR",    0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 4 * 6, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 4 * 10, D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};
	UINT numElements = ARRAYSIZE(layout);

	m_Device->CreateInputLayout(layout,
		numElements,
		buffer,
		fsize,
		VertexLayout);

	delete[] buffer;
}



void Renderer::CreatePixelShader(ID3D11PixelShader** PixelShader, const char* FileName)
{
	FILE* file;
	long int fsize;

	file = fopen(FileName, "rb");
	assert(file);

	fsize = _filelength(_fileno(file));
	unsigned char* buffer = new unsigned char[fsize];
	fread(buffer, fsize, 1, file);
	fclose(file);

	m_Device->CreatePixelShader(buffer, fsize, NULL, PixelShader);

	delete[] buffer;
}

void Renderer::SetDefaultViewport()
{
	D3D11_VIEWPORT viewport;
	viewport.Width = (FLOAT)SCREEN_WIDTH;
	viewport.Height = (FLOAT)SCREEN_HEIGHT;
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;
	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	m_DeviceContext->RSSetViewports(1, &viewport);
}

void Renderer::SetDepthViewport()
{
	D3D11_VIEWPORT viewport;
	viewport.Width = (FLOAT)SCREEN_WIDTH * 2;
	viewport.Height = (FLOAT)SCREEN_HEIGHT * 2 ;
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;
	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	m_DeviceContext->RSSetViewports(1, &viewport);
}

void Renderer::SetDefaultSamplerState
()
{
	D3D11_SAMPLER_DESC samplerDesc{};
	samplerDesc.Filter = D3D11_FILTER_ANISOTROPIC;
	samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.MaxAnisotropy = 4;
	samplerDesc.MaxLOD = D3D11_FLOAT32_MAX;

	ID3D11SamplerState* samplerState{};
	m_Device->CreateSamplerState(&samplerDesc, &samplerState);

	m_DeviceContext->PSSetSamplers(0, 1, &samplerState);
}

void Renderer::SetDepthSamplerState()
{
	D3D11_SAMPLER_DESC samplerDesc{};
	samplerDesc.Filter = D3D11_FILTER_ANISOTROPIC;
	samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
	samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
	samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
	samplerDesc.MaxAnisotropy = 4;
	samplerDesc.MaxLOD = D3D11_FLOAT32_MAX;

	ID3D11SamplerState* samplerState{};
	m_Device->CreateSamplerState(&samplerDesc, &samplerState);

	m_DeviceContext->PSSetSamplers(0, 1, &samplerState);
}