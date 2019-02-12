//
// Copyright (c) Richard Raj. All rights reserved.
// Licensed under the MIT license. See LICENSE file for details.
//

#include "cppdb/status.h"
#include <cassert>
#include <iostream>

int main() {
  cppdb::Status s;
  assert(s.isNone());
  s = cppdb::Status::OK();
  assert(s.isOk());
  s = cppdb::Status::Error();
  assert(s.isError());
  std::cout << "All tests pass" << std::endl;
}
