#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "qry.h"
#include "rectangle.h"
#include "path.h"
#include "svg.h"
#include "circle.h"
#include "geometry.h"
#include "polygon.h"

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

int chooseColorIM(int s){
    if(s < 25){
        return 0;
    }else if( s < 50){
        return 1;
    }else if( s < 100){
        return 2;
    }else if( s < 250){
        return 3;
    }else if( s < 600){
        return 4;
    }else if( s < 1000){
        return 5;
    }else if( s < 8000){
        return 6;
    }else{
        return 7;
    }
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

int cmpstr(const void* a, const void* b){
    const char* aa = (const char*)a;
    const char* bb = (const char*)b;
    return strcmp(aa, bb);
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

void printFgCommand(FILE *txt, List listCircle, List listRect){
    for(Node rect = getListFirst(listRect); rect; rect = getListNext(listRect, rect)){
        char ids[getListSize(listCircle)][50];
        int index = 0;
        int stopCount = 0;
        
        Rectangle rectangle = getListInfo(rect);
        double xR = getRectangleX(rectangle);
        double yR = getRectangleY(rectangle);
        double wR = getRectangleWidth(rectangle);
        double hR = getRectangleHeight(rectangle);
        fprintf(txt,"%s \n",getRectangleId(rectangle));

        for(Node circ = getListFirst(listCircle); circ; circ = getListNext(listCircle, circ)){
            Circle circle = getListInfo(circ);
            double xC = getCircleX(circle);
            double yC = getCircleY(circle);
            if((xC >= xR && xC <= xR + wR) && (yC >= yR && yC <= yR + hR)){
                strcpy(ids[index], getCircleId(circle));
                index++;
                stopCount++;
            }
        }
        stopCount = index;
        qsort(ids, stopCount, sizeof(ids[0]), cmpstr);
        for(index = 0; index < stopCount; index++){
            fprintf(txt, "%s\n", ids[index]);
        }
        fprintf(txt, "\n");
    }
    endList(listRect, NULL);
    endList(listCircle, NULL);
}

void fgCommand(KdTree treeRect, KdTree treeCircle, double x, double y, double r, FILE *txt){
    List list = getSearchRangeRadiusKdTree(treeCircle, x, y, r);
    List listCirc = createList();
    List listRect = createList();

    int size = getListSize(list) + 1 % 2 == 0 ? getListSize(list) + 2 : getListSize(list) + 1;

    int increment = 1;

    for(Node aux = getListFirst(list); aux != NULL; aux = getListNext(list ,aux)){
        double *key = (double *) getListInfo(aux);
        int test = 1;

        NodeKdTree node_rect = nearestNeighborKdTree(getKdRoot(treeRect), key);
        Rectangle rect = getKdTreeInfo(node_rect);
        Circle circle = getKdTreeInfoByKey(treeCircle, key);

        if(isCircleDead(circle)){
            increment++;
            free(key);
            continue;
        }

        insertListElement(listCirc, circle);

        for(Node rectaux = getListFirst(listRect); rectaux; rectaux = getListNext(listRect, rectaux)){
            if(rect == getListInfo(rectaux)){
                test = 0;
            }
        }
        if(test == 1){
            insertListElement(listRect, rect);
        }

        if(isInside(rect, getCircleX(circle), getCircleY(circle))){
            if(IsMotionCircle(circle)){
                increment++;
                free(key);
                continue;
            }
        }

        setRectangleSheltered(rect, getRectangleSheltered(rect) + 1);

        deleteKdTreeElement(treeCircle, key);

        setCircleMotion(circle, getCircleX(circle), getCircleY(circle));

        double new_x = getRectangleX(rect) + (getRectangleWidth(rect) * increment / size);
        setCircleX(circle, new_x);

        double new_y = getRectangleY(rect) + (getRectangleHeight(rect) * increment / size);
        setCircleY(circle, new_y);

        insertKdTreeElement(treeCircle, circle, getCircleCenter(circle));


        increment++;
        free(key);
    }
    printFgCommand(txt, listCirc, listRect);

    endList(list, NULL);

}

void recursiveRectMaxX(KdTree tree, NodeKdTree root, double* coordinate){
    if(root == NULL){
        return;
    }

    recursiveRectMaxX(tree, getKdNodeLeft(tree, root), coordinate);
    recursiveRectMaxX(tree, getKdNodeRight(tree, root), coordinate);

    Rectangle rectangle = getKdTreeInfo(root);
    double rectX = getRectangleX(rectangle) + getRectangleWidth(rectangle);
    double rectY = getRectangleY(rectangle) + getRectangleHeight(rectangle);

    if(coordinate[0] < rectX){
        coordinate[0] = rectX;
    }
    if(coordinate[1] < rectY){
        coordinate[1] = rectY;
    }
    return;
}

void recursiveCircleMaxX(KdTree tree, NodeKdTree root, double* coordinate){
    if(root == NULL){
        return;
    }

    recursiveCircleMaxX(tree, getKdNodeLeft(tree, root), coordinate);
    recursiveCircleMaxX(tree, getKdNodeRight(tree, root), coordinate);

    Circle circle = getKdTreeInfo(root);
    double circX = getCircleX(circle);
    double circY = getCircleY(circle);

    if(coordinate[0] < circX){
        coordinate[0] = circX;
    }
    if(coordinate[1] < circY){
        coordinate[1] = circY;
    }
    return;
}

List createBoundingBox(KdTree treeRect, KdTree treeCircle){
    List listBB = createList();

    double* XYrect = malloc(2*(sizeof(double)));
    XYrect[0] = 0;
    XYrect[1] = 200;
    double* XYCirc = malloc(2*(sizeof(double)));
    XYCirc[0] = 0;
    XYCirc[1] = 200;
    recursiveRectMaxX(treeRect, getKdRoot(treeRect), XYrect);
    recursiveCircleMaxX(treeCircle, getKdRoot(treeCircle), XYCirc);

    double XY2[2];
    if(XYrect[0] > XYCirc[0]){
        XY2[0] = XYrect[0] + 2;
    }else{
        XY2[0] = XYCirc[0] + 2;
    }

    if(XYrect[1] > XYCirc[1]){
        XY2[1] = XYrect[1] + 2;
    }else{
        XY2[1] = XYCirc[1] + 2;
    }

    free(XYrect);
    free(XYCirc);

    Info BB = createRectangle(0, 0, XY2[1], XY2[0], "", "@", "@");

    insertListElement(listBB, BB);

    return listBB;


}

void findRadiationOnAllCircle(KdTree treeCircle, NodeKdTree root, KdTree treePoly, double s, List listDeadCircle){
    if(root == NULL){
        return;
    }

    Circle circle = getKdTreeInfo(root);
    double *key = getCircleCenter(circle);

    int numberShadows  = shadowsOnPoint(treePoly, getKdRoot(treePoly), key[0], key[1]);

    double radiation = s * pow((1 - 0.2), numberShadows);

    setCircleRadiation(circle, radiation);

    char color[8][20] = {"#00FFFF", "#00FF00", "#FF00FF", "#0000FF", "#800080", "#000080", "#FF0000", "#000000"};

    setCircleFill(circle, color[chooseColorIM(getCircleRadiation(circle))]);

    if(getCircleRadiation(circle) >= 1000 && !isCircleRemoved(circle)){
        int test = 1;
        for(Node circAux = getListFirst(listDeadCircle); circAux; circAux = getListNext(listDeadCircle, circAux)){
            if(circle == getListInfo(circAux)){
                test = 0;
            }
        }
        if(test == 1){
            insertListElement(listDeadCircle, circle);
            if(isCircleDead(circle)){
                setIsCircleRemoved(circle);
            }
        }
    } 

    findRadiationOnAllCircle(treeCircle, getKdNodeLeft(treeCircle, root), treePoly, s, listDeadCircle);
    findRadiationOnAllCircle(treeCircle, getKdNodeRight(treeCircle, root), treePoly, s, listDeadCircle);
}

void imCommand(KdTree treePoly,KdTree treeRect, KdTree treeCircle, List listBB, double x, double y, int s, FILE *txt){
    shadowsTravelling(treePoly, treeRect, listBB, x, y, s);

    List listDeadCircle = createList();

    findRadiationOnAllCircle(treeCircle, getKdRoot(treeCircle), treePoly, s, listDeadCircle);

    if(getListSize(listDeadCircle) > 0){
        char ids[getListSize(listDeadCircle)][50];
        int index = 0;
        int stopCount = 0;

        for(Node circ = getListFirst(listDeadCircle); circ; circ = getListNext(listDeadCircle, circ)){
            Circle circle = getListInfo(circ);
            strcpy(ids[index], getCircleId(circle));
            index++;
            stopCount++;
        }
        stopCount = index;
        qsort(ids, stopCount, sizeof(ids[0]), cmpstr);
        for(index = 0; index < stopCount; index++){
            fprintf(txt, "%s\n", ids[index]);
        }
        fprintf(txt, "\n");
    }

    endList(listDeadCircle, NULL);

}

void changeEminentlyDead(KdTree treeCircle, NodeKdTree root, List listDeadCircle){
    if(root == NULL){
        return;
    }

    changeEminentlyDead(treeCircle, getKdNodeLeft(treeCircle, root), listDeadCircle);

    Circle circle = getKdTreeInfo(root);

    if(getCircleRadiation(circle) >= 1000 && !isCircleRemoved(circle)){
        int test = 1;
        for(Node circAux = getListFirst(listDeadCircle); circAux; circAux = getListNext(listDeadCircle, circAux)){
            if(circle == getListInfo(circAux)){
                test = 0;
            }
        }
        if(test == 1){
            insertListElement(listDeadCircle, circle);
            setIsDead(circle);
            setIsCircleRemoved(circle);
        }
    } 

    changeEminentlyDead(treeCircle, getKdNodeRight(treeCircle, root), listDeadCircle);
}

void t30Command(KdTree treeCircle, FILE* txt){

    List listDeadCircle = createList();

    changeEminentlyDead(treeCircle, getKdRoot(treeCircle), listDeadCircle);

    if(getListSize(listDeadCircle) > 0){
        char ids[getListSize(listDeadCircle)][50];
        int index = 0;
        int stopCount = 0;

        for(Node circ = getListFirst(listDeadCircle); circ; circ = getListNext(listDeadCircle, circ)){
            Circle circle = getListInfo(circ);
            strcpy(ids[index], getCircleId(circle));
            index++;
            stopCount++;
        }
        stopCount = index;
        qsort(ids, stopCount, sizeof(ids[0]), cmpstr);
        for(index = 0; index < stopCount; index++){
            fprintf(txt, "%s\n", ids[index]);
        }
        fprintf(txt, "\n");
    }

    endList(listDeadCircle, NULL);


}

void readQry(char *pathIn,char* pathOut ,char *nameQry, char *nameGeo, KdTree treeRect, KdTree treeCircle){

    if(!nameQry){
        return;
    }

    char id[50], command[30];

    double x = 0, y = 0, r = 0;

    int s = 0;

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
    List listBB = NULL;
    List listPoly = createList();
    KdTree treeCircIM = createKdTree();

    char color[8][20] = {"#00FFFF", "#00FF00", "#FF00FF", "#0000FF", "#800080", "#000080", "#FF0000", "#000000"};

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

        }else if(strcmp(command, "fg") == 0){
            fscanf(qry, "%lf %lf %lf\n", &x, &y, &r);
            fprintf(txt, "fg\n");
            fgCommand(treeRect, treeCircle, x, y, r, txt);

        }else if(strcmp(command, "im") == 0){
            fscanf(qry, "%lf %lf %d\n", &x, &y, &s);
            fprintf(txt, "im\n");
            listBB = listBB == NULL ? createBoundingBox(treeRect, treeCircle) : listBB;
            KdTree treePoly = createKdTree();
            imCommand(treePoly, treeRect, treeCircle, listBB, x, y, s, txt);
            Circle aux = createCircle(x, y, s, "", color[chooseColorIM(s)], "");
            setIsBomb(aux);
            double key[2];
            key[0] = x;
            key[1] = y;
            insertListElement(listPoly, treePoly);
            insertKdTreeElement(treeCircIM, aux, key);

        }else if(strcmp(command, "t30") == 0){
            fscanf(qry, "\n");
            fprintf(txt, "t30\n");
            t30Command(treeCircle, txt);
            printf("passei aq\n");
        }
    }

    writeSvg(treeRect, treeCircle, listBB, listPoly, treeCircIM, pathOut, fullNameQry);

    if(listBB != NULL){
        endRectangle(getListInfo(getListFirst(listBB)));
        endList(listBB, NULL);
    }

    for(Node aux = getListFirst(listPoly); aux; aux = getListNext(listPoly, aux)){
        KdTree treePoly = getListInfo(aux);
        if(treePoly != NULL){
            endAllPolygon(treePoly, getKdRoot(treePoly));
            deleteKdTree(treePoly);
        }
    }
    endList(listPoly, NULL);

    if(treeCircIM != NULL){
        endAllCircle(treeCircIM, getKdRoot(treeCircIM));
        deleteKdTree(treeCircIM);
    }

    fclose(txt);
    free(fullNameQry);
    free(fullPathQry);
    fclose(qry);
}