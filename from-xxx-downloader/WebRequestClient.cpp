#inclxxxx-geheimes-Wort!!e "WebRequestClient.h"

WebRequestClient::WebRequestClient(CefRefPtr<ResourceHandler>resourceHandler, CefRefPtr<CefCallback>callback, ResourceHandler_ActionType on_data_handler){
	_resourceHandler = resourceHandler;
	_resourceHandler__callback_added = callback; _dataLength = 0;
	m_on_data_handler = on_data_handler;
}
void WebRequestClient::OnRequestComplete(CefRefPtr<CefURLRequest> request){
	_response = request->GetResponse();
	if (m_on_data_handler == ResourceHandler_ActionType_WANT_TEXT_LECTURE_TYPE){
		_resourceHandler->_clientHandler->onResourceInterceptText(request->GetRequest()->GetURL(), _data);
	}
	else if (m_on_data_handler == ResourceHandler_ActionType_WANT_DATA_IN_ORDER_TO_CAUSE_MODIFICATIONS){

		_data=_resourceHandler->_clientHandler->onResourceModifytemplate_js_by_xxxx-geheimes-Wort!!(request->GetRequest()->GetURL(), _data);
	}

	//_data=_resourceHandler->_clientHandler->_OnResourceResponse(_resourceHandler->_browser, _resourceHandler->_frame, request->GetRequest(),
	//request->GetRequestStatus(), request->GetRequestError(), request->GetResponse(),_data);
	
	//::MessageBoxA(NULL,_data.c_str(),"data hier",MB_OK);
	_dataLength = _data.length();
	_resourceHandler__callback_added->Continue();
}
void WebRequestClient::OnDownloadData(CefRefPtr<CefURLRequest> request, const void* data, size_t data_length){
	//char* newstr = new char[data_length];
	
	//if (request->GetResponse()->GetMimeType().ToString().find("video") != std::string::npos){
	//	::MessageBoxA(NULL, "video anscheinend", "data hier", MB_OK);

	//}
	//memcpy(newstr, data, data_length);
	//char* sp = static_cast<char*>(const_cast<void*>(data));
	//CefString str=CefString(newstr);
	//std::string final_str = newstr;
	//std::string sp = static_cast<std::string>(const_cast<void*>(data));
	//std::string dd = std::string(sp);
	_data += std::string(static_cast<const char*>(data), data_length);//http://chromiumembedded.googlecode.com/svn/trunk/cef3/tests/unittests/urlrequest_unittest.cc
	//delete sp;

}