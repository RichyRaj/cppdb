# cppdb
#### A Simple Key-Value Store in C++

**cppdb** is a thread-safe key-value store written in **C++** for learning purposes. Uses a log-structured file backend as the data store and an in-memory hash table index. cppdb comes with a multithreaded [TCP server](https://github.com/RichyRaj/cppdb/blob/master/server/server.cpp) that can be used to query GET / PUT requests over a network. 

The storage mechanism is based on Chapter 3 of the [Designing Data-Intensive Applications](https://dataintensive.net/) book.

The project was inspired by :
- [gerlacdt/db-key-value-store](https://github.com/gerlacdt/db-key-value-store)
- [Code review of the above project](https://www.youtube.com/watch?v=ifBUfIb7kdo)

The API design was loosely based on
[RocksDB](https://github.com/facebook/rocksdb).

---

#### Usage

```cpp
#include "cppdb/db.h"

int main() {
    cppdb::Status s;
    cppdb::DB db;
    s = db.open("/tmp/players.db");
    assert(s.isOk());
    s = db.put("David De Gea", "1");
    assert(s.isOk());
    s = db.put("Victor Lindelof", "2");
    assert(s.isOk());
    s = db.put("Ander Herrera", "21");
    assert(s.isOk());
    s = db.put("Paul Pogba", "6");
    assert(s.isOk());
    s = db.put("Anthony Marial", "9");
    assert(s.isOk());
    v = db.get("Anthony Marial");
    assert(v == "9");
    v = db.get("David De Gea");
    assert(v == "1");
    s = db.update("Anthony Marial", "11");
    v = db.get("Anthony Marial");
    assert(v == "11");
    s = db.close();
    assert(s.isOk());
}
```

---

#### TODO:

- [ ] Add delete operation.
- [ ] Add drop operation.
- [ ] Review error handling.
- [ ] Review fileStream.clear().
- [ ] Support Config based opertaions.
- [ ] Remove old data in file.
- [ ] Crash recovery.
- [x] Mutlithreading ?

---
