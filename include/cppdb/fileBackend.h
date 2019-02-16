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
    FileBackend() {}
    cppdb::Status open(const std::string&);
    cppdb::Status close();
    cppdb::Status put(const std::string&, const std::string&);
    cppdb::Status buildIndex(std::unordered_map<std::string, int>*);
    bool isOk();
 private:
    std::fstream f;
};
}  // namespace cppdb
