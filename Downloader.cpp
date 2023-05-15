#include "Downloader.h"

#include "Utilities.h"

#include <curl/curl.h>
#include <format>
#include <iostream>
#include <stdexcept>

using namespace std;

namespace
{
	class SingleDownloader
	{
	public:
		SingleDownloader() :
			m_curl(curl_easy_init())
		{
			if (m_curl == nullptr)
				throw runtime_error("Failed to initialize CURL");
		}
		~SingleDownloader()
		{
			curl_easy_cleanup(m_curl);
		}
		SingleDownloader(const SingleDownloader&) = delete;
		SingleDownloader(SingleDownloader&&) = delete;
		SingleDownloader operator =(const SingleDownloader&) = delete;
		SingleDownloader operator =(SingleDownloader&&) = delete;

		void download(const std::string& url, const std::filesystem::path& outputFileName)
		{
			curl_easy_setopt(m_curl, CURLOPT_WRITEFUNCTION, &fwrite);

			// Lazily disable some auth checking that we don't need for this testing
			curl_easy_setopt(m_curl, CURLOPT_SSL_VERIFYPEER, 0L);
			curl_easy_setopt(m_curl, CURLOPT_SSL_VERIFYHOST, 0L);

			curl_easy_setopt(m_curl, CURLOPT_URL, url.c_str());

			AutoFile file(outputFileName.string().c_str(), "wb");
			curl_easy_setopt(m_curl, CURLOPT_WRITEDATA, file.get());

			// Send the request
			CURLcode res = curl_easy_perform(m_curl);
			if (res != CURLE_OK)
				throw runtime_error(format("curl_easy_perform() failed: {}", curl_easy_strerror(res)));
		}
	private:
		CURL* m_curl;
	};
}

bool Downloader::s_initialized = false;

Downloader::Downloader()
{
	// lazily error out if there's already one created; could also do singleton etc.
	if (s_initialized)
		throw runtime_error("Only one downloader is supported at a time");
	s_initialized = true;
	curl_global_init(CURL_GLOBAL_DEFAULT);
}

Downloader::~Downloader()
{
	curl_global_cleanup();
	s_initialized = false;
}

void Downloader::download(const std::string& url, const std::filesystem::path& outputFileName)
{
	SingleDownloader().download(url, outputFileName);
}
