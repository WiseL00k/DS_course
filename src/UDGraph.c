#include "UDGraph.h"
#include "LQueue.h"

Status visit(int k)
{
    printf("%d ", k);
    return OK;
}

#ifdef USE_ADJMATRIX

Status InitGraph_M(MGraph *G, GraphKind kind, VexType *vexs, int n)
{
    int i, j, info;
    if (n < 0 || (n > 0 && vexs == NULL))
        return ERROR;
    if (kind == UDG)
        info = 0;
    else if (kind == UDN)
        info = INFINITY;
    else
        return ERROR;
    G->n = n;
    G->e = 0;
    G->kind = kind;
    if (n == 0)
        return OK;
    if (NULL == (G->vexs = (VexType *)malloc(n * sizeof(VexType))))
        return OVERFLOW;
    for (i = 0; i < G->n; ++i)
        G->vexs[i] = vexs[i];
    if (NULL == (G->arcs = (int **)malloc(n * sizeof(int *))))
        return OVERFLOW;
    for (i = 0; i < n; ++i)
        if (NULL == (G->arcs[i] = (int *)malloc(n * sizeof(int))))
            return OVERFLOW;
    if (NULL == (G->tags = (int *)malloc(n * sizeof(int))))
        return OVERFLOW;
    for (i = 0; i < n; ++i)
    {
        G->tags[i] = UNVISITED;
        for (j = 0; j < n; ++j)
            G->arcs[i][j] = info;
    }
    return OK;
}

Status CreateGraph_M(MGraph *G, GraphKind kind, VexType *vexs, int n, ArcInfo *arcs, int e)
{
    if (n < 0 || e < 0 || (n > 0 && vexs == NULL) || (e > 0 && arcs == NULL))
        return ERROR;
    G->kind = kind;
    switch (G->kind)
    {
    case UDG:
        return CreateUDG_M(G, vexs, n, arcs, e); // 创建无向图
    case UDN:
        return CreateUDN_M(G, vexs, n, arcs, e); // 创建无向带权图
    default:
        return ERROR;
    }
}

Status CreateUDG_M(MGraph *G, VexType *vexs, int n, ArcInfo *arcs, int e)
{
    int i, j, k;
    VexType v, w;
    if (InitGraph_M(G, UDG, vexs, n) != OK)
        return ERROR;
    G->e = e;
    for (k = 0; k < G->e; ++k)
    {
        v = arcs[k].v;
        w = arcs[k].w;
        i = LocateVex_M(*G, v);
        j = LocateVex_M(*G, w);
        if (i < 0 || j < 0)
            return ERROR;
        G->arcs[i][j] = G->arcs[j][i] = 1;
    }
    return OK;
}

Status CreateUDN_M(MGraph *G, VexType *vexs, int n, ArcInfo *arcs, int e)
{
    int i, j, k;
    VexType v, w;
    if (InitGraph_M(G, UDN, vexs, n) != OK)
        return ERROR;
    G->e = e;
    for (k = 0; k < G->e; ++k)
    {
        v = arcs[k].v;
        w = arcs[k].w;
        i = LocateVex_M(*G, v);
        j = LocateVex_M(*G, w);
        if (i < 0 || j < 0)
            return ERROR;
        G->arcs[i][j] = G->arcs[j][i] = arcs[k].info;
    }
    return OK;
}

Status DestroyGraph_M(MGraph *G)
{
    if (G == NULL)
        return ERROR;
    free(G->vexs);
    for (int i = 0; i < G->n; ++i)
    {
        free(G->arcs[i]);
        G->arcs[i] = NULL;
    }
    free(G->arcs);
    free(G->tags);
    G->vexs = NULL;
    G->arcs = NULL;
    G->tags = NULL;
    G->n = 0;
    G->e = 0;
    return OK;
}

int LocateVex_M(MGraph G, VexType v)
{
    if (G.vexs == NULL)
        return -1;
    for (int i = 0; i < G.n; ++i)
        if (v == G.vexs[i])
            return i; // 找到顶点返回下标i
    return -1;        // 未找到顶点返回-1
}

