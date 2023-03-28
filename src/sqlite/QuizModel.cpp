#include "app/sqlite/QuizModel.h"

namespace app {

    QuizModel::QuizModel(sqlite3_stmt* stmt, const std::vector<std::string>& select) : Model() {
        int columnIndex = 0;

        id = getValueFromSelect<int>(select, stmt, columnIndex, QuizModel::FIELD_ID, 0);
        explanation = getValueFromSelect<std::string>(select, stmt, columnIndex, QuizModel::FIELD_EXPLANATION, "");
        question = getValueFromSelect<std::string>(select, stmt, columnIndex, QuizModel::FIELD_QUESTION, "");
        answerTrue = getValueFromSelect<std::string>(select, stmt, columnIndex, QuizModel::FIELD_ANSWER_TRUE, "");
        answerFalseOne = getValueFromSelect<std::string>(select, stmt, columnIndex, QuizModel::FIELD_ANSWER_FALSE_ONE, "");
        answerFalseTwo = getValueFromSelect<std::string>(select, stmt, columnIndex, QuizModel::FIELD_ANSWER_FALSE_TWO, "");
        answerFalseThree = getValueFromSelect<std::string>(select, stmt, columnIndex, QuizModel::FIELD_ANSWER_FALSE_THREE, "");
    }

    QuizModel::QuizModel(const int& id, const std::string& explanation, const std::string& question, const std::string& answerTrue,
                         const std::string& answerFalseOne, const std::string& answerFalseTwo, const std::string& answerFalseThree) {
        this->id = id;
        this->explanation = explanation;
        this->question = question;
        this->answerTrue = answerTrue;
        this->answerFalseOne = answerFalseOne;
        this->answerFalseTwo = answerFalseTwo;
        this->answerFalseThree = answerFalseThree;
    }

    int& QuizModel::getId() {
        return id;
    }

    std::string& QuizModel::getExplanation() {
        return explanation;
    }

    std::string& QuizModel::getQuestion() {
        return question;
    }

    std::string& QuizModel::getAnswerTrue() {
        return answerTrue;
    }

    std::string& QuizModel::getAnswerFalseOne() {
        return answerFalseOne;
    }

    std::string& QuizModel::getAnswerFalseTwo() {
        return answerFalseTwo;
    }

    std::string& QuizModel::getAnswerFalseThree() {
        return answerFalseThree;
    }

    std::string QuizModel::insertSql() {
        std::stringstream sql;

        sql << "INSERT OR REPLACE INTO " << TABLE_NAME
           << "(id,explanation,question,answer_true,answer_false_one,answer_false_two,answer_false_three) "
           << "VALUES (?,?,?,?,?,?,?);";

        return sql.str();
    }

    void QuizModel::insertBind(sqlite3_stmt* stmt) {
        sqlite3_bind_int(stmt, 1, id);
        sqlite3_bind_text(stmt, 2, explanation.c_str(), static_cast<int>(explanation.size()), SQLITE_STATIC);
        sqlite3_bind_text(stmt, 3, question.c_str(), static_cast<int>(question.size()), SQLITE_STATIC);
        sqlite3_bind_text(stmt, 4, answerTrue.c_str(), static_cast<int>(answerTrue.size()), SQLITE_STATIC);
        sqlite3_bind_text(stmt, 5, answerFalseOne.c_str(), static_cast<int>(answerFalseOne.size()), SQLITE_STATIC);
        sqlite3_bind_text(stmt, 6, answerFalseTwo.c_str(), static_cast<int>(answerFalseTwo.size()), SQLITE_STATIC);
        sqlite3_bind_text(stmt, 7, answerFalseThree.c_str(), static_cast<int>(answerFalseThree.size()), SQLITE_STATIC);
    }

}
