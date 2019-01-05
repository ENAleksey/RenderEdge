#include "SystemTextures.h"
#include "Log.h"

CSystemTextures* SystemTextures;


CSystemTextures::CSystemTextures(IDirect3DDevice9* pDevice) : m_pDevice(pDevice)
{
	InitTemporaryResources();
}

CSystemTextures::~CSystemTextures()
{
	ReleaseTemporaryResources();
}

void CSystemTextures::OnResetDevice()
{
	InitTemporaryResources();
}

void CSystemTextures::OnLostDevice()
{
	ReleaseTemporaryResources();
}


void CSystemTextures::InitTemporaryResources()
{
	{
		if (!preIntegratedGFRT.Create(m_pDevice, 128, 32, 1, ETextureUsage::Dynamic, ETextureFormat::RG16))
			LOG(ERROR) << __FUNCTION__ << " -> Failed to create preIntegratedGFRT!";

		D3DLOCKED_RECT lock;
		preIntegratedGFRT.GetTexture()->LockRect(0, &lock, nullptr, D3DLOCK_DISCARD);

		uint32 DestStride = lock.Pitch;
		uint8* DestBuffer = static_cast<uint8*>(lock.pBits);

		for (int32 y = 0; y < preIntegratedGFRT.GetHeight(); y++)
		{
			float Roughness = (float)(y + 0.5f) / preIntegratedGFRT.GetHeight();
			float m = Roughness * Roughness;
			float m2 = m * m;

			for (int32 x = 0; x < preIntegratedGFRT.GetWidth(); x++)
			{
				float NoV = (float)(x + 0.5f) / preIntegratedGFRT.GetWidth();

				D3DXVECTOR3 V;
				V.x = sqrt(1.0f - NoV * NoV);
				V.y = 0.0f;
				V.z = NoV;

				float A = 0.0f;
				float B = 0.0f;

				const uint32 NumSamples = 128;
				for (uint32 i = 0; i < NumSamples; i++)
				{
					float E1 = (float)i / NumSamples;
					float E2 = (double)math::ReverseBits(i) / (double)0x100000000LL;

					{
						float Phi = 2.0f * D3DX_PI * E1;
						float CosPhi = cos(Phi);
						float SinPhi = sin(Phi);
						float CosTheta = sqrt((1.0f - E2) / (1.0f + (m2 - 1.0f) * E2));
						float SinTheta = sqrt(1.0f - CosTheta * CosTheta);

						D3DXVECTOR3 H(SinTheta * cos(Phi), SinTheta * sin(Phi), CosTheta);
						float VoH = D3DXVec3Dot(&V, &H);
						D3DXVECTOR3 L = 2.0f * VoH * H - V;

						float NoL = max(L.z, 0.0f);
						float NoH = max(H.z, 0.0f);
						VoH = max(VoH, 0.0f);

						if (NoL > 0.0f)
						{
							float Vis_SmithV = NoL * (NoV * (1 - m) + m);
							float Vis_SmithL = NoV * (NoL * (1 - m) + m);
							float Vis = 0.5f / (Vis_SmithV + Vis_SmithL);

							float NoL_Vis_PDF = NoL * Vis * (4.0f * VoH / NoH);
							float Fc = 1.0f - VoH;
							Fc *= math::Square(Fc*Fc);
							A += NoL_Vis_PDF * (1.0f - Fc);
							B += NoL_Vis_PDF * Fc;
						}
					}
				}

				A /= NumSamples;
				B /= NumSamples;

				uint16* Dest = (uint16*)(DestBuffer + x * 4 + y * DestStride);
				Dest[0] = (int32)(math::Clamp(A, 0.0f, 1.0f) * 65535.0f + 0.5f);
				Dest[1] = (int32)(math::Clamp(B, 0.0f, 1.0f) * 65535.0f + 0.5f);
			}
		}

		preIntegratedGFRT.GetTexture()->UnlockRect(0);
	}
}

void CSystemTextures::ReleaseTemporaryResources()
{
	preIntegratedGFRT.Release();
}