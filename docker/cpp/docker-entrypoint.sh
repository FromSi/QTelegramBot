#!/bin/bash

su -c "mkdir -p $(pwd)/cmake-docker && cmake -S $(pwd) -B $(pwd)/cmake-docker && cd $(pwd)/cmake-docker && make -j4 && cd ../" user

env | grep QTELEGRAM_TELEGRAM_BOT_TOKEN_API >> /etc/environment
env | grep QTELEGRAM_TELEGRAM_BOT_QUIZ_HEADER >> /etc/environment
env | grep QTELEGRAM_TELEGRAM_BOT_DISABLE_NOTIFICATION >> /etc/environment

cron -f
