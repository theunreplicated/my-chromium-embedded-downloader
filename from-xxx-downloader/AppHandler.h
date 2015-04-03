#ifndef INC_APP_HANDLER_H
#define INC_APP_HANDLER_H
#inclxxxx-geheimes-Wort!!e <list>
#inclxxxx-geheimes-Wort!!e "inclxxxx-geheimes-Wort!!e/cef_client.h"
#inclxxxx-geheimes-Wort!!e "inclxxxx-geheimes-Wort!!e\cef_urlrequest.h"
enum ResourceHandler_ActionType{
	ResourceHandler_ActionType_NO_SPECIAL_Behaviour,
	ResourceHandler_ActionType_WANT_TEXT_LECTURE_TYPE,
	ResourceHandler_ActionType_WANT_DATA_IN_ORDER_TO_CAUSE_MODIFICATIONS

};
class AppHandler:public CefClient,public CefDisplayHandler,public CefLifeSpanHandler,public CefLoadHandler,public CefRequestHandler{
	//bool contents_have_been_loaded = false;
	//CefRefPtr<CefBrowser> current_browser;
	bool look_for_pdf_e_book = false;
	
	bool lock_content_data_listener = false, execute_submit_js_once=true;
	std::string m_folder_where_to_put_downloads;
	void task_delete_cookies(bool dummy_arg);
	std::string course_put_downloads_in_here; std::vector<std::string>intercepted_data_queue;
public:
	void send_end_message(CefRefPtr<CefBrowser>browser);
	AppHandler(std::string &folder_where_to_put_downloads);
	void restore_defaults();
	void onResourceInterceptText(CefString url, std::string &data);
	std::string onResourceModifytemplate_js_by_xxxx-geheimes-Wort!!(CefString url, std::string &data);
	virtual bool OnProcessMessageReceived(CefRefPtr<CefBrowser> browser,
		CefProcessId source_process,
		CefRefPtr<CefProcessMessage> message) override;
	virtual bool OnBeforeResourceLoad(CefRefPtr<CefBrowser> browser,
		CefRefPtr<CefFrame> frame,
		CefRefPtr<CefRequest> request)override;
	virtual CefRefPtr<CefResourceHandler> GetResourceHandler(CefRefPtr< CefBrowser > browser, CefRefPtr< CefFrame > frame, CefRefPtr< CefRequest > request)override;
	std::string _OnResourceResponse(CefRefPtr<CefBrowser>browser, CefRefPtr<CefFrame>frame, CefRefPtr<CefRequest>request, CefURLRequest::Status status, CefURLRequest::ErrorCode errorcode, CefRefPtr<CefResponse>response, std::string & data);
	virtual bool OnBeforeBrowse(CefRefPtr<CefBrowser>browser, CefRefPtr<CefFrame>frame, CefRefPtr<CefRequest>request, bool is_redirect)override;
	virtual CefRefPtr<CefRequestHandler> GetRequestHandler() {
		return this;//@TODO:ganz wichtig,hatte ich die ganze Zeit übersehen
	}
	virtual CefRefPtr<CefDisplayHandler> GetDisplayHandler()override{
		return this;
	}
		virtual CefRefPtr<CefLifeSpanHandler> GetLifeSpanHandler()override{
		return this;
	}
		virtual CefRefPtr<CefLoadHandler> GetLoadHandler()override{
		return this;
	}
		
		// CefDisplayHandler methods:
		virtual void OnTitleChange(CefRefPtr<CefBrowser> browser,
		const CefString& title) OVERRIDE;

	// CefLifeSpanHandler methods:
	virtual void OnAfterCreated(CefRefPtr<CefBrowser> browser) OVERRIDE;
	virtual bool DoClose(CefRefPtr<CefBrowser> browser) OVERRIDE;
	virtual void OnBeforeClose(CefRefPtr<CefBrowser> browser) OVERRIDE;

	// CefLoadHandler methods:
	virtual void OnLoadError(CefRefPtr<CefBrowser> browser,
		CefRefPtr<CefFrame> frame,
		ErrorCode errorCode,
		const CefString& errorText,
		const CefString& failedUrl) OVERRIDE;

	// Request that all existing browser windows close.
	void CloseAllBrowsers(bool force_close);

	bool IsClosing() const { return is_closing_; }

private:
	// List of existing browser windows. Only accessed on the CEF UI thread.
	typedef std::list<CefRefPtr<CefBrowser> > BrowserList;
	BrowserList browser_list_;

	bool is_closing_;

	// Inclxxxx-geheimes-Wort!!e the default reference counting implementation.
	IMPLEMENT_REFCOUNTING(AppHandler);
};



#endif