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
#include "Misc.h"

#include <assert.h>
#include <stdio.h>
#include <string.h>

/*
 * int ReadLine(char* buffer, int maxlen)
 * - 값을 입력받는 함수. fgets()의 반환값을 보정한 문자열을 반환.
 * - 입력값:
 *   - buffer: 문자열을 저장할 버퍼
 *   - maxlen: 버퍼의 최대 길이
 * - 출력값: 문자열의 길이. 오류가 발생했다면 -1.
 */
int ReadLine(char* buffer, int maxlen) {
	printf("> ");
	char* str = fgets(buffer, maxlen, stdin);

	if (str == NULL) return -1;

	int length = strlen(buffer);
	buffer[--length] = '\0'; // 마지막 '\n' 제거

	return length;
}

/*
 * void Indent(int indent)
 * - 들여쓰기용 함수
 * - 입력값:
 *   - indent: 들여쓰기 깊이
 */
static void Indent(int indent) {
	// 들여쓰기
	for (int i = 0; i < indent; i++) printf("  ");
}

/*
 * void DumpExpression(int indent, const ExpressionRef expr)
 * - 수식 트리를 출력하는 함수.
 * - 입력값:
 *	 - indent: 인덴트
 *   - expr: 수식
 */
void DumpExpression(int indent, const ExpressionRef expr) {
    Indent(indent);

    switch (expr->Type) {
		case Expr_Error:
            printf("<<Error - Cause: %s>>\n", expr->Value.Error.ErrorMsg);
            
            if (expr->Value.Error.Left) {
                Indent(indent); printf("<<Left:\n");
                DumpExpression(indent + 1, expr->Value.Error.Left);
            }

            if (expr->Value.Error.Right) {
                Indent(indent); printf("<<Right:\n");
                DumpExpression(indent + 1, expr->Value.Error.Right);
            }

            break;
		
        case Expr_Assign:
            printf("<<Assignment>>\n");
            Indent(indent); printf("<<AssignTo: %s>>\n", expr->Value.Assign.ID);
            Indent(indent); printf("<<Expression:\n");
            DumpExpression(indent + 1, expr->Value.Assign.Expr);
            break;

        case Expr_Var:
            printf("<<Variable - Negate: %s, Name: %s>>\n", (expr->Negate ? "true" : "false"), expr->Value.Variable.ID);
            break;

        case Expr_Value:
            printf("<<Value - Negate: %s, Value: %lf>>\n", (expr->Negate ? "true" : "false"), expr->Value.Value.Value);
            break;

        case Expr_Op:
            printf("<<Operation - Negate: %s, Opcode: %c>>\n", (expr->Negate ? "true" : "false"), expr->Value.Operation.Opcode);
            
            if (expr->Value.Error.Left) {
                Indent(indent); printf("<<Left:\n");
                DumpExpression(indent + 1, expr->Value.Operation.Left);
            }

            if (expr->Value.Error.Right) {
                Indent(indent); printf("<<Right:\n");
                DumpExpression(indent + 1, expr->Value.Operation.Right);
            }
            break;

		default: // 절대 도달 못함.
			assert(false && "NEVER REACHED");
			break;
	}
}