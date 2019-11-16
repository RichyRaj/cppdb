//
// Copyright (c) Richard Raj. All rights reserved.
// Licensed under the MIT license. See LICENSE file for details.
//

#include "cppdb/db.h"

cppdb::Status cppdb::DB::open(const std::string& name) {
    cppdb::Status s;
    if (isOpen) {
        s = h.close();
        if (s.isError()) {
            return cppdb::Status::Error();
        }
    }
    isOpen = true;
    s = h.open(name);
    return s;
}

cppdb::Status cppdb::DB::close() {
    return h.close();
}

cppdb::Status cppdb::DB::put(const std::string& key, const std::string& value) {
    std::lock_guard<std::shared_timed_mutex> lg(m);
    if (key.length()) {
        return h.put(key, value);
    }
    return cppdb::Status::Error();
}

cppdb::Status cppdb::DB::update(const std::string& key,
const std::string& value) {
    std::lock_guard<std::shared_timed_mutex> lg(m); 
    if (h.find(key)) {
        return h.put(key, value);
    }
    throw std::string("ERROR: Key Not Found");
}

std::string cppdb::DB::get(const std::string& key) {
    std::shared_lock<std::shared_timed_mutex> lg(m);
    if (key.length()) {
        return h.get(key);
    }
    throw std::string("ERROR: Empty Key");
}
