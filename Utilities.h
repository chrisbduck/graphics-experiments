#pragma once

#include <SFML/Graphics.hpp>
#include <chrono>
#include <cstdio>
#include <string>

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

class TimeLogger
{
public:
	TimeLogger(const std::string& label);
	~TimeLogger();
private:
	std::chrono::time_point<std::chrono::high_resolution_clock> m_startTime;
	std::string m_label;
};

// Miscellaneous functions

float magnitude(const sf::Vector2f& vector);

// Returns a random float in the range [0, 1)  - i.e., includes 0 but not 1.
float randomFloat();

float timeSinceEpochInSeconds();
