#include<iostream>
#include<fstream>
#include<string>
#include<string.h>
#include<cstdlib>
#include<conio.h>

using namespace std;

class Person
{
	protected:
		string name,address,gender,email,cnic;
		string illness,covid_sym,recent_illness;
		int last_donation;
	
	public:
		Person(string name,string address,string gender,string email,string illness,string recent_illness,string covid_sym,int last_donation,string cnic)
		{
			this->name=name;
			this->address=address;
			this->gender=gender;
			this->email=email;
			this->illness=illness;
			this->recent_illness=recent_illness;
			this->covid_sym=covid_sym;
			this->last_donation=last_donation;
			this->cnic=cnic;
		}
		
		Person(string name,string address,string gender,string email,string cnic)
		{
			this->name=name;
			this->address=address;
			this->gender=gender;
			this->email=email;
			this->cnic=cnic;
		}

	
};

class Donor:public Person
{
	string blood_type;
	int bottles;
	
	public:
		Donor(string blood_type,string name,string address,string gender,string email,string illness,string recent_illness,string covid_sym,int last_donation,string cnic,int bottles):Person(name,address,gender,email,illness,recent_illness,covid_sym,last_donation,cnic)             
		{
			this->blood_type=blood_type;
			this->bottles=bottles;
		}
		
		void file_storing()
		{
			ofstream fout;
    		fout.open("donor.txt",ios::app);
    		
			if
			(!fout)
			{
				cout<<"\n\n\t\tfile of DONOR not found!!!";
				exit(0);	
			}
			
			fout.seekp(0,ios_base::end);
			
			fout<<cnic;
			fout<<"\n"<<blood_type;
			fout<<"\nbottles donated: "<<bottles;
			fout<<"\nname: "<<name;
			fout<<"\naddress: "<<address;
			fout<<"\ngender: "<<gender;
			fout<<"\nemail: "<<email;
			fout<<"\npermanent illness: "<<illness;
			fout<<"\ncovid 2019 symptoms: "<<covid_sym;
			fout<<"\nrecent illness in the past months: "<<recent_illness;
			fout<<"\nlast donation of blood (in days): "<<last_donation;
			fout<<"\n----------------\n";
			fout.close();
			cout<<"\n\n\t\tSUCCESSFULL....PLEASE RECIEVE YOUR JUICE FROM THE DESK!!! < THANK YOU >";
		}
		
};

class Recepient:public Person
{
	string needed_blood,given_blood;
	int bottles;
	
	public:
		Recepient(string needed_blood,int bottles,string name,string address,string gender,string email,string cnic):Person(name,address,gender,email,cnic)
		{
			this->needed_blood=needed_blood;
			this->bottles=bottles;
		}
		
		void file_storing()
		{
			ofstream fout;
    		fout.open("recepient.txt",ios::app);
    		
			if(!fout)
			{
				cout<<"\n\n\t\tfile of recepient not found!!!";
				exit(0);	
			}
			
			fout<<cnic;
			fout<<"\nblood recieved: "<<needed_blood;
			fout<<"\nbottles needed: "<<bottles;
			fout<<"\nname: "<<name;
			fout<<"\naddress: "<<address;
			fout<<"\ngender: "<<gender;
			fout<<"\nemail: "<<email;
			fout<<"\n----------------\n";
			fout.close();
		}
		
		int searching()
		{
			int count=0,count1=0;
			string second_line,first_line;
			
			ifstream fin;
			fin.open("donor.txt");
			cout<<"\n\n\t\tPerson having the requested blood group\n";
			
			while(!fin.eof())
			{
				getline(fin,first_line);
				getline(fin,second_line);
				
				if(second_line==needed_blood || count==1)
				{
					count=1;
					cout<<"\n"<<first_line<<"\n"<<second_line;
					
					if(second_line=="----------------")
					{
						cout<<"\n\n";
						break;
					}
				}		
			}	
			
			if(count==0)
			{
				cout<<"\n\n\t\tSORRY!!Requested Blood Group is not availaible..";
			}
			
			fin.close();
			return count;
		}
		
