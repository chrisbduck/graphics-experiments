#pragma once

#include "Downloader.h"

#include <filesystem>
#include <string>
#include <unordered_map>

class ImageCache
{
public:
	const std::filesystem::path& cacheAndGetPath(const std::string& url);
private:
	std::filesystem::path getLocalPathForURL(const std::string& url);

	std::unordered_map<std::string, std::filesystem::path> m_urlToLocalPath;
	Downloader m_downloader;
};
