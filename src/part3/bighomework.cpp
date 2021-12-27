#include <iostream>
#include<fstream>
#include<string>
#include<string.h>
#include<algorithm>
#include<vector>
#include<sstream>
using namespace std;
string s[999999];
string name[999999];
string transp[1000];//定义的三个全局变量 后面会用到 

struct Terminal {
 char user[200]; //用户名 
 char mach[200]; // 计算机名 
 char root[200]; // 根目录 
 char wdir[200]; // 工作目录 
 char strin[200]; // 重定向标准输入 
 char strout[200]; // 重定向标准输出 
};
Terminal gTerm;
void doCat(int argc, char * argv[])
{
	if(argc==1)
	{
		cerr<<"wrong demands"<<endl;
		return;
	}
	string Root=gTerm.root;string Wdir=gTerm.wdir;//切换成字符串可以直接加减 
	for(int i=0;i<999999;i++)
	{
		stringstream ss;
		ss<<i+1;
		name[i]=ss.str();	
	}
	for(int i=0;i<999999;i++)
	while(name[i].length()<6)
		name[i]=" "+name[i]; //构建序号字符串数组 
	bool flag[4];
	for(int i =0;i<4;i++) flag[i]=false;
	for(int i =0;i<argc;i++)
	{
		if((string)argv[i]=="-n") flag[0]=true;
		if((string)argv[i]=="-b") flag[1]=true;
		if((string)argv[i]=="-s") flag[2]=true;
		if((string)argv[i]=="-E") flag[3]=true;
	}//"判定是否有相应的功能"
	int j;int row = 0;int time=0;
	string *str=new string[argc];
	for(int i=0;i<argc;i++)
		str[i]=argv[i];
	if(str[1]=="--help")
	{
		string help[100];
		ifstream A("cat.txt");
		if(!A)
		{
		    cerr<<"no such file";
		    return;
	    }
		int H=0;int hhh=0;
		while(!A.eof())
		{
			getline(A,help[H]);H++;}
		A.close();	
		for(int q =0;q<H;q++)
		{
		for(int len=0;len<help[q].length();len++)
		{
			gTerm.strout[hhh]=help[q][len];hhh++;
		}
		gTerm.strout[hhh]='\n';hhh++;
		}
		gTerm.strout[hhh]='\0';
	}//输出help 
	if(str[1]!="--help")//不是help的情况 
	{
		
		string path = gTerm.wdir;
		
		for(int i = 1;i<argc;i++)
		{	
			if(str[i]!="-n"&&str[i]!="-b"&&str[i]!="-s"&&str[i]!="-E") {j=i;break;}//判定第一个文件的位置 
		}
		for(int i =j;i<argc;i++)
		{
			if(str[i]=="-")//是-的情况			
			{
				int head=0;
				int b = sizeof(gTerm.strin);
				for(int i=0;i<b-1;i++)
				{
					if(gTerm.strin[i]=='\n')
					{
						s[row]=((string)gTerm.strin).substr(head,i-head);
						head=i+1;row++;
					}
				}
				s[row]=((string)gTerm.strin).substr(head,b-1);row++;
			}//读取strin 
			else
			{	//先处理文件名 
				string NAME;
				if(str[i][0]=='/')
				{
					if(Root=="/") NAME=str[i];
					if(Root!="/") NAME=Root+str[i];
				
				}
				if(str[i][0]!='/')
				{
					if(Root=="/") 
					{
						if(Wdir=="/") NAME="/"+str[i];
						if(Wdir!="/") NAME=Wdir+"/"+str[i];
					}
					if(Root!="/") 
					{
						if(Wdir=="/") NAME=Root+"/"+str[i];
						if(Wdir!="/") NAME=Root+Wdir+"/"+str[i];
					}
				}
				ifstream fin(NAME.c_str());
				if(!fin)
				{
					
			
				cerr<<"no such file"<<endl;
				return;
			
				}
				while(!fin.eof())
				{
					getline(fin,s[row]);
					row++;
				}//使用getline函数逐行读取 
				fin.close();
			}//读取文件 
		}
		if(flag[0]==true&&flag[1]==false&&flag[2]==false&&flag[3]==false)//deal with s[i] 
		{
			for(int i=0;i<row;i++)
			{
				s[i]=name[i]+"  "+s[i]+"\n";
				for(int t=0;t<s[i].length();t++)
					{
						gTerm.strout[time]=s[i][t];
						time++;
					}
			}
			gTerm.strout[time]='\0';
		}
		if(flag[0]==true&&flag[1]==false&&flag[2]==false&&flag[3]==true)
		{
			for(int i=0;i<row;i++)
			{
				s[i]=name[i]+"  "+s[i]+"$"+"\n";
				for(int t=0;t<s[i].length();t++)
					{
						gTerm.strout[time]=s[i][t];
						time++;
					}
			}
			gTerm.strout[time]='\0';
		}
		if(flag[0]==false&&flag[1]==true&&flag[2]==false&&flag[3]==true)
		{
			int oyyz=0;
			for(int i=0;i<row;i++)
			{
				if(s[i]!="")
				{
					s[i]=name[oyyz]+"  "+s[i]+"$"+"\n";oyyz++;
					for(int t=0;t<s[i].length();t++)
					{
						gTerm.strout[time]=s[i][t];
						time++;
					}
				}
				if(s[i]=="")
				{	
					gTerm.strout[time]='$';
					time++;
					gTerm.strout[time]='\n';
					time++;
				}
			}
			gTerm.strout[time]='\0';
		}
		if(flag[0]==false&&flag[1]==true&&flag[2]==false&&flag[3]==false)
		{
			int oyyz=0;
			for(int i=0;i<row;i++)
			{
				if(s[i]!="")
				{
					s[i]=name[oyyz]+"  "+s[i]+"\n";oyyz++;
					for(int t=0;t<s[i].length();t++)
					{
						gTerm.strout[time]=s[i][t];
						time++;
					}
				}
				if(s[i]=="")
				{
					gTerm.strout[time]='\n';
					time++;
				}
			}
			gTerm.strout[time]='\0';
		}
		if(flag[0]==false&&flag[1]==true&&flag[2]==false&&flag[3]==true)
		{
			int oyyz=0;
			for(int i=0;i<row;i++)
			{
				if(s[i]!="")
				{
					s[i]=name[oyyz]+"  "+s[i]+"$"+"\n";oyyz++;
					for(int t=0;t<s[i].length();t++)
					{
						gTerm.strout[time]=s[i][t];
						time++;
					}
				}
				if(s[i]=="")
				{	gTerm.strout[time]='$';
					time++;
					gTerm.strout[time]='\n';
					time++;
				}
			}
			gTerm.strout[time]='\0';
		}
		if(flag[0]==true&&flag[1]==false&&flag[2]==true&&flag[3]==false)
		{
			int oyyz=0;string timely;
			for(int i=0;i<row;i++)
			{
				if(s[i]!="")
				{
					s[i]=name[oyyz]+"  "+s[i]+"\n";oyyz++;
					for(int t=0;t<s[i].length();t++)
					{
						gTerm.strout[time]=s[i][t];
						time++;
					}
				}
				if(i==0&&s[i]=="")
				{	
					timely=name[oyyz]+"  "+"\n";oyyz++;
					for(int t=0;t<timely.length();t++)
					{
						gTerm.strout[time]=timely[t];
						time++;//这里不处理s【】 是避免影响空白行的判断 
					}
				}
				if(i>0&&s[i]==""&&s[i-1]!="")
				{
					timely=name[oyyz]+"  "+"\n";oyyz++;
					for(int t=0;t<timely.length();t++)
					{
						gTerm.strout[time]=timely[t];
						time++;
					}
				}
			}
			gTerm.strout[time]='\0';
		}
		if(flag[0]==true&&flag[1]==false&&flag[2]==true&&flag[3]==true)
		{
			int oyyz=0;string timely;
			for(int i=0;i<row;i++)
			{
				if(s[i]!="")
				{
					s[i]=name[oyyz]+"  "+s[i]+"$"+"\n";oyyz++;
					for(int t=0;t<s[i].length();t++)
					{
						gTerm.strout[time]=s[i][t];
						time++;
					}
				}
				if(i==0&&s[i]=="")
				{
					timely=name[oyyz]+"  "+"$"+"\n";oyyz++;
					for(int t=0;t<timely.length();t++)
					{
						gTerm.strout[time]=timely[t];
						time++;
					}
				}
				if(i>0&&s[i]==""&&s[i-1]!="")
				{
					timely=name[oyyz]+"  "+"$"+"\n";oyyz++;
					for(int t=0;t<timely.length();t++)
					{
						gTerm.strout[time]=timely[t];
						time++;
					}
				}
			}
			gTerm.strout[time]='\0';
		}
		if(flag[0]==false&&flag[1]==true&&flag[2]==true&&flag[3]==false)
		{
			int oyyz=0;
			for(int i=0;i<row;i++)
			{
				if(s[i]!="")
				{
					s[i]=name[oyyz]+"  "+s[i]+"\n";oyyz++;
					for(int t=0;t<s[i].length();t++)
					{
						gTerm.strout[time]=s[i][t];
						time++;
					}
				}
				if(i==0&&s[i]=="")
				{
					gTerm.strout[time]='\n';time++;
				}
				if(i>0&&s[i]==""&&s[i-1]!="")
				{
					gTerm.strout[time]='\n';time++;
				}
			}
			gTerm.strout[time]='\0';
		}
		if(flag[0]==false&&flag[1]==true&&flag[2]==true&&flag[3]==true)
		{
			int oyyz=0;
			for(int i=0;i<row;i++)
			{
				if(s[i]!="")
				{
					s[i]=name[oyyz]+"  "+s[i]+"$"+"\n";oyyz++;
					for(int t=0;t<s[i].length();t++)
					{
						gTerm.strout[time]=s[i][t];
						time++;
					}
				}
				if(i==0&&s[i]=="")
				{	
					gTerm.strout[time]='$';time++;
					gTerm.strout[time]='\n';time++;
				}
				if(i>0&&s[i]==""&&s[i-1]!="")
				{
					gTerm.strout[time]='$';time++;
					gTerm.strout[time]='\n';time++;
				}
			}
			gTerm.strout[time]='\0';
		}
		if(flag[0]==false&&flag[1]==false&&flag[2]==false&&flag[3]==false)
		{
			for(int i=0;i<row;i++)
			{
				s[i]=s[i]+"\n";
				for(int t=0;t<s[i].length();t++)
					{
						gTerm.strout[time]=s[i][t];
						time++;
					}
			}
			gTerm.strout[time]='\0';
		}
		if(flag[0]==false&&flag[1]==false&&flag[2]==false&&flag[3]==true)
		{
			for(int i=0;i<row;i++)
			{
				s[i]=s[i]+"$"+"\n";
				for(int t=0;t<s[i].length();t++)
					{
						gTerm.strout[time]=s[i][t];
						time++;
					}
			}
			gTerm.strout[time]='\0';
		}
		if(flag[0]==false&&flag[1]==false&&flag[2]==true&&flag[3]==false)
		{
			int oyyz=0;string timely;
			for(int i=0;i<row;i++)
			{
				if(s[i]!="")
				{
					s[i]=s[i]+"\n";oyyz++;
					for(int t=0;t<s[i].length();t++)
					{
						gTerm.strout[time]=s[i][t];
						time++;
					}
				}
				if(i==0&&s[i]=="")
				{
					timely="\n";oyyz++;
					for(int t=0;t<timely.length();t++)
					{
						gTerm.strout[time]=timely[t];
						time++;
					}
				}
				
				if(i>0&&s[i]==""&&s[i-1]!="")
				{
					timely="\n";oyyz++;
					for(int t=0;t<timely.length();t++)
					{
						gTerm.strout[time]=timely[t];
						time++;
					}
				}
			}
			gTerm.strout[time]='\0';
		}
		if(flag[0]==false&&flag[1]==false&&flag[2]==true&&flag[3]==true)
		{
			int oyyz=0;string timely;
			for(int i=0;i<row;i++)
			{
				if(s[i]!="")
				{
					s[i]=s[i]+"$"+"\n";oyyz++;
					for(int t=0;t<s[i].length();t++)
					{
						gTerm.strout[time]=s[i][t];
						time++;
					}
				}
				if(i==0&&s[i]=="")
				{
					timely="$";timely=timely+"\n";oyyz++;
					for(int t=0;t<timely.length();t++)
					{
						gTerm.strout[time]=timely[t];
						time++;
					}
				}
				if(i>0&&s[i]==""&&s[i-1]!="")
				{
					timely="$";timely=timely+"\n";oyyz++;
					for(int t=0;t<timely.length();t++)
					{
						gTerm.strout[time]=timely[t];
						time++;
					}
				}
			}
			gTerm.strout[time]='\0';
		}
	}

}
	
