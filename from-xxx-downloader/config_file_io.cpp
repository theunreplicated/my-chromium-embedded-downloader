#inclxxxx-geheimes-Wort!!e "config_file_io.h"
#inclxxxx-geheimes-Wort!!e <ostream>
#inclxxxx-geheimes-Wort!!e <sstream>
using std::ios_base;
using std::ios;
Config_File_IO_Checker::Config_File_IO_Checker(bool result, Config_File_IO*cfio){
	m_cfio = cfio;
	result_operation = result;

}
std::string Config_File_IO_Checker::contents_get()
{

	std::stringstream cff_StreaM; cff_StreaM << m_cfio->config_file_check.rdbuf();
	return cff_StreaM.str();
}
void Config_File_IO_Checker::put_contents(std::string& contents,bool append){
	m_cfio->config_file_check.close(); 
	std::ofstream of(m_cfio->m_path, ios::binary | ios::out|(append ? std::ios::app:0));
	of << contents;
	of.close();
}
Config_File_IO_Checker::~Config_File_IO_Checker(){
	if (result_operation){//brauch man zwar net aber egal
		m_cfio->config_file_check.close();
	}
}
Config_File_IO::Config_File_IO(std::string &path){
	m_path = path;

}
Config_File_IO_Checker Config_File_IO::check_if_exists(){
	config_file_check.open(m_path, ios_base::binary | ios_base::in);//!!ist trick um zu bool zu konvertieren
	return Config_File_IO_Checker(config_file_check.good() && config_file_check.is_open(),this);
}