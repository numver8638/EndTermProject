#include "Parser.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Lexer.h"

/*
 * ExpressionRef CreateExpression(enum ExpressionType type)
 * - 지정된 타입의 새로운 수식트리를 생성합니다.
 * - 입력값:
 *   - type: 수식 타입
 * - 반환값: 수식트리
 */
ExpressionRef CreateExpression(enum ExpressionType type) {
    ExpressionRef ref = malloc(sizeof(Expression));

    memset(ref, 0, sizeof(Expression));
    ref->Type = type;

    return ref;
}

/*
 * void Consume(LexerRef lexer)
 * - 현재 단어를 소비하고 다음 단어를 분석합니다.
 * - 입력값:
 *   - lexer: 단어 분석기 상태 변수
 */
void Consume(LexerRef lexer) {
    Lex(lexer);
}

/*
 * int GetCurrent(LexerRef lexer)
 * - 현재 분석된 단어를 가져옵니다.
 * - 입력값:
 *   - lexer: 단어 분석기 상태 변수
 * - 반환값: 단어 타입
 */
int GetCurrent(LexerRef lexer) {
    return lexer->Type;
}

ExpressionRef ParseExpression(LexerRef);
ExpressionRef ParseAdditive(LexerRef);

/*
 * ExpressionRef ParseValue(LexerRef lexer)
 * - 값/변수/괄호식을 분석합니다.
 * - 입력값:
 *   - lexer: 단어 분석기 상태 변수
 * - 반환값: 수식 트리
 */
ExpressionRef ParseValue(LexerRef lexer) {
    int type = GetCurrent(lexer);
    bool negate = false;

    if (type == LEX_MINUS || type == LEX_PLUS) { // 처음 시작이 '+' 나 '-' : 부호
        Consume(lexer); // 부호 소비

        negate = (type == LEX_MINUS); // 부호가 '-'면 부정.

        type = GetCurrent(lexer); // 다음 단어 저장.
    }

    switch (type) {
        case LEX_ID: { // 변수 타입
            ExpressionRef expr = CreateExpression(Expr_Var); // 변수 타입 수식트리 생성
            expr->Value.Variable.ID = strdup(lexer->Image); // 변수 이름 복사
            expr->Negate = negate; // 반전 필요?
            Consume(lexer); // 단어 소비

            return expr;
        }

        case LEX_VALUE: { // 값 타입
            ExpressionRef expr = CreateExpression(Expr_Value); // 값 타입 수식트리 생성
            expr->Value.Value.Value = lexer->Value; // 값 복사
            expr->Negate = negate; // 반전 필요?
            Consume(lexer); // 단어 소비

            return expr;
        }

        case LEX_LEFTPAREN: { // 왼쪽 괄호 - 괄호식 시작
            Consume(lexer);
            ExpressionRef inParen = ParseAdditive(lexer); // 괄호식 안 수식 분석

            if (GetCurrent(lexer) != LEX_RIGHTPAREN) { // 오른쪽 괄호가 아니면...
                // 오류. 괄호가 닫히지 않음.

                ExpressionRef expr = CreateExpression(Expr_Error);
                expr->Value.Error.ErrorMsg = "paren not closed";
                expr->Value.Error.Left = inParen;
                return expr;
            }
            else { // 맞으면...
                Consume(lexer); // 오른쪽 괄호 소비.
                inParen->Negate = negate; // 반전 필요?
                return inParen;
            }
        }

        default: { // 오류.
            ExpressionRef expr = CreateExpression(Expr_Error);
            expr->Value.Error.ErrorMsg = GetCurrent(lexer) == LEX_END ? "unexpected end of expression" : "unknown value";
            // 문장의 끝이면 -> 예상치 못한 식의 끝, 아니면 -> 모르는 값

            return expr;
        }
    }
}

/*
 * ExpressionRef ParseMultiplicative(LexerRef lexer)
 * - 곱하기/나누기/제곱 연산식을 분석합니다.
 * - 입력값:
 *   - lexer: 단어 분석기 상태 변수
 * - 반환값: 수식 트리
 */
