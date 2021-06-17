#ifndef __LIST__
#define __LIST__

typedef void* List;
typedef void* Node;
typedef void* Info;


/*
* Cria Uma lista dinamica
* Pre:Nenhum requesito
* Pos: Retorna um void* com o endereço da lista
*/
List createList();

/*
* Encerra uma lista dinamica
* Pre: Um void* com o endereço da lista, Um int* caso queria o número de visitas
* Pos: Nenhum retorno
*/
void endList(List list, int* numberVisits);

/*
* Insere um elemento criando um no na ultima posição da lista dinamica
* Pre: Um void* com o endereço da lista, Um void* com o endereço da informaçao
* Pos: Nenhum retorno
*/
void insertListElement(List list, Info info);

/*
* Remove um no informado na lista dinamica
* Pre: Um void* com o endereço da lista, Um void* com o endereço do no
* Pos: Nenhum retorno
*/
void removeListNode(List list, Node node);

/*
* Recupera um void* de informaçao de um no na lista dinamica
* Pre: Um void* com o endereço do no
* Pos: Um void* com o endereço da informaçao
*/
Info getListInfo(Node node);

/*
* Recupera o proximo no apontado por outro no na lista dinamica
* Pre: Um void* com o endereço da lista, Um void* com o endereço do no
* Pos: Um void* com o endereço do no
*/
Node getListNext(List list, Node node);

/*
* Recupera o no anterior apontado por outro no na lista dinamica
* Pre: Um void* com o endereço da lista, Um void* com o endereço do no
* Pos: Um void* com o endereço do no
*/
Node getListBack(List list, Node node);

/*
* Recupera o primeiro no de uma lista dinamica
* Pre: Um void* com o endereço da lista
* Pos: Um void* com o endereço do no
*/
Node getListFirst(List list);

/*
 Recupera a quantidade de elementos dentro da lista dinamica
* Pre: Um void* com o endereço da lista
* Pos: Um int com o valor
*/
int getListSize(List list);

/*
* Recupera a quantidade de visitas relativo a lista dinamica
* Pre: Um void* com o endereço da lista
* Pos: Um int com o valor
*/
int getListVisit(List list);

#endif
