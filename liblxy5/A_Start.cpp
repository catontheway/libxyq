#include "_global.h"


// #define POSITIVE(x,y) ((((x) - (y))>0)? ((x)-(y)):((y)-(x)))
const int IS_UNKNOWN = 0;
const int IS_OPEN = 1;
const int IS_CLOSE = 2;
const int MAP_ROAD = 0;
const int MAP_WALL = 1;
//const int MAP_CANT = 2;


bool cFindPath::findAstart(cObj* pObj, int Xend, int Yend)
{
// 	auto paths = g_pMainState->m_Map.m_pBmp->_reader->_astar.findAstart(pObj->GetX() / 20, pObj->GetY() / 20, Xend /= 20, Yend /= 20);
// 
// 	if (paths.empty())
// 	{
// 		return true;
// 	}
// 
// 	pObj->m_AstartPathVecs.clear();//清空
// 	pObj->m_AstartPathIndex = -1;
// 	VecInt v;
// 	forv(paths, i)
// 	{
// 		v.x = paths[i].x * 20;
// 		v.y = /*g_pMainState->m_Map.m_pMap->m_Height - */paths[i].y * 20;
// 		pObj->m_AstartPathVecs.push_back(v);
// 		pObj->m_AstartPathIndex += 1;
// 	}
// 	pObj->m_AstartPathIndex -= 1;
// 	if (pObj->m_AstartPathIndex < 0)return false;
// 	pObj->setNextTargetOnAstart(pObj->m_AstartPathVecs[pObj->m_AstartPathIndex].x, pObj->m_AstartPathVecs[pObj->m_AstartPathIndex].y);
// 	pObj->m_AstartPathIndex -= 1;
//	return false;


	if (Xend < 0 || Yend < 0)
	{
		return false;
	}
	InitMap();

	int Xstart = pObj->GetX() / 20;
	int Ystart = pObj->GetY() / 20;
	Xend /= 20;
	Yend /= 20;

	if (Xend>m_Width - 1 || Yend>m_Height - 1)return false;
	//如果目标点在障碍内,则移动目标点的位置
	while(g_Map[Xend][Yend].iColor==MAP_WALL)
	{
		if (Xend > Xstart)
			Xend -= 1;
		else
			Xend += 1;
		if (Yend > Ystart)
			Yend -= 1;
		else
			Yend += 1;
		if (abs(Xend - Xstart)<10 && abs(Yend == Ystart)<10)
			return true;
	}
	VecInt coordinate;
	VecInt minCoord;
	coordinate.x = Xstart;
	coordinate.y = Ystart;
	int xx1 = (Xstart - Xend)*5;
	int yy1 = (Ystart - Yend)*5;
	g_Map[Xstart][Ystart].iH = (int)sqrt(xx1*xx1 + yy1*yy1);;
	g_Map[Xstart][Ystart].iG = 0;
	g_Map[Xstart][Ystart].iF = g_Map[Xstart][Ystart].getF();

	// 1. 把起始格添加到开启列表
	m_iOpenList.push_back(coordinate, g_Map);
	g_Map[Xstart][Ystart].isOpen = IS_OPEN;

	//2.重复如下工作
	int minF = g_Map[Xstart][Ystart].iF; //该变量表示最小F值
	m_isFind = false; //该变量，用来检测目标位置是否被添加进了关闭列表

	while (!m_iOpenList.empty()) //当开启列表为空时， 循环停止
	{
		//a).寻找开启列表 中F最低的格子，我们称它为当前格
		minCoord = m_iOpenList.begin();
		minF = g_Map[minCoord.x][minCoord.y].getF();
		if ((minCoord.x == Xend) && (minCoord.y == Yend)) //如果目标位置被添加到了关闭容器，直接跳出循环
		{
			m_isFind = true;
			break;
		}

		//b).把遍历得到的当前格切换到关闭列表
		m_iOpenList.removeFront(g_Map); //删除开启列表中的F值最低的格子
		g_Map[minCoord.x][minCoord.y].isOpen = IS_CLOSE;//把该格子的标记设置为“在关闭列表中”


		int i = -1, j = -1;
		int x = 0, y = 0;
		for (i = -1; i < 2; ++i)  //遍历当前格子周围的其他8个格子
		{
			for (j = -1; j < 2; ++j)
			{
				x = minCoord.x + i;
				y = minCoord.y + j;

				if ((x < 0) || (y < 0) || (x > m_Width - 1) || (y > m_Height - 1)) //* 坐标在屏幕之外，略过
					continue;
				if (g_Map[x][y].iColor == MAP_WALL) //* 格子为墙，不能通过，略过
				{
					continue;
				}
				if (g_Map[x][y].isOpen == IS_CLOSE) //* 格子已经在关闭列表中了，略过
					continue;
				if (g_Map[x][y].isOpen == IS_UNKNOWN) //* 如果该格子未加入到开启列表，
				{
					coordinate.x = x;
					coordinate.y = y;
					g_Map[x][y].father = minCoord;  //当前格作为这一格的父节点
					 xx1 = (Xend - x) * 5;
					 yy1 = (Yend - y) * 5;
					g_Map[x][y].iH =(int)sqrt( xx1*xx1 + yy1*yy1);
					//设置G
					if ((i == 0) || (j == 0))
					{
						g_Map[x][y].iG = g_Map[minCoord.x][minCoord.y].iG + 5;
					}
					else
					{
						g_Map[x][y].iG = g_Map[minCoord.x][minCoord.y].iG + 7;
					}
	
					//设置F
					g_Map[x][y].iF = g_Map[x][y].getF();
					//加入开吂列表
					g_Map[x][y].isOpen = IS_OPEN;
					//放入开启列表
					m_iOpenList.push_back(coordinate, g_Map);  //把他加入到开启列表中
					continue;
				}

				if (g_Map[x][y].isOpen == IS_OPEN) //* 如果该格子已经在开启列表中
				{
					int newG;
					if ((i == 0) || (j == 0))  //计算新的G值
					{
						newG = g_Map[minCoord.x][minCoord.y].iG + 5;
					}
					else
					{
						newG = g_Map[minCoord.x][minCoord.y].iG + 7;
					}
					if (newG < g_Map[x][y].iG) //如果新的G值比先前的更好
					{
						g_Map[x][y].father = minCoord; //把该格的父节点改为当前格
						int position = g_Map[x][y].iHeapPosition; //得到该节点在堆中的位置
						g_Map[x][y].iG = newG;
						g_Map[x][y].iF = g_Map[x][y].getF();
						m_iOpenList.newHeap(position, g_Map);             //由于F值发生了变化，更新此节点在堆中的位置
					}
				}
			}
		}
	}
	if (m_isFind) //3).如果找到路径了，保存路径
	{
		AstartNode tempNode;
		tempNode.father = minCoord;
		pObj->m_AstartPathVecs.clear();//清空
		pObj->m_AstartPathIndex = -1;
		int x1, y1;
		while (true)
		{
			if ((tempNode.father.x == -1) && (tempNode.father.y == -1)){
				break;
			}
			x1= tempNode.father.x ;
			y1= tempNode.father.y ;
			tempNode.father.x*=20;
			tempNode.father.y*=20;
			pObj->m_AstartPathVecs.push_back(tempNode.father);
			pObj->m_AstartPathIndex += 1;
			tempNode.father = g_Map[x1][y1].father;
		}
		pObj->m_AstartPathIndex -= 1;
		if (pObj->m_AstartPathIndex < 0)return false;
		pObj->setNextTargetOnAstart(pObj->m_AstartPathVecs[pObj->m_AstartPathIndex].x, pObj->m_AstartPathVecs[pObj->m_AstartPathIndex].y);
		pObj->m_AstartPathIndex -= 1;
	}
	else //没找到路径的处理
	{

	}
	return false;
}
//我准备在cMyMap中调用它
void cFindPath::setDataByMap(cMyMap* pMap)
{
//	return;
	Free();
	m_Height = pMap->m_pMap->m_Height/20;
	m_Width = pMap->m_pMap->m_Width/20;
	if (!m_Height)return;
	if (!m_Width)return;
	g_Map = new AstartNode*[m_Width];
	for (int i = 0; i < m_Width;i++)
	{
		g_Map[i] = new AstartNode[m_Height];
	}
	for (int i = 0; i < m_Width;i++)
	for (int j = 0; j < m_Height; j++)
	{
		if (pMap->m_pBmp->isFold(i * 20, j * 20))
		{
			g_Map[i][j].iColor = MAP_WALL;
		}
		else
			g_Map[i][j].iColor = MAP_ROAD;
	}

}

