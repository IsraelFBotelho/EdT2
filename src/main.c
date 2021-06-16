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
    char *nameArqAnalysis = NULL;
    char *titleAnalysis = NULL;
    int numberVisits = 0;
    int swAnalysis = 0;
    int numberListSize = 0;
    KdTree treeRect = createKdTree();
    KdTree treeCircle = createKdTree();


    readArgv(argc, argv, &pathOut, &pathIn, &nameArqGeo, &nameArqQry, &swAnalysis, &nameArqAnalysis, &titleAnalysis);

    readGeo(pathIn, nameArqGeo, treeRect, treeCircle);

    numberListSize = getKdTreeSize(treeRect) + getKdTreeSize(treeCircle);

    writeSvg(treeRect, treeCircle, NULL, NULL, NULL, NULL, pathOut, nameArqGeo);

    readQry(pathIn, pathOut, nameArqQry, nameArqGeo, treeRect, treeCircle);



    endAllRectangle(treeRect, getKdRoot(treeRect));
    endAllCircle(treeCircle, getKdRoot(treeCircle));
    numberVisits = deleteKdTree(treeCircle) + deleteKdTree(treeRect);


    if(swAnalysis == 1){

        startAnalysis(pathOut, numberVisits, numberListSize);
    }else if(swAnalysis == 2){

        continueAnalysis(pathOut, numberVisits, numberListSize);
    }else if(swAnalysis == 3){

        endAnalysis(pathOut, numberVisits, numberListSize, titleAnalysis, nameArqAnalysis);
    }


    free(titleAnalysis);
    free(nameArqAnalysis);
    free(pathOut);
    free(nameArqGeo);
    free(pathIn);
    free(nameArqQry);

    return 0;
}