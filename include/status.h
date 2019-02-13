//
// Copyright (c) Richard Raj. All rights reserved.
// Licensed under the MIT license. See LICENSE file for details.
//

/**
A Status represents the result of a cppdb operation
An operation can be in one of the following states : Ok, Error, None
**/

#pragma once

namespace cppdb {
enum Code {
  S_Ok,
  S_Error,
  S_None
};

class Status {
 public:
    Status() : code(S_None) {}
    explicit Status(cppdb::Code s) : code(s) {}

    static Status OK() {
      return Status(S_Ok);
    }
    static Status Error() {
      return Status(S_Error);
    }

    cppdb::Code getState() const {
      return code;
    }

    bool isOk() const {
      return getState() == S_Ok;
    }
    bool isError() const {
      return getState() == S_Error;
    }
    bool isNone() const {
      return getState() == S_None;
    }

 private:
    Code code;
};
}  // namespace cppdb
