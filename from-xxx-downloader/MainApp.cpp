#inclxxxx-geheimes-Wort!!e "MainApp.h"
#inclxxxx-geheimes-Wort!!e <string>
#inclxxxx-geheimes-Wort!!e "inclxxxx-geheimes-Wort!!e/cef_browser.h"
#inclxxxx-geheimes-Wort!!e "inclxxxx-geheimes-Wort!!e/cef_command_line.h"
#inclxxxx-geheimes-Wort!!e "inclxxxx-geheimes-Wort!!e/wrapper/cef_helpers.h"
#inclxxxx-geheimes-Wort!!e "AppHandler.h"
#inclxxxx-geheimes-Wort!!e "extern\picojson.h"
#inclxxxx-geheimes-Wort!!e "submit_course_preview_js_handler.h"
#inclxxxx-geheimes-Wort!!e <fstream>
#inclxxxx-geheimes-Wort!!e "string_helper.h"
#inclxxxx-geheimes-Wort!!e "xxxx-geheimes-Wort!!_cef_dl_basic_taskdialog.h"
#inclxxxx-geheimes-Wort!!e "download_scheme_handler.h"
#inclxxxx-geheimes-Wort!!e "DownLoadHandler_Browser.h"
#inclxxxx-geheimes-Wort!!e "download_js_handler.h"
#inclxxxx-geheimes-Wort!!e "config_file_io.h"
#inclxxxx-geheimes-Wort!!e "path_helper.h"
#inclxxxx-geheimes-Wort!!e "app_handler_request_context_handler.h"
#inclxxxx-geheimes-Wort!!e "inclxxxx-geheimes-Wort!!e/base/cef_bind.h"
#inclxxxx-geheimes-Wort!!e "inclxxxx-geheimes-Wort!!e/wrapper/cef_closure_task.h"
#inclxxxx-geheimes-Wort!!e "Thread.h"
#define MODE_USE_WINDOWED
#define T_EVENT_THE_SIGNAL_TO_DOWNLOAD 2083
using std::string;
//Cefv8value darf nur im ui thread aufgerufen werden,echt blöd
//an original cefsimple Applcation  orientiert und z.t. kopiert
//HANDLE signal_thread_message_queue_ready;
CefRefPtr<MainApp> mainapp_Ref;
DWORD WINAPI thread_save_course_item_data(void*dummy_arg){
	Threading::register_thread_message_loop();
	//::SetEvent(signal_thread_message_queue_ready);//brauche ma hier net,wisse sowieso dass er in unter der Login-Zeit gertig ist
	MSG msg;
	while (Threading::message_get(msg)){
		switch (msg.message){
		case T_EVENT_THE_SIGNAL_TO_DOWNLOAD:
		{
			picojson::array ayx;  //::MessageBox(NULL, TEXT("video url speichern"), TEXT("yooooo, echt"), MB_OK);
			CefString url = mainapp_Ref->urls_list[msg.lParam];
			ayx.emplace_back(picojson::value(url.ToString()));
			ayx.emplace_back(picojson::value(std::to_string(mainapp_Ref->submit_course_urls_list->at(msg.wParam).v1)));
			ayx.emplace_back(picojson::value(std::to_string(mainapp_Ref->submit_course_urls_list->at(msg.wParam).v2)));
			std::ofstream ofx;
			ofx.open(mainapp_Ref->current_course_download_location + "\\video_urls.json", std::ios::out | std::ios::binary | std::ios::app);
			ofx << "," << picojson::value(ayx);//dann nachher auch 2. Datei automatisch leeren,da die ja mit append funktioniert
			ofx.close();

			if (mainapp_Ref->partial_downloads_location == "" || mainapp_Ref->partial_downloads_location.length() == 0){
				mainapp_Ref->partial_downloads_location = mainapp_Ref->get_url_filename_for_partial_downloads_list();

			}
			mainapp_Ref->write_to_partial_downloads_list(mainapp_Ref->partial_downloads_location.ToString(), msg.wParam);

			mainapp_Ref->write_additional_course_data(true);
			mainapp_Ref->submitted_additional_course_informations->clear();//also dann immer nur Blöcke reinschreiben //@TODO:THREAD


		};/*brreak brauch man afaik net*/ break;


		}


	}
	return 0;
}
void standard_folder_create(std::string& path){
	if (!(::CreateDirectoryA(path.c_str(), NULL) ||
		(GetLastError() == ERROR_ALREADY_EXISTS)))
	{
		::MessageBox(NULL, TEXT("komisch,folder zu erstellen ist schief gelaufen-jeder-soll-merken-dass-das-einfaches-copy-n-paste-ist-im-ProgrammCode-auch-evtl.-Reversengineers-was aber keiner machen wird"), TEXT("Ihre Meinung dazu ,bitte"), MB_OK);
		::PostQuitMessage(0);
		//return false;
	}
	//else{ return true; }


}
MainApp::MainApp(std::string & folder_where_to_put_downloads) {
	m_folder_where_to_put_downloads = folder_where_to_put_downloads;//wird natürlich mehrmals aufgerufen
	CHECK(folder_where_to_put_downloads.size()>0);
	//::MessageBoxA(NULL,"called","called",MB_OK);

	standard_folder_create((m_folder_where_to_put_downloads + std::string("\\_____________directory_of_partial_downloads_list")));
	

}
void MainApp::OnBeforeCommandLineProcessing(
	const CefString& process_type,
	CefRefPtr<CefCommandLine> command_line) {//werte gibts auf peter.sh
	//command_line->AppendSwitchWithValue("renderer-process-limit","1");//so kann ich das Problem umgehen,dass nicht der gleiche Renderer genuttzt wird,aber trotzdem keine gute Lösung,beei mir gehts,da auf dem einen Fenster kaum was gerendert wird,aber sonst net so toll
}