Status GetVex_M(MGraph G, int k, VexType *w)
{
    if (k < 0 || k >= G.n)
        return -1;  // k顶点不存在
    *w = G.vexs[k]; // 将k顶点的值赋给w
    return OK;
}

Status PutVex_M(MGraph G, int k, VexType v)
{
    if (k < 0 || k >= G.n)
        return -1; // k顶点不存在
    G.vexs[k] = v; // 将v赋给k顶点
    return OK;
}

int FirstAdjVex_M(MGraph G, int k)
{
    int i;
    if (k < 0 || k >= G.n)
        return -1; // k顶点不存在
    for (i = 0; i < G.n; ++i)
        if (G.kind == UDG && G.arcs[k][i] != 0)
            return i;
        else if (G.kind == UDN && G.arcs[k][i] != INFINITY)
            return i;
    return -1; // k顶点无邻接顶点
}

int NextAdjVex_M(MGraph G, int k, int m)
{
    int i;
    if (k < 0 || k >= G.n || m < 0 || m >= G.n)
        return -1; // k顶点或m顶点不存在
    for (i = m + 1; i < G.n; ++i)
    {
        if (G.kind == UDG && G.arcs[k][i] != 0)
            return i;
        else if (G.kind == UDN && G.arcs[k][i] != INFINITY)
            return i;
    }
    return -1; // k顶点无邻接顶点
}

Status AddArc_M(MGraph *G, int k, int m, int info)
{
    if (k < 0 || k >= G->n || m < 0 || m >= G->n)
        return ERROR;                                    // k顶点或m顶点不存在
    if (G->arcs[k][m] == 0 || G->arcs[k][m] == INFINITY) // 判断k和m之间是否存在弧
        return ERROR;
    if (G->kind == UDG) // 无向图
    {
        G->arcs[k][m] = G->arcs[m][k] = 1;
    }
    else if (G->kind == UDN) // 无向网
    {
        G->arcs[k][m] = G->arcs[m][k] = info;
    }
    G->e++; // 边数加1
    return OK;
}

Status RemoveArc_M(MGraph *G, int k, int m)
{
    if (k < 0 || k >= G->n || m < 0 || m >= G->n)
        return ERROR;                                     // k顶点或m顶点不存在
    if (G->kind == UDG && G->arcs[k][m] && G->arcs[m][k]) // 无向图
    {
        G->arcs[k][m] = G->arcs[m][k] = 0; // 删除k顶点与m顶点之间的边或弧
        G->e--;                            // 边数减1
    }
    else
    {
        return ERROR; // 无向网
    }
    return OK;
}

Status DFS_M(MGraph G, int k, Status (*visit)(int))
{
    int i;
    if (ERROR == visit(k)) // 访问k顶点
        return ERROR;
    G.tags[k] = VISITED;
    for (i = FirstAdjVex_M(G, k); i >= 0; i = NextAdjVex_M(G, k, i))
        if (G.tags[i] == UNVISITED) // 位序为i的邻接顶点未被访问过
            DFS_M(G, i, visit);     // 对i顶点递归深度搜索
    return OK;
}

Status DFSTraverse_M(MGraph G, Status (*visit)(int))
{
    int i;
    for (i = 0; i < G.n; ++i)
        G.tags[i] = UNVISITED; // 初始化标志数组
    for (i = 0; i < G.n; ++i)
        if (G.tags[i] == UNVISITED) // 若i顶点未访问,则以其为起点进行深度优先遍历
            if (ERROR == DFS_M(G, i, visit))
                return ERROR;
    return OK;
}

