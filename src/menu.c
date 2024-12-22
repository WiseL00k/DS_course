#include "menu.h"

time_t rawtime;
struct tm *timeinfo;

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

void useDefaultData(VexType **vexs, int *n, ArcInfo **arcs, int *e, int *currentDatap)
{
    if (*currentDatap == USER_DATA || *currentDatap == RANDOM_DATA)
    {
        free(vexs);
        free(arcs);
        *vexs = default_test_vexs;
        *arcs = default_test_arcs;
        *n = 10;
        *e = 13;
        *currentDatap = DEFAULT_DATA;
    }
    puts("已加载默认测试数据!");
}

void useUserData(VexType **vexs, int *n, ArcInfo **arcs, int *e, int *currentDatap)
{
    if (*currentDatap == USER_DATA || *currentDatap == RANDOM_DATA)
    {
        free(*vexs);
        free(*arcs);
    }
    puts("请输入顶点数和边数(格式: 顶点数,边数):");
    scanf(" %d,%d", n, e);
    *vexs = (VexType *)malloc(*n * sizeof(VexType));
    *arcs = (ArcInfo *)malloc(*e * sizeof(ArcInfo));
    puts("请输入顶点信息:");
    for (int i = 0; i < *n; i++)
    {
        scanf(" %c", &(*vexs)[i]);
    }
    puts("请输入边的信息:");
    for (int i = 0; i < *e; i++)
    {
        printf("请输入第%d条边的信息(格式: 起点,终点,权值):\n", i + 1);
        scanf(" %c,%c,%d", &(*arcs)[i].v, &(*arcs)[i].w, &(*arcs)[i].info);
    }
    *currentDatap = USER_DATA;
    MGraph G_M;
    CreateGraph_M(&G_M, UDN, *vexs, *n, *arcs, *e);
    if (!isConnected_M(&G_M))
    {
        printf("图不连通!请检查输入数据是否正确!\n");
        return;
    }
    puts("已加载用户输入测试数据!");
}

void useRandomData(VexType **vexs, int *n, ArcInfo **arcs, int *e, int *currentDatap)
{
    if (*currentDatap == USER_DATA || *currentDatap == RANDOM_DATA)
    {
        free(*vexs);
        free(*arcs);
    }
    generateRandomConnectedGraphData(vexs, n, arcs, e);
    *currentDatap = RANDOM_DATA;
}

void GenerateMenu(VexType *vexs, int n, ArcInfo *arcs, int e)
{
    int select = -1;
    int outputResultWay = USE_STRING;
    double graphDensity = e / (n * (n - 1) / 2.0f);
    do
    {
        select = -1;
        system("cls"); // 清屏
        displayGenerateMenu(n, e);
        fflush(stdin); // 清空输入缓冲区
        scanf("%d", &select);
        switch (select)
        {
        case USE_PRIM:
            system("cls"); // 清屏
            generatePrim(vexs, n, arcs, e, outputResultWay);
            break;
        case USE_KRUSKAL:
            system("cls"); // 清屏
            generateKruskal(vexs, n, arcs, e, outputResultWay);
            break;
        case USE_RECOMMENDED:
            system("cls"); // 清屏
            printf("=========================================\n");
            printf("当前图密度为: %.2lf\n", graphDensity);
            printf("系统推荐使用: %s算法\n", graphDensity > 0.5 ? "Prim" : "Kruskal");
            printf("=========================================\n");
            if (graphDensity > 0.5)
                generatePrim(vexs, n, arcs, e, outputResultWay);
            else
                generateKruskal(vexs, n, arcs, e, outputResultWay);
            break;
        case OUTPUT_RESULT_WAY:
            outputResultWayMenu(&outputResultWay);
            break;
        case EXIT:
            break;
        default:
            printf("输入错误,请重试!\n");
            puts("按任意键以继续...");
            system("pause");
            break;
        }
    } while (select != EXIT);
}

void displayMenuHeadline()
{
    puts("       ____   ____    _   _   _____   ");
    puts("      / ___| |  _ \\  | | | | |_   _| ");
    puts("     | |  _  | | | | | | | |   | |    ");
    puts("     | |_| | | |_| | | |_| |   | |    ");
    puts("      \\____| |____/   \\___/    |_|  ");
    printf("-------------------------------------------\n");
    printf("\t     数据结构课程设计\n");
    printf("\t     城际铁路建设方案\n");
    printf("-------------------------------------------\n");
    printf("姓名:XXXX 班级:XX计科XX班 学号:XXXXXXXXXX\n");
    printf("-------------------------------------------\n");
}

