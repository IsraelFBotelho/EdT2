#ifndef __ANALYSIS__
#define __ANALYSIS__

/*
* Cria um arquivo temporario com as informaçoes das visitas e tamanho da estrutura de dados atual
* Pre: Um char* com o caminho de saida, Um int com o numero de visitas, Um int com o tamanho da estrutura
* Pos: Nenhum retorno
*/
void startAnalysis(char* pathOut, int visit, int size);

/*
* Pega um arquivo temporario ja existente e escreve informaçoes das visitas e tamanho da estrutura de dados atual
* Um char* com o caminho de saida, Um int com o numero de visitas, Um int com o tamanho da estrutura
* Pos: Nenhum retorno
*/
void continueAnalysis(char* pathOut, int visit, int size);

/*
* Pega um arquivo temporario ja existente com informaçoes de visitas e tamanho de estrutura de dados, além das informaçoes do programa atual
*    e cria um grafico Visita x Tamanho com pontos no svg, além de tracejados apontando os pontos, também escreve o nome da analise em baixo
* Pre: Um char* com o caminho de saida, Um int com o numero de visitas, Um int com o tamanho da estrutura, Um char* com o titulo da analise
*      Um char* com o nome do arquivo gerado
* Pos: Nenhum retorno
*/
void endAnalysis(char* pathOut, int visit, int size, char* titleAnalysis, char* nameArqAnalysis);

#endif