#ifndef INC_DOWNLOAD_HANDLER_BROWSER_H
#define INC_DOWNLOAD_HANDLER_BROWSER_H
#inclxxxx-geheimes-Wort!!e "inclxxxx-geheimes-Wort!!e/cef_client.h"
#inclxxxx-geheimes-Wort!!e "inclxxxx-geheimes-Wort!!e\cef_v8.h"
#inclxxxx-geheimes-Wort!!e "inclxxxx-geheimes-Wort!!e\base\cef_lock.h"
#inclxxxx-geheimes-Wort!!e "MainApp.h"
#inclxxxx-geheimes-Wort!!e <list>
#inclxxxx-geheimes-Wort!!e <array>
class AppHandler;
//Das alles hier ist ein Heap(läuft aber größtenteils trotzdem auf dem Stack oO)
class DownLoadHandler_Browser :public CefClient, CefLifeSpanHandler, public CefDownloadHandler, public CefRequestHandler{
	IMPLEMENT_REFCOUNTING(DownLoadHandler_Browser);
	friend AppHandler;
	typedef std::list<CefRefPtr<CefBrowser> > BrowserList;
	BrowserList browser_list_;//auch kopiert von AppHandler.h mit unten den 3 funktionen vom lifespanhandler+closeallbrowsers
	int current_download_id;//=0/*0 sinnlos*/;
	std::pair<int, int>current_download_xxxx-geheimes-Wort!!d_id_pair;
	unsigned int submit_course_list_elem_ptr;
	std::vector<int>imaginaerer_zeiger_auf_download_folder_vector;
	int current_c_cId;
	bool download_id_lock = false,dl_maybe_Started=false;
	std::vector<int>mapping_id_to_js_id; std::vector<uint32>mapping_id_to_download_item_id;
	//unsigned int mapping_idcounter = 0,mapping_idcounter_dl_item_id=0;
	bool is_closing_ = false, pause_now=false,resume_now = false; uint32 pause_id,resume_id = 0;/*0 sinnlos*/
	uint32 get_dl_item_id_for_js_id(int dl_item_id); std::string path_folder_where_to_put_downloads_in;
	virtual void OnAfterCreated(CefRefPtr<CefBrowser> browser) OVERRIDE;//scheint trotzdem nicht zu gehen
	virtual bool DoClose(CefRefPtr<CefBrowser> browser) OVERRIDE;
	virtual void OnBeforeClose(CefRefPtr<CefBrowser> browser) OVERRIDE;
	void CloseAllBrowsers(bool force_close);
	void signal_download_finished(CefRefPtr<CefBrowser>browser, CefRefPtr<CefDownloadItem> download_item);
	int get_js_id_for_dl_item_id(uint32 dl_item_id); //std::vector<std::array<CefRefPtr<CefV8Value>, 3>> *m_submit_course_urls_list;
	CefRefPtr<CefBrowser>current_browser;
	void trigger_percentage_change(std::string & id, CefRefPtr<CefBrowser>browser, CefRefPtr<CefDownloadItem> download_item);
	bool add_all_elements_to_html_download_queue();
	//mutable base::Lock lock_;//vom cefclient beispiel
	std::vector<std::string>list_download_queue_folders_of_courses;
	bool do_send_process_message_again = false; unsigned int global_ref_cpp_id_group = 0; std::vector<std::string>group_c_ref_download_folder;
	std::vector<bool>js_id_download_finished;
	//int test_browser_identifier = -999;
	//MainApp*m_mainapp;
	std::vector<std::string> compare_with_list_Download_queue_course_vectors(std::vector<std::string> cmp_vector);
	virtual bool OnBeforeBrowse(CefRefPtr<CefBrowser> browser,
		CefRefPtr<CefFrame> frame,
		CefRefPtr<CefRequest> request,
		bool is_redirect) {
		//int identifier = browser->GetIdentifier();
		//int ident2 = test_browser_identifier;//nutzt nix
		if (!do_send_process_message_again){
		//	CHECK(m_mainapp);
			//int ident = m_mainapp->browser_ref_for_browsers->GetIdentifier();
			auto msg = CefProcessMessage::Create("handshake_with_mainapp_getting_to-Know_each_other");
			browser->SendProcessMessage(PID_RENDERER,msg);
			do_send_process_message_again = true;
		}
		
		return false;
	}
public:
	~DownLoadHandler_Browser();
/*	CefRefPtr<CefBrowser> get_Browser() const {
		base::AutoLock lock_scope(lock_);
		return current_browser;
	}*/
	
/*	virtual CefRefPtr<CefRequestHandler> GetRequestHandler() {
		return this;
	}
	virtual bool OnBeforeResourceLoad(CefRefPtr<CefBrowser> browser,
		CefRefPtr<CefFrame> frame,
		CefRefPtr<CefRequest> request){
		auto url = request->GetURL();
		return false;
	}virtual bool OnBeforeBrowse(CefRefPtr<CefBrowser>browser, CefRefPtr<CefFrame>frame, CefRefPtr<CefRequest>request, bool is_redirect){
		auto url = request->GetURL();
		return false;
	}*/
	/*virtual bool OnBeforeBrowse(CefRefPtr<CefBrowser> browser,
		CefRefPtr<CefFrame> frame,
		CefRefPtr<CefRequest> request,
		bool is_redirect) {
		auto msg = CefProcessMessage::Create("handshake_with_mainapp_getting_to-Know_each_other");
		browser->SendProcessMessage(PID_RENDERER, msg);
		return false;//bei onaftercreated kommt die prozess-message nicht an??

	}*/
	CefRefPtr<CefRequestHandler>GetRequestHandler(){ return this; }
	CefRefPtr<CefLifeSpanHandler>GetLifeSpanHandler(){ return this; };
	DownLoadHandler_Browser(std::vector<course_url_list_values> *submit_course_urls_list, MainApp*mainapp);
	virtual bool OnProcessMessageReceived(CefRefPtr<CefBrowser> browser,
		CefProcessId source_process, 
		CefRefPtr<CefProcessMessage> message) override;
	CefRefPtr<CefDownloadHandler>GetDownloadHandler()override;
	virtual void OnBeforeDownload(
		CefRefPtr<CefBrowser> browser,
		CefRefPtr<CefDownloadItem> download_item,
		const CefString& suggested_name,
		CefRefPtr<CefBeforeDownloadCallback> callback)override;
	virtual void OnDownloadUpdated(
		CefRefPtr<CefBrowser> browser,
		CefRefPtr<CefDownloadItem> download_item,
		CefRefPtr<CefDownloadItemCallback> callback)override;
};
#endif