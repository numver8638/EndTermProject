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
#include "VariableTable.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "LinkedList.h"

// 변수는 링크드 리스트로 관리함.
static LinkedListRef Variables;

/*
 * 변수를 저장하는 구조체.
 */
typedef struct {
    char   Name[64];
    double Value;
} Variable, *VariableRef;

/*
 * void InitializeVariableTable()
 * - 변수 테이블을 초기화하는 함수
 */
void InitializeVariableTable() {
    // 링크드 리스트 생성.
    Variables = List_Create();
}

/*
 * bool HasVariable(const char* id)
 * - 변수가 있는지 조회하는 함수
 * - 입력값:
 *   - id: 변수명
 * - 출력값: 변수가 있으면 true, 없으면 false.
 */
bool HasVariable(const char* id) {
    // 리스트 순회
    FOREACH_LIST(Variables, element) {
        VariableRef var = (VariableRef)element->Value;

        if (strcmp(var->Name, id) == 0) return true;
    }

    return false;
}

/*
 * double GetVariable(const char* id)
 * - 변수의 값을 가져오는 함수.
 * - 입력값:
 *   - id: 변수명
 * - 출력값: 변수에 저장된 값. 없는 변수일 경우 오류(assert) 발생.
 */
double GetVariable(const char* id) {
    // 리스트 순회
    FOREACH_LIST(Variables, element) {
        VariableRef var = (VariableRef)element->Value;

        if (strcmp(var->Name, id) == 0) {
            return var->Value;
        }
    }

    assert(false && "Not declared variable referenced");
    return 0;
}

/*
 * void SetVariable(const char* id, double value)
 * - 변수가 있는지 조회하는 함수
 * - 입력값:
 *   - id: 변수명
 *   - value: 값
 */
void SetVariable(const char* id, double value) {
    // 리스트 순회하면서 저장된 값부터 찾음.
    FOREACH_LIST(Variables, element) {
        VariableRef var = (VariableRef)element->Value;

        // 이미 변수가 정의되었다면...
        if (strcmp(var->Name, id) == 0) {
            // 변수에 값을 저장하고 함수 종료.
            var->Value = value;
            return;
        }
    }
    
    // 변수가 정의 되지 않았으므로
    // 새로운 변수를 정의함.
    VariableRef var = malloc(sizeof(Variable));
    memset(var, 0, sizeof(Variable));
    strcpy(var->Name, id);
    var->Value = value;

    // 리스트에 추가.
    List_Append(Variables, var);
}

/*
 * void FreeVariableTable()
 * - 변수 테이블 삭제 함수
 */
void FreeVariableTable() {
    // 리스트 삭제
    List_Destroy(Variables, NULL);
}

/*
 * bool HasVariable(const char* id)
 * - 변수가 있는지 조회하는 함수
 * - 입력값:
 *   - id: 변수명
 * - 출력값: 변수가 있으면 true, 없으면 false.
 */
void DumpVariableTable() {
    printf("The table has %d variable(s)\n\n", Variables->Count);

    // 리스트 순회
    FOREACH_LIST(Variables, element) {
        VariableRef var = (VariableRef) element->Value;

        printf("%s = %lf\n", var->Name, var->Value);
    }

    printf("\n");
}