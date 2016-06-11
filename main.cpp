#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <fstream>
#include <stack>

using namespace std;
//���ű�ṹ
typedef struct kt
{
    char key_name[10];
    int key;
    char kind[10];
} KT;
KT x[100];

//ʹ��������ʷ��������Ľ��
struct L
{
    int t;//����
    char n[10];/*name*/
    int v;/*value*/
    L *next=NULL;
};
typedef struct L NODE;
NODE *W=new(NODE);
//������
typedef struct action_table
{
    char ch[100];
} AT;
AT a_table[96][36];

//goto��
typedef struct goto_table
{
    char ch2[100];
} GT;
GT g_table[96][15];


void make_table (char s[30])//����Ϊѡ��ʹ�õ��ļ������Զ������ļ����д���
{
    int i=0,j=0,k=0,n;
    char cl[1000],tmp[300],file[30];
    sprintf(file,"%s.txt",s);
    ifstream infile(file);
    while (infile.getline(cl,1000))
    {
        i=0;
        n=0;
        //puts(cl);
        while (i<strlen(cl))
        {
            j=0;
            while (cl[i]!='.'&&cl[i]!='{'&&cl[i]!='}')
                tmp[j++]=cl[i++];
            if (cl[i]=='.'||cl[i]=='{'||cl[i]=='}')
                i++;
            tmp[j]='\0';
            if (strcmp(tmp,"")!=0)
            {
                if (strcmp(file,"result_action.txt")==0)
                    strcpy(a_table[k][n++].ch,tmp);
                else
                    strcpy(g_table[k][n++].ch2,tmp);
                //puts(xu[k][n-1].ch);
            }
        }
        //printf("%d\n",n);
        /*for (i=0;i<n;i++)
        {
            if (strcmp(file,"result_action.txt")==0)
                printf("%s   ",a_table[k][i].ch);
            else
                printf("%s   ",g_table[k][i].ch2);
        }
        printf("\n%d\n\n",k);*/
        k++;
    }
}

void insert_to_list(int u,char z[10],int y) //�ڴʷ������������ĩβ���һ��
{
    NODE *p=NULL;
    NODE *tail=W;//�����ҵ�����б�β��
    if (tail==NULL)//��ʼΪ�յ����
    {
        tail->t=u;
        strcpy(tail->n,z);
        tail->v=y;
        tail->next=NULL;
    }
    else//�ҵ���β�����������
    {
        p=new(NODE);
        p->t=u;
        strcpy(p->n,z);
        p->v=y;
        p->next=NULL;
        while(tail->next!=NULL)
            tail=tail->next;
        tail->next=p;
    }
}

void print(NODE *pnew)
{
    while(pnew!=NULL)
    {
        printf("(%d,%s,%d)\n",pnew->t,pnew->n,pnew->v);
        pnew=pnew->next;
    }
}
// �ʷ�������±��Ӧ�б��룬�����Ƿ���ȡ���ֵ��ַ���
char *ID[36]= {"prog","id","semi","proc","begin","integer","real","array","of","record"
               ,"num","end","if","then","else","or","and","not","while","do","endif","endwhile","read",
               "write","[","]",":",",",":=","+","-","*","/","(",")","$"
              };

