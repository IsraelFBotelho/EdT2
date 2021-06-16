#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "path.h"
#include "rectangle.h"
#include "circle.h"
#include "polygon.h"


void recursiveDrawRectangle(FILE *svg, KdTree tree, NodeKdTree node);
void recursiveDrawBoundingBox(FILE *svg, KdTree tree, NodeKdTree node);
void recursiveDrawCircle(FILE *svg, KdTree tree, NodeKdTree node);

int chooseColor(int s){
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

FILE* createSvg(char *fullPathSvg){

    FILE *svg = fopen(fullPathSvg, "w");

    if(!svg){
        printf("Erro na criacao do SVG!!\n");
        free(fullPathSvg);
        exit(1);
    }

    fprintf(svg, "<svg xmlns=\"http://www.w3.org/2000/svg\" xmlns:xlink=\"http://www.w3.org/2000/xlink\">\n");
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

    if(getRectangleSheltered(rectangle) > 0){
        fprintf(svg, "\t<text x=\"%lf\" y=\"%lf\" fill=\"black\" font-size=\"smaller\">%d</text>", x + (width/2), y + (height/2), getRectangleSheltered(rectangle));
    }

    recursiveDrawRectangle(svg, tree, getKdNodeRight(tree, node));
}

void drawBoundingBox(FILE *svg, List list_bb){

    if(list_bb == NULL){
        return;
    }

    for(Node *aux = getListFirst(list_bb); aux; aux = getListNext(list_bb, aux)){
        Rectangle *rectangle = getListInfo(aux);
        double x = getRectangleX(rectangle);
        double y = getRectangleY(rectangle);
        double height = getRectangleHeight(rectangle);
        double width = getRectangleWidth(rectangle);
        fprintf(svg, "\t<rect id=\"Bounding Box\" x=\"%lf\" y=\"%lf\" width=\"%lf\" height=\"%lf\" stroke=\"red\" fill=\"none\" fill-opacity=\"0%%\" stroke-opacity=\"100%%\" stroke-width=\"5\"/>\n",x, y, width, height);
    }
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


    Circle circle = getKdTreeInfo(node);

    double x = getCircleX(circle);
    double y = getCircleY(circle);
    double r = getCircleR(circle);
    char *id = getCircleId(circle);
    char *fill = getCircleFill(circle);
    char *stroke = getCircleStroke(circle);

    if(getCircleRadiation(circle) > 0){
        printf("%lf\n", getCircleRadiation(circle));
    }

    fprintf(svg, "\t<circle id=\"%s\" cx=\"%lf\" cy=\"%lf\" r=\"%lf\" stroke=\"%s\" fill=\"%s\" opacity=\"0.7\">\n", id, x, y, r, stroke, fill);

    if(IsMotionCircle(circle)){
        double *motion = getCircleMotion(circle);
        fprintf(svg, "\t\t<animate attributeName=\"cx\" from=\"%lf\" to=\"%lf\" dur=\"2s\" fill=\"none\" stroke=\"black\" stroke-width=\"2\"/>\n",motion[0], x);
        fprintf(svg, "\t\t<animate attributeName=\"cy\" from=\"%lf\" to=\"%lf\" dur=\"2s\" fill=\"none\" stroke=\"black\" stroke-width=\"2\"/>\n",motion[1], y);
    }

    fprintf(svg, "\t</circle>\n");

    if(IsMotionCircle(circle)){
        double *motion = getCircleMotion(circle);
        fprintf(svg, "\t<line x1=\"%lf\" y1=\"%lf\" x2=\"%lf\" y2=\"%lf\" style=\"stroke:black;stroke-width:0.5;stroke-dasharray:0.5\"/>\n", x, y, motion[0], motion[1]);

        fprintf(svg,"\t<circle cx=\"%lf\" cy=\"%lf\" r=\"%lf\" stroke=\"gray\" fill=\"lightgray\" opacity=\"0.3\"/>]\t", motion[0], motion[1], r);
    }
    
    recursiveDrawCircle(svg, tree, getKdNodeRight(tree, node));
}

void recursiveDrawPolygon(FILE *svg, KdTree tree, NodeKdTree node){
    if(node == NULL){
        return;
    }

    recursiveDrawPolygon(svg, tree, getKdNodeLeft(tree, node));

    Polygon polygon = getKdTreeInfo(node);

    fprintf(svg, "\t<polygon points=\"");

    double *PointsX = getPolygonX(polygon);
    double *PointsY = getPolygonY(polygon);

    for(int i = 0; i < getPolygonEdge(polygon); i++){
        fprintf(svg, "%lf,%lf ", PointsX[i], PointsY[i]);
    }

    char color[8][20] = {"#00FFFF", "#00FF00", "#FF00FF", "#0000FF", "#800080", "#000080", "#FF0000", "#000000"};

    double s = getPolygonRadiacao(polygon);

    fprintf(svg, "\" fill=\"%s\" fill-opacity=\"3%%\" />\n", color[chooseColor(s)]);

    recursiveDrawPolygon(svg, tree, getKdNodeRight(tree, node));

}

void drawPolygon(FILE *svg, KdTree tree){
    if(tree==NULL){
        return;
    }

    recursiveDrawPolygon(svg, tree, getKdRoot(tree));
}

void writeSvg(KdTree tree_rect, KdTree tree_circle, List list_bb, KdTree treePoly, KdTree treeCircIM, char *pathOut, char *nameArq){
    char s[] = "svg";
    char* nameSvg = s;
    char *nameArqExtr = (char *) extractName(nameArq);
    char *nameArqSvg = insertExtension(nameArqExtr, nameSvg);
    char *fullPathSvg = catPath(pathOut, nameArqSvg);

    FILE* svg = createSvg(fullPathSvg);

    drawRectangle(svg, tree_rect);

    drawCircle(svg, tree_circle);

    drawBoundingBox(svg, list_bb);

    drawPolygon(svg, treePoly);

    drawCircle(svg, treeCircIM);

    endSvg(svg);

    free(nameArqExtr);
    free(nameArqSvg);
    free(fullPathSvg);
}