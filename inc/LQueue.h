#ifndef __LQUEUE_H__
#define __LQUEUE_H__

#include <stdio.h>
#include <stdlib.h>
#include "Status.h" // 状态码定义

// 队列元素类型
typedef int ElemType;

// 链队列结点类型
typedef struct LQNode
{
    ElemType data;
    struct LQNode *next;
} LQNode, *QueuePtr;

typedef struct
{
    QueuePtr front; // 队头指针
    QueuePtr rear;  // 队尾指针
} LQueue;           // 链队列

void InitQueue_LQ(LQueue *Q);              // 构造一个空队列
void DestroyQueue_LQ(LQueue *Q);           // 销毁队列Q
Status QueueEmpty_LQ(LQueue Q);            // 判断队列Q是否为空
int QueueLength_LQ(LQueue Q);              // 求队列Q的长度
Status GetHead_LQ(LQueue Q, ElemType *e);  // 若队列不空,则用e返回队头元素,并返回OK;否则返回ERROR
Status EnQueue_LQ(LQueue *Q, ElemType e);  // 入队
Status DeQueue_LQ(LQueue *Q, ElemType *e); // 出队

#endif /* __LQUEUE_H__ */