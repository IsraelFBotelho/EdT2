#include <stdio.h>
#include <stdlib.h>
#include "kdTree.h"
#include <math.h>

typedef struct nodeKdTreeStruct{
    Info info;
    // 0 para x e 1 para y
    int dimension;
    double key[2];
    struct nodeKdTreeStruct *left;
    struct nodeKdTreeStruct *right;
}NodeKDTreeStruct;

typedef struct kdTreeStruct{
    NodeKDTreeStruct *root;
    int size;
}KdTreeStruct;

void recursiveInsertRight(NodeKDTreeStruct *node, Info info, double key[2]);
void recursiveInsertLeft(NodeKdTree node, Info info, double key[2]);

KdTree createKdTree(){
    KdTreeStruct *new = (KdTreeStruct *) malloc(sizeof(KdTreeStruct));

    new->root = NULL;
    new->size = 0;

    return new;
}

void recursiveInsertRight(NodeKDTreeStruct *node, Info info, double key[2]){
    NodeKDTreeStruct *node_aux = (NodeKDTreeStruct *) node;

    if(node_aux->right == NULL){
        NodeKDTreeStruct *new = (NodeKDTreeStruct *) malloc(sizeof(NodeKDTreeStruct));

        new->info = info;
        new->key[0] = key[0];
        new->key[1] = key[1];
        new->left = NULL;
        new->right = NULL;
        new->dimension = node_aux->dimension == 0 ? 1 : 0;
        node_aux->right = new;


    }else{

        if(node_aux->right->key[node_aux->right->dimension] > key[node_aux->right->dimension]){
            recursiveInsertLeft(node_aux->right, info, key);

        }else{
            recursiveInsertRight(node_aux->right, info, key);
        }

    }
}

void recursiveInsertLeft(NodeKdTree node, Info info, double key[2]){
    NodeKDTreeStruct *node_aux = (NodeKDTreeStruct *) node;
    
    if(node_aux->left == NULL){
        NodeKDTreeStruct *new = (NodeKDTreeStruct *) malloc(sizeof(NodeKDTreeStruct));

        new->info = info;
        new->key[0] = key[0];
        new->key[1] = key[1];
        new->left = NULL;
        new->right = NULL;
        new->dimension = node_aux->dimension == 0 ? 1 : 0;
        node_aux->left = new;


    }else{
        if(node_aux->left->key[node_aux->left->dimension] > key[node_aux->left->dimension]){
            recursiveInsertLeft(node_aux->left, info, key);

        }else{
            recursiveInsertRight(node_aux->left, info, key);
        }

    }

}

void insertKdTreeElement(KdTree tree, Info info, double key[2]){
    KdTreeStruct *tree_aux = (KdTreeStruct *) tree;
    
    if(tree_aux->root == NULL){
        NodeKDTreeStruct *new = (NodeKDTreeStruct *) malloc(sizeof(NodeKDTreeStruct));

        new->info = info;
        new->key[0] = key[0];
        new->key[1] = key[1];
        new->left = NULL;
        new->right = NULL;
        new->dimension = 0;
        tree_aux->root = new;

    }else{
        if(tree_aux->root->key[tree_aux->root->dimension] > key[tree_aux->root->dimension]){
            recursiveInsertLeft(tree_aux->root, info, key);

        }else{
            recursiveInsertRight(tree_aux->root, info, key);
        }
    }

    tree_aux->size++;
}

NodeKdTree minMinNode(NodeKdTree x, NodeKdTree y, NodeKdTree z, int d){
    NodeKDTreeStruct *res = (NodeKDTreeStruct*) x;
    NodeKDTreeStruct *aux2  = (NodeKDTreeStruct*) y;
    NodeKDTreeStruct *aux  = (NodeKDTreeStruct*) z;
    if(aux2 != NULL && aux2->key[d] < res->key[d]){
        res = y;
    }
    if(aux != NULL && aux->key[d] < res->key[d]){
        res = z;
    }
    return res;
}

NodeKdTree minTreeValue(NodeKdTree tree, int d){
    NodeKDTreeStruct* root = (NodeKDTreeStruct*) tree;

    if(root == NULL){
        return root;
    }

    int cd = root->dimension;

    if(cd == d){
        if(root->left == NULL){
            return root;
        }
        return minTreeValue(root->left, d);
    }
    return minMinNode(root, minTreeValue(root->left, d), minTreeValue(root->right, d), d);
}

