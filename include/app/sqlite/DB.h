#ifndef APP_DB_H
#define APP_DB_H

#include "sqlite3.h"
#include <string>

namespace app {

    /**
     * @brief Работа с БД
     */
    class DB {
    private:
        /**
         * @brief Количество подключенных классов
         */
        static int connectCount;

    protected:
        /**
         * @brief Точка обращения к БД
         */
        static sqlite3* db;

        /**
         * @brief Статус соединения к БД
         */
        static bool isConnection;

    public:
        /**
         * @brief Конструктор подключающее соединение
         */
        explicit DB(const std::string& dbName);

        /**
         * @brief Деструктор отключающий соединение
         */
        ~DB();

    };

}

#endif
