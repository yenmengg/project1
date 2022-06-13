#include "Transaction.hpp"

Transaction::Transaction(string from, string to, int value)
    : m_from(from)
    , m_to(to)
    , m_value(value)
{
    hash<string> hasher;
    m_transactionHash = to_string(hasher(from+to+to_string(m_value)));
}
