#include "app/sqlite/QuizAndChatModel.h"

namespace app {

    QuizAndChatModel::QuizAndChatModel(sqlite3_stmt* stmt, const std::vector<std::string>& select) : Model() {
        int columnIndex = 0;

        quizId = getValueFromSelect<int>(select, stmt, columnIndex, QuizAndChatModel::FIELD_QUIZ_ID, 0);
        chatId = getValueFromSelect<int64_t>(select, stmt, columnIndex, QuizAndChatModel::FIELD_CHAT_ID, 0);
    }

    QuizAndChatModel::QuizAndChatModel(const int& quizId, const int64_t& chatId) {
        this->quizId = quizId;
        this->chatId = chatId;
    }

    int& QuizAndChatModel::getQuizId() {
        return quizId;
    };

    int64_t& QuizAndChatModel::getChatId() {
        return chatId;
    }

    std::string QuizAndChatModel::insertSql() {
        std::stringstream sql;

        sql << "INSERT OR REPLACE INTO " << TABLE_NAME
           << "(quiz_id,chat_id) "
           << "VALUES (?,?);";

        return sql.str();
    }

    void QuizAndChatModel::insertBind(sqlite3_stmt* stmt) {
        sqlite3_bind_int(stmt, 1, quizId);
        sqlite3_bind_int64(stmt, 2, chatId);
    }

}