Status BFSTraverse_M(MGraph G, Status (*visit)(int))
{
    int i, j, k;
    LQueue Q;
    InitQueue_LQ(&Q);
    for (i = 0; i < G.n; ++i)
        G.tags[i] = UNVISITED; // 初始化标志数组
    for (i = 0; i < G.n; ++i)
    {
        if (G.tags[i] == UNVISITED)
        {
            if (ERROR == visit(i))
                return ERROR;
            G.tags[i] = VISITED;
            EnQueue_LQ(&Q, i);
            while (DeQueue_LQ(&Q, &k) == OK)
            {
                for (j = FirstAdjVex_M(G, k); j >= 0; j = NextAdjVex_M(G, k, j))
                {
                    if (G.tags[j] == UNVISITED)
                    {
                        if (ERROR == visit(j))
                            return ERROR;
                        G.tags[j] = VISITED;
                        EnQueue_LQ(&Q, j);
                    }
                }
            }
        }
    }
    return OK;
}

Status PrintGraph_M(MGraph H)
{
    printf("该邻接矩阵图的信息如下\n");
    printf("顶点数:%d,边数:%d\n", H.n, H.e);
    printf("邻接矩阵如下\n");
    printf("顶点数组 关 系 数 组\n");
    printf("行\\列->\t ");
    for (int i = 0; i < H.n; i++)
    {
        printf("%d\t", i);
    }
    printf("\n");
    for (int i = 0; i < H.n; i++)
    {
        printf("%d %c\t ", i, H.vexs[i]);
        for (int j = 0; j < H.n; j++)
        {
            if (H.arcs[i][j] == INFINITY)
                printf("∞\t");
            else
                printf("%d\t", H.arcs[i][j]);
        }
        printf("\n");
    }
    return OK;
}

Status SetArc_M(MGraph *G, VexType v, VexType w, int info)
{
    if (v == w && G->kind == UDG)
        return ERROR;
    int k = LocateVex_M(*G, v);
    int m = LocateVex_M(*G, w);
    if (k < 0 || k >= G->n || m < 0 || m >= G->n)
        return ERROR; // k顶点或m顶点不存在
    if (G->kind == UDG)
        G->arcs[k][m] = G->arcs[m][k] = 1;
    else if (G->kind == UDN)
        G->arcs[k][m] = G->arcs[m][k] = info;
    else
        G->arcs[k][m] = info;
    return OK;
}

#endif

#ifdef USE_ADJLIST

Status CreateGraph_AL(ALGraph *G, GraphKind kind, VexType *vexs, int n, ArcInfo *arcs, int e)
{
    if (n < 0 || e < 0 || (n > 0 && vexs == NULL) || (e > 0 && arcs == NULL))
        return ERROR;
    G->kind = kind;
    switch (G->kind)
    {
    case UDG:
        return CreateUDG_AL(G, vexs, n, arcs, e); // 创建无向图
    default:
        return ERROR;
    }
}

Status CreateUDG_AL(ALGraph *G, VexType *vexs, int n, ArcInfo *arcs, int e)
{
    int i, j, k;
    VexType v, w;
    AdjVexNodeP p;
    G->n = n;
    G->e = e;
    G->vexs = (VexNode *)malloc(sizeof(VexNode) * n);
    G->tags = (int *)malloc(sizeof(int) * n);
    if (G->vexs == NULL || G->tags == NULL) // 内存分配失败
        return ERROR;
    for (i = 0; i < n; ++i)
    {
        G->vexs[i].data = vexs[i];
        G->vexs[i].firstArc = NULL;
        G->tags[i] = UNVISITED;
    }
    for (k = 0; k < G->e; ++k)
    {
        v = arcs[k].v;
        w = arcs[k].w;
        if (v == w) // 无向图无自环
            continue;
        i = LocateVex_AL(*G, v);
        j = LocateVex_AL(*G, w);
        if (i < 0 || j < 0) // v或w顶点不存在
            return ERROR;

        p = (AdjVexNodeP)malloc(sizeof(AdjVexNode));
        if (p == NULL)
            return ERROR;
        p->info = 1;
        p->adjvex = j;
        p->nextArc = G->vexs[i].firstArc;
        G->vexs[i].firstArc = p;

        p = (AdjVexNodeP)malloc(sizeof(AdjVexNode));
        if (p == NULL)
            return ERROR;
        p->info = 1;
        p->adjvex = i;
        p->nextArc = G->vexs[j].firstArc;
        G->vexs[j].firstArc = p;
    }
    return OK;
}

