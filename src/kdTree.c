#include <stdio.h>
#include <stdlib.h>
#include "kdTree.h"

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

        if(node_aux->right->key[node_aux->right->dimension] < key[node_aux->right->dimension]){
            recursiveInsertRight(tree_aux, node_aux->right, info, key);

        }else{
            recursiveInsertLeft(tree_aux, node_aux->right, info, key);
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
        return node_aux;
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

void deleteKdTree(KdTree tree){
    KdTreeStruct *tree_aux = (KdTreeStruct *) tree;

    if(tree_aux->root != NULL){
        deleteAllElements(tree_aux->root);
    }

    free(tree_aux);
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

NodeKdTree getRootKdTree(KdTree tree){
    KdTreeStruct *tree_aux = (KdTreeStruct *) tree;

    return tree_aux->root;
}

void printTree(NodeKDTreeStruct *root){
if(root == NULL){
    return;
}

printTree(root->left);
printf("[%lf, %lf] ->%d |",root->key[0], root->key[1], root->dimension);
printTree(root->right);


}

int main(){
    KdTree arv = createKdTree();
    KdTreeStruct *aux = (KdTreeStruct *) arv;
    int ia = 2;
    void* i = (void *) ia;
    double a[2] = {7, 2};
    double b[2] = {5, 4};
    double c[2] = {9, 6};
    double d[2] = {2, 3};
    double e[2] = {4, 7};
    double f[2] = {8, 1};

    // printTree(aux->root);
    // printf("\n");
 
    insertKdTreeElement(arv, i, a);
    insertKdTreeElement(arv, i, b);
    // printTree(aux->root);
    // printf("\n");
    insertKdTreeElement(arv, i, c);
    insertKdTreeElement(arv, i, d);
    insertKdTreeElement(arv, 9, e);
    insertKdTreeElement(arv, i, f);


    printTree(aux->root);
    printf("\n");


    int ass = (int) getKdTreeInfoByKey(arv, e);

    printf("%d \n",ass);

    deleteKdTreeElement(arv, a);

    printTree(aux->root);
    printf("\n");

    deleteKdTree(arv);
}