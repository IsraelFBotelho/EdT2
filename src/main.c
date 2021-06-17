#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "rectangle.h"
#include "circle.h"
#include "geo.h"
#include "argv.h"
#include "svg.h"
#include "qry.h"
#include "analysis.h"
#include "kdTree.h"

int main(int argc, char* argv[]){

    char *pathOut = NULL;
    char *nameArqGeo = NULL;
    char *pathIn = NULL;
    char *nameArqQry = NULL;
    KdTree treeRect = createKdTree();
    KdTree treeCircle = createKdTree();


    readArgv(argc, argv, &pathOut, &pathIn, &nameArqGeo, &nameArqQry);

    readGeo(pathIn, nameArqGeo, treeRect, treeCircle);

    writeSvg(treeRect, treeCircle, NULL, NULL, NULL, NULL, pathOut, nameArqGeo);

    readQry(pathIn, pathOut, nameArqQry, nameArqGeo, treeRect, treeCircle);


    endAllRectangle(getKdTreeRoot(treeRect));
    endAllCircle(getKdTreeRoot(treeCircle));
    endKdTree(treeRect);
    endKdTree(treeCircle);

    free(pathOut);
    free(nameArqGeo);
    free(pathIn);
    free(nameArqQry);

    return 0;
}