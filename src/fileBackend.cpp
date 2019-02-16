//
// Copyright (c) Richard Raj. All rights reserved.
// Licensed under the MIT license. See LICENSE file for details.
//

#include "cppdb/fileBackend.h"

cppdb::Status cppdb::FileBackend::open(const std::string &name) {
  // Creates a new file / opens an exisiting file in append mode
  // Returns true/false status of the opertaion which will be converted to a
  // proper Status instance by the DB wrapper
  if (name.empty()) {
    return cppdb::Status::Error();
  }
  if (f.is_open()) {
    f.close();
  }
  f.open(name, std::fstream::in | std::fstream::out | std::fstream::app);
  if (isOk()) {
    return cppdb::Status::OK();
  }
  return cppdb::Status::Error();
}

cppdb::Status cppdb::FileBackend::close() {
  // TODO(richardraj): Check and remove ....
  f.clear();
  f.close();
  if (isOk()) {
    return cppdb::Status::OK();
  }
  return cppdb::Status::Error();
}

cppdb::Status cppdb::FileBackend::buildIndex(
  std::unordered_map<std::string, int>* index) {
  nextOffset = 0;
  std::string line;
  while (std::getline(f, line)) {
    std::stringstream linestream(line);
    std::string key;
    key = line.substr(0, line.find(','));
    (*index)[key] = nextOffset;
    // next offset
    int noChars(line.length() + 1);
    nextOffset += noChars;
  }
  // TODO(richardraj): calls to seekg requrie this. Read more on this. Remove
  // once get is implemented..
  f.clear();

  if (isOk()) {
    return cppdb::Status::OK();
  }
  return cppdb::Status::Error();
}

int cppdb::FileBackend::put(const std::string &key,
const std::string &value) {
  int currentOffset = nextOffset;
  if (key.empty() || value.empty()) {
    return -1;
  }
  if (!isOk()) {
    return -1;
  }
  f << key << "," << value << std::endl;
  // 1 for comma. 1 for new line
  nextOffset += key.length() + 1 + value.length() + 1;
  if (!isOk()) {
    return -1;
  }
  return currentOffset;
}

/**
Given an offset, gets the line and returns the value 
*/
std::string cppdb::FileBackend::get(int offset) {
  // offset = 1071;
  std::string line;
  f.clear();
  f.seekg(offset, std::ios::beg);
  std::getline(f, line);
  std::stringstream linestream(line);
  std::string key;
  std::string value;
  std::getline(linestream, key, ',');
  linestream >> value;
  return value;
}

bool cppdb::FileBackend::isOk() const {
  if (!f || !f.good() || f.fail()) {
    return false;
  }
  return true;
}
