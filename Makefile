# Default target
default_target: help

# [ALL] SQLite update database and migrations
.PHONY: all_sqlite_update
all_sqlite_update:
	docker pull keinos/sqlite3:3.40.1
	docker run --rm --user $$(id -u):$$(id -g) -v "$$(pwd):/workspace" -w /workspace keinos/sqlite3 sh -c "sqlite3 database.sqlite < ./sqlite_scripts/migrations.sql"

# [DEV] Configure for development
.PHONY: dev_config
dev_configure:
	mkdir -p $$(pwd)/cmake
	cmake -S $$(pwd) -B $$(pwd)/cmake

# [DEV] Init for development
.PHONY: dev_init
dev_init:
	-git clone -b v1.6 https://github.com/reo7sp/tgbot-cpp
	cd tgbot-cpp && cmake . && make -j4 && sudo make install
	-sudo rm -rf tgbot-cpp
	$(MAKE) all_sqlite_update
	$(MAKE) dev_configure
	ln -s database.sqlite ./cmake/database.sqlite

# [DEV] Build for development
.PHONY: dev_build
dev_build:
	$(MAKE) all_sqlite_update
	$(MAKE) dev_configure
	cd $$(pwd)/cmake && make -j4

# [DOCKER] Install docker
.PHONY: docker_install
docker_install:
	cp ./docker/example.docker-compose.override.yml ./docker/docker-compose.override.yml
	cp ./docker/cpp/example.crontab ./docker/cpp/crontab
	chmod +x ./docker/cpp/docker-entrypoint.sh

# [DOCKER] Run docker
.PHONY: docker_run
docker_run:
	$(MAKE) all_sqlite_update
	docker compose -f ./docker/docker-compose.yml -f ./docker/docker-compose.override.yml up --build -d

# [DOCKER] Stop docker
.PHONY: docker_stop
docker_stop:
	docker compose -f ./docker/docker-compose.yml -f ./docker/docker-compose.override.yml stop

# [DOCKER] Login to cpp container
.PHONY: docker_cpp
docker_cpp:
	docker compose -f ./docker/docker-compose.yml -f ./docker/docker-compose.override.yml exec cpp bash -l

# Help
.PHONY: help
help:
	@echo "Makefile Targets:"
	@echo "... all_sqlite_update ([ALL] SQLite update database and migrations)"
	@echo "... dev_configure ([DEV] Configure for development)"
	@echo "... dev_init ([DEV] Init for development)"
	@echo "... dev_build ([DEV] Build for development)"
	@echo "... docker_install ([DOCKER] Install docker)"
	@echo "... docker_run ([DOCKER] Run docker)"
	@echo "... docker_stop ([DOCKER] Stop docker"
	@echo "... docker_cpp ([DOCKER] Login to cpp container)"
