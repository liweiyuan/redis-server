#include "storage.h"

Storage& Storage::getInstance() {
    static Storage instance;
    return instance;
}

void Storage::set(const std::string& key, const std::string& value) {
    std::lock_guard<std::mutex> lock(g_store_mutex);
    g_store[key] = value;
}

std::string Storage::get(const std::string& key) {
    std::lock_guard<std::mutex> lock(g_store_mutex);
    return g_store[key];
}

bool Storage::has(const std::string& key) {
    std::lock_guard<std::mutex> lock(g_store_mutex);
    return g_store.count(key);
}