		void delete_thing()
		{
			string single_line,second_line;
			int count=0,count1=0;
			
			ifstream fin;
			fin.open("donor.txt");
			
			if(!fin)
		    {
		    	cout<<"\n\n\t\tfile of DONOR not found!!!";
				exit(0);	
			}
			
			ofstream fout;
			fout.open("new.txt");
			
			fin.seekg(0,ios_base::beg);
			
			while(!fin.eof())
			{
				getline(fin,single_line);
				getline(fin,second_line);
				
				if(count1==0)
				{
					if(second_line==needed_blood || count==1)
					{
						count=1;
						
						if(second_line=="----------------")
						{
							count=0;
							count1=1;
							continue;
						}
					}
					
					else
					{
						fout<<single_line<<"\n"<<second_line;
						fout<<"\n";
					}	
				}
				
				else
				{
					fout<<single_line<<"\n"<<second_line;
					fout<<"\n";
				}		
			}
			
			fin.close();
			fout.close();
			
			remove("donor.txt");
		
			if(rename("new.txt","donor.txt")!=0)
				cout<<"\n\n\t\tfile of donor couldn't be renamed..";
			
		}
		
		void accepting_blood()
		{
			string choice;
			
			cout<<"\n\nEnter < YES > OR < yes > if you want the blood\n";
        	cin>>choice;
        	
        	if(choice=="yes" || choice=="YES")
	        {
	        	Recepient::delete_thing();
	        	Recepient::file_storing();
	        	cout<<"	\n\n\t\tPlease wait for a few minutes until your turn\n\n\t\t\tTHANKYOU!!!";
	        }
	        
	        else
	        {
	        	cout<<"\n\n\t\tNO PROBLEM!!!";
			}
		}
		
