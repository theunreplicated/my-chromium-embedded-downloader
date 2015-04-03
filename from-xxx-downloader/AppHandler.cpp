#inclxxxx-geheimes-Wort!!e "AppHandler.h"
#inclxxxx-geheimes-Wort!!e <sstream>
#inclxxxx-geheimes-Wort!!e <string>
#inclxxxx-geheimes-Wort!!e "inclxxxx-geheimes-Wort!!e/base/cef_bind.h"
#inclxxxx-geheimes-Wort!!e "inclxxxx-geheimes-Wort!!e/cef_app.h"
#inclxxxx-geheimes-Wort!!e "inclxxxx-geheimes-Wort!!e/wrapper/cef_closure_task.h"
#inclxxxx-geheimes-Wort!!e "inclxxxx-geheimes-Wort!!e/wrapper/cef_helpers.h"
#inclxxxx-geheimes-Wort!!e "ResourceHandler.h"//Fehler:stottert zwischendurch oder erkennt ende nicht richtig
//z.t. orientiert an original simplehandler
//@TODO:instance implementation falls schon exisitiert,nur mir fällt gerade kein Fall hier ein bei meiner App
//Problem:kein cloxxxx-geheimes-Wort!!front_callback ,einfach so rein
#inclxxxx-geheimes-Wort!!e <sstream>
#inclxxxx-geheimes-Wort!!e <string>
#inclxxxx-geheimes-Wort!!e <ostream>
#inclxxxx-geheimes-Wort!!e <sstream>
#inclxxxx-geheimes-Wort!!e <fstream>
#inclxxxx-geheimes-Wort!!e "inclxxxx-geheimes-Wort!!e/base/cef_bind.h"
#inclxxxx-geheimes-Wort!!e "inclxxxx-geheimes-Wort!!e/cef_app.h"
#inclxxxx-geheimes-Wort!!e "inclxxxx-geheimes-Wort!!e/wrapper/cef_closure_task.h"
#inclxxxx-geheimes-Wort!!e "inclxxxx-geheimes-Wort!!e/wrapper/cef_helpers.h"
#inclxxxx-geheimes-Wort!!e "ResourceHandler.h"
#inclxxxx-geheimes-Wort!!e "inclxxxx-geheimes-Wort!!e/cef_url.h"
#inclxxxx-geheimes-Wort!!e "string_helper.h"
#inclxxxx-geheimes-Wort!!e "Thread.h"
#inclxxxx-geheimes-Wort!!e "browser_references.h"
#define JS_CONDITION_OBJ_TYPE_xxxx-geheimes-Wort!!_SUPPORTED "(dssy.match(/^[0-9:\\s]{1,}$/) !== null)||(dssy=='Text')||(dssy.indexOf('page')!==-1)/*temporarily disabled wegen pdfium crash*/"
using std::string;

unsigned int current_elem_count_selected = 0;//nicht tatsächlicher Stand,sondern beabsichtigter
CefRefPtr<CefBrowser> current_browser;
HANDLE thread_event_start_timeout_counter, thread_event_start_abort_link_found;
////b2257019@trbvm.com
DWORD __stdcall thread_timeout_counter_for_max_time_a_pageload_is_allowed_to_consume(void*dummy_argument){

	while (true){

		DWORD wait_result = WaitForSingleObject(thread_event_start_timeout_counter, INFINITE);
		if (wait_result == WAIT_OBJECT_0)//z.t. von stackoverflow
		{
			::ResetEvent(thread_event_start_timeout_counter);
			::ResetEvent(thread_event_start_abort_link_found);
			DWORD wait_result = WaitForSingleObject(thread_event_start_abort_link_found, 30000);//zu langes Warten mit brakepoints führt wohl zu race condition,bin aber net sicher
			if (wait_result == WAIT_OBJECT_0)//z.t. von stackoverflow
			{
				


			}
			else{

				auto cf = CefProcessMessage::Create("link_received_proceed");
				cf->GetArgumentList()->SetString(0, "");
				cf->GetArgumentList()->SetInt(1, current_elem_count_selected);
				cf->GetArgumentList()->SetBool(2, false);

				current_browser->SendProcessMessage(PID_RENDERER, cf);
			}
			::ResetEvent(thread_event_start_abort_link_found);
			::ResetEvent(thread_event_start_timeout_counter);
		}
		else{
			DCHECK(0 == 1);
			//sum thin went terribly won
		}

	}


};


