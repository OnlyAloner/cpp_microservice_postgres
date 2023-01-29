#ifndef Postgres_hpp
#define Postgres_hpp

#include <stack>
#include <pqxx/pqxx>
#include <iostream>
#include <chrono>
#include <utility>
#include <thread>
#include "crud/Crud.hpp"
#include "../../pkg/mutex/Mutex.hpp"

class CPostgres {
private: 
    CCrud m_crud;
    std::mutex mutex_stack;
    std::stack<std::pair<pqxx::work*, pqxx::connection*>> m_dbPool;
public:
    CPostgres(int connSize, std::string connString);

    std::pair<pqxx::work*, pqxx::connection*> GetConnection();
    void ReturnConnection(std::pair<pqxx::work*, pqxx::connection*> connection);
    CCrud* GetCrud();
};

#endif /* Postgres_hpp */