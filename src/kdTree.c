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
    int visit;
}KdTreeStruct;

void recursiveInsertRight(KdTree tree, NodeKDTreeStruct *node, Info info, double key[2]);
void recursiveInsertLeft(KdTree tree, NodeKdTree node, Info info, double key[2]);

KdTree createKdTree(){
    KdTreeStruct *new = (KdTreeStruct *) malloc(sizeof(KdTreeStruct));

    new->root = NULL;
    new->size = 0;
    new->visit = 0;

    return new;
}

void recursiveInsertRight(KdTree tree, NodeKDTreeStruct *node, Info info, double key[2]){
    KdTreeStruct *tree_aux = (KdTreeStruct *) tree;
    NodeKDTreeStruct *node_aux = (NodeKDTreeStruct *) node;

    tree_aux->visit++;

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
            recursiveInsertLeft(tree_aux, node_aux->right, info, key);

        }else{
            recursiveInsertRight(tree_aux, node_aux->right, info, key);
        }

    }
}

void recursiveInsertLeft(KdTree tree, NodeKdTree node, Info info, double key[2]){
    KdTreeStruct *tree_aux = (KdTreeStruct *) tree;
    NodeKDTreeStruct *node_aux = (NodeKDTreeStruct *) node;

    tree_aux->visit++;
    
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
            recursiveInsertLeft(tree_aux, node_aux->left, info, key);

        }else{
            recursiveInsertRight(tree_aux, node_aux->left, info, key);
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
            recursiveInsertLeft(tree, tree_aux->root, info, key);

        }else{
            recursiveInsertRight(tree, tree_aux->root, info, key);
        }
    }

    tree_aux->size++;
}

NodeKdTree minTreeValue(NodeKdTree node){
    NodeKDTreeStruct *node_aux = (NodeKDTreeStruct *) node;

    if(node_aux != NULL && node_aux->left != NULL){
        node_aux = minTreeValue(node_aux->left);
    }

    return node_aux;
}

