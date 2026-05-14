#include <algorithm>
#include <cmath>
#include <cstddef>
#include <iomanip>
#include <iostream>
#include <limits>
#include <random>

std::mt19937 gen(std::random_device{}());

int *createArray1D(const std::size_t size) { return new int[size]; }

double **createMatrix(const std::size_t rows, const std::size_t cols) {
  double **matrix{new double *[rows]};
  for (std::size_t i{}; i < rows; ++i) {
    matrix[i] = new double[cols];
  }
  return matrix;
}

int ***createArray3D(const std::size_t d1, const std::size_t d2,
                     const std::size_t d3) {
  int ***arr{new int **[d1]};
  for (std::size_t i{}; i < d1; ++i) {
    arr[i] = new int *[d2];
    for (std::size_t j{}; j < d2; ++j) {
      arr[i][j] = new int[d3];
    }
  }
  return arr;
}

void fillArray1D(int *const arr, const std::size_t size, const int min_val,
                 const int max_val) {
  std::uniform_int_distribution<> dist(min_val, max_val);
  for (std::size_t i{}; i < size; ++i) {
    arr[i] = dist(gen);
  }
}

void fillMatrix(double **const matrix, const std::size_t rows,
                const std::size_t cols, const double min_val,
                const double max_val) {
  std::uniform_real_distribution<> dist(min_val, max_val);
  for (std::size_t i{}; i < rows; ++i) {
    for (std::size_t j{}; j < cols; ++j) {
      matrix[i][j] = dist(gen);
    }
  }
}

void fillArray3D(int ***const arr, const std::size_t d1, const std::size_t d2,
                 const std::size_t d3, const int min_val, const int max_val) {
  std::uniform_int_distribution<> dist(min_val, max_val);
  for (std::size_t i{}; i < d1; ++i) {
    for (std::size_t j{}; j < d2; ++j) {
      for (std::size_t k{}; k < d3; ++k) {
        arr[i][j][k] = dist(gen);
      }
    }
  }
}

void printArray1D(const int *const arr, const std::size_t size) {
  for (std::size_t i{}; i < size; ++i) {
    std::cout << std::setw(6) << arr[i] << " ";
    if ((i + 1) % 10 == 0)
      std::cout << "\n";
  }
  std::cout << "\n";
}

void printMatrix(double *const *const matrix, const std::size_t rows,
                 const std::size_t cols) {
  for (std::size_t i{}; i < rows; ++i) {
    for (std::size_t j{}; j < cols; ++j) {
      std::cout << std::fixed << std::setprecision(2) << std::setw(8)
                << matrix[i][j] << " ";
    }
    std::cout << "\n";
  }
}

void deleteArray1D(int *const arr) { delete[] arr; }

void deleteMatrix(double **const matrix, const std::size_t rows) {
  for (std::size_t i{}; i < rows; ++i) {
    delete[] matrix[i];
  }
  delete[] matrix;
}

void deleteArray3D(int ***const arr, const std::size_t d1,
                   const std::size_t d2) {
  for (std::size_t i{}; i < d1; ++i) {
    for (std::size_t j{}; j < d2; ++j) {
      delete[] arr[i][j];
    }
    delete[] arr[i];
  }
  delete[] arr;
}

void task1() {
  std::cout << "\nЗАДАЧА 1: вставка 0 в середину массива\n";

  const std::size_t SIZE{20};
  int *arr{createArray1D(SIZE + 1)};

  fillArray1D(arr, SIZE, 1, 100);

  std::cout << "Исходный массив (20 элементов):\n";
  printArray1D(arr, SIZE);

  for (std::size_t i{SIZE - 1}; i >= 10; --i) {
    *(arr + i + 1) = *(arr + i);
  }

  *(arr + 10) = 0;

  std::cout << "\nМассив после вставки 0 (21 элемент):\n";
  printArray1D(arr, SIZE + 1);

  deleteArray1D(arr);
}

void task2() {
  std::cout << "\nЗАДАЧА 2: сортировка по убыванию\n";

  const std::size_t SIZE{15};
  int *arr{createArray1D(SIZE)};

  fillArray1D(arr, SIZE, 1, 100);

  std::cout << "Исходный массив:\n";
  printArray1D(arr, SIZE);

  for (std::size_t i{}; i < SIZE - 1; ++i) {
    for (std::size_t j{}; j < SIZE - 1 - i; ++j) {
      if (arr[j] < arr[j + 1]) {
        std::swap(arr[j], arr[j + 1]);
      }
    }
  }

  std::cout << "\nОтсортированный массив (по убыванию):\n";
  printArray1D(arr, SIZE);

  deleteArray1D(arr);
}

