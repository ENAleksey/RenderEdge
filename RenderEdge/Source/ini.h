#pragma once

#include <string>
#include <fstream>
#include <sstream>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <ostream>

#define FINI_SAFE
#define FINI_BUFFER_SIZE 256

#if __cplusplus >= 201103L
#include <unordered_map>
#define FINI_CPP11
#define ALLOCATE_SECTIONS 100
#define ALLOCATE_KEYS 5
#else
#include <map>
#endif

#include <cstring>

typedef std::stringstream fini_sstream_t;
typedef std::string fini_string_t;
typedef char fini_char_t;
typedef std::ifstream fini_ifstream_t;
typedef std::ofstream fini_ofstream_t;

#define CHAR_SIZE sizeof(fini_char_t)

///Simple converter using templates and streams to effectively required for the flexibility of handling native types
class Converters
{
public:
	template <typename T, typename U>
	T Convert(U value);
	template <typename T>
	void GetLine(fini_sstream_t& out, T& value);
	void GetLine(fini_sstream_t& out, fini_string_t& value);
	template <typename T>
	size_t GetDataSize(T& value);
	size_t GetDataSize(fini_string_t value);
};

///
//template <typename T = fini_string_t, typename U = fini_string_t, typename V = fini_string_t>
class INI
{
public:
	typedef fini_string_t section_t;
	typedef fini_string_t key_t;
	typedef fini_string_t value_t;
	typedef INI/*<section_t, key_t, value_t>*/ ini_t;

	///Type definition declarations
#ifdef FINI_CPP11
	typedef typename std::unordered_map<key_t, value_t> keys_t;
	typedef typename std::unordered_map<section_t, keys_t*> sections_t;
#else
	typedef typename std::map<key_t, value_t> keys_t;
	typedef typename std::map<section_t, keys_t*> sections_t;
#endif

	typedef typename keys_t::iterator keysit_t;
	typedef typename sections_t::iterator sectionsit_t;

	typedef typename std::pair<key_t, value_t> keyspair_t;
	typedef typename std::pair<section_t, keys_t*> sectionspair_t;

	typedef char data_t;

	enum source_e { SOURCE_FILE, SOURCE_MEMORY };

	///Data members
	std::string filename;
	keys_t* current;
	sections_t sections;
	source_e source;

	///Constuctor/Destructor
	INI()
	{
		Init();
	}

	~INI()
	{
		Clear();
	}

	///Access Content
	//Provide bracket access to section contents
	keys_t& operator[](section_t section)
	{
#ifdef FINI_SAFE
		if (!sections[section])
			sections[section] = new keys_t;
#endif

		return *sections[section];
	}

	//Create a new section and select it
	bool create(const section_t section)
	{
		if (select(section))
			return false;

		current = new keys_t;
		sections[section] = current;

		reserveKeys(current);

		return true;
	}

	//Select a section for performing operations
	bool select(const section_t section)
	{
		sectionsit_t sectionsit = sections.find(section);
		if (sectionsit == sections.end())
			return false;

		current = sectionsit->second;

		return true;
	}

	///Set
	//Assign a value for key under the selected section
	bool set(const key_t key, const value_t value)
	{
		if (current == nullptr)
			return false;

		(*current)[key] = value;

		return true;
	}

	template <typename W, typename X>
	bool set(const W key, const X value)
	{
		return set(Converters::Convert<key_t>(key), Converters::Convert<value_t>(value));
	}

	///Get
	std::string GetString(const std::string& section, const std::string& key, const std::string def = std::string())
	{
		if (!select(section))
			return def;

		keysit_t it = current->find(key);
		if (current == nullptr || it == current->end())
			return def;

		return it->second;
	}

	///Functions
	void Parse(std::istream& buffer)
	{
		std::string theLine;
		while (std::getline(buffer, theLine))
		{
			if (*theLine.rbegin() == '\r')
				theLine.erase(theLine.end() - 1);

			char* line = const_cast<char*>(theLine.c_str());

			// Advance past new line characters
			while (*line == '\r' || *line == '\n')
				continue;

			if (line == nullptr || *line == 0)
				continue;

			// Strip trailing spaces from the current line
			while (*line && isspace(line[strlen(line) - 1]))
				line[strlen(line) - 1] = 0;


			if (*line == '[' && line[strlen(line) - 1] == ']') // Section
			{
				// Remove the brackets
				line++;
				line[strlen(line) - 1] = 0;

				current = new keys_t;
				sections[line] = current;
			}
			else if (current && *line) // Key=Value
			{
				char* value = nullptr;

				// ignore [comment] lines that start with ;
				if (*line != ';')
					value = strstr(line, "=");

				// Ignore any lines that don't contain a key-value pair
				if (value)
				{
					char* key = line;

					// Terminate the propertyname, advancing past the =
					*value++ = 0;

					// strip leading whitespace from the property name
					while (*key && isspace(*key))
						key++;

					// Strip trailing spaces from the property name.
					while (*key && isspace(key[strlen(key) - 1]))
						key[strlen(key) - 1] = 0;

					// Strip leading whitespace from the property value
					while (*value && isspace(*value))
						value++;

					// Strip comment from the property value
					while (strchr(value, ';'))
					{
						while (*value && value[strlen(value) - 1] != ';')
							value[strlen(value) - 1] = 0;
						value[strlen(value) - 1] = 0;
					}

					// strip trailing whitespace from the property value
					while (*value && isspace(value[strlen(value) - 1]))
						value[strlen(value) - 1] = 0;

					(*current)[key] = value;
				}
			}
		}
	}

