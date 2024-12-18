#ifndef __MST_H__
#define __MST_H__

#include "UDGraph.h"
#include "Status.h"

// 生成最小生成树
Status generateMST(); 
Status Prim(MGraph G, int i, MGraph* T);
Status Kruskal(ALGraph G, ALGraph* T);

#endif // __MST_H__