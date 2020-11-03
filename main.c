/**************************
** ��Ŀ��:ѧ������ϵͳ
** ������:��һ�
** �� ��:2020/10/27
** �޸�����:2020/10/29
** �� ��:�๦�ܼ�¼����������һ��ѧ���ɼ������
** �� ��:V2.0
**------------------------
*************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXLEN 10
#define N 30    //�涨����������
int num[N+1]= {0},score[N+1]= {0}; //����ȫ������ʵ����������Ӧ����
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
    else printf("����Ƿ���\n");
    goto MENU;
    return 0;
}
/**********************************
** ������:record
** �� ��: num[],score[],*ftotal��name[][]
** num---ѧ������
** score---��������
** *ftotal---ָ�룺ʵ������
** name[][]--�����ַ���
** �� ��: void
** ��������:���û�����
************************************/
void record(int num[],int score[],int *ftotal,char name[][MAXLEN])
{
    int now;
    printf("�����뱾��������:");
    scanf("%d",ftotal);
    while(getchar()!='\n');
    if(*ftotal>N||*ftotal<=0)
    {
        printf("��������ȷ��С��30������\n");
        return;
    }
    for(now=1; now<=*ftotal; now++)
    {
        printf("����������:");
        gets(name[now]);
        printf("������ѧ�ż��ɼ����м���,����:");
        scanf("%d,%d",&num[now],&score[now]);
        while(getchar()!='\n');
    }
    printf("�������,���س����ص����˵�\n");
    getchar();
}
/**********************************
** ������:list
** �� ��: num[],score[],*ftotal��name[][]
** num---ѧ������
** score---��������
** *ftotal---ָ�룺ʵ������
** name[][]--�����ַ���
** �� ��: void
** ��������:�����û�����˳���������
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
    printf("��ӡ���,���س����ص����˵�\n");
    while(getchar()!='\n');
    getchar();
}
/**********************************
** ������:calcsumave
** �� ��: num[],score[],*ftotal
** num---ѧ������
** score---��������
** *ftotal---ָ�룺ʵ������
** �� ��: void
** ��������:�����ּܷ�ƽ��ֵ�ٴ�ӡ����
************************************/
void calcsumave(int num[],int score[],int *ftotal)
{
    int now,sum;
    sum=0;
    for(now=1; now<=*ftotal; now++)
    {
        sum = sum + score[now];
    }
    printf("�ܷ���%d,ƽ������%.2f\n",sum,(float)sum/ *ftotal);
    printf("��ӡ���,���س����ص����˵�\n");
    while(getchar()!='\n');
    getchar();
}
/**********************************
** ������:SelectionSort
** �� ��: num[],score[],*ftotal,*compare��name[][]
** num-------ѧ������
** score-----��������
** *ftotal---ָ�룺ʵ������
** *compare--����ָ�룬�����ж��������ǵ���
** name[][]--�����ַ�������
** �� ��: void
** ��������:��������������������
** ����ģ��:Ascending/Descending
************************************/
void SelectionSort(int num[],int score[],int(*compare)(int a,int b),int *ftotal,char name[][MAXLEN])
{
    int i,now,temp,targetnum[*ftotal+1],targetscore[*ftotal+1];
    char targetname[N][MAXLEN];
    char tempname[MAXLEN];
    for(now=1; now<=*ftotal; now++)
    {
        targetnum[now]=num[now];
        targetscore[now]=score[now];//��ԭ�������鸴��һ���µ������Թ���������
        strcpy(targetname[now],name[now]);
    }


    for(i=1; i<=*ftotal; i++) //�˴�ѭ����ָ������ȷ���ڼ�λ��
    {
        for(now=i+1; now<=*ftotal; now++) //�˴�ѭ����ָ���ڼ�λ�����������Ƚ�ȷ��������
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
        printf("����:");
        puts(targetname[now]);
        printf("ѧ��:%d,����:%d\n",targetnum[now],targetscore[now]);
    }
    printf("��ӡ���,���س����ص����˵�\n");
    while(getchar()!='\n');
    getchar();
}
/**********************************
** ������:Ascending
** �� ��: a,b
** a---���жϵ���1
** b---���жϵ���2
** �� ��: x---1||0
** x Ϊ 1, ��ʾ...a>=b
** x Ϊ 0, ��ʾ...a<b
** ��������:�����������ж�˭��С
************************************/
int Ascending(int a,int b)
{
    if(a>=b)return 1;
    else return 0;
}
/**********************************
** ������:Descending
** �� ��: a,b
** a---���жϵ���1
** b---���жϵ���2
** �� ��: x---1||0
** x Ϊ 1, ��ʾ...a<=b
** x Ϊ 0, ��ʾ...a>=b
** ��������:�����������ж�˭����
************************************/
int Descending(int a,int b)
{
    if(a<=b)return 1;
    else return 0;
}
/**********************************
** ������:SearchData
** �� ��: num[],score[],*ftotal��name[][],*print
** num---ѧ������
** score---��������
** *ftotal---ָ�룺ʵ������
** *print----����ָ�룺���ھ�������������Щ����
** �� �ã�PrintByNumber,PrintByname
** �� ��: void
** ��������:���ڲ����е����������ٸ���������ö�Ӧ��������ӡ����
************************************/
void SearchData(int num[],int score[],int *ftotal,char name[][MAXLEN],void (*print)(int targetnum[],int targetscore[],char targetname[][MAXLEN],int *ftotal))
{
    getchar();
    int i,now,temp,targetnum[*ftotal+1],targetscore[*ftotal+1];
    char targetname[N][MAXLEN];
    char tempname[MAXLEN];//���ڴ����Ҫ����������
    for(now=1; now<=*ftotal; now++)
    {
        targetnum[now]=num[now];
        targetscore[now]=score[now];//��ԭ�������鸴��һ���µ������Թ���������
        strcpy(targetname[now],name[now]);
    }
    for(i=1; i<=*ftotal; i++) //�˴�ѭ����ָ������ȷ���ڼ�λ��
    {
        for(now=i+1; now<=*ftotal; now++) //�˴�ѭ����ָ���ڼ�λ�����������Ƚ�ȷ��������
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


        printf("��ӡ���,���س����ص����˵�\n");
        while(getchar()!='\n');
        getchar();
}
/**********************************
** ������:StatisticAnalysis
** �� ��: score[],*ftotal
** score---��������
** *ftotal---ָ�룺ʵ������
** �� ��: void
** ��������:���ݷ�������������������ͨ���񲻼��������������
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
    printf("��������%d��,ռ������%.2f%%\n��������%d��,ռ������%.2f%%\n�е�����%d��,ռ������%.2f%%\n��������%d��,ռ������%.2f%%\n����������%d��,ռ������%.2f%%\n",perfect,(float)perfect/ *ftotal*100,great,(float)great/ *ftotal*100,good,(float)good/ *ftotal*100,bad,(float)bad/ *ftotal*100,miss,(float)miss/ *ftotal*100);
    printf("��ӡ���,���س����ص����˵�\n");
    while(getchar()!='\n');
    getchar();

}
/**********************************
** ������:Ascendingnum
** �� ��: num[],score[],*ftotal
** num---ѧ������
** score---��������
** *ftotal---ָ�룺ʵ������
** name[][]--�����ַ�������
** �� ��: void
** ��������:��ѧ�Ž������������
************************************/
void Ascendingnum(int num[],int score[],int *ftotal,char name[][MAXLEN])
{
    int i,now,temp,targetnum[*ftotal+1],targetscore[*ftotal+1];
    char targetname[N][MAXLEN];
    char tempname[MAXLEN];
    for(now=1; now<=*ftotal; now++)
    {
        targetnum[now]=num[now];
        targetscore[now]=score[now];//��ԭ�������鸴��һ���µ������Թ���������
        strcpy(targetname[now],name[now]);
    }
    for(i=1; i<=*ftotal; i++) //�˴�ѭ����ָ������ȷ���ڼ�λ��
    {
        for(now=i+1; now<=*ftotal; now++) //�˴�ѭ����ָ���ڼ�λ�����������Ƚ�ȷ��������
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
        printf("����:");
        puts(targetname[now]);
        printf("ѧ��:%d,����:%d\n",targetnum[now],targetscore[now]);
    }
    printf("��ӡ���,���س����ص����˵�\n");
    while(getchar()!='\n');
    getchar();
}
/**********************************
** ������:PrintByName
** �� ��: targetnum[],targetscore[],targetname[][],*ftotal
** targetnum---�����������к��ѧ������
** targetscore---�����������к�ķ�������
** *ftotal---ָ�룺ʵ������
** targetname[][]--�����������к�������ַ�������
** �� ��: void
** ��������:���������������������а��������������Ա����ʱ������ȷ�ķ�������
************************************/
void PrintByName(int targetnum[],int targetscore[],char targetname[][MAXLEN],int *ftotal)
{
    int resultscore,resultrank,now;
    int mark=0;//����Ƿ��ҵ�
    char searchname[MAXLEN];
    printf("����������Ѱ�ҵ�����:");
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
        printf("����:");
        puts(searchname);
        printf("��Ӧ�ķ�����:%d,������%d\n",resultscore,resultrank);
    }
    else printf("��Ǹû���ҵ������ҵ��ˣ���˶Ժ�����");

}
/**********************************
** ������:PrintByNumber
** �� ��: targetnum[],targetscore[],targetname[][],*ftotal
** targetnum---�����������к��ѧ������
** targetscore---�����������к�ķ�������
** *ftotal---ָ�룺ʵ������
** targetname[][]--�����������к�������ַ�������
** �� ��: void
** ��������:���������������������а���ѧ���������Ա����ʱ������ȷ�ķ�������
************************************/
void PrintByNumber(int targetnum[],int targetscore[],char targetname[][MAXLEN],int *ftotal)
{
    int resultdata,searchnum,resultrank,now;
    char resultname[MAXLEN];
    int mark = 0;
    printf("����������Ѱ�ҵ�ѧ��:");
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
        printf("��ѧ�Ŷ�Ӧ������:");
        puts(resultname);
        printf("��Ӧ�ķ�����:%d,������%d\n",resultdata,resultrank);
    }
    else printf("��Ǹû���ҵ������ҵ��ˣ���˶Ժ�����");
}
/**********************************
** ������:SortByName
** �� ��: num[],score[],name[][],*ftotal
** name----�����ַ�������
** score--��������
** *ftotal---ָ�룺ʵ������
** num----ѧ������
** �� ��: void
** ��������:�������ְ����ֵ������������
************************************/
void SortByName(int num[],int score[],char name[][MAXLEN],int *ftotal)
{
    int i,now,temp,targetnum[*ftotal+1],targetscore[*ftotal+1];
    char targetname[N][MAXLEN];
    char tempname[MAXLEN];
    for(now=1; now<=*ftotal; now++)
    {
        targetnum[now]=num[now];
        targetscore[now]=score[now];//��ԭ�������鸴��һ���µ������Թ���������
        strcpy(targetname[now],name[now]);
    }


    for(i=1; i<=*ftotal; i++) //�˴�ѭ����ָ������ȷ���ڼ�����
    {
        for(now=i+1; now<=*ftotal; now++) //�˴�ѭ����ָ���ڼ������������������Ƚ�
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
        printf("����:");
        puts(targetname[now]);
        printf("ѧ��:%d,����:%d\n",targetnum[now],targetscore[now]);
    }
    printf("��ӡ���,���س����ص����˵�\n");
}
