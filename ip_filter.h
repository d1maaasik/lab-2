#ifndef IP_FILTER_H
#define IP_FILTER_H

#include <vector>
#include <string>

// Объявление функции разделения строки на части
std::vector<std::string> split(const std::string& str, char d);

// Функция для вывода IP-адресов на экран
void printIPAddresses(const std::vector<std::vector<std::string>>& ip_pool);

// Функция для вывода IP-адресов с первым байтом равным заданному значению
void printIPsWithFirstByte(const std::vector<std::vector<std::string>>& ip_pool, int first_byte);

// Функция для вывода IP-адресов с первым и вторым байтом равными заданным значениям
void printIPsWithFirstAndSecondByte(const std::vector<std::vector<std::string>>& ip_pool, int first_byte, int second_byte);

// Функция для вывода IP-адресов, у которых хотя бы один байт равен заданному значению
void printIPsWithAnyByte(const std::vector<std::vector<std::string>>& ip_pool, int byte_value);

#endif // IP_FILTER_H
