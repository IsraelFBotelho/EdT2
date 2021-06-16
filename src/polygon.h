#ifndef __POLYGON__
#define __POLYGON__

typedef void* Polygon;

Polygon createPolygon(int edge, double *x, double*y, int radiacao);

double* getPolygonCenter(Polygon polygon);

int getPolygonEdge(Polygon polygon);

double* getPolygonY(Polygon polygon);

double* getPolygonX(Polygon polygon);

#endif