#include <stdio.h>
#include <stdlib.h>
#include "geometry.h"
#include "rectangle.h"
#include "polygon.h"
#include <math.h>


// (x1,y1) = ponto de impacto (x2,y2) = vértice do retangulo
double* traceCoordinate(double x1, double y1, double x2, double y2, Rectangle BB){
    
    double *coordinates = (double *) malloc(2*sizeof(double));

    double m = (y2-y1) / (x2-x1);
    double n = y2 -(m*x2);

    if(m == 0){
        // reta é consttante em y se diminui poe x = 0 se aumenta x = getRectangleWidth(BB)
        if(x1 > x2){
            // esquerda
            coordinates[0] = 0;
            coordinates[1] = y1;
        }else{
            // descendo
            coordinates[0] = getRectangleWidth(BB);
            coordinates[1] = y1;
        }
    }else if(isinf(m)){
        // reta é constante em x e se diminui poe y = 0 se almenta y = getRectangleHeight(BB)
        if(y1 > y2){
            // subindo
            coordinates[0] = x1;
            coordinates[1] = 0;
        }else{
            // descendo
            coordinates[0] = x1;
            coordinates[1] = getRectangleHeight(BB);
        }
    }else{

        if(x1 > x2){
            coordinates[0] = 0;
            coordinates[1] = n;
            // sompra para a esquerda

        }else{
            coordinates[0] = getRectangleWidth(BB);
            coordinates[1] = (coordinates[0]*m) + n;
            // sompra para a direita
        }

        if(coordinates[1] > getRectangleHeight(BB)){
            // subindo
            coordinates[1] = getRectangleHeight(BB);
            coordinates[0] = (coordinates[1] - n) / m;

        }else if(coordinates[1] < 0){
            // descendo
            coordinates[1] = 0;
            coordinates[0] = (coordinates[1] - n) / m;
        }
        
    }

    return coordinates;
}

void makeShadow(KdTree treePoly, double* iM, double* v1, double* v2, Rectangle boundingBox){

    int edge = 0;
    double x[7];
    double y[7];

    x[0] = v1[0];
    x[1] = v2[0];
    y[0] = v1[1];
    y[1] = v2[1];

    double *coor = traceCoordinate(iM[0], iM[1], v1[0], v1[1], boundingBox);
    x[2] = coor[0];
    y[2] = coor[1];
    free(coor);

    coor = traceCoordinate(iM[0], iM[1], v2[0], v2[1], boundingBox);
    x[3] = coor[0];
    y[3] = coor[1];
    free(coor);
    edge = 4;

    y[6] = y[2];
    y[2] = y[3];
    y[3] = y[6];

    x[6] = x[2];
    x[2] = x[3];
    x[3] = x[6];

    // int i = 4;

    // if(y[2] == 0 && (x[2] > 0 && x[2] < getRectangleWidth(boundingBox))){

    // }


    Polygon shadow = createPolygon(edge, x, y, 0);
    insertKdTreeElement(treePoly, shadow, getPolygonCenter(shadow));
}

void recursiveShadowsTravelling(KdTree treePoly, KdTree treeRect, NodeKdTree root, Rectangle boundingBox, double xIM, double yIM){
    if(root == NULL){
        return;
    }

    recursiveShadowsTravelling(treePoly, treeRect, getKdNodeLeft(treeRect,root), boundingBox, xIM, yIM);
    recursiveShadowsTravelling(treePoly, treeRect, getKdNodeRight(treeRect,root), boundingBox, xIM, yIM);

    Rectangle rect = getKdTreeInfo(root);

    double x = getRectangleX(rect);
    double y = getRectangleY(rect);
    double x_w = getRectangleX(rect) + getRectangleWidth(rect);
    double y_h = getRectangleY(rect) + getRectangleHeight(rect);

    double iM[2];
    iM[0] = xIM;
    iM[1] = yIM;

    double v1[2];
    v1[0] = x;
    v1[1] = y;
    double v2[2];
    v2[0] = x_w;
    v2[1] = y;
    double v3[2];
    v3[0] = x;
    v3[1] = y_h;
    double v4[2];
    v4[0] = x_w;
    v4[1] = y_h;


    makeShadow(treePoly, iM, v1, v2, boundingBox);
    makeShadow(treePoly, iM, v1, v3, boundingBox);
    makeShadow(treePoly, iM, v3, v4, boundingBox);
    makeShadow(treePoly, iM, v2, v4, boundingBox);
}

KdTree shadowsTravelling(KdTree treeRect, List listBB, double xIM, double yIM){
    KdTree treePoly = createKdTree();

    Rectangle BB = getListInfo(getListFirst(listBB));

    recursiveShadowsTravelling(treePoly, treeRect, getKdRoot(treeRect), BB, xIM, yIM);

    return treePoly;
}