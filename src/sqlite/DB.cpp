#include "app/sqlite/DB.h"

namespace app {

    int DB::connectCount = 0;

    sqlite3* DB::db{};

    bool DB::isConnection = false;

    DB::DB(const std::string& dbName) {
        if (connectCount == 0) {
            int responseCode = sqlite3_open(dbName.c_str(), &db);

            if (responseCode) {
                sqlite3_close(db);
            }
        }

        connectCount++;

        isConnection = db != nullptr;
    }

    DB::~DB() {
        if (db != nullptr) {
            connectCount--;
        } else {
            connectCount = 0;
        }

        if (connectCount == 0) {
            sqlite3_close(db);

            isConnection = false;
        }
    }

}
