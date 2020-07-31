#include<iostream>
#include<fstream>
#include<conio.h>
#include<stdlib.h>
#include<string.h>

using namespace std;

class user
{
	protected: 
		char uid[20],name[20],gender[6],fathers_name[20],pno[11],pwd[20];
		int age;
	public:
		friend class candidate;
		void input_data();
		void display_data();
		void display_one_user(char []);
		int check_uid(char []);
		int login(char []);
		void change_pno(char []);
		void change_pwd(char []);
};

class candidate : public user
{
	protected:
		char party_name[20];
	public:
		void input_data();
		void display_data();
		friend class vote;
};

class vote
{
	protected:
		char uid[20];
		char choice[20];
	public:
		void voting(char []);
		void vote_stat();
		int count_vote();
		int count_vote(char []);
		int check_vote(char []);
};

void dispchar()
{
	cout<<endl;
	for(int i=0;i<80;i++)
	{
		cout<<"*";
	}
	cout<<endl;
}

int user::check_uid(char id[20])
{
	user u;
	ifstream fdata;
	fdata.open("Data\\user.txt",ios::in|ios::binary);
	
	while(fdata.read((char*)&u,sizeof(u)))
	{
		if(stricmp(u.uid,id)==0)
		return(1);
	}
	fdata.close();
	return(0);
}

int check_uidd(char a[20])
{
	int i;
	for(i=0;a[i]!='\0';i++)
	{
		if(a[i]<48 || a[i]>57 || strlen(a)!=12)
		return(0);
	}
	if(strlen(a)==12)
	return(1);
	return(0);
}

int check_pno(char a[20])
{
	int i;
	for(i=0;a[i]!='\0';i++)
	{
		if(a[i]<48 || a[i]>57 || strlen(a)!=10)
		return(0);
	}
	if(strlen(a)==10)
	return(1);
	return(0);
}

char* password()
{
	char pwd[25], ch;
	int i=0;
	while (1)
	{
		ch = getch();
		
		if (ch == 13)
		{
			pwd[i]='\0';
			break;
		}
		if (ch==8)
		{
			if(i==0)
			{
        		continue;
			}
			else
			{
				cout<<"\b \b";
        		i--;
        		continue;
			}			
    	}
    	pwd[i++] = ch;
    	cout<<"*";
   }
   return(pwd);
}

void user::input_data()
{
	user u;
	char co_pwd[20];
	int ch;
	ofstream fdata;
	fdata.open("Data\\user.txt",ios::app|ios::binary);
	
	system("cls");
	dispchar();
	cout<<"\t\t\t\t NEW USER ";
	dispchar();
	
	cout<<"Enter Unique ID : ";
	cin>>u.uid;
	if(check_uid(u.uid)==0 && check_uidd(u.uid)==1)
	{
		cout<<"Enter name : ";
		cin>>u.name;
		cout<<"Gender M/F : ";
		cin>>u.gender;
		cout<<"Enter Age : ";
		cin>>u.age;
		if(u.age>=18)
		{
			cout<<"Father's Name : ";
			cin>>u.fathers_name;
			cout<<"Enter pno : ";
			cin>>u.pno;
			if(check_pno(u.pno) && (u.pno[0]=='9' || u.pno[0]=='8' || u.pno[0]=='7'|| u.pno[0]=='6'))
			{
				cout<<"Enter password : ";
				strcpy(u.pwd,password());
				cout<<"\nConfirm password : ";
				strcpy(co_pwd,password());
				
				if(strcmp(u.pwd,co_pwd)==0)
				{
					cout<<"\n\nDo you want to save :\n";
					cout<<"1: Save \n2: Exit Without Saving\nEnter Choice : ";
					cin>>ch;
					if(ch==1)
					{
						fdata.write((char*)&u,sizeof(u));
						cout<<"\nData Saved";
					}
				}
				else
				{
					cout<<"\nBoth Passowrds are diffrent";
				}	
			}
			else
			{
				cout<<"\n\nInvalid pno";
			}
		}
		else
		{
			cout<<"\nUnderAge";
		}
	}
	else
	{
		if(check_uid(u.uid)!=0)
			cout<<"UID already present";
		else
			cout<<"Invalid UID";
	}
	
	fdata.close();
}