		void search_donor()
		{
			int count,count1;
			string choice;
			count=Recepient::searching();
			
			if(count==1)
			{
				Recepient::accepting_blood();
			}
			
			else
			{
				int choice1,choice2,choice3,choice4,choice5,choice6,choice7,choice8;
				
				cout<<"\n\nEnter < YES > OR < yes > if you want the blood from other donors\n";
	        	cin>>choice;
	        	
	        	if(choice=="yes" || choice=="YES")
		        {
		        	if(needed_blood=="ab+" || needed_blood=="AB+")
	            	{
		                cout<<"\n\t\tyou can recieve from all blood groups..";
		
		                cout<<"\n\n\tEnter choice.\n\t1.from A+\n\t2.from A-\n\t3.from B+\n\t4.from B-\n\t5.from AB-\n\t6.from O+\n\t7.from O-\n\n";
		                cin>>choice1;
		
		                switch(choice1)
		                {
		                	case 1:
		                	needed_blood="A+";
							count1=Recepient::searching();	
							
							if(count1==1)
							{
								Recepient::accepting_blood();
								return;
							}
							
							if(count1==0)
							{
								return;
							}
							
		                	break;	
		                	
		                	case 2:
		                	needed_blood="A-";
							count1=Recepient::searching();	
							
							if(count1==1)
							{
								Recepient::accepting_blood();
								return;
							}
							
							if(count1==0)
							{
								return;
							}
							
		                	break;	
		                	
		                	case 3:
		                	needed_blood="B+";
							count1=Recepient::searching();	
							
							if(count1==1)
							{
								Recepient::accepting_blood();
								return;
							}
							
							if(count1==0)
							{
								return;
							}
								
		                	break;
		                	
		                	case 4:
		                	needed_blood="B-";
							count1=Recepient::searching();	
							
							if(count1==1)
							{
								Recepient::accepting_blood();
								return;
							}
							
							if(count1==0)
							{
								return;
							}	
		                	break;
		                	
		                	case 5:
		                	needed_blood="AB-";
							count1=Recepient::searching();	
							
							if(count1==1)
							{
								Recepient::accepting_blood();
								return;
							}
							
							if(count1==0)
							{
								return;
							}
								
		                	break;
		                	
		                	case 6:
		                	needed_blood="O+";
							count1=Recepient::searching();	
							
							if(count1==1)
							{
								Recepient::accepting_blood();
								return;
							}
							
							if(count1==0)
							{
								return;
							}	
		                	break;
		                	
		                	case 7:
		                	needed_blood="O-";
							count1=Recepient::searching();	
							
							if(count1==1)
							{
								Recepient::accepting_blood();
								return;
							}
							
							if(count1==0)
							{
								return;
							}	
		                	break;
		                	
		                	default:
		                	cout<<"\n\n\t\tPlease select from the following choices..";
		                	break;	
						}
		            }
		            
		            if(needed_blood=="ab-" || needed_blood=="AB-")
	            	{
	            		cout<<"\n\n\t\tyou can recieve from A-, B-, O ...";
	
		                cout<<"\n\n\tEnter choice.\n\t1.from A-\n\t2.from B-\n\t3.from O-\n\n";
		                cin>>choice2;
		                
		                switch(choice2)
		                {
		                	case 1:
		                	needed_blood="A-";
							count1=Recepient::searching();	
							
							if(count1==1)
							{
								Recepient::accepting_blood();
								return;
							}
								
							if(count1==0)
							{
								return;
							}
								
		                	break;	
		                	
		                	case 2:
		                	needed_blood="B-";
							count1=Recepient::searching();	
							
							if(count1==1)
							{
								Recepient::accepting_blood();
								return;
							}
							
							if(count1==0)
							{
								return;
							}	
		                	break;
		                	
		                	case 3:
		                	needed_blood="O-";
							count1=Recepient::searching();	
							
							if(count1==1)
							{
								Recepient::accepting_blood();
								return;
							}
							
							if(count1==0)
							{
								return;
							}
		                	break;	
		                	
		                	default:
		                	cout<<"\n\n\t\tPlease select from the following choices..";
		                	break;
		                	
						}
	            	}
		            
		            if(needed_blood=="b+" || needed_blood=="B+")
	            	{
		                cout<<"\n\n\t\tyou can recieve from B-, O+, O-...";
		                cout<<"\n\n\tEnter choice.\n\t1.from B-\n\t2.from O+\n\t3.from O-\n";
		                cin>>choice3;
		                
		                switch(choice2)
		                {
		                	case 1:
		                	needed_blood="B-";
							count1=Recepient::searching();	
							
							if(count1==1)
							{
								Recepient::accepting_blood();
								return;
							}
							
							if(count1==0)
							{
								return;
							}	
		                	break;
		                	
		                	case 2:
		                	needed_blood="O+";
							count1=Recepient::searching();	
							
							if(count1==1)
							{
								Recepient::accepting_blood();
								return;
							}
							
							if(count1==0)
							{
								return;
							}
		                	break;
		                	
		                	case 3:
		                	needed_blood="O-";
							count1=Recepient::searching();	
							
							if(count1==1)
							{
								Recepient::accepting_blood();
								return;
							}
							
							if(count1==0)
							{
								return;
							}	
		                	break;
		                	
		                	default:
		                	cout<<"\n\n\t\tPlease select from the following choices..";
		                	break;
						}
	            	}
		            
		            if(needed_blood=="b-" || needed_blood=="B-")
	            	{
		                cout<<"\n\n\t\tyou can only recieve from O- ...\n\n";
		                
		                	needed_blood="O-";
							count1=Recepient::searching();	
							
							if(count1==1)
							{
								Recepient::accepting_blood();
								return;
							} 
							
							if(count1==0)
							{
								return;
							}   		
		            }
		            
		            if(needed_blood=="a+" || needed_blood=="A+")
	            	{
		                cout<<"\n\n\t\tyou can recieve from A-, O+, O- ...";
		                cout<<"\n\n\tEnter choice.\n\t1.from A-\n\t2.from O+\n\t3.from O-\n";
		                cin>>choice5;
		                
		                switch(choice5)
		                {
		                	case 1:
		                	needed_blood="A-";
							count1=Recepient::searching();	
							
							if(count1==1)
							{
								Recepient::accepting_blood();
								return;
							}
							
							if(count1==0)
							{
								return;
							}	
		                	break;
		                	
		                	case 2:
		                	needed_blood="O+";
							count1=Recepient::searching();	
							
							if(count1==1)
							{
								Recepient::accepting_blood();
								return;
							}
							
							if(count1==0)
							{
								return;
							}
		                	break;
		                	
		                	case 3:
		                	needed_blood="O-";
							count1=Recepient::searching();	
							
							if(count1==1)
							{
								Recepient::accepting_blood();
								return;
							}
							
							if(count1==0)
							{
								return;
							}	
		                	break;	
		                	
		                	default:
		                	cout<<"\n\n\t\tPlease select from the following choices..";
		                	break;
		                }
		            }
		            
		            if(needed_blood=="a-" || needed_blood=="A-")
		            {
		                cout<<"\n\n\t\tyou can recieve from O- ...\n\n";
	                
	                	needed_blood="O-";
						count1=Recepient::searching();	
						
						if(count1==1)
						{
							Recepient::accepting_blood();
							return;
						}
						
						if(count1==0)
						{
							return;
						}
		            }
	                
	                if(needed_blood=="o+" || needed_blood=="O+")
		            {
		                cout<<"\n\n\t\tyou can recieve from O- ...\n\n";
		                
	                	needed_blood="O-";
						count1=Recepient::searching();	
						
						if(count1==1)
						{
							Recepient::accepting_blood();
							return;
						}
						
						if(count1==0)
						{
							return;
						}
		            }
		            
		            if(needed_blood=="o-" || needed_blood=="O-")
		            {
		                cout<<"\n\n\t\tyou can only recieve from O- ...\n\n\tSORRY!!The requested blood group is not available at the moment\n\n";
		                return;
		            } 
		        }
			}
		}
		    
		
};

