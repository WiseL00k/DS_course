#ifndef __MENU_H__
#define __MENU_H__

#include <stdio.h>
#include <time.h>
#include "UDGraph.h"
#include "MST.h"

#define EXIT 0
#define DEFAULT_DATA 1
#define USER_DATA 2
#define RANDOM_DATA 3
#define GENEGATE_MST 4

#define USE_PRIM 1
#define USE_KRUSKAL 2
#define USE_RECOMMENDED 3
#define OUTPUT_RESULT_WAY 4

#define USE_STRING 1
#define USE_PRINT 2

void GenerateMenu(VexType *vexs, int n, ArcInfo *arcs, int e);
void displayInputDataMenu();
void displayGenerateMenu();
void displayOutputResultWayMenu();
void displayMenuHeadline();
void outputResultWayMenu(int *outputResultWay);
void generatePrim(VexType *vexs, int n, ArcInfo *arcs, int e, int outputResultWay);
void generateKruskal(VexType *vexs, int n, ArcInfo *arcs, int e, int outputResultWay);
// 输出Prim算法得出的建设方案
void outPutResult_M(MGraph T);
// 输出Kruskal算法得出的建设方案
void outPutResult_AL(ALGraph T);
#endif /* __MENU_H__ */