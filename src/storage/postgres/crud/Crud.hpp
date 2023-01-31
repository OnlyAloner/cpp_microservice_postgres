#ifndef Crud_hpp
#define Crud_hpp

class CPostgres;

#include <vector>
#include <utility>
#include <iostream>
#include <pqxx/pqxx>

struct Name {
    std::string id;
    std::string name;
};

class CCrud {
private:
    CPostgres* m_postgres;
public:
    CCrud(CPostgres* postgers);
    // ~CCrud();

    std::pair<std::string, std::exception*> Create(std::string name);
    int GetList(std::vector<Name>& resp);
    std::pair<Name, std::exception*> GetByPk(std::string id);
    std::pair<std::string, std::exception*> Update(std::string name, std::string id);
    std::exception* Delete(std::string id);
};

#include "../Postgres.hpp"

#endif /* Crud_hpp */