#ifndef __RECTANGLE__
#define __RECTANGLE__

#include "list.h"
#include "kdTree.h"

typedef void* Rectangle;

/*
* Cria uma estrutura de um retangulo e as preenche
* Pre: Um double com valor, Um double com valor, Um double com valor, Um double com valor, Um char[30] com valor, Um char[25] com valor, Um char[25] com valor
* Pos: Retorna um void* com o endereço do retangulo
*/
Rectangle createRectangle(double x, double y, double height, double width, char id[30], char fill[25], char stroke[25]);

/*
* Encerra uma estrutura de informaçoes de um retangulo
* Pre: Um void* com o endereço do retangulo
* Pos: Nenhum retorno
*/
void endRectangle(Rectangle rectangle);

/*
* Encerra todos as estruturas de informaçoes dos retangulos de uma árvore
* Pre Um void* com o endereço da raiz da árvore
* Pos: Nenhum retorno
*/
void endAllRectangle(NodeKdTree node);

/*
* Recupera um char* com o id de um retangulo
* Pre: Um void* com o endereço do retangulo
* Pos: Retorna um char* com valores
*/
char* getRectangleId(Rectangle rectangle);

/*
* Recupera um double com o x de um retangulo
* Pre: Um void* com o endereço do retangulo
* Pos: Retorna um double com valor
*/
double getRectangleX(Rectangle rectangle);

/*
* Recupera um double com o y de um retangulo
* Pre: Um void* com o endereço do retangulo
* Pos: Retorna um double com valor
*/
double getRectangleY(Rectangle rectangle);

/*
* Recupera um double com a altura de um retangulo
* Pre: Um void* com o endereço do retangulo
* Pos: Retorna um double com valor
*/
double getRectangleHeight(Rectangle rectangle);

/*
* Recupera um double com a largura de um retangulo
* Pre: Um void* com o endereço do retangulo
* Pos: Retorna um double com valor
*/
double getRectangleWidth(Rectangle rectangle);

/*
* Recupera um char* com a string da cor do preenchimento de um retangulo
* Pre: Um void* com o endereço do retangulo
* Pos: Retorna um char* com a cor
*/
char* getRectangleFill(Rectangle rectangle);

/*
* Recupera um char* com a string da cor da borda de um retangulo
* Pre: Um void* com o endereço do retangulo
* Pos: Retorna um char* com a cor
*/
char* getRectangleStroke(Rectangle rectangle);

/*
* Recupera o endereço de um retangulo com base nop seu id
* Pre: Um void* com o endereço da raiz da árvore, uum char* com o id
* Pos: Retorna um nó
*/
NodeKdTree getRectangleNodeById(NodeKdTree root, char* id);

/*
* Recupera um double* com o centro de massa do retangulo
* Pre: Um void* com o endereço do retangulo
* Pos: Retorna um double* com valor
*/
double* getRectangleCenter(Rectangle rectangle);

/*
* Recupera quantos circulos o retângulo abrigou pelo comando fg
* Pre: Um void* com o endereço do retangulo
* Pos: Retorna um int com valor
*/
int getRectangleSheltered(Rectangle rectangle);

/*
* Recupera quantos retanguloss possui dentro um ponto (x,y)
* Pre: Um void* com a raiz da árvore de retangulos
* Pos: Retorna um void* com a lista de retangulos
*/
List getInsiderKdTree(KdTree tree, double x, double y);

/*
* Altera e/ou define a quantidade de circulos abrigados pelo retangulo no comando fg
* Pre: Um void* com o endereço do retangulo, Um int com o novo valor
* Pos: Nenhum retorno
*/
void setRectangleSheltered(Rectangle rectangle, int value);

/*
* Altera e/ou define a cor de preenchimento do retangulo
* Pre: Um void* com o endereço do retangulo, Um char[25] com o novo valor
* Pos: Nenhum retorno
*/
void setRectangleFill(Rectangle rectangle, char fill[25]);

/*
* Altera e/ou define a cor de borda do retangulo
* Pre: Um void* com o endereço do retangulo, Um char[25] com o novo valor
* Pos: Nenhum retorno
*/
void setRectangleStroke(Rectangle rectangle, char stroke[25]);


#endif
