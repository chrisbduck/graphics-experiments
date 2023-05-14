#include "Utilities.h"

#include <format>
#include <iostream>

using namespace std;

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