void cFindPath::Free()
{
	if (!g_Map)return;
	for (int i = 0; i < m_Width; i++)
	{
		delete[] g_Map[i];
	}
	SAFE_DELETE_ARRAY(g_Map);
	m_Width = 0;
	m_Height = 0;
}

bool cFindPath::InitMap()
{
//	return true;
	if (!m_Height)return false;
	if (!m_Width)return false;
	for (int x = 0; x < m_Width; x++)
	{
		for (int y = 0; y < m_Height; y++)
		{
			g_Map[x][y].iHeapPosition = -1;
			g_Map[x][y].iH = -1;
			g_Map[x][y].iG = -1;
			g_Map[x][y].iF = -1;
			g_Map[x][y].isOpen = IS_UNKNOWN;
			g_Map[x][y].father.x = -1;
			g_Map[x][y].father.y = -1;
		}
	}
	if (!m_iOpenList.empty()) //清空开启列表
		m_iOpenList.clear();

	return true;
}

cFindPath::~cFindPath()
{
	Free();
}


//构造函数
cHeap::cHeap()
{
}

//判断二叉堆是否为空
bool cHeap::empty()
{
	if (vecs.size() == 0)
		return true;
	else
		return false;
}

//清空二叉堆
void cHeap::clear()
{
	if (vecs.size() != 0)
		vecs.clear();
}