void task3() {
  std::cout << "\nЗАДАЧА 3: обмен первого с максимальным по модулю\n";

  const std::size_t ROWS{7};
  const std::size_t COLS{9};
  double **matrix{createMatrix(ROWS, COLS)};

  fillMatrix(matrix, ROWS, COLS, -50.0, 50.0);

  std::cout << "Исходная матрица:\n";
  printMatrix(matrix, ROWS, COLS);

  for (std::size_t i{}; i < ROWS; ++i) {
    double max_abs{std::abs(matrix[i][0])};
    std::size_t max_col{};
    int count_max{1};

    for (std::size_t j{1}; j < COLS; ++j) {
      double abs_val{std::abs(matrix[i][j])};
      if (abs_val > max_abs) {
        max_abs = abs_val;
        max_col = j;
        count_max = 1;
      } else if (abs_val == max_abs) {
        ++count_max;
      }
    }

    if (count_max == 1 && max_col != 0) {
      std::swap(matrix[i][0], matrix[i][max_col]);
    }
  }

  std::cout << "\nМатрица после обработки:\n";
  printMatrix(matrix, ROWS, COLS);

  deleteMatrix(matrix, ROWS);
}

void task4() {
  std::cout << "\nЗАДАЧА 4: cумма справа от побочной диагонали\n";

  const std::size_t SIZE{6};

  double **matrix{createMatrix(SIZE, SIZE)};

  fillMatrix(matrix, SIZE, SIZE, -20.0, 20.0);

  std::cout << "Квадратная матрица:\n";
  printMatrix(matrix, SIZE, SIZE);

  double sum{0.0};

  for (std::size_t i{}; i < SIZE; ++i) {
    for (std::size_t j{}; j < SIZE; ++j) {
      if (j > SIZE - 1 - i) {
        sum += matrix[i][j];
      }
    }
  }

  std::cout << std::fixed << std::setprecision(2);
  std::cout << "\nСумма элементов справа от побочной диагонали: " << sum
            << "\n";

  deleteMatrix(matrix, SIZE);
}

void task5() {
  std::cout << "\nЗАДАЧА 5: анализ успеваемости групп\n";

  const std::size_t GROUPS{3};
  const std::size_t STUDENTS{25};
  const std::size_t EXAMS{4};

  int ***results{createArray3D(GROUPS, STUDENTS, EXAMS)};

  fillArray3D(results, GROUPS, STUDENTS, EXAMS, 1, 4);

  std::cout << "Анализ результатов сессии:\n";
  std::cout << "Групп | Студентов | Средний балл\n";
  std::cout << "------|-----------|-------------\n";

  double max_avg{0.0};
  std::size_t best_group{};

  for (std::size_t g{}; g < GROUPS; ++g) {
    double sum{0.0};
    int count{};

    for (std::size_t s{}; s < STUDENTS; ++s) {
      for (std::size_t e{}; e < EXAMS; ++e) {
        int grade{results[g][s][e]};
        if (grade > 1) {
          sum += grade;
          ++count;
        }
      }
    }

    double avg{count > 0 ? sum / count : 0.0};

    std::cout << "  " << (g + 1) << "   |    " << STUDENTS << "    | "
              << std::fixed << std::setprecision(2) << avg << "\n";

    if (avg > max_avg) {
      max_avg = avg;
      best_group = g + 1;
    }
  }

  std::cout << "\nЛучше всех подготовилась группа " << best_group
            << " со средним баллом " << max_avg << "\n";

  deleteArray3D(results, GROUPS, STUDENTS);
}

int main() {
  std::cout << "Решение задач\n";

  while (true) {
    std::cout << "\nВыберите задачу:\n";
    std::cout << "  1 - Вставка 0 в середину массива (адресная арифметика)\n";
    std::cout << "  2 - Сортировка по убыванию\n";
    std::cout << "  3 - Обмен в матрице (первый с максимальным по модулю)\n";
    std::cout << "  4 - Сумма справа от побочной диагонали\n";
    std::cout << "  5 - Анализ успеваемости групп (3D массив)\n";
    std::cout << "  0 - Выход\n";
    std::cout << "> ";

    int choice;
    std::cin >> choice;

    if (!std::cin) {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      std::cout << "Некорректный ввод. Попробуйте снова.\n";
      continue;
    }

    switch (choice) {
    case 1:
      task1();
      break;
    case 2:
      task2();
      break;
    case 3:
      task3();
      break;
    case 4:
      task4();
      break;
    case 5:
      task5();
      break;
    case 0:
      std::cout << "Выход из программы.\n";
      return 0;
    default:
      std::cout << "Неверный номер задачи. Попробуйте снова.\n";
    }
  }

  return 0;
}
