#ifndef __KDTREE__
#define __KDTREE__

#include "list.h"

typedef void* KdTree;
typedef void* NodeKdTree;

KdTree createKdTree();

void insertKdTreeElement(KdTree tree, Info info, double key[2]);

void deleteKdTreeElement(KdTree tree, double key[2]);

void deleteKdTree(KdTree tree);

Info getKdTreeInfo(NodeKdTree node);

NodeKdTree getKdNodeLeft(KdTree tree, NodeKdTree node);

NodeKdTree getKdNodeRight(KdTree tree, NodeKdTree node);

#endif