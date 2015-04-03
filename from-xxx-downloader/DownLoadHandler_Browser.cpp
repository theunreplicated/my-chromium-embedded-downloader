#inclxxxx-geheimes-Wort!!e "DownLoadHandler_Browser.h"
#inclxxxx-geheimes-Wort!!e "inclxxxx-geheimes-Wort!!e/base/cef_bind.h"
#inclxxxx-geheimes-Wort!!e "inclxxxx-geheimes-Wort!!e/cef_app.h"
#inclxxxx-geheimes-Wort!!e "inclxxxx-geheimes-Wort!!e/wrapper/cef_closure_task.h"
#inclxxxx-geheimes-Wort!!e "inclxxxx-geheimes-Wort!!e/wrapper/cef_helpers.h"
#inclxxxx-geheimes-Wort!!e "path_helper.h"
#inclxxxx-geheimes-Wort!!e "config_file_io.h"
#inclxxxx-geheimes-Wort!!e "picojson.h"
#inclxxxx-geheimes-Wort!!e "string_helper.h"
#inclxxxx-geheimes-Wort!!e "Thread.h"
#inclxxxx-geheimes-Wort!!e "browser_references.h"
//kopiert von AppHandler.cpp
using std::string;
vector<string> file_path_for_dl_thread_queue;
bool thread_idle = true;
CRITICAL_SECTION critical_section_dl_folder;
HANDLE thread_event_change_downloaded_files;


picojson::value::array read_video_urls_data(string base_path){
	Config_File_IO cf(base_path + "\\video_urls.json");
	auto check = cf.check_if_exists();
	DCHECK(check.result_operation);//vllt. wäre ein continue besser
	

	string data = check.contents_get();/*wäre sowieso gut wenn exceptions da verwendet würden*/

	//process(prozessieren auf DEutsch;-)) nun json-daten
	std::stringstream new_stringstream; picojson::value vi;
	data.erase(data.begin(), data.begin() + 1);
	new_stringstream << "[" << data << "]";

	new_stringstream >> vi;
	const picojson::value::array& obj = vi.get<picojson::array>();

	return obj;
}
DWORD WINAPI dl_file_save_thread(void*dummy_argument){//am besten wäre's wenn der thread n klassen-member wäre,geht vllt. mit userdata von der winapi
	while (true){

		DWORD wait_result = WaitForSingleObject(thread_event_change_downloaded_files, INFINITE);
		if (wait_result == WAIT_OBJECT_0)//z.t. von stackoverflow
		{


			thread_idle = false;
			while (file_path_for_dl_thread_queue.size() > 0){
				//LPCRITICAL_SECTION cs;
			
				auto obj = read_video_urls_data(file_path_for_dl_thread_queue[0]);
				//auto ar=obj.begin()->get<picojson::array>();
				obj.erase(obj.begin());
				std::ofstream ofx;//von mainapp.cpp kopiert
				ofx.open(file_path_for_dl_thread_queue[0] + "\\video_urls.json", std::ios::out | std::ios::binary);
				string val = picojson::value(obj).serialize();
				val.erase(val.begin(),val.begin()+1);
				val.erase(val.size() - 1);
				ofx << "," << val;
				ofx.close();
				::EnterCriticalSection(&critical_section_dl_folder);
				file_path_for_dl_thread_queue.erase(file_path_for_dl_thread_queue.begin());
				::LeaveCriticalSection(&critical_section_dl_folder);
			}
			::ResetEvent(thread_event_change_downloaded_files);
			thread_idle = true;

		}
		else {
			::MessageBox(NULL, TEXT("sum thin went wong"), TEXT("went won sthr.road xy12, ny 512"), MB_OK);
		}




	}


}
CefRefPtr<CefDownloadHandler>DownLoadHandler_Browser::GetDownloadHandler(){ 
	return this; 
};
DownLoadHandler_Browser::DownLoadHandler_Browser(std::vector<course_url_list_values> *submit_course_urls_list, MainApp*mainapp){
	//m_submit_course_urls_list = submit_course_urls_list;
	//m_mainapp = mainapp;
	downloader_browser = this;
	::InitializeCriticalSection(&critical_section_dl_folder);
	thread_event_change_downloaded_files=Threading::event_create();
	Thread t(dl_file_save_thread);
}

