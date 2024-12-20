#include <stdio.h>
#include <stdlib.h>
#include "UDGraph.h"
#include "menu.h"

int main(void)
{
    int select = -1, n = 5, e = 7;
    VexType *vexs = NULL;
    ArcInfo *arcs = NULL;
    // 默认测试数据
    VexType default_test_vexs[5] = {'A', 'B', 'C', 'D', 'E'};
    ArcInfo default_test_arcs[7] = {{'A', 'B', 3}, {'A', 'D', 8}, {'A', 'E', 10}, {'E', 'D', 9}, {'B', 'D', 6}, {'C', 'B', 15}, {'C', 'E', 12}};
    vexs = default_test_vexs;
    arcs = default_test_arcs;
    // 主菜单
    do
    {
        select = -1;
        system("cls"); // 清屏
        displayInputDataMenu();
        fflush(stdin); // 清空输入缓冲区
        scanf("%d", &select);
        switch (select)
        {
        case DEFAULT_DATA:
        {
            vexs = default_test_vexs;
            arcs = default_test_arcs;
            n = 5;
            e = 7;
            puts("已加载默认测试数据!");
            puts("按任意键以继续...");
            system("pause");
            break;
        }
        case USER_DATA:
        {
            puts("请输入顶点数和边数:");
            scanf(" %d %d", &n, &e);
            vexs = (VexType *)malloc(n * sizeof(VexType));
            arcs = (ArcInfo *)malloc(e * sizeof(ArcInfo));
            puts("请输入顶点信息:");
            for (int i = 0; i < n; i++)
            {
                scanf(" %c", &vexs[i]);
            }
            puts("请输入边的信息:");
            for (int i = 0; i < e; i++)
            {
                scanf(" %c %c %d", &arcs[i].v, &arcs[i].w, &arcs[i].info);
            }
            puts("已加载用户输入测试数据!");
            puts("按任意键以继续...");
            system("pause");
            break;
        }
        case GENEGATE_MST:
            GenerateMenu(vexs, n, arcs, e);
        // 退出
        case EXIT:
            printf("已退出程序!\n谢谢使用!\n");
            break;
        default:
            printf("输入错误,请重试!\n");
            puts("按任意键以继续...");
            system("pause");
            break;
        }
    } while (select != EXIT);

    return 0;
}
