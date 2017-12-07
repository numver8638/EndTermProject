// MIT License

// Copyright (c) 2017 Jinhwan Shin(신진환)

// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:

// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
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
