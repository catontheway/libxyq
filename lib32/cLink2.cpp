#include "cLink2.h"
#include <windows.h>

cLink2::cLink2(ccastar::ulong max)
{
	head.datasize = max * sizeof(sLink2);
	head.handle = HeapCreate(HEAP_GENERATE_EXCEPTIONS, head.datasize, head.datasize);
	head.first = nullptr;
	head.tail = nullptr;
	head.cur = nullptr;
	head.nodesCount = 0;
}

cLink2::~cLink2()
{
	if (head.handle)
	{
		HeapDestroy((HANDLE)head.handle);
	}
}

bool cLink2::insert(ccastar::voidp v, ccastar::ulong k, eInsert e /* = eInsert::after */)
{
	sLink2* node = (sLink2*)HeapAlloc(head.handle, 0, sizeof(sLink2));
	if (!node)
	{
		return false;
	}

	node->v = v;
	node->k = k;

	//	将当前节点的父与子链接起来
	if (head.cur)
	{
		if (e == eInsert::after)
		{
			node->parent = head.cur;
			node->child = head.cur->child;
			head.cur->child = node;
			if (node->child)
				node->child->parent = node;
			if (head.cur == head.tail)
				head.tail = node;
		}
		else
		{
			node->parent = head.cur->parent;
			node->child = head.cur;
			head.cur->parent = node;
			if (node->parent)
				node->parent->child = node;
			if (head.cur == head.first)
				head.first = node;
		}
	}
	else
	{
		//	链表是空的
		node->parent = nullptr;
		node->child = nullptr;

		head.first = node;
		head.tail = node;
	}

	head.cur = node;

	++head.nodesCount;

	return TRUE;
}

void cLink2::remove()
{
	if (!head.cur)
		return;

	sLink2* cur = head.cur;

	if (--head.nodesCount == 0)
	{
		head.first = nullptr;
		head.tail = nullptr;
		head.cur = nullptr;
	}
	else
	{
		//	将当前节点的父与子链接起来
		if (cur->parent)
			cur->parent->child = cur->child;

		if (cur->child)
		{
			cur->child->parent = cur->parent;

			//	更新表头
			head.cur = cur->child;
		}
		else
			head.cur = cur->parent;


		if (cur == head.first)
			head.first = cur->child;
		else if (cur == head.tail)
			head.tail = cur->parent;

	}

	HeapFree(head.handle, 0, cur);
}

void cLink2::remove(ccastar::voidp link)
{
	setCur(link);
	remove();
}

void cLink2::clear()
{
	cLink2::~cLink2();
	cLink2::cLink2(head.datasize);
}

void cLink2::setCur(ccastar::voidp link)
{
	head.cur = (sLink2*)link;
}

bool cLink2::setParent()
{
	if (head.cur)
	{
		if (head.cur->parent)
		{
			head.cur = head.cur->parent;
			return true;
		}
	}
	return false;
}

bool cLink2::setChild()
{
	if (head.cur)
	{
		if (head.cur->child)
		{
			head.cur = head.cur->child;
			return true;
		}
	}
	return false;
}

void cLink2::setFirst()
{
	head.cur = head.first;
}

void cLink2::setTail()
{
	head.cur = head.tail;
}

ccastar::voidp cLink2::getValue()
{
	return head.cur ? head.cur->v : nullptr;
}

ccastar::ulong cLink2::getKey()
{
	return head.cur ? head.cur->k : 0;
}

ccastar::voidp cLink2::getCur()
{
	return head.cur;
}

ccastar::ulong cLink2::getNodesCount()
{
	return head.nodesCount;
}