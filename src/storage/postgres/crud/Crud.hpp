#ifndef Crud_hpp
#define Crud_hpp

class CPostgres;

#include <vector>
#include <utility>
#include <iostream>
#include "../../../pkg/defer/Defer.hpp"

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
    std::pair<std::vector<Name>, std::exception*> GetList();
    std::pair<Name, std::exception*> GetByPk(std::string id);
    std::pair<std::string, std::exception*> Update(std::string name, std::string id);
    std::exception* Delete(std::string id);
};

#include "../Postgres.hpp"

#endif /* Crud_hpp */