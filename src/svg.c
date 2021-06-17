#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "path.h"
#include "rectangle.h"
#include "circle.h"
#include "polygon.h"
#include "utils.h"

#define OPACITY_SHADOW 2

void recursiveDrawRectangle(FILE *svg, NodeKdTree node);
void recursiveDrawBoundingBox(FILE *svg, NodeKdTree node);
void recursiveDrawCircle(FILE *svg, NodeKdTree node);

FILE* createSvg(char *fullPathSvg){

    FILE *svg = fopen(fullPathSvg, "w");

    if(!svg){
        printf("Erro na criacao do SVG!!\n");
        free(fullPathSvg);
        exit(1);
    }

    fprintf(svg,"<!--nome do aluno: Israel Faustino Botelho Junior-->\n");
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

    NodeKdTree root = getKdTreeRoot(tree);
    
    recursiveDrawRectangle(svg, root);
}

void recursiveDrawRectangle(FILE *svg, NodeKdTree node){

    if(node == NULL){
        return;
    }

    recursiveDrawRectangle(svg,getKdTreeNodeLeft(node));

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

    recursiveDrawRectangle(svg, getKdTreeNodeRight(node));
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

    NodeKdTree root = getKdTreeRoot(tree);

    recursiveDrawCircle(svg, root);
}

void recursiveDrawCircle(FILE *svg, NodeKdTree node){

    if(node == NULL){
        return;
    }

    recursiveDrawCircle(svg, getKdTreeNodeLeft(node));


    Circle circle = getKdTreeInfo(node);

    if(isCircleDead(circle)){
        setCircleFill(circle, "none");
    }
    double x = getCircleX(circle);
    double y = getCircleY(circle);
    double r = getCircleR(circle);
    char *id = getCircleId(circle);
    char *fill = getCircleFill(circle);
    char *stroke = getCircleStroke(circle);

    fprintf(svg, "\t<circle id=\"%s\" cx=\"%lf\" cy=\"%lf\" r=\"%lf\" stroke=\"%s\" fill=\"%s\" opacity=\"0.7\">\n", id, x, y, r, stroke, fill);

    if(isCircleMotion(circle)){
        double *motion = getCircleMotion(circle);
        fprintf(svg, "\t\t<animate attributeName=\"cx\" from=\"%lf\" to=\"%lf\" dur=\"2s\" fill=\"none\" stroke=\"black\" stroke-width=\"2\"/>\n",motion[0], x);
        fprintf(svg, "\t\t<animate attributeName=\"cy\" from=\"%lf\" to=\"%lf\" dur=\"2s\" fill=\"none\" stroke=\"black\" stroke-width=\"2\"/>\n",motion[1], y);
    }

    fprintf(svg, "\t</circle>\n");

    if(isCircleMotion(circle)){
        double *motion = getCircleMotion(circle);
        fprintf(svg, "\t<line x1=\"%lf\" y1=\"%lf\" x2=\"%lf\" y2=\"%lf\" style=\"stroke:black;stroke-width:0.5;stroke-dasharray:0.5\"/>\n", x, y, motion[0], motion[1]);

        fprintf(svg,"\t<circle cx=\"%lf\" cy=\"%lf\" r=\"%lf\" stroke=\"gray\" fill=\"lightgray\" opacity=\"0.3\"/>]\t", motion[0], motion[1], r);
    }

    if(isCircleDead(circle)){
        fprintf(svg, "\t<line x1=\"%lf\" y1=\"%lf\" x2=\"%lf\" y2=\"%lf\" style=\"stroke:black;stroke-width:0.5\"/>\n",(x+r),(y),(x-r), (y));
        fprintf(svg, "\t<line x1=\"%lf\" y1=\"%lf\" x2=\"%lf\" y2=\"%lf\" style=\"stroke:black;stroke-width:0.5\"/>\n",(x),(y+r),(x), (y-r));
    }

    if(isCircleMeteor(circle)){
        fprintf(svg, "\t<line x1=\"%lf\" y1=\"%lf\" x2=\"%lf\" y2=\"%lf\" style=\"stroke:orange\"/>\n",(x+5),(y+1),(x-5), (y+1));
        fprintf(svg, "\t<line x1=\"%lf\" y1=\"%lf\" x2=\"%lf\" y2=\"%lf\" style=\"stroke:orange\"/>\n",(x+1),(y+5),(x+1), (y-5));
        fprintf(svg, "\t<line x1=\"%lf\" y1=\"%lf\" x2=\"%lf\" y2=\"%lf\" style=\"stroke:orange\"/>\n",(x+5),(y-1),(x-5), (y-1));
        fprintf(svg, "\t<line x1=\"%lf\" y1=\"%lf\" x2=\"%lf\" y2=\"%lf\" style=\"stroke:orange\"/>\n",(x-1),(y+5),(x-1), (y-5));
    }
    
    recursiveDrawCircle(svg, getKdTreeNodeRight(node));
}

