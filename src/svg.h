#ifndef __SVG__
#define __SVG__

#include <stdio.h>
#include "rectangle.h"

/*
* Cria e Preenche um arquivo svg com os arquivos de uma lista passada para um diretorio de saida
* Pre: Um void* com o endereço da árvore de retangulo, Um void* com o endereço da árvore de circulos, Um void* com o endereço da lista de bounding box,
       Um void* com o endereço de uma lista de árvores de poligonos, Um void* com o endereço de uma árvore de circulos do comando im,
       Um void* com o endereço da lista de retângulos do comando nve,
       Um char* com a string do caminho de saida, Um char* com a string do nome do SVG
* Pos: Nenhum retorno
*/
void writeSvg(KdTree tree_rect, KdTree tree_circle, List list_bb, List listPoly, KdTree treeCircIM, List nveRects, char *pathOut, char *nameArq);

#endif
