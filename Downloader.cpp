#include "Downloader.h"

#include "Utilities.h"

#include <curl/curl.h>
#include <format>
#include <stdexcept>

using namespace std;

Downloader::Downloader()
{
	curl_global_init(CURL_GLOBAL_DEFAULT);
	m_curl = curl_easy_init();
	if (m_curl == nullptr)
		throw runtime_error("Failed to initialize CURL");
	
	curl_easy_setopt(m_curl, CURLOPT_WRITEFUNCTION, &fwrite);

	// Lazily disable some auth checking that we don't need for this testing
	curl_easy_setopt(m_curl, CURLOPT_SSL_VERIFYPEER, 0L);
	curl_easy_setopt(m_curl, CURLOPT_SSL_VERIFYHOST, 0L);
}

Downloader::~Downloader()
{
	curl_easy_cleanup(m_curl);
	curl_global_cleanup();
}

void Downloader::download(const std::string& url, const std::string& outputFileName)
{
	curl_easy_setopt(m_curl, CURLOPT_URL, url.c_str());

	AutoFile file(outputFileName.c_str(), "wb");
	curl_easy_setopt(m_curl, CURLOPT_WRITEDATA, file.get());

	// Send the request
	CURLcode res = curl_easy_perform(m_curl);
	if (res != CURLE_OK)
		fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
}
