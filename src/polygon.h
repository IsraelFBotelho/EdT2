#ifndef __POLYGON__
#define __POLYGON__

typedef void* Polygon;
#include "kdTree.h"

/*
* Cria uma estrutura de poligono
* Pre: Um int com o número de arestas, Um double* com até 7 valores, Um double* com até 7 valores,
       Um double com valor
* Pos: Um void* com a estrutura
*/
Polygon createPolygon(int edge, double *x, double*y, double radiation);

/*
* Encerra todos os poligonos de uma árvore
* Pre: Um void* com o endereço da raiz da árvore
* Pos: Nenhum retorno
*/
void endAllPolygon(NodeKdTree root);

/*
* Recupera o centro de massa de um poligono
* Pre: Um void* com o endereço do poligono
* Pos: Um double* com valor
*/
double* getPolygonCenter(Polygon polygon);

/*
* Recupera quantos lados o poligono tem
* Pre: Um void* com o endereço do poligono
* Pos: Um int com valor
*/
int getPolygonEdge(Polygon polygon);

/*
* Recupera todos os y dos poligonos
* Pre: Um void* com o endereço do poligono
* Pos: Um double* com até 7 valores
*/
double* getPolygonY(Polygon polygon);

/*
* Recupera todos os x dos poligonos
* Pre: Um void* com o endereço do poligono
* Pos: Um double* com até 7 valores
*/
double* getPolygonX(Polygon polygon);

/*
* Recupera o valor da radiação do poligono
* Pre: Um void* com o endereço do poligono
* Pos: Um double com valor
*/
double getPolygonRadiation(Polygon polygon);

/*
* Recupera quantas sombras se tem na coordenada (x,y)
* Pre: Um void* com o endereço da raiz da árvore, Um double com valor,
       Um double com valor
* Pos: Um int com valor
*/
int shadowsOnPoint(NodeKdTree root, double x, double y);

#endif