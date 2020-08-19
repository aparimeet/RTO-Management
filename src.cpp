#include<iostream>
#include<cstring>
#include<fstream>
#include<string.h>
#include<cmath>
#include<ctime>

using namespace std;

int number_of_issued_licenses=0;
int number_of_registered_vehicles=0;
class person
{
public:
	int license_no, age;//,no_of_vehicles;
	int registeration_number;
	int fine=0;
	char name[20], gender;
    int idate, imonth, iyear;    //issue year
    int cdate, cmonth, cyear;    //current year
    int edate, emonth, eyear;    //expiry year


	void input()
	{
		cout<<"Enter  name, gender and age \n";//and number of vehicles possessed\n";
		cin>>name>>gender>>age;//>>no_of_vehicles;
	}
	void display()
	{
		cout<<"\nLicence Number = "<<license_no<<"  Name = "<<name<<"  Age = "<<age << endl;//write all outputs ?????
	}
	void display_vehicle()
	{
	cout<<"\nRegisteration Number = "<<registeration_number<<"\nIssue Date = "<<idate<<"/"<<imonth<<"/"<<iyear;
	cout<<"\nExpiry date = "<<edate<<"/"<<emonth<<"/"<<eyear << endl;
	}
	void operator=(person obj)
	{
	license_no=obj.license_no;
	age=obj.age;
	//no_of_vehicles=obj.no_of_vehicles;
	fine=obj.fine;
	strcpy(name,obj.name);
	gender=obj.gender;
	}
};



class rto : public person
{
	public:
		/*int idate, imonth, iyear;    //issue year
    		int cdate, cmonth, cyear;    //current year
    		int edate, emonth, eyear;    //expiry year*/
		void issue_date()
		{

    		time_t t = time(NULL);
            tm* timePtr = localtime(&t);
    		cdate = timePtr->tm_mday;
    		cmonth = (timePtr->tm_mon) + 1;
            cyear = (timePtr->tm_year)+1900;
    		expiry_date();
		}
		void expiry_date()
		{
    		edate = cdate;
    		emonth = cmonth;
    		eyear = cyear + 20;
		}
		void license_issue()
		{

			//stream out("record.txt",ios::app|ios::binary);
			//ofstream out("status.txt",ios::out|ios::binary);
			person s;
			char op	;
			ofstream file("record.txt",ios::app|ios::binary);
			do
			{
        			s.input();
                    number_of_issued_licenses++;
                    s.license_no=number_of_issued_licenses;
                    issue_date();
        			file.write((char*)&s,sizeof(s));
        			cout<<"New Entry made successfully and your details are as follows :\n";
                    s.display();
        			cout<<"Any more entry (Y/N)\n";
        			cin>>op;
   			}while(op=='y' || op=='Y');
			file.close();
			display_all();

		}


		void vehicle_registeration()
        {

                        //stream out("record.txt",ios::app|ios::binary);
                        //ofstream out("status.txt",ios::out|ios::binary);
                        //person s;
                        //char op ;
                        //ofstream file("record1.txt",ios::app|ios::binary);//record 1 is a separate file that consists of only those records that have registered a vehicle
                        //do
                        //{
                person s;
                int search;
                cout<<"Enter the licence number which is registering the vehicle\n";
                cin>>search;
                ifstream f2("record.txt");
                ofstream file("record1.txt");//record 1 stores the file witha registered vehicle
                f2.read((char*)&s,sizeof(s));
                while(!f2.eof())
                {
                    if(s.license_no==search)
                    {
                        number_of_registered_vehicles++;
                        s.registeration_number=number_of_registered_vehicles;
                        issue_date();
                        file.write((char*)&s,sizeof(s));
                        cout<<"New Entry made successfully and your details are as follows :\n";
                        s.display();
                        s.display_vehicle();
                    }

                                f2.read((char*)&s,sizeof(s));

                        }
                        f2.close();
                        display_all();
                        //      cout<<"Any more entry (Y/N)\n";
                        //      cin>>op;
                        //}while(op=='y' || op=='Y');
                        file.close();
                        //display_all();

                }




