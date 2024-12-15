#include "LQueue.h"

void InitQueue_LQ(LQueue *Q)
{
    if (Q == NULL)
        return;
    Q->front = Q->rear = NULL; // 初始化队头和队尾指针
}

void DestroyQueue_LQ(LQueue *Q)
{
    if (Q == NULL)
        return;
    QueuePtr p = NULL;
    while (Q->front != NULL)
    {
        p = Q->front;
        Q->front = Q->front->next;
        free(p);
        p = NULL;
    }
    Q->front = Q->rear = NULL; // 销毁队列
}

Status QueueEmpty_LQ(LQueue Q)
{
    if (Q.front == NULL)
        return TRUE;
    else
        return FALSE;
}

int QueueLength_LQ(LQueue Q)
{
    int length = 0;
    QueuePtr p = Q.front;
    while (p != NULL)
    {
        length++;
        p = p->next;
    }
    return length;
}

Status GetHead_LQ(LQueue Q, ElemType *e)
{
    if (Q.front == NULL)
        return ERROR;
    *e = Q.front->data; // 队头元素赋给e
    return OK;          // 返回队头元素
}

Status EnQueue_LQ(LQueue *Q, ElemType e)
{
    if (Q == NULL)
        return ERROR;
    LQNode *p = (QueuePtr)malloc(sizeof(LQNode)); // 创建新结点
    if (p == NULL)
        return OVERFLOW;
    p->data = e; // 将新结点数据域赋值
    p->next = NULL;
    if (Q->front == NULL)
        Q->front = p; // 如果队列为空，修改队头指针
    else
        Q->rear->next = p; // 将新结点插入队尾
    Q->rear = p;           // 修改队尾指针
    return OK;             // 入队成功
}

Status DeQueue_LQ(LQueue *Q, ElemType *e)
{
    if (Q == NULL)
        return ERROR;
    if (Q->front == NULL)
        return ERROR;
    LQNode *p = Q->front;      // 保存队头结点
    *e = p->data;              // 队头元素赋给e
    Q->front = Q->front->next; // 修改队头指针
    if (Q->front == NULL)
        Q->rear = NULL; // 如果队列为空，修改队尾指针
    free(p);            // 释放原队头结点
    return OK;          // 出队成功
}
