# Телеграм бот QTelegramBot
Его задача отправлять по времени CRON викторины (quiz) в зарегистрированные группы.

<p align="center">
  <img src="https://github.com/FromSi/QTelegramBot/blob/master/screenshots/s1.jpg" height="400"/>
</p>

Демо версия работы телеграм бота. Был сделан бот переводчик на основе шаблона [QTranslateBot](https://t.me/quiz_translate_bot). Его работу можно увидеть в группе [Illuminati Inc.](https://t.me/illuminatinc)

## Возможности проекта
* Токен бота можно установить через переменную `QTELEGRAM_TELEGRAM_BOT_TOKEN_API`
* Заголовочный текст перед вопросом также можно установить через переменную `QTELEGRAM_TELEGRAM_BOT_QUIZ_HEADER`
* Звук сообщений можно отключить (по умолчанию `false`) через переменную `QTELEGRAM_TELEGRAM_BOT_DISABLE_NOTIFICATION`
* Регистрация только supergroup чатов (в других чатах работать не будет)
* Обработка ограничений на отправку (ведет статус активности на отправку quiz)
* Отправка polls в виде quiz. Один вопрос и четыре варианта ответа (один правильный)
* В вопрос также можно добавить подсказку
* Если quizzes закончились, то чат будет просто проигнорирован до следующего нового вопроса в БД
* Все действия происходят через CRON расписание
* Используется база данных `SQLite3`
* Для запуска на сервере достаточно иметь `docker`, `git` и `make`

## Установка
* Нужен docker без использования sudo

Выполнить команду:
```
# Ubuntu
sudo apt update && sudo apt install git make
```

### (Дополнительно) Для нативной разработки
Выполнить команды в корне проекта:
```
# Ubuntu
sudo apt update 
sudo apt install g++ binutils cmake libboost-system-dev libssl-dev zlib1g-dev libcurl4-openssl-dev libsqlite3-dev
make dev_init && make dev_build
```

Добавить переменную окружения (допустим в `~/.bashrc`).
```
# API-токен бота
export QTELEGRAM_TELEGRAM_BOT_TOKEN_API="token"
# Заголовок для вопроса quiz (можно оставить пустым)
export QTELEGRAM_TELEGRAM_BOT_QUIZ_HEADER="Header:"
# Отключение звуковых уведомлений
export QTELEGRAM_TELEGRAM_BOT_DISABLE_NOTIFICATION="true"
```

Для работы на CLion нужно настроить:
```
File | Settings | Build, Execution, Deployment | CMake
```

И в `Build directory` поставьте на директорию `cmake`.


### (Дополнительно) Для Docker запуска
* Запуск через docker подходит для сервера.

1. Запустить команду `make docker_install`
1. Редактировать необходимые данные в файле `./docker/docker-compose.override.yml`
1. Редактировать CRON время в файле `./docker/cpp/crontab`
1. Запустить команду `make docker_run`

Чтобы остановить docker, нужно выполнить `make docker_stop`
