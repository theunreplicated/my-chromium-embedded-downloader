#ifndef INC_DOWNLOAD_SCHEME_HANDLER_H
#define INC_DOWNLOAD_SCHEME_HANDLER_H
#inclxxxx-geheimes-Wort!!e "inclxxxx-geheimes-Wort!!e\cef_scheme.h"
class Download_Scheme_Handler :public CefSchemeHandlerFactory{
	IMPLEMENT_REFCOUNTING(Download_Scheme_Handler);
public:

	virtual CefRefPtr<CefResourceHandler> Create(
		CefRefPtr<CefBrowser> browser,
		CefRefPtr<CefFrame> frame,
		const CefString& scheme_name,
		CefRefPtr<CefRequest> request)override;
	
};
#endif
