#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "qry.h"
#include "rectangle.h"
#include "path.h"
#include "svg.h"
#include "circle.h"

FILE *getTxtFile(char* nameArq, char* pathOut){
    char t[] = "txt";
    char* nameTxt = t;
    char *nameArqExtr =(char *) extractName(nameArq);
    char *nameArqTxt = insertExtension(nameArqExtr, nameTxt);
    char *fullPathTxt = catPath(pathOut, nameArqTxt);

    FILE *txt = fopen(fullPathTxt, "w");

    if(!txt){
        printf("Erro na criacao do TXT!!\n");
        free(fullPathTxt);
        exit(1);
    }

    free(nameArqExtr);
    free(nameArqTxt);
    free(fullPathTxt);
    return txt;
    
}

char *getQryFileName(char* fullNameGeo, char* nameQry){
    char* nameGeo = extractName(fullNameGeo);
    char* fullName = malloc((strlen(nameGeo) + strlen(nameQry) + 2) *sizeof(char));
    sprintf(fullName,"%s-%s",nameGeo,nameQry);

    free(nameGeo);
    return fullName;
}

int isInside(Rectangle rect, double x, double y){
    if(!rect){
        return 0;
    }
    double x_aux = getRectangleX(rect);
    double y_aux = getRectangleY(rect);
    double h_aux = getRectangleHeight(rect);
    double w_aux = getRectangleWidth(rect);

    if(x >= x_aux && x <= x_aux + w_aux){
        if(y >= y_aux && y <= y_aux + h_aux){
            return 1;
        }
    }
    return 0;
}

int isInsideOf(Rectangle rect1, Rectangle rect2){

    if(!rect1 || !rect2){
        return 0;
    }

    double x1, x2, w1, w2, h1, h2, y1, y2;

    x1 = getRectangleX(rect1);
    x2 = getRectangleX(rect2);
    y1 = getRectangleY(rect1);
    y2 = getRectangleY(rect2);
    w1 = getRectangleWidth(rect1);
    w2 = getRectangleWidth(rect2);
    h1 = getRectangleHeight(rect1);
    h2 = getRectangleHeight(rect2);

    if(x1 <= x2 && ((x1 + w1) >= (x2 + w2))){
        if(y1 <= y2 && ((y1 + h1) >= (y2 + h2))){
            return 1;
        }
    }
    return 0;
}

void dpiCommand(KdTree treeRect, double x, double y, FILE *txt){

    NodeKdTree root = getKdRoot(treeRect);
    List list = getInsiderKdTree(treeRect, x, y);

    for(Node aux = getListFirst(list); aux; aux = getListNext(list ,aux)){
        double *key = (double *) getListInfo(aux);
        Rectangle rectangle = getKdTreeInfoByKey(treeRect, key);

        if(isInside(rectangle, x, y)){
            fprintf(txt, "%s\n", getRectangleId(rectangle));
            endRectangle(rectangle);
            deleteKdTreeElement(treeRect, key);

        }
        free(key);

    }
    endList(list, NULL);

}

void drCommand(KdTree treeRect, char* id, FILE *txt){
    NodeKdTree node = getRectangleNodeById(treeRect, getKdRoot(treeRect), id);
    Rectangle rectangle_node = getKdTreeInfo(node);

    double x = getRectangleX(rectangle_node);
    double y = getRectangleY(rectangle_node);
    double w = getRectangleWidth(rectangle_node);
    double h = getRectangleHeight(rectangle_node);

    List list = getSearchRangeKdTree(treeRect, x, y, w, h);

    for(Node aux = getListFirst(list); aux; aux = getListNext(list ,aux)){
        double *key = (double *) getListInfo(aux);
        Rectangle rectangle = getKdTreeInfoByKey(treeRect, key);
        

        if(rectangle_node != rectangle && isInsideOf(rectangle_node, rectangle)){
            fprintf(txt, "%s\n", getRectangleId(rectangle));
            endRectangle(rectangle);
            deleteKdTreeElement(treeRect, key);

        }
        free(key);

    }
    endList(list, NULL);

}

void readQry(char *pathIn,char* pathOut ,char *nameQry, char *nameGeo, KdTree treeRect, KdTree treeCircle){

    if(!nameQry){
        return;
    }

    char id[30], command[30];
    int k = 0;
    double x = 0, y = 0, height = 0, width = 0;

    char* fullPathQry = catPath(pathIn, nameQry);

    FILE *qry = fopen(fullPathQry, "r");

    if(qry == NULL){
        printf("\nArquivo .qry nao foi encontrado");
        free(fullPathQry);
        return;
    }

    char* aux = extractName(nameQry);
    char* fullNameQry = getQryFileName(nameGeo, aux);\
    free(aux);

    FILE *txt = getTxtFile(fullNameQry, pathOut);


    while(!feof(qry)){
        fscanf(qry,"%s",command);

        if(strcmp(command, "dpi") == 0){
            fscanf(qry, "%lf %lf\n",&x,&y);
            fprintf(txt,"dpi\n");
            dpiCommand(treeRect, x, y, txt);

        }else if(strcmp(command, "dr") == 0){
            fscanf(qry, "%s\n", id);
            fprintf(txt, "dr\n");
            drCommand(treeRect, id, txt);
        }
    }

    writeSvg(treeRect, treeCircle, NULL, pathOut, fullNameQry);

    fclose(txt);
    free(fullNameQry);
    free(fullPathQry);
    fclose(qry);
}