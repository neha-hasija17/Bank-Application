#include <bits/stdc++.h>
#include <thread>
using namespace std;
int cust_id=200000;
int account_no=100000;

 
class Account{
	protected:
		double balance;
		int acc_type;
		int acc_no;

	public:
		friend void start_thread();
		static double rate;
		static double low_bal;
		friend class Customer;
		Account(){
			acc_no=account_no;
			account_no++;
		}
		virtual void createAccount(){
			cout<<"Enter the type of account to open : "<<endl;
			cout<<"1. Saving\n2. Current"<<endl;
			cin>>acc_type;
			cout<<"Enter amount to add while opening: "<<endl;
			cin>>balance;
		}
		virtual double checkBalance(){};
		virtual void deposit(){};
		virtual void withdraw(){};
		void deleteAccount(const Account &obj){
			delete this;
		}

};
double Account::rate=2;
double Account::low_bal=500;
void SMS(int ph,string name,int type,double bal){
	string s;
	if(type==1) s="Savings";
	else if(type==2) s="Current";
	if(bal<Account::low_bal){
		cout<<"Dear "<<name<<" your balance in "<<s<<" account is less than minimum balance!!"<<endl;
		cout<<"SMS sent to customer on  "<<ph<<endl;
	}
}
void mail(string email,string name,int type,double bal){

	string s;
	if(type==1) s="Savings";
	else if(type==2) s="Current";
	if(bal<Account::low_bal){
		cout<<"Dear "<<name<<" your balance in "<<s<<" account is less than minimum balance!!"<<endl;
		cout<<"Email sent to customer on "<<email<<endl;
	}
}
class savings: public Account{
	public:
		double checkBalance(){
			//cout<<"derived"<<endl;
			return balance;
		}	
		friend void start_thread();
		void createAccount(){
			cout<<"type 1"<<endl;
			cin>>acc_type;
			cout<<"enter opening balance"<<endl;
			cin>>balance;
		}
		void deposit(){
			double D,interest;
			cout<<"Enter amount to deposit: "<<endl;
			cin>>D;
			balance+=D;
			interest=(balance*(Account::rate))/100;
			balance+=interest;
			cout<<"Balance after deposition: "<<balance<<endl;
		}
		void withdraw(){
			double W;
			cout<<"Enter amount to withdraw: "<<endl;
			cin>>W;
			if(W>balance) {
				cout<<"not enough balance!"<<endl;
				return;
			}
			balance-=W;
			if(balance<Account::low_bal){
				cout<<"balance is less than minimum balance!"<<endl;
			}
			cout<<"balance after withdrawal is: "<<balance<<endl;
		}
};
class current: public Account{
	public:
		double checkBalance(){
			//cout<<"derived"<<endl;
			return balance;
		}
		friend void start_thread();
		void createAccount(){
			cout<<"type 2 for current account"<<endl;
			cin>>acc_type;
			cout<<"enter opening balance"<<endl;
			cin>>balance;
		}
		void deposit(){
			double D;
			cout<<"Enter amount to deposit: "<<endl;
			cin>>D;
			balance+=D;

			cout<<"Balance after deposition: "<<balance<<endl;
		}
		void withdraw(){
			double W,penalty;
			cout<<"Enter amount to withdraw: "<<endl;
			cin>>W;
			if(W>balance) {
				cout<<"not enough balance!"<<endl;
				return;
			}
			balance-=W;
			if(balance<Account::low_bal){
				penalty=(Account::low_bal-balance)/100;
				balance-=penalty;
				cout<<"balance is less than minimum balance!"<<endl;
			}
			cout<<"balance after withdrawal is: "<<balance<<endl;
		}
};
class Customer{
	int c_id;
	string c_name;
	string gender;
	string Aadhar;
	Account *a[2];
	int count;
	int phone;
	string email;
	public:
	int Al;
	bool enable;
	Customer(){
		count=0;
	}
	void fn();
	friend void start_thread();
	void createCustomer();
	void display();
	void update();
	void operator()();
	void AddAccount();
	void CheckBalance();
	void Withdrawal();
	void Deposition();
	void DelAccount();
};

