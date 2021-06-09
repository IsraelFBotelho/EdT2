#ifndef __KDTREE__
#define __KDTREE__

#include "list.h"

typedef void* KdTree;
typedef void* NodeKdTree;

KdTree createKdTree();

void insertKdTreeElement(KdTree tree, Info info, double key[2]);

void deleteKdTreeElement(KdTree tree, double key[2]);

int deleteKdTree(KdTree tree);

Info getKdTreeInfo(NodeKdTree node);

Info getKdTreeInfoByKey(KdTree tree, double key[2]);

NodeKdTree getKdNodeLeft(KdTree tree, NodeKdTree node);

NodeKdTree getKdNodeRight(KdTree tree, NodeKdTree node);

NodeKdTree getKdRoot(KdTree tree);

int getKdTreeSize(KdTree tree);

int getKdTreeVisit(KdTree tree);

int getKdTreeDimension(NodeKdTree node);

List getSearchRangeKdTree(KdTree tree, double x, double y, double w, double h);

#endif