#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include "Block.hpp" 
#include "Transaction.hpp"

using namespace std;

class Blockchain
{
public:
    Blockchain()
    {
        chain.push_back(createGenesisBlock());
        difficulty = 1;
    }

    Block createGenesisBlock()
    {
        return Block(0, "0", {});
    }
    
    void minePendingTransactions()
    {
        // Takes all the pending transactions, puts them in a Block and starts the
        // mining process.
        
        // create a new Block with the hash of the previous Block
        Block block(chain.size(), chain.back().m_blockHash, m_pendingTransactions);

        // take long time ....
        //block.mineBlock(difficulty);
        //cout << "Block successfully mined" << endl;

        chain.push_back(block);
        m_pendingTransactions.clear();
    }

    void addTransaction(Transaction transaction)
    {
        // Add a new transaction to the list of pending transactions

        // the amount sent is not greater than balance
        int balance = getBalanceOfAddress(transaction.m_from);
        if (balance < transaction.m_value)
        {
            cout << "Not enough balance" << endl;
            return;
        }

        // Get all pending transactions for "from" wallet
        // calculate the total amount of spend coins so far.
        // If this exceeds the balance, cannot add this transaction.

        int totalAmount = transaction.m_value;
        for (auto tx : m_pendingTransactions)
        {
            if (tx.m_from == transaction.m_from)
            {
                totalAmount += tx.m_value;
            }
        }

        if (totalAmount > balance) 
        {
            cout << "Pending transactions for this wallet is higher than its balance" << endl;
            return;
        }

        m_pendingTransactions.push_back(transaction);
    }


    int getBalanceOfAddress(string address)
    {
        // 100 coins
        int balance = 100;

        for (auto block : chain)
        {
            for (auto tx : block.m_transactions)
            {
                if (tx.m_from == address)
                {
                    balance -= tx.m_value;
                }

                if (tx.m_to == address)
                {
                    balance += tx.m_value;
                }
            }
        }

        return balance;
    }

    bool isChainValid()
    {
        for (int i = 1; i < chain.size(); i++)
        {
            auto curBlock = chain[i];
            auto preBlock = chain[i - 1];

            if (curBlock.m_blockHash != curBlock.calculateHash())
            {
                return false;
            }

            if (curBlock.m_parentHash != preBlock.m_blockHash)
            {
                return false;
            }
        }

        return true;
    }

    void dump()
    {
        for (auto blk : chain)
        {
            blk.printBlock();
        }
    }

public:
    vector<Block> chain;
    int difficulty;
    vector<Transaction> m_pendingTransactions;
};

int main(int argc, char* argv[])
{
    Blockchain blockchain = Blockchain();

    //load transaction from input file
    if (argc > 1)
    {
        ifstream infile(argv[1]);
        string line;
        if (infile.is_open()) 
        {
            while (getline(infile, line))
            {
                istringstream iss(line);
                string from;
                string to;
                int val;
                if (iss >> from >> to >> val)
                {
                    Transaction transaction(from, to, val);
                    blockchain.addTransaction(transaction);

                    // to do: generate new block every 10 sec 
                    blockchain.minePendingTransactions();
                }
            }
            infile.close();
        }
    }
    

    Transaction transaction1 = Transaction("addr1","addr3",2);
    blockchain.addTransaction(transaction1);
    blockchain.minePendingTransactions();

    Transaction transaction2 = Transaction("addr1","addr5",4);
    blockchain.addTransaction(transaction2);
    blockchain.minePendingTransactions();

    cout << "balance " << blockchain.getBalanceOfAddress("addr1") << endl;

    blockchain.dump();

    cout << "blockchain valid: " << blockchain.isChainValid()<<endl;

    /*
    // Uncomment to test tampering with the chain
    blockchain.chain[1].m_transactions[0].m_value += 9;
    cout << "blockchain valid: " << blockchain.isChainValid()<<endl;
    */

  return 0;
}