#include "txtJiaju.h"

ccc_txt_instance_cpp(txtJiaju);

txtJiaju::txtJiaju()
{
	sTable tableEmpty;
	_tables.insert(std::make_pair(eIcon::一家y, tableEmpty));
	_tables.insert(std::make_pair(eIcon::二家e, tableEmpty));
	_tables.insert(std::make_pair(eIcon::三家s, tableEmpty));
	_tables.insert(std::make_pair(eIcon::四家s, tableEmpty));
}
