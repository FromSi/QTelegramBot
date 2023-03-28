#ifndef APP_MODEL_H
#define APP_MODEL_H

#include <string>
#include <vector>
#include "sqlite3.h"

namespace app {

    /**
     * @brief Абстракция для описания моделей. Модели "сериализуют" таблицы
     */
    class Model {

    public:
        /**
         * @brief Конструктор по умолчанию
         */
        explicit Model() = default;

        /**
         * @brief Деструктор по умолчанию
         */
        ~Model() = default;

        /**
         * @brief Получение SQL запроса на создание строки в БД
         */
        virtual std::string insertSql() = 0;

        /**
         * @brief Присоединение к SQL запроса на создание переменных в безопасном режиме
         */
        virtual void insertBind(sqlite3_stmt* stmt) = 0;

        /**
         * @brief Получение значений из SELECT
         * @tparam T
         * @param select
         * @param stmt
         * @param columnIndex
         * @param fieldName
         * @param defaultValue
         * @return
         */
        template <typename T>
        T getValueFromSelect(const std::vector<std::string>& select, sqlite3_stmt* stmt, int& columnIndex,
                             const std::string& fieldName, const T& defaultValue);

    };

    template<typename T>
    T Model::getValueFromSelect(const std::vector<std::string>& select, sqlite3_stmt* stmt, int& columnIndex,
                                       const std::string& fieldName, const T& defaultValue) {
        auto searchField = std::find(select.begin(), select.end(), fieldName);

        if (searchField == select.end() && !select.empty()) {
            return defaultValue;
        }

        if constexpr (std::is_same_v<T, std::string>) {
            const char* result = reinterpret_cast<const char*>(sqlite3_column_text(stmt, columnIndex++));

            return (result != nullptr) ? std::string(reinterpret_cast<const char*>(result)) : defaultValue;
        }

        if constexpr (std::is_same_v<T, int>) {
            return sqlite3_column_int(stmt, columnIndex++);
        }

        if constexpr (std::is_same_v<T, int64_t>) {
            return sqlite3_column_int64(stmt, columnIndex++);
        }

        return defaultValue;
    }

}

#endif