NodeKdTree recursivedeleteTreeElement(NodeKdTree node, double key[2]){
    NodeKDTreeStruct *node_aux = (NodeKDTreeStruct *) node;

    if(node_aux == NULL){
        return NULL;
    }

    if(key[node_aux->dimension] < node_aux->key[node_aux->dimension]){
        node_aux->left = recursivedeleteTreeElement(node_aux->left, key);

    } else if (key[node_aux->dimension] > node_aux->key[node_aux->dimension]){
        node_aux->right = recursivedeleteTreeElement(node_aux->right, key);

    }else{
        if(node_aux->left == NULL){
            NodeKDTreeStruct *aux = node_aux->right;
            free(node_aux);
            return aux;

        }else if(node_aux->right == NULL){
            NodeKDTreeStruct *aux = node_aux->left;
            free(node_aux);
            return aux;
        }

        NodeKDTreeStruct *aux = (NodeKDTreeStruct *) minTreeValue(node_aux->right);
        node_aux->key[1] = aux->key[1];
        node_aux->key[0] = aux->key[0];
        node_aux->info = aux->info;

        node_aux->right = recursivedeleteTreeElement(node_aux->right, node_aux->key);
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

void deleteAllElements(KdTree tree, NodeKdTree node){
    NodeKDTreeStruct *node_aux = (NodeKDTreeStruct *) node;
    KdTreeStruct *tree_aux = (KdTreeStruct *) tree;

    if(node_aux->left != NULL){
        tree_aux->visit++;
        deleteAllElements(tree, node_aux->left);
    }
    if(node_aux->right != NULL){
        tree_aux->visit++;
        deleteAllElements(tree, node_aux->right);
    }

    free(node_aux);
}

int deleteKdTree(KdTree tree){
    KdTreeStruct *tree_aux = (KdTreeStruct *) tree;
    int visit = 0;

    if(tree_aux->root != NULL){
        tree_aux->visit++;
        deleteAllElements(tree, tree_aux->root);
    }
    
    visit = tree_aux->visit;
    free(tree_aux);

    return visit;
}

NodeKdTree findKdNode(NodeKdTree node, double key[2]){
    NodeKDTreeStruct *node_aux = (NodeKDTreeStruct *) node;

    if(node_aux == NULL ||( node_aux->key[1] == key[1] && node_aux->key[0] == key[0])){
        return node_aux;
    }

    if(node_aux->key[node_aux->dimension] < key[node_aux->dimension]){
        return findKdNode(node_aux->right, key);
    }else{
        return findKdNode(node_aux->left, key);
    }
}

Info getKdTreeInfoByKey(KdTree tree, double key[2]){
    KdTreeStruct *tree_aux = (KdTreeStruct *) tree;

    NodeKDTreeStruct *node = findKdNode(tree_aux->root, key);
    
    if(node != NULL){
        return node->info;
    }
    printf("Cheguei EU NAO EXISTO\n");
    return NULL;
}

Info getKdTreeInfo(NodeKdTree node){
    NodeKDTreeStruct *node_aux = (NodeKDTreeStruct *) node;

    return node_aux->info;
}

NodeKdTree getKdNodeLeft(KdTree tree, NodeKdTree node){
    NodeKDTreeStruct *node_aux = (NodeKDTreeStruct *) node;
    KdTreeStruct *tree_aux = (KdTreeStruct *) tree;

    tree_aux->visit++;
    return node_aux->left;
}

NodeKdTree getKdNodeRight(KdTree tree, NodeKdTree node){
    NodeKDTreeStruct *node_aux = (NodeKDTreeStruct *) node;
    KdTreeStruct *tree_aux = (KdTreeStruct *) tree;

    tree_aux->visit++;
    return node_aux->right;
}

NodeKdTree getKdRoot(KdTree tree){
    KdTreeStruct *tree_aux = (KdTreeStruct *) tree;

    return tree_aux->root;
}

int getKdTreeSize(KdTree tree){
    KdTreeStruct *tree_aux = (KdTreeStruct *) tree;

    return tree_aux->size;
}

int getKdTreeVisit(KdTree tree){
    KdTreeStruct *tree_aux = (KdTreeStruct *) tree;

    return tree_aux->visit;
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

List getSearchRangeKdTree(KdTree tree, double x, double y, double w, double h){
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

List getSearchRangeRadiusKdTree(KdTree tree, double x, double y, double r){
    KdTreeStruct *tree_aux = (KdTreeStruct *) tree;

    List list = createList();
    recursiveSearchRangeRadiusKdTree(list, tree_aux->root, x, y, r);

    return list;
}

NodeKdTree closestKdNode(double key[2], NodeKdTree one, NodeKdTree two){
    NodeKDTreeStruct *one_aux = (NodeKDTreeStruct *) one;
    NodeKDTreeStruct *two_aux = (NodeKDTreeStruct *) two;

    if(one_aux == NULL){
        return two_aux;
    }else if(two_aux == NULL){
        return one_aux;
    }

    double dist1 = pow(key[0] - one_aux->key[0], 2) + pow(key[1] - one_aux->key[1], 2);
    double dist2 = pow(key[0] - two_aux->key[0], 2) + pow(key[1] - two_aux->key[1], 2);
    if(dist1 < dist2){
        return one;
    }
    return two;
}

NodeKdTree nearestNeighborKdTree(KdTree tree, NodeKdTree root, double key[2]){
    NodeKDTreeStruct *root_aux = (NodeKDTreeStruct *) root;
    KdTreeStruct *tree_aux = (KdTreeStruct *) tree;

    NodeKDTreeStruct *nextBranch = NULL;
    NodeKDTreeStruct *otherBranch = NULL;

    if(root == NULL){
        return NULL;
    }
    
    tree_aux->visit++;

    if(key[root_aux->dimension] < root_aux->key[root_aux->dimension]){
        nextBranch = root_aux->left;
        otherBranch = root_aux->right;
    }else{
        nextBranch = root_aux->right;
        otherBranch = root_aux->left;
    }

    NodeKDTreeStruct *aux = nearestNeighborKdTree(tree, nextBranch, key);
    NodeKDTreeStruct *best = closestKdNode(key, aux, root_aux);

    double radiusSquared = sqrt(pow(key[0] - best->key[0], 2) + pow(key[1] - best->key[1], 2));
    double distance = key[root_aux->dimension] - root_aux->key[root_aux->dimension];

    if(radiusSquared >= distance * distance){
        aux = nearestNeighborKdTree(tree, otherBranch, key);
        best = closestKdNode(key, aux, best);
    }

    return best;
}
