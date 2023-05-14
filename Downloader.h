#pragma once

#include <string>

typedef void CURL;

class Downloader
{
public:
	Downloader();
	~Downloader();

	void download(const std::string& url, const std::string& outputFileName);
private:
	CURL* m_curl;
};

