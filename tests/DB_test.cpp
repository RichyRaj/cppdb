//
// Copyright (c) Richard Raj. All rights reserved.
// Licensed under the MIT license. See LICENSE file for details.
//

#include <cassert>
#include <iostream>
#include <thread>
#include "cppdb/status.h"
#include "cppdb/fileBackend.h"
#include "cppdb/hashIndex.h"
#include "cppdb/db.h"

void insertX(cppdb::DB& db) {
  // Does 1000 x inserts
  for (int i = 0; i < 100; i++) {
    db.put("x", std::to_string(i));
    std::cout << "Wrote" << i << std::endl;
  }
}

void readX(cppdb::DB& db) {
  // Reads x 1000 times
  for (int i = 0; i < 100; i++) {
    std::cout << "Reading " << db.get("x") << std::endl;
  }
}


void testMultithreadPut() {
  cppdb::DB db;
  db.open("/tmp/mt.db");
  db.put("x", "-1");
  std::thread t1(insertX, std::ref(db));
  std::thread t2(readX, std::ref(db));
  t1.join();
  t2.join();
  db.close();
}

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
  int offset;
  s = b.open("./first.db");
  assert(s.isOk());
  offset = b.put("Carrick", "16");
  assert(s.isOk());
  offset = b.put("Messi", "10");
  assert(s.isOk());
  s = b.close();
  assert(s.isOk());
  std::cout << "File tests pass" << std::endl;
  // ===========================================================================
  // Index Tests
  cppdb::HashIndex h(b);
  std::string v;
  s = h.open("./first.db");
  assert(s.isOk());
  s = h.put("Ronaldo", "7");
  assert(s.isOk());
  s = h.put("De Gea", "1");
  assert(s.isOk());
  v = h.get("De Gea");
  assert(v == "1");

  s = h.close();
  assert(s.isOk());

  s = h.open("./firstTest.db");
  assert(s.isOk());
  s = h.put("Ronaldo", "7");
  assert(s.isOk());
  s = h.put("Ibra", "9");
  assert(s.isOk());
  v = h.get("Ibra");
  assert(v == "9");
  s = h.put("Ronaldo", "9");
  assert(s.isOk());
  v = h.get("Ronaldo");
  assert(v == "9");
  std::cout << "Index tests pass" << std::endl;
  // ===========================================================================
  // Library Tests
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
  std::cout << "Library tests pass" << std::endl;
  // ===========================================================================
  testMultithreadPut();
  std::cout << "Multi-Thread tests pass" << std::endl;
}