class Admin
{
	string username,password;
	
	public:	
		Admin()
		{
			
		}
		
		void get_data()
		{
			cout<<"\nEnter username: ";
			cin>>username;
			cout<<"Enter password: ";
			cin>>password;	
		}
		
		int signup()
		{
			int count=0;
			string admin;
			string single_line;
			
			cout<<"\n\nEnter the BLOOD DONATION code: ";
			cin>>admin;
			
			if(admin=="1053")
			{
				Admin::get_data();
				
				ifstream fin;
				fin.open("admin.txt");
				
				ofstream fout;
				fout.open("admin.txt",ios::app);
				
				if(!fin)
			    {
			    	cout<<"\n\n\t\tfile of ADMIN not found!!!";
					exit(0);	
				}
				
				while(!fin.eof())
				{
					getline(fin,single_line);
					
					if(username==single_line)
					{
						count=1;		
						break;
					}
				}
				
				if(count==0)
				{
					fout<<username;
					fout<<"\n"<<password;
					fout<<"\n---------------------\n";	
				}
				
				fin.close();
				fout.close();
				return count;
			}
			
			else
			{
				return count=2;
			}
		}
		
		int signin()
		{
			string single_line,second_line;
			int count=0;

			ifstream fin;
			fin.open("admin.txt");
			
			if(!fin)
		    {
		    	cout<<"\n\n\t\tfile of ADMIN not found!!!";
				exit(0);	
			}
			
			while(!fin.eof())
			{
				getline(fin,single_line);
				
				if(username==single_line)
				{
					getline(fin,single_line);
					
					if(password==single_line)
					{
						count=1;
						break;
					}
				}	
			}
			fin.close();
			return count;	
		}
		
		void counting(string needed_blood)
		{
			string single_line;
			int i,j,count=0;
			string bottle;
			int total=0;
			char str[19];
			
			ifstream fin;
			fin.open("blood.txt");
			
			if(!fin)
		    {
		    	cout<<"\n\n\t\tfile of BLOOD not found!!!";
				exit(0);	
			}
			
			while(!fin.eof())
			{
				getline(fin,single_line);
				i=single_line.find(needed_blood);
				
				if(i>0)
				{
					getline(fin,single_line);
					i=single_line.find(":");
					i=i+2;
		
					for(i,j=0;i<single_line.size();i++,j++)
					{
						bottle=single_line[i];				
					}
					
					count=1;
				 	strcpy(str,bottle.c_str());
				 	int k=atoi(str);
				 	total=total+k;
				}	
			}
			
			if(count==0)
			{
				cout<<"\n\n\t\tBlood group is not availaible in the laboratory...\n\n";	
			}
			
			cout<<"\n\nblood type: "<<needed_blood;
			cout<<"\nremaining bottles: "<<total;
			
			fin.close();
		}
		
