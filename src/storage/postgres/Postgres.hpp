#ifndef Postgres_hpp
#define Postgres_hpp

#include <stack>
#include <pqxx/pqxx>
#include <iostream>
#include <chrono>
#include <thread>
#include "crud/Crud.hpp"

class CPostgres {
private: 
    std::mutex m_dbPoolMutex;
    std::stack<pqxx::connection*> m_dbPool;

    CCrud m_crud;
public:
    CPostgres(int connSize, std::string connString);

    pqxx::connection* GetConnection();
    void ReturnConnection(pqxx::connection* connection);
    CCrud* GetCrud();

};

#endif /* Postgres_hpp */