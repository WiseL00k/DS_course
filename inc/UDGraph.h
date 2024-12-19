#ifndef __UDGRAPH_H__
#define __UDGRAPH_H__

#include <stdio.h>
#include <stdlib.h>
#include "Status.h" // 状态码定义


// 选择图存储方式，选择一种即可 邻接矩阵 ADJMATRIX 或者 邻接表 ADJLIST
// 这里因为需要根据边数和点数选择最优存储方式，所以两种都选择了
#define USE_ADJLIST 
#define USE_ADJMATRIX

#define UNVISITED 0
#define VISITED 1
#define INFINITY MAXINT
#define MAXINT 0x0FFFFFFF

typedef char VexType;
typedef struct
{
    VexType v, w;
    int info;
} ArcInfo;

// 暂未实现有向图相关API接口,只支持无向图
typedef enum
{
    DG,
    DN,
    UDG, // 无向图
    UDN  // 无向带权图
} GraphKind;

Status visit(int k); // 访问顶点k

#ifdef USE_ADJMATRIX
typedef struct
{
    VexType *vexs;
    int **arcs;
    int n, e;
    GraphKind kind;
    int *tags;
} MGraph; // 邻接数组类型

// 初始化含n个顶点且无边的kind类的图G
Status InitGraph_M(MGraph *G, GraphKind kind, VexType *vexs, int n);
// 创建n个顶点和e条边的kind类的图G,vexs为顶点信息,arcs为边(弧)信息
Status CreateGraph_M(MGraph *G, GraphKind kind, VexType *vexs, int n, ArcInfo *arcs, int e);
// 创建无向图G
Status CreateUDG_M(MGraph *G, VexType *vexs, int n, ArcInfo *arcs, int e);
// 创建无向带权图G
Status CreateUDN_M(MGraph *G, VexType *vexs, int n, ArcInfo *arcs, int e);
// 销毁图G
Status DestroyGraph_M(MGraph *G);
// 查找顶点v在图G中的位序
int LocateVex_M(MGraph G, VexType v);
// 取图G的k顶点的值到w
Status GetVex_M(MGraph G, int k, VexType *w);
// 对图G的k顶点赋值w
Status PutVex_M(MGraph G, int k, VexType w);
// 求图G中k顶点的第一个邻接顶点的位序,若不存在则返回-1
int FirstAdjVex_M(MGraph G, int k);
// m顶点为k顶点的邻接顶点,求图G中k顶点相对于m顶点的下一个邻接顶点的位序
int NextAdjVex_M(MGraph G, int k, int m);
// 在图G中增加k顶点到m顶点的边或弧,若为带权图,info为权值,否则为1
Status AddArc_M(MGraph *G, int k, int m, int info);
// 在图G中删除k顶点到m顶点的边或弧
Status RemoveArc_M(MGraph *G, int k, int m);
// 深度优先搜索图G中从顶点k开始访问
Status DFS_M(MGraph G, int k, Status (*visit)(int));
// 深度优先遍历图G
Status DFSTraverse_M(MGraph G, Status (*visit)(int));
// 广度优先遍历图G
Status BFSTraverse_M(MGraph G, Status (*visit)(int));
// 打印邻接矩阵图
Status PrintGraph_M(MGraph H);
// 在图G中设置顶点v到顶点w的弧或边
Status SetArc_M(MGraph *G, VexType v, VexType w, int info);

#endif

#ifdef USE_ADJLIST

typedef struct AdjVexNode
{
    int adjvex;
    struct AdjVexNode *nextArc;
    int info;
} AdjVexNode, *AdjVexNodeP;
typedef struct VexNode
{
    VexType data;
    struct AdjVexNode *firstArc;
} VexNode;
typedef struct
{
    VexNode *vexs;
    int n, e;
    GraphKind kind;
    int *tags;
} ALGraph; // 邻接表类型

// 创建n个顶点和e条边的kind类的图G,vexs为顶点信息,arcs为边(弧)信息
Status CreateGraph_AL(ALGraph *G, GraphKind kind, VexType *vexs, int n, ArcInfo *arcs, int e);
// 创建无向图G
Status CreateUDG_AL(ALGraph *G, VexType *vexs, int n, ArcInfo *arcs, int e);
// 创建无向带权图G
Status CreateUDN_AL(ALGraph *G, VexType *vexs, int n, ArcInfo *arcs, int e);
// 销毁图G
Status DestroyGraph_AL(ALGraph *G);
// 查找顶点v在图G中的位序
Status LocateVex_AL(ALGraph G, VexType v);
// 取图G的k顶点的值到w
Status GetVex_AL(ALGraph G, int k, VexType *w);
// 对图G的k顶点赋值w
Status PutVex_AL(ALGraph G, int k, VexType w);
// 求图G中k顶点的第一个邻接顶点的位序,并使p指向求得顶点,若不存在则返回-1
int FirstAdjVex_AL(ALGraph G, int k, AdjVexNodeP *p);
// 在图G中k顶点的邻接链表，令p指向p的下一个顶点,若不存在则返回-1
int NextAdjVex_AL(ALGraph G, int k, AdjVexNodeP *p);
// 在图G中增加k顶点到m顶点的边或弧,若为带权图,info为权值,否则为1
Status AddArc_AL(ALGraph *G, int k, int m, int info);
// 在图G中删除k顶点到m顶点的边或弧
Status RemoveArc_AL(ALGraph *G, int k, int m);
// 深度优先搜索图G,从顶点k开始访问
Status DFS_AL(ALGraph G, int k, Status (*visit)(int));
// 深度优先遍k历图G
Status DFSTraverse_AL(ALGraph G, Status (*visit)(int));
// 广度优先遍历图G
Status BFSTraverse_AL(ALGraph G, Status (*visit)(int));
// 打印邻接表图
Status PrintGraph_AL(ALGraph H);
// 在图G中设置顶点v到顶点w的弧或边
Status SetArc_AL(ALGraph *G, VexType v, VexType w, int info);

#endif

#endif /* __UDGRAPH_H__ */