Status DestroyGraph_AL(ALGraph *G)
{
    if (G == NULL)
        return ERROR;
    free(G->vexs);
    free(G->tags);
    G->vexs = NULL;
    G->tags = NULL;
    G->n = 0;
    G->e = 0;
    return OK;
}

int LocateVex_AL(ALGraph G, VexType v)
{
    if (G.vexs == NULL)
        return -1;
    for (int i = 0; i < G.n; ++i)
        if (G.vexs[i].data == v)
            return i;
    return -1;
}

Status GetVex_AL(ALGraph G, int k, VexType *w)
{
    if (k < 0 || k >= G.n)
        return ERROR;
    *w = G.vexs[k].data;
    return OK;
}

Status PutVex_AL(ALGraph G, int k, VexType w)
{
    if (k < 0 || k >= G.n)
        return ERROR;
    G.vexs[k].data = w;
    return OK;
}

int FirstAdjVex_AL(ALGraph G, int k, AdjVexNodeP *p)
{
    if (k < 0 || k >= G.n)
        return -1;
    *p = G.vexs[k].firstArc;
    if (*p != NULL)
        return (*p)->adjvex;
    else
        return -1;
}

int NextAdjVex_AL(ALGraph G, int k, AdjVexNodeP *p)
{
    if (k < 0 || k >= G.n)
        return -1;
    if (*p == NULL)
        return -1;
    *p = (*p)->nextArc;
    if (*p != NULL)
        return (*p)->adjvex;
    else
        return -1;
}

Status AddArc_AL(ALGraph *G, int k, int m, int info)
{
    AdjVexNodeP p;
    if (k < 0 || k >= G->n || m < 0 || m >= G->n) // k顶点或m顶点不存在
        return ERROR;
    p = G->vexs[k].firstArc;
    while (p != NULL) // 判断弧是否已存在
    {
        if (m == p->adjvex) // 弧已存在
            return ERROR;
        p = p->nextArc;
    }
    p = (AdjVexNodeP)malloc(sizeof(AdjVexNode));
    if (p == NULL)
        return OVERFLOW;
    p->info = G->kind == UDN ? info : 1;
    p->adjvex = m;
    p->nextArc = G->vexs[k].firstArc;
    G->vexs[k].firstArc = p;
    if (UDG == G->kind || UDN == G->kind)
    {
        p = (AdjVexNodeP)malloc(sizeof(AdjVexNode));
        if (p == NULL)
            return OVERFLOW;
        p->info = G->kind == UDN ? info : 1;
        p->adjvex = k;
        p->nextArc = G->vexs[m].firstArc;
        G->vexs[m].firstArc = p;
    }
    G->e++;
    return OK;
}

Status RemoveArc_AL(ALGraph *G, int k, int m)
{
    AdjVexNodeP p, q;
    Status removeFlag = ERROR;
    if (k < 0 || k >= G->n || m < 0 || m >= G->n) // k顶点或m顶点不存在
        return ERROR;
    p = G->vexs[k].firstArc;
    q = NULL;
    while (p != NULL) // 判断弧是否已存在
    {
        if (m == p->adjvex) // 找到目标弧并删除
        {
            if (q == NULL)
                G->vexs[k].firstArc = p->nextArc;
            else
                q->nextArc = p->nextArc;
            free(p);
            G->e--; // 边数减1
            removeFlag = OK;
            break;
        }
        q = p;
        p = p->nextArc;
    }
    if (UDG == G->kind || UDN == G->kind)
    {
        p = G->vexs[m].firstArc;
        q = NULL;
        while (p != NULL)
        {
            if (k == p->adjvex)
            {
                if (q == NULL)
                    G->vexs[m].firstArc = p->nextArc;
                else
                    q->nextArc = p->nextArc;
                free(p);
            }
            q = p;
            p = p->nextArc;
        }
    }
    return removeFlag;
}

