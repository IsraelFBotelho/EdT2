#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "kdTree.h"
#include "circle.h"

typedef struct circleStruct{
    double x;
    double y;
    double r;
    double center[2];
    double motion[2];
    int isMotion;
    int radiation;
    char id[50];
    char fill[25];
    char stroke[25];
}CircleStruct;

Circle createCircle(double x, double y, double r, char id[50], char fill[25], char stroke[25]){

    CircleStruct *new = (CircleStruct *) malloc(sizeof(CircleStruct));

    new->x = x;
    new->y = y;
    new->r = r;
    new->center[0] = x;
    new->center[1] = y;
    new->radiation = 0;
    new->isMotion = 0;
    new->motion[0] = 0;
    new->motion[1] = 0;
    strcpy(new->id, id);
    strcpy(new->fill, fill);
    strcpy(new->stroke, stroke);
    
    return new;
}

void endCircle(Circle circle){
    CircleStruct *circle_aux = (CircleStruct *) circle;
    free(circle_aux);
}

void endAllCircle(KdTree tree, NodeKdTree node){
    if(node == NULL){
        return;
    }

    endAllCircle(tree, getKdNodeLeft(tree, node));
    endAllCircle(tree, getKdNodeRight(tree, node));
    
    CircleStruct *circle = (CircleStruct *) getKdTreeInfo(node);

    free(circle);
}

double getCircleX(Circle circle){
    CircleStruct *circle_aux = (CircleStruct *) circle;

    return circle_aux->x;
}

double getCircleY(Circle circle){
    CircleStruct *circle_aux = (CircleStruct *) circle;

    return circle_aux->y;
}

double* getCircleCenter(Circle circle){
    CircleStruct *circle_aux = (CircleStruct *) circle;

    return circle_aux->center;
}

double getCircleR(Circle circle){
    CircleStruct *circle_aux = (CircleStruct *) circle;

    return circle_aux->r;
}

char* getCircleId(Circle circle){
    CircleStruct *circle_aux = (CircleStruct *) circle;

    return circle_aux->id;
}

char* getCircleFill(Circle circle){
    CircleStruct *circle_aux = (CircleStruct *) circle;

    return circle_aux->fill;
}

char* getCircleStroke(Circle circle){
    CircleStruct *circle_aux = (CircleStruct *) circle;

    return circle_aux->stroke;
}

int getCircleRadiation(Circle circle){
    CircleStruct *circle_aux = (CircleStruct *) circle;

    return circle_aux->radiation;
}

int IsMotionCircle(Circle circle){
    CircleStruct *circle_aux = (CircleStruct *) circle;

    return circle_aux->isMotion;
}

double* getCircleMotion(Circle circle){
    CircleStruct *circle_aux = (CircleStruct *) circle;

    return circle_aux->motion;
}

void setCircleX(Circle circle, double x){
    CircleStruct *circle_aux = (CircleStruct *) circle;


    circle_aux->x = x;
    circle_aux->center[0] = x;
}

void setCircleY(Circle circle, double y){
    CircleStruct *circle_aux = (CircleStruct *) circle;

    circle_aux->y = y;
    circle_aux->center[1] = y;
}

void setCircleRadiation(Circle circle, int radiation){
    CircleStruct *circle_aux = (CircleStruct *) circle;

    circle_aux->radiation = radiation;
}

void setCircleFill(Circle circle, char fill[25]){
    CircleStruct *circle_aux = (CircleStruct *) circle;

    strcpy(circle_aux->fill, fill);
}

void setCircleStroke(Circle circle, char stroke[25]){
    CircleStruct *circle_aux = (CircleStruct *) circle;

    strcpy(circle_aux->stroke, stroke);
}

void setCircleMotion(Circle circle, double x, double y){
    CircleStruct *circle_aux = (CircleStruct *) circle;

    circle_aux->isMotion = 1;
    circle_aux->motion[0] = x;
    circle_aux->motion[1] = y;
}
