#include "menu.h"

time_t rawtime;
struct tm *timeinfo;

void GenerateMenu(VexType *vexs, int n, ArcInfo *arcs, int e)
{
    int select = -1;
    int outputResultWay = USE_STRING;
    double graphDensity = e / (n * (n - 1) / 2);
    do
    {
        select = -1;
        system("cls"); // 清屏
        displayGenerateMenu();
        fflush(stdin); // 清空输入缓冲区
        scanf("%d", &select);
        switch (select)
        {
        case USE_PRIM:
            generatePrim(vexs, n, arcs, e, outputResultWay);
            break;
        case USE_KRUSKAL:
            generateKruskal(vexs, n, arcs, e, outputResultWay);
            break;
        case USE_RECOMMENDED:
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

void displayInputDataMenu()
{
    // 获取当前系统时间
    time(&rawtime);
    // 将时间转换为本地时间
    timeinfo = localtime(&rawtime);

    printf("------------------------------------------\n");
    printf("\t数据结构课程设计\n");
    printf("\t城际铁路建设方案\n");
    printf("------------------------------------------\n");
    printf("姓名:XXX 班级:XX计科X班 学号:XXXXXXXXXX\n");
    printf("------------------------------------------\n");
    printf("\t1. 使用默认数据(默认)\n");
    printf("\t2. 用户自行输入\n");
    printf("\t3. 开始测试\n");
    printf("\t0. 退出\n");
    printf("------------------------------------------\n");
    printf("在选择好测试数据后,便可开始测试\n");
    printf("------------------------------------------\n");
    printf("当前时间: %d年%d月%d日 %02d:%02d\n", timeinfo->tm_year + 1900, timeinfo->tm_mon + 1, timeinfo->tm_mday, timeinfo->tm_hour, timeinfo->tm_min);
    printf("请输入你的选择: ");
}

void displayGenerateMenu()
{
    // 获取当前系统时间
    time(&rawtime);
    // 将时间转换为本地时间
    timeinfo = localtime(&rawtime);
    printf("------------------------------------------\n");
    printf("\t数据结构课程设计\n");
    printf("\t城际铁路建设方案\n");
    printf("------------------------------------------\n");
    printf("姓名:XXX 班级:XX计科X班 学号:XXXXXXXXXX\n");
    printf("------------------------------------------\n");
    printf("\t1. 使用Prim算法\n");
    printf("\t2. 使用Kruskal算法\n");
    printf("\t3. 使用系统推荐算法(自动二选一)\n");
    printf("\t4. 选择输出结果方式\n");
    printf("\t0. 退出\n");
    printf("------------------------------------------\n");
    printf("当前时间: %d年%d月%d日 %02d:%02d\n", timeinfo->tm_year + 1900, timeinfo->tm_mon + 1, timeinfo->tm_mday, timeinfo->tm_hour, timeinfo->tm_min);
    printf("请输入你的选择: ");
}

void displayOutputResultWayMenu()
{
    // 获取当前系统时间
    time(&rawtime);
    // 将时间转换为本地时间
    timeinfo = localtime(&rawtime);
    printf("------------------------------------------\n");
    printf("\t数据结构课程设计\n");
    printf("\t城际铁路建设方案\n");
    printf("------------------------------------------\n");
    printf("姓名:XXX 班级:XX计科X班 学号:XXXXXXXXXX\n");
    printf("------------------------------------------\n");
    printf("\t1. 直接输出方案(默认)\n");
    printf("\t2. 打印存储结构\n");
    printf("\t0. 退出\n");
    printf("------------------------------------------\n");
    printf("当前时间: %d年%d月%d日 %02d:%02d\n", timeinfo->tm_year + 1900, timeinfo->tm_mon + 1, timeinfo->tm_mday, timeinfo->tm_hour, timeinfo->tm_min);
    printf("请输入你的选择: ");
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
    puts("按任意键以继续...");
    system("pause");
}

// 输出Prim算法得出的建设方案
void outPutResult_M(MGraph T)
{
    int weight = 0;
    puts("==========================================");
    printf("使用Prim算法得出的铁路建设方案如下:\n");
    printf("铁路(边)\t\t权值\n");
    for (int i = 0; i < T.n; i++)
    {
        for (int j = i; j < T.n; j++)
        {
            if (T.arcs[i][j] != INFINITY)
            {
                printf("%c市<->%c市\t\t%d\n", T.vexs[i], T.vexs[j], T.arcs[i][j]);
                weight += T.arcs[i][j];
            }
        }
    }
    printf("总权值: %d\n", weight);
    puts("==========================================");
}

// 输出Kruskal算法得出的建设方案
void outPutResult_AL(ALGraph T)
{
    int weight = 0;
    int *visited = (int *)calloc(T.n * T.n, sizeof(int)); // 用于记录已经访问过的边
    puts("==========================================");
    printf("使用Kruskal算法得出的铁路建设方案如下:\n");
    printf("铁路(边)\t\t权值\n");
    for (int i = 0; i < T.n; i++)
    {
        for (AdjVexNodeP p = T.vexs[i].firstArc; p; p = p->nextArc)
        {
            int u = i;
            int v = p->adjvex;
            if (!visited[u * T.n + v] && !visited[v * T.n + u])
            {
                printf("%c市<->%c市\t\t%d\n", T.vexs[u].data, T.vexs[v].data, p->info);
                weight += p->info;
                visited[u * T.n + v] = 1;
                visited[v * T.n + u] = 1;
            }
        }
    }
    printf("总权值: %d\n", weight);
    puts("==========================================");
    free(visited);
}
