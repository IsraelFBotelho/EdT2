#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "rectangle.h"
#include "kdTree.h"

typedef struct rectangleStruct{

    double center[2];
    double x;
    double y;
    double height;
    double width;
    char id[50];
    char fill[25];
    char stroke[25];
} RectangleStruct;

Rectangle createRectangle(double x, double y, double height, double width, char id[50], char fill[25], char stroke[25]){
    RectangleStruct *new = (RectangleStruct *) malloc(sizeof(RectangleStruct));

    new->x = x;
    new->y = y;
    new->height = height;
    new->width = width;
    new->center[0] = x + (width / 1.999);
    new->center[1] = y + (height / 1.999);
    strcpy(new->id, id);
    strcpy(new->fill, fill);
    strcpy(new->stroke, stroke);
    
    return new;
}

void endRectangle(Rectangle rectangle){
    RectangleStruct *rectangle_aux = (RectangleStruct *) rectangle;
    free(rectangle_aux);
}

void endAllRectangle(KdTree tree, NodeKdTree node){
    if(node == NULL){
        return;
    }

    endAllRectangle(tree, getKdNodeLeft(tree, node));
    endAllRectangle(tree, getKdNodeRight(tree, node));

    RectangleStruct* rectangle = (RectangleStruct *) getKdTreeInfo(node);

    free(rectangle);
}

char* getRectangleId(Rectangle rectangle){
    RectangleStruct *rectangle_aux = (RectangleStruct *) rectangle;

    return rectangle_aux->id;
}

double* getRectangleCenter(Rectangle rectangle){
    RectangleStruct *rectangle_aux = (RectangleStruct *) rectangle;
    
    return rectangle_aux->center;
}

double getRectangleX(Rectangle rectangle){
    RectangleStruct *rectangle_aux = (RectangleStruct *) rectangle;

    return rectangle_aux->x;
}

double getRectangleY(Rectangle rectangle){
    RectangleStruct *rectangle_aux = (RectangleStruct *) rectangle;

    return rectangle_aux->y;
}

double getRectangleHeight(Rectangle rectangle){
    RectangleStruct *rectangle_aux = (RectangleStruct *) rectangle;

    return rectangle_aux->height;
}

double getRectangleWidth(Rectangle rectangle){
    RectangleStruct *rectangle_aux = (RectangleStruct *) rectangle;

    return rectangle_aux->width;
}

char* getRectangleFill(Rectangle rectangle){
    RectangleStruct *rectangle_aux = (RectangleStruct *) rectangle;

    return rectangle_aux->fill;
}

char* getRectangleStroke(Rectangle rectangle){
    RectangleStruct *rectangle_aux = (RectangleStruct *) rectangle;

    return rectangle_aux->stroke;
}

void setRectangleFill(Rectangle rectangle, char fill[25]){
    RectangleStruct *rectangle_aux = (RectangleStruct *) rectangle;

    strcpy(rectangle_aux->fill, fill);
}

void setRectangleStroke(Rectangle rectangle, char stroke[25]){
    RectangleStruct *rectangle_aux = (RectangleStruct *) rectangle;

    strcpy(rectangle_aux->stroke, stroke);
}

NodeKdTree getRectangleNodeById(KdTree tree, NodeKdTree root, char* id){
    if(root == NULL){
        return NULL;
    }

    RectangleStruct *rectangle = (RectangleStruct *) getKdTreeInfo(root);

    if(strcmp(rectangle->id, id) == 0){
        return root;
    }

    NodeKdTree right = getRectangleNodeById(tree, getKdNodeRight(tree, root), id);

    NodeKdTree left = getRectangleNodeById(tree, getKdNodeLeft(tree, root), id);

    if(right != NULL){
        return right;
    }else{
        return left;
    }
}

void recursiveInsiderKdTree(KdTree tree, List list, NodeKdTree root, double x, double y){

    if(root == NULL){
        return;
    }

    RectangleStruct *rectangle = getKdTreeInfo(root);

    if(rectangle->x <= x && (rectangle->x + rectangle->width) >= x){
        if(rectangle->y <= y && (rectangle->y + rectangle->height) >= y){
            double *aux = malloc(2*(sizeof(double)));
            aux[0] = rectangle->center[0];
            aux[1] = rectangle->center[1];
            insertListElement(list, aux);
        }
    }

    double key[2] = {x, y};

    if(rectangle->center[getKdTreeDimension(root)] <= key[getKdTreeDimension(root)]){
        recursiveInsiderKdTree(tree, list, getKdNodeLeft(tree, root), x, y);
        recursiveInsiderKdTree(tree, list, getKdNodeRight(tree, root), x, y);
    }else{
        recursiveInsiderKdTree(tree, list, getKdNodeLeft(tree, root), x, y);
    }

}

List getInsiderKdTree(KdTree tree, double x, double y){

    List list = createList();
    recursiveInsiderKdTree(tree, list, getKdRoot(tree), x, y);

    return list;
}