DownLoadHandler_Browser::~DownLoadHandler_Browser(){
	::DeleteCriticalSection(&critical_section_dl_folder);
}
/*
std::vector<std::string> DownLoadHandler_Browser::compare_with_list_Download_queue_course_vectors(std::vector<std::string> cmp_vector){
	std::vector<std::string>cmp_result;
	//yield return wäre hier gut,ist aber möglich mit viel aufwand//coroutine(vllt.auch für nested functions,wäre was )
	unsigned int  run_to_size = max(cmp_vector.size(), list_download_queue_folders_of_courses.size());/*std wäre besser als die windows macros*/
	//for (unsigned int i = 0; i < run_to_size; i++){
		//@TODO:gucken ob hier alles so stimmt,nein,eben net

	//}
	/*for (string i : cmp_vector){
		for (string j : list_download_queue_folders_of_courses){
			if (i == j){ cmp_result.push_back(i); break; }


		}

	}
	return cmp_result;
}*/
std::vector<std::string> DownLoadHandler_Browser::compare_with_list_Download_queue_course_vectors(std::vector<std::string> cmp_vector){
	for (auto j = cmp_vector.begin(); j < cmp_vector.end();){
		bool increment = false;
		for (auto i = list_download_queue_folders_of_courses.begin(); i < list_download_queue_folders_of_courses.end(); i++){
			if (*i == *j){
				increment = true;
				j = cmp_vector.erase(j);
				break;
			}
		}

		if (!increment){ j++; }//geht vllt. auch ohne if mit anfangs begin()-1 als Iterator-Startwert und gleich j++, aber bin mir net sicher,kann auch genauso gut net gehen
	}
	return cmp_vector;
}
bool DownLoadHandler_Browser::add_all_elements_to_html_download_queue(){
	//@TODO:das javascript-array soll zT.ersetzt werden
	std::string fullpath = get_current_application_path() + "\\" + PATH_COMPLTEDED_COURSE_CONFIG_PATH;
	Config_File_IO cf(fullpath);
	auto check=cf.check_if_exists();
	if (!check.result_operation){ return false; }
	//CHECK(check.result_operation);
	string folder_locations=check.contents_get();
	//folder_locations.erase(folder_locations.begin(),folder_locations.begin());//gehts so net
	//DCHECK(folder_locations[0]!='?');
	if (folder_locations.find("?") == std::string::npos){ return false; }
	folder_locations.erase(folder_locations.begin(), folder_locations.begin() + 1);
	std::string::size_type found_q = folder_locations.find("?");
	std::vector<std::string>list_str;
	if (found_q != std::string::npos){
		
		do{
			//last_found_q = found_q;

			list_str.push_back(folder_locations.substr(0, found_q));
			folder_locations.erase(0, found_q + 1);
			found_q = folder_locations.find("?");


		} while (found_q != std::string::npos);//@TODO:vllt. wäre ne einfache while besser mit einfachem löschen von dem 1. element
	}
	list_str.push_back(folder_locations);
	std::vector<string>toadd;
	if (list_download_queue_folders_of_courses.size() >0 ){//Um doppelete zu verhindern//@TODO:testen,bei weitem keine 100% code coverage!!lächerlich so ein VErgleich
		toadd = compare_with_list_Download_queue_course_vectors(list_str);//geht wohl so net@TODO:das hier hinkriegen
	}//Warum?wenn noch einige Gruppen in der Download-Queue sin,sind sie noch nicht weggelöscht beim erneuten Laden der Config-Folder-Datei,werden also nochmal geladen
	else{
		toadd = list_str;
	}
	list_download_queue_folders_of_courses.insert(list_download_queue_folders_of_courses.end(), toadd.begin(), toadd.end());

	std::string gen_js_code = "sd_site.download_list_hide();";
	for (string x : toadd){
		auto pos=x.find_last_of("/");
		if (pos == std::string::npos){

			pos = x.find_last_of("\\");
		}
		string name = x.substr(pos);
		gen_js_code += "var current_grouppe=sd_site.addGroup('"+name+"'," + std::to_string(global_ref_cpp_id_group++) + ");";
		
		auto obj = read_video_urls_data(x);
		group_c_ref_download_folder.push_back(x);
		
		for (picojson::value::array::const_iterator it = obj.begin(); it != obj.end(); ++it) {
			const picojson::value::array& obj_r = it->get < picojson::array>();
			//MessageBoxA(NULL, obj_r.at(0).to_str().c_str(), "dfd", MB_OK);
			
			array<string, 3>dv = { obj_r.at(0).to_str(), obj_r.at(1).to_str(), obj_r.at(2).to_str() };
			gen_js_code += "sd_site.addElement('" + dv[1]+ "__" + dv[2]+ "','"+dv[0]+"',0,"+dv[1]+","+dv[2]+",current_grouppe);";


		}


	}

	//gen_js_code += "sd_site.state_control_click(0);"
		gen_js_code+="sd_site.download_list_show();"; //submit_course_list_elem_ptr = 0;
	current_browser->GetMainFrame()->ExecuteJavaScript(gen_js_code, current_browser->GetMainFrame()->GetURL(), 0);
	//nun alle urls.json derer öffnen

	
}
/*void DownLoadHandler_Browser::add_all_elements_to_html_download_queue(CefRefPtr<CefBrowser>browser){
	std::string gen_js_code = "sd_site.download_list_hide();";
	CHECK(m_submit_course_urls_list->size()>=0);
	for (auto&  data:*m_submit_course_urls_list){
		gen_js_code += "sd_site.addElement('" + std::to_string(data[1]->GetIntValue())+"__"+std::to_string(data[2]->GetIntValue())+"',0);";
		//@TODO:urls übergeben
	}
	//@TODO:start download queue,v.a. bei complete
	gen_js_code += "sd_site.state_control_click(0);sd_site.download_list_show();"; submit_course_list_elem_ptr = 0;
	browser->GetMainFrame()->ExecuteJavaScript(gen_js_code, browser->GetMainFrame()->GetURL(), 0);

}*/
bool DownLoadHandler_Browser::OnProcessMessageReceived(CefRefPtr<CefBrowser> browser,
	CefProcessId source_process,
	CefRefPtr<CefProcessMessage> message){
	
	if (message->GetName() == "start_download"){
		if (download_id_lock){
			while (download_id_lock == true){
				__asm{nop}/*sleep?,darf nicht von VS wegoptimiert werden*/ }
			//throw std::runtime_error("programm-fehler-dachte nicht dass das passieren konnte-liste implementiern hieer oder vector(eigentlich so dasselbe)"); 
			
		}
		current_download_id = message->GetArgumentList()->GetInt(1);
		current_download_xxxx-geheimes-Wort!!d_id_pair = { message->GetArgumentList()->GetInt(2), message->GetArgumentList()->GetInt(3) };//so geht das initialisiern beim std::array net?
		browser->GetHost()->StartDownload(message->GetArgumentList()->GetString(0));
		current_c_cId = message->GetArgumentList()->GetInt(4);
		path_folder_where_to_put_downloads_in = group_c_ref_download_folder[current_c_cId];
		
		download_id_lock = true;
		return true;
	}
	else if (message->GetName() == "pause_download"){
		if (download_id_lock){
			while (download_id_lock == true){
				__asm{nop}
			}//https://www.c-plusplus.net/forum/279961-full/ *sleep?,darf nicht von VS wegoptimiert werden*/ 
			//throw std::runtime_error("programm-fehler-dachte nicht dass das passieren konnte-liste implementiern hieer oder vector(eigentlich so dasselbe)"); 
			
		}
		pause_id= get_dl_item_id_for_js_id(message->GetArgumentList()->GetInt(0));
		pause_now = true; return true;
	}
	else if (message->GetName() == "resume_download"){
		if (download_id_lock){
			while (download_id_lock == true){
				__asm{nop}
			}
			//throw std::runtime_error("programm-fehler-dachte nicht dass das passieren konnte-liste implementiern hieer oder vector(eigentlich so dasselbe)"); 
			
		}
		resume_id = get_dl_item_id_for_js_id(message->GetArgumentList()->GetInt(0));
		resume_now = true; return true;
	}
	//else if (message->GetName() == "folder_where_to_put_downloads"){
		//path_folder_where_to_put_downloads_in = message->GetArgumentList()->GetString(0);war vorher Kardinalfehler(hat zum Glück nix mit dem Papst zu tun,ordinal-und kardinal-typen(nicht als Mensch)) brauche ma nimmi!!yay!und 3-faches yuyuuuh, warum nur? fragt sich der fragende Bürger
		//return true;
	//}
	else if (/*(message->GetName() == "you-can-begin-now-with-boost-dl") ||*/ (message->GetName() == "js_code_initialized")){
		//int ident=m_mainapp->browser_ref_for_browsers->GetIdentifier();
		add_all_elements_to_html_download_queue();

		return true;
	}
	else if (message->GetName() == "download_of_group_finished"){
		auto group_id = message->GetArgumentList()->GetInt(0);
		//nun von globaler config-datei entfernen
		string value = group_c_ref_download_folder[group_id];
		Config_File_IO cfio(get_current_application_path() + "\\" + PATH_COMPLTEDED_COURSE_CONFIG_PATH);
		auto cs=cfio.check_if_exists();
		CHECK(cs.result_operation);
		string data = cs.contents_get();
		//cs.~Config_File_IO_Checker();
		cs.put_contents(str_replace("?"+value,"",data));//einfach aktueller course rauslöschen

		return true;
	}


	return false;
}
void DownLoadHandler_Browser::OnBeforeDownload(
	CefRefPtr<CefBrowser> browser,
	CefRefPtr<CefDownloadItem> download_item,
	const CefString& suggested_name,
	CefRefPtr<CefBeforeDownloadCallback> callback){
	mapping_id_to_js_id.push_back(current_download_id);
	js_id_download_finished.push_back(false);
	mapping_id_to_download_item_id.push_back(download_item->GetId());
	imaginaerer_zeiger_auf_download_folder_vector.push_back(current_c_cId);
	std::string sn = suggested_name.ToString();
	std::string extension = sn.substr(sn.find_last_of("."), sn.size()-1);
	//@TODO:besserer dateiname,und zwar richtig
	callback->Continue(path_folder_where_to_put_downloads_in + "\\" +
		std::to_string(current_download_xxxx-geheimes-Wort!!d_id_pair.first) + "__" + 
		std::to_string(current_download_xxxx-geheimes-Wort!!d_id_pair.second) + extension, false);//@TODO:path bekommen
	//dl_maybe_Started = true;

	download_id_lock = false;
}
int DownLoadHandler_Browser::get_js_id_for_dl_item_id(uint32 dl_item_id){
	for (std::vector<uint32>::size_type i = 0; i != mapping_id_to_download_item_id.size(); i++) {//http://stackoverflow.com/questions/409348/iteration-over-vector-in-c
		if (mapping_id_to_download_item_id[i] == dl_item_id){
			return mapping_id_to_js_id[i];

			//break;
		}
	}
	
	throw std::runtime_error("Programm-Fehler mannmannmann");
}
uint32 DownLoadHandler_Browser::get_dl_item_id_for_js_id(int dl_item_id){
	for (std::vector<int>::size_type i = 0; i != mapping_id_to_js_id.size(); i++) {//http://stackoverflow.com/questions/409348/iteration-over-vector-in-c
		if (mapping_id_to_js_id[i] == dl_item_id){
			return mapping_id_to_download_item_id[i];

			//break;
		}
	}

	throw std::runtime_error("Programm-Fehler mannmannmann");
}
void DownLoadHandler_Browser::trigger_percentage_change(std::string & id, CefRefPtr<CefBrowser>browser, CefRefPtr<CefDownloadItem> download_item){
	std::string js_str = "sd_site.changePercentageDownload(" + id + "," + std::to_string(download_item->GetPercentComplete()) + ");";
	browser->GetMainFrame()->ExecuteJavaScript(js_str, browser->GetMainFrame()->GetURL(), 0);
	if (download_item->GetPercentComplete() == 100){

		signal_download_finished(browser, download_item);
	}
}
void DownLoadHandler_Browser::signal_download_finished(CefRefPtr<CefBrowser>browser, CefRefPtr<CefDownloadItem> download_item){
	//if (download_item->GetTotalBytes() == download_item->GetReceivedBytes()){
	auto js_id_for_chromium_dl_id = get_js_id_for_dl_item_id(download_item->GetId());
	if (!js_id_download_finished[js_id_for_chromium_dl_id]){//ist notwendig
		dl_maybe_Started = false;
		js_id_download_finished[js_id_for_chromium_dl_id] = true;
		//trigger_percentage_change(std::to_string(js_id_for_chromium_dl_id), browser, download_item);
		string js_id = std::to_string(js_id_for_chromium_dl_id);
		std::string js_str = "sd_site.markAsFinished(" + js_id + ");";
		{//finish,also aus video_urls.json element rauslöschen
			//Config_File_IO cf();
			//while (!thread_idle){ __asm{nop} };//warten auf thread,falls noch net fertig
			::EnterCriticalSection(&critical_section_dl_folder);
			file_path_for_dl_thread_queue.push_back(group_c_ref_download_folder[imaginaerer_zeiger_auf_download_folder_vector[js_id_for_chromium_dl_id]]);//ohne locking aber egal,brauch man so wie ichs sehe hier net
			::LeaveCriticalSection(&critical_section_dl_folder);
			::SetEvent(thread_event_change_downloaded_files);

			//kann zu ner race condition führen,wenn der thread nicht mehr mitkommt

			//auto ah=cf.check_if_exists();
			//CHECK(ah.result_operation);
			//string contents = ah.contents_get();
			//auto pos_of_closing_brackets=contents.find_first_of("\"]");//zu problematisch,falls in get_string
			//if (pos_of_closing_brackets != std::string::npos){
			//	contents.erase(contents.begin(),pos_of_closing_brackets);


			//}


		}
		/*std::string */js_str += "sd_site.start_download_of_next_item(" + js_id + ");";
		browser->GetMainFrame()->ExecuteJavaScript(js_str, browser->GetMainFrame()->GetURL(), 0);
		//}//@TODO:check ob richtig gedownloadet
	}

}
void DownLoadHandler_Browser::OnDownloadUpdated(
	CefRefPtr<CefBrowser> browser,
	CefRefPtr<CefDownloadItem> download_item,
	CefRefPtr<CefDownloadItemCallback> callback){
	
	//if (download_item->IsValid()){

		//trigger_percentage_change(std::to_string(get_js_id_for_dl_item_id(download_item->GetId())),browser,download_item);
		//}
	
	if (download_item->IsInProgress()){
		if (pause_now && (download_item->GetId() == pause_id)){
			callback->Pause();}
		if (resume_now && (download_item->GetId() == resume_id)){ 
			callback->Resume(); resume_now = false; pause_now = false;}
		
		try{
			trigger_percentage_change(std::to_string(get_js_id_for_dl_item_id(download_item->GetId())), browser, download_item);
		}
		catch (std::runtime_error &e){
			//ich glaub die exceptions sollte man net so häufig nutzen wie hier,also default mäßig eher net

		}
	}
		if (download_item->IsComplete())
		{
			auto js_id_for_chromium_dl_id = get_js_id_for_dl_item_id(download_item->GetId());
			trigger_percentage_change(std::to_string(js_id_for_chromium_dl_id), browser, download_item);
			signal_download_finished(browser,download_item);
			

			//if (m_submit_course_urls_list->size() >= (++submit_course_list_elem_ptr + 1)){
				//js str fehlt hier
				//browser->GetMainFrame()->ExecuteJavaScript(js_str, browser->GetMainFrame()->GetURL(), 0);
			//} else{/*alles fertig?TODO*/ }

			
		}
		if (download_item->IsCanceled()){
			dl_maybe_Started = false;
			
			std::string js_str = "sd_site.markAsAborted(" + std::to_string(get_js_id_for_dl_item_id(download_item->GetId())) + ");";
				browser->GetMainFrame()->ExecuteJavaScript(js_str, browser->GetMainFrame()->GetURL(), 0);
			
		}


	//}
		//if (download_item->I)
		
}

