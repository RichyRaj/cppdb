//
// Copyright (c) Richard Raj. All rights reserved.
// Licensed under the MIT license. See LICENSE file for details.
//

#include "cppdb/hashIndex.h"

cppdb::Status cppdb::HashIndex::open(const std::string& name) {
    // Opening a db includes opening the file associated and setting up
    // the index
    cppdb::Status s;

    // Create/Open the backend
    s = f.open(name);
    if (s.isError()) {
        return s;
    }
    // backend is ready
    // loop through the contents and build the index
    s = f.buildIndex(&index);

    // TODO(richardraj): Remove
    std::cout << "=================== INDEX ================================="
    << std::endl;
    for (auto const& x : index) {
        std::cout << x.first << " ---- " << x.second << std::endl;
    }
    std::cout << "=================== INDEX ================================="
    << std::endl;
    return s;
}

cppdb::Status cppdb::HashIndex::close() {
    cppdb::Status s;
    s = f.close();
    if (s.isError()) {
        return s;
    }
    index.clear();
    return cppdb::Status::OK();
}
