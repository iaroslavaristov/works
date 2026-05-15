#include <algorithm>
#include <cctype>
#include <cstring>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <limits>
#include <sstream>
#include <string>
#include <vector>

void part1_task1() {
  const char *str{"Привет 123 мир 456 тест 78 конец"};
  std::cout << "    ЗАДАЧА 1.1: Поиск чисел в строке    \n";
  std::cout << "Исходная строка: " << str << "\n\n";

  int sum{};
  bool found{};
  const char *ptr{str};

  while (*ptr) {
    while (*ptr && !isdigit(*ptr) && *ptr != '-') {
      ptr++;
    }

    if (*ptr) {
      char numStr[20];
      int i{};

      if (*ptr == '-') {
        numStr[i++] = *ptr++;
      }

      while (*ptr && isdigit(*ptr)) {
        numStr[i++] = *ptr++;
      }
      numStr[i] = '\0';

      int num{atoi(numStr)};
      std::cout << "Найдено число: " << num << "\n";
      sum += num;
      found = true;
    }
  }

  if (found) {
    std::cout << "\nСумма всех чисел: " << sum << "\n";
  } else {
    std::cout << "\nЧисла в строке не найдены\n";
  }
}

void capitalizeUtf8(char *str) {
  bool newWord{true};
  for (int i{}; str[i] != '\0'; ++i) {
    unsigned char c{static_cast<unsigned char>(str[i])};
    if (c == ' ' || c == '\t') {
      newWord = true;
    } else if (newWord && c == 0xD0 &&
               static_cast<unsigned char>(str[i + 1]) >= 0xB0) {
      str[i + 1] =
          static_cast<char>(static_cast<unsigned char>(str[i + 1]) - 0x20);
      newWord = false;
      ++i;
    } else if (newWord && c == 0xD1 &&
               static_cast<unsigned char>(str[i + 1]) >= 0x80 &&
               static_cast<unsigned char>(str[i + 1]) <= 0x8F) {
      str[i] = static_cast<char>(0xD0);
      str[i + 1] =
          static_cast<char>(static_cast<unsigned char>(str[i + 1]) + 0x20);
      newWord = false;
      ++i;
    } else if (newWord && isalpha(c)) {
      str[i] = static_cast<char>(toupper(c));
      newWord = false;
    } else if (!isspace(c)) {
      newWord = false;
    }
  }
}

void part1_task2() {
  char str[256]{};
  std::cout << "ЗАДАЧА 1.2: заглавные буквы\n";
  std::cout << "Введите строку (до точки): ";
  std::cin.getline(str, 256);

  char *dot{strchr(str, '.')};
  if (dot)
    *dot = '\0';

  std::cout << "Исходная строка: " << str << "\n";
  capitalizeUtf8(str);
  std::cout << "Результат: " << str << "\n";
}
bool containsLetterA(const std::string &word) {
  return word.find("а") != std::string::npos ||
         word.find("А") != std::string::npos;
}

std::vector<std::string> splitIntoWords(const std::string &str) {
  std::vector<std::string> words;
  std::string word;
  for (char c : str) {
    if (isspace(static_cast<unsigned char>(c))) {
      if (!word.empty()) {
        words.push_back(word);
        word.clear();
      }
    } else {
      word += c;
    }
  }
  if (!word.empty()) {
    words.push_back(word);
  }
  return words;
}

void part2_task1() {
  std::string filename{"task2_1.txt"};

  std::ofstream outFile{filename};
  outFile << "мама мыла раму\n";
  outFile << "привет мир\n";
  outFile << "как дела\n";
  outFile << "хорошая погода\n";
  outFile.close();

  std::cout << "\n    ЗАДАЧА 2.1: Фразы с буквой 'а'    \n";
  std::cout << "Исходный файл:\n";

  std::ifstream inFile{filename};
  std::vector<std::string> phrases;
  std::string line;
  while (std::getline(inFile, line)) {
    phrases.push_back(line);
    std::cout << "  " << line << "\n";
  }
  inFile.close();

  std::vector<std::string> result;
  for (const auto &phrase : phrases) {
    auto words{splitIntoWords(phrase)};
    bool allHaveA{true};
    for (const auto &word : words) {
      if (!containsLetterA(word)) {
        allHaveA = false;
        break;
      }
    }
    if (allHaveA && !words.empty()) {
      result.push_back(phrase);
    }
  }

  outFile.open(filename);
  for (const auto &phrase : result) {
    outFile << phrase << "\n";
  }
  outFile.close();

  std::cout << "\nРезультат (оставлены фразы, где все слова содержат 'а'):\n";
  for (const auto &phrase : result) {
    std::cout << "  " << phrase << "\n";
  }
}