//返回二叉堆中的第一个元素（即F值最低的元素）
VecInt cHeap::begin()
{
	return vecs[0];
}

//删除二叉堆的堆首元素（即F值最低的元素）
void cHeap::removeFront(AstartNode**g_Map)
{
	if (vecs.size() == 0)
		return;

	g_Map[vecs[vecs.size() - 1].x][vecs[vecs.size() - 1].y].iHeapPosition = 0;
	g_Map[vecs[0].x][vecs[0].y].iHeapPosition = -1;

	vecs[0] = vecs[vecs.size() - 1];      //用最后一个元素把第一个元素覆盖掉，即为删除
	vecs.pop_back();                //删除容器尾巴元素



	int currentIndex = 0;
	while (currentIndex < vecs.size()) //把新的堆首元素放在堆中适当的位置
	{
		int leftChildIndex = 2 * currentIndex + 1;
		int rightChildIndex = 2 * currentIndex + 2;

		//已经到最底层，结束
		if (rightChildIndex > vecs.size())
			break;
		int minIndex = leftChildIndex;

		//有两个孩子，找出两个孩子节点中F值最低的元素
		if (rightChildIndex<vecs.size() && (g_Map[vecs[minIndex].x][vecs[minIndex].y].getF()  > g_Map[vecs[rightChildIndex].x][vecs[rightChildIndex].y].getF()))
		{
			minIndex = rightChildIndex;
		}

		//如果当前节点的F值 大于 他孩子节点的F值，则交换
		if (g_Map[vecs[currentIndex].x][vecs[currentIndex].y].getF() > g_Map[vecs[minIndex].x][vecs[minIndex].y].getF())
		{
			VecInt temp = vecs[minIndex];
			vecs[minIndex] = vecs[currentIndex];
			vecs[currentIndex] = temp;

			//同步保存地图中该坐标在堆中的最新位置
			g_Map[vecs[currentIndex].x][vecs[currentIndex].y].iHeapPosition = currentIndex;
			g_Map[vecs[minIndex].x][vecs[minIndex].y].iHeapPosition = minIndex;
			currentIndex = minIndex;
		}
		else
		{
			break;
		}
	}
}

//返回堆中的最小F值
int cHeap::getMinF(AstartNode**g_Map)
{
	if (vecs.size() > 0)
		return g_Map[vecs[0].x][vecs[0].x].getF();
	else
		return 0;
}


