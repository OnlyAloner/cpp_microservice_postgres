#include "Crud.hpp"

CCrud::CCrud(CPostgres* postgres) : m_postgres(postgres) 
{

}

// std::pair<std::string, std::exception*> CCrud::Create(std::string name) {
//     auto conn = m_postgres->GetConnection();
//     defer(m_postgres->ReturnConnection(conn));

//     auto worker = pqxx::work(*conn);

//     try
//     {   
//         (*conn).prepare("INSERT_INTO_NAMES", "INSERT INTO NAMES(name) VALUES($1) RETURNING name;");

//         std::string id;

//         pqxx::result resp = worker.exec_prepared("INSERT_INTO_NAMES", name);

//         id = resp[0][0].c_str();

//         worker.commit();

//         return std::make_pair(id, nullptr);
//     }
//     catch (const std::exception& e)
//     {
//         std::cout << e.what() << '\n';
//         auto err = new std::exception();
//         return std::make_pair("Error", err);
//     }
// }
std::pair<std::vector<Name>, std::exception*> CCrud::GetList() {
    // auto conn = m_postgres->conn;

    auto conn = m_postgres->GetConnection();
    auto worker = conn.first;
    // std::cout << "WORKER\n";
    // defer(m_postgres->ReturnConnection(conn));

    // auto worker = m_postgres->worker;
    // defer(worker.commit());

    std::vector<Name> names;
    try
    {
        pqxx::result response = (*worker).exec("SELECT * FROM names LIMIT 10;");

        for (auto x:response) {
            Name name;
            name.id = x[0].c_str();
            name.name = x[1].c_str();
            names.push_back(name);
        }
        m_postgres->ReturnConnection(conn);
        return std::make_pair(names, nullptr);
    }
    catch (const std::exception& e)
    {
        m_postgres->ReturnConnection(conn);
        std::cout << e.what() << '\n';
        auto excep = new std::exception(e);
        return std::make_pair(names, excep);
    }
}
// std::pair<Name, std::exception*> CCrud::GetByPk(std::string id) {
//     auto conn = m_postgres->GetConnection();
//     defer(m_postgres->ReturnConnection(conn));

//     auto worker = pqxx::work(*conn);

//     Name name;
//     try
//     {
//         (*conn).prepare("SELECT_FROM_NAMES_BY_PK", "SELECT * FROM names WHERE id = $1;");

//         pqxx::result response = worker.exec_prepared("SELECT_FROM_NAMES_BY_PK", id);

//         name.id = response[0][0].c_str();
//         name.name = response[0][1].c_str();

//         worker.commit();
//         return std::make_pair(name, nullptr);
//     }
//     catch (const std::exception* e)
//     {
//         return std::make_pair(name, nullptr);
//     }
// }
// // std::pair<std::string, std::exception> CCrud::Update(std::string name, std::string id) {
// //     auto worker = m_connection->

// //     try
// //     {
// //         pqxx::result response = worker.exec("UPDATE names SET name = " + name + " WHERE id = " + id + " RETURNING id, name");
// //         worker.commit();
// //         return std::make_pair(response, nullptr);
// //     }
// //     catch (const std::exception& e)
// //     {
// //         return std::make_pair(nullptr, e);
// //     }
// // }
// std::exception* CCrud::Delete(std::string id) {
//     auto conn = m_postgres->GetConnection();
//     defer(m_postgres->ReturnConnection(conn));

//     auto worker = pqxx::work(*conn);

//     try
//     {
//         (*conn).prepare("DELETE_FROM_NAMES", "DELETE FROM names WHERE id = $1;");

//         pqxx::result response = worker.exec_prepared("DELETE_FROM_NAMES", id);

//         worker.commit();
//         return nullptr;
//     }
//     catch (const std::exception& e)
//     {
//         return nullptr;
//     }
// }