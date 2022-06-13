# project1

compile:

g++ -std=c++11 main.cpp Block.cpp Transaction.cpp -o main

run:

1. ./main
2. ./main input.txt


output:

1. print logs in console:

blockchain.dump();

2. write to output file:

./main input.txt > log


input format for transactions:

[from_address to_address value]

input.txt:

addr1 addr2 10

addr3 addr2 1

addr5 addr3 4

addr4 addr1 5


---------------------------
Design details:

1. define Transaction class

calculate hash using (from, to, value) for each transaction 

to do: 
generate (private key, public key) for signature, and checks if it is valid


2. define Block class

a. calculate hash using (parentHash, blockHeight, transactions) for each block 

b. use nonce for block mining

3. define blockchain class in main.c

a. chain: array of blocks 

b. adjust difficulty for block mining 

c. create genesis block as the first block

d. pendingTransactions: store transactions, put them in a block and start mining every 10 sec

e. add a new transaction to pending transactions if:

the amount sent is not greater than balance

pending transactions for this wallet is not higher than balance

f. get the balance of a given wallet address

g. check chain valid: loop all the blocks in the chain and verify if nobody has tampered with the hashes

---------------------------
reference:

https://bitcoin.org/bitcoin.pdf

https://onezero.medium.com/how-does-the-blockchain-work-98c8cd01d2ae


-------------------------------
Questions:

1. Compare the difference between account/UTXO based models.

以太坊的 Account 架構: https://etherscan.io/
類似銀行帳戶，有資料庫在記錄每個帳號和帳號的餘額，透過交易來更新
同一個地址(帳戶)發送出的交易有先後順序之分（Nonce）

比特幣的 UTXO 模型: https://blockstream.info/
比特幣是一坨一坨的錢堆，我們的地址像是能夠操控這些錢堆的鑰匙。可以把錢堆湊在一起做交易；也可以把一坨錢堆拆開來交易
每一筆交易可以有多個 input（錢堆），交易後也可以變成一或多個新的錢堆。

UTXO 解決 Account model 同一個地址（帳戶）無法「同時」進行兩筆交易的問題
一個地址可以「同時」將多個錢堆發送給多個不同的地址，在同一個區塊，甚至同一筆交易中完成。可以把多個錢堆同時進行交易，讓交易變得更加有效率。

2. How to ensure transaction order in an account based model?
以太幣為了避免 Double Spending, 同一筆錢被花了兩次，會以 Nonce 來標註每一筆交易的先後次序，若同時發送多筆交易，一旦前面有一筆交易卡住，則後面的交易也都會跟著塞住。

3. What is transaction/block?
A transaction is a cryptographically signed instruction from an account that changes the state of the blockchain. We can track the details of all transactions in the network.

A block is a place in a blockchain where information is stored and encrypted.
Blocks are identified by long numbers that include encrypted transaction information from previous blocks and new transaction information.

4. Why is setting block generation time necessary?
The 

Block time defines the time it takes to mine a block.

The expected block time is set at a constant value to make sure, miners cannot impact the security of the network by adding more computational power. The average block time of the network is evaluated after n number of blocks, and if it is greater than the expected block time, then the difficulty level of the proof of work algorithm will be reduced, and if it is less than the expected block time then the difficulty level will be increased. 

5. When to update the account balance?

Each node in the blockchain is keeping a copy of the ledger.
The blockchain system doesn’t keep track of account balances; it only records each transaction that is verified and approved. To determine your wallet balance, you need to analyze and verify all the transactions that ever took place on the whole network connected to your wallet.

