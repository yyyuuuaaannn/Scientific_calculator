#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#define LEN 100
#define PI 3.141593
#define E 2.718282

struct db
{
    int type;
    double cont;
};

void trans(char *, struct db *);
void calc(struct db *);

int main(void)
{
    char str[LEN];
    struct db in[LEN]={0};
    struct db * p;
    //int i;
    while(1)
    {
        system("cls");
        printf("科学计算器\n");
        gets(str);
        trans(str,in);
        
        // for(p=in,i=0;i<10;i++,p++)
        // {
        //     printf("%f   %d\n",p->cont,p->type);
        // }

        calc(in);

        // putchar('\n');
        // for(p=in,i=0;i<10;i++,p++)
        // {
        //     printf("%f   %d\n",p->cont,p->type);
        // }
        
        for(p=in;p<in+LEN;p++)
            if(p->type==1)
            {
               printf("=\n%f",p->cont);
               break;
            }
            
        getchar();
    }
}

void trans(char * str, struct db * in)
{
    char * p =str;
    int flag=0;
    in->type=2;
    in->cont=-1;
    in++;
    for(;p<str+LEN&&*p!='\0';p++)
    {
        if(isdigit(*p)&&!flag)
        {
            flag=1;
            in->type=1;
            in->cont=atof(p);
            in++;
        }
        else if(isalpha(*p))
        {
            flag=0;
            in->type=2;
            if(strstr(p,"pi")==p) in->cont=PI,in->type=1,in++;
            else if(strstr(p,"e")==p) in->cont=E,in->type=1,in++;
            else if(strstr(p,"sin")==p) in->cont=10,in++;
            else if(strstr(p,"cos")==p) in->cont=11,in++;
            else if(strstr(p,"tan")==p) in->cont=12,in++;
            else if(strstr(p,"log")==p) in->cont=13,in++;
            else if(strstr(p,"ln")==p) in->cont=14,in++;
        }
        else
        {
            switch(*p)
            {
                case '.': break;
                case '(': in->cont=-1;in->type=2;flag=0;in++;break;
                case ')': in->cont=-2;in->type=2;flag=0;in++;break;
                case '+': in->cont=1;in->type=2;flag=0;in++;break;
                case '-': in->cont=2;in->type=2;flag=0;in++;break;
                case '*': in->cont=3;in->type=2;flag=0;in++;break;
                case '/': in->cont=4;in->type=2;flag=0;in++;break;
                case '^': in->cont=5;in->type=2;flag=0;in++;break;
            }
        }
    }
    in->type=2;
    in->cont=-2;
}

void calc(struct db * in)
{
    struct db * p;
    int p1,p2;

    for(p=in+1;p<in+LEN&&!(p->type==2&&p->cont==-2);p++)
        if(p->type==2&&p->cont==-1)   
            calc(p);

    for(p=in+1;p<in+LEN&&!(p->type==2&&p->cont==-2);p++)
    {
        if(p->type==2)
        {
            switch((int)(p->cont))
            {
                case 10: 
                    for(p2=1;!(p+p2)->type;p2++);
                    p->cont=sin((p+p2)->cont);
                    p->type=1;
                    (p+p2)->type=0;
                    break;
                case 11: 
                    for(p2=1;!(p+p2)->type;p2++);
                    p->cont=cos((p+p2)->cont);
                    p->type=1;
                    (p+p2)->type=0;
                    break;
                case 12: 
                    for(p2=1;!(p+p2)->type;p2++);
                    p->cont=tan((p+p2)->cont);
                    p->type=1;
                    (p+p2)->type=0;
                    break;
                case 13: 
                    for(p1=1;!(p-p1)->type;p1++);
                    for(p2=1;!(p+p2)->type;p2++);
                    p->cont=log((p+p2)->cont)/log((p-p1)->cont);
                    p->type=1;
                    (p-p1)->type=0;
                    (p+p2)->type=0;
                    break;
                case 14: 
                    for(p2=1;!(p+p2)->type;p2++);
                    p->cont=log((p+p2)->cont);
                    p->type=1;
                    (p+p2)->type=0;
                    break;
            }
        }
    }
    
    for(p=in+1;p<in+LEN&&!(p->type==2&&p->cont==-2);p++)
    {
        if(p->type==2&&p->cont==2&&(p-1)->type==2)
        {
            for(p2=1;!(p+p2)->type;p2++);
            p->cont=-((p+p2)->cont);
            p->type=1;
            (p+p2)->type=0;
        }
    }
    
    for(p=in+1;p<in+LEN&&!(p->type==2&&p->cont==-2);p++)
    {
        if(p->type==2)
        {
            switch((int)(p->cont))
            {
                case 5: 
                    for(p1=1;!(p-p1)->type;p1++);
                    for(p2=1;!(p+p2)->type;p2++);
                    p->cont=pow(((p-p1)->cont),((p+p2)->cont));
                    p->type=1;
                    (p-p1)->type=0;
                    (p+p2)->type=0;
                    break;
                
            }
        }
    }

    for(p=in+1;p<in+LEN&&!(p->type==2&&p->cont==-2);p++)
    {
        if(p->type==2)
        {
            switch((int)(p->cont))
            {
                case 3: 
                    for(p1=1;!(p-p1)->type;p1++);
                    for(p2=1;!(p+p2)->type;p2++);
                    p->cont= ((p-p1)->cont) * ((p+p2)->cont);
                    p->type=1;
                    (p-p1)->type=0;
                    (p+p2)->type=0;
                    break;

                case 4: 
                    for(p1=1;!(p-p1)->type;p1++);
                    for(p2=1;!(p+p2)->type;p2++);
                    p->cont= ((p-p1)->cont) / ((p+p2)->cont);
                    p->type=1;
                    (p-p1)->type=0;
                    (p+p2)->type=0;
                    break;
                
            }
        }
    }

    for(p=in+1;p<in+LEN&&!(p->type==2&&p->cont==-2);p++)
    {
        if(p->type==2)
        {
            switch((int)(p->cont))
            {
                case 1: 
                    for(p1=1;!(p-p1)->type;p1++);
                    for(p2=1;!(p+p2)->type;p2++);
                    p->cont= ((p-p1)->cont) + ((p+p2)->cont);
                    p->type=1;
                    (p-p1)->type=0;
                    (p+p2)->type=0;
                    break;

                case 2: 
                    for(p1=1;!(p-p1)->type;p1++);
                    for(p2=1;!(p+p2)->type;p2++);
                    p->cont= ((p-p1)->cont) - ((p+p2)->cont);
                    p->type=1;
                    (p-p1)->type=0;
                    (p+p2)->type=0;
                    break;
                
            }
        }
    }

    in->type=0;
    for(p=in+1;p<in+LEN;p++)
        if(p->type==2&&p->cont==-2)
        {
            p->type=0;
            break;
        }
}
