//
//  main.c
//  BinarySearchTree
//
//  Created by 김희철 on 2018. 6. 18..
//  Copyright © 2018년 Heekim. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

typedef char element;

typedef struct TreeNode {
    element data;
    struct TreeNode * left;
    struct TreeNode * right;
} TreeNode;


// 노드를 트리에 넣는 함수
TreeNode * insertNode (TreeNode * target, element data) {
    TreeNode * newNode;
    // target 이 NULL 이라면, 동적할당
    if (!target) {
        newNode = (TreeNode *)malloc(sizeof(TreeNode));
        newNode->data = data;
        newNode->right = NULL;
        newNode->left = NULL;
        // 새 노드 반환
        return newNode;
    // 삽입하려는 데이터가 더 작다면 왼쪽 서브트리로 삽입해야함
    } else if (target->data > data) {
        target->left = insertNode(target->left, data);
    // 삽입하려는 데이터가 더 크다면 오른쪽 서브트리로 삽입해야함
    } else if (target->data < data) {
        target->right = insertNode(target->right, data);
    // 그렇지않으면 이미 존재하는 데이터임
    } else {
        printf("이미 존재하는 데이터입니다\n");
    }
    return target;
}

// 트리의 노드를 삭제하는 함수
void deleteNode (TreeNode * root, element data) {
    TreeNode * target;
    TreeNode * parent;
    TreeNode * child;
    TreeNode * succ;
    TreeNode * succParent;
    
    parent = NULL;
    target = root;
    // 해당 data 가 들어있는 노드를 찾는 과정
    // target 이 NULL 이 아니고 data 가 일치할때까지 반복
    while (target && target->data != data) {
        parent = target;
        if (target->data > data) {
            target = target->left;
        } else {
            target = target->right;
        }
    }
    // 만약 찾고자하는 데이터가 없으면 종료
    if (!target) {
        printf("존재하는 데이터가 없습니다 \n");
        return;
    }
    
    /* 1. 단말노드인경우
          부모노드의 left 와 right 을 NULL 로 설정 */
    
    if (!target->left && !target->right) {
        if (parent) {
            if (parent->left == target) {
                parent->left = NULL;
            } else {
                parent->right = NULL;
            }
        } else {
            root = NULL;
        }
        
        
    /* 2. 자식노드가 하나인경우
          삭제하려는 노드의 자식노드가 부모노드의 자식이됨 */
        
    } else if (!target->left || !target->right) {
        if (target->left) {
            child = target->left;
        } else {
            child = target->right;
        }
        
        // 부모노드가 있는 경우 연결
        if (parent) {
            if (parent->left == target) {
                parent->left = child;
            } else {
                parent->right = child;
            }
        // 부모노드가 없는경우 최상위 노드이므로 최상위 노드는 child 가 됨
        } else {
            root = child;
        }
        
        
    /* 3. 자식노드가 두개인경우
          삭제하는 노드의 후계자를 찾아 연결
          (1) 왼쪽 서브트리의 가장 오른쪽 노드를 후계자로 등록하는 방법과
          (2) 오른쪽 서브트리의 가장 왼쪽 노드를 후계자로 등록하는 방법 중
             (1)의 방법임 */
        
    } else {
        // succParent 는 후계자의 부모, 임시로 등록
        succParent = target;
        // succ 은 후계자가 될 노드, (1)의 방법이므로 왼쪽 서브트리의 최상단 노드 등록
        succ = succParent->left;
        // 오른쪽으로 계속 이동.
        while (succ->right) {
            // 이동하면서 후계자의 부모를 저장
            succParent = succ;
            // 이동
            succ = succ->right;
        }
        
        // 후계자부모의 왼쪽이 후계자와 동일하다면, 후계자부모의 왼쪽 자식노드를 후계자의 왼쪽노드로 등록
        if (succParent->left == succ) {
            succParent->left = succ->left;
        // 후계자부모의 오른쪽이 후계자와 동일하다면, 후계자부모의 오른쪽 자식노드를 후계자의 왼쪽노드로 등록
        } else {
            succParent->right = succ->left;
        }
        // 이제 후계자가 될 가장 오른쪽 노드가 삭제될 노드에 위치하게됨
        // 데이터를 먼저 옮기고
        target->data = succ->data;
        // 주소 대입
        target = succ;
    }
    // 이후 노드 삭제
    free(target);
}

// data 값에 일치하는 Node의 위치를 탐색
TreeNode * searchNode (TreeNode * root, element data) {
    TreeNode * target = root;
    // target 이 NULL 일때까지 반복
    while (target) {
        // target 의 데이터가 찾고자하는 data 보다 크다면 왼쪽으로
        if (target->data > data) {
            target = target->left;
        // target 의 데이터가 찾고자하는 data 보다 작다면 오른쪽으로
        } else if (target->data < data) {
            target = target->right;
        // 일치하면 return
        } else if (target->data == data) {
            return target;
        }
    }
    // 위의 반복문을 벗어난다는것은 데이터가 없다는 것
    printf("일치하는 데이터가 없습니다. \n");
    return target;
}

// 중위순회
void printInorder (TreeNode * root) {
    TreeNode * target = root;
    if (target) {
        printInorder(target->left);
        printf("%c ", target->data);
        printInorder(target->right);
    }
}

void menu () {
    printf("\n ------------------- \n");
    printf("\n\t 1. 트리출력");
    printf("\n\t 2. 문자 삽입");
    printf("\n\t 3. 문자 삭제");
    printf("\n\t 4. 문자 검색");
    printf("\n\t 5. 종료");
    printf("\n ------------------- \n");
    printf("\n 메뉴입력 >>> ");
}

int main(void) {
    TreeNode * root = NULL;
    TreeNode * foundedNode = NULL;
    char choice;
    element data;
    
    root = insertNode(root, 'G');
    insertNode(root, 'I');
    insertNode(root, 'H');
    insertNode(root, 'D');
    insertNode(root, 'B');
    insertNode(root, 'M');
    insertNode(root, 'N');
    insertNode(root, 'A');
    insertNode(root, 'J');
    insertNode(root, 'E');
    insertNode(root, 'Q');
    
    while(1) {
        menu();
        choice = getchar(); getchar();
        switch(choice) {
            case '1':
                printf("\t [이진트리 출력]  ");
                printInorder(root); printf("\n");
                break;
            case '2':
                printf("삽입할 문자를 입력하세요 : ");
                data = getchar();getchar();
                insertNode(root, data);
                break;
            case '3':
                printf("삭제할 문자를 입력하세요 : ");
                data = getchar(); getchar();
                deleteNode(root, data);
                break;
            case '4':
                printf("찾을 문자를 입력하세요 : ");
                data = getchar(); getchar();
                foundedNode = searchNode(root, data);
                if (foundedNode) {
                    printf("\n %c 를 찾았습니다! \n", foundedNode->data);
                } else {
                    printf("\n 문자를 찾지 못했습니다 \n ");
                }
                break;
            case '5':
                return 0;
            default:
                printf("없는 메뉴입니다. 메뉴를 다시 선택하세요.\n");
                break;
        }
    }
}
