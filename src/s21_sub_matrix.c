#include "s21_matrix.h"

int s21_sub_matrix(s21_matrix* A, s21_matrix* B, s21_matrix* result) {
  int flag = OK;

  if (A == NULL || B == NULL || result == NULL || isNotCorrect(*A) ||
      isNotCorrect(*B)) {
    flag = INCORRECT_MATRIX;
  } else {
    if (result->matrix != NULL) {
      s21_remove_matrix(result);
    }

    if (A->rows != B->rows || A->columns != B->columns) {
      flag = CALCULATION_ERROR;
    } else if (s21_create_matrix(A->rows, A->columns, result) == OK) {
      for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->columns; j++) {
          result->matrix[i][j] = A->matrix[i][j] - B->matrix[i][j];
        }
      }
      flag = OK;
    } else {
      flag = INCORRECT_MATRIX;
    }
  }

  return flag;
}