#include "Postgres.hpp"
struct nameR {
    std::string name;
};

CPostgres::CPostgres(int connSize, std::string connString, crow::SimpleApp& app) : m_crud(this), connString(connString)
{
    // dbPool = new dmitigr::pgfe::Connection_pool(90,
    //         dmitigr::pgfe::Connection_options{}
    //         .set(dmitigr::pgfe::Communication_mode::net)
    //         .set_hostname("localhost")
    //         .set_port(5434)
    //         .set_database("postgres")
    //         .set_username("postgres")
    //         .set_password("postgres"));

    // dbPool->connect();


    CROW_ROUTE(app, "/")([this](){
        std::vector<Name> resp;
        if (this->GetCrud()->GetList(resp)) {
            std::cout << "ERROR\n";
            return crow::response(500, "");
        }

        std::string ans = "";
        for (auto x:resp) {
          ans += x.name;
        }

        return crow::response(200, ans);
    });
    // cds::threading::Manager::attachThread();


    for (int i = 0; i < connSize; i++) {
        std::cout << "ConnString: " << connString << '\n';
        std::cout << "Creating connection number: " << i << '\n';
        auto conn = new dmitigr::pgfe::Connection(dmitigr::pgfe::Connection_options{}
            .set(dmitigr::pgfe::Communication_mode::net)
            .set_hostname("localhost")
            .set_port(5434)
            .set_database("postgres")
            .set_username("postgres")
            .set_password("postgres"));

        conn->connect();
        m_dbPool.emplace(conn);
    }

    // cds::threading::Manager::detachThread();
}

CCrud* CPostgres::GetCrud() {
    return &m_crud;
}

dmitigr::pgfe::Connection* CPostgres::GetConnection() {
    bool index = false;
    // cds::threading::Manager::attachThread();

    // dmitigr::pgfe::Connection* conn;
    std::lock_guard<std::mutex> lock(mutex_stack);
    auto conn = m_dbPool.top();
    m_dbPool.pop();
    return conn;

    // while (conn.first == nullptr) {
    //     m_dbPool.pop(conn);

    //     std::this_thread::sleep_for(std::chrono::milliseconds(index));
    //     index = true;
    // }

// #ifdef MUTEX_STACK
//     while (true) {
//         std::this_thread::sleep_for(std::chrono::milliseconds(index));

//         if (m_dbPool.empty()) {
//             index = true;
//             continue;
//         }

//     }
// #endif

    return conn;
}

void CPostgres::ReturnConnection(dmitigr::pgfe::Connection* connection) {
    // cds::threading::Manager::attachThread();
#ifdef MUTEX_STACK
    std::lock_guard<std::mutex> lock(mutex_stack);
#endif

    m_dbPool.emplace(connection);

}