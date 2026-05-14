#include <cmath>
#include <expected>
#include <format>
#include <iostream>
#include <limits>
#include <string>

struct Coefficients {
  double a{};
  double b{};
  double c{};
};

std::expected<Coefficients, std::string> getCoefficients() {
  std::cout << "Введите a, b, c (через пробел, a != 0): ";

  Coefficients vals{};
  if (!(std::cin >> vals.a >> vals.b >> vals.c)) {
    if (std::cin.eof())
      return std::unexpected("Ввод завершен (EOF)");

    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    return std::unexpected("Ожидается три числа через пробел");
  }

  if (vals.a == 0.0) {
    return std::unexpected("Коэффициент a не может быть равен нулю");
  }

  return vals;
}

int main() {
  auto res{getCoefficients()};
  if (!res) {
    std::cerr << std::format("Ошибка: {}\n", res.error());
    return 1;
  }

  auto [a, b, c]{*res};
  double k{a + b};

  bool hasRealRoots{true};
  if (k == 0.0 && c != 0.0) {
    hasRealRoots = false;
  }

  std::cout << (hasRealRoots ? "Уравнение имеет вещественные корни\n"
                             : "Уравнение не имеет вещественных корней\n");

  if (k != 0.0) {
    std::cout << std::format("x = {:.4f}\n", -c / k);
  } else if (c == 0.0) {
    std::cout << "Любое x является решением" << '\n';
  }

  return 0;
}
