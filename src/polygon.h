#ifndef __POLYGON__
#define __POLYGON__

typedef void* Polygon;
#include "kdTree.h"

Polygon createPolygon(int edge, double *x, double*y, double radiacao);

void endAllPolygon(KdTree tree, NodeKdTree root);

double* getPolygonCenter(Polygon polygon);

int getPolygonEdge(Polygon polygon);

double* getPolygonY(Polygon polygon);

double* getPolygonX(Polygon polygon);

double getPolygonRadiacao(Polygon polygon);

double radiationOnPoint(KdTree tree, NodeKdTree root, double x, double y);

#endif