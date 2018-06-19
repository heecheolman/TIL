//
//  main.c
//  Heap
//
//  Created by 김희철 on 2018. 6. 20..
//  Copyright © 2018년 Heekim. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

#define MAX_ELEMENT 100

typedef int element;
// 힙 구조체 정의
typedef struct HeapType {
    element heapTree[MAX_ELEMENT];
    int heapSize;
} HeapType;


// 힙을 생성후 반환
HeapType * createHeap() {
    HeapType * heap = (HeapType *)malloc(sizeof(HeapType));
    heap->heapSize = 0;
    return heap;
}

// 힙에 데이터 삽입
void insertHeap(HeapType * heap, element data) {
    // 삽입하기위해 공백노드가 들어갈 자리를 만들고 그 위치가 cur이 됨
    int cur = ++(heap->heapSize);
    // cur이 최상단이 아니거나, 삽입할 데이터가 부모노드의 데이터보다 크다면 계속 반복
    // 부모노드의 데이터보다 크다는것은 아직 최대히프에 만족하지못함
    while(cur != 1 && data > heap->heapTree[cur / 2]) {
        // 들어온 데이터가 큰 경우이므로 기존의 부모노드가 자식노드로 밀려남 ( 정확히 여기선 덮어쓴다는 표현이 맞음 )
        heap->heapTree[cur] = heap->heapTree[cur / 2];
        // 부모노드로 이동
        cur /= 2;
    }
    // 반복문을 벗어낫다는것은 삽입될 해당 데이터가 적절한위치에 있는것이므로 삽입
    heap->heapTree[cur] = data;
}

element deleteHeap(HeapType * heap) {
    // data 는 최상위노드의 데이터 반환을 위한 저장용
    element data = heap->heapTree[1];
    // temp 는 완전이진트리의 마지막 노드 저장용
    element temp = heap->heapTree[heap->heapSize];
    // 최상위 노드
    int parent = 1;
    // 최상위 노드의 왼쪽자식노드, 오른쪽도 있는경우는 while 문의 if문에서 비교후 3으로 증가예정
    int child = 2;
    // 노드 하나를 제거하므로 사이즈를 1줄임
    (heap->heapSize)--;
    // child 가 힙사이즈와 같거나 작다면 계속 반복
    // 비교할 대상이 아직 남아있는것임
    while(child <= heap->heapSize) {
        // child < heap->heapSize, 자식노드가 힙사이즈보다 작다. 즉, 오른쪽 자식노드가 존재한다
        // 오른쪽 자식노드가 존재하고, 왼쪽자식노드보다 오른쪽자식노드가 값이 더크다면 오른쪽 서브트리로 이동
        if(child < heap->heapSize && heap->heapTree[child] < heap->heapTree[child + 1]) {
            // 이동
            child++;
        }
        // 만약 아까저장한 완전이진트리의 값이 최상위노드의 가장 큰 값을 갖는 노드보다 크다면
        // temp 는 최상위노드에 위치하면 됨, 반복문을 벗어남
        if(temp >= heap->heapTree[child]) {
            break;
        // 그렇지않다면
        // 부모노드와 자식노드를 위치를 계속 바꾼다
        } else {
            heap->heapTree[parent] = heap->heapTree[child];
            parent = child;
            child *= 2;
        }
    }
    // 결정된 자리에 temp 삽입
    heap->heapTree[parent] = temp;
    // 최상위 데이터 반환
    return data;
}

void printHeap(HeapType * heap) {
    printf("Heap : ");
    for(int i = 1; i < heap->heapSize + 1; i++) {
        printf("[%d] ", heap->heapTree[i]);
    }
    printf("\n");
}

int main(void) {
    int n;
    element data;
    
    HeapType * heap = createHeap();
    insertHeap(heap, 10);
    insertHeap(heap, 45);
    insertHeap(heap, 19);
    insertHeap(heap, 11);
    insertHeap(heap, 96);
    
    printHeap(heap);
    
    n = heap->heapSize;
    for(int i = 1; i < n + 1; i++) {
        data = deleteHeap(heap);
        printf("\n delete : [%d] ", data);
    }
}
/* 출력결과
 
 Heap : [96] [45] [19] [10] [11]
 
 delete : [96]
 delete : [11]
 delete : [10]
 delete : [45]
 delete : [19]
 
 */
