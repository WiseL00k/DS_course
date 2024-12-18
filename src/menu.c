#include "menu.h"

void GenerateMenu(VexType *vexs, int n, ArcInfo *arcs, int e)
{
    int select = -1;
    int outputResultWay = USE_STRING;
    double graphDensity = e / (n * (n - 1) / 2);
    do
    {
        system("cls"); // 清屏
        displayGenerateMenu();
        fflush(stdin); // 清空输入缓冲区
        scanf("%d", &select);
        switch (select)
        {
        case USE_PRIM:
            generatePrim(vexs, n, arcs, e, &outputResultWay);
            break;
        case USE_KRUSKAL:
            generateKruskal(vexs, n, arcs, e, &outputResultWay);
            break;
        case USE_RECOMMENDED:
            if (graphDensity > 0.5)
                generatePrim(vexs, n, arcs, e, &outputResultWay);
            else
                generateKruskal(vexs, n, arcs, e, &outputResultWay);
            break;
        case OUTPUT_RESULT_WAY:
            outputResultWayMenu(outputResultWay);
            break;
        case EXIT:
            break;
        default:
            break;
        }
    } while (select != EXIT);
}

void displayInputDataMenu()
{
    printf("------------------------------------------\n");
    printf("\t数据结构课程设计\n");
    printf("\t城际铁路建设方案\n");
    printf("------------------------------------------\n");
    printf("姓名:XXX 班级:XX计科X班 学号:XXXXXXXXXX\n");
    printf("------------------------------------------\n");
    printf("\t1. 使用默认数据\n");
    printf("\t2. 用户自行输入\n");
    printf("\t3. 开始测试\n");
    printf("\t0. 退出\n");
    printf("------------------------------------------\n");
    printf("在选择好测试数据后,便可开始测试\n");
    printf("------------------------------------------\n");
    printf("请输入你的选择: ");
}

void displayGenerateMenu()
{
    printf("------------------------------------------\n");
    printf("\t数据结构课程设计\n");
    printf("\t城际铁路建设方案\n");
    printf("------------------------------------------\n");
    printf("姓名:XXX 班级:XX计科X班 学号:XXXXXXXXXX\n");
    printf("------------------------------------------\n");
}

void displayOutputResultWayMenu()
{

}

void outputResultWayMenu(int outputResultWay)
{

}

void generatePrim(VexType *vexs, int n, ArcInfo *arcs, int e, int *outputResultWay)
{
    MGraph G, T;

    Prim(G, 0, &T);
}

void generateKruskal(VexType *vexs, int n, ArcInfo *arcs, int e, int *outputResultWay)
{
    ALGraph G, T;

    Kruskal(G, &T);
}