NodeKdTree recursivedeleteTreeElement(NodeKdTree node, double key[2]){
    NodeKDTreeStruct *node_aux = (NodeKDTreeStruct *) node;

    if(node_aux == NULL){
        return NULL;
    }

    if(key[0] == node_aux->key[0] && key[1] == node_aux->key[1]){
        if(node_aux->right != NULL){
            NodeKDTreeStruct *aux = (NodeKDTreeStruct *) minTreeValue(node_aux->right, node_aux->dimension);
            node_aux->key[1] = aux->key[1];
            node_aux->key[0] = aux->key[0];
            node_aux->info = aux->info;
            node_aux->right = recursivedeleteTreeElement(node_aux->right, node_aux->key);

        }else if(node_aux->left != NULL){
            NodeKDTreeStruct *aux = (NodeKDTreeStruct *) minTreeValue(node_aux->left, node_aux->dimension);
            node_aux->key[1] = aux->key[1];
            node_aux->key[0] = aux->key[0];
            node_aux->info = aux->info;
            node_aux->right = recursivedeleteTreeElement(node_aux->left, node_aux->key);
            node_aux->left = NULL;
        }else{
            free(node_aux);
            return NULL;
        }

    } else if (key[node_aux->dimension] < node_aux->key[node_aux->dimension]){
        node_aux->left = recursivedeleteTreeElement(node_aux->left, key);

    }else{
        node_aux->right = recursivedeleteTreeElement(node_aux->right, key);

    }

    return node_aux;
}

void deleteKdTreeElement(KdTree tree, double key[2]){
    KdTreeStruct *tree_aux = (KdTreeStruct *) tree;
    
    if(tree_aux->size > 0){
        tree_aux->root = recursivedeleteTreeElement(tree_aux->root, key);
        tree_aux->size--;
    }

}

void deleteAllElements(NodeKdTree node){
    NodeKDTreeStruct *node_aux = (NodeKDTreeStruct *) node;

    if(node_aux->left != NULL){
        deleteAllElements(node_aux->left);
    }
    if(node_aux->right != NULL){
        deleteAllElements(node_aux->right);
    }

    free(node_aux);
}

void endKdTree(KdTree tree){
    KdTreeStruct *tree_aux = (KdTreeStruct *) tree;

    if(tree_aux->root != NULL){
        deleteAllElements(tree_aux->root);
    }
    free(tree_aux);
}

NodeKdTree findKdTreeNode(NodeKdTree node, double key[2]){
    NodeKDTreeStruct *node_aux = (NodeKDTreeStruct *) node;

    if(node_aux == NULL ||( node_aux->key[1] == key[1] && node_aux->key[0] == key[0])){
        return node_aux;
    }

    if(node_aux->key[node_aux->dimension] > key[node_aux->dimension]){
        return findKdTreeNode(node_aux->left, key);
    }else{
        return findKdTreeNode(node_aux->right, key);
    }
}

Info getKdTreeInfoByKey(KdTree tree, double key[2]){
    KdTreeStruct *tree_aux = (KdTreeStruct *) tree;

    NodeKDTreeStruct *node = findKdTreeNode(tree_aux->root, key);
    
    if(node != NULL){
        return node->info;
    }
    
    return NULL;
}

Info getKdTreeInfo(NodeKdTree node){
    NodeKDTreeStruct *node_aux = (NodeKDTreeStruct *) node;

    return node_aux->info;
}

NodeKdTree getKdTreeNodeLeft(NodeKdTree node){
    NodeKDTreeStruct *node_aux = (NodeKDTreeStruct *) node;

    return node_aux->left;
}

NodeKdTree getKdTreeNodeRight(NodeKdTree node){
    NodeKDTreeStruct *node_aux = (NodeKDTreeStruct *) node;

    return node_aux->right;
}

NodeKdTree getKdTreeRoot(KdTree tree){
    KdTreeStruct *tree_aux = (KdTreeStruct *) tree;

    return tree_aux->root;
}

int getKdTreeSize(KdTree tree){
    KdTreeStruct *tree_aux = (KdTreeStruct *) tree;

    return tree_aux->size;
}

int getKdTreeDimension(NodeKdTree node){
    NodeKDTreeStruct *node_aux = (NodeKDTreeStruct *) node;

    return node_aux->dimension;
}

void recursiveSearchRangeKdTree(List list, NodeKdTree root, double x, double y, double w, double h){
    NodeKDTreeStruct *root_aux = (NodeKDTreeStruct *) root;

    if(root == NULL){
        return;
    }

    if(root_aux->key[0] >= x && root_aux->key[0] <= (x+w)){
        if(root_aux->key[1] >= y && root_aux->key[1] <= (y+h)){
            double *aux = malloc(2*(sizeof(double)));
            aux[0] = root_aux->key[0];
            aux[1] = root_aux->key[1];
            insertListElement(list ,aux);
        }
    }

    double key_aux[2] = {x, y};
    double key_aux2[2] = {x+w, y+h};

    if(key_aux2[root_aux->dimension] >= root_aux->key[root_aux->dimension]){
        recursiveSearchRangeKdTree(list, root_aux->right, x, y, w, h);
    }
    if(key_aux[root_aux->dimension] <= root_aux->key[root_aux->dimension]){
        recursiveSearchRangeKdTree(list, root_aux->left, x, y, w, h);
    }
}

