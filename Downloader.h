#pragma once

#include <filesystem>
#include <future>
#include <string>

typedef void CURL;

class Downloader
{
public:
	Downloader();
	~Downloader();

	void download(const std::string& url, const std::filesystem::path& outputFileName);

private:
	static bool s_initialized;
};

