//
// Copyright (c) Richard Raj. All rights reserved.
// Licensed under the MIT license. See LICENSE file for details.
//

#include<iostream>
#include "cppdb/fileBackend.h"

cppdb::Status cppdb::FileBackend::open(const std::string& name) {
  // Creates a new file / opens an exisiting file in append mode
  // Returns true/false status of the opertaion which will be converted to a
  // proper Status instance by the DB wrapper
  if (name.empty()) {
    return cppdb::Status::Error();
  }
  if (f.is_open()) {
      f.close();
  }
  f.open(name,  std::fstream::app);
  // f.close();
  if (isOk()) {
    return cppdb::Status::OK();
  }
  return cppdb::Status::Error();
}

cppdb::Status cppdb::FileBackend::close() {
  f.close();
  if (isOk()) {
    return cppdb::Status::OK();
  }
  return cppdb::Status::Error();
}

cppdb::Status cppdb::FileBackend::put(const std::string& key,
    const std::string& value) {
    if (key.empty() || value.empty()) {
        return cppdb::Status::Error();
    }
    if (!isOk()) {
        return cppdb::Status::Error();
    }
    f << key << "," << value << std::endl;
    if (isOk()) {
      return cppdb::Status::OK();
    }
    return cppdb::Status::Error();
}

bool cppdb::FileBackend::isOk() {
  if (!f || !f.good() || f.fail()) {
    return false;
  }
  return true;
}
