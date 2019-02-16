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
    if (key.length()) {
        return h.put(key, value);
    }
    return cppdb::Status::Error();
}

std::string cppdb::DB::get(const std::string& key) {
    if (key.length()) {
        return h.get(key);
    }
    throw std::string("ERROR: Empty Key");
}
