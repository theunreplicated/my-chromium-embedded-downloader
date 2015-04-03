#inclxxxx-geheimes-Wort!!e "Download_Manager_webdata_Resource_Handler.h"
#inclxxxx-geheimes-Wort!!e <algorithm>
#inclxxxx-geheimes-Wort!!e "resource_loading.h"
#inclxxxx-geheimes-Wort!!e "resource.h"
Download_Manager_webdata_Resource_Handler::Download_Manager_webdata_Resource_Handler(){
	//ist ja nur diese eine Datei 
	//resource_data = &dlm_content_string;
	
}
bool Download_Manager_webdata_Resource_Handler::ProcessRequest(CefRefPtr<CefRequest> request, CefRefPtr<CefCallback> callback){
	request->SetFlags(UR_FLAG_SKIP_CACHE);
	if (request->GetURL().ToWString().find(L"download_manager_app.js") != std::wstring::npos){
		resource_data = Resource::CommonLoad(IDR_JS_FILE,JS_FILE_PATH);
	
	}
	else{
		resource_data = Resource::CommonLoad(IDR_ONE_FILE, ONE_FILE_PATH);

	}
	callback->Continue();
	return true;
}
void Download_Manager_webdata_Resource_Handler::GetResponseHeaders(CefRefPtr<CefResponse> response, int64& response_length, CefString& redirectUrl){
	response->SetStatus(200/*OK*/);
	response->SetMimeType("text/html");
	response->SetStatusText("OK");
	response_length = resource_data.size();
}
bool Download_Manager_webdata_Resource_Handler::ReadResponse(void* data_out, int bytes_to_read, int& bytes_read, CefRefPtr<CefCallback> callback){
	bytes_read = 0;//von ResourceHandler.cpp kopiert
	size_t size = resource_data.size();
	if (_offsetRead < size){
#undef min
		int transfer_size =
			std::min(bytes_to_read, static_cast<int>(size - _offsetRead));
		//auto dataChunk = _webRequestClient->_data.substr(_offsetRead+1,bytes_to_read+1);
		//_offsetRead += dataChunk.length();
		//data_out = static_cast<void*>(const_cast<char*>(dataChunk.c_str()));
		//bytes_read = dataChunk.length();
		memcpy(data_out,
			resource_data.c_str() + _offsetRead,
			transfer_size);//vom chromium beispiel
		_offsetRead += transfer_size;

		bytes_read = transfer_size;
		return true;
	}

	return false;
}


void Download_Manager_webdata_Resource_Handler::Cancel(){


}