int find_in_key_table(char * str){  //�ڲ�����ű��ǿ��Ƿ��Ѿ�����
    int i = 0;
    while(strcmp(x[i].key_name , "")){
        if(!strcmp(x[i].key_name , str))
            return 1;
        i ++;
    }
    return 0;
}
int lexical() //�ʷ�����
{
    //FILE *fp1,*fp2;
    char cl[1000],token[30];
    int i=0,k=0,j=0,sum=0,flag=0,m=0;
    float fd=0;
    ifstream infile("a.txt");
    while (infile.getline(cl,1000))//ÿ�ζ�һ�н��뻺��
    {
        i=0;
        while (i<strlen(cl))
        {
            flag=0;
            k=0;
            if (cl[i]==' ')
            {
                flag=0;
                for (j=0; j<30; j++)
                    token[j]='\0';
            }
            else
            {
                if (isalpha(cl[i]))//�����ַ�ʱ
                {
                    while (isalnum(cl[i]))
                        token[k++]=cl[i++];//���浽ĿǰΪֹ�ķǱ������ַ���
                    token[k++]='\0';
                    i--;
                    for (j=0; j<24; j++)
                    {
                        if (!strcmp(token,ID[j]))//�Ƚϲ鿴�ǲ���prog�ȹؼ���
                        {
                            flag=1;
                            //printf("(%s,0)\n",token);
                            insert_to_list(j,token,0);
                            break;
                        }
                    }
                    if (flag==0)//���ǹؼ���
                    {
                        //printf("(ID,%s)\n",token);
                        insert_to_list(1,token,0);
                        if(! find_in_key_table(token)){
                            strcpy(x[m].key_name,token);
                            m ++;
                        }
                    }
                }
                else
                {
                    if (isdigit(cl[i])) // �������֣��᷵�ظ��������
                    {
                        sum=0;
                        fd=0;
                        int t_p = 0;
                        while(isdigit(cl[i]))
                        {
                            token[t_p] = cl[i];
                            t_p++;
                            i++;
                        }
                        if (cl[i]=='.')
                        {
                            token[t_p] = cl[i];
                            t_p++;
                            i++;
                            while(isdigit(cl[i]))
                            {
                                token[t_p] = cl[i];
                                t_p++;
                                i++;
                            }
                            i--;
                            token[t_p] = '\0';
                            fd = atof(token);
//                            printf("(REAL,%f)\n",fd);
                            insert_to_list(10,token,fd);//����num����
                        }
                        else
                        {
                            i--;
                            token[t_p] = '\0';
                            sum = atoi(token);
//                            printf("(INT,%d)\n",sum);
                            insert_to_list(10,token,sum);//����num����
                        }
                    }
                    else switch(cl[i])
                        {
                        case '[':
                            //printf("[\n");
                            insert_to_list(24,"[",0);
                            break;
                        case ']':
                            //printf("]\n");
                            insert_to_list(25,"]",0);
                            break;
                        case ':':
                            if (cl[i+1]=='=')
                            {
                                i++;
                                //printf(":=\n");
                                insert_to_list(28,":=",0);
                            }
                            else
                            {
                                //printf(":\n");
                                insert_to_list(26,":",0);
                            }
                            break;
                        case ',':
                            // printf(",\n");
                            insert_to_list(27,",",0);
                            break;
                        case '+':
                            //printf("+\n");
                            insert_to_list(29,"+",0);
                            break;
                        case '-':
                            //printf("-\n");
                            insert_to_list(30,"-",0);
                            break;
                        case '*':
                            //printf("*\n");
                            insert_to_list(31,"*",0);
                            break;
                        case '/':
                            if (cl[i+1]=='/')
                                i=strlen(cl);
                            else
                                //printf("/\n");
                                insert_to_list(32,"/",0);
                            break;
                        case '(':
                            //printf("(\n");
                            insert_to_list(33,"(",0);
                            break;
                        case ')':
                            //printf(")\n");
                            insert_to_list(34,")",0);
                            break;
                        case '$':
                            //printf("$\n");
                            insert_to_list(35,"$",0);
                            break;
                        default :
                            printf("%d is error\n",cl[i]);
                            break;
                        }
                }
            }
            i++;
        }
    }
    return 0;
}
int is_num(char * s){//�ж�һ���ַ����ǲ���ȫ�����֣��������ɻ�����ж��Ƿ�Ϊ������
    int l = strlen(s);
//    cout<<"=========debug======\n"<<s<<endl;
    for(int i = 0;i < l; i++){
        if(!isdigit(s[i])){
//            cout<<"=========debug======\n"<<s<<endl;
            return 0;
        }
    }
    return 1;
}

