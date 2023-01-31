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
int CCrud::GetList(std::vector<Name>& resp) {
    auto conn = m_postgres->GetConnection();

    std::vector<Name> names;
    try
    {
        {
            conn->execute([&resp](auto&& r)
            {
                Name name;
                name.id = to<std::string>(r[0]);
                name.name = to<std::string>(r[1]);

                resp.emplace_back(name);
            }, "SELECT * FROM names LIMIT 10");
            m_postgres->ReturnConnection(conn);
        }

        return 0;
    }
    catch (const dmitigr::pgfe::Client_exception& e)
    {
        std::cout << "HERE: " << e.what() << '\n';
        auto excep = new std::exception(e);
        return 1;
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