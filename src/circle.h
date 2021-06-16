#ifndef __CIRCLE__
#define __CIRCLE__

#include "kdTree.h"

typedef void* Circle;
/*
* Cria uma estrutura de um circulo e as preenche
* Pre: Um double com valor, Um double com valor, Um double com valor, Um char* com valor, Um char* com valor, Um char* com valor
* Pos: Retorna um void* com o endereço do circulo 
*/
Circle createCircle(double x, double y, double r, char id[50], char fill[25], char stroke[25]);

/*
* Encerra uma estrutura de informação de um circulo
* Pre: Um void* com o endereço do circulo
* Pos: Nenhum retorno
*/
void endCircle(Circle circle);

/*
* Encerra Todas as estruturas de informaçoes de circulos de uma arvore
* Pre: Um void* o endereço da arvore, Um void* com o endereço da raiz da arvore
* Pos: Nenhum retorno
*/
void endAllCircle(KdTree tree, NodeKdTree node);

/*
* Recupera um double com o x de um circulo
* Pre: Um void* com o endereço do circulo
* Pos: Retorna um double com valor
*/
double getCircleX(Circle circle);

/*
* Recupera um double com o y de um circulo
* Pre: Um void* com o endereço do circulo
* Pos: Retorna um double com valor
*/
double getCircleY(Circle circle);

/*
* Recupera um double* com o x,y de um circulo
* Pre: Um void* com o endereço do circulo
* Pos: Retorna um double* com 2 valores
*/
double *getCircleCenter(Circle circle);

/*
* Recupera um double com o raio de um circulo
* Pre: Um void* com o endereço do circulo
* Pos: Retorna um double com valor
*/
double getCircleR(Circle circle);

/*
* Recupera um char* com o id de um circulo
* Pre: Um void* com o endereço do circulo
* Pos: Um char* com valores
*/
char* getCircleId(Circle circle);

/*
* Recupera um char* com a string da cor de preenchimento de um circulo
* Pre: Um void* com o endereço do circulo
* Pos: Um char* com valores
*/
char* getCircleFill(Circle circle);

/*
* Recupera um char* com a string da cor da borda de um circulo
* Pre: Um void* com o endereço do circulo
* Pos: Um char* com valores
*/
char* getCircleStroke(Circle circle);

double getCircleRadiation(Circle circle);

int IsMotionCircle(Circle circle);

double* getCircleMotion(Circle circle);

void setCircleX(Circle circle, double x);

void setCircleY(Circle circle, double y);

void setCircleRadiation(Circle circle, double radiation);

void setCircleMotion(Circle circle, double x, double y);

#endif