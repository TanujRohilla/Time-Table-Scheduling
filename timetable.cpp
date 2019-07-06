#include <iostream>
#include <map>
#include <iterator>
#include <string>
#include <stdlib.h>
#include <ctime>
#include <vector>
#include <list>

using namespace std;
map<int, string> subject;
map<int, string>:: iterator it2;
map<string, string> professor;
map<string, int> credits;
vector <string> timetable[6][6][9];
vector<string>::iterator it;
list<string>T[6];

int subject_key_counter=0;    

void printTT(int k)
{
	/*
		Objective: Print time table
		Argument: class
		Return: None
	*/

    int temp=1;
    cout<<" \t\t";
    for(int i=0;i<8;i++)
    	for(it=timetable[k][0][i].begin();it<timetable[k][0][i].end();it++)			// print timing 
    		cout<<*it<<"\t\t";
    	cout<<endl<<endl;
    
    for (int j=1;j<=5;j++)
    {
     	for(it=timetable[k][j][0].begin();it!=timetable[k][j][0].end();it++)
           cout<<*it<<"\t\t";
        
        if((++temp)%2==0)
        {
        	temp=1;
        	cout<<endl;
        }
    }
}

bool isCreditEmpty()
{
	/*
		Objective: Check credit/number of class left for particular professor
		Argument: None
		Return: True if credit = 0 , false otherwise 
	*/
    map<string,int>::iterator it1;
    int flag=0;
    
    for(it1=credits.begin();it1!=credits.end();it1++)
    {
        if(it1->second!=0)
            return false;
        else
            flag=1;
    }
    if(flag==1)
        return true;
}

bool checkProfTime(int day,int time,string pname,int c_no)
{	
	/*
		Objective: check conflicting of schedule of class of same professor ( one professor cannot teach 2 or more class at same time)
		Argument: day, time, professor name , total class scheduled
		Return: true if conflicting between classes , false otherwise
	*/
	
    int count_t=0;
    for(int i=0;i<c_no;i++)
    { 
        for(it=timetable[i][day][0].begin();it!=timetable[i][day][0].end();it++)
        {
         
            string temp=*it;

            if(count_t==time)
            {
               if(pname==professor[temp])
                return true;
               else
                 return false;
            }
            count_t++;
        }
    }
    return false;
}

void printTeacher(int k)
{
	/*
		Objective: Print subjectcode - teacher
		Argument: k  
		Return : None
	*/
    cout<<endl;
    list<string>temp[6]=T;
    while(!temp[k].empty())
    {
        string sub=temp[k].front();
        temp[k].pop_front();
        string Teacher=temp[k].front();
        temp[k].pop_front();
        cout<<sub<<" :- "<<Teacher<<endl;
    }
}

bool check_lab(string lab)
{
	/*
		Objective : Find whether particular schedule is la or not
		Argument: Schedule
		Output: true if lab , false otherwise
	*/
   size_t found = lab.find("(L)");
    if (found != string::npos)
        return true;
     else
        return false;
}


int main()
{   int tot_sub,hrs,random_number,labs;
    static int all_sub=0;
    string course,subcode,prof,ch,choice;
    int count_cr=0;	// count total subject of particular course;
    for(int k=0;k<5;k++)
    {
   	count_cr=0;
    cout<<"Enter Course name:";
    cin>>course;
    cout<<"Enter total number of subject:";
    cin>>tot_sub;
    cout<<"Detail of subject, professor and number of hours tought by professor in a week\n";
    all_sub+=tot_sub;
    for (int i=0; i<tot_sub; i++)
    {

        cout<<"Enter subject code :";
        cin>>subcode;
		T[k].push_back(subcode);
        cout<<"Which professor will take "<<subcode<<" :";
         cin>>prof;
         T[k].push_back(prof);
        professor.insert(pair<string, string>(subcode,prof));
        cout<<"Enter Number of hours tought in a week :";
        cin>>hrs;
        
        credits[subcode]=hrs;
        subject[subject_key_counter]=subcode;
        subject_key_counter++;
        count_cr++;
        cout<<"Is their any lab:";
        cin>>choice;
        
		if(choice.compare("yes")==0)
        {
        	string str=subcode+"(LAB)";
        	cout<<"Enter total number of lab in a week:";
        	cin>>labs;
        	credits[str]=labs;
        	subject[subject_key_counter]=str;
        	subject_key_counter++;
        	count_cr++;
        }
    }

cout<<endl;
cout<<endl;
    timetable[k][0][0].push_back("9-10");
    timetable[k][0][1].push_back("10-11");
    timetable[k][0][2].push_back("11-12");
    timetable[k][0][3].push_back("12-1");
    timetable[k][0][4].push_back("1-2");
    timetable[k][0][5].push_back("2-3");
    timetable[k][0][6].push_back("3-4");
    timetable[k][0][7].push_back("4-5");
    timetable[k][1][0].push_back("Monday");
    timetable[k][2][0].push_back("Tuesday");
    timetable[k][3][0].push_back("Wednesd");
    timetable[k][4][0].push_back("Thursd");
    timetable[k][5][0].push_back("Friday");


	srand(time(0));
    for (int i=0;i<8;i++)
    {

        for (int j=1;j<=5;j++)
        {   l1:
           
            random_number=(rand()%count_cr);
            random_number+=(subject_key_counter-count_cr);
       
            map <int, string>::iterator it = subject.find(random_number);
            map <string,string>::iterator checkprof = professor.find(it->second);
            map <string, int>::iterator checkcredit = credits.find(it->second);

            if (it != subject.end()&&!isCreditEmpty())   // is empty timetable
            {
                    if (checkcredit->second != 0 )			// check credit = 0 or not
                    {
                     
                        if(!checkProfTime(j,i,checkprof->second,k))   // checking conflicting between classes
                        {
                            if(check_lab(it->second)&&i!=7)   // check whether schedule is lab or not
                               {
                                  timetable[k][j][0].push_back(it->second);		// scheduling consecutive lab
                                  timetable[k][j][0].push_back(it->second);
                                  credits[checkprof->first] = checkcredit->second - 1;  // updating credit of lab
                                  credits[checkprof->first] = checkcredit->second - 1;
                               }
                               else     												// schedule is normal theory
                                {
                                    credits[checkprof->first] = checkcredit->second - 1; 	// updating credit
                                    timetable[k][j][0].push_back(it->second);				// pushing value into timetable
                                }

                        }
                
                    }
                else
                {
                      	goto l1;
                }
            }

        }

    }
    printTT(k);			// printing time table
    printTeacher(k);	// print teachers
}

    return 0;
}