void displayInputDataMenu(int n, int e)
{
    // 获取当前系统时间
    time(&rawtime);
    // 将时间转换为本地时间
    timeinfo = localtime(&rawtime);

    displayMenuHeadline();
    printf("\t   1. 使用默认数据(默认)\n");
    printf("\t   2. 用户自行输入\n");
    printf("\t   3. 随机生成数据\n");
    printf("\t   4. 开始测试\n");
    printf("\t   0. 退出\n");
    printf("-------------------------------------------\n");
    printf("在选择好测试数据后,便可开始测试\n");
    printf("-------------------------------------------\n");
    printf("当前城市(顶点)数: %d, 铁路(边)数: %d\n", n, e);
    printf("当前时间: %d年%d月%d日 %02d:%02d\n", timeinfo->tm_year + 1900, timeinfo->tm_mon + 1, timeinfo->tm_mday, timeinfo->tm_hour, timeinfo->tm_min);
    printf("-------------------------------------------\n");
    printf("请输入你的选择<0-4>: ");
}

void displayGenerateMenu(int n, int e)
{
    // 获取当前系统时间
    time(&rawtime);
    // 将时间转换为本地时间
    timeinfo = localtime(&rawtime);
    displayMenuHeadline();
    printf("\t1. 使用Prim算法\n");
    printf("\t2. 使用Kruskal算法\n");
    printf("\t3. 使用系统推荐算法(自动二选一)\n");
    printf("\t4. 选择输出结果方式\n");
    printf("\t0. 返回\n");
    printf("-------------------------------------------\n");
    printf("当前城市(顶点)数: %d, 铁路(边)数: %d\n", n, e);
    printf("当前时间: %d年%d月%d日 %02d:%02d\n", timeinfo->tm_year + 1900, timeinfo->tm_mon + 1, timeinfo->tm_mday, timeinfo->tm_hour, timeinfo->tm_min);
    printf("-------------------------------------------\n");
    printf("请输入你的选择<0-4>: ");
}

void displayOutputResultWayMenu()
{
    // 获取当前系统时间
    time(&rawtime);
    // 将时间转换为本地时间
    timeinfo = localtime(&rawtime);
    displayMenuHeadline();
    printf("\t  1. 直接输出方案(默认)\n");
    printf("\t  2. 打印存储结构\n");
    printf("\t  0. 返回\n");
    printf("-------------------------------------------\n");
    printf("当前时间: %d年%d月%d日 %02d:%02d\n", timeinfo->tm_year + 1900, timeinfo->tm_mon + 1, timeinfo->tm_mday, timeinfo->tm_hour, timeinfo->tm_min);
    printf("-------------------------------------------\n");
    printf("请输入你的选择<0-2>: ");
}

void outputResultWayMenu(int *outputResultWay)
{
    int select = -1;
    do
    {
        select = -1;
        system("cls"); // 清屏
        displayOutputResultWayMenu();
        fflush(stdin); // 清空输入缓冲区
        scanf("%d", &select);
        switch (select)
        {
        case USE_STRING:
            *outputResultWay = USE_STRING;
            printf("已选择直接输出方案方式输出结果!\n");
            break;
        case USE_PRINT:
            *outputResultWay = USE_PRINT;
            printf("已选择打印无向图存储结构方式输出结果!\n");
            break;
        case EXIT:
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
}

void generatePrim(VexType *vexs, int n, ArcInfo *arcs, int e, int outputResultWay)
{
    MGraph G, T;
    if (ERROR == CreateGraph_M(&G, UDN, vexs, n, arcs, e))
    {
        printf("创建图失败!\n");
        puts("按任意键以继续...");
        system("pause");
        return;
    }
    if (OK == Prim(G, 0, &T))
    {
        printf("Prim算法结果:\n");
        if (outputResultWay == USE_PRINT)
        {
            PrintGraph_M(T);
        }
        else if (outputResultWay == USE_STRING)
        {
            outPutResult_M(T);
        }
    }
    else
    {
        printf("Prim算法失败!\n");
        printf("请检查输入数据是否正确!是否是连通图!\n");
        PrintGraph_M(T);
    }
    DestroyGraph_M(&G);
    DestroyGraph_M(&T);
    puts("按任意键以继续...");
    system("pause");
}

void generateKruskal(VexType *vexs, int n, ArcInfo *arcs, int e, int outputResultWay)
{
    ALGraph G, T;
    if (ERROR == CreateGraph_AL(&G, UDN, vexs, n, arcs, e))
    {
        printf("创建图失败!\n");
        puts("按任意键以继续...");
        system("pause");
        return;
    }
    printf("Kruskal算法结果:\n");
    if (OK == Kruskal(G, &T))
    {
        if (outputResultWay == USE_PRINT)
        {
            PrintGraph_AL(T);
        }
        else if (outputResultWay == USE_STRING)
        {
            outPutResult_AL(T);
        }
    }
    else
    {
        printf("Kruskal算法失败!\n");
        printf("请检查输入数据是否正确!是否是连通图!\n");
        PrintGraph_AL(T);
    }
    DestroyGraph_AL(&G);
    DestroyGraph_AL(&T);
    puts("按任意键以继续...");
    system("pause");
}
