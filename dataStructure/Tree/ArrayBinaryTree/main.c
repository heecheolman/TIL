//
//  main.c
//  ArrayBinaryTree
//
//  Created by 김희철 on 2018. 6. 17..
//  Copyright © 2018년 Heekim. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 16

typedef int element;
typedef struct TreeNode {
    element data;
} TreeNode;

// Tree 구조체
typedef struct Tree {
    TreeNode TreeArray[MAX_SIZE];
    int cur;
} Tree;

// 트리를 동적할당 후 반환
Tree * createTree() {
    Tree * tree = (Tree *)malloc(sizeof(Tree));
    tree->cur = 1;
    for(int i = 0; i < MAX_SIZE; i++) {
        tree->TreeArray[i].data = 0;
    }
    return tree;
}

// 트리에 노드 삽입
void insertTree(Tree * tree, element data) {
    if(tree->cur == MAX_SIZE) {
        printf("Tree is Full! \n");
    }
    tree->TreeArray[tree->cur].data = data;
    (tree->cur)++;
}

// 트리 삭제, 삭제한 노드의 데이터를 반환
element removeTree(Tree * tree) {
    if(tree->cur == 0) {
        printf("Tree is Empty! \n");
    }
    element removeData = tree->TreeArray[tree->cur].data;
    (tree->cur)--;
    return removeData;
}

// 입력된 위치의 오른쪽 자식노드 출력
void printRightChild(Tree * tree, int position) {
    if(position * 2 > MAX_SIZE) {
        printf("this node is leaf node!\n");
        return;
    }
    printf("Tree[%d] Right Child NodeData is : %d\n", position, tree->TreeArray[position * 2 + 1].data);
}

// 입력된 위치의 왼쪽 자식노드 출력
void printLeftChild(Tree * tree, int position) {
    if(position * 2 > MAX_SIZE) {
        printf("this node is leaf node! \n");
        return;
    }
    printf("Tree[%d] Left Child NodeData is : %d\n", position, tree->TreeArray[position * 2].data);
}

// 입력된 위치의 부모 노드 출력
void printParent(Tree * tree, int position) {
    if(position == 1) {
        printf("Root Node! \n");
        return;
    }
    int parentIndex = position / 2;
    printf("Tree[%d] Parent NodeData is : %d\n", position, tree->TreeArray[parentIndex].data);
}

// 트리의 모든 노드를 순회하며 출력
void treeTraversal(Tree * tree) {
    int target = 1;
    printf("\n Tree ==> ");
    for(int i = target; i < MAX_SIZE; i++) {
        printf(" %d", tree->TreeArray[i].data);
    }
    printf("\n");
}

int main(void) {
    Tree * tree = createTree();
    insertTree(tree, 1);
    insertTree(tree, 2);
    insertTree(tree, 3);
    insertTree(tree, 4);
    insertTree(tree, 5);
    insertTree(tree, 6);
    insertTree(tree, 7);
    insertTree(tree, 8);
    insertTree(tree, 9);
    insertTree(tree, 10);
    insertTree(tree, 11);
    insertTree(tree, 12);
    insertTree(tree, 13);
    insertTree(tree, 14);
    insertTree(tree, 15);
    
    treeTraversal(tree);
    
    printParent(tree, 5);
    printParent(tree, 6);
    printParent(tree, 7);
    printParent(tree, 8);
    printParent(tree, 1);
    
    printLeftChild(tree, 5);
    printRightChild(tree, 5);
    
    printLeftChild(tree, 7);
    printRightChild(tree, 7);
    
    printLeftChild(tree, 13);
    
    /* 트리모양
     
     

            1
       2          3
    4     5     6    7
   8  9 10 11 12 13 14 15
     
    
    
    */
    /* 출력결과
     
     Tree ==>  1 2 3 4 5 6 7 8 9 10 11 12 13 14 15
     Tree[5] Parent NodeData is : 2
     Tree[6] Parent NodeData is : 3
     Tree[7] Parent NodeData is : 3
     Tree[8] Parent NodeData is : 4
     Root Node!
     Tree[5] Left Child NodeData is : 10
     Tree[5] Right Child NodeData is : 11
     Tree[7] Left Child NodeData is : 14
     Tree[7] Right Child NodeData is : 15
     this node is leaf node!

    */
}
