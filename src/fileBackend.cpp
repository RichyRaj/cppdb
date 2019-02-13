//
// Copyright (c) Richard Raj. All rights reserved.
// Licensed under the MIT license. See LICENSE file for details.
//

#include "cppdb/fileBackend.h"

cppdb::Status cppdb::FileBackend::open(const std::string& name) {
  // Makes sure that we are able to create/open the database
  // Returns true/false status of the opertaion which will be converted to a
  // proper Status instance by the DB wrapper
  if (name.empty()) {
    return cppdb::Status::Error();
  }
  f.open(name,  std::fstream::app);
  f.close();
  if (isOk()) {
    return cppdb::Status::OK();
  }
}

bool cppdb::FileBackend::isOk() {
  if (!f || !f.good() || f.fail()) {
    return false;
  }
  return true;
}
