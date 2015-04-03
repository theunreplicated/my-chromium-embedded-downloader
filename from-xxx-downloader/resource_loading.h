#ifndef INC_RESOURCE_LOADING_H
#define INC_RESOURCE_LOADING_H
//#inclxxxx-geheimes-Wort!!e <windows.h>
//#inclxxxx-geheimes-Wort!!e <cstdio>
//#inclxxxx-geheimes-Wort!!e "resource.h"
struct ResourceFileLoadReturnType;
namespace Resource{
	ResourceFileLoadReturnType* /***/LoadFileInResource(int name, int type/*, DWORD& size, const char*& data*/);
	char * CommonLoad(int name, int type);
};
#endif