//往堆中添加新的元素（节点）
void cHeap::push_back(VecInt element, AstartNode**g_Map)
{
	vecs.push_back(element);//把新节点添加到堆的末尾
	int currentIndex = vecs.size() - 1;
	g_Map[vecs[currentIndex].x][vecs[currentIndex].y].iHeapPosition = currentIndex; //保存该坐标在堆中的位置

	while (currentIndex > 0) //不断的与他的父节点比较，直到该新节点的F值大于他的父节点的F值为止 或者 该新节点到了堆首
	{
		int parentIndex = (currentIndex - 1) / 2;
		if (g_Map[vecs[currentIndex].x][vecs[currentIndex].y].getF() < g_Map[vecs[parentIndex].x][vecs[parentIndex].y].getF())
		{
			VecInt temp = vecs[currentIndex];
			vecs[currentIndex] = vecs[parentIndex];
			vecs[parentIndex] = temp;

			//同步保存地图中该坐标在堆中的最新位置
			g_Map[vecs[currentIndex].x][vecs[currentIndex].y].iHeapPosition = currentIndex;
			g_Map[vecs[parentIndex].x][vecs[parentIndex].y].iHeapPosition = parentIndex;
			currentIndex = parentIndex;
			continue;
		}
		else
		{
			break;
		}
	}
}

//当堆中某元素的F值发生改变时，更新该元素在堆中的位置
void cHeap::newHeap(int position, AstartNode**g_Map)
{
	int currentIndex = position;
	int parentIndex;
	//while (currentIndex > 0) //如果该元素新的F值比他的父节点的F值小，交换
	//{
	//	parentIndex = (currentIndex - 1) / 2;
	//	if (g_Map[v[currentIndex].sx][v[currentIndex].sy].getF()  < g_Map[v[parentIndex].sx][v[parentIndex].sy].getF())
	//	{
	//		Coordinate temp = v[currentIndex];
	//		v[currentIndex] = v[parentIndex];
	//		v[parentIndex] = temp;
	//		g_Map[v[currentIndex].sx][v[currentIndex].sy].iHeapPosition = parentIndex;
	//		g_Map[v[parentIndex].sx][v[parentIndex].sy].iHeapPosition = currentIndex;
	//		currentIndex = parentIndex;
	//		continue;
	//	}
	//	else
	//	{
	//		break;
	//	}
	//}
	VecInt temp;
	//如果上面的循环没有执行，则无法判断该节点的最新F值的相对大小，
	//所以，此时需要把该节点移动到堆首删除掉，然后再在堆末尾添加该节点，最后程序再把该节点移动到堆中适当的位置处
	if (currentIndex == position)
	{
		while (currentIndex > 0) //把该节点移动到堆首
		{
			parentIndex = (currentIndex - 1) / 2;
			temp = vecs[currentIndex];
			vecs[currentIndex] = vecs[parentIndex];
			vecs[parentIndex] = temp;
			g_Map[vecs[currentIndex].x][vecs[currentIndex].y].iHeapPosition = currentIndex;
			g_Map[vecs[parentIndex].x][vecs[parentIndex].y].iHeapPosition = parentIndex;
			currentIndex = parentIndex;
		}
	}
	temp = vecs[0];
	removeFront(g_Map); //删除该节点
	push_back(temp, g_Map);//重新在堆中插入该节点
}

//返回堆中元素的个数
int cHeap::getSize()
{
	return vecs.size();
}












