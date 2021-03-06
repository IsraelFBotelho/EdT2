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
    int shadows;
    int isDead;
    int isBomb;
    int isRemoved;
    double radiation;
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
    new->shadows = 0;
    new->isMotion = 0;
    new->isDead = 0;
    new->isBomb = 0;
    new->isRemoved = 0;
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

void endAllCircle(NodeKdTree node){
    if(node == NULL){
        return;
    }

    endAllCircle(getKdTreeNodeLeft(node));
    endAllCircle(getKdTreeNodeRight(node));
    
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

double getCircleRadiation(Circle circle){
    CircleStruct *circle_aux = (CircleStruct *) circle;

    return circle_aux->radiation;
}

double* getCircleMotion(Circle circle){
    CircleStruct *circle_aux = (CircleStruct *) circle;

    return circle_aux->motion;
}

int getCircleAmountShadow(Circle circle){
    CircleStruct *circle_aux = (CircleStruct *) circle;

    return circle_aux->shadows;
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

void setCircleRadiation(Circle circle, double radiation){
    CircleStruct *circle_aux = (CircleStruct *) circle;

    circle_aux->radiation += radiation;

    if(circle_aux->radiation > 8000){
        circle_aux->isDead = 1;
    }
}

void setCircleAmountShadow(Circle circle){
    CircleStruct *circle_aux = (CircleStruct *) circle;

    circle_aux->shadows++;
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

void setIsCircleMeteor(Circle circle){
    CircleStruct *circle_aux = (CircleStruct *) circle;

    circle_aux->isBomb = 1;
}

void setIsCircleDead(Circle circle){
    CircleStruct *circle_aux = (CircleStruct *) circle;

    circle_aux->isDead = 1;
}

void setIsCircleRemoved(Circle circle){
    CircleStruct *circle_aux = (CircleStruct *) circle;

    circle_aux->isRemoved = 1;
}

int isCircleRemoved(Circle circle){
CircleStruct *circle_aux = (CircleStruct *) circle;

    return circle_aux->isRemoved;
}

int isCircleDead(Circle circle){
    CircleStruct *circle_aux = (CircleStruct *) circle;

    return circle_aux->isDead;
}

int isCircleMotion(Circle circle){
    CircleStruct *circle_aux = (CircleStruct *) circle;

    return circle_aux->isMotion;
}

int isCircleMeteor(Circle circle){
    CircleStruct *circle_aux = (CircleStruct *) circle;

    return circle_aux->isBomb;
}