	//Parse an INI's contents into memory from the filename given during construction
	bool Open(std::string fileName)
	{
		filename = fileName;
		source = SOURCE_FILE;

		std::ifstream file(fileName.c_str());

		if (!file.is_open())
			return false;

		Parse(file);

		file.close();

		return true;
	}

	bool Open(char* data)
	{
		source = SOURCE_MEMORY;

		std::stringstream sstream;
		sstream << data;

		Parse(sstream);

		return true;
	}

	//Clear the contents from memory
	void Clear()
	{
		Clean();
		sections.clear();
	}

	///Output
	//Save from memory into file
	bool Save(const std::string filename = "")
	{
		if (!hasFileAssociation(filename))
			return false;

		fini_ofstream_t file(((filename == "") ? this->filename : filename).c_str(), std::ios::trunc);
		if (!file.is_open())
			return false;

		//Loop through sections
		for (typename INI::sectionsit_t i = sections.begin(); i != sections.end(); i++)
		{
			if (i->second->size() == 0)  //No keys/values in section, skip to next
				continue;

			//Write section
			const fini_string_t temp = makeSection(i->first);
			const fini_char_t* line = temp.c_str();
			file.write(line, strlen(line));

			for (typename INI::keysit_t j = i->second->begin(); j != i->second->end(); j++)
			{
				//Write key and value
				const fini_string_t temp = makeKeyValue(j->first, j->second);
				const fini_char_t* line = temp.c_str();
				file.write(line, strlen(line));
			}
		}

		file.close();

		return true;
	}

private:
	///Functions
	void Init()
	{
		reserveSections();
	}

	//Clean the contents for descruction
	void Clean()
	{
		for (sectionsit_t i = sections.begin(); i != sections.end(); i++)
			delete i->second;

		current = nullptr;
	}

	//Make any alterations to the raw line
	void nake(const fini_char_t*)  //Strip the line of any non-interpretable characters
	{

	}

	void reserveSections()
	{
#ifdef FINI_CPP11
		sections.reserve(ALLOCATE_SECTIONS);
#endif
	}

	void reserveKeys(keys_t* current)
	{
#ifdef FINI_CPP11
		current->reserve(ALLOCATE_KEYS);
#endif
	}

	bool hasFileAssociation(std::string filename)
	{
		if (source == SOURCE_MEMORY && filename == "") //No association to a file
			return false;

		return true;
	}

	///Output
	//Creates a section as a string
	fini_string_t makeSection(const section_t& section)
	{
		fini_sstream_t line;
		line << '[' << section << ']' << std::endl;

		return line.str();
	}

	//Creates a key and a value as a string
	fini_string_t makeKeyValue(const key_t& key, const value_t& value)
	{
		fini_sstream_t line;
		line << key << '=' << value << std::endl;

		return line.str();
	}
};

///Definitions
template <typename T, typename U>
inline T Converters::Convert(U value)
{
	fini_sstream_t sout;
	T result;

	sout << value;
	sout >> result;

	sout.str(fini_string_t());

	return result;
}

template <>
inline fini_string_t Converters::Convert<fini_string_t, fini_string_t>(fini_string_t value)
{
	return value;
}

template <>
inline fini_string_t Converters::Convert<fini_string_t>(const fini_char_t* value)
{
	return value;
}

template <typename T>
inline void Converters::GetLine(fini_sstream_t& out, T& value)
{
	out >> value;
}

inline void Converters::GetLine(fini_sstream_t& out, fini_string_t& value)
{
	std::getline(out, value);
}

template <typename T>
inline size_t Converters::GetDataSize(T& value)
{
	return sizeof(value);
}

inline size_t Converters::GetDataSize(fini_string_t value)
{
	return value.size() + 1;
}