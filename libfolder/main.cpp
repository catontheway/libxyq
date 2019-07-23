#include <tchar.h>
#include <windows.h>
#include "../libutil/cFolder.h"


int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	cFolder::getInstance()->write();
	return 0;
}