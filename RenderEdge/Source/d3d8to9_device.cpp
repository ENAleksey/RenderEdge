/**
 * Copyright (C) 2015 Patrick Mours. All rights reserved.
 * License: https://github.com/crosire/d3d8to9#license
 */

#include <d3d9.h>
#include <d3dx9.h>

#include "d3d8to9.hpp"
#include <regex>
#include <assert.h>

#include "Engine.h"

struct VertexShaderInfo
{
	IDirect3DVertexShader9 *Shader;
	IDirect3DVertexDeclaration9 *Declaration;
};

// IDirect3DDevice8
Direct3DDevice8::Direct3DDevice8(Direct3D8 *d3d, IDirect3DDevice9 *ProxyInterface, BOOL EnableZBufferDiscarding) :
	D3D(d3d), ProxyInterface(ProxyInterface), ZBufferDiscarding(EnableZBufferDiscarding)
{
	D3D->AddRef();
}
Direct3DDevice8::~Direct3DDevice8()
{
	ProxyInterface->Release();
	D3D->Release();
}

HRESULT STDMETHODCALLTYPE Direct3DDevice8::QueryInterface(REFIID riid, void **ppvObj)
{
	if (ppvObj == nullptr)
	{
		return E_POINTER;
	}

	if (riid == __uuidof(this) ||
		riid == __uuidof(IUnknown))
	{
		AddRef();

		*ppvObj = this;

		return S_OK;
	}

	return ProxyInterface->QueryInterface(riid, ppvObj);
}
ULONG STDMETHODCALLTYPE Direct3DDevice8::AddRef()
{
	return InterlockedIncrement(&RefCount);
}
ULONG STDMETHODCALLTYPE Direct3DDevice8::Release()
{
	ULONG LastRefCount = InterlockedExchange(&RefCount, RefCount);
	
	Direct3DSurface8 *const RenderTarget = CurrentRenderTarget;
	Direct3DSurface8 *const DepthStencil = CurrentDepthStencilSurface;

	if (RenderTarget != nullptr &&
		DepthStencil != nullptr &&
		LastRefCount == 3)
	{
		CurrentRenderTarget = nullptr;
		CurrentDepthStencilSurface = nullptr;
		RenderTarget->Release();
		DepthStencil->Release();
	}
	else if (RenderTarget != nullptr &&
		LastRefCount == 2)
	{
		CurrentRenderTarget = nullptr;
		RenderTarget->Release();
	}
	else if (DepthStencil != nullptr &&
		LastRefCount == 2)
	{
		CurrentDepthStencilSurface = nullptr;
		DepthStencil->Release();
	}

	LastRefCount = InterlockedDecrement(&RefCount);

	if (LastRefCount == 0)
	{
		if (MainEngine != nullptr)
		{
			delete MainEngine;
			MainEngine = nullptr;
		}

		delete this;
	}

	return LastRefCount;
}

