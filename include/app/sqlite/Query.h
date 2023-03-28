#ifndef APP_QUERY_H
#define APP_QUERY_H

#include "app/sqlite/DB.h"

#include "sqlite3.h"
#include <vector>
#include <string>
#include <sstream>
#include <iostream>

namespace app {

    /**
     * @brief Главный контроллер для запросов между пользователей, моделью и БД
     * @tparam T
     */
    template<class T>
    class Query : public DB{

    protected:
        /**
         * @brief Сделать запрос на SELECT
         * @param sql
         * @param data
         * @return
         */
        bool selectExec(const std::vector<std::string>& select, const std::string& sql, std::vector<T>& data);

        /**
         * @brief Сделать запрос на DELETE
         * @param sql
         * @return
         */
        bool removeExec(const std::string& sql);

    public:
        /**
         * @brief Конструктор по умолчанию
         * @param dbName
         */
        explicit Query(const char* dbName = "database.sqlite") : DB(dbName) { }

        /**
         * @brief Деструктор по умолчанию
         */
        ~Query() = default;

         /**
           * @brief Составление запроса на получение списка данных
\          * @return
          */
        std::vector<T> selectAll();

         /**
          * @brief Составление запроса на получение списка данных
          * @param where
          * @return
          */
        std::vector<T> selectAll(const std::string& where);

         /**
          * @brief Составление запроса на получение списка данных
          * @param select
          * @param where
          * @param leftJoinForWhere Нужно явно указывать LEFT JOIN
          * @param orderBy
          * @param limit
          * @return
          */
        std::vector<T> selectAll(const std::vector<std::string>& select, const std::string& where, const std::string& leftJoinForWhere,
                                 const std::string& orderBy, const int& limit);

         /**
          * @brief Составление запроса на получение первой строчки данных
          * @return
          */
        T selectFirst();

         /**
          * @brief Составление запроса на получение первой строчки данных
          * @param where
          * @return
          */
        T selectFirst(const std::string& where);

         /**
          * @brief Составление запроса на получение первой строчки данных
          * @param select
          * @param where
          * @param leftJoinForWhere Нужно явно указывать LEFT JOIN
          * @param orderBy
          * @return
          */
        T selectFirst(const std::vector<std::string>& select, const std::string& where, const std::string& leftJoinForWhere,
                      const std::string& orderBy);

        /**
         * @brief Составление запроса на создание данных
         * @param model
         * @return
         */
        bool insert(T& model);

        /**
         * @brief Составление запроса на удаление данных через одно поле
         * @param columnName
         * @param columnValue
         * @return
         */
        bool remove(const char* columnName, const int& columnValue);

        /**
         * @brief Составление запроса на удаление данных через два поля с оператором AND
         * @param columnOneName
         * @param columnOneValue
         * @param columnTwoName
         * @param columnTwoValue
         * @return
         */
        bool remove(const char* columnOneName, const int& columnOneValue, const char* columnTwoName, const int& columnTwoValue);

    };

    template<class T>
    bool Query<T>::selectExec(const std::vector<std::string>& select, const std::string& sql, std::vector<T>& data) {
        sqlite3_stmt *stmt;

        if (!this->isConnection) {
            return false;
        }

        int responseCode = sqlite3_prepare_v2(this->db, sql.c_str(), -1, &stmt, nullptr);

        if (responseCode != SQLITE_OK) {
            sqlite3_finalize(stmt);

            return false;
        }

        while ((responseCode = sqlite3_step(stmt)) == SQLITE_ROW) {
            data.push_back(T(stmt, select));
        }

        sqlite3_finalize(stmt);

        if (responseCode != SQLITE_DONE) {
            return false;
        }

        return true;
    }

    template<class T>
    bool Query<T>::removeExec(const std::string& sql) {
        sqlite3_stmt *stmt;

        if (!this->isConnection) {
            return false;
        }

        int responseCode = sqlite3_prepare_v2(this->db, sql.c_str(), -1, &stmt, nullptr);

        if (responseCode != SQLITE_OK) {
            sqlite3_finalize(stmt);

            return false;
        }

        responseCode = sqlite3_step(stmt);

        sqlite3_finalize(stmt);

        return responseCode == SQLITE_DONE;
    }

    template<class T>
    std::vector<T> Query<T>::selectAll() {
        return selectAll("");
    }

    template<class T>
    std::vector<T> Query<T>::selectAll(const std::string& where) {
        return selectAll({}, where, "", "", 0);
    }

    template<class T>
    std::vector<T> Query<T>::selectAll(const std::vector<std::string>& select, const std::string& where, const std::string& leftJoinForWhere,
                                       const std::string& orderBy, const int& limit) {
        std::stringstream sql;
        std::vector<T> data;

        sql << "SELECT ";

        if (select.empty()) {
            sql << T::TABLE_NAME << ".* ";
        } else {
            for (size_t i = 0; i < select.size(); i++) {
                sql << select[i];

                if (i != select.size() - 1) {
                    sql << ",";
                }
            }

            sql << " ";
        }

        sql << "FROM " << T::TABLE_NAME << " ";

        if (!leftJoinForWhere.empty()) {
            sql << leftJoinForWhere << " ";
        }

        if (!where.empty()) {
            sql << "WHERE " << where << " ";
        }

        if (!orderBy.empty()) {
            sql << "ORDER BY " << orderBy << " ";
        }

        if (limit > 0) {
            sql << "LIMIT " << limit << " ";
        }

        sql << ";";

        selectExec(select, sql.str(), data);

        return data;
    }

    template<class T>
    T Query<T>::selectFirst() {
        return selectFirst("");
    }

    template<class T>
    T Query<T>::selectFirst(const std::string& where) {
        return selectFirst({}, where, "", "");
    }

    template<class T>
    T Query<T>::selectFirst(const std::vector<std::string>& select, const std::string& where, const std::string& leftJoinForWhere,
                            const std::string& orderBy) {
        std::vector<T> data = selectAll(select, where, leftJoinForWhere, orderBy, 1);

        return data.empty() ? T() : data[0];
    }

    template<class T>
    bool Query<T>::remove(const char* columnName, const int& columnValue) {
        std::string sql("DELETE FROM " + T::TABLE_NAME + " WHERE " + columnName + "=" + std::to_string(columnValue) + ";");

        return removeExec(sql);
    }

    template<class T>
    bool Query<T>::remove(const char* columnOneName, const int& columnOneValue, const char* columnTwoName, const int& columnTwoValue) {
        std::string sql("DELETE FROM " + T::TABLE_NAME + " WHERE " + columnOneName + "=" + std::to_string(columnOneValue) + " AND "
            + columnTwoName + "=" + std::to_string(columnTwoValue) + ";");

        return removeExec(sql);
    }

    template<class T>
    bool Query<T>::insert(T& model) {
        sqlite3_stmt *stmt;

        std::string sql = model.insertSql();

        int responseCode = sqlite3_prepare_v2(this->db, sql.c_str(), -1, &stmt, nullptr);

        if (responseCode != SQLITE_OK) {
            sqlite3_finalize(stmt);

            return false;
        }

        model.insertBind(stmt);

        responseCode = sqlite3_step(stmt);

        sqlite3_finalize(stmt);

        return responseCode == SQLITE_DONE;
    }

}

#endif
