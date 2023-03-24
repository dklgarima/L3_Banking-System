/* Creating a banking system */

#include<iostream>
#include<fstream>
#include<string.h>
#include<conio.h>

using namespace std;

class Account{ //base class
	
	protected:
		
		int account_No,id;     //declaring attributes
	    double balance;
	    double Ibalance;
	    double serviceCharges;   
	    float annual_interest_rate;
	    int Ndepo;
	    int Nwithdrawal;
	
    public:
    	
    	Account(){}
    	
    	Account(double Ibal,float r,char *n){   // constructors
    		
    		Ibalance = Ibal;
    		annual_interest_rate= 4;
		}
		
		int getPersonID(){   //declaring methods
			return id;
		}
		
    	virtual double makeDeposit(double b, double amount) {      //depositing certain amount to the balance
            
            Account A;
			b = b + amount;
            Ndepo++;
            A.setBalance(b);
            return b;
        }
		
        virtual double makeWithdrawal(double amount,double b){      //withdrawing amount from the balance
        	
        	Account A;
            b = b - amount;
            Nwithdrawal++;
            A.setBalance(b);
            return b; 
				
		}
		
		void setBalance(double b)     //setter
		{
			balance=b;
		}
		
		double getBalance()         //getter
		{
			return balance;
		}
		
        virtual void calcInt(double b){     //calculating the monthly interest
        	
        	double monthlyInterestRate = annual_interest_rate / 12;
            double monthlyInterest = b * monthlyInterestRate;
            b += monthlyInterest;
            
		}
		
        virtual void monthlyProc(double b){  
        	
        	b -= serviceCharges;
        	calcInt(b);
            Ndepo = 0;
            Nwithdrawal = 0;
            serviceCharges = 0.0;
            
		}
		
        void Create_Account(){   //To ask details from the users
        
        	cout<<endl;
        	fflush(stdin);
        	cout<<"Enter the account number :";
	        cin>>account_No;
	        cout<<endl;
	        cout<<"Enter the id allocated :";
	        cin>>id;
	        cout<<endl;
	        cout<<"Enter the initial balance : ";
	        cin>>Ibalance;
	        Ndepo = 0;
            Nwithdrawal = 0;
            serviceCharges = 0.0;
            balance=Ibalance;
	        cout<<endl;
		}
		
		void display_details(){   //To display all the Information
			
			cout<<endl;
			cout<<"____________________________________________"<<endl;
        	cout<<"Account No. = "<<account_No<<endl;
        	cout<<"Unique identity number = "<<id<<endl;
        	cout<<"Service charge = "<<serviceCharges<<endl;
        	cout<<"Initial balance = $ "<<Ibalance<<endl;
        	cout<<"Final balance = $ "<<balance<<endl;
			cout<<"_____________________________________________"<<endl;	
		}
        
};



class Saving_Account : public Account{ //derived class from base class Account
	
	protected:
		bool check;  //attributes
		
	public:
		
		//Savings() : Account(){}

		double makeWithdrawal(double amount,double bl){  //methods
			
            if (bl >= 25.00 ) {
            	cout<<endl;
			    Account::makeWithdrawal(amount,bl);
			    //check = false;
 
		    } 
		    else if (bl<25.00){
		    	cout<<"Your account is inactive."<<endl;
		    	cout<<"Current balance = "<<bl<<endl;
		    	exit(0);
		    	//check = false;
			} 	
        } 
		
        double makeDeposit(double amount, double money) {
               if (money < 25){
            	check = false;
            	cout<<"Your account is still inactive.Please deposit more amount."<<endl;
			} 
            else if (money + amount > 25) {
            	check = true;
                Account::makeDeposit(amount,money);
			}
            
        }
 
		void monthlyProc(double b){
				if (Nwithdrawal > 4){
				serviceCharges += 1 * (Nwithdrawal - 4);
				
            if (b - serviceCharges  < 25.00) {
                check = false;
                cout<<endl;
                cout << "Your account has been deactivated due to balance less than $25."<<endl;
            }
            else{
            	serviceCharges= 0;
			}
            
            Account::monthlyProc(b);
            Account::display_details();
		}
		}
	

};

class Checking_Account : public Account { //creating a derived class from base class
 
public:
 
    //Checking_Account() : Account() {}

    double makeWithdrawal(double amount,double money){
    	Account A;
    	
		if (money<amount) {
 
            cout << "Please donot enter the amount more than your current balance."; 
			serviceCharges += 15.00;  //money won't be withdrawn but the service charge will be deducted.
			
			if (serviceCharges>money){
			money-=serviceCharges;
			cout<<"Amount pending to be paid to the bank is $"<<money<<endl;
			}
		}
		
        else if (amount < 0) {  // doesn't accept the negative number 
 
            cout << "Error! Please enter positive number ";
        }
 
        else {
            Account::makeWithdrawal(amount,money);
        }
        
	

	}
	
