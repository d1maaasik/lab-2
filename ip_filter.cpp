#include <cassert> // Для проверки условий в коде (assert)
#include <cstdlib> // Для std::stoi (преобразование строки в число)
#include <iostream> // Для вывода в консоль
#include <fstream> // Для работы с файлами
#include <string> // Для работы со строками
#include <vector> // Для работы с динамическими массивами
#include <algorithm> // Для std::sort
#include "ip_filter.h" // Заголовочный файл для работы с фильтрацией IP

// Функция для разделения строки на части
std::vector<std::string> split(const std::string& str, char d) {
    std::vector<std::string> r;

    if (str.empty()) return r;

    auto start = 0U;
    auto stop = str.find_first_of(d);

    while (stop != std::string::npos) {
        r.push_back(str.substr(start, stop - start));
        start = stop + 1;
        stop = str.find_first_of(d, start);
    }

    r.push_back(str.substr(start)); // добавляем последнюю часть
    return r;
}

int main() {
    try {
        std::vector<std::vector<std::string>> ip_pool;

        // Открытие файла для чтения
        std::ifstream file("D:/progrlab2/02/ip_filter.tsv");
        if (!file.is_open()) {
            throw std::runtime_error("Не удалось открыть файл ip_filter.tsv");
        }

        // Чтение IP-адресов из файла
        for (std::string line; std::getline(file, line);) {
            // Разделяем строку по табуляции и затем IP-адрес по точке
            ip_pool.push_back(split(split(line, '\t')[0], '.'));
        }

        file.close(); // Закрытие файла после чтения

        // Лексикографическая сортировка IP-адресов с лямбда-функцией
        std::sort(ip_pool.begin(), ip_pool.end(), [](const auto& a, const auto& b) {
            for (size_t i = 0; i < 4; ++i) {
                int partA = (i < a.size()) ? std::stoi(a[i]) : 0;
                int partB = (i < b.size()) ? std::stoi(b[i]) : 0;
                if (partA != partB) return partA > partB;
            }
            return false;
        });

        // Вывод отсортированных IP-адресов
        std::cout << "Список адресов после сортировки:\n";
        for (const auto& ip : ip_pool) {
            for (size_t i = 0; i < ip.size(); ++i) {
                if (i != 0) std::cout << ".";
                std::cout << ip[i];
            }
            std::cout << "\n";
        }

        // Вывод IP с первым байтом равным 1
        std::cout << "Вывод IP с первым байтом 1:\n";
        std::for_each(ip_pool.begin(), ip_pool.end(), [](const auto& ip) {
            if (!ip.empty() && std::stoi(ip[0]) == 1) {
                for (size_t i = 0; i < ip.size(); ++i) {
                    if (i != 0) std::cout << ".";
                    std::cout << ip[i];
                }
                std::cout << "\n";
            }
        });

        // Вывод IP с первым байтом 46 и вторым 70
        std::cout << "Вывод IP с первым байтом 46 и вторым 70:\n";
        std::for_each(ip_pool.begin(), ip_pool.end(), [](const auto& ip) {
            if (ip.size() >= 2 && std::stoi(ip[0]) == 46 && std::stoi(ip[1]) == 70) {
                for (size_t i = 0; i < ip.size(); ++i) {
                    if (i != 0) std::cout << ".";
                    std::cout << ip[i];
                }
                std::cout << "\n";
            }
        });

        // Вывод IP с любым байтом равным 46
        std::cout << "Вывод IP с байтом равным 46:\n";
        std::for_each(ip_pool.begin(), ip_pool.end(), [](const auto& ip) {
            if (std::any_of(ip.begin(), ip.end(), [](const auto& part) {
                return std::stoi(part) == 46;
            })) {
                for (size_t i = 0; i < ip.size(); ++i) {
                    if (i != 0) std::cout << ".";
                    std::cout << ip[i];
                }
                std::cout << "\n";
            }
        });

    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
} 