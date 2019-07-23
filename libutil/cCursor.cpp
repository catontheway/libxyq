#include "cCursor.h"

cCursor* cCursor::getInstance()
{
	static cCursor* s_cursor = new cCursor();
	return s_cursor;
}