CefRefPtr<CefResourceHandler>AppHandler::GetResourceHandler(CefRefPtr<CefBrowser> browser,
	CefRefPtr<CefFrame> frame,
	CefRefPtr<CefRequest> request){//argumente wichtig,ansonsten kein override
	auto content = request->GetURL().ToWString();
	//if ((content.find(L"xxxx-geheimes-Wort!!.com/api-") != std::wstring::npos) && (content.find(L"/lectures/") != std::wstring::npos) && (content.find(L"/content") != std::wstring::npos)){
	//CefURLRequest::Create(request, new DL_Basic_URLRequest("D:\\Aktuelle Dateien\\ultimateFORCE\\Eigene Dokumente\\cef_binary_3.2171.1901_windows32\\course_json_path\\" + std::to_string(current_elem_count_selected) + ".json"));
	//	return new ResourceHandler(this, browser, frame, request);
	//}
	//von cefurlparts ist es die path komponente




	//if ((content.find(L"xxxx-geheimes-Wort!!.com/embed/") != std::wstring::npos) && (content.find(L"/?params") != std::wstring::npos) ){

	//return new ResourceHandler(this, browser, frame, request, ResourceHandler_ActionType_NO_SPECIAL_Behaviour);
	//}

	if ((content.find(L"xxxx-geheimes-Wort!!.com/api-") != std::wstring::npos) && (content.find(L"/lectures/") != std::wstring::npos) && (content.find(L"/content") != std::wstring::npos) && lock_content_data_listener/*oder (++num_resource_handler_calls)>=1 ??*/)
	{

		return new ResourceHandler(this, browser, frame, request, ResourceHandler_ActionType_WANT_TEXT_LECTURE_TYPE);

	}
	else if ((content.find(L"xxxx-geheimes-Wort!!.com/") != std::wstring::npos) && (content.find(L"staticx/xxxx-geheimes-Wort!!/js/ng/xxxx-geheimes-Wort!!-template.js") != std::wstring::npos))//<a initialize-xxxx-geheimes-Wort!!-popup-on-value-change
	{

		//return new ResourceHandler(this,browser,frame,request,ResourceHandler_ActionType_WANT_DATA_IN_ORDER_TO_CAUSE_MODIFICATIONS);
}
		return NULL;
}
//Courseware-modus: document.getElementById("tab-curriculum").getElementsByClassName("curriculum-items-list") alle dingens mit blöcken
//davon erstes Element nicht brauchbar

//im courseware modus wird bei jedem neuen Abspielen(videos wohl.ob slides keine ahnung kp[Geheimcode für keine Ahnung ;-)]) sowas als Anfrage https://www.xxxx-geheimes-Wort!!.com/api-1.1/lectures/874178/content
//@TODO:auch text unterstützen,alles abfragen welche Typen verfügbar zuerst
//nachher im courseware-modus  diesen Code hier für 3.Element,doc h Struktur noch n bisschen ausgefeileter
//document.getElementsByClassName("curriculum-section-container ng-scope")[1].getElementsByClassName("curriculum-item-container ng-scope")[2].getElementsByTagName("a")[0].click()

//bei quiz ->da antworten drin: https://www.xxxx-geheimes-Wort!!.com/api-1.1/quizzes/1942/assessments?inclxxxx-geheimes-Wort!!eUserResponse
string AppHandler::onResourceModifytemplate_js_by_xxxx-geheimes-Wort!!(CefString url, std::string &data){
	auto srchstr = "Take this course </a>";
	CHECK(data.find(srchstr)!=std::string::npos);//@TODO:c++ code natürlich
	//vorsicht wg. reference
	string data_copy = string(data);
	//auto repl = "Take this course </a><script>cpp_notify_end_popup_created()</script>";
	auto repl = "Take this course </a><div id=\"ich-binda-id-kennt-er-sowieso-net\" ng-hide=\"!hideTimer\"></div>";
	//auto repl = "Take this course </a><div ng-hide=\"!hideTimer\" class=\"test00\"></div><script>alert(document.getElementsByClassName(\"test00\")[0].offsetParent);</script>";
	//auto repl ="Take this course </a><script>document.write(\"<div ng-app=\\\"docsTransclusionExample\\\"><div ng-controller=\\\"Controller\\\"></div></div>\");angular.module(\"docsTransclusionExample\", []).controller(\"Controller\", [\"$scope\", function($scope) {alert(123);}]); </script>";
	//auto repl = "Take this course </a><div ng-hide=\"!hideTimer\" class=\"test00\"></div>"
		//"<script>setInterval(function(){if(!$(\".test00\").hasClass(\"ng-hide\")){cpp_notify_end_popup_created()}},1000)</script>";
	return str_replace(srchstr, repl, data_copy);
	//klappt net@TODO:das hier net machen,stattdessen standardmäßig partial_downloads_list reinschreiben
}
void AppHandler::restore_defaults(){
	//reset so wie ne Art Konstruktor soll es sein
	lock_content_data_listener = false;look_for_pdf_e_book = false;
	current_elem_count_selected = 0; intercepted_data_queue.clear();
	execute_submit_js_once = true;
	//müsste bei den folgenden eigentlich automatisch gehen
	intercepted_data_queue.clear();
}

