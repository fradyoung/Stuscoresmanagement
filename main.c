/**************************
** ��Ŀ��:ѧ������ϵͳ
** ������:��һ�
** �� ��:2020/10/27
** �޸�����:2020/11/3
** �� ��:�๦�ܼ�¼����������һ��ѧ���ɼ������
** �� ��:V3.0
**------------------------
*************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXLEN 10
#define N 30    //�涨����������
#define CN 6    //�涨�����޿γ���
int num[N+1]= {0},score[N+1][CN+1]= {0}; //����ȫ������ʵ����������Ӧ����
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
    else printf("����Ƿ���\n");
    goto MENU;
    return 0;
}
/**********************************
** ������:record
** �� ��: num[],score[][],*ftotalmember��name[][MAXLEN],*ftotalcourse
** num---ѧ������
** score---������ά����
** *ftotalmember---ָ�룺ʵ������
** name[][]--�����ַ���
** *ftotalcourse--ָ�룺ʵ�ʿγ���
** �� ��: void
** ��������:���û�����
************************************/
void record(int num[],int score[][CN+1],int *ftotalmember,char name[][MAXLEN],int *ftotalcourse)
{
    int now,bin;
    printf("�����뱾��������:");
    scanf("%d",ftotalmember);
    getchar();
    printf("�����빲�м��ſγ�:");
    scanf("%d",ftotalcourse);
    while(getchar()!='\n');
    if(*ftotalmember>N||*ftotalmember<=0||*ftotalcourse>6||*ftotalcourse<=0)
    {
        printf("��������ȷ�İ༶�������߿γ���\n");
        return;
    }
    for(now=1; now<=*ftotalmember; now++)
    {
        printf("����������:");
        gets(name[now]);
        printf("������ѧ��:");
        scanf("%d",&num[now]);
        while(getchar()!='\n');
        for(bin=1;bin<=*ftotalcourse;bin++)
        {
            printf("�������%d�ſγ̵ĳɼ�",bin);
            scanf("%d",&score[now][bin]);
            getchar();
        }

    }
    printf("�������,���س����ص����˵�\n");
    getchar();
}
/**********************************
** ������:list
** �� ��: num[],score[],*ftotalmember��name[][]
** num---ѧ������
** score---������ά����
** *ftotalmember---ָ�룺ʵ������
** *ftotalcourse--ָ�룺ʵ�ʿγ���
** name[][]--�����ַ���
** �� ��: void
** ��������:�����û�����˳���������
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
        printf("�ܷ���%d,ƽ������%.2f\n",sumnow,(float)sumnow/ *ftotalcourse);
    }
    printf("��ӡ���,���س����ص����˵�\n");
    while(getchar()!='\n');
    getchar();
}
/**********************************
** ������:calcsumaveforcourse
** �� ��: num[],score[],*ftotalmember,*ftotalcourse
** num---ѧ������
** *ftotalcourse--ָ�룺ʵ�ʿγ���
** score---������ά����
** *ftotalmember---ָ�룺ʵ������
** �� ��: void
** ��������:����ÿ���γ��ּܷ�ƽ��ֵ�ٴ�ӡ����
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
        printf("�γ�%d�ܷ���%d,ƽ������%.2f\n",temp,sum,(float)sum/ *ftotalmember);
    }

    printf("��ӡ���,���س����ص����˵�\n");
    while(getchar()!='\n');
    getchar();
}
/**********************************
** ������:calcsumaveforstu
** �� ��: num[],score[],*ftotalmember,*ftotalcourse
** num---ѧ������
** *ftotalcourse--ָ�룺ʵ�ʿγ���
** score---������ά����
** *ftotalmember---ָ�룺ʵ������
** �� ��: void
** ��������:����ÿλѧ���ּܷ�ƽ��ֵ�ٴ�ӡ����
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
        printf("ѧ��ѧ��%d�ܷ���%d,ƽ������%.2f\n",num[temp],sum,(float)sum/ *ftotalcourse);
    }

    printf("��ӡ���,���س����ص����˵�\n");
    while(getchar()!='\n');
    getchar();
}
/**********************************
** ������:SelectionSort
** �� ��: num[],score[],*ftotalmember,*compare��name[][]
** num-------ѧ������
** score-----������ά����
** *ftotalmember---ָ�룺ʵ������
** *ftotalcourse--ָ�룺ʵ�ʿγ���
** *compare--����ָ�룬�����ж��������ǵ���
** name[][]--�����ַ�������
** �� ��: void
** ��������:��������������������
** ����ģ��:Ascending/Descending
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


    for(i=1; i<=*ftotalmember; i++) //�˴�ѭ����ָ������ȷ���ڼ�λ��
    {
        for(now=i+1; now<=*ftotalmember; now++) //�˴�ѭ����ָ���ڼ�λ�����������Ƚ�ȷ��������
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
        printf("����:");
        puts(targetname[now]);
        printf("ѧ��:%d,�ܷ�:%d\n",targetnum[now],targetsumscore[now]);
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
** �� ��: num[],score[],*ftotalmember��name[][],*print��*ftotalcourse
** num---ѧ������
** score---������ά����
** *ftotalmember---ָ�룺ʵ������
** *print----����ָ�룺���ھ�������������Щ����
** *ftotalcourse--ָ�룺ʵ�ʿγ���
** �� �ã�PrintByNumber,PrintByname
** �� ��: void
** ��������:���ڲ����е����������ٸ���������ö�Ӧ��������ӡ����
************************************/
void SearchData(int num[],int score[][CN+1],int *ftotalmember,int *ftotalcourse,char name[][MAXLEN],void (*print)(int targetnum[],int targetscore[][CN+1],char targetname[][MAXLEN],int *ftotalmember,int *ftotalcourse))
{
    getchar();
    int i,now,temp,bin,targetnum[*ftotalmember+1],targetscore[*ftotalmember+1][CN+1],targetsumscore[*ftotalmember+1];
    char targetname[N][MAXLEN];
    char tempname[MAXLEN];//���ڴ����Ҫ����������
    for(now=1; now<=*ftotalmember; now++)
    {
        targetnum[now]=num[now];
        for(bin=1,targetsumscore[now]=0;bin<=*ftotalcourse;bin++)
        {
            targetscore[now][bin]=score[now][bin];//��ԭ�������鸴��һ���µ������Թ���������
            targetsumscore[now] +=score[now][bin];
        }
        strcpy(targetname[now],name[now]);
    }
    for(i=1; i<=*ftotalmember; i++) //�˴�ѭ����ָ������ȷ���ڼ�λ��
    {
        for(now=i+1; now<=*ftotalmember; now++) //�˴�ѭ����ָ���ڼ�λ�����������Ƚ�ȷ��������
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


        printf("��ӡ���,���س����ص����˵�\n");
        while(getchar()!='\n');
        getchar();
}
/**********************************
** ������:StatisticAnalysis
** �� ��: score[],*ftotalmember
** score---������ά����
** *ftotalmember---ָ�룺ʵ������
** *ftotalcourse--ָ�룺ʵ�ʿγ���
** �� ��: void
** ��������:���ݷ�������������������ͨ���񲻼��������������
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
        printf("��%d�ſν������������%d��,ռ������%.2f%%\n��������%d��,ռ������%.2f%%\n�е�����%d��,ռ������%.2f%%\n��������%d��,ռ������%.2f%%\n����������%d��,ռ������%.2f%%\n",course,perfect,(float)perfect/ *ftotalmember*100,great,(float)great/ *ftotalmember*100,good,(float)good/ *ftotalmember*100,bad,(float)bad/ *ftotalmember*100,miss,(float)miss/ *ftotalmember*100);
        perfect=0,great=0,good=0,bad=0,miss=0;
    }
    printf("��ӡ���,���س����ص����˵�\n");
    while(getchar()!='\n');
    getchar();

}
/**********************************
** ������:Ascendingnum
** �� ��: num[],score[],*ftotalmember��*ftotalcourse
** num---ѧ������
** score---������ά����
** *ftotalmember---ָ�룺ʵ������
** *ftotalcourse--ָ�룺ʵ�ʿγ���
** name[][]--�����ַ�������
** �� ��: void
** ��������:��ѧ�Ž������������
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
            targetscore[now][bin]=score[now][bin];//��ԭ�������鸴��һ���µ������Թ���������
        }
        strcpy(targetname[now],name[now]);
    }
    for(i=1; i<=*ftotalmember; i++) //�˴�ѭ����ָ������ȷ���ڼ�λ��
    {
        for(now=i+1; now<=*ftotalmember; now++) //�˴�ѭ����ָ���ڼ�λ�����������Ƚ�ȷ��������
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
        printf("����:");
        puts(targetname[now]);
        printf("ѧ��:%d,",targetnum[now]);
        for(bin=1;bin<=*ftotalcourse;bin++)
        {
            printf("�γ�%d�ɼ���%d,",bin,targetscore[now][bin]);
        }
        printf("\n");
    }
    printf("��ӡ���,���س����ص����˵�\n");
    while(getchar()!='\n');
    getchar();
}
/**********************************
** ������:PrintByName
** �� ��: targetnum[],targetscore[],targetname[][],*ftotalmember,*ftotalcourse
** targetnum---�����������к��ѧ������
** targetscore---�����������к�ķ�����ά����
** *ftotalmember---ָ�룺ʵ������
** *ftotalcourse--ָ�룺ʵ�ʿγ���
** targetname[][]--�����������к�������ַ�������
** �� ��: void
** ��������:���������������������а��������������Ա����ʱ������ȷ�ķ�������
************************************/
void PrintByName(int targetnum[],int targetscore[][CN+1],char targetname[][MAXLEN],int *ftotalmember,int *ftotalcourse)
{
    int resultscore[CN+1],resultrank,now,temp;
    int mark=0;//����Ƿ��ҵ�
    char searchname[MAXLEN];
    printf("����������Ѱ�ҵ�����:");
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
        printf("����:");
        puts(searchname);
        for(temp=1;temp<=*ftotalcourse;temp++)
        {
            printf("�γ�%d����:%d\t",temp,resultscore[temp]);
        }
        printf("������%d\n",resultrank);
    }
    else printf("��Ǹû���ҵ������ҵ��ˣ���˶Ժ�����\n");

}
/**********************************
** ������:PrintByNumber
** �� ��: targetnum[],targetscore[],targetname[][],*ftotalmember,*ftotalcourse
** targetnum---�����������к��ѧ������
** targetscore---�����������к�ķ�����ά����
** *ftotalmember---ָ�룺ʵ������
** *ftotalcourse--ָ�룺ʵ�ʿγ���
** targetname[][]--�����������к�������ַ�������
** �� ��: void
** ��������:���������������������а���ѧ���������Ա����ʱ������ȷ�ķ�������
************************************/
void PrintByNumber(int targetnum[],int targetscore[][CN+1],char targetname[][MAXLEN],int *ftotalmember,int *ftotalcourse)
{
    int resultdata[*ftotalcourse+1],searchnum,resultrank,now,temp;
    char resultname[MAXLEN];
    int mark = 0;
    printf("����������Ѱ�ҵ�ѧ��:");
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
        printf("��ѧ�Ŷ�Ӧ������:");
        puts(resultname);
        for(temp=1;temp<=*ftotalcourse;temp++)
        {
            printf("�γ�%d����:%d\t",temp,resultdata[temp]);
        }
        printf("������%d\n",resultrank);
    }
    else printf("��Ǹû���ҵ������ҵ��ˣ���˶Ժ�����");
}
/**********************************
** ������:SortByName
** �� ��: num[],score[],name[][],*ftotalmember,*ftotalcourse
** name----�����ַ�������
** score--������ά����
** *ftotalmember---ָ�룺ʵ������
** *ftotalcourse--ָ�룺ʵ�ʿγ���
** num----ѧ������
** �� ��: void
** ��������:�������ְ����ֵ������������
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
            targetscore[now][bin]=score[now][bin];//��ԭ�������鸴��һ���µ������Թ���������
        }
        strcpy(targetname[now],name[now]);
    }


    for(i=1; i<=*ftotalmember; i++) //�˴�ѭ����ָ������ȷ���ڼ�����
    {
        for(now=i+1; now<=*ftotalmember; now++) //�˴�ѭ����ָ���ڼ������������������Ƚ�
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
        printf("����:");
        puts(targetname[now]);
        printf("ѧ��:%d,",targetnum[now]);
        for(bin=1;bin<=*ftotalcourse;bin++)
        {
            printf("�γ�%d�ɼ���%d,",bin,targetscore[now][bin]);
        }
        printf("\n");
    }
    getchar();
    printf("��ӡ���,���س����ص����˵�\n");
}
