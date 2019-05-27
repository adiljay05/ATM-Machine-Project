#include<iostream>
#include<fstream>
#include<string>
#include<conio.h>
#include<cstdio>
#include<windows.h>
#include<ctime>
using namespace std;
int index,index2;
string crd,pinNo,Blnce,trHistory;
	void success(string number,string t1[3])
	{
		ofstream out("successful logins.txt",ios::app);
		out<<t1[0]<<'\t'<<number<<'\n';
		out<<'\n';
		out.close();
	}
//-------------------------------------------------------------------------------
	void deleted_record(int x[3],string t1[3])
	{
		ofstream out("unsuccessful logins.txt",ios::app);
		for(int i=0;i<3;i++)
		{
			out<<t1[i]<<'\t'<<x[i]<<'\t';
			out<<crd<<'\t'<<pinNo<<'\t'<<Blnce<<"\t\t"<<trHistory<<'\n';
		}
		out<<"\n\n";
		out.close();
		ShellExecute(NULL, "open","file.exe", NULL, NULL, SW_SHOWDEFAULT);
	}
//--------------------------------------------------------------------------------
	void delete_temp_files()
	{
		remove("history.bin");
		rename("temporary.bin", "history.bin");
		remove("credit.bin");
		rename("temp2.bin","credit.bin");
	}
//--------------------------------------------------------------------------------
	int transaction_history(int index)
	{
		string balance;
		ifstream in("history.bin",ios::binary);
		for (int i = 1; i <= index; i++)
        getline(in, balance);
		getline(in, balance);
		cout<<balance<<' ';
		cout<<'\n';
		in.close();
	}
//---------------------------------------------------------------------------------
	int withdraw_amount(int index)
	{
		int *temp;            
		temp=new int[10];     
		int *final_array;
		final_array=new int[10];
		int withdraw,remaining,balance;
		int historic_amount;
		ifstream in("credit.bin",ios::binary);
		ofstream out1("temp2.bin",ios::binary);
		for (int i = 1; i <= index; i++){
		in>>balance;
		out1<<balance;
		if(!in.eof())
		out1<<'\n';
		}
		in>>balance;
		cout<<"Enter amount to withdraw\n";
		cin>>withdraw;
		if(withdraw>balance || withdraw>25000)
		{
			if(withdraw>balance)
			{
				cout<<"Transaction failed\nInsufficient account balance\n";
				return 0;
			}
			else if (withdraw>25000)
			{
				cout<<"Transaction failed\nBeyond the withdrawl limit\n";
				return 0;
			}
			
		}
		else if(balance>withdraw){
		remaining=balance-withdraw;
		out1<<remaining;
		if(!in.eof())
		out1<<'\n';
        while(!in.eof())               
			{
				in>>balance;
				out1<<balance;
				if(!in.eof())
				out1<<'\n';
			}
        in.close();
		ifstream in1("history.bin",ios::binary);
		ofstream out("temporary.bin",ios::binary);
			for (int i = 1; i <= index; i++)
			{
				for(int j=0;j<10;j++)
				{
        			in1>>historic_amount;
        			out<<historic_amount<<' ';
        		}
        		if(!in1.eof())
				out<<'\n';
        	}
			for(int i=0;i<10;i++)
			{
				in1>>historic_amount;    
				temp[i]=historic_amount;
			}
			final_array[0]=withdraw;
			for(int i=1;i<10;i++)
			{
				final_array[i]=temp[i-1];
			}
			for(int i=0;i<10;i++)
			{
				out<<final_array[i]<<' ';
			}
			if(!in1.eof())
			out<<'\n';
			
			while(!in1.eof())
			{
				for(int j=0;j<10;j++)
				{
        			in1>>historic_amount;
        			
        			out<<historic_amount<<' ';
        		}
        		if(!in1.eof())	
				out<<'\n';
			}
			
		
		in1.close();
		out.close();
		out1.close();
		cout<<"Transaction was successful\n";
		delete_temp_files();
		}
	}
//---------------------------------------------------------------------------------
	int current_balance(int index)
	{
		string balance;
		ifstream in("credit.bin",ios::binary);
		for (int i = 1; i <= index; i++)
        getline(in, balance);
		in>>balance;
		cout<<"Your Current account balance is Rs. : "<<balance<<'\n';
		in.close();
	}
//---------------------------------------------------------------------------------
	void menu()
	{
		cout<<"Select an option\n1. Check current account balance\n2. Withdraw amount\n3. Transaction history\n4. Enter 4 to terminate\n";
	}