//wie vorhin vom beispiel cefclient vom CefProjekt
void DownLoadHandler_Browser::CloseAllBrowsers(bool force_close) {
	if (!CefCurrentlyOn(TID_UI)) {
		// Execute on the UI thread.
		CefPostTask(TID_UI,
			base::Bind(&DownLoadHandler_Browser::CloseAllBrowsers, this, force_close));
		return;
	}

	if (browser_list_.empty())
		return;

	BrowserList::const_iterator it = browser_list_.begin();
	for (; it != browser_list_.end(); ++it)
		(*it)->GetHost()->CloseBrowser(force_close);
}
void DownLoadHandler_Browser::OnAfterCreated(CefRefPtr<CefBrowser> browser) {
	CEF_REQUIRE_UI_THREAD();
	current_browser = browser;
	//auto msg=CefProcessMessage::Create("handshake_with_mainapp_getting_to-Know_each_other");
	//browser->SendProcessMessage(PID_RENDERER,msg);
	
	//test_browser_identifier = browser->GetIdentifier();
	// Add to the list of existing browsers.
	browser_list_.push_back(browser);
}
bool DownLoadHandler_Browser::DoClose(CefRefPtr<CefBrowser> browser) {
	CEF_REQUIRE_UI_THREAD();

	// Closing the main window requires special handling. See the DoClose()
	// documentation in the CEF header for a detailed destription of this
	// process.
	if (browser_list_.size() == 1) {
		// Set a flag to indicate that the window close should be allowed.
		is_closing_ = true;
	}

	// Allow the close. For windowed browsers this will result in the OS close
	// event being sent.
	return false;
}

void DownLoadHandler_Browser::OnBeforeClose(CefRefPtr<CefBrowser> browser) {
	CEF_REQUIRE_UI_THREAD();

	// Remove from the list of existing browsers.
	BrowserList::iterator bit = browser_list_.begin();
	for (; bit != browser_list_.end(); ++bit) {
		if ((*bit)->IsSame(browser)) {
			browser_list_.erase(bit);
			break;
		}
	}

	if (browser_list_.empty()) {
		// All browser windows have closed. Quit the application message loop.
		CefQuitMessageLoop();
	}
}