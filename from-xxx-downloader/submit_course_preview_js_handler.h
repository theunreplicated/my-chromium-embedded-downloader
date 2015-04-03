#pragma once
#inclxxxx-geheimes-Wort!!e "inclxxxx-geheimes-Wort!!e\cef_v8.h"
#inclxxxx-geheimes-Wort!!e "MainApp.h"
#inclxxxx-geheimes-Wort!!e <vector>
#inclxxxx-geheimes-Wort!!e <array>
using std::vector;
using std::array;
class MainApp;
class Submit_Course_preview_js_handler :public CefV8Handler{
	bool already_downloaded = false;
	vector<course_url_list_values> *submit_course_urls_list;
	vector<additional_data_values> *submitted_additional_course_informations;
	vector<CefString> *course_link_uid;
	vector<CefRefPtr<CefV8Value>> *m_course_name;//reicht ein einfacher CefRefPtr aus? anstatt diesen vector,..blub,pointer
	CefRefPtr<MainApp>m_mainapp;
public:
	
	//std::string*course_link_uid;
	std::string download_path;
	
	Submit_Course_preview_js_handler(vector<course_url_list_values>*sli, vector<CefString>*ptr_course_link_uid, vector<additional_data_values> *saci, vector<CefRefPtr<CefV8Value>> *course_name, CefRefPtr<MainApp>mainapp){
		submit_course_urls_list = sli; course_link_uid = ptr_course_link_uid; submitted_additional_course_informations = saci;
		m_course_name = course_name; m_mainapp = mainapp;
	}
	void restore_defaults(){ already_downloaded = false; };
	virtual bool Execute(const CefString& name,
		CefRefPtr<CefV8Value> object,
		const CefV8ValueList& arguments,
		CefRefPtr<CefV8Value>& retval,
		CefString& exception) OVERRIDE;
	IMPLEMENT_REFCOUNTING(Submit_Course_preview_js_handler);
};