AES::AES(unsigned char* key)
{
	unsigned char sBox[] =
	{ /* 0 1 2 3 4 5 6 7 8 9 a b c d e f */
		0x63, 0x7c, 0x77, 0x7b, 0xf2, 0x6b, 0x6f, 0xc5, 0x30, 0x01, 0x67, 0x2b, 0xfe, 0xd7, 0xab, 0x76, /*0*/
		0xca, 0x82, 0xc9, 0x7d, 0xfa, 0x59, 0x47, 0xf0, 0xad, 0xd4, 0xa2, 0xaf, 0x9c, 0xa4, 0x72, 0xc0, /*1*/
		0xb7, 0xfd, 0x93, 0x26, 0x36, 0x3f, 0xf7, 0xcc, 0x34, 0xa5, 0xe5, 0xf1, 0x71, 0xd8, 0x31, 0x15, /*2*/
		0x04, 0xc7, 0x23, 0xc3, 0x18, 0x96, 0x05, 0x9a, 0x07, 0x12, 0x80, 0xe2, 0xeb, 0x27, 0xb2, 0x75, /*3*/
		0x09, 0x83, 0x2c, 0x1a, 0x1b, 0x6e, 0x5a, 0xa0, 0x52, 0x3b, 0xd6, 0xb3, 0x29, 0xe3, 0x2f, 0x84, /*4*/
		0x53, 0xd1, 0x00, 0xed, 0x20, 0xfc, 0xb1, 0x5b, 0x6a, 0xcb, 0xbe, 0x39, 0x4a, 0x4c, 0x58, 0xcf, /*5*/
		0xd0, 0xef, 0xaa, 0xfb, 0x43, 0x4d, 0x33, 0x85, 0x45, 0xf9, 0x02, 0x7f, 0x50, 0x3c, 0x9f, 0xa8, /*6*/
		0x51, 0xa3, 0x40, 0x8f, 0x92, 0x9d, 0x38, 0xf5, 0xbc, 0xb6, 0xda, 0x21, 0x10, 0xff, 0xf3, 0xd2, /*7*/
		0xcd, 0x0c, 0x13, 0xec, 0x5f, 0x97, 0x44, 0x17, 0xc4, 0xa7, 0x7e, 0x3d, 0x64, 0x5d, 0x19, 0x73, /*8*/
		0x60, 0x81, 0x4f, 0xdc, 0x22, 0x2a, 0x90, 0x88, 0x46, 0xee, 0xb8, 0x14, 0xde, 0x5e, 0x0b, 0xdb, /*9*/
		0xe0, 0x32, 0x3a, 0x0a, 0x49, 0x06, 0x24, 0x5c, 0xc2, 0xd3, 0xac, 0x62, 0x91, 0x95, 0xe4, 0x79, /*a*/
		0xe7, 0xc8, 0x37, 0x6d, 0x8d, 0xd5, 0x4e, 0xa9, 0x6c, 0x56, 0xf4, 0xea, 0x65, 0x7a, 0xae, 0x08, /*b*/
		0xba, 0x78, 0x25, 0x2e, 0x1c, 0xa6, 0xb4, 0xc6, 0xe8, 0xdd, 0x74, 0x1f, 0x4b, 0xbd, 0x8b, 0x8a, /*c*/
		0x70, 0x3e, 0xb5, 0x66, 0x48, 0x03, 0xf6, 0x0e, 0x61, 0x35, 0x57, 0xb9, 0x86, 0xc1, 0x1d, 0x9e, /*d*/
		0xe1, 0xf8, 0x98, 0x11, 0x69, 0xd9, 0x8e, 0x94, 0x9b, 0x1e, 0x87, 0xe9, 0xce, 0x55, 0x28, 0xdf, /*e*/
		0x8c, 0xa1, 0x89, 0x0d, 0xbf, 0xe6, 0x42, 0x68, 0x41, 0x99, 0x2d, 0x0f, 0xb0, 0x54, 0xbb, 0x16 /*f*/
	};
	unsigned char invsBox[256] =
	{ /* 0 1 2 3 4 5 6 7 8 9 a b c d e f */
		0x52, 0x09, 0x6a, 0xd5, 0x30, 0x36, 0xa5, 0x38, 0xbf, 0x40, 0xa3, 0x9e, 0x81, 0xf3, 0xd7, 0xfb, /*0*/
		0x7c, 0xe3, 0x39, 0x82, 0x9b, 0x2f, 0xff, 0x87, 0x34, 0x8e, 0x43, 0x44, 0xc4, 0xde, 0xe9, 0xcb, /*1*/
		0x54, 0x7b, 0x94, 0x32, 0xa6, 0xc2, 0x23, 0x3d, 0xee, 0x4c, 0x95, 0x0b, 0x42, 0xfa, 0xc3, 0x4e, /*2*/
		0x08, 0x2e, 0xa1, 0x66, 0x28, 0xd9, 0x24, 0xb2, 0x76, 0x5b, 0xa2, 0x49, 0x6d, 0x8b, 0xd1, 0x25, /*3*/
		0x72, 0xf8, 0xf6, 0x64, 0x86, 0x68, 0x98, 0x16, 0xd4, 0xa4, 0x5c, 0xcc, 0x5d, 0x65, 0xb6, 0x92, /*4*/
		0x6c, 0x70, 0x48, 0x50, 0xfd, 0xed, 0xb9, 0xda, 0x5e, 0x15, 0x46, 0x57, 0xa7, 0x8d, 0x9d, 0x84, /*5*/
		0x90, 0xd8, 0xab, 0x00, 0x8c, 0xbc, 0xd3, 0x0a, 0xf7, 0xe4, 0x58, 0x05, 0xb8, 0xb3, 0x45, 0x06, /*6*/
		0xd0, 0x2c, 0x1e, 0x8f, 0xca, 0x3f, 0x0f, 0x02, 0xc1, 0xaf, 0xbd, 0x03, 0x01, 0x13, 0x8a, 0x6b, /*7*/
		0x3a, 0x91, 0x11, 0x41, 0x4f, 0x67, 0xdc, 0xea, 0x97, 0xf2, 0xcf, 0xce, 0xf0, 0xb4, 0xe6, 0x73, /*8*/
		0x96, 0xac, 0x74, 0x22, 0xe7, 0xad, 0x35, 0x85, 0xe2, 0xf9, 0x37, 0xe8, 0x1c, 0x75, 0xdf, 0x6e, /*9*/
		0x47, 0xf1, 0x1a, 0x71, 0x1d, 0x29, 0xc5, 0x89, 0x6f, 0xb7, 0x62, 0x0e, 0xaa, 0x18, 0xbe, 0x1b, /*a*/
		0xfc, 0x56, 0x3e, 0x4b, 0xc6, 0xd2, 0x79, 0x20, 0x9a, 0xdb, 0xc0, 0xfe, 0x78, 0xcd, 0x5a, 0xf4, /*b*/
		0x1f, 0xdd, 0xa8, 0x33, 0x88, 0x07, 0xc7, 0x31, 0xb1, 0x12, 0x10, 0x59, 0x27, 0x80, 0xec, 0x5f, /*c*/
		0x60, 0x51, 0x7f, 0xa9, 0x19, 0xb5, 0x4a, 0x0d, 0x2d, 0xe5, 0x7a, 0x9f, 0x93, 0xc9, 0x9c, 0xef, /*d*/
		0xa0, 0xe0, 0x3b, 0x4d, 0xae, 0x2a, 0xf5, 0xb0, 0xc8, 0xeb, 0xbb, 0x3c, 0x83, 0x53, 0x99, 0x61, /*e*/
		0x17, 0x2b, 0x04, 0x7e, 0xba, 0x77, 0xd6, 0x26, 0xe1, 0x69, 0x14, 0x63, 0x55, 0x21, 0x0c, 0x7d /*f*/
	};
	memcpy(Sbox, sBox, 256);
	memcpy(InvSbox, invsBox, 256);
	KeyExpansion(key, w);
}

