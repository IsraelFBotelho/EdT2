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
* Pre: Um void* com o endereço da raiz da arvore
* Pos: Nenhum retorno
*/
void endAllCircle(NodeKdTree node);

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
* Pos: Retorna um char* com valores
*/
char* getCircleId(Circle circle);

/*
* Recupera um char* com a string da cor de preenchimento de um circulo
* Pre: Um void* com o endereço do circulo
* Pos: Retorna um char* com valores
*/
char* getCircleFill(Circle circle);

/*
* Recupera um char* com a string da cor da borda de um circulo
* Pre: Um void* com o endereço do circulo
* Pos: Retorna um char* com valores
*/
char* getCircleStroke(Circle circle);

/*
* Recupera um double com o valor da radiação de um circulo
* Pre: Um void* com o endereço do circulo
* Pos: Retorna um double com valor
*/
double getCircleRadiation(Circle circle);

/*
* Recupera um double com a posição inicial do circulo antes de se mover
* Pre: Um void* com o endereço do circulo
* Pos: Retorna um double* com valor
*/
double* getCircleMotion(Circle circle);

/*
* Recupera um int com a quantidade de sombras a qual o circulo está
* Pre: Um void* com o endereço do circulo
* Pos: Retorna um int com valor
*/
int getCircleAmountShadow(Circle circle);

/*
* Altera e/ou define o x de um circulo
* Pre: Um void* com o endereço do circulo, um double com valor
* Pos: Nenhum retorno
*/
void setCircleX(Circle circle, double x);

/*
* Altera e/ou define o y de um circulo
* Pre: Um void* com o endereço do circulo, um double com valor
* Pos: Nenhum retorno
*/
void setCircleY(Circle circle, double y);

/*
* Altera e/ou define a radiação de um circulo
* Pre: Um void* com o endereço do circulo, um double com valor
* Pos: Nenhum retorno
*/
void setCircleRadiation(Circle circle, double radiation);

/*
* Altera e/ou define a posição do circulo antes de se mover
* Pre: Um void* com o endereço do circulo, um double com valor, um double com valor
* Pos: Nenhum retorno
*/
void setCircleMotion(Circle circle, double x, double y);

/*
* Altera e/ou define a cor de preenchimento de um circulo
* Pre: Um void* com o endereço do circulo, um char* com valor
* Pos: Nenhum retorno
*/
void setCircleFill(Circle circle, char fill[25]);

/*
* Define que o circulo está morto
* Pre: Um void* com o endereço do circulo
* Pos: Nenhum retorno
*/
void setIsCircleDead(Circle circle);

/*
* Define se o circulo é um meteoro
* Pre: Um void* com o endereço do circulo
* Pos: Nenhum retorno
*/
void setIsCircleMeteor(Circle circle);

/*
* Aumenta em 1 a quantidade de sombras
* Pre: Um void* com o endereço do circulo
* Pos: Nenhum retorno
*/
void setCircleAmountShadow(Circle circle);

/*
* Define se o circulo tem que ser removido da lista
* Pre: Um void* com o endereço do circulo
* Pos: Nenhum retorno
*/
void setIsCircleRemoved(Circle circle);

/*
* Verifica se o circulo esta removido da lista
* Pre: Um void* com o endereço do circulo
* Pos: Retorna um int com valor booleano
*/
int isCircleRemoved(Circle circle);

/*
* Verifica se o circulo se moveu
* Pre: Um void* com o endereço do circulo
* Pos: Retorna um int com valor booleano
*/
int isCircleMotion(Circle circle);

/*
* Verifica se o circulo é um meteoro
* Pre: Um void* com o endereço do circulo
* Pos: Retorna um int com valor booleano
*/
int isCircleMeteor(Circle circle);

/*
* Verifica se o circulo esta morto
* Pre: Um void* com o endereço do circulo
* Pos: Retorna um int com valor booleano
*/
int isCircleDead(Circle circle);

#endif