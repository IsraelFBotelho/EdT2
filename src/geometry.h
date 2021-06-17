#ifndef __GEOMETRY__
#define __GEOMETRY__

#include "kdTree.h"

/*
* Calcula todas as sombras que retangulos geram a partir de um ponto e salva em uma arvore
* Pre: Um void* com o endereço da arvore das sombras, Um void* com o endereço da arvore dos retangulos, Uma lista com as Bounding Box
       Um double com o x do ponto, Um double com o y do ponto, Um int com o valor de radiação do ponto
* Pos: Nenhum retorno
*/
void shadowsTravelling(KdTree treePoly, KdTree treeRect, List listBB, double xIM, double yIM, int radiacao);

#endif