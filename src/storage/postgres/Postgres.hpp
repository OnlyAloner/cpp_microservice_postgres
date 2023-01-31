#ifndef Postgres_hpp
#define Postgres_hpp

#include <stack>
#include <pqxx/pqxx>
#include <iostream>
#include <chrono>
#include <utility>
#include <thread>
#include <atomic>
#include "crow.h"
#include "crud/Crud.hpp"
#include <cds/container/treiber_stack.h>
#include <cds/gc/hp.h>
#include <dmitigr/pgfe/pgfe.hpp>

typedef cds::gc::HP gc_type;

#define MUTEX_STACK

class CPostgres {
private: 
    CCrud m_crud;

    // cds::container::TreiberStack<gc_type, std::pair<pqxx::work*, pqxx::connection*>> m_dbPool;

#ifdef MUTEX_STACK
    std::mutex mutex_stack;
    std::stack<dmitigr::pgfe::Connection*> m_dbPool;
#endif

public:
    std::string connString;
    dmitigr::pgfe::Connection_pool* dbPool;
    CPostgres(int connSize, std::string connString, crow::SimpleApp& app);

    dmitigr::pgfe::Connection* GetConnection();
    void ReturnConnection(dmitigr::pgfe::Connection* connection);
    CCrud* GetCrud();
};

#endif /* Postgres_hpp */