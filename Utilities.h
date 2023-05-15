#pragma once

#include <SFML/Graphics.hpp>
#include <cstdio>

// A RAII wrapper for when we need a temporary FILE*
class AutoFile
{
public:
	AutoFile(const char* pFileName, const char* pOpenMode);
	AutoFile(const AutoFile& other) = delete;
	AutoFile(AutoFile&& other) noexcept;
	AutoFile& operator =(const AutoFile& other) = delete;
	AutoFile& operator =(AutoFile&& other) noexcept;
	~AutoFile();

	FILE* get() const { return m_file; }
private:
	FILE* m_file;
};

// Miscellaneous functions
float magnitude(const sf::Vector2f& vector);