HRESULT STDMETHODCALLTYPE Direct3DDevice8::TestCooperativeLevel()
{
	return ProxyInterface->TestCooperativeLevel();
}
UINT STDMETHODCALLTYPE Direct3DDevice8::GetAvailableTextureMem()
{
	return ProxyInterface->GetAvailableTextureMem();
}
HRESULT STDMETHODCALLTYPE Direct3DDevice8::ResourceManagerDiscardBytes(DWORD Bytes)
{
	UNREFERENCED_PARAMETER(Bytes);

	return ProxyInterface->EvictManagedResources();
}
HRESULT STDMETHODCALLTYPE Direct3DDevice8::GetDirect3D(Direct3D8 **ppD3D8)
{
	if (ppD3D8 == nullptr)
	{
		return D3DERR_INVALIDCALL;
	}

	D3D->AddRef();

	*ppD3D8 = D3D;

	return D3D_OK;
}
HRESULT STDMETHODCALLTYPE Direct3DDevice8::GetDeviceCaps(D3DCAPS8 *pCaps)
{
	if (pCaps == nullptr)
	{
		return D3DERR_INVALIDCALL;
	}

	D3DCAPS9 DeviceCaps;

	const HRESULT hr = ProxyInterface->GetDeviceCaps(&DeviceCaps);

	if (FAILED(hr))
	{
		return hr;
	}

	ConvertCaps(DeviceCaps, *pCaps);

	return D3D_OK;
}
HRESULT STDMETHODCALLTYPE Direct3DDevice8::GetDisplayMode(D3DDISPLAYMODE *pMode)
{
	return ProxyInterface->GetDisplayMode(0, pMode);
}
HRESULT STDMETHODCALLTYPE Direct3DDevice8::GetCreationParameters(D3DDEVICE_CREATION_PARAMETERS *pParameters)
{
	return ProxyInterface->GetCreationParameters(pParameters);
}
HRESULT STDMETHODCALLTYPE Direct3DDevice8::SetCursorProperties(UINT XHotSpot, UINT YHotSpot, Direct3DSurface8 *pCursorBitmap)
{
	if (pCursorBitmap == nullptr)
	{
		return D3DERR_INVALIDCALL;
	}

	return ProxyInterface->SetCursorProperties(XHotSpot, YHotSpot, pCursorBitmap->GetProxyInterface());
}
void STDMETHODCALLTYPE Direct3DDevice8::SetCursorPosition(UINT XScreenSpace, UINT YScreenSpace, DWORD Flags)
{
	ProxyInterface->SetCursorPosition(XScreenSpace, YScreenSpace, Flags);
}
BOOL STDMETHODCALLTYPE Direct3DDevice8::ShowCursor(BOOL bShow)
{
	return ProxyInterface->ShowCursor(bShow);
}
HRESULT STDMETHODCALLTYPE Direct3DDevice8::CreateAdditionalSwapChain(D3DPRESENT_PARAMETERS8 *pPresentationParameters, Direct3DSwapChain8 **ppSwapChain)
{
	if (pPresentationParameters == nullptr || ppSwapChain == nullptr)
	{
		return D3DERR_INVALIDCALL;
	}

	*ppSwapChain = nullptr;

	D3DPRESENT_PARAMETERS PresentParams;
	ConvertPresentParameters(*pPresentationParameters, PresentParams);

	IDirect3DSwapChain9 *SwapChainInterface = nullptr;

	const HRESULT hr = ProxyInterface->CreateAdditionalSwapChain(&PresentParams, &SwapChainInterface);

	if (FAILED(hr))
	{
		return hr;
	}

	*ppSwapChain = new Direct3DSwapChain8(this, SwapChainInterface);

	return D3D_OK;
}
HRESULT STDMETHODCALLTYPE Direct3DDevice8::Reset(D3DPRESENT_PARAMETERS8 *pPresentationParameters)
{
	if (pPresentationParameters == nullptr)
	{
		return D3DERR_INVALIDCALL;
	}

	D3DPRESENT_PARAMETERS PresentParams;
	ConvertPresentParameters(*pPresentationParameters, PresentParams);
	g_pPresentParameters = pPresentationParameters;

	if (!g_bVsyncEnabled)
	{
		PresentParams.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;
		PresentParams.FullScreen_RefreshRateInHz = 0;
	}

	// Set FOURCC_INTZ format
	/*D3DDISPLAYMODE currentDisplayMode;
	ProxyInterface->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &currentDisplayMode);
	if (ProxyInterface->CheckDeviceFormat(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, currentDisplayMode.Format, D3DUSAGE_DEPTHSTENCIL, D3DRTYPE_SURFACE, FOURCC_INTZ) == D3D_OK)
	{
	PresentParams.AutoDepthStencilFormat = FOURCC_INTZ;
	}*/


	if (CurrentRenderTarget != nullptr)
	{
		CurrentRenderTarget->Release();
		CurrentRenderTarget = nullptr;
	}
	if (CurrentDepthStencilSurface != nullptr)
	{
		CurrentDepthStencilSurface->Release();
		CurrentDepthStencilSurface = nullptr;
	}

	MainEngine->OnLostDevice();

	const HRESULT hr = ProxyInterface->Reset(&PresentParams);

	if (FAILED(hr))
	{
		return hr;
	}

	// Set default render target
	IDirect3DSurface9 *RenderTargetInterface = nullptr;
	IDirect3DSurface9 *DepthStencilInterface = nullptr;

	ProxyInterface->GetRenderTarget(0, &RenderTargetInterface);
	ProxyInterface->GetDepthStencilSurface(&DepthStencilInterface);

	Direct3DSurface8 *RenderTargetProxyObject = nullptr;
	Direct3DSurface8 *DepthStencilProxyObject = nullptr;

	if (RenderTargetInterface != nullptr)
	{
		RenderTargetProxyObject = new Direct3DSurface8(this, RenderTargetInterface);

		RenderTargetInterface->Release();
	}
	if (DepthStencilInterface != nullptr)
	{
		DepthStencilProxyObject = new Direct3DSurface8(this, DepthStencilInterface);

		DepthStencilInterface->Release();
	}

	SetRenderTarget(RenderTargetProxyObject, DepthStencilProxyObject);

	MainEngine->OnResetDevice();

	return D3D_OK;
}
HRESULT STDMETHODCALLTYPE Direct3DDevice8::Present(const RECT *pSourceRect, const RECT *pDestRect, HWND hDestWindowOverride, const RGNDATA *pDirtyRegion)
{
	UNREFERENCED_PARAMETER(pDirtyRegion);

	MainEngine->OnRender();

	return ProxyInterface->Present(pSourceRect, pDestRect, hDestWindowOverride, nullptr);
}
HRESULT STDMETHODCALLTYPE Direct3DDevice8::GetBackBuffer(UINT iBackBuffer, D3DBACKBUFFER_TYPE Type, Direct3DSurface8 **ppBackBuffer)
{
	if (ppBackBuffer == nullptr)
	{
		return D3DERR_INVALIDCALL;
	}

	*ppBackBuffer = nullptr;

	IDirect3DSurface9 *SurfaceInterface = nullptr;

	const HRESULT hr = ProxyInterface->GetBackBuffer(0, iBackBuffer, Type, &SurfaceInterface);

	if (FAILED(hr))
	{
		return hr;
	}

	*ppBackBuffer = new Direct3DSurface8(this, SurfaceInterface);

	return D3D_OK;
}
HRESULT STDMETHODCALLTYPE Direct3DDevice8::GetRasterStatus(D3DRASTER_STATUS *pRasterStatus)
{
	return ProxyInterface->GetRasterStatus(0, pRasterStatus);
}
void STDMETHODCALLTYPE Direct3DDevice8::SetGammaRamp(DWORD Flags, const D3DGAMMARAMP *pRamp)
{
	ProxyInterface->SetGammaRamp(0, Flags, pRamp);
}
void STDMETHODCALLTYPE Direct3DDevice8::GetGammaRamp(D3DGAMMARAMP *pRamp)
{
	ProxyInterface->GetGammaRamp(0, pRamp);
}
HRESULT STDMETHODCALLTYPE Direct3DDevice8::CreateTexture(UINT Width, UINT Height, UINT Levels, DWORD Usage, D3DFORMAT Format, D3DPOOL Pool, Direct3DTexture8 **ppTexture)
{
	if (ppTexture == nullptr)
	{
		return D3DERR_INVALIDCALL;
	}

	*ppTexture = nullptr;

	if (Pool == D3DPOOL_DEFAULT)
	{
		D3DDEVICE_CREATION_PARAMETERS CreationParams;
		ProxyInterface->GetCreationParameters(&CreationParams);

		if ((Usage & D3DUSAGE_DYNAMIC) == 0 &&
			SUCCEEDED(D3D->GetProxyInterface()->CheckDeviceFormat(CreationParams.AdapterOrdinal, CreationParams.DeviceType, D3DFMT_X8R8G8B8, D3DUSAGE_RENDERTARGET, D3DRTYPE_TEXTURE, Format)))
		{
			Usage |= D3DUSAGE_RENDERTARGET;
		}
		else
		{
			Usage |= D3DUSAGE_DYNAMIC;
		}
	}

	IDirect3DTexture9 *TextureInterface = nullptr;

	const HRESULT hr = ProxyInterface->CreateTexture(Width, Height, Levels, Usage, Format, Pool, &TextureInterface, nullptr);

	if (FAILED(hr))
	{
		return hr;
	}

	*ppTexture = new Direct3DTexture8(this, TextureInterface);

	return D3D_OK;
}
HRESULT STDMETHODCALLTYPE Direct3DDevice8::CreateVolumeTexture(UINT Width, UINT Height, UINT Depth, UINT Levels, DWORD Usage, D3DFORMAT Format, D3DPOOL Pool, Direct3DVolumeTexture8 **ppVolumeTexture)
{
	if (ppVolumeTexture == nullptr)
	{
		return D3DERR_INVALIDCALL;
	}

	*ppVolumeTexture = nullptr;

	IDirect3DVolumeTexture9 *TextureInterface = nullptr;

	const HRESULT hr = ProxyInterface->CreateVolumeTexture(Width, Height, Depth, Levels, Usage, Format, Pool, &TextureInterface, nullptr);

	if (FAILED(hr))
	{
		return hr;
	}

	*ppVolumeTexture = new Direct3DVolumeTexture8(this, TextureInterface);

	return D3D_OK;
}
HRESULT STDMETHODCALLTYPE Direct3DDevice8::CreateCubeTexture(UINT EdgeLength, UINT Levels, DWORD Usage, D3DFORMAT Format, D3DPOOL Pool, Direct3DCubeTexture8 **ppCubeTexture)
{
	if (ppCubeTexture == nullptr)
	{
		return D3DERR_INVALIDCALL;
	}

	*ppCubeTexture = nullptr;

	IDirect3DCubeTexture9 *TextureInterface = nullptr;

	const HRESULT hr = ProxyInterface->CreateCubeTexture(EdgeLength, Levels, Usage, Format, Pool, &TextureInterface, nullptr);

	if (FAILED(hr))
	{
		return hr;
	}

	*ppCubeTexture = new Direct3DCubeTexture8(this, TextureInterface);

	return D3D_OK;
}
HRESULT STDMETHODCALLTYPE Direct3DDevice8::CreateVertexBuffer(UINT Length, DWORD Usage, DWORD FVF, D3DPOOL Pool, Direct3DVertexBuffer8 **ppVertexBuffer)
{
	if (ppVertexBuffer == nullptr)
	{
		return D3DERR_INVALIDCALL;
	}

	*ppVertexBuffer = nullptr;

	IDirect3DVertexBuffer9 *BufferInterface = nullptr;

	const HRESULT hr = ProxyInterface->CreateVertexBuffer(Length, Usage, FVF, Pool, &BufferInterface, nullptr);

	if (FAILED(hr))
	{
		return hr;
	}

	*ppVertexBuffer = new Direct3DVertexBuffer8(this, BufferInterface);

	return D3D_OK;
}
HRESULT STDMETHODCALLTYPE Direct3DDevice8::CreateIndexBuffer(UINT Length, DWORD Usage, D3DFORMAT Format, D3DPOOL Pool, Direct3DIndexBuffer8 **ppIndexBuffer)
{
	if (ppIndexBuffer == nullptr)
	{
		return D3DERR_INVALIDCALL;
	}

	*ppIndexBuffer = nullptr;

	IDirect3DIndexBuffer9 *BufferInterface = nullptr;

	const HRESULT hr = ProxyInterface->CreateIndexBuffer(Length, Usage, Format, Pool, &BufferInterface, nullptr);

	if (FAILED(hr))
	{
		return hr;
	}

	*ppIndexBuffer = new Direct3DIndexBuffer8(this, BufferInterface);

	return D3D_OK;
}
HRESULT STDMETHODCALLTYPE Direct3DDevice8::CreateRenderTarget(UINT Width, UINT Height, D3DFORMAT Format, D3DMULTISAMPLE_TYPE MultiSample, BOOL Lockable, Direct3DSurface8 **ppSurface)
{
	if (ppSurface == nullptr)
	{
		return D3DERR_INVALIDCALL;
	}

	*ppSurface = nullptr;

	DWORD QualityLevels = 1;
	D3DDEVICE_CREATION_PARAMETERS CreationParams;
	ProxyInterface->GetCreationParameters(&CreationParams);

	HRESULT hr = D3D->GetProxyInterface()->CheckDeviceMultiSampleType(CreationParams.AdapterOrdinal, CreationParams.DeviceType, Format, FALSE, MultiSample, &QualityLevels);

	if (FAILED(hr))
	{
		return D3DERR_INVALIDCALL;
	}

	IDirect3DSurface9 *SurfaceInterface = nullptr;

	hr = ProxyInterface->CreateRenderTarget(Width, Height, Format, MultiSample, QualityLevels - 1, Lockable, &SurfaceInterface, nullptr);

	if (FAILED(hr))
	{
		return hr;
	}

	*ppSurface = new Direct3DSurface8(this, SurfaceInterface);

	return D3D_OK;
}
HRESULT STDMETHODCALLTYPE Direct3DDevice8::CreateDepthStencilSurface(UINT Width, UINT Height, D3DFORMAT Format, D3DMULTISAMPLE_TYPE MultiSample, Direct3DSurface8 **ppSurface)
{
	if (ppSurface == nullptr)
	{
		return D3DERR_INVALIDCALL;
	}

	*ppSurface = nullptr;

	DWORD QualityLevels = 1;
	D3DDEVICE_CREATION_PARAMETERS CreationParams;
	ProxyInterface->GetCreationParameters(&CreationParams);

	HRESULT hr = D3D->GetProxyInterface()->CheckDeviceMultiSampleType(CreationParams.AdapterOrdinal, CreationParams.DeviceType, Format, FALSE, MultiSample, &QualityLevels);

	if (FAILED(hr))
	{
		return D3DERR_INVALIDCALL;
	}

	IDirect3DSurface9 *SurfaceInterface = nullptr;

	hr = ProxyInterface->CreateDepthStencilSurface(Width, Height, Format, MultiSample, QualityLevels - 1, ZBufferDiscarding, &SurfaceInterface, nullptr);

	if (FAILED(hr))
	{
		return hr;
	}

	*ppSurface = new Direct3DSurface8(this, SurfaceInterface);

	return D3D_OK;
}
HRESULT STDMETHODCALLTYPE Direct3DDevice8::CreateImageSurface(UINT Width, UINT Height, D3DFORMAT Format, Direct3DSurface8 **ppSurface)
{
	if (ppSurface == nullptr)
	{
		return D3DERR_INVALIDCALL;
	}

	*ppSurface = nullptr;

	if (Format == D3DFMT_R8G8B8)
	{
		Format = D3DFMT_X8R8G8B8;
	}

	IDirect3DSurface9 *SurfaceInterface = nullptr;

	const HRESULT hr = ProxyInterface->CreateOffscreenPlainSurface(Width, Height, Format, D3DPOOL_SYSTEMMEM, &SurfaceInterface, nullptr);

	if (FAILED(hr))
	{
		return hr;
	}

	*ppSurface = new Direct3DSurface8(this, SurfaceInterface);

	return D3D_OK;
}
HRESULT STDMETHODCALLTYPE Direct3DDevice8::CopyRects(Direct3DSurface8 *pSourceSurface, const RECT *pSourceRectsArray, UINT cRects, Direct3DSurface8 *pDestinationSurface, const POINT *pDestPointsArray)
{
	if (pSourceSurface == nullptr || pDestinationSurface == nullptr || pSourceSurface == pDestinationSurface)
	{
		return D3DERR_INVALIDCALL;
	}

	D3DSURFACE_DESC SourceDesc, DestinationDesc;
	pSourceSurface->GetProxyInterface()->GetDesc(&SourceDesc);
	pDestinationSurface->GetProxyInterface()->GetDesc(&DestinationDesc);

	if (SourceDesc.Format != DestinationDesc.Format)
	{
		return D3DERR_INVALIDCALL;
	}

	HRESULT hr = D3DERR_INVALIDCALL;

	if (cRects == 0)
	{
		cRects = 1;
	}

	for (UINT i = 0; i < cRects; i++)
	{
		RECT SourceRect, DestinationRect;

		if (pSourceRectsArray != nullptr)
		{
			SourceRect = pSourceRectsArray[i];
		}
		else
		{
			SourceRect.left = 0;
			SourceRect.right = SourceDesc.Width;
			SourceRect.top = 0;
			SourceRect.bottom = SourceDesc.Height;
		}

		if (pDestPointsArray != nullptr)
		{
			DestinationRect.left = pDestPointsArray[i].x;
			DestinationRect.right = DestinationRect.left + (SourceRect.right - SourceRect.left);
			DestinationRect.top = pDestPointsArray[i].y;
			DestinationRect.bottom = DestinationRect.top + (SourceRect.bottom - SourceRect.top);
		}
		else
		{
			DestinationRect = SourceRect;
		}

		if (SourceDesc.Pool == D3DPOOL_MANAGED || DestinationDesc.Pool != D3DPOOL_DEFAULT)
		{
			if (D3DXLoadSurfaceFromSurface != nullptr)
			{
				hr = D3DXLoadSurfaceFromSurface(pDestinationSurface->GetProxyInterface(), nullptr, &DestinationRect, pSourceSurface->GetProxyInterface(), nullptr, &SourceRect, D3DX_FILTER_NONE, 0);
			}
			else
			{
				hr = E_FAIL;
			}
		}
		else if (SourceDesc.Pool == D3DPOOL_DEFAULT)
		{
			hr = ProxyInterface->StretchRect(pSourceSurface->GetProxyInterface(), &SourceRect, pDestinationSurface->GetProxyInterface(), &DestinationRect, D3DTEXF_NONE);
		}
		else if (SourceDesc.Pool == D3DPOOL_SYSTEMMEM)
		{
			const POINT pt = { DestinationRect.left, DestinationRect.top };

			hr = ProxyInterface->UpdateSurface(pSourceSurface->GetProxyInterface(), &SourceRect, pDestinationSurface->GetProxyInterface(), &pt);
		}

		if (FAILED(hr))
		{
			break;
		}
	}

	return hr;
}
HRESULT STDMETHODCALLTYPE Direct3DDevice8::UpdateTexture(Direct3DBaseTexture8 *pSourceTexture, Direct3DBaseTexture8 *pDestinationTexture)
{
	if (pSourceTexture == nullptr || pDestinationTexture == nullptr || pSourceTexture->GetType() != pDestinationTexture->GetType())
	{
		return D3DERR_INVALIDCALL;
	}

	IDirect3DBaseTexture9 *SourceBaseTextureInterface, *DestinationBaseTextureInterface;

	switch (pSourceTexture->GetType())
	{
		case D3DRTYPE_TEXTURE:
			SourceBaseTextureInterface = static_cast<Direct3DTexture8 *>(pSourceTexture)->GetProxyInterface();
			DestinationBaseTextureInterface = static_cast<Direct3DTexture8 *>(pDestinationTexture)->GetProxyInterface();
			break;
		case D3DRTYPE_VOLUMETEXTURE:
			SourceBaseTextureInterface = static_cast<Direct3DVolumeTexture8 *>(pSourceTexture)->GetProxyInterface();
			DestinationBaseTextureInterface = static_cast<Direct3DVolumeTexture8 *>(pDestinationTexture)->GetProxyInterface();
			break;
		case D3DRTYPE_CUBETEXTURE:
			SourceBaseTextureInterface = static_cast<Direct3DCubeTexture8 *>(pSourceTexture)->GetProxyInterface();
			DestinationBaseTextureInterface = static_cast<Direct3DCubeTexture8 *>(pDestinationTexture)->GetProxyInterface();
			break;
		default:
			return D3DERR_INVALIDCALL;
	}

	return ProxyInterface->UpdateTexture(SourceBaseTextureInterface, DestinationBaseTextureInterface);
}
HRESULT STDMETHODCALLTYPE Direct3DDevice8::GetFrontBuffer(Direct3DSurface8 *pDestSurface)
{
	if (pDestSurface == nullptr)
	{
		return D3DERR_INVALIDCALL;
	}

	return ProxyInterface->GetFrontBufferData(0, pDestSurface->GetProxyInterface());
}
HRESULT STDMETHODCALLTYPE Direct3DDevice8::SetRenderTarget(Direct3DSurface8 *pRenderTarget, Direct3DSurface8 *pNewZStencil)
{
	HRESULT hr;

	if (pRenderTarget != nullptr)
	{
		hr = ProxyInterface->SetRenderTarget(0, pRenderTarget->GetProxyInterface());

		if (FAILED(hr))
		{
			return hr;
		}

		if (CurrentRenderTarget != nullptr)
		{
			CurrentRenderTarget->Release();
		}

		CurrentRenderTarget = pRenderTarget;
		CurrentRenderTarget->AddRef();
	}

	if (pNewZStencil != nullptr)
	{
		hr = ProxyInterface->SetDepthStencilSurface(pNewZStencil->GetProxyInterface());

		if (FAILED(hr))
		{
			return hr;
		}

		if (CurrentDepthStencilSurface != nullptr)
		{
			CurrentDepthStencilSurface->Release();
		}

		CurrentDepthStencilSurface = pNewZStencil;
		CurrentDepthStencilSurface->AddRef();
	}
	else
	{
		ProxyInterface->SetDepthStencilSurface(nullptr);

		if (CurrentDepthStencilSurface != nullptr)
		{
			CurrentDepthStencilSurface->Release();
		}

		CurrentDepthStencilSurface = nullptr;
	}

	return D3D_OK;
}
HRESULT STDMETHODCALLTYPE Direct3DDevice8::GetRenderTarget(Direct3DSurface8 **ppRenderTarget)
{
	if (ppRenderTarget == nullptr)
	{
		return D3DERR_INVALIDCALL;
	}

	if (CurrentRenderTarget != nullptr)
	{
		CurrentRenderTarget->AddRef();
	}

	*ppRenderTarget = CurrentRenderTarget;

	return D3D_OK;
}
HRESULT STDMETHODCALLTYPE Direct3DDevice8::GetDepthStencilSurface(Direct3DSurface8 **ppZStencilSurface)
{
	if (ppZStencilSurface == nullptr)
	{
		return D3DERR_INVALIDCALL;
	}

	if (CurrentDepthStencilSurface != nullptr)
	{
		CurrentDepthStencilSurface->AddRef();
	}

	*ppZStencilSurface = CurrentDepthStencilSurface;

	return D3D_OK;
}
HRESULT STDMETHODCALLTYPE Direct3DDevice8::BeginScene()
{
	HRESULT hr = ProxyInterface->BeginScene();

	MainEngine->OnBeginScene();

	return hr;
}
HRESULT STDMETHODCALLTYPE Direct3DDevice8::EndScene()
{
	MainEngine->OnEndScene();

	return ProxyInterface->EndScene();
}
HRESULT STDMETHODCALLTYPE Direct3DDevice8::Clear(DWORD Count, const D3DRECT *pRects, DWORD Flags, D3DCOLOR Color, float Z, DWORD Stencil)
{
	return ProxyInterface->Clear(Count, pRects, Flags, Color, Z, Stencil);
}
HRESULT STDMETHODCALLTYPE Direct3DDevice8::SetTransform(D3DTRANSFORMSTATETYPE State, const D3DMATRIX *pMatrix)
{
	g_TransformState = State;
	return ProxyInterface->SetTransform(State, pMatrix);
}
HRESULT STDMETHODCALLTYPE Direct3DDevice8::GetTransform(D3DTRANSFORMSTATETYPE State, D3DMATRIX *pMatrix)
{
	return ProxyInterface->GetTransform(State, pMatrix);
}
HRESULT STDMETHODCALLTYPE Direct3DDevice8::MultiplyTransform(D3DTRANSFORMSTATETYPE State, const D3DMATRIX *pMatrix)
{
	return ProxyInterface->MultiplyTransform(State, pMatrix);
}
HRESULT STDMETHODCALLTYPE Direct3DDevice8::SetViewport(const D3DVIEWPORT8 *pViewport)
{
	return ProxyInterface->SetViewport(pViewport);
}
HRESULT STDMETHODCALLTYPE Direct3DDevice8::GetViewport(D3DVIEWPORT8 *pViewport)
{
	return ProxyInterface->GetViewport(pViewport);
}
HRESULT STDMETHODCALLTYPE Direct3DDevice8::SetMaterial(const D3DMATERIAL8 *pMaterial)
{
	return ProxyInterface->SetMaterial(pMaterial);
}
HRESULT STDMETHODCALLTYPE Direct3DDevice8::GetMaterial(D3DMATERIAL8 *pMaterial)
{
	return ProxyInterface->GetMaterial(pMaterial);
}
HRESULT STDMETHODCALLTYPE Direct3DDevice8::SetLight(DWORD Index, const D3DLIGHT8 *pLight)
{
	return ProxyInterface->SetLight(Index, pLight);
}
HRESULT STDMETHODCALLTYPE Direct3DDevice8::GetLight(DWORD Index, D3DLIGHT8 *pLight)
{
	return ProxyInterface->GetLight(Index, pLight);
}
HRESULT STDMETHODCALLTYPE Direct3DDevice8::LightEnable(DWORD Index, BOOL Enable)
{
	return ProxyInterface->LightEnable(Index, Enable);
}
HRESULT STDMETHODCALLTYPE Direct3DDevice8::GetLightEnable(DWORD Index, BOOL *pEnable)
{
	return ProxyInterface->GetLightEnable(Index, pEnable);
}
HRESULT STDMETHODCALLTYPE Direct3DDevice8::SetClipPlane(DWORD Index, const float *pPlane)
{
	return ProxyInterface->SetClipPlane(Index, pPlane);
}
HRESULT STDMETHODCALLTYPE Direct3DDevice8::GetClipPlane(DWORD Index, float *pPlane)
{
	return ProxyInterface->GetClipPlane(Index, pPlane);
}
HRESULT STDMETHODCALLTYPE Direct3DDevice8::SetRenderState(D3DRENDERSTATETYPE State, DWORD Value)
{
	FLOAT Biased;

	switch (static_cast<DWORD>(State))
	{
		case D3DRS_LINEPATTERN:
		case D3DRS_ZVISIBLE:
		case D3DRS_EDGEANTIALIAS:
		case D3DRS_PATCHSEGMENTS:
			return D3DERR_INVALIDCALL;
		case D3DRS_SOFTWAREVERTEXPROCESSING:
			return ProxyInterface->SetSoftwareVertexProcessing(Value);
		case D3DRS_ZBIAS:
			Biased = static_cast<FLOAT>(Value) * -0.000005f;
			Value = *reinterpret_cast<const DWORD *>(&Biased);
		default:
			return ProxyInterface->SetRenderState(State, Value);
	}
}
HRESULT STDMETHODCALLTYPE Direct3DDevice8::GetRenderState(D3DRENDERSTATETYPE State, DWORD *pValue)
{
	if (pValue == nullptr)
	{
		return D3DERR_INVALIDCALL;
	}

	HRESULT hr;
	*pValue = 0;

	switch (static_cast<DWORD>(State))
	{
		case D3DRS_LINEPATTERN:
		case D3DRS_ZVISIBLE:
		case D3DRS_EDGEANTIALIAS:
			return D3DERR_INVALIDCALL;
		case D3DRS_ZBIAS:
			hr = ProxyInterface->GetRenderState(D3DRS_DEPTHBIAS, pValue);
			*pValue = static_cast<DWORD>(*reinterpret_cast<const FLOAT *>(pValue) * -500000.0f);
			return hr;
		case D3DRS_SOFTWAREVERTEXPROCESSING:
			*pValue = ProxyInterface->GetSoftwareVertexProcessing();
			return D3D_OK;
		case D3DRS_PATCHSEGMENTS:
			*pValue = 1;
			return D3D_OK;
		default:
			return ProxyInterface->GetRenderState(State, pValue);
	}
}
HRESULT STDMETHODCALLTYPE Direct3DDevice8::BeginStateBlock()
{
	return ProxyInterface->BeginStateBlock();
}
HRESULT STDMETHODCALLTYPE Direct3DDevice8::EndStateBlock(DWORD *pToken)
{
	if (pToken == nullptr)
	{
		return D3DERR_INVALIDCALL;
	}

	return ProxyInterface->EndStateBlock(reinterpret_cast<IDirect3DStateBlock9 **>(pToken));
}
HRESULT STDMETHODCALLTYPE Direct3DDevice8::ApplyStateBlock(DWORD Token)
{
	if (Token == 0)
	{
		return D3DERR_INVALIDCALL;
	}

	return reinterpret_cast<IDirect3DStateBlock9 *>(Token)->Apply();
}
HRESULT STDMETHODCALLTYPE Direct3DDevice8::CaptureStateBlock(DWORD Token)
{
	if (Token == 0)
	{
		return D3DERR_INVALIDCALL;
	}

	return reinterpret_cast<IDirect3DStateBlock9 *>(Token)->Capture();
}
HRESULT STDMETHODCALLTYPE Direct3DDevice8::DeleteStateBlock(DWORD Token)
{
	if (Token == 0)
	{
		return D3DERR_INVALIDCALL;
	}

	reinterpret_cast<IDirect3DStateBlock9 *>(Token)->Release();

	return D3D_OK;
}
HRESULT STDMETHODCALLTYPE Direct3DDevice8::CreateStateBlock(D3DSTATEBLOCKTYPE Type, DWORD *pToken)
{
	if (pToken == nullptr)
	{
		return D3DERR_INVALIDCALL;
	}

	return ProxyInterface->CreateStateBlock(Type, reinterpret_cast<IDirect3DStateBlock9 **>(pToken));
}
HRESULT STDMETHODCALLTYPE Direct3DDevice8::SetClipStatus(const D3DCLIPSTATUS8 *pClipStatus)
{
	return ProxyInterface->SetClipStatus(pClipStatus);
}
HRESULT STDMETHODCALLTYPE Direct3DDevice8::GetClipStatus(D3DCLIPSTATUS8 *pClipStatus)
{
	return ProxyInterface->GetClipStatus(pClipStatus);
}
HRESULT STDMETHODCALLTYPE Direct3DDevice8::GetTexture(DWORD Stage, Direct3DBaseTexture8 **ppTexture)
{
	if (ppTexture == nullptr)
	{
		return D3DERR_INVALIDCALL;
	}

	*ppTexture = nullptr;

	IDirect3DBaseTexture9 *BaseTextureInterface = nullptr;

	const HRESULT hr = ProxyInterface->GetTexture(Stage, &BaseTextureInterface);

	if (FAILED(hr))
	{
		return hr;
	}

	if (BaseTextureInterface != nullptr)
	{
		IDirect3DTexture9 *TextureInterface = nullptr;
		IDirect3DCubeTexture9 *CubeTextureInterface = nullptr;
		IDirect3DVolumeTexture9 *VolumeTextureInterface = nullptr;

		switch (BaseTextureInterface->GetType())
		{
			case D3DRTYPE_TEXTURE:
				BaseTextureInterface->QueryInterface(IID_PPV_ARGS(&TextureInterface));
				*ppTexture = new Direct3DTexture8(this, TextureInterface);
				break;
			case D3DRTYPE_VOLUMETEXTURE:
				BaseTextureInterface->QueryInterface(IID_PPV_ARGS(&VolumeTextureInterface));
				*ppTexture = new Direct3DVolumeTexture8(this, VolumeTextureInterface);
				break;
			case D3DRTYPE_CUBETEXTURE:
				BaseTextureInterface->QueryInterface(IID_PPV_ARGS(&CubeTextureInterface));
				*ppTexture = new Direct3DCubeTexture8(this, CubeTextureInterface);
				break;
			default:
				BaseTextureInterface->Release();
				return D3DERR_INVALIDCALL;
		}

		BaseTextureInterface->Release();
	}

	return D3D_OK;
}
HRESULT STDMETHODCALLTYPE Direct3DDevice8::SetTexture(DWORD Stage, Direct3DBaseTexture8 *pTexture)
{
	if (pTexture == nullptr)
	{
		return ProxyInterface->SetTexture(Stage, nullptr);
	}

	IDirect3DBaseTexture9 *BaseTextureInterface;

	switch (pTexture->GetType())
	{
		case D3DRTYPE_TEXTURE:
			BaseTextureInterface = static_cast<Direct3DTexture8 *>(pTexture)->GetProxyInterface();
			break;
		case D3DRTYPE_VOLUMETEXTURE:
			BaseTextureInterface = static_cast<Direct3DVolumeTexture8 *>(pTexture)->GetProxyInterface();
			break;
		case D3DRTYPE_CUBETEXTURE:
			BaseTextureInterface = static_cast<Direct3DCubeTexture8 *>(pTexture)->GetProxyInterface();
			break;
		default:
			return D3DERR_INVALIDCALL;
	}

	g_pTexture9 = static_cast<Direct3DTexture8 *>(pTexture)->GetProxyInterface();

	return ProxyInterface->SetTexture(Stage, BaseTextureInterface);
}
HRESULT STDMETHODCALLTYPE Direct3DDevice8::GetTextureStageState(DWORD Stage, D3DTEXTURESTAGESTATETYPE Type, DWORD *pValue)
{
	switch (static_cast<DWORD>(Type))
	{
		case D3DTSS_ADDRESSU:
			return ProxyInterface->GetSamplerState(Stage, D3DSAMP_ADDRESSU, pValue);
		case D3DTSS_ADDRESSV:
			return ProxyInterface->GetSamplerState(Stage, D3DSAMP_ADDRESSV, pValue);
		case D3DTSS_ADDRESSW:
			return ProxyInterface->GetSamplerState(Stage, D3DSAMP_ADDRESSW, pValue);
		case D3DTSS_BORDERCOLOR:
			return ProxyInterface->GetSamplerState(Stage, D3DSAMP_BORDERCOLOR, pValue);
		case D3DTSS_MAGFILTER:
			return ProxyInterface->GetSamplerState(Stage, D3DSAMP_MAGFILTER, pValue);
		case D3DTSS_MINFILTER:
			return ProxyInterface->GetSamplerState(Stage, D3DSAMP_MINFILTER, pValue);
		case D3DTSS_MIPFILTER:
			return ProxyInterface->GetSamplerState(Stage, D3DSAMP_MIPFILTER, pValue);
		case D3DTSS_MIPMAPLODBIAS:
			return ProxyInterface->GetSamplerState(Stage, D3DSAMP_MIPMAPLODBIAS, pValue);
		case D3DTSS_MAXMIPLEVEL:
			return ProxyInterface->GetSamplerState(Stage, D3DSAMP_MAXMIPLEVEL, pValue);
		case D3DTSS_MAXANISOTROPY:
			return ProxyInterface->GetSamplerState(Stage, D3DSAMP_MAXANISOTROPY, pValue);
		default:
			return ProxyInterface->GetTextureStageState(Stage, Type, pValue);
	}
}
HRESULT STDMETHODCALLTYPE Direct3DDevice8::SetTextureStageState(DWORD Stage, D3DTEXTURESTAGESTATETYPE Type, DWORD Value)
{
	switch (static_cast<DWORD>(Type))
	{
		case D3DTSS_ADDRESSU:
			return ProxyInterface->SetSamplerState(Stage, D3DSAMP_ADDRESSU, Value);
		case D3DTSS_ADDRESSV:
			return ProxyInterface->SetSamplerState(Stage, D3DSAMP_ADDRESSV, Value);
		case D3DTSS_ADDRESSW:
			return ProxyInterface->SetSamplerState(Stage, D3DSAMP_ADDRESSW, Value);
		case D3DTSS_BORDERCOLOR:
			return ProxyInterface->SetSamplerState(Stage, D3DSAMP_BORDERCOLOR, Value);
		case D3DTSS_MAGFILTER:
			return ProxyInterface->SetSamplerState(Stage, D3DSAMP_MAGFILTER, Value);
		case D3DTSS_MINFILTER:
			return ProxyInterface->SetSamplerState(Stage, D3DSAMP_MINFILTER, Value);
		case D3DTSS_MIPFILTER:
			return ProxyInterface->SetSamplerState(Stage, D3DSAMP_MIPFILTER, Value);
		case D3DTSS_MIPMAPLODBIAS:
			return ProxyInterface->SetSamplerState(Stage, D3DSAMP_MIPMAPLODBIAS, Value);
		case D3DTSS_MAXMIPLEVEL:
			return ProxyInterface->SetSamplerState(Stage, D3DSAMP_MAXMIPLEVEL, Value);
		case D3DTSS_MAXANISOTROPY:
			return ProxyInterface->SetSamplerState(Stage, D3DSAMP_MAXANISOTROPY, Value);
		default:
			return ProxyInterface->SetTextureStageState(Stage, Type, Value);
	}
}
HRESULT STDMETHODCALLTYPE Direct3DDevice8::ValidateDevice(DWORD *pNumPasses)
{
	return ProxyInterface->ValidateDevice(pNumPasses);
}
HRESULT STDMETHODCALLTYPE Direct3DDevice8::GetInfo(DWORD DevInfoID, void *pDevInfoStruct, DWORD DevInfoStructSize)
{
	UNREFERENCED_PARAMETER(DevInfoID);
	UNREFERENCED_PARAMETER(pDevInfoStruct);
	UNREFERENCED_PARAMETER(DevInfoStructSize);

	return S_FALSE;
}
HRESULT STDMETHODCALLTYPE Direct3DDevice8::SetPaletteEntries(UINT PaletteNumber, const PALETTEENTRY *pEntries)
{
	return ProxyInterface->SetPaletteEntries(PaletteNumber, pEntries);
}
HRESULT STDMETHODCALLTYPE Direct3DDevice8::GetPaletteEntries(UINT PaletteNumber, PALETTEENTRY *pEntries)
{
	return ProxyInterface->GetPaletteEntries(PaletteNumber, pEntries);
}
HRESULT STDMETHODCALLTYPE Direct3DDevice8::SetCurrentTexturePalette(UINT PaletteNumber)
{
	return ProxyInterface->SetCurrentTexturePalette(PaletteNumber);
}
HRESULT STDMETHODCALLTYPE Direct3DDevice8::GetCurrentTexturePalette(UINT *pPaletteNumber)
{
	return ProxyInterface->GetCurrentTexturePalette(pPaletteNumber);
}
HRESULT STDMETHODCALLTYPE Direct3DDevice8::DrawPrimitive(D3DPRIMITIVETYPE PrimitiveType, UINT StartVertex, UINT PrimitiveCount)
{
	return ProxyInterface->DrawPrimitive(PrimitiveType, StartVertex, PrimitiveCount);
}
HRESULT STDMETHODCALLTYPE Direct3DDevice8::DrawIndexedPrimitive(D3DPRIMITIVETYPE PrimitiveType, UINT MinIndex, UINT NumVertices, UINT StartIndex, UINT PrimitiveCount)
{
	return MainEngine->OnDrawIndexedPrimitive(CurrentBaseVertexIndex, g_pTexture9, g_Stride, CurrentVertexShaderHandle, g_TransformState, PrimitiveType, MinIndex, NumVertices, StartIndex, PrimitiveCount);

	//return ProxyInterface->DrawIndexedPrimitive(PrimitiveType, CurrentBaseVertexIndex, MinIndex, NumVertices, StartIndex, PrimitiveCount);
}
HRESULT STDMETHODCALLTYPE Direct3DDevice8::DrawPrimitiveUP(D3DPRIMITIVETYPE PrimitiveType, UINT PrimitiveCount, const void *pVertexStreamZeroData, UINT VertexStreamZeroStride)
{
	return ProxyInterface->DrawPrimitiveUP(PrimitiveType, PrimitiveCount, pVertexStreamZeroData, VertexStreamZeroStride);
}
HRESULT STDMETHODCALLTYPE Direct3DDevice8::DrawIndexedPrimitiveUP(D3DPRIMITIVETYPE PrimitiveType, UINT MinVertexIndex, UINT NumVertexIndices, UINT PrimitiveCount, const void *pIndexData, D3DFORMAT IndexDataFormat, const void *pVertexStreamZeroData, UINT VertexStreamZeroStride)
{
	return ProxyInterface->DrawIndexedPrimitiveUP(PrimitiveType, MinVertexIndex, NumVertexIndices, PrimitiveCount, pIndexData, IndexDataFormat, pVertexStreamZeroData, VertexStreamZeroStride);
}
HRESULT STDMETHODCALLTYPE Direct3DDevice8::ProcessVertices(UINT SrcStartIndex, UINT DestIndex, UINT VertexCount, Direct3DVertexBuffer8 *pDestBuffer, DWORD Flags)
{
	if (pDestBuffer == nullptr)
	{
		return D3DERR_INVALIDCALL;
	}

	return ProxyInterface->ProcessVertices(SrcStartIndex, DestIndex, VertexCount, pDestBuffer->GetProxyInterface(), nullptr, Flags);
}
HRESULT STDMETHODCALLTYPE Direct3DDevice8::CreateVertexShader(const DWORD *pDeclaration, const DWORD *pFunction, DWORD *pHandle, DWORD Usage)
{
	return E_NOTIMPL;
}
HRESULT STDMETHODCALLTYPE Direct3DDevice8::SetVertexShader(DWORD Handle)
{
	HRESULT hr;

	if ((Handle & 0x80000000) == 0)
	{
		ProxyInterface->SetVertexShader(nullptr);
		hr = ProxyInterface->SetFVF(Handle);

		CurrentVertexShaderHandle = 0;
	}
	else
	{
		const DWORD handleMagic = Handle << 1;
		VertexShaderInfo *const ShaderInfo = reinterpret_cast<VertexShaderInfo *>(handleMagic);

		hr = ProxyInterface->SetVertexShader(ShaderInfo->Shader);
		ProxyInterface->SetVertexDeclaration(ShaderInfo->Declaration);

		CurrentVertexShaderHandle = Handle;
	}

	return hr;
}
HRESULT STDMETHODCALLTYPE Direct3DDevice8::GetVertexShader(DWORD *pHandle)
{
	if (pHandle == nullptr)
	{
		return D3DERR_INVALIDCALL;
	}

	if (CurrentVertexShaderHandle == 0)
	{
		return ProxyInterface->GetFVF(pHandle);
	}
	else
	{
		*pHandle = CurrentVertexShaderHandle;

		return D3D_OK;
	}
}
HRESULT STDMETHODCALLTYPE Direct3DDevice8::DeleteVertexShader(DWORD Handle)
{
	if ((Handle & 0x80000000) == 0)
	{
		return D3DERR_INVALIDCALL;
	}

	if (CurrentVertexShaderHandle == Handle)
	{
		SetVertexShader(0);
	}

	const DWORD HandleMagic = Handle << 1;
	VertexShaderInfo *const ShaderInfo = reinterpret_cast<VertexShaderInfo *>(HandleMagic);

	if (ShaderInfo->Shader != nullptr)
	{
		ShaderInfo->Shader->Release();
	}
	if (ShaderInfo->Declaration != nullptr)
	{
		ShaderInfo->Declaration->Release();
	}

	delete ShaderInfo;

	return D3D_OK;
}
HRESULT STDMETHODCALLTYPE Direct3DDevice8::SetVertexShaderConstant(DWORD Register, const void *pConstantData, DWORD ConstantCount)
{
	return ProxyInterface->SetVertexShaderConstantF(Register, static_cast<const float *>(pConstantData), ConstantCount);
}
HRESULT STDMETHODCALLTYPE Direct3DDevice8::GetVertexShaderConstant(DWORD Register, void *pConstantData, DWORD ConstantCount)
{
	return ProxyInterface->GetVertexShaderConstantF(Register, static_cast<float *>(pConstantData), ConstantCount);
}
HRESULT STDMETHODCALLTYPE Direct3DDevice8::GetVertexShaderDeclaration(DWORD Handle, void *pData, DWORD *pSizeOfData)
{
	UNREFERENCED_PARAMETER(Handle);
	UNREFERENCED_PARAMETER(pData);
	UNREFERENCED_PARAMETER(pSizeOfData);

	return E_NOTIMPL;
}
HRESULT STDMETHODCALLTYPE Direct3DDevice8::GetVertexShaderFunction(DWORD Handle, void *pData, DWORD *pSizeOfData)
{
	if ((Handle & 0x80000000) == 0)
	{
		return D3DERR_INVALIDCALL;
	}

	const DWORD HandleMagic = Handle << 1;
	IDirect3DVertexShader9 *VertexShaderInterface = reinterpret_cast<VertexShaderInfo *>(HandleMagic)->Shader;

	if (VertexShaderInterface == nullptr)
	{
		return D3DERR_INVALIDCALL;
	}

	return VertexShaderInterface->GetFunction(pData, reinterpret_cast<UINT *>(pSizeOfData));
}
HRESULT STDMETHODCALLTYPE Direct3DDevice8::SetStreamSource(UINT StreamNumber, Direct3DVertexBuffer8 *pStreamData, UINT Stride)
{
	if (pStreamData == nullptr)
	{
		return D3DERR_INVALIDCALL;
	}

	g_Stride = Stride;
	g_pStreamData9 = pStreamData->GetProxyInterface();

	return ProxyInterface->SetStreamSource(StreamNumber, pStreamData->GetProxyInterface(), 0, Stride);
}
HRESULT STDMETHODCALLTYPE Direct3DDevice8::GetStreamSource(UINT StreamNumber, Direct3DVertexBuffer8 **ppStreamData, UINT *pStride)
{
	if (ppStreamData == nullptr)
	{
		return D3DERR_INVALIDCALL;
	}
	else
	{
		*ppStreamData = nullptr;
	}

	UINT StreamOffset = 0;
	IDirect3DVertexBuffer9 *VertexBufferInterface = nullptr;

	const HRESULT hr = ProxyInterface->GetStreamSource(StreamNumber, &VertexBufferInterface, &StreamOffset, pStride);

	if (FAILED(hr))
	{
		return hr;
	}

	if (VertexBufferInterface != nullptr)
	{
		*ppStreamData = new Direct3DVertexBuffer8(this, VertexBufferInterface);
	}

	return D3D_OK;
}
HRESULT STDMETHODCALLTYPE Direct3DDevice8::SetIndices(Direct3DIndexBuffer8 *pIndexData, UINT BaseVertexIndex)
{
	if (pIndexData == nullptr || BaseVertexIndex > 0x7FFFFFFF)
	{
		return D3DERR_INVALIDCALL;
	}

	CurrentBaseVertexIndex = static_cast<INT>(BaseVertexIndex);

	return ProxyInterface->SetIndices(pIndexData->GetProxyInterface());
}
HRESULT STDMETHODCALLTYPE Direct3DDevice8::GetIndices(Direct3DIndexBuffer8 **ppIndexData, UINT *pBaseVertexIndex)
{
	if (ppIndexData == nullptr)
	{
		return D3DERR_INVALIDCALL;
	}

	*ppIndexData = nullptr;

	if (pBaseVertexIndex != nullptr)
	{
		*pBaseVertexIndex = static_cast<UINT>(CurrentBaseVertexIndex);
	}

	IDirect3DIndexBuffer9 *IntexBufferInterface = nullptr;

	const HRESULT hr = ProxyInterface->GetIndices(&IntexBufferInterface);

	if (FAILED(hr))
	{
		return hr;
	}

	if (IntexBufferInterface != nullptr)
	{
		*ppIndexData = new Direct3DIndexBuffer8(this, IntexBufferInterface);
	}

	return D3D_OK;
}
HRESULT STDMETHODCALLTYPE Direct3DDevice8::CreatePixelShader(const DWORD *pFunction, DWORD *pHandle)
{
	return E_NOTIMPL;
}
HRESULT STDMETHODCALLTYPE Direct3DDevice8::SetPixelShader(DWORD Handle)
{
	CurrentPixelShaderHandle = Handle;

	return ProxyInterface->SetPixelShader(reinterpret_cast<IDirect3DPixelShader9 *>(Handle));
}
HRESULT STDMETHODCALLTYPE Direct3DDevice8::GetPixelShader(DWORD *pHandle)
{
	if (pHandle == nullptr)
	{
		return D3DERR_INVALIDCALL;
	}

	*pHandle = CurrentPixelShaderHandle;

	return D3D_OK;
}
HRESULT STDMETHODCALLTYPE Direct3DDevice8::DeletePixelShader(DWORD Handle)
{
	if (Handle == 0)
	{
		return D3DERR_INVALIDCALL;
	}

	if (CurrentPixelShaderHandle == Handle)
	{
		SetPixelShader(0);
	}

	reinterpret_cast<IDirect3DPixelShader9 *>(Handle)->Release();

	return D3D_OK;
}
HRESULT STDMETHODCALLTYPE Direct3DDevice8::SetPixelShaderConstant(DWORD Register, const void *pConstantData, DWORD ConstantCount)
{
	return ProxyInterface->SetPixelShaderConstantF(Register, static_cast<const float *>(pConstantData), ConstantCount);
}
HRESULT STDMETHODCALLTYPE Direct3DDevice8::GetPixelShaderConstant(DWORD Register, void *pConstantData, DWORD ConstantCount)
{
	return ProxyInterface->GetPixelShaderConstantF(Register, static_cast<float *>(pConstantData), ConstantCount);
}
HRESULT STDMETHODCALLTYPE Direct3DDevice8::GetPixelShaderFunction(DWORD Handle, void *pData, DWORD *pSizeOfData)
{
	if (Handle == 0)
	{
		return D3DERR_INVALIDCALL;
	}

	IDirect3DPixelShader9 *const PixelShaderInterface = reinterpret_cast<IDirect3DPixelShader9 *>(Handle);

	return PixelShaderInterface->GetFunction(pData, reinterpret_cast<UINT *>(pSizeOfData));
}
HRESULT STDMETHODCALLTYPE Direct3DDevice8::DrawRectPatch(UINT Handle, const float *pNumSegs, const D3DRECTPATCH_INFO *pRectPatchInfo)
{
	return ProxyInterface->DrawRectPatch(Handle, pNumSegs, pRectPatchInfo);
}
HRESULT STDMETHODCALLTYPE Direct3DDevice8::DrawTriPatch(UINT Handle, const float *pNumSegs, const D3DTRIPATCH_INFO *pTriPatchInfo)
{
	return ProxyInterface->DrawTriPatch(Handle, pNumSegs, pTriPatchInfo);
}
HRESULT STDMETHODCALLTYPE Direct3DDevice8::DeletePatch(UINT Handle)
{
	return ProxyInterface->DeletePatch(Handle);
}