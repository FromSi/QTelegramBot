#ifndef APP_ENVIRONMENT_H
#define APP_ENVIRONMENT_H

#include <cstdlib>
#include <string>
#include <cstring>

namespace app {

    /**
     * @brief Работа с переменными окружения
     */
    class Environment {

    public:
        /**
         * @brief Ключ переменной для телеграм API-токен бота
         */
        inline static const std::string TELEGRAM_BOT_TOKEN_API = "QTELEGRAM_TELEGRAM_BOT_TOKEN_API";

        /**
         * @brief Ключ переменной для телеграм заголовка для вопроса
         */
        inline static const std::string TELEGRAM_BOT_QUIZ_HEADER = "QTELEGRAM_TELEGRAM_BOT_QUIZ_HEADER";

        /**
         * @brief Ключ переменной для отключения звуковых уведомлений
         */
        inline static const std::string TELEGRAM_BOT_DISABLE_NOTIFICATION = "QTELEGRAM_TELEGRAM_BOT_DISABLE_NOTIFICATION";

        /**
         * @brief Конструктор по умолчанию
         */
        explicit Environment() = default;

        /**
         * @brief Деструктор по умолчанию
         */
        ~Environment() = default;

        /**
         * @brief Получение телеграм API-токен бота
         * @return
         */
        static std::string getTelegramBotTokenApi();

        /**
         * @brief Проверка на существование значения телеграм API-токен бота
         * @return
         */
        static bool hasTelegramBotTokenApi();

        /**
         * @brief Получение телеграм заголовка для вопроса
         * @return
         */
        static std::string getTelegramBotQuizHeader();

        /**
         * @brief Проверка на существование значения телеграм заголовка для вопроса
         * @return
         */
        static bool hasTelegramBotQuizHeader();

        /**
         * @brief Получение команды на отключение телеграм уведомлений
         * @return
         */
        static bool hasTelegramBotDisableNotification();

        /**
         * @brief Получение пути до sqlite3 файла
         * @return
         */
        static std::string getSqliteFilePath();

        /**
         * @brief Проверка на существование значения пути до sqlite3 файла
         * @return
         */
        static bool hasSqliteFilePath();

    };

}

#endif