List getKdTreeSearchRange(KdTree tree, double x, double y, double w, double h){
    KdTreeStruct *tree_aux = (KdTreeStruct *) tree;

    List list = createList();
    recursiveSearchRangeKdTree(list, tree_aux->root, x, y, w, h);

    return list;
}

void recursiveSearchRangeRadiusKdTree(List list, NodeKdTree root, double x, double y, double r){
    NodeKDTreeStruct *root_aux = (NodeKDTreeStruct *) root;

    if(root == NULL){
        return;
    }

    if(pow(root_aux->key[0] - x, 2) + pow(root_aux->key[1] - y, 2) <= pow(r,2)){
        double *aux = malloc(2*(sizeof(double)));
        aux[0] = root_aux->key[0];
        aux[1] = root_aux->key[1];
        insertListElement(list ,aux);
    }

    double key_aux[2] = {x-r, y-r};
    double key_aux2[2] = {x+r, y+r};

    if(key_aux2[root_aux->dimension] >= root_aux->key[root_aux->dimension]){
        recursiveSearchRangeRadiusKdTree(list, root_aux->right, x, y, r);
    }
    if(key_aux[root_aux->dimension] <= root_aux->key[root_aux->dimension]){
        recursiveSearchRangeRadiusKdTree(list, root_aux->left, x, y, r);
    }
}

List getKdTreeSearchRangeRadius(KdTree tree, double x, double y, double r){
    KdTreeStruct *tree_aux = (KdTreeStruct *) tree;

    List list = createList();
    recursiveSearchRangeRadiusKdTree(list, tree_aux->root, x, y, r);

    return list;
}

NodeKdTree closestKdTreeNode(double key[2], NodeKdTree one, NodeKdTree two){
    NodeKDTreeStruct *one_aux = (NodeKDTreeStruct *) one;
    NodeKDTreeStruct *two_aux = (NodeKDTreeStruct *) two;

    if(one_aux == NULL){
        return two_aux;
    }else if(two_aux == NULL){
        return one_aux;
    }

    double dist1 = sqrt(pow(key[0] - one_aux->key[0], 2) + pow(key[1] - one_aux->key[1], 2));
    double dist2 = sqrt(pow(key[0] - two_aux->key[0], 2) + pow(key[1] - two_aux->key[1], 2));
    if(dist1 < dist2){
        return one;
    }
    return two;
}

NodeKdTree nearestNeighborKdTree(NodeKdTree root, double key[2]){
    NodeKDTreeStruct *root_aux = (NodeKDTreeStruct *) root;

    NodeKDTreeStruct *nextBranch = NULL;
    NodeKDTreeStruct *otherBranch = NULL;

    if(root == NULL){
        return NULL;
    }

    if(key[root_aux->dimension] < root_aux->key[root_aux->dimension]){
        nextBranch = root_aux->left;
        otherBranch = root_aux->right;
    }else{
        nextBranch = root_aux->right;
        otherBranch = root_aux->left;
    }

    NodeKDTreeStruct *aux = nearestNeighborKdTree(nextBranch, key);
    NodeKDTreeStruct *best = closestKdTreeNode(key, aux, root_aux);

    double radiusSquared = pow(key[0] - best->key[0], 2) + pow(key[1] - best->key[1], 2);
    double distance = key[root_aux->dimension] - root_aux->key[root_aux->dimension];

    if(radiusSquared >= distance * distance){
        aux = nearestNeighborKdTree(otherBranch, key);
        best = closestKdTreeNode(key, aux, best);
    }

    return best;
}

double* getKdTreeMinValue(NodeKdTree root){
    NodeKDTreeStruct *root_aux = (NodeKDTreeStruct *) root;

    if(root == NULL){
        return NULL;
    }

    if(root_aux->left != NULL){
        return getKdTreeMinValue(root_aux->left);
    }

    return root_aux->key;
}

double* getKdTreeMaxValue(NodeKdTree root){
    NodeKDTreeStruct *root_aux = (NodeKDTreeStruct *) root;

    if(root == NULL){
        return NULL;
    }

    if(root_aux->left != NULL){
        return getKdTreeMinValue(root_aux->right);
    }

    return root_aux->key;
}