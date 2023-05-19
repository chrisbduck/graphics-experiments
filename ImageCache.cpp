#include "ImageCache.h"

#include <filesystem>
#include <iostream>

using namespace std;

namespace
{
	const std::string c_localCacheFolder("cache");
}

std::filesystem::path ImageCache::getLocalPathForURL(const std::string& url)
{
	hash<string> hasher;
	const auto extPos = url.rfind('.');
	if (extPos == string::npos)
		throw runtime_error("invalid path: " + url);
	const auto extension = url.substr(extPos);
	return filesystem::current_path() / c_localCacheFolder / (to_string(hasher(url)) + extension);
}

const std::filesystem::path& ImageCache::cacheAndGetPath(const std::string& url)
{
	// Check the memory cache of file presence
	const auto iLocalPath = m_urlToLocalPath.find(url);
	if (iLocalPath != m_urlToLocalPath.end())
		return iLocalPath->second;

	// Check the file system
	filesystem::path localFileName = getLocalPathForURL(url);
	if (!exists(localFileName))
	{
		// Download
		cout << "downloading " << localFileName.filename() << " from " << url << endl;
		m_downloader.download(url, localFileName);
	}

	// Cache and return
	const auto& iInsertedPath = m_urlToLocalPath.insert({ url, localFileName }).first;
	cout << "loading local file " << localFileName.filename() << endl;
	return iInsertedPath->second;
}
