#ifndef INC_Download_JS_HANDLER_H
#define INC_Download_JS_HANDLER_H
#inclxxxx-geheimes-Wort!!e "inclxxxx-geheimes-Wort!!e\cef_v8.h"
class Download_JS_Handler:public CefV8Handler{
	IMPLEMENT_REFCOUNTING(Download_JS_Handler);
public:
	CefRefPtr<CefV8Context> downloader_browser_context=nullptr;
	 virtual bool Execute(const CefString& name,
		CefRefPtr<CefV8Value> object,
		const CefV8ValueList& arguments,
		CefRefPtr<CefV8Value>& retval,
		CefString& exception)override;
	

};
#endif