//---------------------------------------------------------------------------------
	int delete_record(string number,int index)
	{
		ifstream in("cards.bin",ios::binary);
		ifstream in1("pins.bin",ios::binary);
		ifstream in2("credit.bin",ios::binary);
		ifstream in3("history.bin",ios::binary);
		ofstream out("card_temp.bin",ios::binary);
		ofstream out1("pin_temp.bin",ios::binary);
		ofstream out2("credit_temp.bin",ios::binary);
		ofstream out3("history_temp.bin",ios::binary);
		string card,pin_number,balance,t_history;
		//---for card number
		for (int i = 1; i <= index; i++)
		{
        	getline(in, card);
        	out<<card<<'\n';
    	}
		getline(in, card);
		crd=card;
		while(!in.eof())
		{
			getline(in, card);
			out<<card<<'\n';
		}
		
		//---for pin number
		for (int i = 1; i <= index; i++)
		{
        	getline(in1, pin_number);
        	out1<<pin_number<<'\n';
    	}
		getline(in1, pin_number);
		pinNo=pin_number;
		while(!in1.eof())
		{
			getline(in1, pin_number);
			out1<<pin_number<<'\n';
		}
		//---for credit
		for (int i = 1; i <= index; i++)
		{
        	getline(in2, balance);
        	out2<<balance<<'\n';
    	}
		getline(in2, balance);
		Blnce=balance;
		while(!in2.eof())
		{
			getline(in2, balance);
			out2<<balance<<'\n';
		}
		//---for transaction history
		for (int i = 1; i <= index; i++)
		{
				getline(in3, t_history);
				out3<<t_history<<'\n';
    	}
		getline(in3, t_history);
		trHistory=t_history;
		while(!in3.eof())
		{
				getline(in3, t_history);
				out3<<t_history<<'\n';
		}
		in.close();
		in1.close();
		in2.close();
		in3.close();
		out.close();
		out1.close();
		out2.close();
		out3.close();
		string *temp_data;
		ifstream in_card("card_temp.bin",ios::binary);
		int index1=0;
		string input;
		while(!in_card.eof())
		{
			getline(in_card,input);
			index1++;
		}
		temp_data=new string[index1];
		in_card.close();
		ifstream in_c("card_temp.bin",ios::binary);
		for(int i=0;i<index1;i++)
		{
			in_c>>temp_data[i];
		}
		in_card.close();  
		ofstream write_card("cards.bin",ios::binary);
		for(int i=0;i<index1;i++)
		{
			write_card<<temp_data[i]<<'\n';
		}
		write_card.close();
		delete []temp_data;
		index1=0;
		ifstream in_pin("pin_temp.bin",ios::binary);
		while(!in_pin.eof())
		{
			getline(in_pin,input);
			index1++;
		}
		temp_data=new string[index1];
		cout<<index1<<'\n';
		in_card.close(); 
		ifstream in_pin1("pin_temp.bin",ios::binary);
		for(int i=0;i<index1;i++)
		{
			in_pin1>>temp_data[i];
		}
		in_pin.close();
		ofstream write_pin("pins.bin",ios::binary);
		for(int i=0;i<index1;i++)
		{
			write_pin<<temp_data[i]<<'\n';
		}
		write_pin.close();
		delete []temp_data;
	}
//---------------------------------------------------------------------------------
	int pin_validation(string card_no,int index_value)
	{
		int pin,pin_file,pin_index=-1;
		int valid=0;          
		string entering_time[3];
		time_t rawtime;
  		struct tm * timeinfo;
  		char buffer[80];
  		int tries=2;
		int wrongPin[3];
		ifstream in("pins.bin",ios::binary);
		cout<<"Please enter your pin\n";
		cin>>pin;
		wrongPin[0]=pin;  
	 	time (&rawtime);
 		timeinfo = localtime(&rawtime);
  			strftime(buffer,sizeof(buffer),"%d-%m-%Y %I:%M:%S",timeinfo);
  			string str(buffer);
  			entering_time[0]=str;
  			cout<<"current time : "<<entering_time[0]<<'\n';
		while(!in.eof())
		{
			in>>pin_file;
			pin_index++;
			if(pin_index==index_value)
			{
				if(pin_file==pin)
				{
					success(card_no,entering_time);
					menu();
				}
				else 
				{
					for(int i=1;i<3;i++)
					{
						cout<<"you have "<<tries<<" more tries left\n";
						cout<<"Please enter your pin\n";
						cin>>pin;
						time (&rawtime);
 						timeinfo = localtime(&rawtime);
  						strftime(buffer,sizeof(buffer),"%d-%m-%Y %I:%M:%S",timeinfo);
  						string str(buffer);
  						entering_time[i]=str;
  						cout<<"current time : "<<entering_time[i]<<'\n';
						tries--;
						wrongPin[i]=pin;
							if(pin_file==pin)
							{
								success(card_no,entering_time);
								menu();
								break;
							}
						if(tries==0)
						{
							cout<<"your card has been blocked contact your nearest bank branch\nPress 4 draw your card out then try again\n";
							delete_record(card_no,pin_index);
							deleted_record(wrongPin,entering_time);
							break;
						}
					}
				}
				break;
			}	
		}
		in.close();
	}
	//-----------------------------------------------------------------------------
	int card_validation(string number)
	{
		string atm_no;
		bool checker;
		int index=-1;
		ifstream in("cards.bin",ios::binary);
		while(!in.eof())
		{
			in>>atm_no;
			index++;
			if(atm_no==number)
			{
				checker=true;
				index2=index;
				break;
			}
			else if(atm_no!=number)
			{
				checker=false;
			}
		}
		if(checker==false)
		{
			cout<<"Invalid card number\nPress 4 draw your card out then try again\n";
		}
 		else if (checker==true)
 		{
 			cout<<"your card is valid\n";
 			pin_validation(number,index2);
		}
		in.close();
		return index2;	
	}
int main(void)
{
	int index;
	int options;
	system("CLS");
	string card_no;
	cout<<"Please input your card number\n";
	cin>>card_no;
	card_validation(card_no);
	while(options!=4)
	{
		cin>>options;
		if(options==1)
		current_balance(index2);
		else if(options==2)
		withdraw_amount(index2);
		else if(options==3)
		transaction_history(index2);
		else if(options==4)
		{
			system("CLS");
			cout<<"Thank you for using our services\n";
			break;
		}
		else 
		cout<<"Sorry you have selected a wrong option\n\n\n";
		menu();
	}
}