		void search_record()
		{
			person s;
			int search;
			cout<<"Enter the licence number to be searched\n";
			cin>>search;
			ifstream f2("record.txt");
			f2.read((char*)&s,sizeof(s));
			while(!f2.eof())
			{
				if(s.license_no==search)
					s.display();
				f2.read((char*)&s,sizeof(s));

			}
			f2.close();
			display_all();

		}

		void display_all()
		{
			cout<<"\nDisplaying all the records saved till now\n";
            person s;
            ifstream f2("record.txt");
            f2.read((char*)&s,sizeof(s));
            while(!f2.eof())
            {
                cout<<"\nLicence Number = "<<s.license_no<<"  Name = "<<s.name<<"  Age = "<<s.age<<endl;
                f2.read((char*)&s,sizeof(s));
            }
            f2.close();
		}


void transfer_ownership(string ob1,string ob2,string deleteline)
{
	string line;
	ifstream fin("Sample.txt");
	ofstream temp("temp.txt");
	while(fin>>line)
	{
		line.replace(line.find(deleteline),deleteline.length(),"");
		temp<<line<<endl;
		//if(strcmp(line,ob2)==0)
		//{
		//	temp<<deleteline;
		//}
	}
	temp.close();
	fin.close();
	remove("Sample.txt");
	rename("temp.txt","Sample.txt");
}
int addFine()
{
	int fine;
	int flag=1,choice;
	while(flag==0)
	{
		cout<<"Enter choice\n1 Driving against traffic\n2 Parking on footpath/zebra crossing\n3 Triple riding\n4 Improper number plate\n5 Riding without helmet\n6 Without Seatbelt"<<endl;
		switch(choice)
		{
			case 1: fine= 200;
				break;
			case 2: fine= 50;
				break;
			case 3: fine= 200;
				break;
			case 4: fine= 50;
				break;
			case 5: fine= 150;
				break;
			case 6: fine= 150;
				break;
			default : cout<<"Incorrect Input\n";
						flag=0;
						break;
		}
	}
	return fine;
}

};

int main()
{
	rto obj;
	int ch;
	do{
	cout<<"Enter your choice\n";
	cout<<"1.Licence Issue\n";
	cout<<"2.Licence Renewal\n";//
	cout<<"3.Vehicle Registeration\n";
	cout<<"4.Transfer of vehicle ownership\n";
	cout<<"5.Fine add\n";
	cout<<"6.Exit\n";//
	cout<<"7.Search record from license number\n";
	cout<<"8.Modify a record\n";//

	cin>>ch;

	switch(ch)
	{
		case 1:obj.license_issue();
		       break;
		case 2:{
			obj.issue_date();
			break;
		}
		case 3:obj.vehicle_registeration();
		       break;
		case 4:{
			person s,s1,s2;
			string l1,l2;
			cout<<"Enter the license number of the owner and the seller\n";
			cin>>l1>>l2;
   			/*ifstream f2("record.txt");
                        f2.read((char*)&s,sizeof(s));
                        while(!f2.eof())
                        {
                                if(s.license_no==l1)
                                        s1=s;
				if(s.license_no==l2)
					s2=s;
                                f2.read((char*)&s,sizeof(s));

                        }
                        f2.close();*/
			cout<<"Enter the registration no. of the vehicle to be transferred\n";
		        string deleteline;
	       		cin>>deleteline;
			obj.transfer_ownership(l1,l2,deleteline);
		       break;
		       }
		case 5:
		       {
			       int l;
			       person s;
		       cout<<"Enter the license number\n";
		       cin>>l;
		        ifstream f2("record.txt");
                        f2.read((char*)&s,sizeof(s));
                        while(!f2.eof())
                        {
                                if(s.license_no==l)
				{		int amt=obj.addFine();
                                        s.fine+=amt;
				}
                                f2.read((char*)&s,sizeof(s));

                        }
                        f2.close();


		       }
		case 7:obj.search_record();
		       break;
		//case 8:obj.modify();
		  //     break;

         }


	}while(ch!=6);
return 0;
}




