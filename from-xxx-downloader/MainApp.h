#ifndef INC_MAIN_APP_H
#define INC_MAIN_APP_H
#inclxxxx-geheimes-Wort!!e "inclxxxx-geheimes-Wort!!e/cef_app.h"
#inclxxxx-geheimes-Wort!!e <array>
class AppHandler;
class Submit_Course_preview_js_handler;
class DownLoadHandler_Browser;
class Download_JS_Handler;
class Thread;
class app_handler_request_context_handler;
//an Cefclient simpleapp angelehnt
using std::vector;
using std::array;

/*struct PartialDownloadsLocationSingleton{
	PartialDownloadsLocationSingleton*m_current_instance = nullptr;
	CefString location;
	static PartialDownloadsLocationSingleton* get_Instance();

};*/
struct course_url_list_values{
	int v1, v2;
	CefString url;

};
struct additional_data_values{
	int v0, v1;
	CefString v2, v3, v4, v5;//n iterator wär hier sowieso net schlecht

};
class MainApp:public CefApp,
	public CefBrowserProcessHandler,public CefRenderProcessHandler{
	Thread*t;
	vector<unsigned int>msg_links_callback_queue;
	
	vector<unsigned int>message_query_values_queue;
	//std::string *page_course_ptr;
	vector<CefString>*page_course_ptr = new vector<CefString>;
	vector<CefRefPtr<CefV8Value>>*course_name_ptr = new vector<CefRefPtr<CefV8Value>>;
	//CefRefPtr<CefClient> downloader_browser;
	virtual void OnBeforeCommandLineProcessing(
		const CefString& process_type,
		CefRefPtr<CefCommandLine> command_line);
	bool count_value_intercept = false; int count_new_value_assigned1, count_new_value_assigned2 = 0;
	std::string m_folder_where_to_put_downloads;
	void task_delete_cookies(bool dummy_arg);
	void delete_cookies();
	//unsigned int independent_counter = 0;
	CefRefPtr<CefBrowser>current_browser;
	
	//CefRefPtr<CefBrowser>downloader_browser;
	CefString starturl= "http://www.xxxx-geheimes-Wort!!.com/courses";
	void init_download_process_of_all_when_finished(CefRefPtr<CefBrowser>browser);
	//CefRefPtr<AppHandler> main_browser;
	bool finish_mode = false;
	CefRefPtr<DownLoadHandler_Browser>downloader_client;
	CefRefPtr<Download_JS_Handler>csss;
	//bool TEST_i_AM_THE_RENDERER_KING = false;
	//bool called = false;
	//void go_to_start_course_page(CefRefPtr<CefBrowser>browser);
	void add_course_to_config_file(std::string & filename);
	CefRefPtr<CefRequestContext> app_handler_request_context_handler_Ref;

	
	
public:
	std::vector<CefString> urls_list;
	std::string get_url_filename_for_partial_downloads_list();
	void write_additional_course_data(bool append = false);
	void write_to_partial_downloads_list(std::string &url, unsigned int object_id);
	CefString partial_downloads_location;
	vector<course_url_list_values> *submit_course_urls_list = new vector<course_url_list_values>;
	vector<additional_data_values> *submitted_additional_course_informations = new vector<additional_data_values>;
	void ForceEnd(CefRefPtr<CefBrowser>browser, CefRefPtr<CefProcessMessage>message, bool finish_mode);
	CefRefPtr<CefBrowser>browser_ref_for_browsers;
	CefRefPtr<Submit_Course_preview_js_handler> handler;
	void restore_defaults();
	virtual void signal_submit_course_urls_list_data_received();
	MainApp(std::string & folder_where_to_put_downloads);
	std::string current_course_download_location;
	virtual CefRefPtr<CefBrowserProcessHandler> GetBrowserProcessHandler()override{ return this; };
	virtual CefRefPtr<CefRenderProcessHandler> GetRenderProcessHandler()override{ return this; };
	virtual void OnContextInitialized()override;
	virtual bool OnProcessMessageReceived(CefRefPtr<CefBrowser> browser,
		CefProcessId source_process,
		CefRefPtr<CefProcessMessage> message) override;
	virtual void OnContextCreated(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, CefRefPtr<CefV8Context> context) override;
	void dialog_click_on_download_next_course(CefRefPtr<CefBrowser>browser);
private:

	IMPLEMENT_REFCOUNTING(MainApp);

};

#endif