void doCp(int argc, char * argv[])
{
	string *str=new string[argc];
	for(int i=0;i<argc;i++)
		str[i]=argv[i];
	if(argc==1)
	{
		cerr<<"wrong demands"<<endl;
		return;
	}
	if(str[1]=="--help")
	{
		//shurubangzhu; 
		string help[100];
		ifstream A("cp.txt");
		if(!A)
		{
		    cerr<<"no such file"<<endl;
		    return;
	    }
		    
		int H=0;int hhh=0;
		while(!A.eof())
		{
			getline(A,help[H]);H++;}
		A.close();	
		for(int q =0;q<H;q++)
		{
		for(int len=0;len<help[q].length();len++)
		{
			gTerm.strout[hhh]=help[q][len];hhh++;
		}
		gTerm.strout[hhh]='\n';hhh++;
		}
		gTerm.strout[hhh]='\0';
	}
	else
	
	{
	if(argc>4)
	{
		cerr<<"wrong demands"<<endl;
		return;
	}
	if(str[1]=="-n")
	{		//处理文件名 
		if(str[2]=="-"&&str[3]=="-") strcat(gTerm.strout,gTerm.strin);
		if(str[2]=="-"&&str[3]!="-")
		{
			string f2;
			string Root=gTerm.root;
			string Wdir=gTerm.wdir;
			if(str[3][0]=='/')
			{
				if(Root=="/") f2=str[3];
				if(Root!="/") f2=Root+str[3];
				
			}
			if(str[3][0]!='/')
			{
				if(Root=="/") 
				{
					if(Wdir=="/") f2="/"+str[3];
					if(Wdir!="/") f2=Wdir+"/"+str[3];
				}
				if(Root!="/") 
				{
					if(Wdir=="/") f2=Root+"/"+str[3];
					if(Wdir!="/") f2=Root+Wdir+"/"+str[3];
				}
			}
			ofstream B(f2.c_str(),ios::app);
			if(!B)
			{
				cerr<<"no such file"<<endl;
				return;
			}
			B<<gTerm.strin;
			B.close();
		}
		if(str[2]!="-"&&str[3]=="-")//对文件名的各种情况进行进一步讨论 
		{
			string f1;
			string Root=gTerm.root;
			string Wdir=gTerm.wdir;
			if(str[2][0]=='/')
			{
				if(Root=="/") f1=str[2];
				if(Root!="/") f1=Root+str[2];
					
			}
			if(str[2][0]!='/')
			{
				if(Root=="/") 
				{
					if(Wdir=="/") f1="/"+str[2];
					if(Wdir!="/") f1=Wdir+"/"+str[2];
				}
				if(Root!="/") 
				{
					if(Wdir=="/") f1=Root+"/"+str[2];
					if(Wdir!="/") f1=Root+Wdir+"/"+str[2];
				}
			}
			ifstream A(f1.c_str());
			if(!A)
			{
				cerr<<"no such file"<<endl;
				return;
			}
			int trans=0;int wuwuwu=0;
			while(!A.eof())
			{
				getline(A,transp[trans]);trans++;
			}
			A.close();	
			for(int q =0;q<trans;q++)
			{
				for(int len=0;len<transp[q].length();len++)
				{
					gTerm.strout[wuwuwu]=transp[q][len];wuwuwu++;
				}
				gTerm.strout[wuwuwu]='\n';wuwuwu++;
			}
			gTerm.strout[wuwuwu]='\0';
			
		}
		if(str[2]!="-"&&str[3]!="-")
		{
		
			string f1;string f2;
			string Root=gTerm.root;
			string Wdir=gTerm.wdir;
			if(str[2][0]=='/')
			{
				if(Root=="/") f1=str[2];
				if(Root!="/") f1=Root+str[2];
					
			}
			if(str[3][0]=='/')
			{
				if(Root=="/") f2=str[3];
				if(Root!="/") f2=Root+str[3];
					
			}
			if(str[2][0]!='/')
			{
				if(Root=="/") 
				{
					if(Wdir=="/") f1="/"+str[2];
					if(Wdir!="/") f1=Wdir+"/"+str[2];
				}
				if(Root!="/") 
				{
					if(Wdir=="/") f1=Root+"/"+str[2];
					if(Wdir!="/") f1=Root+Wdir+"/"+str[2];
				}
			}
			if(str[3][0]!='/')
			{
				if(Root=="/") 
				{
					if(Wdir=="/") f2="/"+str[3];
					if(Wdir!="/") f2=Wdir+"/"+str[3];
				}
				if(Root!="/") 
				{
					if(Wdir=="/") f2=Root+"/"+str[3];
					if(Wdir!="/") f2=Root+Wdir+"/"+str[3];
				}
			}
			ifstream A(f1.c_str());
			ofstream B(f2.c_str(),ios::app);
			if(!A)
			{
				cerr<<"no such file"<<endl;
				return;
			}
			if(!B)
			{
				cerr<<"no such file"<<endl;
				return;
			}
			while(!A.eof())
			{
				string ch;
				getline(A,ch);
				if(A.eof()) B << ch;
				else B<<ch<<endl;
			}
			
			
			A.close();
			B.close();
		}
	}
	if((string)argv[1]!="-n")
	{
		if(str[1]=="-"&&str[2]=="-") strcpy(gTerm.strout,gTerm.strin);
		if(str[1]=="-"&&str[2]!="-")
		{
			string f2;
			string Root=gTerm.root;
			string Wdir=gTerm.wdir;
			if(str[2][0]=='/')
			{
				if(Root=="/") f2=str[2];
				if(Root!="/") f2=Root+str[2];
				
			}
			if(str[2][0]!='/')
			{
				if(Root=="/") 
				{
					if(Wdir=="/") f2="/"+str[2];
					if(Wdir!="/") f2=Wdir+"/"+str[2];
				}
				if(Root!="/") 
				{
					if(Wdir=="/") f2=Root+"/"+str[2];
					if(Wdir!="/") f2=Root+Wdir+"/"+str[2];
				}
			}
			ofstream B(f2.c_str());
			if(!B)
			{
				cerr<<"no such file"<<endl;
				return;
			}
			B<<gTerm.strin;
			B.close();
		}
		if(str[1]!="-"&&str[2]=="-")
		{
			string f1;
			string Root=gTerm.root;
			string Wdir=gTerm.wdir;
			if(str[1][0]=='/')
			{
				if(Root=="/") f1=str[1];
				if(Root!="/") f1=Root+str[1];
					
			}
			if(str[1][0]!='/')
			{
				if(Root=="/") 
				{
					if(Wdir=="/") f1="/"+str[1];
					if(Wdir!="/") f1=Wdir+"/"+str[1];
				}
				if(Root!="/") 
				{
					if(Wdir=="/") f1=Root+"/"+str[1];
					if(Wdir!="/") f1=Root+Wdir+"/"+str[1];
				}
			}
			ifstream A(f1.c_str());
			if(!A)
			{
				cerr<<"no such file"<<endl;
				return;
			}
			int trans=0;int wuwuwu=0;
			while(!A.eof())
			{
				getline(A,transp[trans]);trans++;
			}
			A.close();	
			for(int q =0;q<trans;q++)
			{
				for(int len=0;len<transp[q].length();len++)
				{
					gTerm.strout[wuwuwu]=transp[q][len];wuwuwu++;
				}
				gTerm.strout[wuwuwu]='\n';wuwuwu++;
			}
			gTerm.strout[wuwuwu]='\0';
		}
		if(str[1]!="-"&&str[2]!="-")
		{
			string f1;string f2;
			string Root=gTerm.root;
			string Wdir=gTerm.wdir;
			if(str[1][0]=='/')
			{
				if(Root=="/") f1=str[1];
				if(Root!="/") f1=Root+str[1];
					
			}
			if(str[2][0]=='/')
			{
				if(Root=="/") f2=str[2];
				if(Root!="/") f2=Root+str[2];
					
			}
			if(str[1][0]!='/')
			{
				if(Root=="/") 
				{
					if(Wdir=="/") f1="/"+str[1];
					if(Wdir!="/") f1=Wdir+"/"+str[1];
				}
				if(Root!="/") 
				{
					if(Wdir=="/") f1=Root+"/"+str[1];
					if(Wdir!="/") f1=Root+Wdir+"/"+str[1];
				}
			}
			if(str[2][0]!='/')
			{
				if(Root=="/") 
				{
					if(Wdir=="/") f2="/"+str[2];
					if(Wdir!="/") f2=Wdir+"/"+str[2];
				}
				if(Root!="/") 
				{
					if(Wdir=="/") f2=Root+"/"+str[2];
					if(Wdir!="/") f2=Root+Wdir+"/"+str[2];
				}
			}
			ifstream A(f1.c_str());
			ofstream B(f2.c_str());
			if(!A)
			{
				cerr<<"no such file"<<endl;
				return;
			}
			if(!B)
			{
				cerr<<"no such file"<<endl;
				return;
			}
			while(!A.eof())
			{
				string ch;
				getline(A,ch);
				if(A.eof()) B << ch;
				else B<<ch<<endl;
			}
			A.close();B.close();
		}
	}
	}
}

