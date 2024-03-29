//
// Copyright (c) Richard Raj. All rights reserved.
// Licensed under the MIT license. See LICENSE file for details.
//


#pragma once

#include <string>
#include <mutex>
#include "cppdb/status.h"
#include "cppdb/fileBackend.h"
#include "cppdb/hashIndex.h"

namespace cppdb {
class DB {
 public:
    DB()  : f(), h(f), isOpen(false) {}
    cppdb::Status open(const std::string&);
    cppdb::Status close();
    cppdb::Status put(const std::string&, const std::string&);
    cppdb::Status update(const std::string&, const std::string&);
    std::string get(const std::string&);
 private:
    cppdb::FileBackend f;
    cppdb::HashIndex h;
    std::mutex m;
    bool isOpen;
};
}  // namespace cppdb
