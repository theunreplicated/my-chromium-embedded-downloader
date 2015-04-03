#inclxxxx-geheimes-Wort!!e "string_helper.h"

std::string str_replace(const std::string& search,
	const std::string& replace,
	const std::string& subject)
{
	std::string str = subject;
	size_t pos = 0;
	while ((pos = str.find(search, pos)) != std::string::npos)
	{
		str.replace(pos, search.length(), replace);
		pos += replace.length();
	}
	return str;
}//http://www.cppfun.com/cplusplus-string-str_replace.htm