void MainApp::OnContextInitialized() {
	CEF_REQUIRE_UI_THREAD();
	CefRegisterSchemeHandlerFactory("xxxx-geheimes-Wort!!-downloads-view", "", new Download_Scheme_Handler());//sinllos,besser gleich im resource handler vom downloader-browser machen

	// Information used when creating the native window.
	CefWindowInfo window_info;//window info wichtig!
//#if defined(OS_WIN)
	// On Windows we need to specify certain flags that will be passed to
	// CreateWindowEx().
	window_info.SetAsPopup(NULL, "xxxx-geheimes-Wort!!-Downloader4free");
//#endif

	CefRefPtr<AppHandler> handler(new AppHandler(m_folder_where_to_put_downloads));
	//downloader_browser = new DownLoadHandler_Browser();


	cef_string_t encoding_settings;
	encoding_settings.str = L"utf-8";
	encoding_settings.length = 5;
	encoding_settings.dtor = NULL;
	CefBrowserSettings browser_settings;
	browser_settings.default_encoding = encoding_settings;//ansonsten wird beim eigenen resourcehandler bei google auf gut glae/ck angezeigt anstatt dem ü
	std::string url;




	//TEST_i_AM_THE_RENDERER_KING = true;nutzt nichts,instanz wird gelöscht?
	

		
	app_handler_request_context_handler_Ref = CefRequestContext::CreateContext(new app_handler_request_context_handler());
		//app_handler_request_context_handler_Ref = new	app_handler_request_context_handler();
	CefBrowserHost::CreateBrowser(window_info, handler.get(), starturl,
		browser_settings,/*app_handler_request_context_handler_Ref*/NULL/*brauch man wohl net mehr CefRequestContext::CreateContext(app_handler_request_context_handler_Ref)-geht wohl nicht,da er die prozess--einstellung-1 scheinbar ignoriert*//*da steht diese eine Zeile code http://stackoverflow.com/questions/27552022/what-is-the-correct-way-to-use-cefcookiemanager-vc*/);
	url = "xxxx-geheimes-Wort!!-downloads-view://";
	downloader_client = new DownLoadHandler_Browser(submit_course_urls_list/*nutzt wohl nix-wird einfach Kopie erzeugt anscheinend-kann-ja-auch-net-gehen-wenn-schon-dann-mit-ipc*/,this);
	CefBrowserHost::CreateBrowser(window_info, downloader_client /*anders gehts wohl nicht?hmmm..komische@TODO:gucken ob nicht auch direkt aufrufen kann*/, url,
		browser_settings,/* app_handler_request_context_handler_Ref*/NULL);

	//erstelle zweiten browser-für download-manager

	//CefBrowserHost::CreateBrowser(window_info, new DownloadHandler(), ,
	//browser_settings, NULL);
	
}

