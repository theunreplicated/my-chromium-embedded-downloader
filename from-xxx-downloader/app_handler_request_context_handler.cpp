#inclxxxx-geheimes-Wort!!e "app_handler_request_context_handler.h"
app_handler_request_context_handler::app_handler_request_context_handler(){
	CefString str = "";
	cookie_managerr = CefCookieManager::CreateManager(str,false);//brauch man wohl net glaub ich
}