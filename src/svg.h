#ifndef __SVG__
#define __SVG__

#include <stdio.h>
#include "rectangle.h"

/*
* Cria e Preenche um arquivo svg com os arquivos de uma lista passada para um diretorio de saida
* Pre: Um void* com o endereço da lista, Um void* com o endereço da lista de bounding box, Um endereço com a lista de circulos
       Um char* com a string do caminho de saida, Um char* com a string do nome do SVG, Um int com o swList
* Pos: Nenhum retorno
*/
void writeSvg(KdTree tree_rect, KdTree tree_circle, List list_bb, KdTree treePoly, KdTree treeCircIM, char *pathOut, char *nameArq);

#endif