static map<int,Customer> cust_map;
class Bank {
	static Bank *instance;
	string bank_name;
	string bank_branch;
	int IFSC_code;
	string Password;
	Bank() {
		bank_name="";
		bank_branch="";
		IFSC_code=0;
		Password="";
	}
	public:
	static Bank *getInstance() {
		if (!instance)
			instance = new Bank;
		return instance;
	}
	void SetData(){
		cout<<"Enter bank details: "<<endl;
		cout<<"Bank Name: ";
		cin>>bank_name;
		cout<<"Bank Branch: ";
		cin>>bank_branch;
		cout<<"IFSC Code: ";
		cin>>IFSC_code;
		cout<<"Set Password: ";
		cin>>Password;
		cout<<"Bank service provides following accounts: \nSavings Account\nCurrent Account\n\nPlease provide details for each of them"<<endl;
		cout<<"enter details for savings account: "<<endl;
		cout<<"enter rate of interest: ";
		cin>>Account::rate;
		cout<<"enter details for current account: "<<endl;
		cout<<"enter low balance amount: ";
		cin>>Account::low_bal;


	}
	void Display(){
		cout<<"Bank details are: "<<endl;
		cout<<"bank name is: "<<bank_name<<endl;
		cout<<"bank branch is: "<<bank_branch<<endl;
		cout<<"IFSC code is: "<<IFSC_code<<endl;
	}
	void Modify(){
		string pass;
		cout<<"Enter password: "<<endl;
		cin>>pass;
		if(pass!=Password){
			cout<<"Incorrect password"<<endl;
		}
		else{
			string name;
			cout<<"Enter new name: "<<endl;
			cin>>name;
			bank_name=name;
			Display();
		}
	}
};
void Customer::createCustomer(){
	cout<<"Enter customer details: "<<endl;
	cout<<"Customer ID is: "<<cust_id<<endl;
	cout<<"Enter Name: "<<endl;
	cin>>c_name;
	cout<<"Enter Gender: "<<endl;
	cin>>gender;
	cout<<"enter Aadhar Number: "<<endl;
	cin>>Aadhar;
	cout<<"Do you want to create account? (y/n)"<<endl;
	char q;
	cin>>q;
	if(q=='n') return;
	cout<<"which type of account?\n1. Savings\n2.current"<<endl;
	int e;
	cin>>e;
	if(e==1){
		a[count]=new savings;
		a[count]->createAccount();	
	}
	else
	{
		a[count]=new current;
		a[count]->createAccount();
	}
	count++;
	cout<<"Enter phone Number: "<<endl;
	cin>>phone;
	cout<<"Enter email address: "<<endl;	
	cin>>email;
	cout<<"do you want to register with SMS alert/email alert services? (y/n)"<<endl;
	char r;
	cin>>r;

	if(r=='y'){
		cout<<"choose one frome below: \n1. SMS Alert\n2. Email Alert\n3. both\n";
		cin>>Al;
		enable=true;
	}
	else enable=false;
	cust_map[cust_id++]=*this;
}
void Customer::display(){
	if(cust_map.size()==0){
		cout<<"No customers yet!"<<endl; 
		return;
	}
	map<int,Customer>::iterator i;
	for(i=cust_map.begin();i!=cust_map.end();i++){
		cout<<"Customer details are: "<<endl;
		cout<<"Customer ID is: "<<i->first<<endl;
		cout<<"Customer Name is: "<<i->second.c_name<<endl;
		cout<<"Customer Gender: "<<i->second.gender<<endl;
		cout<<"Customer Aadhar Number: "<<i->second.Aadhar<<endl;
		cout<<"Customer Accounts: "<<endl;
		if(i->second.count==0) {
			cout<<"no account yet"<<endl; 
			return;
		}
		else if(i->second.count==1) {
			if(i->second.a[0]->acc_type==1)
				cout<<"Savings Account "<<"Account number: "<<i->second.a[0]->acc_no<<endl;
			else 
				cout<<"Current Account "<<"Account number: "<<i->second.a[0]->acc_no<<endl;
			cout<<"account balance: "<<i->second.a[0]->balance<<endl;
		}
		else if(i->second.count==2)
			cout<<"both savings and current"<<endl;
	}
}    
void Customer::update(){
	if(cust_map.size()==0){cout<<"No customers yet!"<<endl; return;}
	int id,choice;
	cout<<"Enter customer ID to update: "<<endl;
	cin>>id;
	if(cust_map.find(id)==cust_map.end()) {cout<<"No customer with this ID"<<endl; return;}
	cout<<"choose the details to update: "<<endl;
	cout<<"1. Update Customer Name"<<endl;
	cout<<"2. Update Customer Aadhar"<<endl;
	cin>>choice;
	if(choice==1){
		string name;
		cout<<"Enter new name: "<<endl;
		cin>>name;
		cust_map[id].c_name=name;
	}
	else {
		int adhr;
		cout<<"Enter new AADHAR: "<<endl;
		cin>>adhr;
		cust_map[id].Aadhar=adhr;
	}
}

