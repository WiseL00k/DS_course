#include "MST.h"

#define SELECTED 1
#define UNSELECTED 0

typedef struct
{
    int adjInd;
    int lowcost;
} ClosedgeInfo;

// 用普里姆算法从i顶点出发构造图G的最小生成树T，图G和T采用邻接数组存储结构
Status Prim(MGraph G, int i, MGraph *T)
{
    int j, min, k, m = 0;
    ClosedgeInfo *closedge;
    closedge = (ClosedgeInfo *)malloc(G.n * sizeof(ClosedgeInfo));
    InitGraph_M(T, G.kind, G.vexs, G.n); // 初始化含n个顶点且无边的图T
    for (j = 0; j < G.n; j++)
    {
        G.tags[j] = UNSELECTED;
        if (j != i)
        {
            closedge[j].adjInd = i;
            closedge[j].lowcost = G.arcs[i][j];
        }
    }
    closedge[i].lowcost = 0;
    T->tags[i] = SELECTED;
    T->e = 0;
    for (m = 1; m < G.n; m++)
    {
        min = INFINITY;
        k = 0;
        for (j = 0; j < G.n; j++)
        {
            if (closedge[j].lowcost > 0 && closedge[j].lowcost < min)
            {
                k = j;
                min = closedge[j].lowcost;
            }
        }
        if (INFINITY == min)
            break;
        T->tags[k] = SELECTED;
        // 在T中新增边(k,closedge[k].adjInd)
        T->arcs[k][closedge[k].adjInd] = T->arcs[closedge[k].adjInd][k] = closedge[k].lowcost;
        T->e++;
        closedge[k].lowcost = 0; // 将k顶点加入到集合U中
        for (j = 0; j < G.n; j++)
            if (closedge[j].lowcost != 0 && G.arcs[k][j] < closedge[j].lowcost)
            {
                closedge[j].adjInd = k;
                closedge[j].lowcost = G.arcs[k][j];
            }
    }
    free(closedge);
    if(T->e == G.n-1)
        return OK;
    return ERROR;
}

Status Kruskal(ALGraph G, ALGraph *T)
{
}