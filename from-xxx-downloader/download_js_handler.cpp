#inclxxxx-geheimes-Wort!!e "download_js_handler.h"
#inclxxxx-geheimes-Wort!!e <Windows.h>
void do_execute_callback_function_dl_manager(const CefV8ValueList& arguments){
	CefV8ValueList argumentss;
	arguments.at(1)->ExecuteFunction(arguments.at(2), argumentss);

}
bool Download_JS_Handler::Execute(const CefString& name,
	CefRefPtr<CefV8Value> object,
	const CefV8ValueList& arguments,
	CefRefPtr<CefV8Value>& retval,
	CefString& exception){

	if (name == "start"){
		
		auto msg=CefProcessMessage::Create("start_download");
		msg->GetArgumentList()->SetString(0, arguments.at(3)->GetStringValue());
		msg->GetArgumentList()->SetInt(1, arguments.at(0)->GetIntValue());
		msg->GetArgumentList()->SetInt(2, arguments.at(4)->GetIntValue());
		msg->GetArgumentList()->SetInt(3, arguments.at(5)->GetIntValue());
		msg->GetArgumentList()->SetInt(4, arguments[6]->GetIntValue());

		//CefV8Context::GetCurrentContext()->GetBrowser()->GetHost()->StartDownload("http://google.com");//nur im browser process
		//arguments.at(1)->GetFunctionHandler()->Execute("drawPauseButton",arguments.at(2),arguments,CefV8Value::CreateNull(),CefString("nein"));
		//::MessageBox(NULL, std::to_string(arguments.at(0)->GetIntValue()).c_str(),"okok",MB_OK);//problem bei derm ganzen getstringvalue usw.gibt im Fehlerfall nix zurück,also getstringvalue gibt nix zurück,ist aber eigentlich int
		CefV8Context::GetCurrentContext()->GetBrowser()->SendProcessMessage(PID_BROWSER,msg);
		do_execute_callback_function_dl_manager(arguments);//zwar net gut,dass er vor dem dlder button geändert wird(was passiert bei click vor download-start auf den button) wird,spart aber code(aktuell von jetzt ausgehend;-))
		//@TODO(geringe Priorität):callback-function speichern und aufrufen wenn download begonnen
		return true;
	}
	else if (name == "pause"){
		auto msg = CefProcessMessage::Create("pause_download");
		msg->GetArgumentList()->SetInt(0, arguments.at(0)->GetIntValue());
		CefV8Context::GetCurrentContext()->GetBrowser()->SendProcessMessage(PID_BROWSER, msg);
		do_execute_callback_function_dl_manager(arguments);
		return true;
	}
	else if (name == "resume"){
		auto msg = CefProcessMessage::Create("resume_download");
		msg->GetArgumentList()->SetInt(0, arguments.at(0)->GetIntValue());
		CefV8Context::GetCurrentContext()->GetBrowser()->SendProcessMessage(PID_BROWSER, msg);
		do_execute_callback_function_dl_manager(arguments);
		return true;
	}
	else if (name == "init_JS_Handler"){
		//downloader_browser_ref->AddRef();
		CefV8Context::GetCurrentContext()->GetBrowser()->SendProcessMessage(PID_BROWSER,CefProcessMessage::Create("js_code_initialized"));

		return true;
	}
	else if (name == "download_of_group_finished"){
		auto msg=CefProcessMessage::Create("download_of_group_finished");
		msg->GetArgumentList()->SetInt(0, arguments[0]->GetIntValue());
		CefV8Context::GetCurrentContext()->GetBrowser()->SendProcessMessage(PID_BROWSER,msg );
		return true;
	}
	

return false;
}