#inclxxxx-geheimes-Wort!!e "ResourceHandler.h"
#inclxxxx-geheimes-Wort!!e "WebRequestClient.h"

#inclxxxx-geheimes-Wort!!e <map>
#inclxxxx-geheimes-Wort!!e <list>
#define NOMINMAX
#inclxxxx-geheimes-Wort!!e <algorithm>
#inclxxxx-geheimes-Wort!!e "inclxxxx-geheimes-Wort!!e\cef_response.h"
//empfehlung:nur bei html usw. denn z.b. bei mp4 videos kommt: unde es spielt auch net ab: Check failed: blob_context;youtube scheint aber trotzdem zu gehn
//oder auch fehler von chromium,hat mit flash zu tun wohl : https://code.google.com/p/chromium/issues/detail?id=419409
using std::string;
CefResponse::HeaderMap GetHeaderMultimap(CefRefPtr<CefResponse>response){//http://code.google.com/p/cefpython/source/browse/cefpython/response_cef1.pyx aber abgekürzt und z.t. geändert
	CefResponse::HeaderMap cefHeaderMap;//@TOOD:mit pointer
	response->GetHeaderMap(cefHeaderMap);
	/*std::vector<CefString,CefString> pyHeaderMultimap;
	std::multimap<CefString, CefString>::iterator iterator = cefHeaderMap.begin();
	CefString cefKey;
	CefString cefValue;
	//string pyKey;
	//string pyValue;
	while (iterator != cefHeaderMap.end()){
	cefKey = iterator->first;
	cefValue = iterator->second;
	pyHeaderMultimap.push_back({cefKey, cefValue});

	}*/
	return cefHeaderMap;
}

//https://code.google.com/p/cefpython/source/browse/cefpython/cef3/linux/binaries_64bit/wxpython-response.py?r=26d373f81ca9
ResourceHandler::ResourceHandler(CefRefPtr<AppHandler> sh, CefRefPtr< CefBrowser >browser, CefRefPtr< CefFrame >frame, CefRefPtr< CefRequest >request, ResourceHandler_ActionType how_to_handle)/*:_clientHandler(sh)*/{
	_clientHandler = sh;
	_browser = browser;
	_frame = frame;
	_request = request;
	_offsetRead = 0;
	m_action_type_for_webrequest_data_handler = how_to_handle;


}

bool ResourceHandler::ProcessRequest(CefRefPtr<CefRequest> request, CefRefPtr<CefCallback> callback){
	_responseHeadersReadyCallback = callback;
	_webRequestClient = new WebRequestClient(this, callback,m_action_type_for_webrequest_data_handler);
	request->SetFlags(UR_FLAG_ALLOW_CACHED_CREDENTIALS | UR_FLAG_SKIP_CACHE);
	_webRequest = CefURLRequest::Create(request, _webRequestClient);
	return true;
}

void ResourceHandler::GetResponseHeaders(CefRefPtr<CefResponse> response, int64& response_length, CefString& redirectUrl){
	CefRefPtr<CefResponse>wrcResponse = _webRequestClient->_response;
	if (_webRequestClient->_response){

		
		response->SetStatus(wrcResponse->GetStatus());
		{

			auto status_text_to_pass = wrcResponse->GetStatusText();
			if (!status_text_to_pass.empty()){//normal bei chrome??ajax request soll manchmal 0 zurückgeben,wohl bei fail
				response->SetStatusText(status_text_to_pass);
			}
			else{
				::OutputDebugStringA("status text empty");//copy n paste//@TODO:vllt. das zu nem Makro machen
			}

		}
		{
			auto data_to_pass = wrcResponse->GetMimeType();
			if (!data_to_pass.empty()){
				//@TODO:handle wenn getmimetype null zurückgibt:fehler bei setmimetype
				response->SetMimeType(data_to_pass);
			}
			else{
				::OutputDebugStringA("mime type empty");
			}
		}
		CefResponse::HeaderMap mp = GetHeaderMultimap(wrcResponse);
		//if(!mp)
		response->SetHeaderMap(mp);

		response_length = _webRequestClient->_dataLength;
		if (_webRequestClient->_dataLength == 0){
			OutputDebugStringA("no response length seemingly Probably a cached page? Or a redirect?");
		}
	}
	else{
		::OutputDebugStringA("no valid response object??semingly");
	}
}

bool ResourceHandler::ReadResponse(void* data_out, int bytes_to_read, int& bytes_read, CefRefPtr<CefCallback> callback){
	bytes_read = 0;
	size_t size = _webRequestClient->_dataLength;
	if (_offsetRead < size){
#undef min
		int transfer_size =
			std::min(bytes_to_read, static_cast<int>(size - _offsetRead));
		//auto dataChunk = _webRequestClient->_data.substr(_offsetRead+1,bytes_to_read+1);
		//_offsetRead += dataChunk.length();
		//data_out = static_cast<void*>(const_cast<char*>(dataChunk.c_str()));
		//bytes_read = dataChunk.length();
		memcpy(data_out,
			_webRequestClient->_data.c_str() + _offsetRead,
			transfer_size);//vom chromium beispiel
		_offsetRead += transfer_size;

		bytes_read = transfer_size;
		return true;
	}

	return false;
}
void ResourceHandler::Cancel(){
	//okso,ist python pass
}