void user::display_data()
{
	user u;
	ifstream fdata;
	fdata.open("Data\\user.txt",ios::in|ios::binary);
	
	system("cls");
	dispchar();
	cout<<"\t\t\t\t USER DATA";
	dispchar();
	
	cout<<"\n\nUnique ID \t Name     \tPno\n";
	while(fdata.read((char*)&u,sizeof(u)))
	{
		cout<<"\n"<<u.uid;
		cout<<"\t "<<u.name;
		//cout<<"\t"<<u.gender;
		//cout<<"\t"<<u.age;
		//cout<<"\t\t"<<u.fathers_name;
		cout<<"\t"<<u.pno;
		//cout<<"\t"<<u.pwd;
	}
	fdata.close();
}

void user::display_one_user(char id[20])
{
	user u;
	int found=0;
	ifstream fdata;
	fdata.open("Data\\user.txt",ios::in|ios::binary);
		
	while(fdata.read((char*)&u,sizeof(u)))
	{
		if(stricmp(id,u.uid)==0)
		{
			cout<<"\n\n Unique ID : "<<u.uid;
			cout<<"\n Name : "<<u.name;
			cout<<"\n Gender : "<<u.gender;
			cout<<"\n Age : "<<u.age;
			cout<<"\n Father's Name : "<<u.fathers_name;
			cout<<"\n Pno : "<<u.pno;
			found=1;
		}
	}
	if(found==0)
		cout<<"\n UID not found";
	fdata.close();
}

void candidate::input_data()
{
	candidate c;
	user u;
	char id[20];
	int found=0;
	ofstream fdata;
	ifstream fuser;
	fdata.open("Data\\candidate.txt",ios::app|ios::binary);
	fuser.open("Data\\user.txt",ios::in|ios::binary);
	
	system("cls");
	dispchar();
	cout<<"\t\t\t\t NEW CANDIDATE";
	dispchar();
	
	cout<<"Enter Unique ID : ";
	cin>>id;
	
	while(fuser.read((char*)&u,sizeof(u)))
	{
		if(stricmp(u.uid,id)==0)
		{
			strcpy(c.uid,u.uid);
			cout<<"\nName : "<<u.name;
			strcpy(c.name,u.name);
			cout<<"\nGender : "<<u.gender;
			strcpy(c.gender,u.gender);
			cout<<"\nEnter Age : "<<u.age;
			c.age=u.age;
			cout<<"\nFather's Name : "<<u.fathers_name;
			strcpy(c.fathers_name,u.fathers_name);
			cout<<"\nPNO : "<<u.pno;
			strcpy(c.pno,u.pno);
			cout<<"\n\nEnter Party Name : ";
			cin>>c.party_name;
			strcpy(c.pwd,u.pwd);
								
			fdata.write((char*)&c,sizeof(c));
			cout<<"\nData Saved";
			found=1;
		}
	}
	if(found==0)
	{
		cout<<"UID not found";
	}
		
	fdata.close();
	fuser.close();
}


void candidate::display_data()
{
	candidate c;
	ifstream fdata;
	fdata.open("Data\\candidate.txt",ios::in|ios::binary);
	
	system("cls");
	dispchar();
	cout<<"\t\t\t\t CANDIDATE DATA";
	dispchar();
	
	cout<<"\n\nUnique ID\tName\tParty_name\n";
	while(fdata.read((char*)&c,sizeof(c)))
	{
		cout<<"\n"<<c.uid;
		cout<<"\t"<<c.name;
		cout<<"\t"<<c.party_name;
	}
	fdata.close();
}

void user::change_pno(char id[20])
{
	user u;
	ifstream fdata;
	ofstream ftemp;
	fdata.open("Data\\user.txt",ios::in|ios::binary);
	ftemp.open("Data\\temp.txt",ios::app|ios::binary);
	
	while(fdata.read((char*)&u,sizeof(u)))
	{
		if(stricmp(u.uid,id)==0)
		{
			char pno[20];
			cout<<"\n\n\n\tEnter pno : ";
			cin>>pno;
			if(check_pno(pno))
			{
				strcpy(u.pno,pno);
			}
			else
			{
				cout<<"\n\nInvalid pno";
			}
			ftemp.write((char*)&u,sizeof(u));			
		}
		else
		{
			ftemp.write((char*)&u,sizeof(u));
		}
	}
	fdata.close();
	ftemp.close();
	remove("Data\\user.txt");
	rename("Data\\temp.txt","Data\\user.txt");
}

