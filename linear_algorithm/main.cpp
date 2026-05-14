#include <expected>
#include <format>
#include <iostream>
#include <limits>
#include <string>

constexpr double TARIFF{3.0};

std::expected<double, std::string> getEnergy() {
  std::cout << "Введите количество кВт: ";

  double value{};

  if (!(std::cin >> value)) {
    if (std::cin.eof())
      return std::unexpected("Ввод заверешен (EOF)");

    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    return std::unexpected("Введите корректное число");
  }

  if (value < 0.0) {
    return std::unexpected("Значение не может быть отрицательным");
  }

  return value;
}

int main() {
  std::cout << std::format(
      "Стоимость электроэнергии (тариф: {:.2f} Р/кВт * ч)\n\n", TARIFF);

  while (1) {
    auto result{getEnergy()};

    if (result) {
      double total{*result * TARIFF};
      std::cout << std::format("К оплате: {:.2f} Р\n", total);
      break;
    }

    std::cerr << std::format("Ошибка: {}\n", result.error());
  }

  return 0;
}
