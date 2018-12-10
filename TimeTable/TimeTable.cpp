#include<iostream>
#include<stdlib.h>//rand() 
#include<stdio.h>
#include<ctime>//diffrent random number
#include<fstream>
using namespace std;
void display(char xyz[5][8])//to display time table
{   cout<<endl;
    cout<<"      9-10"<<"  10-11"<<"  11-12"<<"  12-1"<<"  1-2"<<"    2-3"<<"     3-4"<<"    4-5";
	for(int i=0;i<5;i++)
	{ 
		cout<<endl;
		switch(i)
		{
			case 0:
				cout<<"mon   ";
				break;
			case 1:
				cout<<"Tue   ";
				break;
			case 2:
			cout<<"wed   ";
				break;
			case 3:
			cout<<"thr   ";
				break; 
			case 4:
			cout<<"fri   ";
	
		}
		for(int j=0;j<8;j++)
		{
		cout<<xyz[i][j]<<"      ";
		}
	}
}
int main()
{
srand(time(NULL));
char msc[5][8];//40 slots
char Teacher_msc[5];
char labTeacher_msc[5];//5 Lab teacher
char mca[5][8];//2 diffrent rooms 
char Teacher_mca[5];     //2 teachers are common in both theory and lab
char labTeacher_mca[5];
//input from txt files
ifstream fmsc;
ifstream fmca;
ifstream fmca_lab;
ifstream fmsc_lab;
	fmsc.open("mscteacher.txt");
	if(!fmsc)
	{
	cout<<"error";
	exit(0);
	}
	int counter=0;
	while(!fmsc.eof())
	{ 
		fmsc>>Teacher_msc[counter];
		counter++;
	}
	fmca.open("mcateacher.txt");
	if(!fmca)
	{
	cout<<"error";
	exit(0);
	}
	counter=0;
	while(!fmca.eof())
	{ 
		fmca>>Teacher_mca[counter];
		counter++;
	}
	fmca_lab.open("mcalabteacher.txt");
	if(!fmca_lab)
	{
	cout<<"error";
	exit(0);
	}
	counter=0;
	while(!fmca_lab.eof())
	{ 
		fmca_lab>>labTeacher_mca[counter];
		counter++;
	}
		fmsc_lab.open("msclabteacher.txt");
	if(!fmsc_lab)
	{
	cout<<"error";
	exit(0);
	}
	counter=0;
	while(!fmsc_lab.eof())
	{ 
		fmsc_lab>>labTeacher_msc[counter];
		counter++;
	}
////verify whether 2 teachers are common
int count=0,count1=0;
for(int i=0;i<5;i++)
{
	for(int k=0;k<5;k++)
	{
		if(Teacher_msc[i]==Teacher_mca[k])
		{
		count++;
		}
		if(labTeacher_msc[i]==labTeacher_mca[k])
		{
		count1++;
		}
	}
}
if(count!=2||count1!=2)
{   
    cout<<"enter correct Details\n";
	exit(0);
}

for(int i=0;i<5;i++)//initialize with !
{
	for(int j=0;j<8;j++)
	{
		msc[i][j]='!';
		mca[i][j]='!';
	}
}

cout<<"format of Time-Table :\n";
display(msc);//outputs blank timetable of msc 

//############################################### Theory classes for msc 1st year #####################################
int k;//track of slot in particular day(slot from 9-5)
int k1;//track of day
int track[30];//track of older k1 generated(no 2 theory of same subject in 1 day)
for(int i=0;i<5;i++)//Teacher_msc
{ 
	for(int j=0;j<3;j++)//classes
	{  
		l1:
    	k1=rand()%5;//day
    	k=rand()%8;//slot in each day
		if(msc[k1][k]=='!')//--unassigned location getting randomly
    	{
    		for(int k2=0;k2<j;k2++)//--check not assigned subject same day
    		{
    			if(k1==track[k2])//if assigned on that day then again find k and k1
				{
					goto l1;
				}
			}	
			msc[k1][k]=Teacher_msc[i];//no 2class same day
			track[j]=k1;//track of day generated earlier
		}
    	else//again find new k and k1
		{
			goto l1;
		}

	} 
}
cout<<"\nTheory time table for Msc 1st year\n\n ";
display(msc);
//############################## MSC 1st year LAB #########################################################
 
int track2[5];//labs schedule track i.e which Teacher_msc lab is left and how many  
for(int i=0;i<5;i++)
{
	track2[i]=2;//4 lab assigned or not is check using this (2-1=1 means 2 scheduled and 2 left now to schedule)
}
for(int i=0;i<5;i++)
{
	for(int j=0;j<8;j++)
	{
		if(msc[i][j]=='!'&&j!=7)//find 2 adjacent unassigned location
		{
			if(msc[i][j+1]=='!')//j unassigned then j+1 should be unassigned
			{   l3:
				int k=rand()%5;//Teacher_msc at random
			    if(track2[k]==0)//all 4 already scheduled
			    {
				  goto l3;//find new k
				}
				msc[i][j]=labTeacher_msc[k];
				msc[i][j+1]=labTeacher_msc[k];
				track2[k]--;//update how many labs were left to schedule
			}
		}
		
	}
}
//################# Complete Time Table for MSC ##############################################
cout<<"\n Complete time table for Msc 1st Year:\n\n";
display(msc);
cout<<endl<<endl;
	//###output to excel file
	ofstream f1;
	f1.open("msc.csv",ios::out);
	f1<<"                                           MSC 1ST YEAR TIME TABLE"<<endl;
	f1<<","<<"      9-10"<<","<<"  10-11"<<","<<"  11-12"<<","<<"  12-1"<<","<<"  1-2"<<","<<"    2-3"<<","<<"     3-4"<<","<<"    4-5";
	for(int i=0;i<5;i++)
	{ 
		f1<<endl;
		switch(i)
		{
			case 0:
				f1<<"Monday"<<",";
				break;
			case 1:
				f1<<"Tuesday"<<",";
				break;
			case 2:
				f1<<"Wednsday"<<",";
				break;
			case 3:
				f1<<"Thrusday"<<",";
				break; 
			case 4:
				f1<<"Friday"<<",";
	
		}
		for(int j=0;j<8;j++)
		{
		f1<<msc[i][j]<<",";
		}
	}
//#################################### MCA 1st year THEORY #################################################
k=0;//track of slot in particular day
k1=0;//track of day
int track_mca[30];
for(int i=0;i<5;i++)//Teacher_mca
{ 
	for(int j=0;j<3;j++)//classes
	{  
		l11:
    	k1=rand()%5;//day
    	k=rand()%8;//slot in each day
		if(mca[k1][k]=='!')//unassigned location getting randomly
    	{
    		for(int k2=0;k2<j;k2++)//check not assigned subject same day
    		{
    			if(k1==track_mca[k2])//if assigned on that day then again find k and k1
				{
					goto l11;
				}
			}	
			if(msc[k1][k]!=Teacher_msc[i])//-->not same  Teacher class at Msc
			{
			
			mca[k1][k]=Teacher_mca[i];//no 2class same day
			track_mca[j]=k1;//track of day generated earlier
			}
			else
			{
				goto l11;
			}
		}
    	else
		{
			goto l11;
		}

	} 
}
//########################### MCA 1st Year LABS ###############################################################
k=0,k1=0;
int track_mca2[5];//labs schedule track i.e which Teacher_mca lab is left and how many  
for(int i=0;i<5;i++)
{
	track_mca2[i]=2;//4 lab assigned or not is check using this (2-1=1 means 2 scheduled and 2 left now to schedule)
}
for(int i=0;i<5;i++)
{
	for(int j=0;j<8;j++)
	{
		if(mca[i][j]=='!'&&j!=7)//find 2 adjacent unassigned location
		{
			if(mca[i][j+1]=='!')//j unassigned then j+1 should be unassigned
			{   l33:
				int k=rand()%5;//lab Teacher_mca
			    if(track_mca2[k]==0)//all 4 already scheduled
			    {
				  goto l33;//find new k
				}
				if(msc[i][j]!=labTeacher_msc[k])//->not same teacher lab in Msc at same time
				{
		        mca[i][j]=labTeacher_mca[k];
				mca[i][j+1]=labTeacher_mca[k];
				track_mca2[k]--;//update how many labs were left to schedule
				}
				else 
				{
				goto l33;
				}
			}
		}
		
	}
}
//#########################  MCA time table but with free slots ########################################
cout<<"\ncomplete time table for Mca 1st year with free slots\n";
display(mca);
//###constraint -- One Teacher Among all the teachers who has no lab at free slot of mca can take lab 
for(int i=0;i<5;i++)//RANDOM LAB AT FREE SLOT WHEN TEACHER IS FREE
{
	for(int j=0;j<8;j++)
	{
		if(mca[i][j]=='!')//find unassigned location
		{  l55:
			
			k=rand()%5;
			if(msc[i][j]!=labTeacher_msc[k])//free or not
			 { 
				mca[i][j]=labTeacher_mca[k];
				track_mca2[k]--;
				continue;
			}
			else
			{
				goto l55;
			}	
			
		}	
	}
}
//########## MCA TIME TABLE ###############################################
cout<<"\nFull Time Table FOR MCA:\n";
display(mca);
//###output to excel####
ofstream f11;
f11.open("mca.csv",ios::out);
	f11<<"                                           MCA 1ST YEAR TIME TABLE"<<endl;
	f11<<","<<"      9-10"<<","<<"  10-11"<<","<<"  11-12"<<","<<"  12-1"<<","<<"  1-2"<<","<<"    2-3"<<","<<"     3-4"<<","<<"    4-5";

	for(int i=0;i<5;i++)
	{ 
		f11<<endl;
		switch(i)
		{
			case 0:
				f11<<"Monday"<<",";
				break;
			case 1:
				f11<<"Tuesday"<<",";
				break;
			case 2:
				f11<<"Wednesday"<<",";
				break;
			case 3:
				f11<<"Thrusday"<<",";
				break; 
			case 4:
				f11<<"Friday"<<",";
	
		}
		for(int j=0;j<8;j++)
		{
		f11<<mca[i][j]<<",";
		}
	}

return 0;
}
