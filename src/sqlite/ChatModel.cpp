#include "app/sqlite/ChatModel.h"

namespace app {

    ChatModel::ChatModel(sqlite3_stmt* stmt, const std::vector<std::string>& select) : Model() {
        int columnIndex = 0;

        chatId = getValueFromSelect<int64_t>(select, stmt, columnIndex, ChatModel::FIELD_CHAT_ID, 0);
        name = getValueFromSelect<std::string>(select, stmt, columnIndex, ChatModel::FIELD_NAME, "");
        username = getValueFromSelect<std::string>(select, stmt, columnIndex, ChatModel::FIELD_USERNAME, "");
        isActive = getValueFromSelect<int>(select, stmt, columnIndex, ChatModel::FIELD_IS_ACTIVE, 0);
    }

    ChatModel::ChatModel(const int64_t& chatId, const std::string& name, const std::string& username,
                         const int& isActive) {
        this->chatId = chatId;
        this->name = name;
        this->username = username;
        this->isActive = isActive;
    }

    int64_t& ChatModel::getChatId() {
        return chatId;
    }

    std::string& ChatModel::getName() {
        return name;
    }

    std::string& ChatModel::getUsername() {
        return username;
    }

    int& ChatModel::getIsActive() {
        return isActive;
    }

    std::string ChatModel::insertSql() {
        std::stringstream sql;

        sql << "INSERT OR REPLACE INTO " << TABLE_NAME
           << "(chat_id,name,username,is_active) "
           << "VALUES (?,?,?,?);";

        return sql.str();
    }

    void ChatModel::insertBind(sqlite3_stmt* stmt) {
        sqlite3_bind_int64(stmt, 1, chatId);
        sqlite3_bind_text(stmt, 2, name.c_str(), static_cast<int>(name.size()), SQLITE_STATIC);
        sqlite3_bind_text(stmt, 3, username.c_str(), static_cast<int>(username.size()), SQLITE_STATIC);
        sqlite3_bind_int(stmt, 4, isActive);
    }

}