AES::~AES()
{

}

void AES::Cipher(char *input, char *output)
{
	unsigned char uch_input[1024];
	strToUChar(input, uch_input);
	Cipher(uch_input);
	ucharToHex(uch_input, output);
}

void AES::InvCipher(char *input, char *output)
{
	unsigned char uch_input[1024];
	hexToUChar(input, uch_input);
	InvCipher(uch_input);
	ucharToStr(uch_input, output);
}

unsigned char* AES::Cipher(unsigned char* input)
{
	unsigned char state[4][4];
	int i, r, c;

	for (r = 0; r < 4; r++)
	{
		for (c = 0; c < 4; c++)
		{
			state[r][c] = input[c * 4 + r];
		}
	}

	AddRoundKey(state, w[0]);

	for (i = 1; i <= 10; i++)
	{
		SubBytes(state);
		ShiftRows(state);
		if (i != 10)MixColumns(state);
		AddRoundKey(state, w[i]);
	}

	for (r = 0; r < 4; r++)
	{
		for (c = 0; c < 4; c++)
		{
			input[c * 4 + r] = state[r][c];
		}
	}

	return input;
}

unsigned char* AES::InvCipher(unsigned char* input)
{
	unsigned char state[4][4];
	int i, r, c;

	for (r = 0; r < 4; r++)
	{
		for (c = 0; c < 4; c++)
		{
			state[r][c] = input[c * 4 + r];
		}
	}

	AddRoundKey(state, w[10]);
	for (i = 9; i >= 0; i--)
	{
		InvShiftRows(state);
		InvSubBytes(state);
		AddRoundKey(state, w[i]);
		if (i)
		{
			InvMixColumns(state);
		}
	}

	for (r = 0; r < 4; r++)
	{
		for (c = 0; c < 4; c++)
		{
			input[c * 4 + r] = state[r][c];
		}
	}

	return input;
}

void* AES::Cipher(void* input, int length)
{
	unsigned char* in = (unsigned char*)input;
	int i;
	if (!length)
	{
		while (*(in + length++));
		in = (unsigned char*)input;
	}
	for (i = 0; i < length; i += 16)
	{
		Cipher(in + i);
	}
	return input;
}

