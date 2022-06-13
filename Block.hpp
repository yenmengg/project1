#ifndef BLOCK_H
#define BLOCK_H

#include <iostream>
#include <vector>
#include <string>

#include "Transaction.hpp"

using namespace std;

class Block
{
public:
    Block(int blockHeight, string parentHash, vector<Transaction> transactions);
    string calculateHash();
    void printBlock();
    void mineBlock(int difficulty);

public:
    string m_blockHash;
    string m_parentHash;
    int m_blockHeight;
    vector<Transaction> m_transactions;
    int nonce;
};

#endif