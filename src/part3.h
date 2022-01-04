#include "global_var.h"

char pwdhelp[]="pwd: pwd \
\n    Print the name of the current working directory.";
char teehelp[]="Usage: tee [OPTION]... [FILE]...\
Copy standard input to each FILE, and also to standard output.\
\n\
\n  -a			 append to the given FILEs, do not overwrite\
\n  --help     display this help and exit\
\n\
\nTinyShell online help: <https://github.com/Leo-Ngok/programming_basics_project>\
\nReport tee bugs to <yuezq21@mails.tsinghua.edu.cn>\
\nFull documentation at: <https://github.com/Leo-Ngok/programming_basics_project>\
\n";
char cdhelp[]="cd: cd [DIR]\
    Change the shell working directory.\
\n    \
\n    Change the current directory to DIR.\
\n    \
\n\
\n    \
\n    Options:\
\n      --help          display this help and exit\
\n    \
\n    `..' is processed by removing the immediately previous pathname component\
\n    back to a slash or the beginning of DIR.\
\n";
char cphelp[]="Usage: cp [OPTION]... SOURCE DEST\
\nCopy SOURCE to DEST.\
\n\
\n  -n,            do not overwrite an existing file\
\n      --help     display this help and exit\
\n\
\nTinyShell online help: <https://github.com/Leo-Ngok/programming_basics_project>\
\nReport cp bugs to <yuezq21@mails.tsinghua.edu.cn>\
\nFull documentation at: <https://github.com/Leo-Ngok/programming_basics_project>\
\n";
char cathelp[]="Usage: cat [OPTION]... [FILE]...\
\n Concatenate FILE(s) to standard output.\
\n\
\n With no FILE, or when FILE is -, read standard input.\
\n\
\n  -b,  number nonempty output lines, overrides -n\
\n  -E,  display $ at end of each line\
\n  -n,  number all output lines\
\n  -s,  suppress repeated empty output lines\
\n\
\nExamples:\
\n  cat        Copy standard input to standard output.\
\n\
\nGNU coreutils online help: <https://github.com/Leo-Ngok/programming_basics_project>\
\nReport cat translation bugs to <yuezq21@mails.tsinghua.edu.cn>\
\nFull documentation at: <https://github.com/Leo-Ngok/programming_basics_project>\
\n";
inline int _getc(FILE* doc,int *pos)
{
    if(doc==NULL)
    {
        return gTerm.strin[(*pos)++];
    }
    else
    {
        return fgetc(doc);
    }
}
void doCat(int argc, char * argv[])
{
	bool flag[4];
    memset(flag,false,sizeof flag);
    register int i=1;
	for(;i<argc;i++)
	{
        if(argv[i][0]!='-'||argv[i][1]=='\0')break;
        switch (argv[i][1]) {
            case 'n':flag[0]=true;break;
            case 'b':flag[1]=true;break;
            case 's':flag[2]=true;break;
            case 'E':flag[3]=true;break;
        }
	}//"判定是否有相应的功能"
    if(argc==i) {
        argc++;
        argv=(char**)realloc(argv,2);
        argv[i]=new char[1];
        argv[i][0]='-';
    }
	if(strcmp(argv[i],"--help")==0)
	{
        strcpy(gTerm.strout, cathelp);
        return;
	}//输出help
    int linenum=0;
    int buffer,pprev=0,prev='\n';
    for(;i<argc;i++)
    {
        int *pos=new int(0);
        FILE *source=NULL;
        if(strcmp(argv[i],"-")!=0)
        {
            source= fopen(Physical_Path(argv[i],true),"r");
            if(source==NULL)
            {
                output_no_file_error("cat",argv[i]);
                fclose(source);
                continue;
            }
        }
        bool line_head=true;
        buffer = _getc(source, pos);
        while(buffer>0)
        {
            //if it is a consecutive blank line
            bool consecutive_line_empty=pprev==prev&&prev==buffer&&buffer=='\n';
            //if -s (suppress repeated empty lines is enabled)
            if(consecutive_line_empty&&flag[2])goto next_iter;
            //output line number
            if((flag[0]||flag[1])&&prev=='\n')
            {
                if(!flag[1]||(flag[1]&&buffer!='\n'))
                {
                    linenum++;
                    int t=linenum,iiii=0;
                    char idx[10];
                    memset(idx,0,sizeof idx);
                    while(t)
                    {
                        idx[iiii++]=t%10+'0';
                        t/=10;
                    }
                    while(iiii<6)idx[iiii++]=' ';
                    for(int w=5;w>=0;w--)cinStrout(idx[w]);
                    cinStrout("  ");
                }
                line_head= false;
            }
            //output ending dollar sign
            if(buffer=='\n')
            {
                line_head=true;
                if(flag[3])cinStrout('$');
            }
            else line_head= false;
            cinStrout(buffer);
            next_iter:
            pprev=prev;
            prev=buffer;
            buffer = _getc(source, pos);
        }
        fclose(source);
    }
}
	
