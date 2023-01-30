#include "Postgres.hpp"

CPostgres::CPostgres(int connSize, std::string connString) : m_crud(this)
{
    for (int i = 0; i < connSize; i++) {
        std::cout << "ConnString: " << connString << '\n';
        std::cout << "Creating connection number: " << i << '\n';
        auto conn = new pqxx::connection(connString);
        auto worker = new pqxx::work((*conn));
        auto connPair = std::make_pair(worker, conn);
        m_dbPool.emplace(connPair);
    }
}

CCrud* CPostgres::GetCrud() {
    return &m_crud;
}

std::pair<pqxx::work*, pqxx::connection*> CPostgres::GetConnection() {
    bool index = false;
    std::pair<pqxx::work*, pqxx::connection*> conn;

#ifdef MUTEX_STACK
    while (true) {
        if (index) std::this_thread::sleep_for(std::chrono::milliseconds(1));

        std::lock_guard<std::mutex> lock(mutex_stack);
        if (m_dbPool.empty()) {
            index = true;
            continue;
        }

        conn = m_dbPool.top();
        m_dbPool.pop();
        break;
    }
#endif

    return conn;
}

void CPostgres::ReturnConnection(std::pair<pqxx::work*, pqxx::connection*> connection) {
#ifdef MUTEX_STACK
    std::lock_guard<std::mutex> lock(mutex_stack);
#endif

    m_dbPool.emplace(connection);

}