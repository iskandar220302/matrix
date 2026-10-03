#include "s21_matrix.h"

int s21_eq_matrix(s21_matrix* A, s21_matrix* B) {
  int result = SUCCESS;

  if (A == NULL || B == NULL || isNotCorrect(*A) || isNotCorrect(*B)) {
    result = FAILURE;
  } else if (A->rows != B->rows || A->columns != B->columns) {
    result = FAILURE;
  } else {
    for (int i = 0; i < A->rows && result == SUCCESS; i++) {
      for (int j = 0; j < A->columns && result == SUCCESS; j++) {
        if (fabs(A->matrix[i][j] - B->matrix[i][j]) > 1e-6) {
          result = FAILURE;
        }
      }
    }
  }

  return result;
}