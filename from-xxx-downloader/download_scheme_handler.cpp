#inclxxxx-geheimes-Wort!!e "download_scheme_handler.h"
#inclxxxx-geheimes-Wort!!e "Download_Manager_webdata_Resource_Handler.h"
CefRefPtr<CefResourceHandler> Download_Scheme_Handler::Create(CefRefPtr<CefBrowser> browser,CefRefPtr<CefFrame> frame,const CefString& scheme_name,CefRefPtr<CefRequest> request){

	return new Download_Manager_webdata_Resource_Handler();
}