void semantic(NODE *pn)
{
    string xustring;
    stack<int> ss;//״̬ջ
    stack<string> ks; //����ջ
    stack<NODE *> kss;//����ջ������ջ����Ӧλ�ô洢��Ӧ���ŵ�type��name��value��
    int k=0,l=0,sum=0,flag,j=1,m=1,cnt=0,f=0,xl=0,tr=0,fal=0,flagif=0,flagthen=0,flagelse=0,flagwhile=0,flagdo=0,flagendwhile=0;
    int fal_while = 0,tr_while = 0;
    char tmp[10],T[100],f1[30];
    string asm_code = "";//���ڱ������м����
    string asm_declr = "";//�����������������
    char asm_tem[200];
    int i = 0;
    ofstream file("b.txt");
    NODE *temp=NULL,*E=NULL,*H=NULL,*F=NULL,*Left=NULL,*W=NULL;
    temp =new (NODE);
    strcpy(temp->n,"$");
    temp->t=35;//�½�ͷ�ڵ㣬��ʹ������Ϊ"$"����Ϊջ�׷���
    temp->v=0;
    temp->next=pn;
    ss.push(0);//�ֱ�ѹ��ջ�׷��źͳ�ʼ״̬
    ks.push(xustring.assign("$"));
    kss.push(temp);
    tmp[0]='\0';
    while(pn!=NULL)
    {
        l=0;
        if (tmp[0]=='\0')
        {
            if (strcmp(a_table[k][pn->t].ch,"accept")==0)
            {
                printf("accept\n");
                break;
//                exit(0);
            }
            flag=strlen(a_table[k][pn->t].ch);
            strcpy(T,a_table[k][pn->t].ch);//T�д�Ŷ�����ǰ�Ķ�����kΪ״̬
            if (flag<3)//������ǹ�Լ
            {
                if (!strcmp(ks.top().c_str(),"if")&&flagif==0)
                {
                    flagif=1;
                    file<<"\n";
                }
                if (!strcmp(ks.top().c_str(),"then")&&flagthen==0)
                {
                    flagthen=1;
                    sprintf(f1,"goto tr%d\ngoto fal%d\ntr%d:",tr,fal,tr);
                    file<<f1<<endl;
                    sprintf(asm_tem,"jnz\t.tr%d\njmp\t.fal%d\n.tr%d:\n",tr,fal,tr);
                    asm_code += asm_tem;
                }
                if (!strcmp(ks.top().c_str(),"else")&&flagelse==0)
                {
                    flagelse=1;
                    sprintf(f1,"goto next%d\n fal%d:",tr,fal);
                    file<<f1<<endl;
                    sprintf(asm_tem,"jmp\t.next%d\n.fal%d:\n",tr,fal);
                    asm_code += asm_tem;
                }
                if (!strcmp(ks.top().c_str(),"while")&&flagwhile==0)
                {
                    flagwhile=1;
                    file<<"\nL"<<fal_while<<":"<<endl;
                    sprintf(f1,"\nL%d:",fal_while);
                    sprintf(asm_tem,".L%d:\n",fal_while);
                    asm_code += asm_tem;
                }
                if (!strcmp(ks.top().c_str(),"do")&&flagdo==0)
                {
                    flagdo=1;
                    sprintf(f1,"goto w_tr%d\ngoto w_fal%d\nw_tr%d:",tr_while,fal_while,tr_while);
                    file<<f1<<endl;
                    sprintf(asm_tem,"jnz\t.w_tr%d\njmp\t.w_fal%d\n.w_tr%d:\n",tr_while,fal_while,tr_while);
                    asm_code += asm_tem;
                }
                ks.push(xustring.assign(ID[pn->t]));//ѹ�뵱ǰ�ؼ��֣��ķ��ս����
                kss.push(pn);
            }
        }
        else//����goto�������tmp�ǹ�Լ��������
        {
            if (strcmp(tmp,"D")==0)
            {
                flag=strlen(g_table[ss.top()][0].ch2);
                strcpy(T,g_table[ss.top()][0].ch2);
            }
            if (strcmp(tmp,"List")==0)
            {
                flag=strlen(g_table[ss.top()][1].ch2);
                strcpy(T,g_table[ss.top()][1].ch2);
            }
            if (strcmp(tmp,"T")==0)
            {
                flag=strlen(g_table[ss.top()][2].ch2);
                strcpy(T,g_table[ss.top()][2].ch2);
            }
            if (strcmp(tmp,"C")==0)
            {
                flag=strlen(g_table[ss.top()][3].ch2);
                strcpy(T,g_table[ss.top()][3].ch2);
            }
            if (strcmp(tmp,"S")==0)
            {
                flag=strlen(g_table[ss.top()][4].ch2);
                strcpy(T,g_table[ss.top()][4].ch2);
            }
            if (strcmp(tmp,"A")==0)
            {
                flag=strlen(g_table[ss.top()][5].ch2);
                strcpy(T,g_table[ss.top()][5].ch2);
            }
            if (strcmp(tmp,"B")==0)
            {
                flag=strlen(g_table[ss.top()][6].ch2);
                strcpy(T,g_table[ss.top()][6].ch2);
            }
            if (strcmp(tmp,"Left")==0)
            {
                flag=strlen(g_table[ss.top()][7].ch2);
                strcpy(T,g_table[ss.top()][7].ch2);
            }
            if (strcmp(tmp,"E")==0) //{D.List.T.C.S.A.B.Left.E.H.F.I.L.W.plist}.
            {
                flag=strlen(g_table[ss.top()][8].ch2);
                strcpy(T,g_table[ss.top()][8].ch2);
            }
            if (strcmp(tmp,"H")==0)
            {
                flag=strlen(g_table[ss.top()][9].ch2);
                strcpy(T,g_table[ss.top()][9].ch2);
            }
            if (strcmp(tmp,"F")==0)
            {
                flag=strlen(g_table[ss.top()][10].ch2);
                strcpy(T,g_table[ss.top()][10].ch2);
            }
            if (strcmp(tmp,"I")==0)
            {
                flag=strlen(g_table[ss.top()][11].ch2);
                strcpy(T,g_table[ss.top()][11].ch2);
            }
            if (strcmp(tmp,"L")==0)
            {
                flag=strlen(g_table[ss.top()][12].ch2);
                strcpy(T,g_table[ss.top()][12].ch2);
            }
            if (strcmp(tmp,"W")==0)
            {
                flag=strlen(g_table[ss.top()][13].ch2);
                strcpy(T,g_table[ss.top()][13].ch2);
            }
            if (strcmp(tmp,"plist")==0)
            {
                flag=strlen(g_table[ss.top()][14].ch2);
                strcpy(T,g_table[ss.top()][14].ch2);
            }
        }
        if (flag<3)//�ǹ�Լ������״̬��ת
        {
            if (tmp[0]!='\0')//��ʾ�ղ��Ǵ�goto��������ģ���Ϊtmp���󲿣�û��Լ��Ϊ��
            {
                printf ("goto %s\n",T);
                tmp[0]='\0';
            }
            else
            {
                printf ("shift %s\n",T);
                pn=pn->next;
            }
            while (T[l]!='\0')//����T�����״̬�ţ������ٶȿ�һ��
            {
                m=1;
                for (j=1; j<flag-l; j++)
                    m=m*10;
                sum+= (T[l]-'0')*m;
                l++;
            }
            ss.push(sum);
            k=sum;//�ñ䵱ǰ״̬
            sum=0;
        }
        else//��Լ̬
        {
            printf ("reduce %s\n",T);
            while (T[l]!='\0')
            {
                if (f==0)
                {
                    while (T[l]!=' ')
                    {
                        tmp[l]=T[l]; //��tmp�д洢����ʽ�󲿣�tmp[0]��ʱ��Ϊ0
                        l++;
                    }
                    tmp[l]='\0';
                    f=1;
                }
                else
                {
                    if (T[l]==' ')  //��¼����ʽ�Ҳ����Ÿ���
                        cnt++;
                    if (T[l]=='\305')
                        cnt=0;
                    l++;
                }
            }
            f=0;
            H=new(NODE);
            F=new(NODE);
            E=new(NODE);
            Left=new(NODE);
            W=new(NODE);
            for (j=0; j<cnt-1; j++) //��������ջ�б���Լ�Ĳ��֣�����ջ���ҵ���Ӧ���ķ���������������Ӧ��λ��
            {
                if (!strcmp(T,"W -> E")) // ����һ�����ȵĲ���ʽ������ֱ�Ӹ�������
                    temp=kss.top();
                if (!strcmp(T,"F -> num"))
                    temp=kss.top();
                if (!strcmp(T,"Left -> id"))
                    temp=kss.top();
                if (!strcmp(T,"F -> id"))
                    temp=kss.top();
                if (!strcmp(T,"E -> H"))
                    temp=kss.top();
                if (!strcmp(T,"F -> ( E )"))
                {
                    if (j==1)
                        temp=kss.top();
                }
                if (!strcmp(T,"H -> F"))
                    temp=kss.top();
                if (!strcmp(T,"H -> H / F"))
                {
                    if (j==0)
                        F=kss.top();
                    if (j==2)
                        H=kss.top();
                }
                if (!strcmp(T,"H -> H * F"))
                {
                    if (j==0)
                        F=kss.top();
                    if (j==2)
                        H=kss.top();
                }
                if (!strcmp(T,"E -> E - H"))
                {

                    if (j==0)
                        H=kss.top();
                    if (j==2)
                        E=kss.top();
                }
                if (!strcmp(T,"E -> E + H"))
                {
                    if (j==0)
                        H=kss.top();
                    if (j==2)
                        E=kss.top();
                }
                if (!strcmp(T,"S -> Left := E semi"))
                {
                    if (j==1)
                        E=kss.top();
                    if (j==3)
                        Left=kss.top();
                }
                ks.pop();
                ss.pop();
                kss.pop();
            }
            cnt=0;
            //�������Ǹ��ݲ���������Ӧ�Ķ�������xl����ʱ������
            char new_var[100] = "T";
            if (!strcmp(T,"E -> E - H"))
            {
                sprintf(f1,"T%d:=%s-%s",xl,E->n,H->n);
                file<<f1<<endl;
//                sprintf(asm_tem,"movl\t$%s,\t$T%d\nsubl\t$%s,\t$T%d\n",E->n,xl,H->n,xl);
                if(is_num(E->n)){//�����������
                    strcpy(asm_tem,"$");
                    strcat(asm_tem,E->n);
                    strcpy(E->n,asm_tem);
                }
                if(is_num(H->n)){//�����������
                    strcpy(asm_tem,"$");
                    strcat(asm_tem,H->n);
                    strcpy(H->n,asm_tem);
                }
                sprintf(asm_tem,"movl\t%s,\t%%eax\nsubl\t%s,\t%%eax\nmovl\t%%eax,\tT%d\n",E->n,H->n,xl);
                asm_code += asm_tem;
                itoa(xl++,temp->n,10);
                strcat(new_var,temp->n);
                strcpy(temp->n,new_var);
//                strcat(temp->n,"T");//�ַ���ƴ�ӣ��ѵ�ǰ�����ֱ�Ϊnum + T����ʾ��ʱ����
                temp->v=E->v - H->v;
                temp->t=E->t;
            }
            if (!strcmp(T,"E -> E + H"))
            {
                sprintf(f1,"T%d:=%s+%s",xl,E->n,H->n);
                file<<f1<<endl;
//                sprintf(asm_tem,"movl\t$%s,\t$T%d\naddl\t$%s,\t$T%d\n",E->n,xl,H->n,xl);
                if(is_num(E->n)){//�����������
                    strcpy(asm_tem,"$");
                    strcat(asm_tem,E->n);
                    strcpy(E->n,asm_tem);
                }
                if(is_num(H->n)){//�����������
                    strcpy(asm_tem,"$");
                    strcat(asm_tem,H->n);
                    strcpy(H->n,asm_tem);
                }
                sprintf(asm_tem,"movl\t%s,\t%%eax\naddl\t%s,\t%%eax\nmovl\t%%eax,\tT%d\n",E->n,H->n,xl);
                asm_code += asm_tem;
                itoa(xl++,temp->n,10);
                strcat(new_var,temp->n);
                strcpy(temp->n,new_var);
//                strcat(temp->n,"T");
                temp->v=E->v + H->v;
                temp->t=E->t;
            }
            if (!strcmp(T,"H -> H * F"))
            {
                sprintf(f1,"T%d:=%s*%s",xl,H->n,F->n);
                file<<f1<<endl;
//                sprintf(asm_tem,"movl\t$%s,\t$T%d\nmull\t$%s,\t$T%d\n",H->n,xl,F->n,xl);
                if(is_num(F->n)){//�����������
                    strcpy(asm_tem,"$");
                    strcat(asm_tem,F->n);
                    strcpy(F->n,asm_tem);
                }
                if(is_num(H->n)){//�����������
                    strcpy(asm_tem,"$");
                    strcat(asm_tem,H->n);
                    strcpy(H->n,asm_tem);
                }
                sprintf(asm_tem,"movl\t%s,\t%%eax\nmull\t%s\nmovl\t%%eax,\tT%d\n",H->n,F->n,xl);
                asm_code += asm_tem;
                itoa(xl++,temp->n,10);
                strcat(new_var,temp->n);
                strcpy(temp->n,new_var);
//                strcat(temp->n,"T");
                temp->v = H->v * F->v;
                temp->t = F->t;
            }
            if (!strcmp(T,"H -> H / F"))
            {
                sprintf(f1,"T%d:=%s/%s",xl,H->n,F->n);
                file<<f1<<endl;
//                sprintf(asm_tem,"movl\t$%s,\t$T%d\ndivl\t$%s,\t$T%d\n",H->n,xl,F->n,xl);
                if(is_num(H->n)){//�����������
                    strcpy(asm_tem,"$");
                    strcat(asm_tem,H->n);
                    strcpy(H->n,asm_tem);
                }
                if(is_num(F->n)){//�����������
                    strcpy(asm_tem,"$");
                    strcat(asm_tem,F->n);
                    strcpy(F->n,asm_tem);
                }
                sprintf(asm_tem,"movl\t%s,\t%%eax\ndivl\t%s\nmovl\t%%eax,\tT%d\n",H->n,F->n,xl);
                asm_code += asm_tem;
                itoa(xl++,temp->n,10);
                strcat(new_var,temp->n);
                strcpy(temp->n,new_var);
//                strcat(temp->n,"T");
                if (F->v!=0)
                    temp->v= H->v / F->v;
                temp->t= H->t;
            }
            if (!strcmp(T,"S -> Left := E semi"))
            {
                sprintf(f1,"%s:=%s",Left->n,E->n);
                file<<f1<<endl;
                if(is_num(E->n)){//�����������
                    strcpy(asm_tem,"$");
                    strcat(asm_tem,E->n);
                    strcpy(E->n,asm_tem);
                }
                sprintf(asm_tem,"movl\t%s,\t%%eax\nmovl\t%%eax,\t%s\n",E->n,Left->n);
                asm_code += asm_tem;
            }
            if (!strcmp(T,"W -> E")) // ��Լ������ת����
            {
                W=temp;
                sprintf(f1,"if %s ",W->n);
                file<<f1;
                sprintf(asm_tem,"movl\t0,\t%%eax\ncmpl   %s, %%eax\n",W->n);
                asm_code += asm_tem;
            }
            if (!strcmp(T,"S -> while W do S endwhile"))
            {
                sprintf(f1,"goto L%d\nw_fal%d:",fal_while,fal_while);
                flagwhile = 0;
                flagdo = 0;
                flagendwhile = 0;
                file<<f1<<endl;
                sprintf(asm_tem,"jnz .L%d\n.w_fal%d:\n",fal_while,fal_while);
                asm_code += asm_tem;
                tr_while++;
                fal_while++;
            }
            if (!strcmp(T,"S -> if W then S else S endif"))
            {
                sprintf(f1,"next%d:",tr);
                file<<f1<<endl;
                asm_code += ".";
                asm_code += f1;
                asm_code += "\n";
                flagif = 0;
                flagthen = 0;
                tr++;
                fal++;
            }
            if (!strcmp(T,"S -> if W then S endif"))
            {
                sprintf(f1,"fal%d:",fal);
                file<<f1<<endl;
                asm_code += ".";
                asm_code += f1;
                asm_code += "\n";
                flagif = 0;
                flagthen = 0;
                tr++;
                fal++;
            }
            H=NULL;
            F=NULL;
            E=NULL;
            Left=NULL;
            ks.push(xustring.assign(tmp));//ѹ�����ʽ��
            kss.push(temp);//ѹ����Ӧ������ֵ
        }
    }
    file.close();
    //AT&T��ಿ��
    //xlΪ��ʱ�����ĸ���
    //ԭ�����еı������Լ���ʹ��Դ���������
    ofstream asm_file("asm.txt");
    while(strcmp(x[i].key_name , "")){ //����һ��Դ����ĵ�Ч
        sprintf(asm_tem,".lcomm\t%s,\t4\n",x[i].key_name);//��Ϊ��֪����ʲô
        asm_declr += asm_tem;
        i ++;
    }
    for(i = 0;i < xl;i++){
        sprintf(asm_tem,".lcomm\tT%d,\t4\n",i);
        asm_declr += asm_tem;
    }
    asm_file<<".section .bss\n";
    asm_file<<asm_declr;
    asm_file<<".section .text\n";
    asm_file<<asm_code;
    asm_file.close();
}

int main()
{
    lexical();
    print(W->next);
    //��ӡ���ű�
//    for(int i = 0; i < 100;i ++){
//        if(strcmp(x[i].key_name , ""))
//            cout<<"id: "<<x[i].key_name<<endl;
//    }
    printf("\n��ʼ�﷨�Ƶ����룺\n");
    make_table("result_action");
    make_table("result_goto");
    semantic(W->next);
    while(W!=NULL)
    {
        delete W;
        W=W->next;
    }
    return 0;
}