		void blood_count()
		{
			int choice;
			cout<<"\t\t\t\tBLOOD DONATION SYSTEM\n\n";
			
			cout<<endl<<endl<<"Enter your Choice:"<<endl<<endl<<"1.\tAB+"<<endl<<"2.\tAB-"<<endl<<"3.\tA+"<<endl<<"4.\tA-"<<endl<<"5.\tB+"<<endl<<"6.\tB-"<<endl<<"7.\tO+"<<endl<<"8.\tO-";
			cout<<endl<<endl<<"Enter your desired Choice= ";
			cin>>choice;
			
			switch(choice)
			{
				case 1:
				Admin::counting("AB+");
				break;	
				
				case 2:
				Admin::counting("AB-");
				break;
				
				case 3:
				Admin::counting("A+");
				break;
				
				case 4:
				Admin::counting("A-");
				break;
				
				case 5:
				Admin::counting("B+");
				break;
				
				case 6:
				Admin::counting("B-");
				break;
				
				case 7:
				Admin::counting("O+");
				break;
				
				case 8:
				Admin::counting("O-");
				break;
				
				default:
				cout<<"\n\n\t\tPlease select from the following choices..";
		        break;
			}	
		}
	
		void adding_blood(string needed_blood)
		{
			string single_line;
			int i,j,count=0;
			string bottle;
			int total=0;
			char str[19];
			
			ifstream fin;
			ofstream fout;
			
			fin.open("donor.txt");
			fout.open("blood.txt",ios::app);
			
			if(!fin)
		    {
		    	cout<<"\n\n\t\tfile of DONOR not found!!!";
				exit(0);	
			}
			
			while(!fin.eof())
			{
				getline(fin,single_line);
				i=single_line.find(needed_blood);
				
				if(i==0)
				{
					getline(fin,single_line);
					i=single_line.find("donated");
					if(i>0)
					{
						i=single_line.find(":");
						i=i+1;
						count=1;
						
						for(i,j=0;i<single_line.size();i++,j++)
						{
							bottle=single_line[i];				
						}
		 	
					 	strcpy(str,bottle.c_str());
					 	int k=atoi(str);
					 	total=total+k;
					}
				}	
			}
			
			if(count==0)
			{
				cout<<"\n\n\t\tBlood group is not availaible at the laboratory...\n\n";
			}
			
			if(count==1)
			{
				cout<<"\n\n\t\tSUCCESFULLY ADDED!!!";
				fout<<"blood type: "<<needed_blood;
				fout<<"\nbottles: "<<total;
				fout<<"\n------------\n";
				fin.close();
				fout.close();	
			}
		}

		void amount_of_blood()
		{
			int choice;
			cout<<"\t\t\t\tBLOOD DONATION SYSTEM\n\n";
			
			cout<<endl<<endl<<"Enter your Choice:"<<endl<<endl<<"1.\tAB+"<<endl<<"2.\tAB-"<<endl<<"3.\tA+"<<endl<<"4.\tA-"<<endl<<"5.\tB+"<<endl<<"6.\tB-"<<endl<<"7.\tO+"<<endl<<"8.\tO-";
			cout<<endl<<endl<<"Enter your desired Choice= ";
			cin>>choice;
			
			switch(choice)
			{
				case 1:
				Admin::adding_blood("AB+");	
				break;	
				
				case 2:
				Admin::adding_blood("AB-");	
				break;
				
				case 3:
				Admin::adding_blood("A+");	
				break;
				
				case 4:
				Admin::adding_blood("A-");	
				break;
				
				case 5:
				Admin::adding_blood("B+");	
				break;
				
				case 6:
				Admin::adding_blood("B-");	
				break;
				
				case 7:
				Admin::adding_blood("O+");	
				break;
				
				case 8:
				Admin::adding_blood("O-");	
				break;
				
				default:
				cout<<"\n\n\t\tPlease select from the following choices..";
		        break;		
			}
		}
		
