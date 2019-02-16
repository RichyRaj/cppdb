//
// Copyright (c) Richard Raj. All rights reserved.
// Licensed under the MIT license. See LICENSE file for details.
//

/**
Defines a File Based Storage Engine for the DB
**/

#pragma once

#include <fstream>
#include <string>
#include <unordered_map>
#include <sstream>
#include <iostream>
#include "cppdb/status.h"

namespace cppdb {
class FileBackend {
 public:
    FileBackend() : f(), nextOffset(0) {}
    cppdb::Status open(const std::string&);
    cppdb::Status close();
    cppdb::Status buildIndex(std::unordered_map<std::string, int>*);

    int put(const std::string&, const std::string&);
    std::string get(int offset);
    bool isOk() const;
 private:
    std::fstream f;
    int nextOffset;
};
}  // namespace cppdb
