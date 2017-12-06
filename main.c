#include <string.h>

#include "Evaluate.h"
#include "Lexer.h"
#include "Misc.h"
#include "Parser.h"
#include "VariableTable.h"

#define MAX_LENGTH (256) // 버퍼의 최대 길이.

int main(int argc, char* argv[]) {
	char buffer[MAX_LENGTH] = {0};

	InitializeVariableTable(); // 변수 테이블 초기화.

	/*
	 * 내부 흐름
	 * -> ReadLine() 으로 값 입력
	 * -> 커맨드인지 확인. 커맨드일경우 맞는 명령 실행 후 루프의 처음으로
	 * -> 커맨드가 아닐경우 ParseExpression()으로 수식 분석
	 * -> Evaluate()로 수식 실행
	 * -> FreeExpression(), FreeLexer()로 후처리.
	 * -> 종료 커맨드 전까지 반복.
	 */
	do {
		int length = ReadLine(buffer, MAX_LENGTH);

		if (length < 0) break;

		if (length == 0) continue;

		// 내부 커맨드
		if (strcmp(buffer, "exit") == 0 || strcmp(buffer, "quit") == 0) {
			// 종료 커맨드
			break;
		}

		// 내부 커맨드
		if (strcmp(buffer, "variables") == 0) {
			// 변수 테이블 출력
			DumpVariableTable();
			continue;
		}

		LexerRef lexer = CreateLexer(buffer);
		ExpressionRef expr = ParseExpression(lexer);

#if DEBUG
		DumpExpression(0, expr);
#endif // DEBUG

		Evaluate(expr);

		FreeExpression(expr);
		FreeLexer(lexer);
	} while (1);

	FreeVariableTable(); // 변수 테이블 삭제
	
	return 0;
}