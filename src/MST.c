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
    if (T->e == G.n - 1)
        return OK;
    return ERROR;
}

Status Kruskal(ALGraph G, ALGraph *T)
{
    // 用克鲁斯卡尔算法构造图G的最小生成树T,图G和T采用邻接表存储结构
    int i, j, v, w;
    MFSet S;
    Heap H;
    RcdType temp, *arcs;
    AdjVexNodeP p;
    // 初始化T
    T->n = G.n;
    T->e = 0;
    T->kind = G.kind;
    T->vexs = (VexNode *)malloc(G.n * sizeof(VexNode));
    T->tags = (int *)malloc(G.n * sizeof(int));
    for (i = 0; i < G.n; i++)
    {
        T->vexs[i].data = G.vexs[i].data;
        T->vexs[i].firstArc = NULL;
        T->tags = UNVISITED;
    }
    InitMFSet(&S, G.n); // 初始化顶点并查集S,每个顶点自成一个子集
    arcs = (RcdType *)malloc((G.e + 1) * sizeof(RcdType));
    j = 1;
    for (i = 0; i < G.n; i++)
    {
        for (p = G.vexs[i].firstArc; p != NULL; p = p->nextArc)
        {
            if (i < p->adjvex)
            {
                arcs[j].v = i;
                arcs[j].w = p->adjvex;
                arcs[j].key = p->info;
                j++;
            }
        }
    }
    MakeHeap(&H, arcs, G.e, G.e + 1, 0, lessPrior); // 建立含所有边的最小堆H
    for (i = 0; i < G.e; i++)
    {
        RemoveFirstHeap(&H, &temp); // 从小顶堆H移除堆顶值,作为当前权值最小的边
        v = temp.v;
        w = temp.w;
        if (TRUE == UnionMFSet(&S, v, w)) // 如果v和w不在同一个子集中,则合并
        {
            AddArc_AL(T, v, w, temp.key); // 加入边(v,w),不会形成回路
            if (T->e == G.n - 1)
                break;
        }
    }
    free(arcs);
    if (T->e == G.n - 1)
        return OK;
    return ERROR;
}