void* AES::InvCipher(void* input, int length)
{
	unsigned char* in = (unsigned char*)input;
	int i;
	for (i = 0; i < length; i += 16)
	{
		InvCipher(in + i);
	}
	return input;
}

void AES::KeyExpansion(unsigned char* key, unsigned char w[][4][4])
{
	int i, j, r, c;
	unsigned char rc[] = { 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1b, 0x36, 0x72 };
	for (r = 0; r < 4; r++)
	{
		for (c = 0; c < 4; c++)
		{
			w[0][r][c] = key[r + c * 4];
		}
	}
	for (i = 1; i <= 10; i++)
	{
		for (j = 0; j < 4; j++)
		{
			unsigned char t[4];
			for (r = 0; r < 4; r++)
			{
				t[r] = j ? w[i][r][j - 1] : w[i - 1][r][3];
			}
			if (j == 0)
			{
				unsigned char temp = t[0];
				for (int r2 = 0; r2 < 3; r2++)
				{
					t[r2] = Sbox[t[(r2 + 1) % 4]];
				}
				t[3] = Sbox[temp];
				t[0] ^= rc[i - 1];
			}
			for (r = 0; r < 4; r++)
			{
				w[i][r][j] = w[i - 1][r][j] ^ t[r];
			}
		}
	}
}

unsigned char AES::FFmul(unsigned char a, unsigned char b)
{
	unsigned char bw[4];
	unsigned char res = 0;
	int i;
	bw[0] = b;
	for (i = 1; i < 4; i++)
	{
		bw[i] = bw[i - 1] << 1;
		if (bw[i - 1] & 0x80)
		{
			bw[i] ^= 0x1b;
		}
	}
	for (i = 0; i < 4; i++)
	{
		if ((a >> i) & 0x01)
		{
			res ^= bw[i];
		}
	}
	return res;
}

void AES::SubBytes(unsigned char state[][4])
{
	int r, c;
	for (r = 0; r < 4; r++)
	{
		for (c = 0; c < 4; c++)
		{
			state[r][c] = Sbox[state[r][c]];
		}
	}
}

void AES::ShiftRows(unsigned char state[][4])
{
	unsigned char t[4];
	int r, c;
	for (r = 1; r < 4; r++)
	{
		for (c = 0; c < 4; c++)
		{
			t[c] = state[r][(c + r) % 4];
		}
		for (c = 0; c < 4; c++)
		{
			state[r][c] = t[c];
		}
	}
}

void AES::MixColumns(unsigned char state[][4])
{
	unsigned char t[4];
	int r, c;
	for (c = 0; c < 4; c++)
	{
		for (r = 0; r < 4; r++)
		{
			t[r] = state[r][c];
		}
		for (r = 0; r < 4; r++)
		{
			state[r][c] = FFmul(0x02, t[r])
				^ FFmul(0x03, t[(r + 1) % 4])
				^ FFmul(0x01, t[(r + 2) % 4])
				^ FFmul(0x01, t[(r + 3) % 4]);
		}
	}
}

void AES::AddRoundKey(unsigned char state[][4], unsigned char k[][4])
{
	int r, c;
	for (c = 0; c < 4; c++)
	{
		for (r = 0; r < 4; r++)
		{
			state[r][c] ^= k[r][c];
		}
	}
}

void AES::InvSubBytes(unsigned char state[][4])
{
	int r, c;
	for (r = 0; r < 4; r++)
	{
		for (c = 0; c < 4; c++)
		{
			state[r][c] = InvSbox[state[r][c]];
		}
	}
}

void AES::InvShiftRows(unsigned char state[][4])
{
	unsigned char t[4];
	int r, c;
	for (r = 1; r < 4; r++)
	{
		for (c = 0; c < 4; c++)
		{
			t[c] = state[r][(c - r + 4) % 4];
		}
		for (c = 0; c < 4; c++)
		{
			state[r][c] = t[c];
		}
	}
}

void AES::InvMixColumns(unsigned char state[][4])
{
	unsigned char t[4];
	int r, c;
	for (c = 0; c < 4; c++)
	{
		for (r = 0; r < 4; r++)
		{
			t[r] = state[r][c];
		}
		for (r = 0; r < 4; r++)
		{
			state[r][c] = FFmul(0x0e, t[r])
				^ FFmul(0x0b, t[(r + 1) % 4])
				^ FFmul(0x0d, t[(r + 2) % 4])
				^ FFmul(0x09, t[(r + 3) % 4]);
		}
	}
}