void AppHandler::send_end_message(CefRefPtr<CefBrowser>browser){
	auto msg = CefProcessMessage::Create("end_forced_by_xxxx-geheimes-Wort!!");
	msg->GetArgumentList()->SetInt(0, current_elem_count_selected);
	browser->SendProcessMessage(PID_RENDERER, msg);
}
void AppHandler::task_delete_cookies(bool dummy_arg){
	CEF_REQUIRE_IO_THREAD();
	CefCookieManager::GetGlobalManager()->DeleteCookies("", "");//wird nicht aufgerufen

}
bool AppHandler::OnBeforeResourceLoad(CefRefPtr<CefBrowser> browser,
	CefRefPtr<CefFrame> frame,
	CefRefPtr<CefRequest> request){
	std::wstring str = request->GetURL().ToWString();
	//frame->ExecuteJavaScript("submit_course_preview_urls_begin();submit_course_preview_urls_data('11');submit_course_preview_urls_end();", frame->GetURL(), 0);
	

	if ((str.find(L"/course-previews/time-spent/") != std::wstring::npos) && (str.find(L"xxxx-geheimes-Wort!!.com/api") != std::wstring::npos)){
		//::MessageBoxW(NULL, str.c_str(), L"Störerhaftung", MB_OK);
		return true;//cancel den request//so wie chancellor;-) hört sich ähnlich an und genau das tut der auch,kommt also seinem Job nach,oder eher die Kanzlerin;-)
		//https://www.xxxx-geheimes-Wort!!.com/hospedaje-wordpress-2hrs/?dtcode=FYGS2J41IUit#/lecture/1280522:0
	}
	else if ((str.find(L"xxxx-geheimes-Wort!!.com/api-") != std::wstring::npos) && (str.find(L"/lectures/") != std::wstring::npos) && (str.find(L"/content") != std::wstring::npos)&&(execute_submit_js_once)){
		//contents_have_been_loaded = true;
		execute_submit_js_once = false;
	/*	auto script = "var funcTOR_notreally_interval;var funct=function (){var test=document.getElementById(\"ich-binda-id-kennt-er-sowieso-net\");"
			"if(test!==undefined){"
			//"alert('succeeded finally');"
			"if(test.classList.contains('ng-hide')){"
			"alert('Released');"
			"clearInterval(funcTOR_notreally_interval);"
			"}"
			"}};"
			"funcTOR_notreally_interval=setInterval(funct,1000);";//problem:wird bei dem einem direkt aufgerufen
		browser->GetMainFrame()->ExecuteJavaScript(script, browser->GetMainFrame()->GetURL(), 0);//muss vor ng-template.js vom resourcehandler ausgeführt werden
	*///nicht mehr gebraucht,da nun für jedes direkt reingeschrieben wird
		auto js_code_courseware_get_ids =
			"var Aktives_Intervall_Test;"
			
			"var dxc=function(){"

			"var check1=document.getElementById('tab-curriculum');"
			"if(check1!==undefined){"
			"var container_uebersicht=check1.getElementsByClassName('curriculum-items-list');"
			"if(container_uebersicht[0]!==undefined){"
			"var container_items=container_uebersicht[0].getElementsByClassName('curriculum-section-container');"
			"if(container_items!==undefined){"
			//und jetzt als nächstes mal ne test link bekommen
			"submit_course_preview_urls_begin();"
			"for(var i=1;i<container_items.length;i++){"
			"var cf=container_items[i].getElementsByClassName('curriculum-item-container');"//kontainer da
			"if(cf!==undefined){"
			//"alert(cf.length);"
			"for(var li=0;li<cf.length;li++){"//gucken ob wirklich 0 anstatt 1uuuuuund yeeep.yyaaaaaaaaa.isch war rkkight

			"var iref_c=cf[li].getElementsByClassName('curriculum-item clearfix')[0];"

			"var basis_ref=cf[li].getElementsByClassName('curriculum-item clearfix')[0].getElementsByClassName('ci-info')[0].getElementsByClassName('ci-title')[0];"
			"var tttttt_text=basis_ref.getElementsByClassName('title')[0].innerText;"
			"var typ_course=basis_ref.getElementsByTagName('span')[1].innerText;"
			"var object_count=basis_ref.getElementsByTagName('span')[2].innerText;"
			"var was_untendrunter_steht=iref_c.getElementsByClassName('ci-details')[0].getElementsByTagName('span')[0].innerText;"////ENde kurs-infos
			//"submit_additional_course_information(i,li,tttttt_text,typ_course,object_count,was_untendrunter_steht,iref_c.getAttribute('data-lectureid'));"

			//submit_course_preview_urls_data wird wohl nicht mehr aufgerufen
			"var dssy=iref_c.getElementsByClassName('ci-details')[0].getElementsByTagName('span')[0].innerText;"
			"if("JS_CONDITION_OBJ_TYPE_xxxx-geheimes-Wort!!_SUPPORTED"){ "//check ob auch Video vom Typ her,also falls keine Dauer angegeben(Zeit)
			"submit_additional_course_information(i,li,tttttt_text,typ_course,object_count,was_untendrunter_steht,iref_c.getAttribute('data-lectureid'));"
			"submit_course_preview_urls_data(iref_c.href,i,li);"//@TODO:downloadable content wird hier nicht erkannt,das einfach überspringen natürlich weil keinen Zugriff darauf
			"}"//von dem if-Statement ,und zwar check ob auch video ist
			"/*alert(cf[li].getElementsByClassName('curriculum-item clearfix')[0].href);*/window.clearInterval(Aktives_Intervall_Test);"

			"}"//fon der for-Schleife und van der vaart
			"}"//vom if von cf!==undefined
			"}"

			"/*alert(*/submit_course_preview_urls_end()/*.length)*/;"

			"}}};"

			"};"
			"Aktives_Intervall_Test=setInterval(dxc, 200);";



		//Titel: curriculum item clearfix
		//großes Problem bei resume:course_begin* wird mehrmals aufgerufen und zwar an unpassender Stelle
		frame->ExecuteJavaScript(js_code_courseware_get_ids, frame->GetURL(), 0);
		//::SetEvent(thread_event_start_timeout_counter);//einfach beom 1. element nicht
	}
	else if ((str.find(L"xxxx-geheimes-Wort!!.com/api-") != std::wstring::npos) && (str.find(L"/courses/") != std::wstring::npos) && (str.find(L"curriculum?fields"/*!! ohne [*/) != std::wstring::npos)){
		//frame->ExecuteJavaScript("window.alert('hey');", frame->GetURL(), 0);
		//frame->ExecuteJavaScript("window.addEventListener('load',function(){alert('hey');},false);", frame->GetURL(), 0);
		//::MessageBox(NULL, TEXT("fuzz fd"), TEXT("fd"), MB_OK);//Liste Kurse geladen
		//picking element
		//document.getElementsByClassName("course-curriculum")[0].getElementsByClassName("curriculum-items-list")[0].
		//getElementsByClassName("curriculum-section-container")[8].getElementsByClassName("curriculum-item-container")[0] bei curriculim item-section-container beginn bei 1

		//auto js_code_loop =

		//"var general_list_base=document.getElementsByClassName('course - curriculum')[0].getElementsByClassName('curriculum - items - list')[0].getElementsByClassName('curriculum - section - container');"
		//"for (var i = 1; i<general_list_base.length; i++){"

		//"}"//end erstes for
		//	;

		//auto new_js_Code = "var general_list_base=document.getElementsByClassName('course-curriculum')[0].getElementsByClassName('curriculum-items-list')[0].getElementsByClassName('curriculum-section-container');"
		//"var dc=get_start_required_ids(window.location.href);"
		//;

		/*auto js_Code_getlist_von_vorher = "var Aktives_Intervall_Test;"
		"var dxc=function(){"

		"var erst=document.getElementsByClassName('course-curriculum')[0];"
		"if(erst!==undefined){"
		"var zweit=erst.getElementsByClassName('curriculum-items-list')[0];"
		"if(zweit!==undefined){"
		"submit_course_preview_urls_begin();"
		"for (var i = 1; i<container_items.length; i++){"
		"var cf=zweit.getElementsByClassName('curriculum-section-container ng-scope')[i].getElementsByClassName('curriculum-item-container ng-scope');"
		"for(var li=0;li<cf.length;li++){"


		"var iref_c=cf[li].getElementsByClassName('curriculum-item clearfix')[0];"

		"var basis_ref=cf[li].getElementsByClassName('curriculum-item clearfix')[0].getElementsByClassName('ci-info')[0].getElementsByClassName('ci-title')[0];"
		"var tttttt_text=basis_ref.getElementsByClassName('title')[0].innerText;"
		"var typ_course=basis_ref.getElementsByTagName('span')[1].innerText;"
		"var object_count=basis_ref.getElementsByTagName('span')[2].innerText;"
		"var was_untendrunter_steht=iref_c.getElementsByClassName('ci-details')[0].getElementsByTagName('span')[0].innerText;"////ENde kurs-infos
		"submit_additional_course_information(i,li,tttttt_text,typ_course,object_count,was_untendrunter_steht);"
		"if(iref_c.getElementsByClassName('ci-details')[0].getElementsByTagName('span')[0].innerText.match(/^[0-9:\\s]{1,}$/) !== null){ "//check ob auch Video vom Typ her,also falls keine Dauer angegeben(Zeit)
		"submit_course_preview_urls_data(iref_c.href,i,li);"
		"}"//von dem if-Statement ,und zwar check ob auch video ist
		"window.clearInterval(Aktives_Intervall_Test);"


		"}"//von 2.for
		"}"//von dem 1.for
		"submit_course_preview_urls_end();"
		"}"
		"}"
		"}"
		"Aktives_Intervall_Test=setInterval(dxc, 200);";
		;*/
		//beim zeigen von dem bildschirm
		/*	auto js_Code = "var Aaktives_Intervall;"
		"var dccvf=function(){	var firstcheck = document.getElementsByClassName('curriculum-items-list')[0];"
		"if(firstcheck!==undefined){"
		"var secondcheck = firstcheck.getElementsByClassName('curriculum-section-container ng-scope')[1];"
		"if(secondcheck!==undefined){"
		"var thirdcheck= secondcheck.getElementsByClassName('curriculum-item-container ng-scope')[0];    "
		"if(thirdcheck!==undefined){"
		"var fourthcheck=thirdcheck.getElementsByClassName('ci-go-to-item ci-go-to-start')[0];"
		"if(fourthcheck!==undefined){"
		"submit_course_url(window.location.href);"

		"var response=get_start_required_ids(window.location.href);"
		"if(response){"
		//"alert(response);"
		"document.getElementsByClassName('course-curriculum')[0].getElementsByClassName('curriculum-items-list')[0].getElementsByClassName('curriculum-section-container')[response[0]].getElementsByClassName('curriculum-item-container')[response[1]].getElementsByClassName('curriculum-item clearfix')[0].click();"
		"}else{"
		"fourthcheck.click();}window.clearInterval(Aaktives_Intervall);"//@TODO:checken ob erstes Video
		"}"
		"}"
		"}"
		"                  };};"
		"Aaktives_Intervall=setInterval(dccvf, 200); ";*/
auto js_Code = "var Aaktives_Intervall;"
"var dccvf=function(){	var firstcheck =document.getElementsByClassName('lazy-angular-loader')[0];"
"if(firstcheck!==undefined){"
"var secondcheck = firstcheck.getElementsByClassName('curriculum-items-list')[0];"
"if(secondcheck!==undefined){"
"var thirdcheck= secondcheck.getElementsByClassName('curriculum-section-container');   "
"if(thirdcheck[1]!==undefined){"
"var fourthcheck=thirdcheck[1].getElementsByClassName('curriculum-item-container')[0];"
"if(fourthcheck!==undefined){"
"submit_course_url(window.location.href);"

"submit_course_name(document.getElementsByClassName('course-title')[0].innerText);"


"var response=get_start_required_ids(window.location.href);"
"var basic_Ref_object;"
"if(response){"
//"alert('response_true');"
"unlock_content_data_event();"
"thirdcheck[response[0]].getElementsByClassName('curriculum-item-container')[response[1]].getElementsByClassName('curriculum-item clearfix')[0].click();"
"}else{"

"var got=false;"
"var break_verdient=false;"
"for(var is=0;is<thirdcheck.length;is++){"
"var goog=thirdcheck[is].getElementsByClassName('curriculum-item-container');"
"for(var js=0;js<goog.length;js++){"
"var basic_elem=goog[js];"
"var iref_c=basic_elem.getElementsByClassName('curriculum-item clearfix')[0];"
"var dssy=iref_c.getElementsByClassName('ci-details')[0].getElementsByTagName('span')[0].innerText;"
"if("JS_CONDITION_OBJ_TYPE_xxxx-geheimes-Wort!!_SUPPORTED"){basic_Ref_object=iref_c;break_verdient=true; break;/*double break wohl net möglich*/}"
/*basis_ref = cf[li].getElementsByClassName('curriculum-item clearfix')[0].getElementsByClassName('ci-info')[0].getElementsByClassName('ci-title')[0]; "
"var tttttt_text=basis_ref.getElementsByClassName('title')[0].innerText;"
"var typ_course=basis_ref.getElementsByTagName('span')[1].innerText;"
"var object_count=basis_ref.getElementsByTagName('span')[2].innerText;"
"var was_untendrunter_steht=iref_c.getElementsByClassName('ci-details')[0].getElementsByTagName('span')[0].innerText;"////ENde kurs-infos
"submit_additional_course_information(i,li,tttttt_text,typ_course,object_count,was_untendrunter_steht,iref_c.getAttribute('data-lectureid'));"

//var iref_c=cf[li].getElementsByClassName('curriculum-item clearfix')[0];"

*/
"}if(break_verdient){break;}}"
"unlock_content_data_event();basic_Ref_object.click();}window.clearInterval(Aaktives_Intervall);"//@TODO:checken ob erstes Video
			"}"
			"}"
			"}"
			"                  };};"
			"Aaktives_Intervall=setInterval(dccvf, 200); ";

		current_elem_count_selected = 0;
		//frame->ExecuteJavaScript(js_Code_getlist_von_vorher,frame->GetURL(),0);
		frame->ExecuteJavaScript(js_Code, frame->GetURL(), 0);

	}
	//@TODO: von dem ios7 kurs wird ende nicht erkannt
	else if (((str.find(L".cloxxxx-geheimes-Wort!!front.net/") != std::wstring::npos) && ((str.find(L".mp4") != std::wstring::npos) || (str.find(L".pdf") != std::wstring::npos) || (str.find(L".mp3") != std::wstring::npos))||((str.find(L"youtube.com")||str.find(L"googlevide.com"))&&(request->GetResourceType()==RT_MEDIA)/*||(request->GetResourceType()==RT_SUB_RESOURCE)*/)) && (!execute_submit_js_once/*müsste gehen,einfach dass man sich die Vorschau-Videos angucken kann*/)){//scheint nicht in allen Fällen zu klappen,ist wohl alles nicht cloxxxx-geheimes-Wort!!front
		//contents_have_been_loaded ist eigentlich schlechter
#ifndef TEST_DONT_PROCEED
		 ::SetEvent(thread_event_start_abort_link_found);
#endif
		current_browser = browser;
		//::MessageBox(NULL, TEXT("cloxxxx-geheimes-Wort!!frint link da"), TEXT("fd"), MB_OK);//@TODO:youtube videos auch handeln
		auto cf = CefProcessMessage::Create("link_received_proceed");
		cf->GetArgumentList()->SetString(0, request->GetURL());
		cf->GetArgumentList()->SetInt(1, current_elem_count_selected);
		cf->GetArgumentList()->SetBool(2, true);
#ifndef TEST_DONT_PROCEED
			browser->SendProcessMessage(PID_RENDERER, cf);
#endif
		if (str.find(L".pdf") != std::wstring::npos){
			look_for_pdf_e_book = false;//pdf führt manchmal zu fehler in der pdf.dll hier breakpoint,aber ob ich was dafür kann??vllt .sollte es nicht unterbrochen werden das Laden von der PDF
			return false;//@TODO:test ob ende pdf.dll breakpoints->absturz access violation oder so was
		}
		else{
			return true;//block request
		}
	}
	else if (str.find(L"xxxx-geheimes-Wort!!.com/course/buynow-popup") != std::wstring::npos){//@TODO:workaround,da nicht immer ausköst

		//löst nicht aus,denke ich
		send_end_message(browser);
	}


	return false;


}
void AppHandler::onResourceInterceptText(CefString url, std::string &data){
	//::MessageBox(NULL,"ss","fdfds",MB_OK);
	if (data.find("{\"type\":\"Article\"") != std::string::npos){//wie kann das sein,breakpoint löst nicht aus
		auto msg = CefProcessMessage::Create("query_2count_values");//problem:wird zu früh aufgerufen,und zwar wird beim ersten Mal ein /data/content geladen,aber die Element sind noch net im Vektor
		msg->GetArgumentList()->SetInt(0, current_elem_count_selected);
		::SetEvent(thread_event_start_abort_link_found);
		current_browser->SendProcessMessage(PID_RENDERER, msg);
		intercepted_data_queue.push_back(data);
		current_browser = current_browser;
		auto cf = CefProcessMessage::Create("link_received_proceed");
		cf->GetArgumentList()->SetString(0, url);
		cf->GetArgumentList()->SetInt(1, current_elem_count_selected);
		cf->GetArgumentList()->SetBool(2, false);
#ifndef TEST_DONT_PROCEED
		current_browser->SendProcessMessage(PID_RENDERER, cf); //@TODO:ohne copy n paste
#endif
	}
	else if (data.find("{\"type\":\"E-Book\"") != std::string::npos){
		look_for_pdf_e_book = true;

	}

}//komisch keine winapi-funktionen gehen hier wirklich,immer nur false als Rückgabe und bei der MEssageBox wird nix angezeigt
bool AppHandler::OnProcessMessageReceived(CefRefPtr<CefBrowser> browser,
	CefProcessId source_process,
	CefRefPtr<CefProcessMessage> message)
{
		if (message->GetName() == "restore_defaults"){
			restore_defaults(); //browser->GetMainFrame()->LoadURL("http://www.xxxx-geheimes-Wort!!.com/courses");

		}
		else if (message->GetName() == "browse_to_url"){
			browser->GetMainFrame()->LoadURL(message->GetArgumentList()->GetString(0));

		}
		else if (message->GetName() == "logout"){ //scheint nicht auszuloggen
			browser->GetMainFrame()->ExecuteJavaScript("window.location.href=document.getElementsByClassName('links logout')[0].getElementsByClassName('link fxac')[0].href;", browser->GetMainFrame()->GetURL(), 0);
			//browser->GetFocusedFrame()->ExecuteJavaScript("window.location.href=document.getElementsByClassName('links logout')[0].getElementsByClassName('link fxac')[0].href;", browser->GetFocusedFrame()->GetURL(), 0);
		}

	else if (message->GetName() == CefString("cloxxxx-geheimes-Wort!!front_mp4_link_received_callback")){
		//::MessageBox(NULL, TEXT("msg zurück bekommen"), TEXT("fd"), MB_OK);
		current_elem_count_selected = message->GetArgumentList()->GetInt(2);
		int id_js_i = message->GetArgumentList()->GetInt(0);//id_js_i  >=1
		int id_js_lower_item_as_i = message->GetArgumentList()->GetInt(1);
		std::string js_str =
			"document.getElementById('tab-curriculum').getElementsByClassName('curriculum-items-list')[0].getElementsByClassName('curriculum-section-container')["
			+ std::to_string(id_js_i) + "]"
			".getElementsByClassName('curriculum-item-container')[" + std::to_string(id_js_lower_item_as_i) + "].getElementsByClassName('curriculum-item clearfix')[0].click();";
		;
		CefString js_code; js_code.FromString(js_str);
	
		browser->GetFocusedFrame()->ExecuteJavaScript(js_code, browser->GetFocusedFrame()->GetURL(), 0);//hoffentlich gehts so
		::ResetEvent(thread_event_start_timeout_counter);
		::SetEvent(thread_event_start_timeout_counter);//@TODO:das hinkriegen,das auch beim allerersten KLick aufs allererste der Countdown läuft
	}//@TODO:irgendwo muss es noch einen Fehler bei den ID'S geben denn bei einem springt er z.b. beim ungefähr 5. mal ganz an den Anfang
	else if (message->GetName() == "set_start_count_value"){
		current_elem_count_selected = message->GetArgumentList()->GetInt(0);
	}
	else if (message->GetName() == "demand_send_start_count_value_changed"){
		CefRefPtr<CefProcessMessage>msg = CefProcessMessage::Create("prepare_value_count_change");
		msg->GetArgumentList()->SetString(0, message->GetArgumentList()->GetString(0));
		msg->GetArgumentList()->SetString(1, message->GetArgumentList()->GetString(1));
		browser->SendProcessMessage(PID_RENDERER, msg);
	}
	else if (message->GetName() == "broadcast_course_name"){

		string basic_dl_suffix_for_folder = message->GetArgumentList()->GetString(0);
		string folder_suffix = str_replace("/", "-", basic_dl_suffix_for_folder);
		folder_suffix = str_replace("<", "", folder_suffix);
		folder_suffix = str_replace(">", "", folder_suffix);
		folder_suffix = str_replace("|", "_", folder_suffix);
		folder_suffix = str_replace("?", ".", folder_suffix);
		folder_suffix = str_replace(":", "", folder_suffix);
		folder_suffix = str_replace("\\", "", folder_suffix);
		folder_suffix = str_replace("\"", "", folder_suffix);
		course_put_downloads_in_here = m_folder_where_to_put_downloads + "\\" + folder_suffix;
		CefRefPtr<CefProcessMessage>msg = CefProcessMessage::Create("tell_course_folder_download_path");
		msg->GetArgumentList()->SetString(0, course_put_downloads_in_here);
		browser->SendProcessMessage(PID_RENDERER, msg);
		
		//downloader_browser
	}
	else if (message->GetName() == "query_2count_values_callback"){
		std::ofstream of;
		of.open(course_put_downloads_in_here + "\\" + std::to_string(message->GetArgumentList()->GetInt(0)) + "_" + std::to_string(message->GetArgumentList()->GetInt(1)) + ".json", std::ios::app);
		//::MessageBox(NULL,"hat was mit absurz zu tun,ins schlechte milieu","fd",MB_OK);
		of << intercepted_data_queue[0];
		intercepted_data_queue.erase(intercepted_data_queue.begin());
		of.close();



	}
	else if (message->GetName() == "unlock_content_data_event_received"){

		lock_content_data_listener = true;
	}
	else if (message->GetName() == "delegate_forced_end"){

		send_end_message(browser);

	}
	else if (message->GetName() == "forward_signal_all_courses_finished"){

		downloader_browser->add_all_elements_to_html_download_queue();
	}
	else if (message->GetName() == "delete_cookies"){

		CefPostTask(TID_IO, base::Bind(&AppHandler::task_delete_cookies, this, true));
	}
	/*else if (message->GetName() == "create_urlrequest_for_dl"){
	CefRefPtr<CefRequest>cefreq;
	std::string str = "https://www.xxxx-geheimes-Wort!!.com/api-1.1/lectures/"+message->GetArgumentList()->GetString(1).ToString()+"/content";
	cefreq->SetURL(str); cefreq->SetMethod("GET");
	CefRequest::HeaderMap headers;
	headers.insert(std::make_pair("User-Agent", "Mozilla/5.0 (Windows NT 6.1; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/39.0.2136.0 Safari/537.36"));
	headers.insert(std::make_pair("HeaderB", "ValueB"));
	cefreq->SetHeaderMap(headers);
	CefURLRequest::Create(cefreq, new DL_Basic_URLRequest("hey"));

	}*/

	return true;
}//vom originalen cefsimple


