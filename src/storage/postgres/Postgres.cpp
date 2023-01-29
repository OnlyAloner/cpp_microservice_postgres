#include "Postgres.hpp"

CPostgres::CPostgres(int connSize, std::string connString) : m_crud(this)
{
    for (int i = 0; i < connSize; i++) {
        std::cout << "ConnString: " << connString << '\n';
        std::cout << "Creating connection number: " << i << '\n';
        auto conn = new pqxx::connection(connString);
        auto worker = new pqxx::work((*conn));
        m_dbPool.emplace(std::make_pair(worker, conn));
    }
}

CCrud* CPostgres::GetCrud() {
    return &m_crud;
}

std::pair<pqxx::work*, pqxx::connection*> CPostgres::GetConnection() {
    bool index = false;
    
    std::pair<pqxx::work*, pqxx::connection*> conn;
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

    return conn;
}

void CPostgres::ReturnConnection(std::pair<pqxx::work*, pqxx::connection*> connection) {
    std::lock_guard<std::mutex> lock(mutex_stack);
    m_dbPool.emplace(connection);
}