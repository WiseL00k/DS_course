#include "Heap.h"

// 大顶堆优先函数
int greatPrior(int x, int y)
{
    return x >= y;
}

// 小顶堆优先函数
int lessPrior(int x, int y)
{
    return x <= y;
}

// prior为相应的优先函数
// 初建最大容量为size的空堆H,当tag为0或1时分别表示小顶堆和大顶堆
Status InitHeap(Heap *H, int size, int tag, int (*prior)(KeyType, KeyType))
{
    H->n = 0;
    H->size = size;
    H->tag = tag;

    H->rcd = (RcdType *)malloc(sizeof(RcdType) * (H->size + 1));
    if (NULL == H->rcd)
        return OVERFLOW;

    H->prior = prior;

    return OK;
}

// 用E建长度为n的堆H,容量为size,当tag为0或1时分别表示小顶堆和大顶堆
void MakeHeap(Heap *H, RcdType *E, int n, int size, int tag, int (*prior)(KeyType, KeyType))
{
    // 用E建立长度为n的堆H，容量为size。当tag为0或1时分别表示小顶堆和大顶堆，prior为相应的优先函数
    // H->rcd = E; // E[1..n]是堆的n个结点，0号单元空闲
    H->n = n;
    H->size = size;
    H->tag = tag;

    if (NULL == H->rcd)
        H->rcd = (RcdType *)malloc(sizeof(RcdType) * (H->size + 1));

    for (int i = 1; i <= size; i++)
    {
        H->rcd[i].key = E[i].key;
    }

    H->prior = prior;
    for (int i = n / 2; i > 0; i--)
        ShiftDown(H, i); // 对以i结点为根的子树进行筛选
}

// 销毁堆H
Status DestroyHeap(Heap *H)
{
    if (!H)
        return ERROR;
    if (NULL != H->rcd)
        free(H->rcd);
    H->rcd = NULL;
    H->n = H->size = 0;
    return OK;
}

Status swapHeapElem(Heap *H, int i, int j)
{
    // 交换堆H中的第i结点和第j结点
    RcdType t;
    if (i <= 0 || i > H->n || j <= 0 || j > H->n)
        return ERROR;
    t = H->rcd[i];
    H->rcd[i] = H->rcd[j];
    H->rcd[j] = t;
    return OK;
}

// 对堆H中位置为pos的结点做筛选,将以pos为根的子树调整为子堆
void ShiftDown(Heap *H, int pos)
{
    int c, rc;
    while (pos <= H->n / 2)
    {
        c = pos * 2;
        rc = pos * 2 + 1;
        if (rc <= H->n && H->prior(H->rcd[rc].key, H->rcd[c].key))
            c = rc; // c为pos结点的左、右孩子中较优先者的位置
        if (H->prior(H->rcd[pos].key, H->rcd[c].key))
            return;
        swapHeapElem(H, pos, c);
        pos = c;
    }
}

// 将e插入堆
Status InsertHeap(Heap *H, RcdType e)
{
    int curr;
    if (H->n >= H->size - 1)
        return ERROR; // 堆已满,插入失败
    curr = ++H->n;
    H->rcd[curr] = e; // 将插入元素加到堆尾
    while (1 != curr && H->prior(H->rcd[curr].key, H->rcd[curr / 2].key))
    {
        swapHeapElem(H, curr, curr / 2);
        curr /= 2;
    }
    return OK;
}

// 删除堆H的堆顶结点,并用e将其返回
Status RemoveFirstHeap(Heap *H, RcdType *e)
{
    if (H->n <= 0)
        return ERROR;
    *e = H->rcd[1];             // 取出堆顶结点
    swapHeapElem(H, 1, H->n--); // 交换堆顶与堆尾结点,堆长度减1
    if (H->n > 1)
        ShiftDown(H, 1); // 从堆顶位置向下筛选
    return OK;
}

void ShiftUp(Heap *H, int pos)
{
    while (1 != pos && H->prior(H->rcd[pos].key, H->rcd[pos / 2].key))
    {
        swapHeapElem(H, pos, pos / 2);
        pos /= 2;
    }
}

// 删除位置pos的结点,用e返回其值
Status RemoveHeap(Heap *H, int pos, RcdType *e)
{
    if (H->n <= 0)
        return ERROR;
    *e = H->rcd[pos];
    if (pos == H->n)
    {
        H->n--;
        return OK;
    }
    // pos的结点值优先于替换值,向下筛选
    if (H->prior(H->rcd[pos].key, H->rcd[H->n].key))
    {
        swapHeapElem(H, pos, H->n--);
        ShiftDown(H, pos);
    }
    else
    {
        swapHeapElem(H, pos, H->n--);
        ShiftUp(H, pos);
    }
    return OK;
}