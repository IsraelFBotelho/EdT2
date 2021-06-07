#ifndef __GEO__
#define __GEO__

#include "list.h"

/*
* Abre e Lê um arquivo .geo, le os seus comandos e armazena as informaçoes em uma estrutura de dados
* Pre: Um char* com a string do caminho de entrada, Um char* com a string do nome do .geo, Um void* com o endereço da arvore de Retangulos,
       Um void* com o endereço da arvore de Circulos
* Pos: Nenhum retorno
*/
void readGeo(char* path, char* name, KdTree *treeRect, KdTree *treeCircle);

#endif
