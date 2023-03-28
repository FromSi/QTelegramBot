#include <iostream>
#include <random>
#include <string>
#include <cstring>
#include <vector>
#include <map>
#include <tuple>
#include "tgbot/tgbot.h"
#include "app/app.h"

void handlerChatsArgument();
void handlerSendQuizzesArgument();
std::string getHelp();

/**
 * @brief Основная точка входа
 * @param argc Количество аргументов
 * @param argv Аргументы для работы с программой
 * @return
 */
int main(int argc, char *argv[]) {
    if (argc < 2) {
        std::cout << "Error: No arguments" << std::endl;
        std::cout << getHelp() << std::endl;

        return EXIT_FAILURE;
    }

    char *firstArgument = argv[1];

    if (std::strcmp(firstArgument, "-c") == 0 || std::strcmp(firstArgument, "--chats") == 0) {
        handlerChatsArgument();
    } else if (std::strcmp(firstArgument, "-sq") == 0 || std::strcmp(firstArgument, "--send_quizzes") == 0) {
        handlerSendQuizzesArgument();
    } else if (std::strcmp(firstArgument, "-h") == 0 || std::strcmp(firstArgument, "--help") == 0) {
        std::cout << getHelp() << std::endl;
    } else {
        std::cout << "Error: " << argv[1] << " argument not supported" << std::endl;
        std::cout << getHelp() << std::endl;

        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

/**
 * Обработчик аргумента: -c --chats
 */
void handlerChatsArgument() {
    if (!app::Environment::hasTelegramBotTokenApi() || !app::Environment::hasSqliteFilePath()) {
        std::cout << "Error: empty ENVs" << std::endl;

        return;
    }

    TgBot::Bot tgBot(app::Environment::getTelegramBotTokenApi());

    try {
        int64_t tgBotId = tgBot.getApi().getMe()->id;
        std::int32_t tgBotLastUpdateId = 0;
        std::map<int64_t, std::tuple<int32_t, app::ChatModel>> chats;

        do {
            auto tgBotUpdates = tgBot.getApi().getUpdates(tgBotLastUpdateId);

            for (TgBot::Update::Ptr& tgBotUpdate : tgBotUpdates) {
                if (tgBotUpdate->updateId >= tgBotLastUpdateId) {
                    tgBotLastUpdateId = tgBotUpdate->updateId + 1;
                }

                if (tgBotUpdate->myChatMember == nullptr) {
                    continue;
                }

                if (tgBotUpdate->myChatMember->newChatMember->user->id != tgBotId) {
                    continue;
                }

                if (tgBotUpdate->myChatMember->chat->type != TgBot::Chat::Type::Supergroup) {
                    continue;
                }

                int64_t chatId = tgBotUpdate->myChatMember->chat->id;
                const auto& chatModel = chats.find(chatId);

                std::string chatName = (!tgBotUpdate->myChatMember->chat->title.empty())
                                       ? tgBotUpdate->myChatMember->chat->title : "empty";

                std::string chatUsername = (!tgBotUpdate->myChatMember->chat->username.empty())
                                           ? tgBotUpdate->myChatMember->chat->username : "empty";

                bool isActive = tgBotUpdate->myChatMember->newChatMember->status != TgBot::ChatMemberLeft::STATUS;
                isActive = isActive && tgBotUpdate->myChatMember->newChatMember->status != TgBot::ChatMemberBanned::STATUS;

                if (tgBotUpdate->myChatMember->newChatMember->status == TgBot::ChatMemberRestricted::STATUS) {
                    isActive = isActive
                            && dynamic_cast<TgBot::ChatMemberRestricted*>(tgBotUpdate->myChatMember->newChatMember.get())->canSendPolls;
                }

                if (chatModel != chats.end()) {
                    if (tgBotUpdate->updateId > std::get<0>(chatModel->second)) {
                        std::get<0>(chatModel->second) = tgBotUpdate->updateId;
                        std::get<1>(chatModel->second).getName() = chatName;
                        std::get<1>(chatModel->second).getUsername() = chatUsername;
                        std::get<1>(chatModel->second).getIsActive() = isActive;
                    }
                } else {
                    chats.insert({chatId, {tgBotUpdate->updateId, app::ChatModel(chatId, chatName, chatUsername, isActive)}});
                }
            }

            if (tgBotUpdates.empty()) {
                tgBotLastUpdateId = 0;
            }
        } while (tgBotLastUpdateId != 0);

        app::Query<app::ChatModel> queryChatModel;

        for (const auto& chat : chats) {
            app::ChatModel chatModel = std::get<1>(chat.second);
            queryChatModel.insert(chatModel);
        }
    } catch (TgBot::TgException& exception) {
        std::cout << "ErrorTG: " << exception.what();

        return;
    }
}

/**
 * Обработчик аргумента: -sq --send_quizzes
 */
void handlerSendQuizzesArgument() {
    if (!app::Environment::hasTelegramBotTokenApi() || !app::Environment::hasSqliteFilePath()) {
        std::cout << "Error: empty ENVs" << std::endl;

        return;
    }

    TgBot::Bot tgBot(app::Environment::getTelegramBotTokenApi());

    app::Query<app::ChatModel> queryChatModel;
    app::Query<app::QuizModel> queryQuizModel;

    std::vector<app::ChatModel> chatModels = queryChatModel.selectAll(app::ChatModel::FIELD_IS_ACTIVE + "=1");

    std::map<int64_t, app::QuizModel> quizzes;

    for (app::ChatModel chatModelItem : chatModels) {
        std::vector<std::string> select{};
        std::string where = app::QuizAndChatModel::FIELD_CHAT_ID + " is not " + std::to_string(chatModelItem.getChatId());
        std::string leftJoinForWhere("LEFT JOIN " + app::QuizAndChatModel::TABLE_NAME + " ON " + app::QuizAndChatModel::FIELD_QUIZ_ID + "=" + app::QuizModel::FIELD_ID);
        std::string orderBy("RANDOM()");

        app::QuizModel quizModel = queryQuizModel.selectFirst(select, where, leftJoinForWhere, orderBy);

        if (quizModel.getId() > 0) {
            quizzes.insert({chatModelItem.getChatId(), quizModel});
        }
    }

    app::Query<app::QuizAndChatModel> queryQuizAndChatModel;

    for (const auto& quiz : quizzes) {
        try {
            app::QuizModel quizModel = quiz.second;
            std::vector<std::string> options{
                quizModel.getAnswerTrue(),
                quizModel.getAnswerFalseOne(),
                quizModel.getAnswerFalseTwo(),
                quizModel.getAnswerFalseThree(),
            };

            std::shuffle(options.begin(), options.end(), std::mt19937(std::random_device()()));

            int answerTrueIndex = static_cast<int>(
                std::distance(options.begin(), std::find(options.begin(), options.end(), quizModel.getAnswerTrue()))
            );

            std::string question = (app::Environment::hasTelegramBotQuizHeader())
                    ? app::Environment::getTelegramBotQuizHeader() + "\n" + quizModel.getQuestion()
                    : quizModel.getQuestion();

            std::cout << app::Environment::hasTelegramBotDisableNotification();

            tgBot.getApi().sendPoll(
                quiz.first,
                question,
                options,
                app::Environment::hasTelegramBotDisableNotification(),
                0,
                nullptr,
                true,
                "quiz",
                false,
                answerTrueIndex,
                quizModel.getExplanation()
            );

            app::QuizAndChatModel quizAndChatModel(quizModel.getId(), quiz.first);

            queryQuizAndChatModel.insert(quizAndChatModel);
        } catch (TgBot::TgException& exception) {
            std::cout << "ErrorTG: " << quiz.first << " " << exception.what();
        }
    }
}

/**
 * Справочная информация по проекту
 *
 * @return
 */
std::string getHelp() {
    return std::string("Support arguments:\n")
        + "\t-c --chats - Handler chats\n"
        + "\t-sq --send_quizzes - Send quiz messages in chats\n"
        + "\t-h --help - Information on the project";
}