void user::change_pwd(char id[20])
{
	user u;
	char pwd[25],co_pwd[25];
	ifstream fdata;
	ofstream ftemp;
	fdata.open("Data\\user.txt",ios::in|ios::binary);
	ftemp.open("Data\\temp.txt",ios::app|ios::binary);
	
	while(fdata.read((char*)&u,sizeof(u)))
	{
		if(stricmp(u.uid,id)==0)
		{
			cout<<"Enter password : ";
			strcpy(pwd,password());
			cout<<"\nConfirm password : ";
			strcpy(co_pwd,password());
			
			if(strcmp(pwd,co_pwd)==0)
			{
				strcpy(u.pwd,pwd);
				cout<<"\n\nPassword changed\n\n";
			}
			else
			{
				cout<<"\nBoth Passowrds are diffrent";
			}
			ftemp.write((char*)&u,sizeof(u));
		}
		else
		{
			ftemp.write((char*)&u,sizeof(u));
		}
	}
	fdata.close();
	ftemp.close();
	remove("Data\\user.txt");
	rename("Data\\temp.txt","Data\\user.txt");
}

int vote::count_vote(char pname[20])
{
	int count=0;
	vote v;
	ifstream fvote;
	fvote.open("Data\\vote.txt",ios::in|ios::binary);
	
	while(fvote.read(((char*)&v),sizeof(v)))
	{
		if(stricmp(v.choice,pname)==0)
			count++;
	}
	fvote.close();
	return(count);
}

int vote::check_vote(char id[20])
{
	vote v;
	ifstream fvote;
	fvote.open("Data\\vote.txt",ios::in|ios::binary);
	
	while(fvote.read((char*)&v,sizeof(v)))
	{
		if(stricmp(v.uid,id)==0)
			return(1);
	}
	fvote.close();
	return(0);
}

void vote::voting(char id[20])
{
	vote v;
	candidate c;
	int found=0;
	ofstream fvote;
	ifstream fcandidate;
	fvote.open("Data\\vote.txt",ios::app|ios::binary);
	fcandidate.open("Data\\candidate.txt",ios::in|ios::binary);
	
	system("cls");
	dispchar();
	cout<<"\t\t\t\t VOTING PAGE";
	dispchar();
	cout<<"\n\n\tCandidate Info";
	c.display_data();
	
	cout<<"\n\n\n\n\n\tEnter Party name for vote : ";
	cin>>v.choice;
		
	while(fcandidate.read((char*)&c,sizeof(c)))
	{
		if(stricmp(c.party_name,v.choice)==0)
		{
			strcpy(v.uid,id);
			fvote.write((char*)&v,sizeof(v));
			cout<<"\n\nThank For the Voting\n";
			found=1;
		}
	}
	fvote.close();
	fcandidate.close();
	if(found==0)
	{
		cout<<"Party not found\n";
	}
}

int vote::count_vote()
{
	int count=0;
	vote v;
	ifstream fvote;
	fvote.open("Data\\vote.txt",ios::in|ios::binary);
	
	while(fvote.read(((char*)&v),sizeof(v)))
	{
			count++;
	}
	fvote.close();
	return(count);
}

void vote::vote_stat()
{
	system("cls");
	dispchar();
	cout<<"\t\t\t\t RESULT";
	dispchar();
	candidate c;
	char winner[20]={"NULL"};
	int max=0;
	float tvote=0,cvote;
	ifstream fdata;
	fdata.open("Data\\candidate.txt",ios::in|ios::binary);
	
	tvote=count_vote();
	cout<<"\n\nNo on vote\t\tPercentage\n\n";
	while(fdata.read((char*)&c,sizeof(c)))
	{
		cvote=count_vote(c.party_name);
		if(cvote>max)
		{
			max=cvote;
			strcpy(winner,c.party_name);
		}
		cout<<cvote<<"\t\t"<<(cvote/tvote)*100.00<<"%\n";
	}
	fdata.close();
	cout<<"\n\n\n\n\t\tWinner is "<<strupr(winner)<<" with "<<max<<" vote\n\n";
}


int user::login(char id[20])
{
	user u;
	char p[20];
	int found=0;
	ifstream fdata;
	fdata.open("Data\\user.txt",ios::in|ios::binary);
	
	while(fdata.read((char*)&u,sizeof(u)))
	{
		if(stricmp(u.uid,id)==0)
		{
			found=1;
			cout<<"Enter Password : ";
			strcpy(p,password());
			if(strcmp(p,u.pwd)==0)
				return(1);
			else
			{
				cout<<"Incorrect Password";
				return(0);
			}
		}
	}
	fdata.close();
	if(found==0)
	{
		cout<<"\nUID not found";
		return(0);
	}	
}

