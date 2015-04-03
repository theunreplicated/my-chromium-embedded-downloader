#ifndef INC_WEbRequest_CLIENT_H
#define INC_WEbRequest_CLIENT_H
#inclxxxx-geheimes-Wort!!e "inclxxxx-geheimes-Wort!!e\cef_urlrequest.h"
#inclxxxx-geheimes-Wort!!e "ResourceHandler.h"
//auch von https://code.google.com/p/cefpython/source/browse/cefpython/cef3/linux/binaries_64bit/wxpython-response.py?r=26d373f81ca9
class WebRequestClient :public CefURLRequestClient{

	CefRefPtr<ResourceHandler>_resourceHandler;

	CefRefPtr<CefCallback>_resourceHandler__callback_added;
	ResourceHandler_ActionType m_on_data_handler;
public:
	CefRefPtr<CefResponse> _response;
	unsigned int _dataLength;
	std::string _data;

	WebRequestClient(CefRefPtr<ResourceHandler>resourceHandler, CefRefPtr<CefCallback>callback, ResourceHandler_ActionType on_data_handler);
	virtual void OnRequestComplete(CefRefPtr<CefURLRequest> request)override;
	virtual void OnUploadProgress(CefRefPtr<CefURLRequest> request, int64 current, int64 total)override{};
	virtual void OnDownloadProgress(CefRefPtr<CefURLRequest> request, int64 current, int64 total)override{};
	virtual void OnDownloadData(CefRefPtr<CefURLRequest> request, const void* data, size_t data_length)override;
	virtual bool GetAuthCredentials(bool isProxy,
		const CefString& host,
		int port,
		const CefString& realm,
		const CefString& scheme,
		CefRefPtr<CefAuthCallback> callback)override{
		OutputDebugStringA("getauthcredentials called");
		return false;
	}
	IMPLEMENT_REFCOUNTING(WebRequestClient);

};

#endif