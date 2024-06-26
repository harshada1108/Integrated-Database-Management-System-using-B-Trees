# Integrated-Database-Management-System-using-B-Trees

Implemented B+ trees of order 4 to efficiently manage four databases: Aadhar, PAN-cards, bank accounts, and LPG subsidies. Three B+ trees are constructed based on Aadhar numbers, PAN numbers, and bank account details as keys. Each node in these trees is interconnected, allowing seamless traversal between Aadhar, PAN, bank account, and LPG data with just Log(N) operations. This approach ensures efficient data retrieval and range search functionalities, addressing the problem statement's requirements effectively.


Below is the question that i have implemented 
corresponding Aadhar numbers. Second database is of PAN-cards that contains in every 
node, name of a person, address, his/her PAN number and his/her Aadhar number. Third 
database is bank-accounts, which contains name of a person, his/her PAN number and the 
account details (bank, account number, deposited amount etc). Fourth database is LPGdatabase which contains name of a person, his/her bank-account-number and whether the 
person has taken LPG subsidy or not (YES or NO). Assume that Aadhar numbers are unique 
as they are derived from biometric data of a person that is assumed to be unique. Take as 
input, above four databases which are already populated. 
1. Print names, addresses and Aadhar numbers of all those people who have Aadhar 
numbers but no PAN numbers. 
2. Print names, addresses and Aadhar numbers of all those people who have multiple 
PAN numbers. Print all the PAN numbers for each such person. 
3. Print names, addresses and Aadhar numbers of all those people who have multiple 
bank accounts registered under multiple (more than 1) PAN numbers. (Note that 
registration of multiple bank accounts with the same PAN number is allowed.) 
4. Print details (Aaadhar, PAN, all bank-account details) of a person who has availed 
LPG subsidy. 
5. Take amount X as input. Print names, addresses and Aadhar numbers of all those 
people who have their total savings (in all bank accounts of theirs) being greater than 
amount X and they have also availed LPG subsidy (YES). This may include people 
having one or more PAN numbers. 
6. Print inconsistent data, i.e. names, addresses and Aadhar numbers of all those people 
who have different names mentioned in either of their Aadhar number, PAN number, 
bank account or LPG connection. 
7. Given two different bank account databases, merge these two databases into a single 
database. 
8. Given two Aadhar numbers A1 and A2, print details of all Aadhar numbers in the 
range of A1 and A2.
