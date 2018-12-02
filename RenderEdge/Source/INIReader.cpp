#include "INIReader.h"
#include <algorithm>
#include "fp_call.h"
#include "Engine.h"

using std::string;

INIReader::INIReader()
{
	bSuccess = 0;
}

void INIReader::Open(const string& fileName)
{
	bSuccess = ini.Open(fileName);
}

void INIReader::Open(uint8_t* data)
{
	bSuccess = ini.Open(reinterpret_cast<char*>(data));
}

bool INIReader::Success() const
{
	return bSuccess;
}

bool INIReader::GetString(const string& section, const string& name, string& value)
{
	string str = ini.GetString(section, name);
	if (!str.empty())
	{
		value = str;
		std::transform(value.begin(), value.end(), value.begin(), ::tolower);
		return true;
	}

	return false;
}

bool INIReader::GetInt(const string& section, const string& key, int32_t& value)
{
	string text;
	if (GetString(section, key, text))
	{
		value = std::stoi(text, nullptr, 0);
		return true;
	}
	return false;
}

bool INIReader::GetUInt(const string& section, const string& key, uint32_t& value)
{
	string text;
	if (GetString(section, key, text))
	{
		value = std::stoul(text, nullptr, 0);
		return true;
	}
	return false;
}

bool INIReader::GetInt64(const string& section, const string& key, int64_t& value)
{
	string text;
	if (GetString(section, key, text))
	{
		value = std::stoll(text, nullptr, 0);
		return true;
	}
	return false;
}

bool INIReader::GetUInt64(const string& section, const string& key, uint64_t& value)
{
	string text;
	if (GetString(section, key, text))
	{
		value = std::stoull(text, nullptr, 0);
		return true;
	}
	return false;
}

bool INIReader::GetFloat(const string& section, const string& key, float& value)
{
	string text;
	if (GetString(section, key, text))
	{
		value = std::stof(text);
		return true;
	}
	return false;
}

bool INIReader::GetDouble(const string& section, const string& key, double& value)
{
	string text;
	if (GetString(section, key, text))
	{
		value = std::stod(text);
		return true;
	}
	return false;
}

bool INIReader::GetBool(const string& section, const string& key, bool& value)
{
	string text;
	if (GetString(section, key, text))
	{
		if (text == "true" || text == "yes" || text == "on" || text == "1")
			value = true;
		else if (text == "false" || text == "no" || text == "off" || text == "0")
			value = false;
		else
			value = false;

		return true;
	}
	return false;
}

bool INIReader::GetColor(const string& section, const string& key, D3DXVECTOR3& value)
{
	string text;
	if (GetString(section, key, text))
	{
		float r = 0.0f, g = 0.0f, b = 0.0f;
		const bool bSuccessful = utils::ParseFloat(text, "r=", r) && utils::ParseFloat(text, "g=", g) && utils::ParseFloat(text, "b=", b);

		if (bSuccessful)
			value = D3DXVECTOR3(r, g, b);

		return bSuccessful;
	}
	return false;
}

bool INIReader::GetColor(const string& section, const string& key, D3DXVECTOR4& value)
{
	string text;
	if (GetString(section, key, text))
	{
		float r = 0.0f, g = 0.0f, b = 0.0f, a = 1.0f;
		const bool bSuccessful = utils::ParseFloat(text, "r=", r) && utils::ParseFloat(text, "g=", g) && utils::ParseFloat(text, "b=", b);
		utils::ParseFloat(text, "a=", a);

		if (bSuccessful)
			value = D3DXVECTOR4(r, g, b, a);

		return bSuccessful;
	}
	return false;
}

bool INIReader::GetVector2(const string& section, const string& key, D3DXVECTOR2& value)
{
	string text;
	if (GetString(section, key, text))
	{
		float x = 0.0f, y = 0.0f;
		const bool bSuccessful = utils::ParseFloat(text, "x=", x) && utils::ParseFloat(text, "y=", y);

		if (bSuccessful)
			value = D3DXVECTOR2(x, y);

		return bSuccessful;
	}
	return false;
}

bool INIReader::GetVector3(const string& section, const string& key, D3DXVECTOR3& value)
{
	string text;
	if (GetString(section, key, text))
	{
		float x = 0.0f, y = 0.0f, z = 0.0f;
		const bool bSuccessful = utils::ParseFloat(text, "x=", x) && utils::ParseFloat(text, "y=", y) && utils::ParseFloat(text, "z=", z);

		if (bSuccessful)
			value = D3DXVECTOR3(x, y, z);

		return bSuccessful;
	}
	return false;
}

bool INIReader::GetVector4(const string& section, const string& key, D3DXVECTOR4& value)
{
	string text;
	if (GetString(section, key, text))
	{
		float x = 0.0f, y = 0.0f, z = 0.0f, w = 1.0f;
		const bool bSuccessful = utils::ParseFloat(text, "x=", x) && utils::ParseFloat(text, "y=", y) && utils::ParseFloat(text, "z=", z);
		utils::ParseFloat(text, "w=", w);

		if (bSuccessful)
			value = D3DXVECTOR4(x, y, z, w);

		return bSuccessful;
	}
	return false;
}