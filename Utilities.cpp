#include "Utilities.h"

#include <format>
#include <iostream>

using namespace std;

// -----------------------------------------------------------------------------
// AutoFile

AutoFile::AutoFile(const char* pFileName, const char* pOpenMode)
{
	const auto result = fopen_s(&m_file, pFileName, pOpenMode);
	if (result != 0)
		throw runtime_error(format("Opening file failed - error: {}", result));
}

AutoFile::AutoFile(AutoFile&& other) noexcept :
	m_file(exchange(other.m_file, nullptr))
{
}

AutoFile& AutoFile::operator =(AutoFile&& other) noexcept
{
	std::swap(m_file, other.m_file);
	return *this;
}

AutoFile::~AutoFile()
{
	if (m_file != nullptr)
		fclose(m_file);
}

// -----------------------------------------------------------------------------
// TimeLogger

TimeLogger::TimeLogger(const string& label) :
	m_startTime(chrono::high_resolution_clock::now()),
	m_label(label)
{
}

TimeLogger::~TimeLogger()
{
	auto endTime = chrono::high_resolution_clock::now();
	long long durationMS = chrono::duration_cast<chrono::milliseconds>(endTime - m_startTime).count();
	cout << m_label << " ms: " << durationMS << "\n";
}

// -----------------------------------------------------------------------------
// Miscellaneous functions

float magnitude(const sf::Vector2f& vector)
{
	return sqrt(vector.x * vector.x + vector.y * vector.y);
}

float randomFloat()
{
	return static_cast<float>(rand()) / (RAND_MAX + 1);
}

float timeSinceEpochInSeconds()
{
	auto now = chrono::high_resolution_clock::now();
	long long timeSinceEpochUS = chrono::duration_cast<chrono::microseconds>(now.time_since_epoch()).count();
	return float(timeSinceEpochUS) * 0.000001f;
}