int AES::getUCharLen(const unsigned char *uch)
{
	int len = 0;
	while (*uch++)
		++len;

	return len;
}

int AES::ucharToHex(const unsigned char *uch, char *hex)
{
	int high, low;
	int tmp = 0;
	if (uch == NULL || hex == NULL){
		return -1;
	}

	if (getUCharLen(uch) == 0){
		return -2;
	}

	while (*uch){
		tmp = (int)*uch;
		high = tmp >> 4;
		low = tmp & 15;
		*hex++ = valueToHexCh(high); //先写高字节
		*hex++ = valueToHexCh(low); //其次写低字节
		uch++;
	}
	*hex = '\0';
	return 0;
}

int AES::hexToUChar(const char *hex, unsigned char *uch)
{
	int high, low;
	int tmp = 0;
	if (hex == NULL || uch == NULL){
		return -1;
	}

	if (strlen(hex) % 2 == 1){
		return -2;
	}

	while (*hex){
		high = ascillToValue(*hex);
		if (high < 0){
			*uch = '\0';
			return -3;
		}
		hex++; //指针移动到下一个字符上
		low = ascillToValue(*hex);
		if (low < 0){
			*uch = '\0';
			return -3;
		}
		tmp = (high << 4) + low;
		*uch++ = tmp;
		hex++;
	}
	*uch = (int)'\0';
	return 0;
}

int AES::strToUChar(const char *ch, unsigned char *uch)
{
	int tmp = 0;
	if (ch == NULL || uch == NULL)
		return -1;
	if (strlen(ch) == 0)
		return -2;

	while (*ch){
		tmp = (int)*ch;
		*uch++ = tmp;
		ch++;
	}
	*uch = (int)'\0';
	return 0;
}

int AES::ucharToStr(const unsigned char *uch, char *ch)
{
	int tmp = 0;
	if (uch == NULL || ch == NULL)
		return -1;

	while (*uch){
		tmp = (int)*uch;
		*ch++ = (char)tmp;
		uch++;
	}
	*ch = '\0';

	return 0;
}

int AES::strToHex(const char *ch, char *hex)
{
	int high, low;
	int tmp = 0;
	if (ch == NULL || hex == NULL){
		return -1;
	}

	if (strlen(ch) == 0){
		return -2;
	}

	while (*ch){
		tmp = (int)*ch;
		high = tmp >> 4;
		low = tmp & 15;
		*hex++ = valueToHexCh(high); //先写高字节
		*hex++ = valueToHexCh(low); //其次写低字节
		ch++;
	}
	*hex = '\0';
	return 0;
}

int AES::hexToStr(const char *hex, char *ch)
{
	int high, low;
	int tmp = 0;
	if (hex == NULL || ch == NULL){
		return -1;
	}

	if (strlen(hex) % 2 == 1){
		return -2;
	}

	while (*hex){
		high = ascillToValue(*hex);
		if (high < 0){
			*ch = '\0';
			return -3;
		}
		hex++; //指针移动到下一个字符上
		low = ascillToValue(*hex);
		if (low < 0){
			*ch = '\0';
			return -3;
		}
		tmp = (high << 4) + low;
		*ch++ = (char)tmp;
		hex++;
	}
	*ch = '\0';
	return 0;
}

int AES::ascillToValue(const char ch){
	int result = 0;
	//获取16进制的高字节位数据
	if (ch >= '0' && ch <= '9'){
		result = (int)(ch - '0');
	}
	else if (ch >= 'a' && ch <= 'z'){
		result = (int)(ch - 'a') + 10;
	}
	else if (ch >= 'A' && ch <= 'Z'){
		result = (int)(ch - 'A') + 10;
	}
	else{
		result = -1;
	}
	return result;
}

char AES::valueToHexCh(const int value)
{
	char result = '\0';
	if (value >= 0 && value <= 9){
		result = (char)(value + 48); //48为ascii编码的‘0’字符编码值
	}
	else if (value >= 10 && value <= 15){
		result = (char)(value - 10 + 65); //减去10则找出其在16进制的偏移量，65为ascii的'A'的字符编码值
	}
	else{
		;
	}

	return result;
}