void Customer::AddAccount(){
	cout<<"Enter customer ID: "<<endl;
	int id,ch;
	cin>>id;
	if(cust_map.find(id)==cust_map.end()) {
		cout<<"Invalid ID."<<endl;
		return;
	}
	cout<<"choose one from below:\n1. savings\n2. current\n";
	int f;
	cin>>f;
	if(f==1){

		cust_map[id].a[cust_map[id].count]=new savings;
		cust_map[id].a[cust_map[id].count]->createAccount();
		cust_map[id].count++;
	}
	else if(f==2){
		cust_map[id].a[cust_map[id].count]=new current;
		cust_map[id].a[cust_map[id].count]->createAccount();
		cust_map[id].count++;
	}
}
void Customer::DelAccount(){
	cout<<"Enter customer ID: "<<endl;
	int id,ch;
	cin>>id;
	if(cust_map.find(id)==cust_map.end()) {
		cout<<"Invalid ID."<<endl;
		return;
	}
	if(cust_map[id].count==0) {cout<<"No account to delete"<<endl;
		return;}
		cout<<"Choose the account to delete: "<<endl;
		cout<<"1. Savings\n2.Current"<<endl;
		cin>>ch;
		cust_map[id].a[ch-1]->deleteAccount(*(cust_map[id].a[ch-1]));

}
void Customer::CheckBalance(){
	cout<<"Enter customer ID: "<<endl;
	int id,ch;
	cin>>id;
	if(cust_map.find(id)==cust_map.end()) {
		cout<<"Invalid ID."<<endl;
		return;
	}
	if(cust_map[id].count==0) {cout<<"No account"<<endl;
		return;}
		cout<<"Choose the account: "<<endl;
		cout<<"1. Savings\n2.Current"<<endl;
		cin>>ch;
		if(ch==1){
			if(cust_map[id].a[0]->acc_type==1)
				cout<<"balance is "<<cust_map[id].a[0]->checkBalance()<<endl;
			else if(cust_map[id].a[1]->acc_type==1)
				cout<<"balance is "<<cust_map[id].a[1]->checkBalance()<<endl;
			else cout<<"No saving account."<<endl;
		}
		else if(ch==2){
			if(cust_map[id].a[0]->acc_type==2)
				cout<<"balance is "<<cust_map[id].a[0]->checkBalance()<<endl;
			else if(cust_map[id].a[1]->acc_type==2)
				cout<<"balance is "<<cust_map[id].a[1]->checkBalance()<<endl;
			else cout<<"No current account"<<endl;
		}
}
void Customer::Deposition(){
	cout<<"Enter customer ID: "<<endl;
	int id,ch;
	cin>>id;
	if(cust_map.find(id)==cust_map.end()) {
		cout<<"Invalid ID."<<endl;
		return;
	}
	if(cust_map[id].count==0) {cout<<"No account"<<endl;
		return;}
		cout<<"Choose the account: "<<endl;
		cout<<"1. Savings\n2.Current"<<endl;
		cin>>ch;
		if(ch==1){
			if(cust_map[id].a[0]->acc_type==1){
				cust_map[id].a[0]->deposit();
			}
			else if(cust_map[id].a[1]->acc_type==1){
				cust_map[id].a[1]->deposit();}
			else cout<<"No saving account"<<endl;
		}
		else if(ch==2){
			if(cust_map[id].a[0]->acc_type==2){
				cust_map[id].a[0]->deposit();}
			else if(cust_map[id].a[1]->acc_type==2)
				{
				cust_map[id].a[1]->deposit();}
			else cout<<"No current account"<<endl;
		}
}
void Customer::Withdrawal(){
	cout<<"Enter customer ID: "<<endl;
	int id,ch;
	cin>>id;
	if(cust_map.find(id)==cust_map.end()) {
		cout<<"Invalid ID."<<endl;
		return;
	}
	if(cust_map[id].count==0) {cout<<"No account"<<endl;
		return;}
		cout<<"Choose the account: "<<endl;
		cout<<"1. Savings\n2.Current"<<endl;
		cin>>ch;
		if(ch==1){
			if(cust_map[id].a[0]->acc_type==1)
				cust_map[id].a[0]->withdraw();
			else if(cust_map[id].a[1]->acc_type==1)
				cust_map[id].a[1]->withdraw();
			else cout<<"No saving account"<<endl;
		}
		else if(ch==2){
			if(cust_map[id].a[0]->acc_type==2)
				cust_map[id].a[0]->withdraw();
			else if(cust_map[id].a[1]->acc_type==2)
				cust_map[id].a[1]->withdraw();
			else cout<<"No current account"<<endl;
		}
}

