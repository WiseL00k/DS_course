#ifndef __MST_H__
#define __MST_H__

#include "UDGraph.h"
#include "Status.h"
#include "Heap.h"
#include "DSU.h"

// 最小边信息
typedef struct
{
    int adjInd;
    int lowcost;
} ClosedgeInfo;

// 生成最小生成树
Status generateMST();
Status Prim(MGraph G, int i, MGraph *T);
Status Kruskal(ALGraph G, ALGraph *T);
// 输出Prim算法得出的建设方案
void outPutResult_M(MGraph T);
// 输出Kruskal算法得出的建设方案
void outPutResult_AL(ALGraph T);

#endif // __MST_H__