		void get_donor_recepient(int count)
		{
			string single_line;
			cout<<"\t\t\t\tBLOOD DONATION SYSTEM\n\n";
			
			ifstream fin;
			ifstream fin1;
			
			fin.open("donor.txt");
			fin1.open("recepient.txt");
			
			if(!fin)
		    {
		    	cout<<"\n\n\t\tfile of DONOR not found!!!";
				exit(0);	
			}
			
			if(!fin1)
		    {
		    	cout<<"\n\n\t\tfile of RECEPIENT not found!!!";
				exit(0);	
			}
			
			if(count==0)
			{
				while(!fin.eof())
				{
					getline(fin,single_line);
					cout<<"\n"<<single_line;			
				}
			}
			
			if(count==1)
			{
				while(!fin1.eof())
				{
					getline(fin1,single_line);
					cout<<"\n"<<single_line;		
				}
			}
		}
		
		void deleting(int count)
		{	
			string single_line;
			int count1=0,count2=0;
			string cnic;
			cout<<"\t\t\t\tBLOOD DONATION SYSTEM\n\n";
			
			ifstream fin;
			ifstream fin1;
			ofstream fout;
			
			fin.open("donor.txt");
			fin1.open("recepient.txt");
			fout.open("new.txt");
			
			if(!fin)
		    {
		    	cout<<"\n\n\t\tfile of DONOR not found!!!";
				exit(0);	
			}
			
			if(!fin1)
		    {
		    	cout<<"\n\n\t\tfile of RECEPIENT not found!!!";
				exit(0);	
			}
			
			
			if(count==0)
			{
				cout<<"Enter cnic of the donor you want to delete: ";
				cin>>cnic;
				
				while(!fin.eof())
				{
					getline(fin,single_line);
					
					if(single_line==cnic || count1==1)			
					{
						count1=1;
						
						if(single_line=="----------------")
						{
							count1=0;
							count2=1;
						}
					}
					
					else
					{
						fout<<single_line;
						fout<<"\n";
					}				
				}
				
				if(count2==1)
					cout<<"\n\n\t\tSUCCESSFULLY DELTED....\n\n";
		
				else
					cout<<"\n\n\t\tCNIC OF DONOR NOT FOUND....\n\n";
					
					
				fin.close();
		    	fout.close();	
		    		
				remove("donor.txt");
		
		    	if(rename("new.txt","donor.txt")!=0)
		    		cout<<"\n\n\t\tfile of donor couldn't be renamed..";
			}
			
			if(count==1)
			{
				cout<<"Enter cnic of the recepient you want to delete: ";
				cin>>cnic;
				
				while(!fin1.eof())
				{
					getline(fin1,single_line);
					
					if(single_line==cnic || count1==1)			
					{
						count1=1;
						
						if(single_line=="----------------")
						{
							count1=0;
							count2=1;
						}
					}
					
					else
					{
						fout<<single_line;
						fout<<"\n";
					}			
				}
				
				if(count2==1)
					cout<<"\n\n\t\tSUCCESSFULLY DELTED....\n\n";
		
				else
					cout<<"\n\n\t\tCNIC OF RECEPIENT NOT FOUND....\n\n";
					
					
				fin1.close();
		    	fout.close();	
		    		
				remove("recepient.txt");
		
		    	if(rename("new.txt","recepient.txt")!=0)
		    		cout<<"\n\n\t\tfile of recepient couldn't be renamed..";
					}
		}

