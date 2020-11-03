/**************************
** 项目名:学生管理系统
** 创建人:杨家华
** 日 期:2020/10/27
** 修改日期:2020/10/29
** 描 述:多功能记录处理分析输出一组学生成绩的软件
** 版 本:V2.0
**------------------------
*************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXLEN 10
#define N 30    //规定的上限人数
int num[N+1]= {0},score[N+1]= {0}; //定义全局数组实际人数，对应分数
void record(int num[],int score[],int *ftotal,char name[][MAXLEN]);
void list(int num[],int score[],int *ftotal,char name[][MAXLEN]);
void calcsumave(int num[],int score[],int *ftotal);
void SelectionSort(int num[],int score[],int(*compare)(int a,int b),int *ftotal,char name[][MAXLEN]);
int Ascending(int a,int b);
int Descending(int a,int b);
void Ascendingnum(int num[],int score[],int *ftotal,char name[][MAXLEN]);
void SearchData(int num[],int score[],int *ftotal,char name[][MAXLEN],void (*print)(int targetnum[],int targetscore[],char targetname[][MAXLEN],int *ftotal));
void StatisticAnalysis(int score[],int *ftotal);
void PrintByName(int targetnum[],int targetscore[],char targetname[][MAXLEN],int *ftotal);
void PrintByNumber(int targetnum[],int targetscore[],char targetname[][MAXLEN],int *ftotal);
void SortByName(int num[],int score[],char name[][MAXLEN],int *ftotal);
int main(void)
{
    printf("Number:200210603\nsubject No.6 - program No.1\n");//
    int in,total=N;
    char name[N][MAXLEN]= {0};
MENU:
    printf("1.Input record\n");
    printf("2.Calculate total and average score of course\n");
    printf("3.Sort in descending order by score\n");
    printf("4.Sort in ascending order by score\n");
    printf("5.Sort in ascending order by number\n");
    printf("6.Sort in dictionary order by name\n");
    printf("7.Search by number\n");
    printf("8.Search by name\n");
    printf("9.Statistic analysis\n");
    printf("10.List record\n");
    printf("0.Exit\n");
    printf("Please enter your choice:");
    scanf("%d",&in);
    if(in==1)record(num,score,&total,name);//ok
    else if(in==0)exit(0);//ok
    else if(in==2)calcsumave(num,score,&total);//ok
    else if(in==3)SelectionSort(num,score,Descending,&total,name);//ok
    else if(in==4)SelectionSort(num,score,Ascending,&total,name);//ok
    else if(in==5)Ascendingnum(num,score,&total,name);
    else if(in==6)SortByName(num,score,name,&total);
    else if(in==7)SearchData(num,score,&total,name,PrintByNumber);//
    else if(in==8)SearchData(num,score,&total,name,PrintByName);//
    else if(in==9)StatisticAnalysis(score,&total);//ok
    else if(in==10)list(num,score,&total,name);//ok
    else printf("输入非法！\n");
    goto MENU;
    return 0;
}
/**********************************
** 函数名:record
** 输 入: num[],score[],*ftotal，name[][]
** num---学号数组
** score---分数数组
** *ftotal---指针：实际人数
** name[][]--姓名字符串
** 输 出: void
** 功能描述:供用户输入
************************************/
void record(int num[],int score[],int *ftotal,char name[][MAXLEN])
{
    int now;
    printf("请输入本班总人数:");
    scanf("%d",ftotal);
    while(getchar()!='\n');
    if(*ftotal>N||*ftotal<=0)
    {
        printf("请输入正确的小于30的数字\n");
        return;
    }
    for(now=1; now<=*ftotal; now++)
    {
        printf("请输入姓名:");
        gets(name[now]);
        printf("请输入学号及成绩，中间以,隔开:");
        scanf("%d,%d",&num[now],&score[now]);
        while(getchar()!='\n');
    }
    printf("输入完毕,按回车键回到主菜单\n");
    getchar();
}
/**********************************
** 函数名:list
** 输 入: num[],score[],*ftotal，name[][]
** num---学号数组
** score---分数数组
** *ftotal---指针：实际人数
** name[][]--姓名字符串
** 输 出: void
** 功能描述:按照用户输入顺序输出数组
************************************/
void list(int num[],int score[],int *ftotal,char name[][MAXLEN])
{
    int now;
    for(now=1; now<=*ftotal; now++)
    {
        printf("name=");
        puts(name[now]);
        printf("num=%d,score=%d\n",num[now],score[now]);
    }
    printf("打印完毕,按回车键回到主菜单\n");
    while(getchar()!='\n');
    getchar();
}
/**********************************
** 函数名:calcsumave
** 输 入: num[],score[],*ftotal
** num---学号数组
** score---分数数组
** *ftotal---指针：实际人数
** 输 出: void
** 功能描述:计算总分及平均值再打印出来
************************************/
void calcsumave(int num[],int score[],int *ftotal)
{
    int now,sum;
    sum=0;
    for(now=1; now<=*ftotal; now++)
    {
        sum = sum + score[now];
    }
    printf("总分是%d,平均分是%.2f\n",sum,(float)sum/ *ftotal);
    printf("打印完毕,按回车键回到主菜单\n");
    while(getchar()!='\n');
    getchar();
}
/**********************************
** 函数名:SelectionSort
** 输 入: num[],score[],*ftotal,*compare，name[][]
** num-------学号数组
** score-----分数数组
** *ftotal---指针：实际人数
** *compare--函数指针，用于判断是正序还是倒序
** name[][]--姓名字符串数组
** 输 出: void
** 功能描述:计算正序或倒序排名再输出
** 调用模块:Ascending/Descending
************************************/
void SelectionSort(int num[],int score[],int(*compare)(int a,int b),int *ftotal,char name[][MAXLEN])
{
    int i,now,temp,targetnum[*ftotal+1],targetscore[*ftotal+1];
    char targetname[N][MAXLEN];
    char tempname[MAXLEN];
    for(now=1; now<=*ftotal; now++)
    {
        targetnum[now]=num[now];
        targetscore[now]=score[now];//将原来的数组复制一份新的数组以供后续排序
        strcpy(targetname[now],name[now]);
    }


    for(i=1; i<=*ftotal; i++) //此处循环是指现在是确定第几位数
    {
        for(now=i+1; now<=*ftotal; now++) //此处循环是指将第几位数与后面的数比较确定最大的数
        {
            if((*compare)(targetscore[i],targetscore[now])==1)
            {
                temp=targetnum[i];
                targetnum[i]=targetnum[now];
                targetnum[now]=temp;
                temp=targetscore[i];
                targetscore[i]=targetscore[now];
                targetscore[now]=temp;
                strcpy(tempname,targetname[i]);
                strcpy(targetname[i],targetname[now]);
                strcpy(targetname[now],tempname);
            }
        }
    }


    for(now=1; now<=*ftotal; now++)
    {
        printf("姓名:");
        puts(targetname[now]);
        printf("学号:%d,分数:%d\n",targetnum[now],targetscore[now]);
    }
    printf("打印完毕,按回车键回到主菜单\n");
    while(getchar()!='\n');
    getchar();
}
/**********************************
** 函数名:Ascending
** 输 入: a,b
** a---被判断的数1
** b---被判断的数2
** 输 出: x---1||0
** x 为 1, 表示...a>=b
** x 为 0, 表示...a<b
** 功能描述:给与两个数判断谁更小
************************************/
int Ascending(int a,int b)
{
    if(a>=b)return 1;
    else return 0;
}
/**********************************
** 函数名:Descending
** 输 入: a,b
** a---被判断的数1
** b---被判断的数2
** 输 出: x---1||0
** x 为 1, 表示...a<=b
** x 为 0, 表示...a>=b
** 功能描述:给与两个数判断谁更大
************************************/
int Descending(int a,int b)
{
    if(a<=b)return 1;
    else return 0;
}
/**********************************
** 函数名:SearchData
** 输 入: num[],score[],*ftotal，name[][],*print
** num---学号数组
** score---分数数组
** *ftotal---指针：实际人数
** *print----函数指针：用于决定后续调用哪些函数
** 调 用：PrintByNumber,PrintByname
** 输 出: void
** 功能描述:先内部进行倒序排名，再根据所需调用对应的搜索打印函数
************************************/
void SearchData(int num[],int score[],int *ftotal,char name[][MAXLEN],void (*print)(int targetnum[],int targetscore[],char targetname[][MAXLEN],int *ftotal))
{
    getchar();
    int i,now,temp,targetnum[*ftotal+1],targetscore[*ftotal+1];
    char targetname[N][MAXLEN];
    char tempname[MAXLEN];//用于存放需要交换的名字
    for(now=1; now<=*ftotal; now++)
    {
        targetnum[now]=num[now];
        targetscore[now]=score[now];//将原来的数组复制一份新的数组以供后续排序
        strcpy(targetname[now],name[now]);
    }
    for(i=1; i<=*ftotal; i++) //此处循环是指现在是确定第几位数
    {
        for(now=i+1; now<=*ftotal; now++) //此处循环是指将第几位数与后面的数比较确定最大的数
        {
            if(targetscore[i]<targetscore[now])
            {
                temp=targetnum[i];
                targetnum[i]=targetnum[now];
                targetnum[now]=temp;
                temp=targetscore[i];
                targetscore[i]=targetscore[now];
                targetscore[now]=temp;
                strcpy(tempname,targetname[i]);
                strcpy(targetname[i],targetname[now]);
                strcpy(targetname[now],tempname);
            }
        }
    }

        (*print)(targetnum,targetscore,targetname,ftotal);


        printf("打印完毕,按回车键回到主菜单\n");
        while(getchar()!='\n');
        getchar();
}
/**********************************
** 函数名:StatisticAnalysis
** 输 入: score[],*ftotal
** score---分数数组
** *ftotal---指针：实际人数
** 输 出: void
** 功能描述:数据分析：分析优秀良好普通及格不及格人数及其比例
************************************/
void StatisticAnalysis(int score[],int *ftotal)
{
    int perfect=0,great=0,good=0,bad=0,miss=0,now;
    for(now=1; now<=*ftotal; now++)
    {
        if(score[now]>=90)perfect++;
        else if(score[now]>=80)great++;
        else if(score[now]>=70)good++;
        else if(score[now]>=60)bad++;
        else miss++;
    }
    printf("优秀人数%d人,占总人数%.2f%%\n良好人数%d人,占总人数%.2f%%\n中等人数%d人,占总人数%.2f%%\n及格人数%d人,占总人数%.2f%%\n不及格人数%d人,占总人数%.2f%%\n",perfect,(float)perfect/ *ftotal*100,great,(float)great/ *ftotal*100,good,(float)good/ *ftotal*100,bad,(float)bad/ *ftotal*100,miss,(float)miss/ *ftotal*100);
    printf("打印完毕,按回车键回到主菜单\n");
    while(getchar()!='\n');
    getchar();

}
/**********************************
** 函数名:Ascendingnum
** 输 入: num[],score[],*ftotal
** num---学号数组
** score---分数数组
** *ftotal---指针：实际人数
** name[][]--姓名字符串数组
** 输 出: void
** 功能描述:按学号进行排名并输出
************************************/
void Ascendingnum(int num[],int score[],int *ftotal,char name[][MAXLEN])
{
    int i,now,temp,targetnum[*ftotal+1],targetscore[*ftotal+1];
    char targetname[N][MAXLEN];
    char tempname[MAXLEN];
    for(now=1; now<=*ftotal; now++)
    {
        targetnum[now]=num[now];
        targetscore[now]=score[now];//将原来的数组复制一份新的数组以供后续排序
        strcpy(targetname[now],name[now]);
    }
    for(i=1; i<=*ftotal; i++) //此处循环是指现在是确定第几位数
    {
        for(now=i+1; now<=*ftotal; now++) //此处循环是指将第几位数与后面的数比较确定最大的数
        {
            if(targetnum[i]>=targetnum[now])
            {
                temp=targetnum[i];
                targetnum[i]=targetnum[now];
                targetnum[now]=temp;
                temp=targetscore[i];
                targetscore[i]=targetscore[now];
                targetscore[now]=temp;
                strcpy(tempname,targetname[i]);
                strcpy(targetname[i],targetname[now]);
                strcpy(targetname[now],tempname);
            }
        }
    }
    for(now=1; now<=*ftotal; now++)
    {
        printf("姓名:");
        puts(targetname[now]);
        printf("学号:%d,分数:%d\n",targetnum[now],targetscore[now]);
    }
    printf("打印完毕,按回车键回到主菜单\n");
    while(getchar()!='\n');
    getchar();
}
/**********************************
** 函数名:PrintByName
** 输 入: targetnum[],targetscore[],targetname[][],*ftotal
** targetnum---分数倒序排列后的学号数组
** targetscore---分数倒序排列后的分数数组
** *ftotal---指针：实际人数
** targetname[][]--分数倒序排列后的姓名字符串数组
** 输 出: void
** 功能描述:根据已重新排名名单进行按照名字搜索，以便输出时给出正确的分数排名
************************************/
void PrintByName(int targetnum[],int targetscore[],char targetname[][MAXLEN],int *ftotal)
{
    int resultscore,resultrank,now;
    int mark=0;//标记是否找到
    char searchname[MAXLEN];
    printf("请输入你想寻找的姓名:");
    gets(searchname);
    for(now=1; now<=*ftotal; now++)
    {
        if(strcmp(searchname,targetname[now])==0)
        {
            resultscore=targetscore[now];
            resultrank=now;
            mark = 1;
        }
    }
    if(mark==1)
    {
        printf("姓名:");
        puts(searchname);
        printf("对应的分数是:%d,排名是%d\n",resultscore,resultrank);
    }
    else printf("抱歉没有找到你想找的人，请核对后再试");

}
/**********************************
** 函数名:PrintByNumber
** 输 入: targetnum[],targetscore[],targetname[][],*ftotal
** targetnum---分数倒序排列后的学号数组
** targetscore---分数倒序排列后的分数数组
** *ftotal---指针：实际人数
** targetname[][]--分数倒序排列后的姓名字符串数组
** 输 出: void
** 功能描述:根据已重新排名名单进行按照学号搜索，以便输出时给出正确的分数排名
************************************/
void PrintByNumber(int targetnum[],int targetscore[],char targetname[][MAXLEN],int *ftotal)
{
    int resultdata,searchnum,resultrank,now;
    char resultname[MAXLEN];
    int mark = 0;
    printf("请输入你想寻找的学号:");
    scanf("%d",&searchnum);
    for(now=1; now<=*ftotal; now++)
    {
        if(targetnum[now]==searchnum)
        {
            resultdata=targetscore[now];
            resultrank=now;
            strcpy(resultname,targetname[now]);
            mark = 1;
        }
    }
    if(mark==1)
    {
        printf("该学号对应的姓名:");
        puts(resultname);
        printf("对应的分数是:%d,排名是%d\n",resultdata,resultrank);
    }
    else printf("抱歉没有找到你想找的人，请核对后再试");
}
/**********************************
** 函数名:SortByName
** 输 入: num[],score[],name[][],*ftotal
** name----名字字符串数组
** score--分数数组
** *ftotal---指针：实际人数
** num----学号数组
** 输 出: void
** 功能描述:根据名字按照字典进行升序排列
************************************/
void SortByName(int num[],int score[],char name[][MAXLEN],int *ftotal)
{
    int i,now,temp,targetnum[*ftotal+1],targetscore[*ftotal+1];
    char targetname[N][MAXLEN];
    char tempname[MAXLEN];
    for(now=1; now<=*ftotal; now++)
    {
        targetnum[now]=num[now];
        targetscore[now]=score[now];//将原来的数组复制一份新的数组以供后续排序
        strcpy(targetname[now],name[now]);
    }


    for(i=1; i<=*ftotal; i++) //此处循环是指现在是确定第几个人
    {
        for(now=i+1; now<=*ftotal; now++) //此处循环是指将第几个人姓名与后面的数比较
        {
            if(strcmp(targetname[now],targetname[i]))
            {
                temp=targetnum[i];
                targetnum[i]=targetnum[now];
                targetnum[now]=temp;
                temp=targetscore[i];
                targetscore[i]=targetscore[now];
                targetscore[now]=temp;
                strcpy(tempname,targetname[i]);
                strcpy(targetname[i],targetname[now]);
                strcpy(targetname[now],tempname);
            }
        }
    }


    for(now=1; now<=*ftotal; now++)
    {
        printf("姓名:");
        puts(targetname[now]);
        printf("学号:%d,分数:%d\n",targetnum[now],targetscore[now]);
    }
    printf("打印完毕,按回车键回到主菜单\n");
}
