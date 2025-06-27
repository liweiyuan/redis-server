#ifndef REDIS_SERVER_STORAGE_H
#define REDIS_SERVER_STORAGE_H

#include <string>
#include <map>
#include <mutex>

class Storage {
public:
    static Storage& getInstance();
    void set(const std::string& key, const std::string& value);
    std::string get(const std::string& key);
    bool has(const std::string& key);

private:
    Storage() = default;
    std::map<std::string, std::string> g_store;
    std::mutex g_store_mutex;
};

#endif //REDIS_SERVER_STORAGE_H