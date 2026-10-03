# Компилятор и флаги
CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -g
LIBS = -lm
CHECK_FLAGS = $(shell pkg-config --cflags --libs check)

# Имя итоговой библиотеки
TARGET = s21_matrix.a

# Исходные файлы
SRCS = s21_create_matrix.c s21_remove_matrix.c s21_eq_matrix.c \
       s21_sum_matrix.c s21_sub_matrix.c s21_mult_matrix.c \
       s21_mult_number.c s21_transpose.c s21_determinant.c \
       s21_calc_complements.c s21_inverse_matrix.c help_func.c

# Объектные файлы
OBJS = $(SRCS:.c=.o)

# Тесты
TEST_DIR = tests
TEST_SRC = $(TEST_DIR)/s21_tests_matrix.c
TEST_TARGET = s21_tests

# Цель по умолчанию
all: $(TARGET)

# Сборка статической библиотеки
$(TARGET): $(OBJS)
	ar rcs $(TARGET) $(OBJS)
	ranlib $(TARGET)

# Компиляция .c в .o (БЕЗ флагов check, так как matrix.h не должен требовать check.h)
%.o: %.c s21_matrix.h
	$(CC) $(CFLAGS) -c $< -o $@

# Сборка и запуск тестов (ТОЛЬКО здесь нужны флаги check)
test: $(TARGET)
	$(CC) $(CFLAGS) $(TEST_SRC) $(TARGET) -o $(TEST_TARGET) $(LIBS) $(CHECK_FLAGS)
	./$(TEST_TARGET)

# Запуск тестов с детальным выводом
test_verbose: $(TARGET)
	$(CC) $(CFLAGS) $(TEST_SRC) $(TARGET) -o $(TEST_TARGET) $(LIBS) $(CHECK_FLAGS)
	./$(TEST_TARGET) --verbose

# Запуск тестов с valgrind
test_valgrind: $(TARGET)
	$(CC) $(CFLAGS) $(TEST_SRC) $(TARGET) -o $(TEST_TARGET) $(LIBS) $(CHECK_FLAGS)
	valgrind --leak-check=full --track-origins=yes ./$(TEST_TARGET)

# Проверка покрытия с выводом в консоль
gcov: CFLAGS += --coverage
gcov: clean
	$(MAKE) gcov_lib
	$(CC) $(CFLAGS) $(GCOV_FLAGS) $(TEST_SRC) $(TARGET) -o $(TEST_TARGET) $(LIBS) $(CHECK_FLAGS)
	./$(TEST_TARGET)
	-gcov $(SRCS) 2>/dev/null || true  # Игнорируем ошибку gcov

# Генерация HTML отчета о покрытии
gcov_report: CFLAGS += --coverage
gcov_report: clean $(TARGET)
	$(CC) $(CFLAGS) $(TEST_SRC) $(TARGET) -o $(TEST_TARGET) $(LIBS) $(CHECK_FLAGS)
	./$(TEST_TARGET)
	lcov --capture --directory . --output-file coverage.info --ignore-errors mismatch
	lcov --remove coverage.info '/usr/*' --output-file coverage.info --ignore-errors unused
	lcov --remove coverage.info '*/tests/*' --output-file coverage.info --ignore-errors unused
	genhtml coverage.info --output-directory coverage_report
	@echo "========================================="
	@echo "Coverage report generated in coverage_report/"
	@echo "Open coverage_report/index.html in your browser"
	@echo "========================================="
	@open coverage_report/index.html 2>/dev/null || xdg-open coverage_report/index.html 2>/dev/null || echo "Please open coverage_report/index.html manually"

# Очистка
clean:
	rm -f $(OBJS) $(TARGET) $(TEST_TARGET)
	rm -f *.gcda *.gcno *.gcov *.info
	rm -rf coverage_report/

# Полная пересборка
rebuild: clean all

.PHONY: all clean rebuild test test_verbose test_valgrind gcov gcov_report