		int functions()
		{
			cout<<"\t\t\t\tBLOOD DONATION SYSTEM\n\n";
			int choice;
			
			cout<<endl<<endl<<"Enter your Choice:"<<endl<<endl<<"1.\tADDING BLOOD FROM DONORS"<<endl<<"2.\tBLOOD COUNT"<<endl<<"3.\tVIEW ALL DONORS"<<endl<<"4.\tVIEW ALL RECEPIENTS"<<endl<<"5.\tDELETE A DONOR"<<endl<<"6.\tDELETE A RECEPIENT"<<endl<<"7.\tEXIT";
			cout<<endl<<endl<<"Enter your desired Choice= ";
			cin>>choice;
			
			switch(choice)
			{
				case 1:
				system("cls");
				Admin::amount_of_blood();	
				cout<<"\n\nPress any key to continue: ";
				getch();
				system("cls");
				functions();
				break;
				
				case 2:
				system("cls");
				Admin::blood_count();
				cout<<"\n\nPress any key to continue: ";
				getch();
				system("cls");
				functions();
				break;	
				
				case 3:
				system("cls");
				Admin::get_donor_recepient(0);
				cout<<"\n\nPress any key to continue: ";
				getch();
				system("cls");
				functions();
				break;
				
				case 4:
				system("cls");
				Admin::get_donor_recepient(1);
				cout<<"\n\nPress any key to continue: ";
				getch();
				system("cls");
				functions();
				break;
				
				case 5:
				system("cls");
				Admin::deleting(0);
				cout<<"\n\nPress any key to continue: ";
				getch();
				system("cls");
				functions();
				break;
				
				case 6:
				system("cls");
				Admin::deleting(1);
				cout<<"\n\nPress any key to continue: ";
				getch();
				system("cls");
				functions();
				break;
				
				case 7:
				system("cls");
				return 0;
				break;
				
				default:
				cout<<"\n\n\t\tPlease select from the following choices..";
				cout<<"\n\nPress any key to continue: ";
				getch();
				system("cls");
		        break;	
			}
		}		
};

void donor()
{
	string blood_type,name,age,address,gender,email,cnic;
	string illness,covid_sym,recent_illness;
	int last_donation,bottles;
	
	system("cls");
	cout<<"\t\t\t\tBLOOD DONATION SYSTEM"<<endl<<endl;
	
	cout<<"Enter your blood group: ";
	cin>>blood_type;
	
	if(blood_type=="ab+")	
	blood_type="AB+";
	
	if(blood_type=="ab-")
	blood_type="AB-";
	
	if(blood_type=="a+")
	blood_type="A+";	
					
	if(blood_type=="a-")
	blood_type="A-";	
			
	if(blood_type=="b+")
	blood_type="B+";	
			
	if(blood_type=="b-")
	blood_type="B-";	
			
	if(blood_type=="o+")
	blood_type="O+";	
			
	if(blood_type=="o-")
	blood_type="O-";
	
	cout<<"Enter your name: ";
	fflush(stdin);
	getline(cin,name);
	cout<<"Enter your address: ";
	fflush(stdin);
	getline(cin,address);
	cout<<"Enter your gender: ";
	cin>>gender;
	cout<<"Enter your email: ";
	cin>>email;
	cout<<"Enter your CNIC: ";
	cin>>cnic;
	cout<<"Enter any permanent illness: ";
	cin>>illness;
	cout<<"Enter any recent illness: ";
	cin>>recent_illness;
	cout<<"Enter any covid symptoms: ";
	cin>>covid_sym;
	cout<<"Enter the days when you last donated blood: ";
	cin>>last_donation;
	
	if(last_donation<120)
	{
		cout<<"\t\t\n\nYou can donate blood after 3 months..\n\n";
	}
	cout<<"How much bottles of blood you want to donate: ";
	cin>>bottles;
	Donor obj1(blood_type,name,address,gender,email,illness,recent_illness,covid_sym,last_donation,cnic,bottles);
	obj1.file_storing();
}