Status DFS_AL(ALGraph G, int k, Status (*visit)(int))
{
    int i;
    AdjVexNodeP p;
    G.tags[k] = VISITED;
    if (ERROR == visit(k))
        return ERROR;
    for (i = FirstAdjVex_AL(G, k, &p); i >= 0; i = NextAdjVex_AL(G, k, &p))
    {
        if (UNVISITED == G.tags[i])
            if (ERROR == DFS_AL(G, i, visit))
                return ERROR;
    }
    return OK;
}

Status DFSTraverse_AL(ALGraph G, Status (*visit)(int))
{
    int i;
    for (i = 0; i < G.n; ++i)
        G.tags[i] = UNVISITED; // 初始化标志数组
    for (i = 0; i < G.n; ++i)
        if (UNVISITED == G.tags[i])
            if (ERROR == DFS_AL(G, i, visit))
                return ERROR;
    return OK;
}

Status BFSTraverse_AL(ALGraph G, Status (*visit)(int))
{
    int i, j, k;
    AdjVexNodeP p;
    LQueue Q;
    InitQueue_LQ(&Q);
    for (i = 0; i < G.n; ++i)
        G.tags[i] = UNVISITED; // 初始化标志数组
    for (i = 0; i < G.n; ++i)
        if (UNVISITED == G.tags[i])
        {
            if (ERROR == visit(i))
                return ERROR;
            G.tags[i] = VISITED;             // 设置标志为已访问
            EnQueue_LQ(&Q, i);               // 访问第一个邻接点
            while (OK == DeQueue_LQ(&Q, &k)) // 若队列非空，则继续访问其邻接点
            {
                for (j = FirstAdjVex_AL(G, k, &p); j >= 0; j = NextAdjVex_AL(G, k, &p))
                    if (UNVISITED == G.tags[j])
                    {
                        if (ERROR == visit(j))
                            return ERROR;
                        G.tags[j] = VISITED;
                        EnQueue_LQ(&Q, j);
                    }
            }
        }
    return OK;
}

Status printALGraph(ALGraph H)
{
    printf("该邻接表图的信息如下\n");
    printf("顶点数:%d,边数:%d\n", H.n, H.e);
    printf("邻接表如下\n");
    for (int k = 0; k < H.n; k++)
    {
        printf("%d: %c->", k, H.vexs[k].data);
        AdjVexNodeP p = H.vexs[k].firstArc;
        for (; p != NULL; p = p->nextArc)
        {
            int j = p->adjvex;
            printf("%d(%c) ", j, H.vexs[j].data);
        }
        printf("\n");
    }
    return OK;
}

Status SetArc_AL(ALGraph *G, VexType v, VexType w, int info)
{
    if (v == w && G->kind == UDG)
        return ERROR;
    int k = LocateVex_AL(*G, v);
    int m = LocateVex_AL(*G, w);
    if (k < 0 || k >= G->n || m < 0 || m >= G->n)
        return ERROR; // k顶点或m顶点不存在
    AdjVexNodeP p = G->vexs[k].firstArc;
    while (p != NULL && p->adjvex != k)
        p = p->nextArc;
    if (G->kind == UDG)
    {
        p->info = 1;
        p = G->vexs[m].firstArc;
        while (p != NULL && p->adjvex != m)
            p = p->nextArc;
        p->info = 1; // 无向图是双向的，设置反向边信息为1
    }
    else if (G->kind == UDN)
    {
        p->info = info;
        p = G->vexs[m].firstArc;
        while (p != NULL && p->adjvex != m)
            p = p->nextArc;
        p->info = info; // 无向图是双向的，设置反向边信息为1
    }
    else
        p->info = info;
    return OK;
}

#endif