void MainApp::signal_submit_course_urls_list_data_received(){
	for (auto & object_id : msg_links_callback_queue){
		auto msg = CefProcessMessage::Create("cloxxxx-geheimes-Wort!!front_mp4_link_received_callback");
		msg->GetArgumentList()->SetInt(0, submit_course_urls_list->at(object_id).v1);//scheisse,kriege grade ein vector out of range hier,doch warum submit_course_urls_list==0
		msg->GetArgumentList()->SetInt(1, submit_course_urls_list->at(object_id).v2);

		msg->GetArgumentList()->SetInt(2, object_id);

		current_browser->SendProcessMessage(PID_BROWSER, msg);//gefährlich mit current_browser so
	}
	msg_links_callback_queue.clear();
}
/*bool MainApp::OnProcessMessageReceived(CefRefPtr<CefBrowser> browser,
	CefProcessId source_process,
	CefRefPtr<CefProcessMessage> message){
	//::MessageBox(NULL,TEXT("dfdf"),TEXT("fdfd"),MB_OK);
	if (message->GetName() == "show_dev_tools:" &&handler != nullptr){//Problem;handler=NULL
		//browser->GetHost()->ShowDevTools(window_info, handler, browser_settings, CefPoint());
		return true;
	}
	return false;
}*/
void MainApp::OnContextCreated(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, CefRefPtr<CefV8Context> context){
	//::MessageBox(NULL, TEXT("I am the renderer,praise me"), TEXT("dffd"), MB_OK);
	CefRefPtr<CefV8Value> object = context->GetGlobal();
	
	//page_course_ptr = new std::string;
	//browser_ref_for_browsers = browser;
	//browser->SendProcessMessage(PID_BROWSER,CefProcessMessage::Create("you-can-begin-now-with-boost-dl"));
	mainapp_Ref = this;
	t = new Thread(thread_save_course_item_data);
	
	handler = new Submit_Course_preview_js_handler(submit_course_urls_list, page_course_ptr, submitted_additional_course_informations, course_name_ptr,this);
	handler->download_path = m_folder_where_to_put_downloads;
	object->SetValue("submit_course_preview_urls_begin",
		CefV8Value::CreateFunction("submit_course_preview_urls_begin", handler),
		V8_PROPERTY_ATTRIBUTE_NONE);
	//CRASH//THe crash statt the clash

	object->SetValue("submit_course_preview_urls_end", CefV8Value::CreateFunction("submit_course_preview_urls_end", handler),
		V8_PROPERTY_ATTRIBUTE_NONE);
	object->SetValue("submit_course_preview_urls_data", CefV8Value::CreateFunction("submit_course_preview_urls_data", handler), V8_PROPERTY_ATTRIBUTE_NONE);
	

	object->SetValue("submit_course_url", CefV8Value::CreateFunction("submit_course_url", handler), V8_PROPERTY_ATTRIBUTE_NONE);
	object->SetValue("submit_additional_course_information", CefV8Value::CreateFunction("submit_additional_course_information", handler), V8_PROPERTY_ATTRIBUTE_NONE);
	object->SetValue("get_start_required_ids", CefV8Value::CreateFunction("get_start_required_ids", handler), V8_PROPERTY_ATTRIBUTE_NONE);
	object->SetValue("submit_course_name", CefV8Value::CreateFunction("submit_course_name", handler), V8_PROPERTY_ATTRIBUTE_NONE);
	object->SetValue("unlock_content_data_event", CefV8Value::CreateFunction("unlock_content_data_event", handler), V8_PROPERTY_ATTRIBUTE_NONE);
	object->SetValue("cpp_notify_end_popup_created",CefV8Value::CreateFunction("cpp_notify_end_popup_created",handler),V8_PROPERTY_ATTRIBUTE_NONE);


	//object->SetValue("download_invoke_action", CefV8Value::CreateObject(new Download_JS_Handler_Accessor()), V8_PROPERTY_ATTRIBUTE_NONE);
	CefRefPtr<CefV8Value> obj = CefV8Value::CreateObject(NULL);
	/*auto csss = */csss=new Download_JS_Handler();//qTODO:nur bei dem bestimmten kontext laufen lassen,net immer
	obj->SetValue("start", CefV8Value::CreateFunction("start",csss),V8_PROPERTY_ATTRIBUTE_NONE);
	obj->SetValue("init_JS_Handler", CefV8Value::CreateFunction("init_JS_Handler", csss), V8_PROPERTY_ATTRIBUTE_NONE);
	obj->SetValue("resume", CefV8Value::CreateFunction("resume", csss), V8_PROPERTY_ATTRIBUTE_NONE);
	obj->SetValue("pause", CefV8Value::CreateFunction("pause", csss), V8_PROPERTY_ATTRIBUTE_NONE);
	obj->SetValue("download_of_group_finished", CefV8Value::CreateFunction("download_of_group_finished",csss),V8_PROPERTY_ATTRIBUTE_NONE);
	

	object->SetValue("download_invoke_action",obj,V8_PROPERTY_ATTRIBUTE_NONE);

	//init ui ende
	//using picojson::array; using picojson::value;// using picojson::object;
	/* array ay;
	std::vector<std::string> testv;
	testv.push_back("http:~~tÜÄ1");
	testv.push_back("g-euul");
	for (auto data : testv){
	ay.push_back(picojson::value(data));
	}*/


	/*std::vector<std::array<CefRefPtr<CefV8Value>, 3>> vy;
	std::array<CefRefPtr<CefV8Value>, 3> dc = { CefV8Value::CreateString("hxxp://google.com/?oopd?fc"), CefV8Value::CreateInt(225), CefV8Value::CreateInt(011) };
	vy.push_back(dc);
	std::array<CefRefPtr<CefV8Value>, 3> /*Häh?wenn ich nochmal neu deklariere und dc verwende=>Error????*//*du = { CefV8Value::CreateString("hxxps://fb:com.saarland"), CefV8Value::CreateInt(999), CefV8Value::CreateInt(9999) };
	vy.push_back(du);
	array ay;
	for (auto data : vy){
	picojson::object oy; oy["url"] = picojson::value(data[0].get()->GetStringValue()); oy["l1_key"] = picojson::value(std::to_string(data[1].get()->GetIntValue()));
	oy["l2_key"] = picojson::value(std::to_string(data[2].get()->GetIntValue()));

	ay.push_back(picojson::value(oy));


	}
	picojson::value v(ay);

	std::ofstream ofs;
	ofs.open("D:\\Aktuelle Dateien\\ultimateFORCE\\Eigene Dokumente\\cef_binary_3.2171.1901_windows32\\course_json_path\\test.json", std::ios::out | std::ios::binary);
	ofs << v;//dann nachher auch 2. Datei automatisch leeren,da die ja mit append funktioniert
	ofs.close();
	//TODO:danach noch zweite datei in append-modus für dl-url
	std::ifstream in("D:\\Aktuelle Dateien\\ultimateFORCE\\Eigene Dokumente\\cef_binary_3.2171.1901_windows32\\course_json_path\\test.json",std::ios::in|std::ios::binary);
	picojson::value vi; std::stringstream ss;
	if (in){
	ss << in.rdbuf();
	in.close();
	}
	else{ throw std::runtime_error("file not found"); }
	ss >> vi;
	if (!picojson::get_last_error().empty()){
	throw std::runtime_error("errors occurred");

	}
	if (!vi.is<picojson::array>()) {
	throw std::runtime_error("mismatch ");

	}
	const picojson::value::array& obj = v.get<picojson::array>();
	for (picojson::value::array::const_iterator it = obj.begin();it != obj.end();++it) {
	const picojson::value::object& obj_r = it->get < picojson::object >() ;
	const picojson::value dd=obj_r.at("l1_key");
	//if (dd == picojson::value(std::string("999"))){ throw std::runtime_error("success"); }
	}

	//daten aktuelle links


	*/


}
void MainApp::add_course_to_config_file(std::string & filename){
	
	Config_File_IO cfio(get_current_application_path() +"\\"+ filename);
	{auto check_existance = cfio.check_if_exists();
	if (!check_existance.result_operation){
		std::string str = "";
		check_existance.put_contents(str);
		check_existance.~Config_File_IO_Checker();
		

	}}
	auto check2 = cfio.check_if_exists();
	CHECK(check2.result_operation);
	check2.put_contents(std::string("?"/*warum das?->darf nicht in path-namen vorkommen*/)+current_course_download_location,true);
	
	



}
void MainApp::init_download_process_of_all_when_finished(CefRefPtr<CefBrowser>browser){
	//if (csss->downloader_browser_context == nullptr){
		//::MessageBox(NULL,TEXT("aa"),TEXT("dr.crash"),MB_OK);
	//}
	//CHECK(downloader_browser);
	browser->SendProcessMessage(PID_BROWSER,CefProcessMessage::Create("forward_signal_all_courses_finished"));

}

