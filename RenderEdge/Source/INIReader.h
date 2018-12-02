#pragma once

#include <d3dx9.h>
#include <string>
#include "ini.h"

class INIReader
{
public:
	INIReader();

	void Open(const std::string& fileName);
	void Open(uint8_t* data);
	bool Success() const;

	bool GetString(const std::string& section, const std::string& name, std::string& value);
	bool GetInt(const std::string& section, const std::string& key, int32_t& value);
	bool GetUInt(const std::string& section, const std::string& key, uint32_t& value);
	bool GetInt64(const std::string& section, const std::string& key, int64_t& value);
	bool GetUInt64(const std::string& section, const std::string& key, uint64_t& value);
	bool GetDouble(const std::string& section, const std::string& key, double& value);
	bool GetFloat(const std::string& section, const std::string& key, float& value);
	bool GetBool(const std::string& section, const std::string& key, bool& value);
	bool GetColor(const std::string& section, const std::string& key, D3DXVECTOR3& value);
	bool GetColor(const std::string& section, const std::string& key, D3DXVECTOR4& value);
	bool GetVector2(const std::string& section, const std::string& key, D3DXVECTOR2& value);
	bool GetVector3(const std::string& section, const std::string& key, D3DXVECTOR3& value);
	bool GetVector4(const std::string& section, const std::string& key, D3DXVECTOR4& value);

private:
	INI ini;
	bool bSuccess;
};