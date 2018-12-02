#pragma once

#include <d3dx9.h>

const float OneOver255 = 1.0f / 255.0f;

struct FVector
{
	float r, g, b, a;

	static float sRGBToLinearTable[256];
	static float Pow22OneOver255Table[256];

	FVector() : r(0.0f), g(0.0f), b(0.0f), a(0.0f) {};
	FVector(const D3DXVECTOR3& Vector, float alpha = 1.0f);
	FVector(const FVector& Vector, float alpha = 1.0f);
	FVector(const D3DXVECTOR4& Vector);
	FVector(const D3DCOLORVALUE& Vector);
	FVector(float InR, float InG, float InB, float InA = 1.0f) : r(InR), g(InG), b(InB), a(InA) {}
	FVector(float value) : r(value), g(value), b(value), a(value) {}


	FVector operator+(const FVector& ColorB) const
	{
		return FVector(
			this->r + ColorB.r,
			this->g + ColorB.g,
			this->b + ColorB.b,
			this->a + ColorB.a
		);
	}
	FVector& operator+=(const FVector& ColorB)
	{
		r += ColorB.r;
		g += ColorB.g;
		b += ColorB.b;
		a += ColorB.a;
		return *this;
	}

	FVector operator-(const FVector& ColorB) const
	{
		return FVector(
			this->r - ColorB.r,
			this->g - ColorB.g,
			this->b - ColorB.b,
			this->a - ColorB.a
		);
	}
	FVector& operator-=(const FVector& ColorB)
	{
		r -= ColorB.r;
		g -= ColorB.g;
		b -= ColorB.b;
		a -= ColorB.a;
		return *this;
	}

	FVector operator*(const FVector& ColorB) const
	{
		return FVector(
			this->r * ColorB.r,
			this->g * ColorB.g,
			this->b * ColorB.b,
			this->a * ColorB.a
		);
	}
	FVector& operator*=(const FVector& ColorB)
	{
		r *= ColorB.r;
		g *= ColorB.g;
		b *= ColorB.b;
		a *= ColorB.a;
		return *this;
	}

	FVector operator*(float Scalar) const
	{
		return FVector(
			this->r * Scalar,
			this->g * Scalar,
			this->b * Scalar,
			this->a * Scalar
		);
	}

	FVector& operator*=(float Scalar)
	{
		r *= Scalar;
		g *= Scalar;
		b *= Scalar;
		a *= Scalar;
		return *this;
	}

	FVector operator/(const FVector& ColorB) const
	{
		return FVector(
			this->r / ColorB.r,
			this->g / ColorB.g,
			this->b / ColorB.b,
			this->a / ColorB.a
		);
	}
	FVector& operator/=(const FVector& ColorB)
	{
		r /= ColorB.r;
		g /= ColorB.g;
		b /= ColorB.b;
		a /= ColorB.a;
		return *this;
	}

	FVector operator/(float Scalar) const
	{
		const float	InvScalar = 1.0f / Scalar;
		return FVector(
			this->r * InvScalar,
			this->g * InvScalar,
			this->b * InvScalar,
			this->a * InvScalar
		);
	}
	FVector& operator/=(float Scalar)
	{
		const float	InvScalar = 1.0f / Scalar;
		r *= InvScalar;
		g *= InvScalar;
		b *= InvScalar;
		a *= InvScalar;
		return *this;
	}

	operator D3DXVECTOR3()
	{
		return D3DXVECTOR3(this->r, this->g, this->b);
	}

	operator D3DXVECTOR4()
	{
		return D3DXVECTOR4(this->r, this->g, this->b, this->a);
	}

	float Max3() const
	{
		return max(max(r, g), b);
	}

	float Max4() const
	{
		return max(max(max(r, g), b), a);
	}

	void ToLinear();
	void ToLinearFixedIntensity();
	static FVector ColorToLinear(const D3DXVECTOR3& Vector);
	static FVector ColorToLinear(const FVector& Vector);
	static FVector ColorToLinearFixedIntensity(const FVector& InColor);
	static FVector ColorFromTemperature(float Temp);
};