//void Customer::operator()(){
void start_thread(){
	map<int,Customer>::iterator it;
	while(1){
	for(it=cust_map.begin();it!=cust_map.end();it++){
		if(it->second.enable && it->second.count>0){
			if(it->second.count==1){
				if(it->second.Al==1)
					SMS(it->second.phone,it->second.c_name,it->second.a[0]->acc_type,it->second.a[0]->balance);
				else if(it->second.Al==2)	
					mail(it->second.email,it->second.c_name,it->second.a[0]->acc_type,it->second.a[0]->balance);
				else if(it->second.Al==3){
					SMS(it->second.phone,it->second.c_name,it->second.a[0]->acc_type,it->second.a[0]->balance);
					mail(it->second.email,it->second.c_name,it->second.a[0]->acc_type,it->second.a[0]->balance);
				}
			}		
			if(it->second.count==2){
				if(it->second.Al==1){
					SMS(it->second.phone,it->second.c_name,it->second.a[0]->acc_type,it->second.a[0]->balance);
					SMS(it->second.phone,it->second.c_name,it->second.a[1]->acc_type,it->second.a[1]->balance);
				}
				else if(it->second.Al==2){	
					mail(it->second.email,it->second.c_name,it->second.a[0]->acc_type,it->second.a[0]->balance);
					mail(it->second.email,it->second.c_name,it->second.a[1]->acc_type,it->second.a[1]->balance);
				}
				else if(it->second.Al==3){
					SMS(it->second.phone,it->second.c_name,it->second.a[0]->acc_type,it->second.a[0]->balance);
					mail(it->second.email,it->second.c_name,it->second.a[0]->acc_type,it->second.a[0]->balance);
					SMS(it->second.phone,it->second.c_name,it->second.a[1]->acc_type,it->second.a[1]->balance);
					mail(it->second.email,it->second.c_name,it->second.a[1]->acc_type,it->second.a[1]->balance);
				}
			}
		}
	}
	//sleep(30);
}
}
Bank *Bank::instance = 0;
int main(){
	Bank *b=b->getInstance();
	b->SetData();
	int c;
	thread th1(start_thread);
	while(1){
		cout<<"Choose any one from below: "<<endl;
		cout<<"1. Create customer account"<<endl;
		cout<<"2. View details of Customer"<<endl;
		cout<<"3. Update customer account"<<endl;
		cout<<"4. Delete account"<<endl;
		cout<<"5. Add Account"<<endl;
		cout<<"6. View bank details"<<endl;
		cout<<"7. Modify bank details"<<endl;
		cout<<"8. Deposit amount"<<endl;
		cout<<"9. Withdraw amount"<<endl;
		cout<<"10. Check Balance"<<endl;
		cin>>c;
		Customer cus;
		switch(c){
			case 1: 
				cus.createCustomer();
				break;
			case 2:  
				cus.display();
				break;
			case 3:
				cus.update();
				break;
			case 4:
				cus.DelAccount();
				break;
			case 5: 
				cus.AddAccount();
				break;
			case 6:
				b->Display();
				break;
			case 7:
				b->Modify();
				break;
			case 8:
				cus.Deposition();
				break;
			case 9:
				cus.Withdrawal();
				break;
			case 10:
				cus.CheckBalance();
				break;
		}
	}
	return 0;
}
