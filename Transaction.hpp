#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Transaction
{
public:
    Transaction(string from, string to, int value);

public:
    string m_transactionHash;
    string m_from;
    string m_to;
    int m_value;
};

#endif