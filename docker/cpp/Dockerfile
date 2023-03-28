FROM ubuntu:22.04

ARG DEBIAN_FRONTEND=noninteractive

RUN apt update && apt install -y \
    build-essential \
    libgmp-dev \
    libmpfr-dev \
    libmpc-dev \
    bash \
    git \
    cron \
    flex \
    cmake \
    gcc-multilib \
    binutils \
    libboost-system-dev \
    libssl-dev \
    zlib1g-dev \
    libcurl4-openssl-dev \
    libsqlite3-dev \
    && rm -rf /var/lib/apt/lists/*

RUN git clone -b v1.6 https://github.com/reo7sp/tgbot-cpp && \
    cd tgbot-cpp && \
    cmake . && \
    make -j4 && \
    make install && \
    cd ../ && \
    rm -rf tgbot-cpp

COPY crontab /etc/cron.d/cron
RUN chmod 0644 /etc/cron.d/cron
RUN crontab /etc/cron.d/cron

ENV TZ=Asia/Almaty
RUN ln -snf /usr/share/zoneinfo/$TZ /etc/localtime && echo $TZ > /etc/timezone

ARG USER_ID
ARG GROUP_ID

RUN addgroup --gid $GROUP_ID user && \
    adduser --disabled-password --gecos '' --uid $USER_ID --gid $GROUP_ID user

WORKDIR /usr/src/app

ENTRYPOINT ["./docker/cpp/docker-entrypoint.sh"]