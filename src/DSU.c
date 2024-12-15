#include "DSU.h"

Status InitMFSet(MFSet *S, int n)
{
    int i;
    S->parent = (int *)malloc(sizeof(int) * n);
    S->n = n;
    if (S->parent == NULL)
        return OVERFLOW;
    for (i = 0; i < n; ++i)
        S->parent[i] = -1;
    return OK;
}

Status DestroyMFSet(MFSet *S)
{
    if (S == NULL)
        return ERROR;
    free(S->parent);
    return OK;
}

int FindMFset_Default(MFSet *S, int i)
{
    // 查找元素i在并查集S中所属的子集，返回集合代表
    if (i < 0 || i >= S->n)
        return ERROR; // 表示不存在元素i
    while (S->parent[i] >= 0)
        i = S->parent[i];
    return i;
}

Status DiffMFSet(MFSet *S, int i, int j)
{
    // 判断元素i和j是否属于同一个集合
    return FindMFSet(S, i) == FindMFSet(S, j);
}

Status UnionMFSet_Default(MFSet *S, int i, int j)
{
    // 合并并查集S中元素i和j所属的两个集合
    if (i < 0 || i >= S->n || j < 0 || j >= S->n)
        return ERROR; // 表示不存在元素i或j

    // 查找i和j所在子树的根结点
    int ri = FindMFSet(S, i);
    int rj = FindMFSet(S, j);

    if (ri == rj)
        return ERROR;

    S->parent[ri] = rj; // 将根结点ri的双亲结点值置为rj

    return OK;
}

Status UnionMFSet_WUR(MFSet *S, int i, int j)
{
    if (i < 0 || i >= S->n || j < 0 || j >= S->n)
        return ERROR; // 表示不存在元素i或j

    // 查找i和j所在子树的根结点
    int ri = FindMFSet(S, i);
    int rj = FindMFSet(S, j);
    if (ri == rj)
        return ERROR;
    if (S->parent[ri] > S->parent[rj]) // 因为是负数，所以rj是较矮的树
    {
        S->parent[rj] += S->parent[ri];
        S->parent[ri] = rj;
    }
    else
    {
        S->parent[ri] += S->parent[rj];
        S->parent[rj] = ri;
    }

    return OK;
}

Status UnionMFSet_PC(MFSet *S, int i, int j)
{
    // 合并并查集S中元素i和j所属的两个集合，同时压缩路径
    if (i < 0 || i >= S->n || j < 0 || j >= S->n)
        return ERROR; // 表示不存在元素i或j

    // 查找i和j所在子树的根结点
    int ri = FindPCMFSet_PC_ite(S, i);
    int rj = FindPCMFSet_PC_ite(S, j);
    if (ri == rj)
        return ERROR;

    S->parent[ri] = rj; // 将根结点ri的双亲结点值置为rj

    return OK;
}

int FindPCMFSet_PC_ite(MFSet *S, int i)
{
    if (i < 0 || i >= S->n)
        return ERROR;
    int parent = i, temp = i;
    while (S->parent[parent] >= 0)
        parent = S->parent[parent];
    while (S->parent[i] >= 0 && i >= 0)
    {
        temp = S->parent[i];
        S->parent[i] = parent;
        i = temp;
    }
    return parent;
}

Status hasRelation(MFSet *S, int i, int j)
{
    if (i < 0 || i >= S->n || j < 0 || j >= S->n)
        return FALSE;
    if (FindMFSet(S, i) == FindMFSet(S, j))
        return TRUE;
    else
        return FALSE;
}

Status displayMFSet(MFSet *S)
{
    if (S == NULL || S->parent == NULL)
        return ERROR;

    printf("index:\t");
    for (int i = 0; i < S->n; ++i)
    {
        printf("%d\t", i);
    }
    printf("\n");
    printf("value:\t");
    for (int i = 0; i < S->n; ++i)
    {
        printf("%d\t", S->parent[i]);
    }
    printf("\n");
    return OK;
}