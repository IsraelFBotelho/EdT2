// #include <stdio.h>
// #include <stdlib.h>
// #include "binaryTree.h"

// typedef struct nodeTreeStruct{
//     Info info;
//     double key[2][2];
//     struct nodeTreeStruct* left;
//     struct nodeTreeStruct* right;
// }NodeTreeStruct;

// typedef struct treeStruct{
//     NodeTreeStruct *root;
//     int size;
//     int visit;
// }TreeStruct;

// void recursiveInsertRight(TreeStruct *tree, NodeTreeStruct *node, Info info);
// void recursiveInsertLeft(TreeStruct *tree, NodeTreeStruct *node, Info info);

// Tree createTree(){
//     TreeStruct *new = (TreeStruct *) malloc(sizeof(TreeStruct));

//     new->root = NULL;
//     new->size = 0;
//     new->visit = 0;

//     return new;
// }

// void recursiveInsertRight(TreeStruct *tree, NodeTreeStruct *node, Info info){
//     tree->visit++;

//     if(node->left == NULL){
//         NodeTreeStruct *new = (NodeTreeStruct *) malloc(sizeof(NodeTreeStruct));

//         new->info = info;
//         // new->key = ??????????;
//         new->left = NULL;
//         new->right = NULL;
//         node->left = new;
//     }else{
//         if(node->right->key < 'alguma coisa'){
//             recursiveInsertRight(tree, node->right, info);
//         }else{
//             recursiveInsertLeft(tree, node->left, info);
//         }
//     }
// }

// void recursiveInsertLeft(TreeStruct *tree, NodeTreeStruct *node, Info info){
//     tree->visit++;
    
//     if(node->left == NULL){
//         NodeTreeStruct *new = (NodeTreeStruct *) malloc(sizeof(NodeTreeStruct));

//         new->info = info;
//         // new->key = ??????????;
//         new->left = NULL;
//         new->right = NULL;
//         node->left = new;
//     }else{
//         if(node->left->key > 'alguma coisa'){
//             recursiveInsertLeft(tree, node->left, info);
//         }else{
//             recursiveInsertRight(tree, node->right, info);
//         }
//     }

// }

// void insertTreeElement(Tree tree, Info info){
//     TreeStruct *tree_aux = (TreeStruct *) tree;
    
//     if(tree_aux->root == NULL){
//         NodeTreeStruct *new = (NodeTreeStruct *) malloc(sizeof(NodeTreeStruct));

//         new->info = info;
//         // new->key = ??????????;
//         new->left = NULL;
//         new->right = NULL;
//         tree_aux->root = new;
//     }else{
//         if(tree_aux->root->key > 'alguma coisa'){
//             recursiveInsertLeft(tree, tree_aux->root, info);
//         }else{
//             recursiveInsertRight(tree, tree_aux->root, info);
//         }
//     }

//     tree_aux->size++;
// }

// NodeTree minTreeValue(NodeTree node){
//     NodeTreeStruct *node_aux = (NodeTreeStruct *) node;

//     if(node_aux != NULL && node_aux->left != NULL){
//         node_aux = minTreeValue(node_aux->left);
//     }

//     return node_aux;
// }

// NodeTree recursivedeleteTreeElement(NodeTree node, double key[2]){
//     NodeTreeStruct *node_aux = (NodeTreeStruct *) node;

//     if(node_aux == NULL){
//         return node_aux;
//     }

//     if(key < node_aux->key){
//         node_aux->left = recursivedeleteTreeElement(node_aux->left, key);
//     } else if (key > node_aux->key){
//         node_aux->right = recursivedeleteTreeElement(node_aux->right, key);
//     }else{
//         if(node_aux->left == NULL){
//             NodeTreeStruct *aux = node_aux->right;
//             free(node_aux);
//             return aux;
//         }else if(node_aux->right == NULL){
//             NodeTreeStruct *aux = node_aux->left;
//             free(node_aux);
//             return aux;
//         }

//         NodeTreeStruct *aux = (NodeTreeStruct *) minTreeValue(node_aux->right);
//         node_aux->key[1] = aux->key[1];
//         node_aux->key[0] = aux->key[0];
//         node_aux->info = aux->info;

//         node_aux->right = recursivedeleteTreeElement(node_aux->right, node_aux->key);
//     }


//     return node_aux;
// }

// void deleteTreeElement(Tree tree, double key[2]){
//     TreeStruct *tree_aux = (TreeStruct *) tree;
//     tree_aux->root = recursivedeleteTreeElement(tree_aux->root, key);
// }