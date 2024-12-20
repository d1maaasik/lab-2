#include <cassert> // Для проверки условий в коде (assert)
#include <cstdlib> // Для std::stoi (преобразование строки в число)
#include <iostream> // Для вывода в консоль
#include <fstream> // Для работы с файлами
#include <string> // Для работы со строками
#include <vector> // Для работы с динамическими массивами
#include <algorithm> // Для std::sort
#include "ip_filter.h" // Заголовочный файл для работы с фильтрацией IP

// Функция для разделения строки на части
std::vector<std::string> split(const std::string &str, char d) {
    std::vector<std::string> r; // Результирующий вектор

    // Если строка пустая, возвращаем пустой вектор
    if (str.empty()) {
        return r;
    }

    std::string::size_type start = 0; // Начальная позиция текущей подстроки
    std::string::size_type stop = str.find_first_of(d); // Находим позицию первого разделителя

    // Проходим по всей строке и разделяем её на части
    while (stop != std::string::npos) {
        // Добавляем подстроку в результирующий вектор
        r.push_back(str.substr(start, stop - start));
        start = stop + 1; // Сдвигаем начальную позицию за разделитель
        stop = str.find_first_of(d, start); // Ищем следующий разделитель
    }
    
    // Добавляем последнюю часть строки (после последнего разделителя)
    r.push_back(str.substr(start));
    
    return r; // Возвращаем вектор частей строки
}

// Функция для сравнения двух IP-адресов (для сортировки)
bool compareIPs(const std::vector<std::string>& a, const std::vector<std::string>& b) {
    // Проходим по каждому из первых 4 байтов IP-адреса
    for (size_t i = 0; i < 4; ++i) {
        // Преобразуем строку в число для сравнения, если часть отсутствует, используем 0
        int partA = (i < a.size()) ? std::stoi(a[i]) : 0;
        int partB = (i < b.size()) ? std::stoi(b[i]) : 0;

        // Если текущие байты различны, возвращаем результат сравнения
        if (partA != partB) {
            return partA > partB; // Сортировка в убывающем порядке
        }
    }
    return false; // Если все байты равны
}

// Функция для вывода IP-адресов на экран
void printIPAddresses(const std::vector<std::vector<std::string>>& ip_pool) {
    // Проходим по каждому IP-адресу
    for (const auto& ip : ip_pool) {
        // Выводим каждую часть IP-адреса
        for (size_t i = 0; i < ip.size(); ++i) {
            if (i != 0) {
                std::cout << "."; // Добавляем точку между байтами
            }
            std::cout << ip[i];
        }
        std::cout << std::endl; // Завершаем вывод строки
    }
}

// Функция для вывода IP-адресов, у которых первый байт равен заданному значению
void printIPsWithFirstByte(const std::vector<std::vector<std::string>>& ip_pool, int first_byte) {
    for (const auto& ip : ip_pool) {
        // Проверяем, равен ли первый байт заданному значению
        if (!ip.empty() && std::stoi(ip[0]) == first_byte) {
            // Выводим IP-адрес
            for (size_t i = 0; i < ip.size(); ++i) {
                if (i != 0) {
                    std::cout << ".";
                }
                std::cout << ip[i];
            }
            std::cout << std::endl;
        }
    }
}

// Функция для вывода IP-адресов, у которых первый и второй байт равны заданным значениям
void printIPsWithFirstAndSecondByte(const std::vector<std::vector<std::string>>& ip_pool, int first_byte, int second_byte) {
    for (const auto& ip : ip_pool) {
        // Проверяем, соответствуют ли первый и второй байт заданным значениям
        if (ip.size() >= 2 && std::stoi(ip[0]) == first_byte && std::stoi(ip[1]) == second_byte) {
            for (size_t i = 0; i < ip.size(); ++i) {
                if (i != 0) {
                    std::cout << ".";
                }
                std::cout << ip[i];
            }
            std::cout << std::endl;
        }
    }
}

// Функция для вывода IP-адресов, у которых хотя бы один байт равен заданному значению
void printIPsWithAnyByte(const std::vector<std::vector<std::string>>& ip_pool, int byte_value) {
    for (const auto& ip : ip_pool) {
        for (const auto& part : ip) {
            // Проверяем, равен ли текущий байт заданному значению
            if (std::stoi(part) == byte_value) {
                for (size_t i = 0; i < ip.size(); ++i) {
                    if (i != 0) {
                        std::cout << ".";
                    }
                    std::cout << ip[i];
                }
                std::cout << std::endl;
                break; // Выходим, чтобы избежать дублирования вывода
            }
        }
    }
}

int main(){
    try {
        std::vector<std::vector<std::string>> ip_pool; // Вектор для хранения IP-адресов

        // Открываем файл для чтения
        std::ifstream file("D:/progrlab2/02/ip_filter.tsv");
        if (!file.is_open()) {
            throw std::runtime_error("Не удалось открыть файл ip_filter.tsv");
        }

        // Чтение IP-адресов из файла
        for (std::string line; std::getline(file, line);) {
            std::vector<std::string> v = split(line, '\t'); // Разделяем строку по табуляции
            ip_pool.push_back(split(v.at(0), '.')); // Разделяем IP-адрес на байты
        }

        file.close(); // Закрываем файл после чтения

        // Лексикографическая сортировка IP-адресов
        std::sort(ip_pool.begin(), ip_pool.end(), compareIPs);

        // Выводим отсортированные IP-адреса
        std::cout << "Список адресов после сортировки:\n";
        printIPAddresses(ip_pool);

        // Выводим IP-адреса с первым байтом, равным 1
        std::cout << "Вывод IP с 1:" << "\n";
        printIPsWithFirstByte(ip_pool, 1);

        // Выводим IP-адреса с первым байтом 46 и вторым 70
        std::cout << "Вывод IP с 46 и 70:" << "\n";
        printIPsWithFirstAndSecondByte(ip_pool, 46, 70);

        // Выводим IP-адреса, где любой байт равен 46
        std::cout << "Вывод IP с 46:" << "\n";    
        printIPsWithAnyByte(ip_pool, 46);

    } catch (const std::exception &e) {
        // Обрабатываем исключения и выводим сообщение об ошибке
        std::cerr << e.what() << std::endl;
    }

    return 0; // Завершение программы
}