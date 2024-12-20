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
    // 默认测试数据
    VexType default_test_vexs[10] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J'};
    ArcInfo default_test_arcs[13] = {
        {'A', 'B', 3},
        {'A', 'D', 8},
        {'A', 'E', 10},
        {'E', 'D', 9},
        {'B', 'D', 6},
        {'C', 'B', 15},
        {'C', 'E', 12},
        {'D', 'F', 7},
        {'F', 'G', 5},
        {'G', 'H', 4},
        {'H', 'I', 2},
        {'I', 'J', 1},
        {'J', 'E', 11},
    };
    vexs = default_test_vexs;
    arcs = default_test_arcs;
    // 主菜单
    do
    {
        select = -1;
        system("cls"); // 清屏
        displayInputDataMenu(n,e);
        fflush(stdin); // 清空输入缓冲区
        scanf("%d", &select);
        switch (select)
        {
        case DEFAULT_DATA:
        {
            if (currentData == USER_DATA || currentData == RANDOM_DATA)
            {
                free(vexs);
                free(arcs);
                vexs = default_test_vexs;
                arcs = default_test_arcs;
                n = 10;
                e = 13;
                currentData = DEFAULT_DATA;
            }
            puts("已加载默认测试数据!");
            break;
        }
        case USER_DATA:
        {
            if (currentData == USER_DATA || currentData == RANDOM_DATA)
            {
                free(vexs);
                free(arcs);
            }
            puts("请输入顶点数和边数:");
            puts("格式: 顶点数,边数");
            scanf(" %d,%d", &n, &e);
            vexs = (VexType *)malloc(n * sizeof(VexType));
            arcs = (ArcInfo *)malloc(e * sizeof(ArcInfo));
            puts("请输入顶点信息:");
            for (int i = 0; i < n; i++)
            {
                scanf(" %c", &vexs[i]);
            }
            puts("请输入边的信息:");
            puts("格式: 起点,终点,权值");
            for (int i = 0; i < e; i++)
            {
                printf("请输入第%d条边的信息:", i + 1);
                scanf(" %c,%c,%d", &arcs[i].v, &arcs[i].w, &arcs[i].info);
            }
            currentData = USER_DATA;
            MGraph G_M;
            CreateGraph_M(&G_M, UDN, vexs, n, arcs, e);
            if (!isConnected_M(&G_M))
            {
                printf("图不连通!请检查输入数据是否正确!\n");
                break;
            }
            puts("已加载用户输入测试数据!");
            break;
        }
        case RANDOM_DATA:
            if (currentData == USER_DATA || currentData == RANDOM_DATA)
            {
                free(vexs);
                free(arcs);
            }
            generateRandomConnectedGraphData(&vexs, &n, &arcs, &e);
            currentData = RANDOM_DATA;
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
