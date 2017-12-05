#include "LinkedList.h"

#include <stdlib.h>

/*
 * 자료 구조:
 *	처음과 끝을 가리키는 변수를 두어 맨 끝에 리스트를 추가하기 편리하게 만듦.
 *	리스트는 struct _Element 안 Next 변수로 연결되며, 끝은 NULL로 나타냄.
 *
 * struct _Element -> | Value , Next | <- Head
 *                               v
 * struct _Element -> | Value , Next |
 *                               v
 * struct _Element -> | Value , Next |
 *                               v
 * struct _Element -> | Value , Next | <- Tail
 *                               v
 *                              NULL
 */

/*
 * LinkedListRef List_Create()
 * - 링크드 리스트 생성 함수
 * - 반환값: 링크드 리스트
 */
LinkedListRef List_Create() {
	LinkedListRef ref =  malloc(sizeof(struct __LinkedList));

	ref->Count = 0;
	ref->Head = NULL;
	ref->Tail = NULL;

	return ref;
}

/*
 * void List_Append(LinkedListRef list, void* value)
 * - 링크드 리스트에 값을 추가하는 함수.
 * - 입력값:
 *   - list: 링크드 리스트
 *   - value: 저장하고 싶은 값이 있는 변수의 포인터
 */
void List_Append(LinkedListRef list, void* value) {
	// 리스트 원소 생성.
	ElementRef element = malloc(sizeof(Element));
	element->Value = value;
	element->Next = NULL;

	if (list->Tail == NULL) {
		list->Head = list->Tail = element;
	}
	else {
		list->Tail->Next = element;
		list->Tail = element;
	}

	++(list->Count);
}

/*
 * void List_Destroy(LinkedListRef list, void(*delegate)(void*))
 * - 링크드 리스트를(전체) 삭제하는 함수
 * - 입력값:
 *   - list: 링크드 리스트
 *   - delegate: 리스트에 저장된 값이 없어질 때 처리할 수 있도록 해주는 함수의 포인터. NULL 가능.
 */
void List_Destroy(LinkedListRef list, void(*delegate)(void*)) {
	if (list->Count > 0) {
		ElementRef prev = NULL;
		FOREACH_LIST(list, element) {
			if (delegate != NULL)
				// 리스트에 저장된 값은 delegate에서 처리할 수 있도록 해줌.
				// ex) 메모리 해제 등
				delegate(element->Value);
			
			free(prev);
			prev = element;
		}

		free(prev);
	}

	free(list);
}