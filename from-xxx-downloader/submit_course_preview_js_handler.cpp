#inclxxxx-geheimes-Wort!!e "submit_course_preview_js_handler.h"
#inclxxxx-geheimes-Wort!!e "string_helper.h"
#inclxxxx-geheimes-Wort!!e <fstream>
#inclxxxx-geheimes-Wort!!e <sstream>

bool Submit_Course_preview_js_handler::Execute(const CefString& name,
	CefRefPtr<CefV8Value> object,
	const CefV8ValueList& arguments,
	CefRefPtr<CefV8Value>& retval,
	CefString& exception){
	
	if (name == "submit_course_preview_urls_begin") {
		submit_course_urls_list->clear();
		submitted_additional_course_informations->clear();
		return true;
	}
	else if (name == "submit_course_preview_urls_end"){
		//retval.get()->Create
		//CefRefPtr<CefV8Value> arr = CefV8Value::CreateArray(submit_course_urls_list->size());
		//unsigned int vector_id_counter = 0;
		//for (auto& vec_data : submit_course_urls_list){
		//for (std::vector<course_url_list_values>::iterator it = submit_course_urls_list->begin(); it != submit_course_urls_list->end(); ++it) {
			//arr->SetValue(vector_id_counter++,it->v1);
			
		//}
			m_mainapp->signal_submit_course_urls_list_data_received();
		//retval.swap(arr);
		return true;
	}
	else if (name == "submit_course_preview_urls_data"){
		
		CefRefPtr<CefV8Value> dd = arguments.at(0);//immer genau das gleiche schreiben,am besten wäre hier so ne lambda funktionen oder vllt. gibts auch sowas bei linq undz zwar hier nr zahlen 0-2
		//CefString str = dd.get()->GetStringValue();
		//array<CefRefPtr<CefV8Value>, 3> dc = { dd, arguments.at(1), arguments.at(2) };
		course_url_list_values dc = { arguments.at(1)->GetIntValue(), arguments.at(2)->GetIntValue(), arguments.at(0)->GetStringValue() };
		submit_course_urls_list->push_back(dc);
		//::MessageBoxW(NULL, str.ToWString().c_str(),TEXT("string-arg-url"), MB_OK);
		return true;
	}
	else if (name == "submit_course_url"){
		//CefRefPtr<CefV8Value>v = arguments.at(0);
		//CefString str = v->GetStringValue();
		//std::string qq = str.ToString();
		//course_link_uid = new std::string;
		course_link_uid->push_back(arguments.at(0)->GetStringValue());

		return true;
	}
	else if (name == "submit_additional_course_information"){
		//array<CefRefPtr<CefV8Value>, 6> dc;
		/*for (int i = 0; i < 6; i++){
			dc[i] = arguments.at(i);
		}
		*/
		additional_data_values dc = { arguments.at(0)->GetIntValue(), arguments.at(1)->GetIntValue(),
			arguments.at(2)->GetStringValue(), arguments.at(3)->GetStringValue(), arguments.at(4)->GetStringValue(), arguments.at(5)->GetStringValue() };//n makro wär hier net schlecht
		/*if (!already_downloaded &&(arguments.at(3)->GetStringValue().ToString().find("Text")!=std::string::npos)){
			CefRefPtr<CefBrowser> browser =
				CefV8Context::GetCurrentContext()->GetBrowser();
			CefRefPtr<CefProcessMessage>msg = CefProcessMessage::Create("create_urlrequest_for_dl");
			msg->GetArgumentList()->SetString(0, arguments.at(6)->GetStringValue());
			msg->GetArgumentList()->SetString(1, arguments.at(0)->GetStringValue());
			msg->GetArgumentList()->SetString(2, arguments.at(1)->GetStringValue());
			browser->SendProcessMessage(PID_BROWSER, msg);
			::MessageBox(NULL, TEXT("found"), TEXT("yooooo, echt"), MB_OK);
		}*/

		submitted_additional_course_informations->push_back(dc);
		return true;
	}
	else if (name == "get_start_required_ids"){
		//CefRefPtr<CefV8Value> arr = CefV8Value::CreateArray(2);
		CefRefPtr<CefV8Value> arr;
		auto dc = arguments.at(0);
		std::string val = dc->GetStringValue().ToString();
		std::string url = str_replace("\\", "", val);
		url = str_replace("/", "", url);
		url = str_replace(":", "", url);//hier 2mal und dasselbe noch einmal + mehr für Titel in ORdner Dingens
		url = url.substr(0, url.find("?"));
		url = str_replace("?", "", url);
				url = str_replace("#", "", url);//@TODO:das hier scheint nicht zu gehen,vllt. weil die urls variiierens
		std::ifstream in(download_path+"\\_____________directory_of_partial_downloads_list\\" + url + ".txt", std::ios::in | std::ios::binary);
		
		if (in){
			already_downloaded = true;
			std::stringstream ss;
			ss << in.rdbuf();
			in.close();
			std::string data=ss.str();
			auto pos_comma=data.find(",");
			std::string s1 = data.substr(0,pos_comma);
			std::string s2 = data.substr(pos_comma+1, data.size() - 1);
			arr = CefV8Value::CreateArray(2);
			CefString st; st.FromString(s1);
			arr->SetValue(0, CefV8Value::CreateString(st));
			CefString st1; st1.FromString(s2);//auf Stack,dürfte daher nicht verändert werden,holt sich aber referencen hmmm..
			arr->SetValue(1, CefV8Value::CreateString(st1));
	
			CefRefPtr<CefBrowser> browser =
				CefV8Context::GetCurrentContext()->GetBrowser();
			
			//CefRefPtr<CefProcessMessage>msg = CefProcessMessage::Create("demand_send_start_count_value_changed");
			
			
			//CefRefPtr<CefProcessMessage>msg = CefProcessMessage::Create("set_start_count_value");
			/*for (size_t i = 0; i < submit_course_urls_list->size(); i++)
			{//http://stackoverflow.com/questions/409348/iteration-over-vector-in-c
				if ((submit_course_urls_list->at(i)[1]->GetStringValue() == message->GetArgumentList()->GetString(0)) && (submit_course_urls_list->at(i)[2]->GetStringValue() == message->GetArgumentList()->GetString(1))){
					msg->GetArgumentList()->SetInt(0, i);
					browser->SendProcessMessage(PID_BROWSER, msg);
					break;
				}

			}*/

			CefRefPtr<CefProcessMessage>msg = CefProcessMessage::Create("demand_send_start_count_value_changed");
			msg->GetArgumentList()->SetString(0,st);
			msg->GetArgumentList()->SetString(1, st1);
			browser->SendProcessMessage(PID_BROWSER,msg);//hier fail kann wohl browser nicht bekommen//muss PID_BROWSER sein,ansonsten crash
			//::MessageBox(NULL, TEXT("after sending message"), TEXT("yooooo, echt"), MB_OK);
		}
		else{
			arr = CefV8Value::CreateBool(false);//nur zur sicherheit
			already_downloaded = false;
			
		}


		retval.swap(arr);
	
		return true;
	}
	else if (name == "submit_course_name"){
		CefRefPtr<CefProcessMessage>msg = CefProcessMessage::Create("broadcast_course_name");
		msg->GetArgumentList()->SetString(0, arguments.at(0)->GetStringValue());
		
		m_course_name->push_back(arguments.at(0));
		CefV8Context::GetCurrentContext()->GetBrowser()->SendProcessMessage(PID_BROWSER, msg);

	}
	else if (name == "unlock_content_data_event"){
		CefRefPtr<CefProcessMessage>msg = CefProcessMessage::Create("unlock_content_data_event_received");
		//msg->GetArgumentList()->SetBool(0,true);

		CefV8Context::GetCurrentContext()->GetBrowser()->SendProcessMessage(PID_BROWSER, msg);
	}
	else if (name == "cpp_notify_end_popup_created"){
		//CefV8Context::GetCurrentContext()->GetBrowser()->SendProcessMessage(PID_BROWSER, CefProcessMessage::Create("delegate_forced_end"));
		//@TODO:nur dann aufrufen wenn wirklich
	}
	

	return false;//muss so net richtig sein,ist aber denk ich besser so hier kombination true/false bei return
}