void doPwd(int argc, char * argv[])//显示工作目录 
{
	if(argc==1)
	{
		string out=gTerm.wdir;
		out=out+"\n";
		for(int i=0;i<out.length();i++)
		gTerm.strout[i]=out[i];
		gTerm.strout[out.length()]='\0';
	}
	if(argc==2&&(string)argv[1]=="--help")
	{
		string help[100];
		ifstream A("pwd.txt");
		if(!A)
			{
				cerr<<"no such file"<<endl;
				return;
			}
		
		int H=0;int hhh=0;
		while(!A.eof())
		{
			getline(A,help[H]);H++;}
		A.close();	
		for(int q =0;q<H;q++)
		{
		for(int len=0;len<help[q].length();len++)
		{
			gTerm.strout[hhh]=help[q][len];hhh++;
		}
		gTerm.strout[hhh]='\n';hhh++;
		}
		gTerm.strout[hhh]='\0';	//shuchubalabla
	}
	if(argc>1&&(string)argv[1]!="--help")
	{
		cerr<<"wrong demands"<<endl;
		return;
	}
}
void doTee(int argc,char * argv[])
{
	string *str=new string[argc];
	for(int i=0;i<argc;i++)
		str[i]=argv[i];
	if(argc==1) strcpy(gTerm.strout,gTerm.strin);
	else
	{
	if(str[1]=="--help")
	{
		string help[100];
		ifstream A("tee.txt");
		if(!A)
			{
				cerr<<"no such file"<<endl;
				return;
			}
		int H=0;int hhh=0;
		while(!A.eof())
		{
			getline(A,help[H]);H++;}
		A.close();	
		for(int q =0;q<H;q++)
		{
		for(int len=0;len<help[q].length();len++)
		{
			gTerm.strout[hhh]=help[q][len];hhh++;
		}
		gTerm.strout[hhh]='\n';hhh++;
		}
		gTerm.strout[hhh]='\0';//shuchuhelp
	}
	if(argc>1&&str[1]!="--help")
	{
		if(str[1]=="-a")
		{	if(argc==2)
				strcpy(gTerm.strout,gTerm.strin);
			else
			{
				strcpy(gTerm.strout,gTerm.strin);
				string Root=gTerm.root;
				string Wdir=gTerm.wdir;
				for(int i =2;i<argc;i++)
				{
					//处理文件名
					string fin; 
					if(str[i]=="-") strcpy(gTerm.strout,gTerm.strin);
					else
					{
						if(str[i][0]=='/')
						{
							if(Root=="/") fin=str[i];
							if(Root!="/") fin=Root+str[i];
				
						}
						if(str[i][0]!='/')
						{
							if(Root=="/") 
							{
								if(Wdir=="/") fin="/"+str[i];
								if(Wdir!="/") fin=Wdir+"/"+str[i];
							}
							if(Root!="/") 
							{
								if(Wdir=="/") fin=Root+"/"+str[i];
								if(Wdir!="/") fin=Root+Wdir+"/"+str[i];
							}
						                       }
						ofstream file(fin.c_str(),ios::app);
						if(!file)
						{
							cerr<<"no such file"<<endl;
							return;
						}
						file<<gTerm.strin;
						file.close();	
					}
					
				}
			}
		}
		if(str[1]!="-a")//判断是哪种情况 
		{	
			if(argc==1)
				strcpy(gTerm.strout,gTerm.strin);
			else
			{
				strcpy(gTerm.strout,gTerm.strin);
				string Root=gTerm.root;
				string Wdir=gTerm.wdir;
				for(int i =1;i<argc;i++)
				{
					//处理文件名
					string fin; 
					if(str[i]=="-") strcpy(gTerm.strout,gTerm.strin);
					else
					{
						if(str[i][0]=='/')
						{
							if(Root=="/") fin=str[i];
							if(Root!="/") fin=Root+str[i];
				
						}
						if(str[i][0]!='/')
						{
							if(Root=="/") 
							{
								if(Wdir=="/") fin="/"+str[i];
								if(Wdir!="/") fin=Wdir+"/"+str[i];
							}
							if(Root!="/") 
							{
								if(Wdir=="/") fin=Root+"/"+str[i];
								if(Wdir!="/") fin=Root+Wdir+"/"+str[i];
							}
						}
						ofstream file(fin.c_str());
						if(!file)
						{
							cerr<<"no such file"<<endl;
							return;
						}
						file<<gTerm.strin;
						file.close();	
					}
					
				}
			}
		}
		
	}
	}
}	
void doCd(int argc, char * argv[])
{
	if(argc!=2)
	{
		cerr<<"wrong demands"<<endl;
		return;
	}
	if((string)argv[1]=="--help")
	{
		string help[100];
		ifstream A("cd.txt");
		if(!A)
		{
			cerr<<"no such file"<<endl;
			return;
		}
		
		int H=0;int hhh=0;
		while(!A.eof())
		{
			getline(A,help[H]);H++;}
		A.close();	
		for(int q =0;q<H;q++)
		{
		for(int len=0;len<help[q].length();len++)
		{
			gTerm.strout[hhh]=help[q][len];hhh++;
		}
		gTerm.strout[hhh]='\n';hhh++;
		}
		gTerm.strout[hhh]='\0';
	}
	else//不需要显示帮助则将相对路径与绝对路径统一处理 
	{
		int len=strlen(argv[1]),cur=strlen(gTerm.wdir);
		if(argv[1][0]=='/') cur=1;
		for(int l=argv[1][0]=='/',r;l<len;l=r+2){//靠bool值判断起点 
			for(r=l;r+1<len&&argv[1][r+1]!='/';r++);
			if(argv[1][l]=='.'){
				if(l==r)continue;
				else if(r==l+1&&argv[1][r]=='.'){
					if(cur!=1){
						while(gTerm.wdir[cur-1]!='/')
							gTerm.wdir[--cur]=0;
						if(cur!=1)gTerm.wdir[--cur]=0;
					}
				}
				else{;
					// alarming
					
					
				}
			}
			else{
				if(cur!=1)gTerm.wdir[cur++]='/';
				copy(argv[1]+l,argv[1]+r+1,gTerm.wdir+cur),cur+=r-l+1;
			}
				
		}
		gTerm.wdir[cur]=0;
		return;
	}
}
int main()
{
/*	gTerm.wdir[0]='/';	gTerm.wdir[1]='a';gTerm.wdir[2]='/';gTerm.wdir[3]='b';gTerm.wdir[4]='\0';
	char*argv[]={(char*)"pwd"};
	doPwd(1,argv);
	cout<<gTerm.strout;*/
/*	char*argv[]={(char*)"cat",(char*)"--help"};
	doCat(2,argv);
	cout<<gTerm.strout;//bangzhu*/
/*	gTerm.root[0]='D';gTerm.root[1]=':';
	char*argv[]={(char*)"cat",(char*)"/src/a.txt"};
	doCat(2,argv);
	cout<<gTerm.strout; */
/*	gTerm.root[0]='D';gTerm.root[1]=':';
	char*argv[]={(char*)"cat",(char*)"-n",(char*)"/src/a.txt"};
	doCat(3,argv);
	cout<<gTerm.strout; */
/*	gTerm.root[0]='D';gTerm.root[1]=':';
	char*argv[]={(char*)"cat",(char*)"-n",(char*)"/src/b.txt",(char*)"/src/c.txt"};
	doCat(4,argv);
	cout<<gTerm.strout; */
/*	gTerm.root[0]='D';gTerm.root[1]=':';
	char*argv[]={(char*)"cat",(char*)"-s",(char*)"a.txt"};
	doCat(3,argv);
	cout<<gTerm.strout; */
/*	gTerm.root[0]='D';gTerm.root[1]=':';
	gTerm.strin[0]='a';gTerm.strin[1]='b';gTerm.strin[2]='c';gTerm.strin[3]='\n';
	gTerm.strin[4]='d';gTerm.strin[5]='e';gTerm.strin[6]='f';
	char*argv[]={(char*)"tee",(char*)"-a",(char*)"/src/a.txt",(char*)"/src/b.txt"};
	doTee(4,argv);
	cout<<gTerm.strout;
*/
	/*gTerm.wdir[0]='/';	gTerm.wdir[1]='a';gTerm.wdir[2]='/';gTerm.wdir[3]='b';gTerm.wdir[4]='\0';
	char*argv[]={(char*)"cd",(char*)"/c"};
	doCd(2,argv);
	cout<<gTerm.wdir;*/
	/*char*argv[]={(char*)"cp",(char*)"a.txt",(char*)"b.txt"};
	doCp(3,argv);*/
	/*char*argv[]={(char*)"cp",(char*)"--help"};
	doCp(2,argv);*/
	/*char*argv[]={(char*)"cp",(char*)"-n",(char*)"a.txt",(char*)"b.txt"};
	doCp(4,argv);*/
	// all of the above in main are test examples
}