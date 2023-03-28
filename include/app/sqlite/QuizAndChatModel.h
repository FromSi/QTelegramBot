#ifndef APP_QUIZANDCHATMODEL_H
#define APP_QUIZANDCHATMODEL_H

#include "app/sqlite/Model.h"

#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include "sqlite3.h"

namespace app {

    /**
     * @brief Модель таблицы quizzes_and_chats
     */
    class QuizAndChatModel : public Model {

    private:
        /**
         * @brief ID викторины
         */
        int quizId = 0;

        /**
         * @brief ID телеграм чата
         */
        int64_t chatId = 0;

    public:
        /**
         * @brief Название таблицы для модели
         */
        inline static const std::string TABLE_NAME = "quizzes_and_chats";

        /**
         * @brief Название полей
         */
        inline static const std::string
            FIELD_QUIZ_ID = TABLE_NAME + ".quiz_id",
            FIELD_CHAT_ID = TABLE_NAME + ".chat_id";

        /**
         * @brief Конструктор по умолчанию. Полезен при простом создании модели
         */
        explicit QuizAndChatModel() : Model() { }

        /**
         * @brief Конструктор для настройки сериализации с БД. Полезен для SELECT запросов
         */
        explicit QuizAndChatModel(sqlite3_stmt* stmt, const std::vector<std::string>& select);

        /**
         * @brief Конструктор для заполнение полей. Полезен для INSERT запросов
         */
        explicit QuizAndChatModel(const int& quizId, const int64_t& chatId);

        /**
         * @brief Деструктор по умолчанию
         */
        ~QuizAndChatModel() = default;

        /**
         * @brief Getter для переменной quizId
         * @return
         */
        int& getQuizId();

        /**
         * @brief Getter для переменной chatId
         * @return
         */
        int64_t& getChatId();

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