bool AppHandler::OnBeforeBrowse(CefRefPtr<CefBrowser>browser, CefRefPtr<CefFrame>frame, CefRefPtr<CefRequest>request, bool is_redirect){
	//	browser->GetHost()->ShowDevTools(,this,);
	//browser->SendProcessMessage(PID_RENDERER, CefProcessMessage::Create("show_dev_tools:"));
	//browser->SendProcessMessage(PID_RENDERER, CefProcessMessage::Create("handshake_with_mainapp_getting_to-Know_each_other"));
	return false;
}
std::string AppHandler::_OnResourceResponse(CefRefPtr<CefBrowser>browser, CefRefPtr<CefFrame>frame, CefRefPtr<CefRequest>request, CefURLRequest::Status status, CefURLRequest::ErrorCode errorcode, CefRefPtr<CefResponse>response, std::string & data){
	//if (request->GetURL().ToString().st)

	//::MessageBoxA(NULL, data.c_str(), "dsds", MB_OK);
	return data;
}

AppHandler::AppHandler(std::string &folder_where_to_put_downloads) : is_closing_(false), m_folder_where_to_put_downloads(folder_where_to_put_downloads)  {
	//DCHECK(!g_instance);//weil keine instanzen-dingens oben implementiert
	//g_instance = this;hier das gleiche wie oben drüber
	apphandler_browser = this;
	thread_event_start_timeout_counter = Threading::event_create();
	thread_event_start_abort_link_found = Threading::event_create();
	Thread t(thread_timeout_counter_for_max_time_a_pageload_is_allowed_to_consume);
}

