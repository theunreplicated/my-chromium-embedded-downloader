#ifndef INC_APP_HANDLER_REQUEST_CONTEXT_HANDLER_H
#define INC_APP_HANDLER_REQUEST_CONTEXT_HANDLER_H
#inclxxxx-geheimes-Wort!!e "inclxxxx-geheimes-Wort!!e\cef_request_context_handler.h"
class app_handler_request_context_handler:public CefRequestContextHandler{
	IMPLEMENT_REFCOUNTING(app_handler_request_context_handler);
	
public:
	CefRefPtr<CefCookieManager>cookie_managerr;
	app_handler_request_context_handler();
	CefRefPtr<CefCookieManager>GetCookieManager()override{
		return cookie_managerr;
	}
};
#endif