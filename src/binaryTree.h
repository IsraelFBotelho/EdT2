#ifndef __BINARYTREE__
#define __BINARYTREE__

#include "list.h"

typedef void* Tree;
typedef void* NodeTree;

Tree createTree();
void insertTreeElement(Tree tree, Info info);

#endif