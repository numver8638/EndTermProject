#pragma once

// 리스트 원소 구조체
typedef struct _Element {
	void* Value; // 값을 가리키는 포인터.
	struct _Element* Next; // 다음 원소
} Element, *ElementRef;

// 리스트 구조체
typedef struct __LinkedList {
	int Count; // 리스트 원소 개수
	ElementRef Head, Tail; // 리스트의 처음(Head)과 끝(Tail)
} *LinkedListRef;

// 리스트 순회 도우미
#define FOREACH_LIST(listRef, element) for (ElementRef element = (listRef)->Head; element != NULL; element = element->Next)

LinkedListRef List_Create();

void List_Append(LinkedListRef, void*);

void List_Destroy(LinkedListRef, void(*)(void*));
