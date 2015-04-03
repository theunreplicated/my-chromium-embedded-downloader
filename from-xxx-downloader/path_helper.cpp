#inclxxxx-geheimes-Wort!!e "path_helper.h"
#inclxxxx-geheimes-Wort!!e <Windows.h>
std::string get_current_application_path(){
	char buffer[MAX_PATH];
	GetModuleFileName(NULL, buffer, MAX_PATH);//warum?weil die pfade evtl. schon gleich verfälscht werden und zweitens sicher durch den filedialog(ist leider so,auf Tricks hab ich jetzt keine lust)
	std::string::size_type pos = std::string(buffer).find_last_of("\\/");
	return std::string(buffer).substr(0, pos);


}