#ifndef __KDTREE__
#define __KDTREE__

#include "list.h"

typedef void* KdTree;
typedef void* NodeKdTree;

/*
* Cria uma estrutura de árvore KD
* Pre: Nenhum requesito
* Pos: Um Void* com o endereço da árvore
*/
KdTree createKdTree();

/*
* Insere na árvore um endereço de informação baseado em uma coordenada (x,y)
* Pre: Um void* com o endereço da árvore, Um void* com o endereço da informação, um double* com valor
* Pos: Nenhum retorno
*/
void insertKdTreeElement(KdTree tree, Info info, double key[2]);

/*
* Deleta um nó da árvore com base em uma coordenada (x,y)
* Pre: Um void* com o endereço da árvore, um double* com valor
* Pos: Nenhum retorno
*/
void deleteKdTreeElement(KdTree tree, double key[2]);

/*
* Encerra uma estrutura de árvore KD
* Pre: Um Void* com o endereço da árvore
* Pos: Nenhum retorno
*/
void endKdTree(KdTree tree);

/*
* Recupera um endereço de informação de um nó de uma árvore
* Pre: Um void* com o endereço do nó
* Pos: Um void* com o endereço da informação 
*/
Info getKdTreeInfo(NodeKdTree node);

/*
* Recupera um endereço de informação de um nó de uma árvore com base em uma coordenada (x,y)
* Pre: Um void* com o endereço do nó, um double* com valor
* Pos: Um void* com o endereço da informação 
*/
Info getKdTreeInfoByKey(KdTree tree, double key[2]);

/*
* Recupera um endereço de um nó da árvore à esquerda do nó passado
* Pre: Um void* com o endereço do nó
* Pos: Um void* com o endereço de um nó
*/
NodeKdTree getKdTreeNodeLeft(NodeKdTree node);

/*
* Recupera um endereço de um nó da árvore à direita do nó passado
* Pre: Um void* com o endereço do nó
* Pos: Um void* com o endereço de um nó
*/
NodeKdTree getKdTreeNodeRight(NodeKdTree node);

/*
* Recupera um endereço de um nó raiz da árvore
* Pre: Um void* com o endereço da árvore
* Pos: Um void* com o endereço de um nó
*/
NodeKdTree getKdTreeRoot(KdTree tree);

/*
* Recupera quantos nós tem na árvore
* Pre: Um void* com o endereço da árvore
* Pos: Um int com valor
*/
int getKdTreeSize(KdTree tree);

/*
* Recupera qual dimensão da coordenada foi usada para ordenar o nó
* Pre: Um void* com o endereço do nó
* Pos: Um int com 0 para x ou 1 para y
*/
int getKdTreeDimension(NodeKdTree node);

/*
* Calcula e cria uma Lista com os nós que estão dentro do retângulo passado
* Pre: Um void* com o endereço da árvore, Um double com x, Um double com y
  Um double com a largura, Um double com a altura
* Pos: Um void* com o endereço da Lista
*/
List getKdTreeSearchRange(KdTree tree, double x, double y, double w, double h);

/*
* Calcula e cria uma Lista com os nós que estão dentro de um Circulo
* Pre: Um void* com o endereço da árvore, Um double com x, Um double com y
  Um double com o raio
* Pos: Um void* com o endereço da Lista
*/
List getKdTreeSearchRangeRadius(KdTree tree, double x, double y, double r);

/*
* Busca o nó mais próximo dado uma coordenada
* Pre: Um void* com o endereço da raiz da árvore, Um double* com valor
* Pos: Um void* com o endereço do nó
*/
NodeKdTree nearestNeighborKdTree(NodeKdTree root, double key[2]);

/*
* Recupera qual qual o menor ponto da árvore
* Pre: Um void* com o endereço da raiz da árvore
* Pos: Um double* com valor
*/
double* getKdTreeMinValue(NodeKdTree root);

/*
* Recupera qual qual o maior ponto da árvore
* Pre: Um void* com o endereço da raiz da árvore
* Pos: Um double* com valor
*/
double* getKdTreeMaxValue(NodeKdTree root);

#endif