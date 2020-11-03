/**************************
** 项目名:学生管理系统
** 创建人:杨家华
** 日 期:2020/10/27
** 修改日期:2020/11/3
** 描 述:多功能记录处理分析输出一组学生成绩的软件
** 版 本:V3.0
**------------------------
*************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXLEN 10
#define N 30    //规定的上限人数
#define CN 6    //规定的上限课程数
int num[N+1]= {0},score[N+1][CN+1]= {0}; //定义全局数组实际人数，对应分数
void record(int num[],int score[][CN+1],int *ftotalmember,char name[][MAXLEN],int *ftotalcourse);
void list(int num[],int score[][CN+1],int *ftotalmember,char name[][MAXLEN],int *ftotalcourse);
void calcsumaveforcourse(int num[],int score[][CN+1],int *ftotalmember,int *ftotalcourse);
void calcsumaveforstu(int num[],int score[][CN+1],int *ftotalmember,int *ftotalcourse);
void SelectionSort(int num[],int score[][CN+1],int(*compare)(int a,int b),int *ftotalmember,char name[][MAXLEN],int *ftotalcourse);
int Ascending(int a,int b);
int Descending(int a,int b);
void Ascendingnum(int num[],int score[][CN+1],int *ftotalmember,char name[][MAXLEN],int *ftotalcourse);
void SearchData(int num[],int score[][CN+1],int *ftotalmember,int *ftotalcourse,char name[][MAXLEN],void (*print)(int targetnum[],int targetscore[][CN+1],char targetname[][MAXLEN],int *ftotalmember,int *ftotalcourse));
void StatisticAnalysis(int score[][CN+1],int *ftotalmember,int *ftotalcourse);
void PrintByName(int targetnum[],int targetscore[][CN+1],char targetname[][MAXLEN],int *ftotalmember,int *ftotalcourse);
void PrintByNumber(int targetnum[],int targetscore[][CN+1],char targetname[][MAXLEN],int *ftotalmember,int *ftotalcourse);
void SortByName(int num[],int score[][CN+1],char name[][MAXLEN],int *ftotalmember,int *ftotalcourse);
int main(void)
{
    printf("Number:200210603\nsubject No.7 - program No.1\n");//
    int in,totalmember=N;
    int totalcourse=6;
    char name[N][MAXLEN]= {0};
MENU:
    printf("1.Input record\n");
    printf("2.Calculate total and average score of every course\n");
    printf("3.Calculate total and average score of every student\n");
    printf("4.Sort in descending order by total score of every student\n");
    printf("5.Sort in ascending order by total score of every student\n");
    printf("6.Sort in ascending order by number\n");
    printf("7.Sort in dictionary order by name\n");
    printf("8.Search by number\n");
    printf("9.Search by name\n");
    printf("10.Statistic analysis for every course\n");
    printf("11.List record\n");
    printf("0.Exit\n");
    scanf("%d",&in);
    if(in==1)record(num,score,&totalmember,name,&totalcourse);
    else if(in==0)exit(0);
    else if(in==2)calcsumaveforcourse(num,score,&totalmember,&totalcourse);
    else if(in==3)calcsumaveforstu(num,score,&totalmember,&totalcourse);
    else if(in==4)SelectionSort(num,score,Descending,&totalmember,name,&totalcourse);
    else if(in==5)SelectionSort(num,score,Ascending,&totalmember,name,&totalcourse);
    else if(in==6)Ascendingnum(num,score,&totalmember,name,&totalcourse);
    else if(in==7)SortByName(num,score,name,&totalmember,&totalcourse);
    else if(in==8)SearchData(num,score,&totalmember,&totalcourse,name,PrintByNumber);
    else if(in==9)SearchData(num,score,&totalmember,&totalcourse,name,PrintByName);
    else if(in==10)StatisticAnalysis(score,&totalmember,&totalcourse);
    else if(in==11)list(num,score,&totalmember,name,&totalcourse);
    else printf("输入非法！\n");
    goto MENU;
    return 0;
}
/**********************************
** 函数名:record
** 输 入: num[],score[][],*ftotalmember，name[][MAXLEN],*ftotalcourse
** num---学号数组
** score---分数二维数组
** *ftotalmember---指针：实际人数
** name[][]--姓名字符串
** *ftotalcourse--指针：实际课程数
** 输 出: void
** 功能描述:供用户输入
************************************/
void record(int num[],int score[][CN+1],int *ftotalmember,char name[][MAXLEN],int *ftotalcourse)
{
    int now,bin;
    printf("请输入本班总人数:");
    scanf("%d",ftotalmember);
    getchar();
    printf("请输入共有几门课程:");
    scanf("%d",ftotalcourse);
    while(getchar()!='\n');
    if(*ftotalmember>N||*ftotalmember<=0||*ftotalcourse>6||*ftotalcourse<=0)
    {
        printf("请输入正确的班级人数或者课程数\n");
        return;
    }
    for(now=1; now<=*ftotalmember; now++)
    {
        printf("请输入姓名:");
        gets(name[now]);
        printf("请输入学号:");
        scanf("%d",&num[now]);
        while(getchar()!='\n');
        for(bin=1;bin<=*ftotalcourse;bin++)
        {
            printf("请输入第%d门课程的成绩",bin);
            scanf("%d",&score[now][bin]);
            getchar();
        }

    }
    printf("输入完毕,按回车键回到主菜单\n");
    getchar();
}
/**********************************
** 函数名:list
** 输 入: num[],score[],*ftotalmember，name[][]
** num---学号数组
** score---分数二维数组
** *ftotalmember---指针：实际人数
** *ftotalcourse--指针：实际课程数
** name[][]--姓名字符串
** 输 出: void
** 功能描述:按照用户输入顺序输出数组
************************************/
void list(int num[],int score[][CN+1],int *ftotalmember,char name[][MAXLEN],int *ftotalcourse)
{
    int now,temp,sumnow;
    for(now=1; now<=*ftotalmember; now++)
    {
        printf("name=%s",name[now]);
        printf("num=%d\t",num[now]);
        for(temp=1,sumnow=0;temp<=*ftotalcourse;temp++)
        {
            printf("course%dscore=%d\t",temp,score[now][temp]);
            sumnow += score[now][temp];
        }
        printf("总分是%d,平均分是%.2f\n",sumnow,(float)sumnow/ *ftotalcourse);
    }
    printf("打印完毕,按回车键回到主菜单\n");
    while(getchar()!='\n');
    getchar();
}
/**********************************
** 函数名:calcsumaveforcourse
** 输 入: num[],score[],*ftotalmember,*ftotalcourse
** num---学号数组
** *ftotalcourse--指针：实际课程数
** score---分数二维数组
** *ftotalmember---指针：实际人数
** 输 出: void
** 功能描述:计算每个课程总分及平均值再打印出来
************************************/
void calcsumaveforcourse(int num[],int score[][CN+1],int *ftotalmember,int *ftotalcourse)
{
    int now,sum,temp;
    for(temp=1;temp<=*ftotalcourse;temp++)
    {
        sum=0;
        for(now=1; now<=*ftotalmember; now++)
        {
            sum = sum + score[now][temp];
        }
        printf("课程%d总分是%d,平均分是%.2f\n",temp,sum,(float)sum/ *ftotalmember);
    }

    printf("打印完毕,按回车键回到主菜单\n");
    while(getchar()!='\n');
    getchar();
}
/**********************************
** 函数名:calcsumaveforstu
** 输 入: num[],score[],*ftotalmember,*ftotalcourse
** num---学号数组
** *ftotalcourse--指针：实际课程数
** score---分数二维数组
** *ftotalmember---指针：实际人数
** 输 出: void
** 功能描述:计算每位学生总分及平均值再打印出来
************************************/
void calcsumaveforstu(int num[],int score[][CN+1],int *ftotalmember,int *ftotalcourse)
{
    int now,sum,temp;
    for(temp=1;temp<=*ftotalmember;temp++)
    {
        sum=0;
        for(now=1; now<=*ftotalcourse; now++)
        {
            sum = sum + score[temp][now];
        }
        printf("学生学号%d总分是%d,平均分是%.2f\n",num[temp],sum,(float)sum/ *ftotalcourse);
    }

    printf("打印完毕,按回车键回到主菜单\n");
    while(getchar()!='\n');
    getchar();
}
/**********************************
** 函数名:SelectionSort
** 输 入: num[],score[],*ftotalmember,*compare，name[][]
** num-------学号数组
** score-----分数二维数组
** *ftotalmember---指针：实际人数
** *ftotalcourse--指针：实际课程数
** *compare--函数指针，用于判断是正序还是倒序
** name[][]--姓名字符串数组
** 输 出: void
** 功能描述:计算正序或倒序排名再输出
** 调用模块:Ascending/Descending
************************************/
void SelectionSort(int num[],int score[][CN+1],int(*compare)(int a,int b),int *ftotalmember,char name[][MAXLEN],int *ftotalcourse)
{
    int i,now,temp,targetnum[*ftotalmember+1],targetsumscore[*ftotalmember+1];
    char targetname[N][MAXLEN];
    char tempname[MAXLEN];
    for(now=1; now<=*ftotalmember; now++)
    {
        targetnum[now]=num[now];
        targetsumscore[now]=0;
        for(temp=1;temp<=*ftotalcourse;temp++)
        {
            targetsumscore[now] += score[now][temp];
        }
        strcpy(targetname[now],name[now]);

    }


    for(i=1; i<=*ftotalmember; i++) //此处循环是指现在是确定第几位数
    {
        for(now=i+1; now<=*ftotalmember; now++) //此处循环是指将第几位数与后面的数比较确定最大的数
        {
            if((*compare)(targetsumscore[i],targetsumscore[now])==1)
            {
                temp=targetnum[i];
                targetnum[i]=targetnum[now];
                targetnum[now]=temp;
                temp=targetsumscore[i];
                targetsumscore[i]=targetsumscore[now];
                targetsumscore[now]=temp;
                strcpy(tempname,targetname[i]);
                strcpy(targetname[i],targetname[now]);
                strcpy(targetname[now],tempname);
            }
        }
    }


    for(now=1; now<=*ftotalmember; now++)
    {
        printf("姓名:");
        puts(targetname[now]);
        printf("学号:%d,总分:%d\n",targetnum[now],targetsumscore[now]);
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
** 输 入: num[],score[],*ftotalmember，name[][],*print，*ftotalcourse
** num---学号数组
** score---分数二维数组
** *ftotalmember---指针：实际人数
** *print----函数指针：用于决定后续调用哪些函数
** *ftotalcourse--指针：实际课程数
** 调 用：PrintByNumber,PrintByname
** 输 出: void
** 功能描述:先内部进行倒序排名，再根据所需调用对应的搜索打印函数
************************************/
void SearchData(int num[],int score[][CN+1],int *ftotalmember,int *ftotalcourse,char name[][MAXLEN],void (*print)(int targetnum[],int targetscore[][CN+1],char targetname[][MAXLEN],int *ftotalmember,int *ftotalcourse))
{
    getchar();
    int i,now,temp,bin,targetnum[*ftotalmember+1],targetscore[*ftotalmember+1][CN+1],targetsumscore[*ftotalmember+1];
    char targetname[N][MAXLEN];
    char tempname[MAXLEN];//用于存放需要交换的名字
    for(now=1; now<=*ftotalmember; now++)
    {
        targetnum[now]=num[now];
        for(bin=1,targetsumscore[now]=0;bin<=*ftotalcourse;bin++)
        {
            targetscore[now][bin]=score[now][bin];//将原来的数组复制一份新的数组以供后续排序
            targetsumscore[now] +=score[now][bin];
        }
        strcpy(targetname[now],name[now]);
    }
    for(i=1; i<=*ftotalmember; i++) //此处循环是指现在是确定第几位数
    {
        for(now=i+1; now<=*ftotalmember; now++) //此处循环是指将第几位数与后面的数比较确定最大的数
        {
            if(targetsumscore[i]<targetsumscore[now])
            {
                temp=targetnum[i];
                targetnum[i]=targetnum[now];
                targetnum[now]=temp;
                for(bin=1;bin<=*ftotalcourse;bin++)
                {
                    temp=targetscore[now][bin];
                    targetscore[now][bin]=targetscore[i][bin];
                    targetscore[i][bin]=temp;
                }
                strcpy(tempname,targetname[i]);
                strcpy(targetname[i],targetname[now]);
                strcpy(targetname[now],tempname);
            }
        }
    }

        (*print)(targetnum,targetscore,targetname,ftotalmember,ftotalcourse);


        printf("打印完毕,按回车键回到主菜单\n");
        while(getchar()!='\n');
        getchar();
}
/**********************************
** 函数名:StatisticAnalysis
** 输 入: score[],*ftotalmember
** score---分数二维数组
** *ftotalmember---指针：实际人数
** *ftotalcourse--指针：实际课程数
** 输 出: void
** 功能描述:数据分析：分析优秀良好普通及格不及格人数及其比例
************************************/
void StatisticAnalysis(int score[][CN+1],int *ftotalmember,int *ftotalcourse)
{
    int perfect=0,great=0,good=0,bad=0,miss=0,now,course;
    for(course=1;course<=*ftotalcourse;course++)
    {
        for(now=1; now<=*ftotalmember; now++)
        {
            if(score[now][course]>=90)perfect++;
            else if(score[now][course]>=80)great++;
            else if(score[now][course]>=70)good++;
            else if(score[now][course]>=60)bad++;
            else miss++;
        }
        printf("第%d门课结果：优秀人数%d人,占总人数%.2f%%\n良好人数%d人,占总人数%.2f%%\n中等人数%d人,占总人数%.2f%%\n及格人数%d人,占总人数%.2f%%\n不及格人数%d人,占总人数%.2f%%\n",course,perfect,(float)perfect/ *ftotalmember*100,great,(float)great/ *ftotalmember*100,good,(float)good/ *ftotalmember*100,bad,(float)bad/ *ftotalmember*100,miss,(float)miss/ *ftotalmember*100);
        perfect=0,great=0,good=0,bad=0,miss=0;
    }
    printf("打印完毕,按回车键回到主菜单\n");
    while(getchar()!='\n');
    getchar();

}
/**********************************
** 函数名:Ascendingnum
** 输 入: num[],score[],*ftotalmember，*ftotalcourse
** num---学号数组
** score---分数二维数组
** *ftotalmember---指针：实际人数
** *ftotalcourse--指针：实际课程数
** name[][]--姓名字符串数组
** 输 出: void
** 功能描述:按学号进行排名并输出
************************************/
void Ascendingnum(int num[],int score[][CN+1],int *ftotalmember,char name[][MAXLEN],int *ftotalcourse)
{
    int i,now,temp,bin,targetnum[*ftotalmember+1],targetscore[*ftotalmember+1][*ftotalcourse];
    char targetname[N][MAXLEN];
    char tempname[MAXLEN];
    for(now=1; now<=*ftotalmember; now++)
    {
        targetnum[now]=num[now];
        for(bin=1;bin<=*ftotalcourse;bin++)
        {
            targetscore[now][bin]=score[now][bin];//将原来的数组复制一份新的数组以供后续排序
        }
        strcpy(targetname[now],name[now]);
    }
    for(i=1; i<=*ftotalmember; i++) //此处循环是指现在是确定第几位数
    {
        for(now=i+1; now<=*ftotalmember; now++) //此处循环是指将第几位数与后面的数比较确定最大的数
        {
            if(targetnum[i]>=targetnum[now])
            {
                temp=targetnum[i];
                targetnum[i]=targetnum[now];
                targetnum[now]=temp;
                for(bin=1;bin<=*ftotalcourse;bin++)
                {
                    temp=targetscore[i][bin];
                    targetscore[i][bin]=targetscore[now][bin];
                    targetscore[now][bin]=temp;
                }
                strcpy(tempname,targetname[i]);
                strcpy(targetname[i],targetname[now]);
                strcpy(targetname[now],tempname);
            }
        }
    }
    for(now=1; now<=*ftotalmember; now++)
    {
        printf("姓名:");
        puts(targetname[now]);
        printf("学号:%d,",targetnum[now]);
        for(bin=1;bin<=*ftotalcourse;bin++)
        {
            printf("课程%d成绩：%d,",bin,targetscore[now][bin]);
        }
        printf("\n");
    }
    printf("打印完毕,按回车键回到主菜单\n");
    while(getchar()!='\n');
    getchar();
}
/**********************************
** 函数名:PrintByName
** 输 入: targetnum[],targetscore[],targetname[][],*ftotalmember,*ftotalcourse
** targetnum---分数倒序排列后的学号数组
** targetscore---分数倒序排列后的分数二维数组
** *ftotalmember---指针：实际人数
** *ftotalcourse--指针：实际课程数
** targetname[][]--分数倒序排列后的姓名字符串数组
** 输 出: void
** 功能描述:根据已重新排名名单进行按照名字搜索，以便输出时给出正确的分数排名
************************************/
void PrintByName(int targetnum[],int targetscore[][CN+1],char targetname[][MAXLEN],int *ftotalmember,int *ftotalcourse)
{
    int resultscore[CN+1],resultrank,now,temp;
    int mark=0;//标记是否找到
    char searchname[MAXLEN];
    printf("请输入你想寻找的姓名:");
    gets(searchname);
    for(now=1; now<=*ftotalmember; now++)
    {
        if(strcmp(searchname,targetname[now])==0)
        {
            for(temp=1;temp<=*ftotalcourse;temp++)
            {
                resultscore[temp]=targetscore[now][temp];
            }
            resultrank=now;
            mark = 1;
        }
    }
    if(mark==1)
    {
        printf("姓名:");
        puts(searchname);
        for(temp=1;temp<=*ftotalcourse;temp++)
        {
            printf("课程%d分数:%d\t",temp,resultscore[temp]);
        }
        printf("排名是%d\n",resultrank);
    }
    else printf("抱歉没有找到你想找的人，请核对后再试\n");

}
/**********************************
** 函数名:PrintByNumber
** 输 入: targetnum[],targetscore[],targetname[][],*ftotalmember,*ftotalcourse
** targetnum---分数倒序排列后的学号数组
** targetscore---分数倒序排列后的分数二维数组
** *ftotalmember---指针：实际人数
** *ftotalcourse--指针：实际课程数
** targetname[][]--分数倒序排列后的姓名字符串数组
** 输 出: void
** 功能描述:根据已重新排名名单进行按照学号搜索，以便输出时给出正确的分数排名
************************************/
void PrintByNumber(int targetnum[],int targetscore[][CN+1],char targetname[][MAXLEN],int *ftotalmember,int *ftotalcourse)
{
    int resultdata[*ftotalcourse+1],searchnum,resultrank,now,temp;
    char resultname[MAXLEN];
    int mark = 0;
    printf("请输入你想寻找的学号:");
    scanf("%d",&searchnum);
    for(now=1; now<=*ftotalmember; now++)
    {
        if(targetnum[now]==searchnum)
        {
            for(temp=1;temp<=*ftotalcourse;temp++)
            {
                resultdata[temp]=targetscore[now][temp];
            }
            resultrank=now;
            strcpy(resultname,targetname[now]);
            mark = 1;
        }
    }
    if(mark==1)
    {
        printf("该学号对应的姓名:");
        puts(resultname);
        for(temp=1;temp<=*ftotalcourse;temp++)
        {
            printf("课程%d分数:%d\t",temp,resultdata[temp]);
        }
        printf("排名是%d\n",resultrank);
    }
    else printf("抱歉没有找到你想找的人，请核对后再试");
}
/**********************************
** 函数名:SortByName
** 输 入: num[],score[],name[][],*ftotalmember,*ftotalcourse
** name----名字字符串数组
** score--分数二维数组
** *ftotalmember---指针：实际人数
** *ftotalcourse--指针：实际课程数
** num----学号数组
** 输 出: void
** 功能描述:根据名字按照字典进行升序排列
************************************/
void SortByName(int num[],int score[][CN+1],char name[][MAXLEN],int *ftotalmember,int *ftotalcourse)
{
    int i,now,temp,bin,targetnum[*ftotalmember+1],targetscore[*ftotalmember+1][CN+1];
    char targetname[N][MAXLEN];
    char tempname[MAXLEN];
    for(now=1; now<=*ftotalmember; now++)
    {
        targetnum[now]=num[now];
        for(bin=1;bin<=*ftotalcourse;bin++)
        {
            targetscore[now][bin]=score[now][bin];//将原来的数组复制一份新的数组以供后续排序
        }
        strcpy(targetname[now],name[now]);
    }


    for(i=1; i<=*ftotalmember; i++) //此处循环是指现在是确定第几个人
    {
        for(now=i+1; now<=*ftotalmember; now++) //此处循环是指将第几个人姓名与后面的数比较
        {
            if(strcmp(targetname[now],targetname[i])<0)
            {
                temp=targetnum[i];
                targetnum[i]=targetnum[now];
                targetnum[now]=temp;
                for(bin=1;bin<=*ftotalcourse;bin++)
                {
                    temp=targetscore[i][bin];
                    targetscore[i][bin]=targetscore[now][bin];
                    targetscore[now][bin]=temp;
                }
                strcpy(tempname,targetname[i]);
                strcpy(targetname[i],targetname[now]);
                strcpy(targetname[now],tempname);
            }
        }
    }


    for(now=1; now<=*ftotalmember; now++)
    {
        printf("姓名:");
        puts(targetname[now]);
        printf("学号:%d,",targetnum[now]);
        for(bin=1;bin<=*ftotalcourse;bin++)
        {
            printf("课程%d成绩：%d,",bin,targetscore[now][bin]);
        }
        printf("\n");
    }
    getchar();
    printf("打印完毕,按回车键回到主菜单\n");
}
