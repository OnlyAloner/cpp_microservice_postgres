#include "Postgres.hpp"

CPostgres::CPostgres(int connSize, std::string connString) : m_crud(this)
{
    std::lock_guard<std::mutex> guard(m_dbPoolMutex);
    for (int i = 0; i < connSize; i++) {
        std::cout << "ConnString: " << connString << '\n';
        std::cout << "Creating connection number: " << i << '\n';
        m_dbPool.emplace(new pqxx::connection(connString));
    }
}

CCrud* CPostgres::GetCrud() {
    return &m_crud;
}

pqxx::connection* CPostgres::GetConnection() {
    int index = 0;

    while (true) {
        std::lock_guard<std::mutex> guard(m_dbPoolMutex);
        if (!m_dbPool.empty()) {
            auto conn = m_dbPool.top();
            defer(m_dbPool.pop());

            return conn;
        }

        guard.~lock_guard();
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
        index++;

        if (index > 30) {
            throw std::runtime_error("Could not get connection from pool");
        }
    }
}

void CPostgres::ReturnConnection(pqxx::connection* connection) {
    std::lock_guard<std::mutex> guard(m_dbPoolMutex);
    m_dbPool.emplace(connection);
}