	void monthlyProc(double b){ //calculating the service charge
        serviceCharges += (5.00 + (Nwithdrawal * 0.10));
        Account::monthlyProc(b);
        Account::display_details();
	}
	
};

void menu()  // menu part 
{
	cout<<"MAIN MENU"<<endl;
	cout<<"_____________________________________________"<<endl;
	cout<<endl;
	cout<<"1. Creating New Bank Account"<<endl;
	cout<<"2. Deposite Money"<<endl;
	cout<<"3. Withdraw Money"<<endl;
	cout<<"4. Display Banking Information"<<endl;
	cout<<"5. Exit"<<endl;
	cout<<"_____________________________________________"<<endl;
	
}

void createAccount()  //function to create account
{
	Account A;
	fstream file;
	char ch;
	file.open("Bank Information.txt",ios::binary | ios::app) ; //opening file
	if(!file)
	{
		cout<<"File can't be created"<<endl;   //in case file cant be opened.
		exit(0);
	}
	else{
		A.Create_Account();
		file.write((char*)&A,sizeof(A));
		cout<<endl;
	}
	file.close();  //closing the file 
}

void Deposite_Amt()  //function to deposite money
{
	Account A; //creating base class object
	Saving_Account S;  //creating derived class object
	fstream file;
	file.open("Bank Information.txt",ios::binary | ios::in | ios::out);
	if(!file)
	{
		cout<<"Can't find file'"<<endl;
		exit(0); //to exit out 
	}
	else
	{
		int id;
		cout<<"Enter Person's ID number: "; //id to verify the person
		cin>>id;
		file.seekp(ios::beg);
		file.read((char*)&A,sizeof(A));
		while(!file.eof()){
			if(A.getPersonID()==id)
			{
				double amt;
				double money,new_money;
				cout<<"Enter the amount to be deposited = ";  //asking the money to be deposited
				cin>>amt;
				money=A.getBalance();
				new_money=S.makeDeposit(amt,money);   //calls deposit method from saving account 
				A.setBalance(new_money);
				file.seekg(file.tellg()-sizeof(A));
				file.write((char*)&A,sizeof(A)); 
				break; 
			}
			file.read((char*)&A,sizeof(A));
		}
		file.close();
	}
}

void Withdraw_Amt() //Function to withdraw money
{
	Account A;
	Checking_Account C;
	fstream file;
	file.open("Bank Information.txt",ios::binary | ios::in | ios::out);
	if(!file)
	{
		cout<<"Can't find file'"<<endl;
		exit(0);
	}
	else
	{
		double money,new_money;
		int id;
		cout<<"Enter Person's ID number: ";   //asking the id for verification 
		cin>>id;
		file.seekp(ios::beg);
		file.read((char*)&A,sizeof(A)); 
		while(!file.eof()){
			if(A.getPersonID()==id)
			{
				double W_amt;
				cout<<"Enter the amount to be withdrawn = ";   //asks the amount to be withdrawn
				cin>>W_amt;
				money=A.getBalance();
				new_money=C.makeWithdrawal(W_amt,money);      //calling the withdrawal method from the checking class
				A.setBalance(new_money);
				file.seekg(file.tellg()-sizeof(A));
				file.write((char*)&A,sizeof(A)); 
				break;
			}
			file.read((char*)&A,sizeof(A));
		}
		file.close();
	
	}
}

void displayInfo()  //Function to display the bank information
{
	Account A;
	fstream file;
	file.open("Bank Information.txt",ios::binary | ios::in );
	if(!file){
		cout<<"File can't be found"<<endl;
		exit(0);
	}
	else
	{
		file.read((char*)&A,sizeof(A));
		while(!file.eof())
		{
			A.display_details();      //calling to display information from the base class
			file.read((char*)&A,sizeof(A));
		}
		file.read((char*)&A,sizeof(A));
		file.close();
	}
	file.close();
}

int main()  //main function
{
	Account A;
	int choice;
	while(true)
	{
		menu();  //calling the menu function 
		
		cout<<"Enter the any choice : ";  //asking the choice to the user
		cin>>choice;
		switch(choice)
		{
			case 1 :
				createAccount(); //calling to create account
				break;
				
			case 2:
				Deposite_Amt();  //calling to deposite amount of money
				break;
			
			case 3:
				Withdraw_Amt();  //calling to withdraw a certain amount
				break;
				
			case 4:
				displayInfo(); //displaying the information
				break;
				
			case 5:
				exit(0);
				
			default:
				cout<<"____________________________________________"<<endl;
				cout<<"Wrong Choice! Please choose a correct choice. "<<endl;
				break;
			
		}
	}
}