void doCp(int argc, char * argv[])
{
	if(argc==1)
	{
		std::cerr<<"cp: missing file operand"<<std::endl;
        std::cerr<<"Try 'cp --help' for more information."<<std::endl;
		return;
	}
	if(strcmp(argv[1],"--help")==0)
	{
		//shurubangzhu; 
        strcpy(gTerm.strout,cphelp);
        return;
	}
    int i=1;
    bool no_clobber=false;
    while(strcmp(argv[i],"-n")==0)
    {
        i++;
        no_clobber=true;
    }
    if(argc-i>2)
    {
        std::cerr<<"bash: cp: too many arguments"<<std::endl;
        return;
    }
    if(strcmp(argv[i],argv[i+1])==0&&!no_clobber)
    {
        std::cerr<<"cp: '"<<(string)argv[i]<<"' and '"<<(string)argv[i]<<"' are the same file"<<std::endl;
        return;
    }
    if(strcmp(argv[i+1],"-")==0)return;
    if(no_clobber)
    {        //处理文件名
        FILE *dest = fopen(Physical_Path(argv[i + 1], true), "r");
        if (dest != NULL) {
            fclose(dest);
            return;
        }
        fclose(dest);
    }
    FILE *dest= fopen(Physical_Path(argv[i+1],true),"w");
    if(strcmp(argv[i],"-")==0)
    {
        fprintf(dest,"%s",gTerm.strin);
    }
    else
    {
        FILE *source= fopen(Physical_Path(argv[i],true),"r");
        if(source==NULL) {
            output_no_file_error("cp",argv[i]);
            fclose(source);
            return;
        }
        int buffer=0;
        while((buffer=fgetc(source))!=-1)
            fprintf(dest,"%c",buffer);

        fclose(source);
    }
    fclose(dest);
}

void doPwd(int argc, char * argv[])//显示工作目录 
{
	if(argc==2&&strcmp(argv[1],"--help")==0)
        strcpy(gTerm.strout,pwdhelp);
	else
    {
        cinStrout(gTerm.wdir);
        cinStrout('\n');
    }
}
void doTee(int argc,char * argv[])
{
    strcpy(gTerm.strout,gTerm.strin);
	if(argc==1) return;
	if(strcmp(argv[1],"--help")==0)
	{
        strcpy(gTerm.strout, teehelp);
        return;
	}
    int i=1;
    while(strcmp(argv[i],"-a")==0)i++;
    for(;i<argc;i++)
    {
        if(strcmp(argv[i],"-")==0)continue;
        FILE* writeto=
                fopen(Physical_Path(argv[i],true),
                      strcmp(argv[1],"-a")==0?"a":"w");
        if(writeto==NULL)
        {
            output_no_file_error("tee",argv[i]);
            return;
        }
        fprintf(writeto,"%s",gTerm.strin);
        fclose(writeto);
    }
}	
void doCd(int argc, char * argv[])
{
    if(argc==1)return;
    if(strcmp(argv[1],"--help")==0)
    {
        strcpy(gTerm.strout,cdhelp);
    }
    else if(argc>2)
    {
        std::cerr<<"bash: cd: too many arguments"<<std::endl;
        return;
    }
    else//不需要显示帮助则将相对路径与绝对路径统一处理
	{
		size_t len=strlen(argv[1]),cur=strlen(gTerm.wdir);
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
				else{
                    if(cur!=1)gTerm.wdir[cur++]='/';
                    std::copy(argv[1]+l,argv[1]+r+1,gTerm.wdir+cur),cur+=r-l+1;
				}
			}
			else{
				if(cur!=1)gTerm.wdir[cur++]='/';
				std::copy(argv[1]+l,argv[1]+r+1,gTerm.wdir+cur),cur+=r-l+1;
			}
				
		}
		gTerm.wdir[cur]=0;
		return;
	}
}
