#include "Evaluate.h"

#include <assert.h>
#include <math.h>
#include <stdio.h>

#include "VariableTable.h"

/*
 * bool CheckError(const ExpressionRef expr)
 * - 수식 트리를 순회하면서 오류가 있는지 판별하는 함수. 오류 출력도 담당.
 * - 입력값:
 *   - expr: 수식
 * - 반환값: true이면 오류 있음, false이면 오류 없음.
 */
static bool CheckError(const ExpressionRef expr) {
	switch (expr->Type) {
		case Expr_Error: // 오류 수식. 항상 true 반환.
			printf("error: %s\n", expr->Value.Error.ErrorMsg);
			return true;
		
		case Expr_Assign: // 대입식. 우항의 오류에 따라 결정.
			return CheckError(expr->Value.Assign.Expr);

		case Expr_Var: { // 변수. 정의되어 있는 변수일 경우에만 false 반환.
			bool hasVariable = HasVariable(expr->Value.Variable.ID);

			if (!hasVariable)
				printf("error: undefined variable \"%s\"\n", expr->Value.Variable.ID);
			
			return !hasVariable;
		}

		case Expr_Value: // 값. 항상 false.
			return false;
		
		case Expr_Op: { // 수식. 좌항과 우항의 오류에 따라 결정.
			bool hasError = false;

			if (expr->Value.Operation.Left)
				hasError = CheckError(expr->Value.Operation.Left);
			
			if (!hasError && expr->Value.Operation.Right)
				hasError = CheckError(expr->Value.Operation.Right);
			
			return hasError;
		}

		default: // 절대 도달 못함.
			assert(false && "NEVER REACHED");
			return true;
	}
}

/*
 * double EvaluateValue(const ExpressionRef expr)
 * - 수식 타입에 맞는 계산을 수행하는 함수.
 * - 입력값:
 *   - expr: 수식
 * - 반환값: 수식 계산 결과
 */
static double EvaluateValue(const ExpressionRef expr) {
	double value = 0.0;

	switch (expr->Type) {
		case Expr_Var:
			value = GetVariable(expr->Value.Variable.ID);
			break;

		case Expr_Value:
			value = expr->Value.Value.Value;
			break;
		
		case Expr_Op: {
			double left = EvaluateValue(expr->Value.Operation.Left);
			double right = EvaluateValue(expr->Value.Operation.Right);

			switch (expr->Value.Operation.Opcode) {
				case '+': 
					value = left + right;
					break;

				case '-':
					value = left - right;
					break;

				case '*':
					value = left * right;
					break;

				case '/': 
					value = left / right;
					break;

				case '^': 
					value = pow(left, right);
					break;

				default:
					assert(false && "NEVER REACHED");
					return 0;
			}

			break;
		}

		default:
			assert(false && "NEVER REACHED");
			return 0;
	}

	// 부호처리해서 반환.
	return expr->Negate ? -value : value;
}

/*
 * void Evaluate(const ExpressionRef expr)
 * - 수식을 평가하고 값을 출력하는 함수.
 * - 입력값:
 *   - expr: 수식
 */
void Evaluate(const ExpressionRef expr) {
	if (CheckError(expr))
		return; // there is an error.
	
	// 대입문과 수식을 구분하여 실행함.
	if (expr->Type == Expr_Assign) {
		double result = EvaluateValue(expr->Value.Assign.Expr);
		SetVariable(expr->Value.Assign.ID, result);

		printf("%s = %lf\n", expr->Value.Assign.ID, result);
	}
	else {
		double result = EvaluateValue(expr);
		SetVariable("ans", result);

		printf("ans = %lf\n", result);
	}
}