void recepient()
{
	string name,address,gender,email,cnic;
	string needed_blood;
	int bottles;
	
	system("cls");
	cout<<"\t\t\t\tBLOOD DONATION SYSTEM"<<endl<<endl;
	
	cout<<"Enter the blood group you need: ";
	cin>>needed_blood;
	cout<<"Enter bottles of blood you need: ";
	cin>>bottles;
	cout<<"Enter your name: ";
	fflush(stdin);
	getline(cin,name);
	cout<<"Enter your address: ";
	fflush(stdin);
	getline(cin,address);
	cout<<"Enter your gender: ";
	cin>>gender;
	cout<<"Enter your email: ";
	cin>>email;
	cout<<"Enter your CNIC: ";
	cin>>cnic;
	
	Recepient object1(needed_blood,bottles,name,address,gender,email,cnic);
	object1.file_storing();
	object1.search_donor();
}
int main()
{
	int choice,choice2,choice3;
	
	for(;;)
	{
		cout<<"\t\t\t\tBLOOD DONATION SYSTEM\n";
		cout<<endl<<endl<<"Enter your Choice:"<<endl<<endl<<"1.\tADMIN"<<endl<<"2.\tCUSTOMER"<<endl<<"3.\tEXIT";
		cout<<endl<<endl<<"Enter your desired Choice= ";
		cin>>choice;
		system("cls");
		
		if(choice==1)
		{
			string username,password;
			int choice1;
			int count,count1;
			
			cout<<"\t\t\t\tBLOOD DONATION SYSTEM"<<endl<<endl<<"\t\t\t\t\tAdmin";
			cout<<endl<<endl<<"Enter your Choice:"<<endl<<endl<<"1.\tSIGN IN"<<endl<<"2.\tSIGN UP"<<endl;
			cout<<endl<<"Enter your desired Choice= ";
			cin>>choice1;
				
			Admin huz;
				
			switch(choice1)
			{
				case 1:
				
				huz.get_data();
				count=huz.signin();
				
				if(count==1)
				{
					cout<<"\n\n\t\tSIGN IN SUCCESSFULL!!!!\n\n";
					cout<<"Press any key to continue: ";
					getch();
					system("cls");	
					huz.functions();	
				}
				
				if(count==0)
				{
					cout<<"\n\n\t\tIncorrect username or password!!!\n\n";	
					cout<<"Press any key to continue: ";
					getch();
					system("cls");
				}	
				break;
				
				case 2:
				count1=huz.signup();
				
				if(count1==1)
				{
					cout<<"\n\n\t\tSIGN UP UNSUCCESSFULL !!!! Please change username....\n\n";
					cout<<"Press any key to continue: ";
					getch();
					system("cls");	
				}
				
				if(count1==0)
				{
					cout<<"\n\n\t\tSIGN UP SUCCESSFULL !!!";	
					cout<<"\n\nPress any key to continue: ";
					getch();
					system("cls");
				}
				
				if(count1==2)	
				{
					cout<<"\n\n\t\tCODE IS INCORRECT!!!\n\n";
					cout<<"\n\nPress any key to continue: ";
					getch();
					system("cls");
				}
				break;
				
				default:
				cout<<"\n\n\t\tPlease select from the following choices..\n\n";	
				cout<<"\n\nPress any key to continue: ";
				getch();
				system("cls");
				break;
				
			}			
		}
		
		if(choice==2)
		{	
			for(;;)
			{
				cout<<"\t\t\t\tBLOOD DONATION SYSTEM\n";
				cout<<endl<<endl<<"Enter your Choice:"<<endl<<endl<<"1.\tDONOR"<<endl<<"2.\tRECEPIENT"<<endl<<"3.\tEXIT"<<endl;
				cout<<endl<<"Enter your desired Choice= ";
				cin>>choice2;
				
				if(choice2==1)
				{		
					donor();	
					cout<<"\n\nPress any key to continue: ";
					getch();
					system("cls");
				}
				
				if(choice2==2)
				{
					recepient();
					cout<<"\n\nPress any key to continue: ";
					getch();
					system("cls");
				}
				
				if(choice2==3)
				{
					system("cls");
					break;
				}		
			}
		}	
		
		if(choice==3)
		{
			cout<<"\t\t\t\tBLOOD DONATION SYSTEM\n";
			break;
		}
	}


	return 0;
}



