#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "kdTree.h"
#include "rectangle.h"
#include "circle.h"
#include "path.h"

void readGeo(char* path, char* name, KdTree *treeRect, KdTree *treeCircle){
    double x, y, width, height, radius;
    char id[30], strokeRect[25] = "black", fillRect[25] = "black";
    char strokeCircle[25] = "black", fillCircle[25] = "black";
    char command[30];

    char* fullPathGeo = catPath(path, name);

    FILE *geo = fopen(fullPathGeo,"r");

    if(geo == NULL){
        printf("Arquivo .geo nao encontrado!!\n");
        free(fullPathGeo);
        exit(1);
    }

    *treeRect = createKdTree();
    *treeCircle = createKdTree();

    while(!feof(geo)){

        fscanf(geo,"%s", command);

        if(strcmp(command, "cc") == 0){
            fscanf(geo, "%s\n", strokeRect);

        }else if(strcmp(command, "cp") == 0){
            fscanf(geo, "%s\n", fillRect);

        } else if(strcmp(command, "bc") == 0){
            fscanf(geo, "%s\n", strokeCircle);

        }else if(strcmp(command, "pc") == 0){
            fscanf(geo, "%s\n", fillCircle);

        }else if(strcmp(command, "r") == 0){
            fscanf(geo,"%s %lf %lf %lf %lf\n", id, &x, &y, &width, &height);
            Info aux = createRectangle(x, y, height, width, id, fillRect, strokeRect);
            insertKdTreeElement(*treeRect, aux, getRectangleCenter(aux));
            
        }else if(strcmp(command, "c") == 0){
            fscanf(geo,"%s %lf %lf %lf\n", id, &x, &y, &radius);
            Info aux = createCircle(x, y, radius, id, fillCircle, strokeCircle);
            insertKdTreeElement(*treeCircle, aux, getCircleCenter(aux));
        }
    }
    free(fullPathGeo);
    fclose(geo);
}