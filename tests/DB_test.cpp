//
// Copyright (c) Richard Raj. All rights reserved.
// Licensed under the MIT license. See LICENSE file for details.
//

#include <cassert>
#include <iostream>
#include "cppdb/status.h"
#include "cppdb/fileBackend.h"

int main() {
  cppdb::Status s;

  // Status Tests
  assert(s.isNone());
  s = cppdb::Status::OK();
  assert(s.isOk());
  s = cppdb::Status::Error();
  assert(s.isError());
  std::cout << "Status tests pass" << std::endl;
  // ===========================================================================
  // File Tests
  cppdb::FileBackend b;
  s = b.open("./first.db");
  assert(s.isOk());
  std::cout << "File tests pass" << std::endl;
}
