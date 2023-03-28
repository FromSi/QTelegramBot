#ifndef APP_QUIZMODEL_H
#define APP_QUIZMODEL_H

#include "app/sqlite/Model.h"

#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include "sqlite3.h"

namespace app {

    /**
     * @brief Модель таблицы quizzes
     */
    class QuizModel : public Model {

    private:
        /**
         * @brief
         */
        int id = 0;

        /**
         * @brief Подсказка
         */
        std::string explanation;

        /**
         * @brief Вопрос
         */
        std::string question;

        /**
         * @brief Правильный ответ
         */
        std::string answerTrue;

        /**
         * @brief Один из неправильных ответов
         */
        std::string answerFalseOne;

        /**
         * @brief Один из неправильных ответов
         */
        std::string answerFalseTwo;

        /**
         * @brief Один из неправильных ответов
         */
        std::string answerFalseThree;

    public:
        /**
         * @brief Название таблицы для модели
         */
        inline static const std::string TABLE_NAME = "quizzes";

        /**
         * @brief Название полей
         */
        inline static const std::string
            FIELD_ID = TABLE_NAME + ".id",
            FIELD_EXPLANATION = TABLE_NAME + ".explanation",
            FIELD_QUESTION = TABLE_NAME + ".question",
            FIELD_ANSWER_TRUE = TABLE_NAME + ".answer_true",
            FIELD_ANSWER_FALSE_ONE = TABLE_NAME + ".answer_false_one",
            FIELD_ANSWER_FALSE_TWO = TABLE_NAME + ".answer_false_two",
            FIELD_ANSWER_FALSE_THREE = TABLE_NAME + ".answer_false_three";

        /**
         * @brief Конструктор по умолчанию. Полезен при простом создании модели
         */
        explicit QuizModel() : Model() { }

        /**
         * @brief Конструктор для настройки сериализации с БД. Полезен для SELECT запросов
         */
        explicit QuizModel(sqlite3_stmt* stmt, const std::vector<std::string>& select);

        /**
         * @brief Конструктор для заполнение полей. Полезен для INSERT запросов
         */
        explicit QuizModel(const int& id, const std::string& explanation, const std::string& question, const std::string& answerTrue,
                           const std::string& answerFalseOne, const std::string& answerFalseTwo, const std::string& answerFalseThree);

        /**
         * @brief Деструктор по умолчанию
         */
        ~QuizModel() = default;

        /**
         * @brief Getter для переменной id
         * @return
         */
        int& getId();

        /**
         * @brief Getter для переменной explanation
         * @return
         */
        std::string& getExplanation();

        /**
         * @brief Getter для переменной question
         * @return
         */
        std::string& getQuestion();

        /**
         * @brief Getter для переменной answerTrue
         * @return
         */
        std::string& getAnswerTrue();

        /**
         * @brief Getter для переменной answerFalseOne
         * @return
         */
        std::string& getAnswerFalseOne();

        /**
         * @brief Getter для переменной answerFalseTwo
         * @return
         */
        std::string& getAnswerFalseTwo();

        /**
         * @brief Getter для переменной answerFalseThree
         * @return
         */
        std::string& getAnswerFalseThree();

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