void welcome()
{
	cout<<"\n\n";
    cout<<"\t\t??       ?? \n";
    cout<<"\t\t ??     ?? ??????  ?????? ?????? ???    ?? ??????? \n";
	cout<<"\t\t  ?     ? ??    ??   ??     ??   ?? ?   ?? ??      \n";
    cout<<"\t\t   ?   ?  ??    ??   ??     ??   ??  ?  ?? ??  ??? \n";
    cout<<"\t\t    ? ?   ??    ??   ??     ??   ??   ? ?? ??   ?? \n";
    cout<<"\t\t     ?     ??????    ??   ?????? ??    ??? ??????? \n\n\n";
    
	cout<<"\t\t???????? ??    ?? ???????? ??????  ???????  ???   ???	\n";
	cout<<"\t\t??       ??    ?? ??         ??    ??       ?? ? ? ??	\n";
    cout<<"\t\t????????   ????   ????????   ??    ?????    ??  ?  ??	\n";
    cout<<"\t\t      ??    ??          ??   ??    ??       ??     ??	\n";
    cout<<"\t\t????????    ??    ????????   ??    ???????  ??     ??	\n\n\n\n\n";
    system("pause");
}

int main()
{
	user u;
	candidate c;
	vote v;
	int choice,ch_user,ch_admin,res;
	char pwd[20] = {"svs1234"},id1[20],p[20];
	welcome();
	while(1)
	{
		system("cls");
		dispchar();
		cout<<"\t\t\t\t ONLINE VOTING SYSTEM";
		dispchar();	
		ch_user=1;
		ch_admin=1;
		cout<<"\n\n1: Admin \n2: User \n3: Exit \nEnter choice : ";
		cin>>choice;
		
		if(choice==1)																	//Admin Login
		{
			cout<<"Enter Password : ";
			strcpy(p,password());
			if(strcmp(p,pwd)==0)
			{
				while(ch_admin!=6)
				{
					system("cls");
					dispchar();
					cout<<"\t\t\t\t ADMIN MODE";
					dispchar();
					cout<<"\n1: New Candidate \n";
					cout<<"2: View All Candidate \n";
					cout<<"3: View All Users \n";
					cout<<"4: View perticular user \n";
					cout<<"5: Vote result \n";
					cout<<"6: Exit\n";
					cout<<"\nEnter Choice : ";
					cin>>ch_admin;
			
					switch(ch_admin)
					{
						case 1:
							c.input_data();
							break;
						case 2:
							c.display_data();
							break;
						case 3:
							u.display_data();
							break;
						case 4:
							cout<<"Enter UID : ";
							cin>>id1;
							u.display_one_user(id1);
							break;
						case 5:
							v.vote_stat();
							break;
						case 6:
							cout<<"\n\nBye\n";
							break;
						default:
							cout<<"\nInvalid Input\n";
					}
					getch();
				}
			}
			else
			{
				cout<<"\nIncorrect password";
			}
		}
		
		else if(choice==2)																//User login
		{
			while(ch_user!=3)
			{
				system("cls");
				dispchar();
				cout<<"\t\t\t\t USER MODE";
				dispchar();
				cout<<"\n\n1: New User \n";
				cout<<"2: Login \n";
				cout<<"3: Exit\n";
				cout<<"\nEnter Choice : ";
				cin>>ch_user;
			
				switch(ch_user)
				{
					case 1:
						u.input_data();
						break;
					case 2:
						cout<<"Enter UID : ";
						cin>>id1;
						res=u.login(id1);
						while(res)
						{
							system("cls");
							dispchar();
							cout<<"\t\t\t\t USER PROFILE";
							dispchar();
							u.display_one_user(id1);
							int ch=1;
							cout<<"\n\n\n\t1: Give Vote\n";
							cout<<"\t2: Change pno\n";
							cout<<"\t3: Change password\n";
							cout<<"\t4: Log Out\n";
							cout<<"\tEnter Choice : ";
							cin>>ch;
							if(ch==1)
							{
								if(v.check_vote(id1)==1)
									cout<<"\nVote Already Given";
								else
									v.voting(id1);
							}
							else if(ch==2)
							{
								u.change_pno(id1);
							}
							else if(ch==3)
							{
								u.change_pwd(id1);
							}
							else
								break;
							getch();
						}
						break;
					case 3:
						cout<<"\n\nHave a Nice Day\n\n";
						break;
					default:
						cout<<"\nInvalid Input\n";
				}
				getch();
			}
		}
		
		else if(choice==3)
		{
			exit(0);
		}
		
		else
		cout<<"\nInvalid Input ";
		getch();
	}
	getch();
	
	return 0;
}