void MainApp::write_additional_course_data(bool append){
	picojson::array ayx_u;
	for (auto data : *submitted_additional_course_informations){
		picojson::array ayx;
		ayx.emplace_back(picojson::value(std::to_string(data.v0)));
		ayx.emplace_back(picojson::value(std::to_string(data.v1)));
		ayx.emplace_back(picojson::value(data.v2));
		ayx.emplace_back(picojson::value(data.v3));
		ayx.emplace_back(picojson::value(data.v4));
		ayx.emplace_back(picojson::value(data.v5));
		ayx_u.emplace_back(ayx);
	}
	//da irgendwo crash
	if (submitted_additional_course_informations->size() > 0){
		std::ofstream of;
		//picojson::array dcd;//@TODO:das hier nachher wieder hinmachen
		of.open(current_course_download_location + "\\course_additional_data.json", std::ios::out | std::ios::binary | append ? std::ios::app : 0);
		//dcd.emplace_back(*page_course_ptr);
		of <</*picojson::value(dcd) <<*/ picojson::value(ayx_u);
		of.close();
	}

}
string MainApp::get_url_filename_for_partial_downloads_list(){
	auto url1 = page_course_ptr->at(0);/*cefv8value kann nur von einem Thread aufgerufen werden?*/
	auto url = url1.ToString();
	url = str_replace("\\", "", url);
	url = str_replace("/", "", url);
	url = str_replace(":", "", url);
	url = url.substr(0, url.find("?"));
	url = str_replace("?", "", url);
	url = str_replace("#", "", url);//nicht sicher ob notwendig
	return url;
}
void MainApp::write_to_partial_downloads_list(string &url, unsigned int object_id){
	std::ofstream of;
	of.open(m_folder_where_to_put_downloads + "\\_____________directory_of_partial_downloads_list\\" + url + ".txt", std::ios::out | std::ios::binary);
	//file write schlägt fehl wg. nicht erlaubten Zeichen @TODO:Fix
	
	//::MessageBoxA(NULL,url.c_str(), "tschö", MB_OK);
	of << submit_course_urls_list->at(object_id).v1;
	of << ",";
	of << submit_course_urls_list->at(object_id).v2;
	of.close();

}
/*void MainApp::go_to_start_course_page(CefRefPtr<CefBrowser>browser)
{ 
	auto msg = CefProcessMessage::Create("browse_to_url"); msg->GetArgumentList()->SetString(0,starturl); browser->SendProcessMessage(PID_BROWSER, msg);
}*/
//TID_IO nur im browser prozess verfügbar,im renderer ist nur der TID_RENDERER und (vllt. noch irgendwelche anderere Threads verfügbar)
//TID_IO führt wohl zu endlos-schleife im renderer(also hier)
//void MainApp::delete_cookies(){

