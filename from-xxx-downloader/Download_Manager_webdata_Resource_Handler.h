#ifndef INC_Download_Manager_webdata_Resource_Handler_H
#define INC_Download_Manager_webdata_Resource_Handler_H
#inclxxxx-geheimes-Wort!!e "inclxxxx-geheimes-Wort!!e\cef_resource_handler.h"
#inclxxxx-geheimes-Wort!!e <string>
//#inclxxxx-geheimes-Wort!!e <array>
//#inclxxxx-geheimes-Wort!!e "inclxxxx-geheimes-Wort!!e\cef_v8.h"
class Download_Manager_webdata_Resource_Handler:public CefResourceHandler{
	IMPLEMENT_REFCOUNTING(Download_Manager_webdata_Resource_Handler);
	std::string resource_data; unsigned int _offsetRead=0;
	
public:
	


	Download_Manager_webdata_Resource_Handler();
	bool ProcessRequest(CefRefPtr<CefRequest> request, CefRefPtr<CefCallback> callback)override;
	virtual void GetResponseHeaders(CefRefPtr<CefResponse> response, int64& response_length, CefString& redirectUrl)override;
	virtual bool ReadResponse(void* data_out, int bytes_to_read, int& bytes_read, CefRefPtr<CefCallback> callback)override;
	virtual void Cancel()override;
	//virtual void OnProcessMess
};

#endif