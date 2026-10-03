#include <check.h>

#include "../s21_matrix.h"

// ==================== ВСПОМОГАТЕЛЬНЫЕ ФУНКЦИИ ====================

void fill_matrix(s21_matrix* A, double values[]) {
  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < A->columns; j++) {
      A->matrix[i][j] = values[i * A->columns + j];
    }
  }
}

// ==================== ТЕСТЫ s21_create_matrix ====================

START_TEST(create_matrix_1) {
  s21_matrix A = {0};
  ck_assert_int_eq(s21_create_matrix(3, 4, &A), OK);
  ck_assert_int_eq(A.rows, 3);
  ck_assert_int_eq(A.columns, 4);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(create_matrix_2) {
  s21_matrix A = {0};
  ck_assert_int_eq(s21_create_matrix(0, 5, &A), INCORRECT_MATRIX);
}
END_TEST

START_TEST(create_matrix_3) {
  s21_matrix A = {0};
  ck_assert_int_eq(s21_create_matrix(5, 0, &A), INCORRECT_MATRIX);
}
END_TEST

START_TEST(create_matrix_4) {
  ck_assert_int_eq(s21_create_matrix(3, 3, NULL), INCORRECT_MATRIX);
}
END_TEST

// ==================== ТЕСТЫ s21_remove_matrix ====================

START_TEST(remove_matrix_1) {
  s21_matrix A = {0};
  s21_create_matrix(3, 3, &A);
  s21_remove_matrix(&A);
  ck_assert_ptr_null(A.matrix);
  ck_assert_int_eq(A.rows, 0);
  ck_assert_int_eq(A.columns, 0);
}
END_TEST

START_TEST(remove_matrix_2) {
  s21_remove_matrix(NULL);
  ck_assert_int_eq(1, 1);
}
END_TEST

START_TEST(remove_matrix_3) {
  s21_matrix A = {0};
  s21_remove_matrix(&A);
  ck_assert_ptr_null(A.matrix);
}
END_TEST

// ==================== ТЕСТЫ s21_eq_matrix ====================

START_TEST(eq_matrix_1) {
  s21_matrix A = {0}, B = {0};
  s21_create_matrix(2, 2, &A);
  s21_create_matrix(2, 2, &B);
  double v[] = {1, 2, 3, 4};
  fill_matrix(&A, v);
  fill_matrix(&B, v);
  ck_assert_int_eq(s21_eq_matrix(&A, &B), SUCCESS);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(eq_matrix_2) {
  s21_matrix A = {0}, B = {0};
  s21_create_matrix(2, 2, &A);
  s21_create_matrix(2, 2, &B);
  double v1[] = {1, 2, 3, 4};
  double v2[] = {1, 2, 3, 5};
  fill_matrix(&A, v1);
  fill_matrix(&B, v2);
  ck_assert_int_eq(s21_eq_matrix(&A, &B), FAILURE);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(eq_matrix_3) {
  s21_matrix A = {0}, B = {0};
  s21_create_matrix(2, 3, &A);
  s21_create_matrix(3, 2, &B);
  ck_assert_int_eq(s21_eq_matrix(&A, &B), FAILURE);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

// ==================== ТЕСТЫ s21_sum_matrix ====================

START_TEST(sum_matrix_1) {
  s21_matrix A = {0}, B = {0}, result = {0};
  s21_create_matrix(2, 2, &A);
  s21_create_matrix(2, 2, &B);
  double v1[] = {1, 2, 3, 4};
  double v2[] = {5, 6, 7, 8};
  fill_matrix(&A, v1);
  fill_matrix(&B, v2);
  ck_assert_int_eq(s21_sum_matrix(&A, &B, &result), OK);
  ck_assert_double_eq_tol(result.matrix[0][0], 6, 1e-7);
  ck_assert_double_eq_tol(result.matrix[0][1], 8, 1e-7);
  ck_assert_double_eq_tol(result.matrix[1][0], 10, 1e-7);
  ck_assert_double_eq_tol(result.matrix[1][1], 12, 1e-7);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(sum_matrix_2) {
  s21_matrix A = {0}, B = {0}, result = {0};
  s21_create_matrix(2, 3, &A);
  s21_create_matrix(3, 2, &B);
  ck_assert_int_eq(s21_sum_matrix(&A, &B, &result), CALCULATION_ERROR);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(sum_matrix_existing_result) {
  s21_matrix A = {0}, B = {0}, result = {0};
  s21_create_matrix(2, 2, &A);
  s21_create_matrix(2, 2, &B);
  s21_create_matrix(1, 1, &result);
  double v1[] = {1, 2, 3, 4};
  double v2[] = {5, 6, 7, 8};
  fill_matrix(&A, v1);
  fill_matrix(&B, v2);
  ck_assert_int_eq(s21_sum_matrix(&A, &B, &result), OK);
  ck_assert_int_eq(result.rows, 2);
  ck_assert_int_eq(result.columns, 2);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
}
END_TEST

// ==================== ТЕСТЫ s21_sub_matrix ====================

START_TEST(sub_matrix_1) {
  s21_matrix A = {0}, B = {0}, result = {0};
  s21_create_matrix(2, 2, &A);
  s21_create_matrix(2, 2, &B);
  double v1[] = {5, 6, 7, 8};
  double v2[] = {1, 2, 3, 4};
  fill_matrix(&A, v1);
  fill_matrix(&B, v2);
  ck_assert_int_eq(s21_sub_matrix(&A, &B, &result), OK);
  ck_assert_double_eq_tol(result.matrix[0][0], 4, 1e-7);
  ck_assert_double_eq_tol(result.matrix[0][1], 4, 1e-7);
  ck_assert_double_eq_tol(result.matrix[1][0], 4, 1e-7);
  ck_assert_double_eq_tol(result.matrix[1][1], 4, 1e-7);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(sub_matrix_existing_result) {
  s21_matrix A = {0}, B = {0}, result = {0};
  s21_create_matrix(2, 2, &A);
  s21_create_matrix(2, 2, &B);
  s21_create_matrix(1, 1, &result);
  double v1[] = {5, 6, 7, 8};
  double v2[] = {1, 2, 3, 4};
  fill_matrix(&A, v1);
  fill_matrix(&B, v2);
  ck_assert_int_eq(s21_sub_matrix(&A, &B, &result), OK);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
}
END_TEST

// ==================== ТЕСТЫ s21_mult_number ====================

START_TEST(mult_number_1) {
  s21_matrix A = {0}, result = {0};
  s21_create_matrix(2, 2, &A);
  double v[] = {1, 2, 3, 4};
  fill_matrix(&A, v);
  ck_assert_int_eq(s21_mult_number(&A, 2.5, &result), OK);
  ck_assert_double_eq_tol(result.matrix[0][0], 2.5, 1e-7);
  ck_assert_double_eq_tol(result.matrix[0][1], 5, 1e-7);
  ck_assert_double_eq_tol(result.matrix[1][0], 7.5, 1e-7);
  ck_assert_double_eq_tol(result.matrix[1][1], 10, 1e-7);
  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(mult_number_existing_result) {
  s21_matrix A = {0}, result = {0};
  s21_create_matrix(2, 2, &A);
  s21_create_matrix(1, 1, &result);
  double v[] = {1, 2, 3, 4};
  fill_matrix(&A, v);
  ck_assert_int_eq(s21_mult_number(&A, 2.0, &result), OK);
  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

// ==================== ТЕСТЫ s21_mult_matrix ====================

START_TEST(mult_matrix_1) {
  s21_matrix A = {0}, B = {0}, result = {0};
  s21_create_matrix(2, 3, &A);
  s21_create_matrix(3, 2, &B);
  double v1[] = {1, 2, 3, 4, 5, 6};
  double v2[] = {7, 8, 9, 10, 11, 12};
  fill_matrix(&A, v1);
  fill_matrix(&B, v2);
  ck_assert_int_eq(s21_mult_matrix(&A, &B, &result), OK);
  ck_assert_double_eq_tol(result.matrix[0][0], 58, 1e-7);
  ck_assert_double_eq_tol(result.matrix[0][1], 64, 1e-7);
  ck_assert_double_eq_tol(result.matrix[1][0], 139, 1e-7);
  ck_assert_double_eq_tol(result.matrix[1][1], 154, 1e-7);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(mult_matrix_2) {
  s21_matrix A = {0}, B = {0}, result = {0};
  s21_create_matrix(2, 3, &A);
  s21_create_matrix(2, 3, &B);
  ck_assert_int_eq(s21_mult_matrix(&A, &B, &result), CALCULATION_ERROR);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

// ==================== ТЕСТЫ s21_transpose ====================

START_TEST(transpose_1) {
  s21_matrix A = {0}, result = {0};
  s21_create_matrix(2, 3, &A);
  double v[] = {1, 2, 3, 4, 5, 6};
  fill_matrix(&A, v);
  ck_assert_int_eq(s21_transpose(&A, &result), OK);
  ck_assert_int_eq(result.rows, 3);
  ck_assert_int_eq(result.columns, 2);
  ck_assert_double_eq_tol(result.matrix[0][0], 1, 1e-7);
  ck_assert_double_eq_tol(result.matrix[0][1], 4, 1e-7);
  ck_assert_double_eq_tol(result.matrix[1][0], 2, 1e-7);
  ck_assert_double_eq_tol(result.matrix[1][1], 5, 1e-7);
  ck_assert_double_eq_tol(result.matrix[2][0], 3, 1e-7);
  ck_assert_double_eq_tol(result.matrix[2][1], 6, 1e-7);
  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(transpose_existing_result) {
  s21_matrix A = {0}, result = {0};
  s21_create_matrix(2, 3, &A);
  s21_create_matrix(1, 1, &result);
  double v[] = {1, 2, 3, 4, 5, 6};
  fill_matrix(&A, v);
  ck_assert_int_eq(s21_transpose(&A, &result), OK);
  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

// ==================== ТЕСТЫ s21_determinant ====================

START_TEST(determinant_1) {
  s21_matrix A = {0};
  s21_create_matrix(3, 3, &A);
  double v[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  fill_matrix(&A, v);
  double det = 0;
  ck_assert_int_eq(s21_determinant(&A, &det), OK);
  ck_assert_double_eq_tol(det, 0, 1e-7);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(determinant_2) {
  s21_matrix A = {0};
  s21_create_matrix(2, 2, &A);
  double v[] = {5, 6, 7, 8};
  fill_matrix(&A, v);
  double det = 0;
  ck_assert_int_eq(s21_determinant(&A, &det), OK);
  ck_assert_double_eq_tol(det, -2, 1e-7);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(determinant_3) {
  s21_matrix A = {0};
  s21_create_matrix(1, 1, &A);
  A.matrix[0][0] = 10;
  double det = 0;
  ck_assert_int_eq(s21_determinant(&A, &det), OK);
  ck_assert_double_eq_tol(det, 10, 1e-7);
  s21_remove_matrix(&A);
}
END_TEST

// ==================== ТЕСТЫ s21_calc_complements ====================

START_TEST(calc_complements_1) {
  s21_matrix A = {0}, result = {0};
  s21_create_matrix(3, 3, &A);
  double v[] = {1, 2, 3, 0, 4, 2, 5, 2, 1};
  fill_matrix(&A, v);
  ck_assert_int_eq(s21_calc_complements(&A, &result), OK);
  ck_assert_double_eq_tol(result.matrix[0][0], 0, 1e-7);
  ck_assert_double_eq_tol(result.matrix[0][1], 10, 1e-7);
  ck_assert_double_eq_tol(result.matrix[0][2], -20, 1e-7);
  ck_assert_double_eq_tol(result.matrix[1][0], 4, 1e-7);
  ck_assert_double_eq_tol(result.matrix[1][1], -14, 1e-7);
  ck_assert_double_eq_tol(result.matrix[1][2], 8, 1e-7);
  ck_assert_double_eq_tol(result.matrix[2][0], -8, 1e-7);
  ck_assert_double_eq_tol(result.matrix[2][1], -2, 1e-7);
  ck_assert_double_eq_tol(result.matrix[2][2], 4, 1e-7);
  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(calc_complements_2) {
  s21_matrix A = {0}, result = {0};
  s21_create_matrix(1, 1, &A);
  A.matrix[0][0] = 5;
  ck_assert_int_eq(s21_calc_complements(&A, &result), OK);
  ck_assert_double_eq_tol(result.matrix[0][0], 1, 1e-7);
  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(calc_complements_existing_result) {
  s21_matrix A = {0}, result = {0};
  s21_create_matrix(2, 2, &A);
  s21_create_matrix(1, 1, &result);
  double v[] = {1, 2, 3, 4};
  fill_matrix(&A, v);
  ck_assert_int_eq(s21_calc_complements(&A, &result), OK);
  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(calc_complements_non_square) {
  s21_matrix A = {0}, result = {0};
  s21_create_matrix(2, 3, &A);
  ck_assert_int_eq(s21_calc_complements(&A, &result), CALCULATION_ERROR);
  s21_remove_matrix(&A);
}
END_TEST

// ==================== ТЕСТЫ s21_inverse_matrix ====================

START_TEST(inverse_matrix_1) {
  s21_matrix A = {0}, result = {0};
  s21_create_matrix(3, 3, &A);
  double v[] = {2, 5, 7, 6, 3, 4, 5, -2, -3};
  fill_matrix(&A, v);
  ck_assert_int_eq(s21_inverse_matrix(&A, &result), OK);
  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(inverse_matrix_2) {
  s21_matrix A = {0}, result = {0};
  s21_create_matrix(3, 3, &A);
  double v[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  fill_matrix(&A, v);
  ck_assert_int_eq(s21_inverse_matrix(&A, &result), CALCULATION_ERROR);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(inverse_matrix_non_square) {
  s21_matrix A = {0}, result = {0};
  s21_create_matrix(2, 3, &A);
  ck_assert_int_eq(s21_inverse_matrix(&A, &result), CALCULATION_ERROR);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(inverse_matrix_null) {
  s21_matrix result = {0};
  ck_assert_int_eq(s21_inverse_matrix(NULL, &result), INCORRECT_MATRIX);
}
END_TEST

// ==================== НАБОР ТЕСТОВ ====================
// ========== ДОПОЛНИТЕЛЬНЫЕ ТЕСТЫ ДЛЯ ПОВЫШЕНИЯ ПОКРЫТИЯ ==========

// Для s21_mult_matrix с уже существующим result
START_TEST(mult_matrix_existing_result) {
  s21_matrix A = {0}, B = {0}, result = {0};
  s21_create_matrix(2, 3, &A);
  s21_create_matrix(3, 2, &B);
  s21_create_matrix(1, 1, &result);
  double v1[] = {1, 2, 3, 4, 5, 6};
  double v2[] = {7, 8, 9, 10, 11, 12};
  fill_matrix(&A, v1);
  fill_matrix(&B, v2);
  ck_assert_int_eq(s21_mult_matrix(&A, &B, &result), OK);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
}
END_TEST

// Для s21_determinant с ошибками
START_TEST(determinant_null) {
  double det = 0;
  ck_assert_int_eq(s21_determinant(NULL, &det), INCORRECT_MATRIX);
}
END_TEST

START_TEST(determinant_null_result) {
  s21_matrix A = {0};
  s21_create_matrix(2, 2, &A);
  ck_assert_int_eq(s21_determinant(&A, NULL), INCORRECT_MATRIX);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(determinant_non_square) {
  s21_matrix A = {0};
  s21_create_matrix(2, 3, &A);
  double det = 0;
  ck_assert_int_eq(s21_determinant(&A, &det), CALCULATION_ERROR);
  s21_remove_matrix(&A);
}
END_TEST

// Для s21_eq_matrix с NULL
START_TEST(eq_matrix_null) {
  s21_matrix A = {0};
  s21_create_matrix(2, 2, &A);
  ck_assert_int_eq(s21_eq_matrix(&A, NULL), FAILURE);
  ck_assert_int_eq(s21_eq_matrix(NULL, &A), FAILURE);
  ck_assert_int_eq(s21_eq_matrix(NULL, NULL), FAILURE);
  s21_remove_matrix(&A);
}
END_TEST

// Для s21_inverse_matrix с существующим result
START_TEST(inverse_matrix_existing_result) {
  s21_matrix A = {0}, result = {0};
  s21_create_matrix(2, 2, &A);
  s21_create_matrix(1, 1, &result);
  double v[] = {4, 7, 2, 6};
  fill_matrix(&A, v);
  ck_assert_int_eq(s21_inverse_matrix(&A, &result), OK);
  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

// Для s21_mult_number с NULL аргументами
START_TEST(mult_number_null) {
  s21_matrix A = {0}, result = {0};
  s21_create_matrix(2, 2, &A);
  ck_assert_int_eq(s21_mult_number(NULL, 2.0, &result), INCORRECT_MATRIX);
  ck_assert_int_eq(s21_mult_number(&A, 2.0, NULL), INCORRECT_MATRIX);
  s21_remove_matrix(&A);
}
END_TEST

// Для s21_sum_matrix с NULL
START_TEST(sum_matrix_null) {
  s21_matrix A = {0}, B = {0}, result = {0};
  s21_create_matrix(2, 2, &A);
  s21_create_matrix(2, 2, &B);
  ck_assert_int_eq(s21_sum_matrix(NULL, &B, &result), INCORRECT_MATRIX);
  ck_assert_int_eq(s21_sum_matrix(&A, NULL, &result), INCORRECT_MATRIX);
  ck_assert_int_eq(s21_sum_matrix(&A, &B, NULL), INCORRECT_MATRIX);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

// Для s21_sub_matrix с NULL
START_TEST(sub_matrix_null) {
  s21_matrix A = {0}, B = {0}, result = {0};
  s21_create_matrix(2, 2, &A);
  s21_create_matrix(2, 2, &B);
  ck_assert_int_eq(s21_sub_matrix(NULL, &B, &result), INCORRECT_MATRIX);
  ck_assert_int_eq(s21_sub_matrix(&A, NULL, &result), INCORRECT_MATRIX);
  ck_assert_int_eq(s21_sub_matrix(&A, &B, NULL), INCORRECT_MATRIX);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

// Для s21_calc_complements с NULL
START_TEST(calc_complements_null) {
  s21_matrix A = {0}, result = {0};
  s21_create_matrix(2, 2, &A);
  ck_assert_int_eq(s21_calc_complements(NULL, &result), INCORRECT_MATRIX);
  ck_assert_int_eq(s21_calc_complements(&A, NULL), INCORRECT_MATRIX);
  s21_remove_matrix(&A);
}
END_TEST

// ========== ДОПОЛНИТЕЛЬНЫЕ ТЕСТЫ ДЛЯ ПОВЫШЕНИЯ ОБЩЕГО ПОКРЫТИЯ ==========

// Для s21_create_matrix - тест на отрицательные значения
START_TEST(create_matrix_negative) {
  s21_matrix A = {0};
  ck_assert_int_eq(s21_create_matrix(-3, 5, &A), INCORRECT_MATRIX);
  ck_assert_int_eq(s21_create_matrix(5, -3, &A), INCORRECT_MATRIX);
}
END_TEST

// Для s21_create_matrix - повторное создание поверх существующей матрицы
START_TEST(create_matrix_overwrite) {
  s21_matrix A = {0};
  s21_create_matrix(2, 2, &A);
  A.matrix[0][0] = 999;
  ck_assert_int_eq(s21_create_matrix(3, 3, &A), OK);
  ck_assert_int_eq(A.rows, 3);
  ck_assert_int_eq(A.columns, 3);
  s21_remove_matrix(&A);
}
END_TEST

// Для s21_remove_matrix - повторное удаление
START_TEST(remove_matrix_double) {
  s21_matrix A = {0};
  s21_create_matrix(2, 2, &A);
  s21_remove_matrix(&A);
  s21_remove_matrix(&A);  // повторное удаление не должно крашиться
  ck_assert_ptr_null(A.matrix);
}
END_TEST

// Для s21_eq_matrix - с некорректными матрицами
START_TEST(eq_matrix_invalid) {
  s21_matrix A = {0}, B = {0};
  A.rows = -1;  // некорректная матрица
  ck_assert_int_eq(s21_eq_matrix(&A, &B), FAILURE);
}
END_TEST

// Для s21_mult_matrix - с существующим result
START_TEST(mult_matrix_existing) {
  s21_matrix A = {0}, B = {0}, result = {0};
  s21_create_matrix(2, 3, &A);
  s21_create_matrix(3, 2, &B);
  s21_create_matrix(1, 1, &result);  // существующая матрица
  double v1[] = {1, 2, 3, 4, 5, 6};
  double v2[] = {7, 8, 9, 10, 11, 12};
  fill_matrix(&A, v1);
  fill_matrix(&B, v2);
  ck_assert_int_eq(s21_mult_matrix(&A, &B, &result), OK);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
}
END_TEST

// Для s21_mult_matrix - с NULL аргументами
START_TEST(mult_matrix_null) {
  s21_matrix A = {0}, B = {0}, result = {0};
  s21_create_matrix(2, 2, &A);
  s21_create_matrix(2, 2, &B);
  ck_assert_int_eq(s21_mult_matrix(NULL, &B, &result), INCORRECT_MATRIX);
  ck_assert_int_eq(s21_mult_matrix(&A, NULL, &result), INCORRECT_MATRIX);
  ck_assert_int_eq(s21_mult_matrix(&A, &B, NULL), INCORRECT_MATRIX);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

// Для s21_determinant - с уже существующей матрицей (покрывает больше строк)
START_TEST(determinant_large) {
  s21_matrix A = {0};
  s21_create_matrix(4, 4, &A);
  double v[] = {5, 1, 2, 3, 4, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
  fill_matrix(&A, v);
  double det = 0;
  ck_assert_int_eq(s21_determinant(&A, &det), OK);
  s21_remove_matrix(&A);
}
END_TEST

// Для s21_inverse_matrix - проверка результата
START_TEST(inverse_matrix_check) {
  s21_matrix A = {0}, inv = {0}, mult = {0};
  s21_create_matrix(2, 2, &A);
  double v[] = {4, 7, 2, 6};
  fill_matrix(&A, v);
  ck_assert_int_eq(s21_inverse_matrix(&A, &inv), OK);
  ck_assert_int_eq(s21_mult_matrix(&A, &inv, &mult), OK);
  // Проверяем что получилась единичная матрица
  ck_assert_double_eq_tol(mult.matrix[0][0], 1.0, 1e-6);
  ck_assert_double_eq_tol(mult.matrix[0][1], 0.0, 1e-6);
  ck_assert_double_eq_tol(mult.matrix[1][0], 0.0, 1e-6);
  ck_assert_double_eq_tol(mult.matrix[1][1], 1.0, 1e-6);
  s21_remove_matrix(&A);
  s21_remove_matrix(&inv);
  s21_remove_matrix(&mult);
}
END_TEST

// Для s21_calc_complements - матрица 2x2
START_TEST(calc_complements_2x2) {
  s21_matrix A = {0}, result = {0};
  s21_create_matrix(2, 2, &A);
  double v[] = {1, 2, 3, 4};
  fill_matrix(&A, v);
  ck_assert_int_eq(s21_calc_complements(&A, &result), OK);
  ck_assert_double_eq_tol(result.matrix[0][0], 4.0, 1e-7);
  ck_assert_double_eq_tol(result.matrix[0][1], -3.0, 1e-7);
  ck_assert_double_eq_tol(result.matrix[1][0], -2.0, 1e-7);
  ck_assert_double_eq_tol(result.matrix[1][1], 1.0, 1e-7);
  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

Suite* matrix_suite(void) {
  Suite* s = suite_create("Matrix Library");

  TCase* tc_create = tcase_create("Create Matrix");
  tcase_add_test(tc_create, create_matrix_1);
  tcase_add_test(tc_create, create_matrix_2);
  tcase_add_test(tc_create, create_matrix_3);
  tcase_add_test(tc_create, create_matrix_4);
  tcase_add_test(tc_create, create_matrix_negative);   // ДОБАВЬТЕ
  tcase_add_test(tc_create, create_matrix_overwrite);  // ДОБАВЬТЕ
  suite_add_tcase(s, tc_create);

  TCase* tc_remove = tcase_create("Remove Matrix");
  tcase_add_test(tc_remove, remove_matrix_1);
  tcase_add_test(tc_remove, remove_matrix_2);
  tcase_add_test(tc_remove, remove_matrix_3);
  tcase_add_test(tc_remove, remove_matrix_double);
  suite_add_tcase(s, tc_remove);

  TCase* tc_eq = tcase_create("Equal Matrix");
  tcase_add_test(tc_eq, eq_matrix_null);
  tcase_add_test(tc_eq, eq_matrix_1);
  tcase_add_test(tc_eq, eq_matrix_2);
  tcase_add_test(tc_eq, eq_matrix_3);
  tcase_add_test(tc_eq, eq_matrix_invalid);
  suite_add_tcase(s, tc_eq);

  TCase* tc_sum = tcase_create("Sum Matrix");
  tcase_add_test(tc_sum, sum_matrix_1);
  tcase_add_test(tc_sum, sum_matrix_2);
  tcase_add_test(tc_sum, sum_matrix_existing_result);
  tcase_add_test(tc_sum, sum_matrix_null);
  suite_add_tcase(s, tc_sum);

  TCase* tc_sub = tcase_create("Sub Matrix");
  tcase_add_test(tc_sub, sub_matrix_1);
  tcase_add_test(tc_sub, sub_matrix_existing_result);
  tcase_add_test(tc_sub, sub_matrix_null);
  suite_add_tcase(s, tc_sub);

  TCase* tc_mult_num = tcase_create("Multiply Number");
  tcase_add_test(tc_mult_num, mult_number_1);
  tcase_add_test(tc_mult_num, mult_number_existing_result);
  tcase_add_test(tc_mult_num, mult_number_null);

  suite_add_tcase(s, tc_mult_num);

  TCase* tc_mult = tcase_create("Multiply Matrix");
  tcase_add_test(tc_mult, mult_matrix_existing_result);
  tcase_add_test(tc_mult, mult_matrix_1);
  tcase_add_test(tc_mult, mult_matrix_2);
  tcase_add_test(tc_mult, mult_matrix_existing);
  tcase_add_test(tc_mult, mult_matrix_null);
  suite_add_tcase(s, tc_mult);

  TCase* tc_trans = tcase_create("Transpose");
  tcase_add_test(tc_trans, transpose_1);
  tcase_add_test(tc_trans, transpose_existing_result);
  suite_add_tcase(s, tc_trans);

  TCase* tc_det = tcase_create("Determinant");
  tcase_add_test(tc_det, determinant_1);
  tcase_add_test(tc_det, determinant_2);
  tcase_add_test(tc_det, determinant_3);
  tcase_add_test(tc_det, determinant_null);
  tcase_add_test(tc_det, determinant_null_result);
  tcase_add_test(tc_det, determinant_non_square);
  tcase_add_test(tc_det, determinant_large);
  suite_add_tcase(s, tc_det);

  TCase* tc_comp = tcase_create("Calc Complements");
  tcase_add_test(tc_comp, calc_complements_1);
  tcase_add_test(tc_comp, calc_complements_2);
  tcase_add_test(tc_comp, calc_complements_existing_result);
  tcase_add_test(tc_comp, calc_complements_non_square);
  tcase_add_test(tc_comp, calc_complements_null);
  tcase_add_test(tc_comp, calc_complements_2x2);
  suite_add_tcase(s, tc_comp);

  TCase* tc_inv = tcase_create("Inverse Matrix");
  tcase_add_test(tc_inv, inverse_matrix_1);
  tcase_add_test(tc_inv, inverse_matrix_2);
  tcase_add_test(tc_inv, inverse_matrix_non_square);
  tcase_add_test(tc_inv, inverse_matrix_null);
  tcase_add_test(tc_inv, inverse_matrix_existing_result);
  tcase_add_test(tc_inv, inverse_matrix_check);
  suite_add_tcase(s, tc_inv);

  return s;
}

int main(void) {
  Suite* s = matrix_suite();
  SRunner* sr = srunner_create(s);
  srunner_run_all(sr, CK_NORMAL);
  int failed = srunner_ntests_failed(sr);
  srunner_free(sr);
  return failed == 0 ? 0 : 1;
}