//	CefPostTask(TID_IO, base::Bind(&MainApp::task_delete_cookies,this,true));

//}
void browser_browse_to_course_url(CefString url, CefRefPtr<CefBrowser>browser){
	auto msg = CefProcessMessage::Create("browse_to_url");
	msg->GetArgumentList()->SetString(0, url);
	browser->SendProcessMessage(PID_BROWSER, msg);

}
void MainApp::ForceEnd(CefRefPtr<CefBrowser>browser,CefRefPtr<CefProcessMessage>message,bool finish_mode){

	//dabei Absturz-problem wohl beseitigt,dafür springt er aber nun bis an den schluss und meldet er sei fertig,so ein mist
	//bei jeder form von Ende:folgendes
	//oder kriegt er keine Daten mehr
	//unsigned int object_id = message->GetArgumentList()->GetInt(0);
	//nun abspeichern
	//das klappt wohl nicht immer,ein Klick auf das Laden ´scheint z uscheitern ohne dass manns mitbekommt,weil das Fenster net augheht,worauf dieser Code beasiert
	write_additional_course_data(true/*nur testweise jetzt*/);
	
	auto url = get_url_filename_for_partial_downloads_list();//access violation??
	if (!finish_mode){
		//::MessageBox(NULL, TEXT("!finish_mode"), TEXT("tschö"), MB_OK);
		//also von xxxx-geheimes-Wort!! geforced
		unsigned int object_id = message->GetArgumentList()->GetInt(0);
		write_to_partial_downloads_list(url,object_id);
		//::MessageBox(NULL, TEXT("das wars dann"), TEXT("tschö"), MB_OK);
		const TASKDIALOG_BUTTON buttons[] = {
			{ IDCANCEL, L"zu mache/Beenden" }, { 100, L"Weiter und ausloggen" }, { IDOK, L"weiter machen-mit-anderem-Kurs-ich kriege nie genug" }
		};
		auto res = xxxx-geheimes-Wort!!_cef_dl_basic_taskdialog(L"Tschö.Ende gefordert vom bösen javascript-Gott von xxxx-geheimes-Wort!!", L"Verzweifele nicht,es gibt Rettung.Egal,wie soll es weitergehn?", buttons, ARRAYSIZE(buttons), L"die 5 Minuten überschritten-aber es gibt noch einene Trost/Rettung.Einfach an dieser Stelle weiter machen.Ok?Klingt super?");
		switch (res)
		{
		case 100:browser->SendProcessMessage(PID_BROWSER, CefProcessMessage::Create("delete_cookies")); browser_browse_to_course_url(page_course_ptr->at(0),browser);// browser->SendProcessMessage(PID_BROWSER, CefProcessMessage::Create("logout"));//@TODO:gucken warum crash
		case IDOK:/*go_to_start_course_page(browser);*/ dialog_click_on_download_next_course(browser); 
			break;
		case IDCANCEL:
		case IDABORT://@TODO:oben implement
			::CefShutdown(); break;
		default:
			break; 
		}
		if (res == IDOK){

			browser_browse_to_course_url(starturl, browser);
		}
	}
	else{
		//::MessageBox(NULL, TEXT("finish_mode"), TEXT("tschö"), MB_OK);
		::DeleteFileA((m_folder_where_to_put_downloads + "\\_____________directory_of_partial_downloads_list\\" + url + ".txt").c_str());
		//kann ruhig failen
	}


}

