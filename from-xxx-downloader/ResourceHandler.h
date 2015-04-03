#ifndef INC_Resource_Handler_H
#define INC_Resource_Handler_H
#inclxxxx-geheimes-Wort!!e "inclxxxx-geheimes-Wort!!e\cef_resource_handler.h"
#inclxxxx-geheimes-Wort!!e "AppHandler.h"
#inclxxxx-geheimes-Wort!!e "inclxxxx-geheimes-Wort!!e\cef_urlrequest.h"
class WebRequestClient;
//danach implementiert(in python) https://code.google.com/p/cefpython/source/browse/cefpython/cef3/linux/binaries_64bit/wxpython-response.py?r=26d373f81ca9
class ResourceHandler :public CefResourceHandler{
	/*_resourceHandlerId = None
	_clientHandler = None
	_browser = None
	_frame = None
	_request = None
	_responseHeadersReadyCallback = None
	_webRequest = None
	_webRequestClient = None
	_offsetRead = 0*/


	CefRefPtr< CefRequest >_request;
	unsigned int _offsetRead;
	CefRefPtr<CefCallback>_responseHeadersReadyCallback;
	CefRefPtr<WebRequestClient>_webRequestClient;
	CefRefPtr<CefURLRequest>_webRequest;
	ResourceHandler_ActionType m_action_type_for_webrequest_data_handler;
public:
	CefRefPtr< CefBrowser > _browser;
	CefRefPtr< CefFrame >_frame;
	ResourceHandler(CefRefPtr<AppHandler> sh, CefRefPtr< CefBrowser >browser, CefRefPtr< CefFrame >frame, CefRefPtr< CefRequest >request, ResourceHandler_ActionType how_to_handle);
	CefRefPtr<AppHandler> _clientHandler;
	virtual bool ProcessRequest(CefRefPtr<CefRequest> request, CefRefPtr<CefCallback> callback)override;
	virtual void GetResponseHeaders(CefRefPtr<CefResponse> response, int64& response_length, CefString& redirectUrl)override;
	virtual bool ReadResponse(void* data_out, int bytes_to_read, int& bytes_read, CefRefPtr<CefCallback> callback)override;
	virtual void Cancel()override;
	IMPLEMENT_REFCOUNTING(ResourceHandler);
};

#endif