//ab hier auch vom CefProjekt cefsimple
void AppHandler::OnAfterCreated(CefRefPtr<CefBrowser> browser) {
	CEF_REQUIRE_UI_THREAD();
	current_browser = browser;
	// Add to the list of existing browsers.
	browser->SendProcessMessage(PID_RENDERER,CefProcessMessage::Create("on_after_created"));
	browser_list_.push_back(browser);
}
bool AppHandler::DoClose(CefRefPtr<CefBrowser> browser) {
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

void AppHandler::OnBeforeClose(CefRefPtr<CefBrowser> browser) {
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

void AppHandler::OnLoadError(CefRefPtr<CefBrowser> browser,
	CefRefPtr<CefFrame> frame,
	ErrorCode errorCode,
	const CefString& errorText,
	const CefString& failedUrl) {
	CEF_REQUIRE_UI_THREAD();

	// Don't display an error for downloaded files.
	if (errorCode == ERR_ABORTED)
		return;

	frame->LoadString(CefString("<html><h1>LOAD ERROR<h1>Laden von dieser Seite hier fehlgeschlagen.Ich hoffe sie sitzen noch am PC.</html>"), failedUrl);
}

void AppHandler::CloseAllBrowsers(bool force_close) {
	if (!CefCurrentlyOn(TID_UI)) {
		// Execute on the UI thread.
		CefPostTask(TID_UI,
			base::Bind(&AppHandler::CloseAllBrowsers, this, force_close));
		return;
	}

	if (browser_list_.empty())
		return;

	BrowserList::const_iterator it = browser_list_.begin();
	for (; it != browser_list_.end(); ++it)
		(*it)->GetHost()->CloseBrowser(force_close);
}
void AppHandler::OnTitleChange(CefRefPtr<CefBrowser> browser,
	const CefString& title) {
	CEF_REQUIRE_UI_THREAD();

	CefWindowHandle hwnd = browser->GetHost()->GetWindowHandle();
	SetWindowTextW(hwnd, std::wstring(title).c_str());
}
//bei stock-trading-ninja-learn-how-to-make-money-trading-stocks gleich absturz ganz nach unten