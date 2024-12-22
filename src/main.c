#include <stdio.h>
#include <stdlib.h>
#include "UDGraph.h"
#include "menu.h"

int main(void)
{
    int select = -1, n = 10, e = 13;
    int currentData = DEFAULT_DATA;
    VexType *vexs = NULL;
    ArcInfo *arcs = NULL;
    vexs = default_test_vexs;
    arcs = default_test_arcs;
    // 主菜单
    do
    {
        select = -1;
        system("cls"); // 清屏
        displayInputDataMenu(n, e);
        fflush(stdin); // 清空输入缓冲区
        scanf("%d", &select);
        switch (select)
        {
        case DEFAULT_DATA:
            useDefaultData(&vexs, &n, &arcs, &e, &currentData);
            break;
        case USER_DATA:
            useUserData(&vexs, &n, &arcs, &e, &currentData);
            break;
        case RANDOM_DATA:
            useRandomData(&vexs, &n, &arcs, &e, &currentData);
            break;
        case GENEGATE_MST:
            GenerateMenu(vexs, n, arcs, e);
            continue;
        // 退出
        case EXIT:
            printf("已退出程序!\n谢谢使用!\n");
            break;
        default:
            printf("输入错误,请重试!\n");
            break;
        }
        if (select != EXIT)
        {
            puts("按任意键以继续...");
            system("pause");
        }
    } while (select != EXIT);

    return 0;
}
