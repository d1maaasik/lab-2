cmake_minimum_required(VERSION 3.10)

project(IFilterProject VERSION 0.1.0)

# Установить политику для FindBoost
cmake_policy(SET CMP0167 NEW)

# Указать путь к Boost (если требуется)
set(BOOST_ROOT "D:/msys64/mingw64")

# Найти Boost
find_package(Boost REQUIRED COMPONENTS unit_test_framework)

# Создание библиотеки и исполняемого файла
add_library(ip_filter_lib ip_filter.cpp)  # Либ для тестов
add_executable(ip_filter ip_filter.cpp)   # Исполняемый файл

# Создание исполняемого файла для тестов
add_executable(test_ip_filter test_ip_filter.cpp)

# Установка стандартов C++
set_target_properties(ip_filter ip_filter_lib test_ip_filter PROPERTIES
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED ON
)

# Установка директорий для заголовочных файлов
target_include_directories(ip_filter_lib PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")
target_include_directories(test_ip_filter PRIVATE ${Boost_INCLUDE_DIRS})

# Связывание библиотек
target_link_libraries(test_ip_filter PRIVATE ${Boost_LIBRARIES} ip_filter_lib)

# Включение тестирования
enable_testing()
add_test(NAME test_ip_filter COMMAND test_ip_filter)

# Включение CPack для создания пакетов
include(CPack)

# Настройки для CPack
set(CPACK_PACKAGE_NAME "ip_filter")
set(CPACK_PACKAGE_VERSION "${PROJECT_VERSION}")
set(CPACK_PACKAGE_DESCRIPTION "A description of your package.")
set(CPACK_PACKAGE_LICENSE "MIT")
set(CPACK_GENERATOR "ZIP")  # Для Windows используем ZIP

# Установка файлов в пакет
install(TARGETS ip_filter DESTINATION bin)
install(TARGETS test_ip_filter DESTINATION bin)

# Сообщение о версии
message("Configured PROJECT_VERSION: ${PROJECT_VERSION}")