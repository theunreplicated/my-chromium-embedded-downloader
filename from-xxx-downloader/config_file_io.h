#ifndef INC_CONFIG_FILE_IO_H
#define INC_CONFIG_FILE_IO_H
#inclxxxx-geheimes-Wort!!e <string>
#inclxxxx-geheimes-Wort!!e <fstream>
class Config_File_IO;
class Config_File_IO_Checker/*Der Checker,ohowooooum*/{
	Config_File_IO*m_cfio;
	
public:
	bool result_operation;
	Config_File_IO_Checker(bool result,Config_File_IO*cfio);
	std::string contents_get();
	void put_contents(std::string& contents, bool append=false);
	~Config_File_IO_Checker();
};
class Config_File_IO{
	std::string m_path;
	std::fstream config_file_check;
	friend Config_File_IO_Checker;
public:
	Config_File_IO(std::string &path);
	Config_File_IO_Checker check_if_exists();

};


#endif