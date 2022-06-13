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


