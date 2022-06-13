#include "Block.hpp"

Block::Block(int blockHeight, string parentHash, vector<Transaction> transactions)
    : m_parentHash(parentHash)
    , m_blockHeight(blockHeight)
    , m_transactions(transactions)
    , nonce(0)
{ 
    m_blockHash = calculateHash();
}

string Block::calculateHash()
{
    hash<string> hasher;

    string str = m_parentHash + to_string(m_blockHeight);

    for (auto tx : m_transactions)
    {
        str += "{ transactionHash:" + tx.m_transactionHash
            + ",from:" + tx.m_from
            + ",to:" + tx.m_to
            + ",value:" + to_string(tx.m_value) + " }, ";
    }
    str += to_string(nonce); //
    return to_string(hasher(str));
}


void Block::printBlock()
{
    cout << "{ block height: " << m_blockHeight;
    cout << ", block hash: " << m_blockHash;
    cout << ", parent hash: " << m_parentHash;

    cout << ", transactions: ";
    for (auto tx : m_transactions)
    {
        cout << "{ tx hash: " << tx.m_transactionHash;
        cout << ", from: " << tx.m_from;
        cout << ", to: " << tx.m_to;
        cout << ", value: " << tx.m_value << " }, ";
    }
    cout << " }" << endl;
}

void Block::mineBlock(int difficulty)
{
    // Starts the mining process on the block. It changes the 'nonce' until the hash
    // of the block starts with enough zeros (= difficulty)

    string target(difficulty,'0');
    while (m_blockHash.substr(0, difficulty) != target)
    {
        nonce++;
        m_blockHash = calculateHash();
    }

    cout<<"Block mined: " << m_blockHash << endl;
}
