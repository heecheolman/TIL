//
//  main.c
//  LinkedBinaryTree
//
//  Created by 김희철 on 2018. 6. 17..
//  Copyright © 2018년 Heekim. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

typedef char element;

// 이진트리의 노드
typedef struct TreeNode {
    element data;
    struct TreeNode * left;
    struct TreeNode * right;
} TreeNode;

// 노드를 만들고 반환하는 함수
// data와 연결할 왼쪽의 노드, 연결할 오른쪽의 노드를 받는다.
TreeNode * makeRootNode(element data, TreeNode * leftNode, TreeNode * rightNode) {
    TreeNode * root = (TreeNode *)malloc(sizeof(TreeNode));
    root->data = data;
    root->left = leftNode;
    root->right = rightNode;
    return root;
}

// 전위순회 DLR
void preOrder(TreeNode * root) {
    if(root) {
        printf("%c ", root->data);
        preOrder(root->left);
        preOrder(root->right);
    }
}

// 중위순회 LDR
void inOrder(TreeNode * root) {
    if(root) {
        inOrder(root->left);
        printf("%c ", root->data);
        inOrder(root->right);
    }
}

// 후위순회 LRD
void postOrder(TreeNode * root) {
    if(root) {
        postOrder(root->left);
        postOrder(root->right);
        printf("%c ", root->data);
    }
}

int main(void) {
    TreeNode * n7 = makeRootNode('D', NULL, NULL);
    TreeNode * n6 = makeRootNode('C', NULL, NULL);
    TreeNode * n5 = makeRootNode('B', NULL, NULL);
    TreeNode * n4 = makeRootNode('A', NULL, NULL);
    TreeNode * n3 = makeRootNode('+', n6, n7);
    TreeNode * n2 = makeRootNode('*', n4, n5);
    TreeNode * n1 = makeRootNode('-', n2, n3);
    
    preOrder(n1); printf("\n");
    inOrder(n1);  printf("\n");
    postOrder(n1); printf("\n");
    
    
    /* 트리모양
     
     
            -
        *        +
     A     B   C    D
     
     
     */
    
    /* 출력결과
     
     - * A B + C D
     A * B - C + D
     A B * C D + -
     
     */
}
