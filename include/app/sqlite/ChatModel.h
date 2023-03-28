#ifndef APP_CHATMODEL_H
#define APP_CHATMODEL_H

#include "app/sqlite/Model.h"

#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include "sqlite3.h"

namespace app {

    /**
     * @brief Модель таблицы chats
     */
    class ChatModel : public Model {

    private:
        /**
         * @brief ID телеграм чата
         */
        int64_t chatId = 0;

        /**
         * @brief Название чата
         */
        std::string name;

        /**
         * @brief Username чата
         */
        std::string username;

        /**
         * @brief Активность в чате
         */
        int isActive = 0;

    public:
        /**
         * @brief Название таблицы для модели
         */
        inline static const std::string TABLE_NAME = "chats";

        /**
         * @brief Название полей
         */
        inline static const std::string
            FIELD_CHAT_ID = TABLE_NAME + ".chat_id",
            FIELD_NAME = TABLE_NAME + ".name",
            FIELD_USERNAME = TABLE_NAME + ".username",
            FIELD_IS_ACTIVE = TABLE_NAME + ".is_active";

        /**
         * @brief Конструктор по умолчанию. Полезен при простом создании модели
         */
        explicit ChatModel() : Model() { }

        /**
         * @brief Конструктор для настройки сериализации с БД. Полезен для SELECT запросов
         */
        explicit ChatModel(sqlite3_stmt* stmt, const std::vector<std::string>& select);

        /**
         * @brief Конструктор для заполнение полей. Полезен для INSERT запросов
         */
        explicit ChatModel(const int64_t& chatId, const std::string& name, const std::string& username,
                           const int& isActive);

        /**
         * @brief Деструктор по умолчанию
         */
        ~ChatModel() = default;

        /**
         * @brief Getter для переменной chatId
         * @return
         */
        int64_t& getChatId();

        /**
         * @brief Getter для переменной name
         * @return
         */
        std::string& getName();

        /**
         * @brief Getter для переменной username
         * @return
         */
        std::string& getUsername();

        /**
         * @brief Getter для переменной isActive
         * @return
         */
        int& getIsActive();

        /**
         * @return
         */
        std::string insertSql() override;

        /**
         * @return
         */
        void insertBind(sqlite3_stmt* stmt) override;

    };

}

#endif
