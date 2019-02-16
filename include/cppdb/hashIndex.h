//
// Copyright (c) Richard Raj. All rights reserved.
// Licensed under the MIT license. See LICENSE file for details.
//

/**
Defines a Hash Table based indexer for the file backend
**/

#pragma once

#include <unordered_map>
#include <iostream>
#include <string>
#include "cppdb/status.h"
#include "cppdb/fileBackend.h"

namespace cppdb {
class HashIndex {
 public:
    explicit HashIndex(cppdb::FileBackend& fb) : f(fb) {}
    cppdb::Status open(const std::string&);
    cppdb::Status close();
    cppdb::Status put(const std::string&, const std::string&);
    std::string get(const std::string&);
 private:
    std::unordered_map<std::string, int> index;
    cppdb::FileBackend& f;
};
}  // namespace cppdb
