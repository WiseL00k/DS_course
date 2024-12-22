#ifndef __HEAP_H__
#define __HEAP_H__

#include <stdlib.h>
#include "Status.h"

// 堆的关键字类型
typedef int KeyType;

// 堆中结点的存储结构
typedef struct
{
    int v, w;
    KeyType key; // 边的权值
} RcdType;

// 堆类型
typedef struct
{
    RcdType *rcd;
    int n;
    int size;
    int tag;
    int (*prior)(KeyType, KeyType);
} Heap;

// 大顶堆优先函数
int greatPrior(int x, int y);
// 小顶堆优先函数
int lessPrior(int x, int y);
// prior为相应的优先函数
// 初建最大容量为size的空堆H,当tag为0或1时分别表示小顶堆和大顶堆
Status InitHeap(Heap *H, int size, int tag, int (*prior)(KeyType, KeyType));
// 用E建长度为n的堆H,容量为size,当tag为0或1时分别表示小顶堆和大顶堆
void MakeHeap(Heap *H, RcdType *E, int n, int size, int tag, int (*prior)(KeyType, KeyType));
// 销毁堆H
Status DestroyHeap(Heap *H);
// 对堆H中位置为pos的结点做筛选,将以pos为根的子树调整为子堆
void ShiftDown(Heap *H, int pos);
// 将e插入堆
Status InsertHeap(Heap *H, RcdType e);
// 删除堆H的堆顶结点,并用e将其返回
Status RemoveFirstHeap(Heap *H, RcdType *e);
// 删除位置pos的结点,用e返回其值
Status RemoveHeap(Heap *H, int pos, RcdType *e);

#endif // __HEAP_H__