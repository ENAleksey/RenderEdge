#pragma once

#include <d3dx9.h>

const float OneOver255 = 1.0f / 255.0f;

struct FColor
{
	float r, g, b, a;

	static float sRGBToLinearTable[256];
	static float Pow22OneOver255Table[256];

	FColor() : r(0.0f), g(0.0f), b(0.0f), a(0.0f) {};
	FColor(const D3DXVECTOR3& color, float alpha = 1.0f);
	FColor(const FColor& color, float alpha = 1.0f);
	FColor(const D3DXVECTOR4& color);
	FColor(const D3DCOLORVALUE& color);
	FColor(float InR, float InG, float InB, float InA = 1.0f) : r(InR), g(InG), b(InB), a(InA) {}
	FColor(float value) : r(value), g(value), b(value), a(value) {}


	FColor operator+(const FColor& color) const
	{
		return FColor(
			this->r + color.r,
			this->g + color.g,
			this->b + color.b,
			this->a + color.a
		);
	}
	FColor& operator+=(const FColor& color)
	{
		r += color.r;
		g += color.g;
		b += color.b;
		a += color.a;
		return *this;
	}

	FColor operator-(const FColor& color) const
	{
		return FColor(
			this->r - color.r,
			this->g - color.g,
			this->b - color.b,
			this->a - color.a
		);
	}
	FColor& operator-=(const FColor& color)
	{
		r -= color.r;
		g -= color.g;
		b -= color.b;
		a -= color.a;
		return *this;
	}

	FColor operator*(const FColor& color) const
	{
		return FColor(
			this->r * color.r,
			this->g * color.g,
			this->b * color.b,
			this->a * color.a
		);
	}
	FColor& operator*=(const FColor& color)
	{
		r *= color.r;
		g *= color.g;
		b *= color.b;
		a *= color.a;
		return *this;
	}

	FColor operator*(float x) const
	{
		return FColor(
			this->r * x,
			this->g * x,
			this->b * x,
			this->a * x
		);
	}

	FColor& operator*=(float x)
	{
		r *= x;
		g *= x;
		b *= x;
		a *= x;
		return *this;
	}

	FColor operator/(const FColor& color) const
	{
		return FColor(
			this->r / color.r,
			this->g / color.g,
			this->b / color.b,
			this->a / color.a
		);
	}
	FColor& operator/=(const FColor& color)
	{
		r /= color.r;
		g /= color.g;
		b /= color.b;
		a /= color.a;
		return *this;
	}

	FColor operator/(float x) const
	{
		const float	invScalar = 1.0f / x;
		return FColor(
			this->r * invScalar,
			this->g * invScalar,
			this->b * invScalar,
			this->a * invScalar
		);
	}
	FColor& operator/=(float x)
	{
		const float	invScalar = 1.0f / x;
		r *= invScalar;
		g *= invScalar;
		b *= invScalar;
		a *= invScalar;
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
	static FColor ToLinear(const D3DXVECTOR3& color);
	static FColor ToLinear(const FColor& color);
	static FColor FromTemperature(float Temp);
};