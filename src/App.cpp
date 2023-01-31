#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

#include <pqxx/pqxx>
#include <dmitigr/pgfe/pgfe.hpp>
// #define CDS_THREADING_AUTODETECT    // http://libcds.sourceforge.net/doc/cds-api/namespacecds_1_1threading.html#_details
#include <cds/init.h>
#include <cds/gc/hp.h>

#include "crow.h"

typedef cds::gc::HP gc_type;

#include "storage/postgres/Postgres.hpp"
#include "./AppComponent.hpp"

#include <iostream>

/**
 *  main
 */
int main(int argc, const char * argv[]) {
  crow::SimpleApp app;

  CPostgres postgres(90, "host=localhost port=5434 dbname=postgres user=postgres password=postgres", app);

  crow::logger::setLogLevel(crow::LogLevel::Warning);

  app.port(2001).concurrency(80).run();


  return 0;
}