ExpressionRef ParseMultiplicative(LexerRef lexer) {
    ExpressionRef left = ParseValue(lexer); // 좌항 분석

    int op = 0;
    switch (GetCurrent(lexer)) { // 연산자 분석
        case LEX_MULTIPLY:
            op = '*';
            break;
        
        case LEX_DIVIDE:
            op = '/';
            break;
        
        case LEX_POWER:
            op = '^';
            break;
        
        default: // 적절한 연산자 없음 - 식의 끝이거나 오류. 그건 나중에 판단.
            return left;
    }

    Consume(lexer); // 연산자 소비

    ExpressionRef expr = CreateExpression(Expr_Op); // 연산 타입의 수식트리 생성
    expr->Value.Operation.Left = left;
    expr->Value.Operation.Right = ParseMultiplicative(lexer); // 우항 분석
    expr->Value.Operation.Opcode = op;

    return expr;
}

/*
 * ExpressionRef ParseAdditive(LexerRef lexer)
 * - 더하기/빼기 연산식을 분석합니다.
 * - 입력값:
 *   - lexer: 단어 분석기 상태 변수
 * - 반환값: 수식 트리
 */
ExpressionRef ParseAdditive(LexerRef lexer) {
    ExpressionRef left = ParseMultiplicative(lexer); // 좌항 분석

    int op = 0;
    switch (GetCurrent(lexer)) { // 연산자 분석
        case LEX_PLUS:
            op = '+';
            break;
        
        case LEX_MINUS:
            op = '-';
            break;
        
        default: // 적절한 연산자 없음 - 식의 끝이거나 오류. 그건 나중에 판단.
            return left;
    }

    Consume(lexer); // 연산자 소비

    ExpressionRef expr = CreateExpression(Expr_Op); // 연산 타입의 수식트리 생성
    expr->Value.Operation.Left = left;
    expr->Value.Operation.Right = ParseAdditive(lexer); // 우항 분석
    expr->Value.Operation.Opcode = op;

    return expr;
}


ExpressionRef ParseExpression(LexerRef lexer) {
	assert(lexer != NULL && "Lexer cannot be null");

    // 첫번째 단어 분석 (첫번째 단어가 분석된 후 수식 분석 시작)
    Consume(lexer);

    ExpressionRef expr = ParseAdditive(lexer); // 수식 분석

    // 등호가 있고, 좌항이 변수명이면...
    if (GetCurrent(lexer) == LEX_ASSIGN && expr->Type == Expr_Var) {
        // 대입문
        Consume(lexer); // '=' 소비

        ExpressionRef left = expr; // 좌항 저장.
        ExpressionRef right = ParseAdditive(lexer); // 우항 수식 분석

        expr = CreateExpression(Expr_Assign);
        expr->Value.Assign.ID = left->Value.Variable.ID;
        expr->Value.Assign.Expr = right;
    }

    // 현재 식의 끝이 아니면
    if (GetCurrent(lexer) != LEX_END) {
        // 오류.

        ExpressionRef old = expr;
        expr = CreateExpression(Expr_Error);
        expr->Value.Error.ErrorMsg = "end of expression expected";
        expr->Value.Error.Left = old;
    }

    return expr;
}

/*
 * void FreeExpression(ExpressionRef expr)
 * - 수식 트리를 메모리 해제 합니다.
 * - 입력값:
 *   - expr: 수식 트리
 */
void FreeExpression(ExpressionRef expr) {
    switch (expr->Type) {
        case Expr_Error:
            if (expr->Value.Error.Left)
                FreeExpression(expr->Value.Error.Left);
            
            if (expr->Value.Error.Right)
                FreeExpression(expr->Value.Error.Right);
            
            break;
        
        case Expr_Op:
            if (expr->Value.Operation.Left)
                FreeExpression(expr->Value.Operation.Left);
            
            if (expr->Value.Operation.Right)
                FreeExpression(expr->Value.Operation.Right);
            
            break;
        
        case Expr_Var:
            free((void*) expr->Value.Variable.ID);
            break;

        default:
            // do nothing
            break;
    }

    free(expr);
}