void part2_task2() {
  std::string inputFile{"task2_2_matrix.txt"};
  std::string outputFile{"task2_2_result.txt"};

  std::ofstream outFile{inputFile};
  outFile << "1 2 3 4\n";
  outFile << "5 6 7 8\n";
  outFile << "9 10 11 12\n";
  outFile << "13 14 15 16\n";
  outFile.close();

  std::cout << "\n    ЗАДАЧА 2.2: Разрыв матрицы    \n";
  std::cout << "Исходная матрица:\n";

  std::ifstream inFile{inputFile};
  std::vector<std::vector<int>> matrix;
  std::string line;
  while (std::getline(inFile, line)) {
    std::istringstream iss{line};
    std::vector<int> row;
    int val;
    while (iss >> val) {
      row.push_back(val);
    }
    if (!row.empty()) {
      matrix.push_back(row);
    }
  }
  inFile.close();

  for (const auto &row : matrix) {
    for (int val : row) {
      std::cout << std::setw(4) << val;
    }
    std::cout << "\n";
  }

  int n{static_cast<int>(matrix.size())};

  outFile.open(outputFile);

  outFile << "Над диагональю:\n";
  for (int i{}; i < n; ++i) {
    for (int j{}; j < n; ++j) {
      if (j > i) {
        outFile << std::setw(4) << matrix[i][j];
      } else {
        outFile << "    ";
      }
    }
    outFile << "\n";
  }

  outFile << "Диагональ:";
  for (int i{}; i < n; ++i) {
    outFile << std::setw(4) << matrix[i][i];
  }
  outFile << "\n";

  outFile << "Под диагональю:\n";
  for (int i{}; i < n; ++i) {
    for (int j{}; j < n; ++j) {
      if (j < i) {
        outFile << std::setw(4) << matrix[i][j];
      } else {
        outFile << "    ";
      }
    }
    outFile << "\n";
  }

  outFile.close();

  std::cout << "\nРезультат записан в файл " << outputFile << "\n";
  std::cout << "Содержимое файла:\n";

  inFile.open(outputFile);
  while (std::getline(inFile, line)) {
    std::cout << line << "\n";
  }
  inFile.close();
}

void part2_task3() {
  std::string filename{"task2_3.bin"};

  std::ofstream outFile{filename, std::ios::binary};
  int testValues[]{5, 3, 8, 1, 9, 2};
  for (int val : testValues) {
    outFile.write(reinterpret_cast<const char *>(&val), sizeof(int));
  }
  outFile.close();

  std::cout << "\n    ЗАДАЧА 2.3: Модификация бинарного файла    \n";
  std::cout << "Исходные данные: ";
  for (int val : testValues) {
    std::cout << val << " ";
  }
  std::cout << "\n";

  std::ifstream inFile{filename, std::ios::binary};
  std::vector<int> allNumbers;
  int num;
  while (inFile.read(reinterpret_cast<char *>(&num), sizeof(int))) {
    allNumbers.push_back(num);
  }
  inFile.close();

  int maxVal{*std::max_element(allNumbers.begin(), allNumbers.end())};
  std::cout << "Максимальное значение: " << maxVal << "\n";

  std::fstream file{filename,
                    std::ios::out | std::ios::binary | std::ios::trunc};

  int startMarker{-1};
  file.write(reinterpret_cast<const char *>(&startMarker), sizeof(int));

  for (int n : allNumbers) {
    file.write(reinterpret_cast<const char *>(&n), sizeof(int));
  }

  int endMarker{maxVal + 1};
  file.write(reinterpret_cast<const char *>(&endMarker), sizeof(int));

  file.close();

  file.open(filename, std::ios::in | std::ios::binary);
  std::vector<int> result;
  while (file.read(reinterpret_cast<char *>(&num), sizeof(int))) {
    result.push_back(num);
  }
  file.close();

  std::cout << "Результат: ";
  for (int n : result) {
    std::cout << n << " ";
  }
  std::cout << "\n";
  std::cout << "(Первое число: -1, последнее: max+1 = " << (maxVal + 1)
            << ")\n";
}

int main() {
  std::cout << "Лабораторная работа: Файлы и строки\n";
  std::cout << "\n\n";

  int part;
  while (true) {
    std::cout << "Выберите часть:\n";
    std::cout << "  1 - Часть 1 (C-строки)\n";
    std::cout << "  2 - Часть 2 (C++ строки и файлы)\n";
    std::cout << "  0 - Выход\n";
    std::cout << "> ";

    std::cin >> part;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    if (part == 0) {
      std::cout << "Выход из программы.\n";
      break;
    }

    if (part == 1) {
      while (true) {
        std::cout << "\n--- ЧАСТЬ 1 (C-строки) ---\n";
        std::cout << "  1 - Задача 1 (найти числа в строке)\n";
        std::cout << "  2 - Задача 2 (заглавные буквы)\n";
        std::cout << "  0 - Назад\n";
        std::cout << "> ";

        int choice;
        std::cin >> choice;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if (choice == 0)
          break;

        switch (choice) {
        case 1:
          part1_task1();
          break;
        case 2:
          part1_task2();
          break;
        default:
          std::cout << "Неверный выбор\n";
        }
      }
    } else if (part == 2) {
      while (true) {
        std::cout << "\n--- ЧАСТЬ 2 (C++ строки и файлы) ---\n";
        std::cout << "  1 - Задача 1 (фразы с буквой 'а')\n";
        std::cout << "  2 - Задача 2 (разрыв матрицы)\n";
        std::cout << "  3 - Задача 3 (бинарный файл)\n";
        std::cout << "  0 - Назад\n";
        std::cout << "> ";

        int choice;
        std::cin >> choice;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if (choice == 0)
          break;

        switch (choice) {
        case 1:
          part2_task1();
          break;
        case 2:
          part2_task2();
          break;
        case 3:
          part2_task3();
          break;
        default:
          std::cout << "Неверный выбор\n";
        }
      }
    } else {
      std::cout << "Неверный выбор части\n";
    }
  }

  return 0;
}
