#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "path.h"
#include "rectangle.h"
#include "circle.h"


void recursiveDrawRectangle(FILE *svg, KdTree tree, NodeKdTree node);
void recursiveDrawBoundingBox(FILE *svg, KdTree tree, NodeKdTree node);
void recursiveDrawCircle(FILE *svg, KdTree tree, NodeKdTree node);


FILE* createSvg(char *fullPathSvg){

    FILE *svg = fopen(fullPathSvg, "w");

    if(!svg){
        printf("Erro na criacao do SVG!!\n");
        free(fullPathSvg);
        exit(1);
    }

    fprintf(svg, "<svg xmlns=\"http://www.w3.org/2000/svg\">\n");
    return svg;
}

void endSvg(FILE *svg){

    if(!svg){
        printf("Erro na finalizacao do SVG!!\n");
        exit(1);
    }

    fprintf(svg, "</svg>");
    fclose(svg);
}

void drawRectangle(FILE *svg, KdTree tree){

    if(tree == NULL){
        return;
    }

    NodeKdTree root = getKdRoot(tree);
    
    recursiveDrawRectangle(svg, tree, root);
}

void recursiveDrawRectangle(FILE *svg, KdTree tree, NodeKdTree node){

    if(node == NULL){
        return;
    }

    recursiveDrawRectangle(svg, tree, getKdNodeLeft(tree, node));

    Rectangle rectangle = getKdTreeInfo(node);

    double x, y, height, width;
    char *id, *fill, *stroke;

    x = getRectangleX(rectangle);
    y = getRectangleY(rectangle);
    height = getRectangleHeight(rectangle);
    width = getRectangleWidth(rectangle);
    id = getRectangleId(rectangle);
    fill = getRectangleFill(rectangle);
    stroke = getRectangleStroke(rectangle);

    if(strcmp(fill, "@") == 0){
        fill = "none";
    }

    if(strcmp(stroke, "@") == 0){
        fill = "none";
    }
    
    fprintf(svg, "\t<rect id=\"%s\" x=\"%lf\" y=\"%lf\" width=\"%lf\" height=\"%lf\" stroke=\"%s\" fill=\"%s\" fill-opacity=\"50%%\" />\n",id, x, y, width, height, stroke, fill);

    recursiveDrawRectangle(svg, tree, getKdNodeRight(tree, node));
}

void drawBoundingBox(FILE *svg, KdTree tree){

    if(tree == NULL){
        return;
    }
    NodeKdTree root = getKdRoot(tree);

    recursiveDrawBoundingBox(svg, tree, root);
}

void recursiveDrawBoundingBox(FILE *svg, KdTree tree, NodeKdTree node){

    if(node == NULL){
        return;
    }

    recursiveDrawBoundingBox(svg, tree, getKdNodeLeft(tree, node));

    Rectangle *rectangle = getKdTreeInfo(node);
    double x = getRectangleX(rectangle);
    double y = getRectangleY(rectangle);
    double height = getRectangleHeight(rectangle);
    double width = getRectangleWidth(rectangle);
    fprintf(svg, "\t<rect id=\"Bounding Box\" x=\"%lf\" y=\"%lf\" width=\"%lf\" height=\"%lf\" stroke=\"red\" fill=\"none\" fill-opacity=\"0%%\" stroke-opacity=\"100%%\" stroke-dasharray=\"4\" stroke-width=\"2\"/>\n",x, y, width, height);

    recursiveDrawBoundingBox(svg, tree, getKdNodeRight(tree, node));

}

void drawCircle(FILE *svg, KdTree tree){

    if(tree == NULL){
        return;
    }

    NodeKdTree root = getKdRoot(tree);

    recursiveDrawCircle(svg, tree, root);
}

void recursiveDrawCircle(FILE *svg, KdTree tree, NodeKdTree node){

    if(node == NULL){
        return;
    }

    recursiveDrawCircle(svg, tree, getKdNodeLeft(tree, node));

    Circle *circle = getKdTreeInfo(node);
    double x = getCircleX(circle);
    double y = getCircleY(circle);
    double r = getCircleR(circle);
    char *id = getCircleId(circle);
    char *fill = getCircleFill(circle);
    char *stroke = getCircleStroke(circle);

    fprintf(svg, "\t<circle id=\"%s\" cx=\"%lf\" cy=\"%lf\" r=\"%lf\" stroke=\"%s\" fill=\"%s\"/>\n", id, x, y, r, stroke, fill);
    
    recursiveDrawCircle(svg, tree, getKdNodeRight(tree, node));
}

void writeSvg(KdTree tree_rect, KdTree tree_circle, KdTree tree_bb, char *pathOut, char *nameArq){
    char s[] = "svg";
    char* nameSvg = s;
    char *nameArqExtr = (char *) extractName(nameArq);
    char *nameArqSvg = insertExtension(nameArqExtr, nameSvg);
    char *fullPathSvg = catPath(pathOut, nameArqSvg);

    FILE* svg = createSvg(fullPathSvg);

    drawRectangle(svg, tree_rect);

    drawCircle(svg, tree_circle);

    drawBoundingBox(svg, tree_bb);

    endSvg(svg);

    free(nameArqExtr);
    free(nameArqSvg);
    free(fullPathSvg);
}