void recursiveDrawPolygon(FILE *svg, NodeKdTree node){
    if(node == NULL){
        return;
    }

    recursiveDrawPolygon(svg, getKdTreeNodeLeft(node));

    Polygon polygon = getKdTreeInfo(node);

    fprintf(svg, "\t<polygon points=\"");

    double *PointsX = getPolygonX(polygon);
    double *PointsY = getPolygonY(polygon);

    for(int i = 0; i < getPolygonEdge(polygon); i++){
        fprintf(svg, "%lf,%lf ", PointsX[i], PointsY[i]);
    }

    char color[8][20] = {"#00FFFF", "#00FF00", "#FF00FF", "#0000FF", "#800080", "#000080", "#FF0000", "#000000"};

    double s = getPolygonRadiation(polygon);
    
    fprintf(svg, "\" fill=\"%s\" fill-opacity=\"%d%%\" />\n", color[chooseColor(s)], OPACITY_SHADOW);

    recursiveDrawPolygon(svg, getKdTreeNodeRight(node));

}

void drawPolygon(FILE *svg, List listPoly){
    if(listPoly==NULL){
        return;
    }

    for(Node aux = getListFirst(listPoly); aux; aux = getListNext(listPoly, aux)){
        KdTree treePoly = getListInfo(aux);
        if(treePoly != NULL){
        recursiveDrawPolygon(svg, getKdTreeRoot(treePoly));

        }
    }
}

void drawNveCommand(FILE *svg, List nveRects){
    if(nveRects == NULL){
        return;
    }

    for(Node aux = getListFirst(nveRects); aux; aux = getListNext(nveRects, aux)){
        Rectangle rectangle = getListInfo(aux);
        double x, y, height, width;
        char *fill, *stroke;

        x = getRectangleX(rectangle);
        y = getRectangleY(rectangle);
        height = getRectangleHeight(rectangle);
        width = getRectangleWidth(rectangle);
        fill = getRectangleFill(rectangle);
        stroke = getRectangleStroke(rectangle);

        fprintf(svg, "\t<rect x=\"%lf\" y=\"%lf\" ry=\"1.5\" rx=\"1.5\" width=\"%lf\" height=\"%lf\" stroke=\"%s\" fill=\"%s\" fill-opacity=\"50%%\" />\n", x, y, width, height, stroke, fill);

    }

}

void writeSvg(KdTree tree_rect, KdTree tree_circle, List list_bb, List listPoly, KdTree treeCircIM, List nveRects, char *pathOut, char *nameArq){
    char s[] = "svg";
    char* nameSvg = s;
    char *nameArqExtr = (char *) extractName(nameArq);
    char *nameArqSvg = insertExtension(nameArqExtr, nameSvg);
    char *fullPathSvg = catPath(pathOut, nameArqSvg);

    FILE* svg = createSvg(fullPathSvg);

    drawRectangle(svg, tree_rect);

    drawCircle(svg, tree_circle);

    drawBoundingBox(svg, list_bb);

    drawPolygon(svg, listPoly);

    drawCircle(svg, treeCircIM);

    drawNveCommand(svg, nveRects);

    endSvg(svg);

    free(nameArqExtr);
    free(nameArqSvg);
    free(fullPathSvg);
}