bool MainApp::OnProcessMessageReceived(CefRefPtr< CefBrowser > browser, CefProcessId source_process, CefRefPtr< CefProcessMessage > message){
	bool  msg_not_handeled = false; 
	auto msgn = message->GetName();
	if (message->GetName() == CefString("link_received_proceed")&&!finish_mode){
		//CHECK(app_handler_request_context_handler_Ref);
		unsigned int object_id = message->GetArgumentList()->GetInt(1);

		

		if (count_value_intercept){
			for (size_t i = 0; i < submit_course_urls_list->size(); i++)
			{//http://stackoverflow.com/questions/409348/iteration-over-vector-in-c

				//::MessageBoxA(NULL, submit_course_urls_list->at(i)[1]->GetStringValue().ToString().c_str(), "fddf", MB_OK);
				//::MessageBoxA(NULL,submit_course_urls_list->at(i)[2]->GetStringValue().ToString().c_str(), "fddf", MB_OK);
				//::MessageBoxA(NULL, (std::to_string(count_new_value_assigned1)+std::to_string(count_new_value_assigned2)).c_str(), "fddf", MB_OK);
				if ((submit_course_urls_list->at(i).v1 == count_new_value_assigned1) && (submit_course_urls_list->at(i).v2 == count_new_value_assigned2)){
					object_id = i;
					//object_id++; 
					count_value_intercept = false;
					break;
				}

			}
		}
		//nun abspeichern
		if (message->GetArgumentList()->GetBool(2)){//check ob abgespeichert werden soll
			CefString val = message->GetArgumentList()->GetString(0);
			urls_list.push_back(message->GetArgumentList()->GetString(0));
			//urls_list.insert(urls_list.begin()/*0 müsste auch gehen*/ + object_id,val );
			int test=submit_course_urls_list->at(object_id).v1;
			::PostThreadMessage(t->thread_id, T_EVENT_THE_SIGNAL_TO_DOWNLOAD, object_id, urls_list.size()-1);
		}




		//std::wstring ws = L"Fertig mit" + std::to_wstring(object_id)+L" von Videos "+std::to_wstring(submit_course_urls_list->size());
		//counttext->Text_set(ws.c_str());

		object_id++; //independent_counter++;

		//submit_course_urls_list->size() == 0 && das er es abspeichern soll also getbool(2) nach aktuellen dingen wohl nicht möglich,da das nur auf diese /content/lecutes datei zutreffen würde,da die zuerst geladen wird.Voraussetzung:laden-reihenfolge verändert sich net

		if (message->GetArgumentList()->GetString(0) == "")/*dann nix gekriegtz*/{
			::MessageBox(NULL, TEXT("Kann aktuelles Element nicht kriegen"), TEXT("zu schnell;-)"), MB_OK);

		}
		
		if (submit_course_urls_list->size() >= (object_id + 1)){
			//problem:submit_course_urls_list = 0
			auto msg = CefProcessMessage::Create("cloxxxx-geheimes-Wort!!front_mp4_link_received_callback");
			msg->GetArgumentList()->SetInt(0, submit_course_urls_list->at(object_id).v1);
			msg->GetArgumentList()->SetInt(1, submit_course_urls_list->at(object_id).v2);

			msg->GetArgumentList()->SetInt(2, object_id);

			browser->SendProcessMessage(source_process, msg);

		}
		else if (submit_course_urls_list->size() == 0){
			//postpone,nach hintern verschieben
			msg_links_callback_queue.push_back(object_id);
			current_browser = browser;
		}
		else {
				write_additional_course_data();
				add_course_to_config_file(PATH_COMPLTEDED_COURSE_CONFIG_PATH);
				const TASKDIALOG_BUTTON buttons[] = {
					{ IDCANCEL, L"zu mache/Beenden" }, { 127, L"Runterladen" }, { IDOK, L"weiter mache-ich kriege nie genug" }
				};/*nachricht d.Programms:ich mache zu(bankrott) ,hier gibts nix mehr*/
				switch (xxxx-geheimes-Wort!!_cef_dl_basic_taskdialog(L"Fertig.Wie soll es weitergehen", L"Ich bin hilflos.Was soll ich als nächstes machen?", buttons, ARRAYSIZE(buttons), L"Wie solls weiter gehen?"))
				{

				case 127:  /*go_to_start_course_page(browser);*/init_download_process_of_all_when_finished(browser);
				case IDOK: browser->SendProcessMessage(PID_BROWSER, CefProcessMessage::Create("delete_cookies")); dialog_click_on_download_next_course(browser); browser_browse_to_course_url(starturl, browser); break;
				case IDCANCEL:
				case IDABORT://@TODO:oben implement
					CefShutdown(); break;
				default:
					break;
				}//Scheint wohl nicht immer auuszulösen,oder falsche Werte
				finish_mode = true;

			
		}
		//abgesehen davon gehts nicht,falls erstes kein Video ist
	}
	else if (message->GetName() == CefString("prepare_value_count_change")){
		count_value_intercept = true;
		//::MessageBox(NULL, TEXT("got-expected-message"), TEXT("yooooo, echt"), MB_OK);
		count_new_value_assigned1 = atoi(message->GetArgumentList()->GetString(0).ToString().c_str());
		count_new_value_assigned2 = atoi(message->GetArgumentList()->GetString(1).ToString().c_str());
	}
	else if (message->GetName() == "tell_course_folder_download_path"){
		//::MessageBox(NULL,"fdfds","fdssfd",MB_OK);
		//::MessageBox(NULL, "fdfds", "fdssfd", MB_OK);
		//::MessageBox(NULL, "fdfds", "fdssfd", MB_OK);
		int err = GetLastError();
		//auto msg = CefProcessMessage::Create("folder_where_to_put_downloads");
		//msg->GetArgumentList()->SetString(0, message->GetArgumentList()->GetString(0));
		//DCHECK(called);//hat nicht die Werte von vorhin,wohl anderer Prozess
		//CHECK(downloader_browser != nullptr);//geht net,browser wird komischerweise zwischenzeitlich Null
		//csss->downloader_browser_ref*//*downloader_browser->SendProcessMessage(PID_BROWSER, msg);//hier crash
		current_course_download_location = message->GetArgumentList()->GetString(0).ToString();
		
		//irgendwann danach crash,und zwar bevor er noch irgendeine url geschrieben hat,hat wohl mit vektor zu tun,out of range
		if (!(::CreateDirectoryA(current_course_download_location.c_str(), NULL) ||
			(GetLastError() == ERROR_ALREADY_EXISTS)))
		{
			::MessageBox(NULL, TEXT("komisch,folder zu erstellen ist schief gelaufen"), TEXT("Ihre Meinung dazu ,bitte"), MB_OK);
			::MessageBoxA(NULL, std::to_string(::GetLastError()).c_str(), "Ihre Meinung dazu ,bitte", MB_OK);
			
			::PostQuitMessage(0);
		}
		std::ofstream ofx;
		ofx.open(current_course_download_location + "\\video_urls.json", std::ios::out | std::ios::binary);//damit nicht das von vorher drin ist
		ofx.close();
		ofx.open(current_course_download_location + "\\course_additional_data.json", std::ios::out | std::ios::binary);
		ofx.close();

	}
	else if (message->GetName() == "query_2count_values"){
		auto object_id = message->GetArgumentList()->GetInt(0);
		//@TODO:queue,falls net verfügbar
		if (submit_course_urls_list->size() >=/*gucken ob frößer als oder größer gleich*/ (object_id + 1)){//voraausgesetzt,dass vorhanden
			
			auto msg = CefProcessMessage::Create("query_2count_values_callback");
			msg->GetArgumentList()->SetInt(0, submit_course_urls_list->at(object_id).v1);//@TODO!!:als erstes:hier gibts ne zugriffverletzung wohl out of range,weil diese werte wohl noch gar net in submit_course_urls_list sind
			msg->GetArgumentList()->SetInt(1, submit_course_urls_list->at(object_id).v2);
			browser->SendProcessMessage(source_process, msg);
			while(message_query_values_queue.size() >= 1){
				auto msg = CefProcessMessage::Create("query_2count_values_callback");
				msg->GetArgumentList()->SetInt(0, submit_course_urls_list->at(message_query_values_queue[0]).v1);//@TODO!!:als erstes:hier gibts ne zugriffverletzung wohl out of range,weil diese werte wohl noch gar net in submit_course_urls_list sind
				msg->GetArgumentList()->SetInt(1, submit_course_urls_list->at(message_query_values_queue[0]).v2);
				browser->SendProcessMessage(source_process, msg);//copy n paste
				message_query_values_queue.erase(message_query_values_queue.begin());
			}
		}
		else{
			
			message_query_values_queue.push_back(object_id);
		}
	}
	else{ msg_not_handeled = true; }

	if ((message->GetName() == CefString("end_forced_by_xxxx-geheimes-Wort!!")) /*|| (finish_mode == true)*/){
		msg_not_handeled = false;
		if (!finish_mode){
			ForceEnd(browser, message, finish_mode);
		}

	}
	else if (message->GetName() == "handshake_with_mainapp_getting_to-Know_each_other"){
		//browser->AddRef();//weiß net ,ob nötig
		
		//downloader_browser = new CefBrowser;//nachricht kommt wohl nicht an
		//downloader_browser = (CefBrowser*)malloc(sizeof(CefBrowser));
		//memcpy(downloader_browser,browser,sizeof(CefBrowser));
		msg_not_handeled = false;
		//downloader_browser = browser;
		//called = true;
		//bool is_renderer_king = TEST_i_AM_THE_RENDERER_KING;
		//browser->AddRef();
		//downloader_browser.swap(browser);
		//downloader_browser->AddRef();//scheißße,nutz nix
		//CHECK(downloader_client!=nullptr);
		//browser->SendProcessMessage(PID_RENDERER,CefProcessMessage::Create("ces"));
		//add_course_to_config_file();//nur Test
		//CHECK(downloader_browser!=nullptr);
	}
	//else if (message->GetName() == "on_after_created"){


	//	int dv = 55;
	//}
	
	return !msg_not_handeled;//eigentlich schlechter stil gleich true zurückzugeben
}
void MainApp::restore_defaults(){
	msg_links_callback_queue.clear();
	message_query_values_queue.clear();
	submit_course_urls_list->clear();
	submitted_additional_course_informations->clear();
	page_course_ptr->clear();
	course_name_ptr->clear();
	count_value_intercept = false;
	finish_mode = false;
	count_new_value_assigned1 = 0;/*ohne,*/ count_new_value_assigned2 = 0;
//	called = false;
}
void MainApp::dialog_click_on_download_next_course(CefRefPtr<CefBrowser>browser){//scheint net zu gehen
	restore_defaults();
	handler->restore_defaults();

	auto msg = CefProcessMessage::Create("restore_defaults");
	browser->SendProcessMessage(PID_BROWSER, msg);

}
//axxxx-geheimes-Wort!!io-typen gibts wohl bei xxxx-geheimes-Wort!! auch,da müsste sich er normal aufhängen,da diese ja auch ne Dauer haben,dass eine Cryptanalysis von dem Cryptanalysis-Typ ist so n Beispiel
//Konto vom 06.12.14 uns später: cs@cs.com,cs2@cs.com,cs3@cs.com,cs4@cs.com,cs5@cs.com,...cs7@cs.com
//csx@cs.com,csx2@cs.com,v8@v12.com,v10@v12.com,v12qv12.com,norbert@gmail.com,v8@v8.com,fullname@engineer.com,cs30@cs30.com,cs30@cs.com,rob_ber@grandtheft.com,rob@robber.com,v8@v16.com,v22@v22.com
//, bulkpurchase@mycharacter.com, gillette@frau-vongilbert.com,fdsfd@ripe.com,adsd@sdccsa.com,fullername@real.com,iiiiiii@dsads.com,golfgti@golfjit.com,nullbert@nullo.com,robby@robber.com,Bethename@nic.saarland,gcsu@gcsu1.com
//step_yo@game.up,goalgetter@gg.gg,ninch@nails.com,g-euul@g-eeul.com, whazz@up.com, fasfd@casc.com,dsads@cdca.com,dsdas@cacs.com,dsasd@cascc.com,loadingstatenge@newyorkcity.uasssssa,berthold@derbaecker.de,
//rambo@sylvester.com,best@price.com,come@leave.com,cheat@ing.com,law_and@order.com,google@facebook.com,maxi@burgerking.com,behindert@lidl.com,free@preview.com,wddev@alsweiter.de,nichtskoennen@gutso.de,surroundend@byzombies.com
//dsd@cac.com,adsasd@csacas.com,lancerevoxii@mitsubushi.com,goodidea@nononono.com,tellmewhat@yousee.com,fddsf@dcc.com,lancerevoxiii@mitsubushi.com,enroll@me.now,was@wollensie.lernen,lancerevoviii@mitsubishi.com,com.commer@telecom.com
//inet.destory@cpp.class,lancerevovii@mitsubushi.com,check_for_it@go.com,proceed@bier.com,dsasd@sacsc.com
//Beim dem UX-Video bleibt er ziemlich vorne hängen