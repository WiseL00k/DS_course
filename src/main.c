#include <stdio.h>
#include <stdlib.h>
#include "UDGraph.h"
#include "DSU.h"
#include "menu.h"

int main(void)
{
    int select, n = 10, e = 10;
    VexType *vexs = NULL;
    ArcInfo *arcs = NULL;
    // 默认测试数据
    VexType default_test_vexs[10] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J'};
    ArcInfo default_test_arcs[10] = {{'A', 'C', 1}, {'A', 'D', 1}, {'C', 'E', 1}, {'C', 'D', 1}, {'B', 'D', 1}, {'G', 'H', 1}, {'G', 'I', 1}, {'H', 'I', 1}, {'H', 'F', 1}, {'I', 'J', 1}};
    vexs = default_test_vexs;
    arcs = default_test_arcs;
    // 主菜单
    do
    {
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
            n = 10;
            e = 10;
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
