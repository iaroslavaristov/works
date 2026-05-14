#include <cmath>
#include <cstddef>
#include <expected>
#include <format>
#include <iostream>
#include <limits>
#include <string>

std::expected<double, std::string> calculateZ(const double x) {
  if (x == 0.0)
    return std::unexpected("x не может быть равен нулю");

  double tanSq{std::tan(x) * std::tan(x)};
  double lnVal{std::log(3 * x * x)};
  double expSin{std::exp(std::sin(x))};
  double pi7{M_PI / 7.0};
  double denomInside{std::abs(expSin - pi7)};

  if (denomInside == 0.0)
    return std::unexpected("Знаменатель равен нулю (e^(sin x) = π/7)");

  double result{(tanSq - lnVal) / std::sqrt(denomInside)};
  return result;
}

void ignoreLine() {
  std::cin.clear();
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void task2() {
  std::cout << "\nЗАДАЧА 2: вычисление Z\n\n";

  while (true) {
    std::cout << "Введите x: ";
    double x{};
    std::cin >> x;

    if (!std::cin) {
      ignoreLine();
      std::cout << "Ошибка ввода. Попробуйте снова.\n\n";
      continue;
    }

    auto result{calculateZ(x)};
    if (result) {
      std::cout << std::format("Z = {:.2f}\n\n", *result);
      break;
    } else {
      std::cout << "Ошибка: " << result.error() << '\n';
      std::cout << "Попробуйте снова." << "\n\n";
    }
  }
}

void task4() {
  std::cout << "\nЗАДАЧА 4: прямоугольники с плозадью K\n";

  unsigned int k{};
  std::cout << "Введите площадь K: ";
  std::cin >> k;

  if (!std::cin || k == 0) {
    ignoreLine();
    std::cout << "Ошибка. K должно быть натуральным числом.\n\n";
    return;
  }

  std::cout << "\nПрямоугольники с площадью " << k << ":\n";
  bool found{false};

  for (unsigned int a{1}; a * a <= k; ++a) {
    if (k % a == 0) {
      unsigned int b{k / a};
      std::cout << " " << a << " x " << b << '\n';
      found = true;
    }
  }

  if (!found) {
    std::cout << "  Нет таких прямоугольников\n";
  }
}

void task5() {
  std::cout << "\nЗАДАЧА 5: прогрессия спортсмена\n";

  double distance{10.0};
  int day{1};

  while (distance <= 20) {
    ++day;
    distance *= 1.10;
  }

  std::cout << "Спортсмен пробежит больше 20 км на " << day << " день\n";
  std::cout << std::format("Расстояние: {:.2f} км\n\n", distance);
}

void task6() {
  std::cout << "\nЗАДАЧА 6: проверка на палиндром\n";

  using ull = unsigned long long;

  ull N{};

  std::cout << "Введите натуральное число N: ";
  std::cin >> N;

  if (!std::cin) {
    ignoreLine();
    std::cout << "Ошибка ввода\n\n";
    return;
  }

  ull original{N};
  ull reversed{};

  do {
    reversed = reversed * 10 + N % 10;
    N /= 10;
  } while (N > 0);

  if (original == reversed) {
    std::cout << "Число " << original << " является палиндромом\n\n";
  } else {
    std::cout << "Число " << original << " не является палиндромом\n";
    std::cout << "В обратном порядке: " << reversed << "\n\n";
  }
}

void task8() {
  std::cout << "\nЗАДАЧА 8: сумма бесконечного ряда\n";

  double x{};
  std::cout << "Введите x (0.2 <= x <= 1): ";
  std::cin >> x;

  if (!std::cin || x < 0.2 || x > 1.0) {
    ignoreLine();
    std::cout << "Ошибка: x должен быть в диапазоне [0.2, 1]\n\n";
    return;
  }

  constexpr double EPS{1e-4};
  double t{(x - 1) / (x + 1)};
  double sum{t};
  double term{t};
  int n{1};

  while (true) {
    term = term * t * t;
    double newTerm = term / (2 * n + 1);

    if (std::abs(newTerm) < EPS)
      break;

    sum += newTerm;
    ++n;
  }

  double checkValue{0.5 * std::log(x)};
  std::cout << "\nРезультаты:\n";
  std::cout << std::format("  Сумма ряда: {:.6f}\n", sum);
  std::cout << std::format("  Проверка (0.5*ln(x)): {:.6f}\n", checkValue);
  std::cout << std::format("  Погрешность: {:.6f}\n",
                           std::abs(sum - checkValue));
  std::cout << std::format("  Число итераций: {}\n\n", n);
}

int main() {
  std::cout << "Решение задач\n\n";

  while (true) {
    std::cout << "Выберите задачу:\n";
    std::cout << "  2 - Вычисление функции Z\n";
    std::cout << "  4 - Прямоугольники (for)\n";
    std::cout << "  5 - Спортсмен (while)\n";
    std::cout << "  6 - Палиндром (do...while)\n";
    std::cout << "  8 - Бесконечный ряд\n";
    std::cout << "  0 - Выход\n";
    std::cout << "> ";

    int choice;
    std::cin >> choice;

    if (!std::cin) {
      ignoreLine();
      std::cout << "Некорректный ввод. Попробуйте снова.\n\n";
      continue;
    }

    switch (choice) {
    case 2: {
      task2();
      break;
    }
    case 4: {
      task4();
      break;
    }
    case 5: {
      task5();
      break;
    }
    case 6: {
      task6();
      break;
    }
    case 8: {
      task8();
      break;
    }
    case 0: {
      std::cout << "Выход из программы.\n";
      return 0;
    }
    default: {
      std::cout << "Неверный номер задачи. Попробуйте снова.\n\n";
    }
    }
  }

  return 0;
}
