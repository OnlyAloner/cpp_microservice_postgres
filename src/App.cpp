#include <pqxx/pqxx>
#include "crow.h"

#include "storage/postgres/Postgres.hpp"
#include "./AppComponent.hpp"

#include <iostream>

void run() {

}

CPostgres postgres(90, "host=localhost port=5434 dbname=postgres user=postgres password=postgres");

void doSomething() {
  
}

/**
 *  main
 */
int main(int argc, const char * argv[]) {
  crow::SimpleApp app;

  crow::logger::setLogLevel(crow::LogLevel::Warning);

  CROW_ROUTE(app, "/")([](){
    // auto response = postgres.GetCrud()->GetList();

    // std::string ans = "";
    // for (auto x:response.first) {
    //   ans += x.name;
    // }

    return "SOMETHING";
  });

  app.port(2001).multithreaded().run();

  return 0;
}
