//
//  main.c
//  ThreadBinaryTree
//
//  Created by 김희철 on 2018. 6. 20..
//  Copyright © 2018년 Heekim. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

typedef char element;


// 새로운 트리노드 정의
typedef struct TreeNode {
    element data;
    struct TreeNode * left;
    struct TreeNode * right;
    int isThread; // 추가
} TreeNode;

// 트리노드를 생성하고 반환하는 함수 기존과 별다를것이 없다
TreeNode * createTreeNode(element data, TreeNode * leftNode, TreeNode * rightNode, int isThread) {
    TreeNode * newNode = (TreeNode *)malloc(sizeof(TreeNode));
    newNode->data = data;
    newNode->left = leftNode;
    newNode->right = rightNode;
    newNode->isThread = isThread;
    return newNode;
}

// 중위후속자를 찾는 함수
TreeNode * findThreadSuccessor(TreeNode * target) {
    // 해당 노드의 오른쪽자식노드를 thread 에 저장
    TreeNode * thread = target->right;
    // isTread 가 true 거나, thread 가 NULL 이라면
    // thread 가 NULL 이라는것은 가장 오른쪽 노드(마지막)임 --> NULL 을 반환하므로 추후의 threadInorder함수의 종료를 뜻함
    if(target->isThread || !thread) {
/*  if(!thread || target->isThread)
    보통 다른 블로그나 다른 코드를보면 주석문처럼 조건문을 주었는데
    내 생각은 조금 달랐다.
    OR 조건문은 첫번째 가 true 이면 오른쪽은 실행되지않는데
    사실상 왼쪽노드로 계속이동했다면 isThread가 대부분 true 이므로
    먼저써주는게 더 효율적이지 않을까 싶다. 어디까지나 내 생각.
 */
        return thread;
    }
    // 위의 조건문을 통과했고 thread 의 왼쪽 자식노드가 존재한다면 계속해서 이동
    // README.md 의 설명문에 있는 그림에서 E 노드의 과정에 속함
    // E 노드는 왼쪽자식노드인 F가 존재하므로 계속이동
    while(thread->left) {
        thread = thread->left;
    }
    // 반환
    return thread;
}

// 스레드 중위순회
void threadInorder(TreeNode * root) {
    // 순회를 위한 target 을 저장한다.
    TreeNode * target;
    target = root;
    // 가장왼쪽 노드로 이동, L 의 과정
    while(target->left) {
        target = target->left;
    }
    do {
        // 데이터를 읽음, D 의 과정 ( 소비 )
        printf("%c ", target->data);
        // 해당 노드의 중위후속자를 찾는다 ( 공급 )
        target = findThreadSuccessor(target);
        // target이 NULL 일경우 벗어남, 가장 마지막 노드인 G 일경우임
    } while(target);
}

int main(void) {
    TreeNode * n7 = createTreeNode('D', NULL, NULL, 0);
    TreeNode * n6 = createTreeNode('C', NULL, NULL, 1);
    TreeNode * n5 = createTreeNode('B', NULL, NULL, 1);
    TreeNode * n4 = createTreeNode('A', NULL, NULL, 1);
    
    TreeNode * n3 = createTreeNode('/', n6, n7, 0);
    TreeNode * n2 = createTreeNode('*', n4, n5, 0);
    
    TreeNode * n1 = createTreeNode('-', n2, n3, 0);
    
    /* 트리모양
     
                (-)
               /   \
             (*)   (/)
            /   \  /  \
          (A)  (B)(C) (D)
     
     */
    
    // 중위후속자를 등록해준다!
    n4->right = n2;
    n5->right = n1;
    n6->right = n3;
    
    printf("\n 스레드 이진트리 중위순회 >> ");
    threadInorder(n1);
    printf("\n");
}

/* 출력결과
 
 스레드 이진트리 중위순회 >> A * B - C / D
 
 */
