#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <map>
#include <stdio.h>

using namespace std;
enum Instr_t { RM, RR, RI, J};
class Instruct
{
public:
    Instruct(string n, Instr_t t, int c)
    {name = n;type = t;code=c;}
    Instruct(){}
    string name;
    Instr_t type;
    unsigned int code;
};
void CodeToMem(int *m, unsigned int &c)
{
    static int pos = 0;
    m[pos]=c;
    pos++;
}
string ReadInstructFrommem(unsigned int c, map<unsigned int, Instruct> &I)
{
    string s;
    unsigned int codeInstr = 0;
    codeInstr = c>>24;
    return I[codeInstr].name;
}
int reg_to_code(string &s)
{
    unsigned int a=0;
    if(s=="r0," ||s=="r0") a = 0;
    if(s=="r1,"||s=="r1") a = 1;
    if(s=="r2,"||s=="r2") a = 2;
    if(s=="r3,"||s=="r3") a = 3;
    if(s=="r4,"||s=="r4") a = 4;
    if(s=="r5,"||s=="r5") a = 5;
    if(s=="r6,"||s=="r6") a = 6;
    if(s=="r7,"||s=="r7") a = 7;
    if(s=="r8,"||s=="r8") a = 8;
    if(s=="r9,"||s=="r9") a = 9;
    if(s=="r10,"||s=="r10") a = 10;
    if(s=="r11,"||s=="r11") a = 11;
    if(s=="r12,"||s=="r12") a = 12;
    if(s=="r13,"||s=="r13") a = 13;
    if(s=="r14,"||s=="r14") a = 14;
    if(s=="r15,"||s=="r15") a = 15;
    if(s=="flags") a = 16;
    return a;
}
void fill_with_instructions(map<string,Instruct> &m)
{
    m["halt"]=Instruct("halt",Instr_t::RI,0);
    m["syscall"]=Instruct("syscall",Instr_t::RI,1);
    m["add"]=Instruct("add",Instr_t::RR,2);
    m["addi"]=Instruct("addi",Instr_t::RI,3);
    m["sub"]=Instruct("sub",Instr_t::RR,4);
    m["subi"]=Instruct("subi",Instr_t::RI,5);
    m["mul"]=Instruct("mul",Instr_t::RR,6);
    m["muli"]=Instruct("muli",Instr_t::RI,7);
    m["div"]=Instruct("div",Instr_t::RR,8);
    m["divi"]=Instruct("divi",Instr_t::RI,9);
    m["lc"]=Instruct("lc",Instr_t::RI, 12);
    m["shl"]=Instruct("shl",Instr_t::RR, 13);
    m["shli"]=Instruct("shli",Instr_t::RI, 14);
    m["shr"]=Instruct("shr",Instr_t::RR, 15);
    m["shri"]=Instruct("shri",Instr_t::RI, 16);
    m["and"]=Instruct("and",Instr_t::RR, 17);
    m["andi"]=Instruct("andi",Instr_t::RI, 18);
    m["or"]=Instruct("or",Instr_t::RR, 19);
    m["ori"]=Instruct("ori",Instr_t::RI, 20);
    m["xor"]=Instruct("xor",Instr_t::RR, 21);
    m["xori"]=Instruct("xori",Instr_t::RI, 22);
    m["not"]=Instruct("not",Instr_t::RI, 23);
    m["mov"]=Instruct("mov",Instr_t::RR, 24);
    m["addd"]=Instruct("addd",Instr_t::RR, 32);
    m["subd"]=Instruct("subd",Instr_t::RR, 33);
    m["muld"]=Instruct("muld",Instr_t::RR, 34);
    m["divd"]=Instruct("divd",Instr_t::RR, 35);
    m["itod"]=Instruct("itod",Instr_t::RR, 36);
    m["dtoi"]=Instruct("dtoi",Instr_t::RR, 37);
    m["push"]=Instruct("push",Instr_t::RI, 38);
    m["pop"]=Instruct("pop",Instr_t::RI, 39);
    m["call"]=Instruct("call",Instr_t::RR, 40);
    m["calli"]=Instruct("calli",Instr_t::J, 41);
    m["ret"]=Instruct("ret",Instr_t::J, 42);
    m["cmp"]=Instruct("cmp",Instr_t::RR, 43);
    m["cmpi"]=Instruct("cmpi",Instr_t::RI, 44);
    m["cmpd"]=Instruct("cmpd",Instr_t::RR, 45);
    m["jmp"]=Instruct("jmp",Instr_t::J, 46);
    m["jne"]=Instruct("jne",Instr_t::J, 47);
    m["jeq"]=Instruct("jeq",Instr_t::J, 48);
    m["jle"]=Instruct("jle",Instr_t::J, 49);
    m["jl"]=Instruct("jl",Instr_t::J, 50);
    m["jge"]=Instruct("jge",Instr_t::J, 51);
    m["jg"]=Instruct("jg",Instr_t::J, 52);
    m["load"]=Instruct("load",Instr_t::RM, 64);
    m["store"]=Instruct("store",Instr_t::RM, 65);
    m["load2"]=Instruct("load2",Instr_t::RM, 66);
    m["store2"]=Instruct("store2",Instr_t::RM, 67);
    m["loadr"]=Instruct("loadr",Instr_t::RR, 68);
    m["storer"]=Instruct("storer",Instr_t::RR, 69);
    m["loadr2"]=Instruct("loadr2",Instr_t::RR, 70);
    m["storer2"]=Instruct("storer2",Instr_t::RR, 71);
    return;
}
void FillReversMap(map<string,Instruct> &base, map<unsigned int,Instruct> &m)
{
    for(auto c: base){m[c.second.code]=c.second;}
}
void changepartofcode(unsigned int &code, int pos, int length, unsigned int i)
{
    unsigned int mask;
    mask = ~(((1<<length)-1)<<pos);
    i&=mask;
    code|=(i<<pos);
}
string outcode(int &c)
{
    string s = "";
    for(int i = 31; i >=0; i--)
    {
        int bit = (c>>i)&1;
        s+=to_string(bit);
    }
    return s;
}
int int_from_20(int inp)
{
    int a=0;
    int d = (inp>>19)&1;
    if(d)
    { a=-1; a=a<<20; a|=inp; }
    else
    {a|=inp;}
    return a;
}
int int_from_16(int inp)
{
    int a=0;
    int d = (inp>>15)&1;
    if(d)
    { a=-1; a=a<<16; a|=inp; }
    else
    {a|=inp;}
    return a;
}
void DoInstruct(int &c, int *regs, int *mem)
{
    unsigned int code;
    code = c>>24;
    unsigned int reg;
    unsigned int reg2;
    FILE *f;
    int op;
    union u
        {
            int a[2];
            double b;
        };
    u d1;
    u d2;
    switch (code)
    {
    case 0:exit(0);break;
    case 1:
        {
        reg = (c>>20)&(0xF);
        op =int_from_20(c&0xFFFFF);
            switch (op)
            {

                case 0: exit(0);break;
                case 100: cin>>regs[reg]; regs[15]+=1; break;
                case 101: cin>>d1.b; regs[reg]=d1.a[0]; regs[reg+1]=d1.a[1]; regs[15]+=1; break;
                case 102: f = fopen("output.txt","a"); fprintf(f,"%d",regs[reg]); fclose(f); regs[15]+=1; break;
                case 104: cin>>regs[reg]; regs[15]+=1; break;
                case 103: d1.a[0]=regs[reg]; d1.a[1]=regs[reg+1];f = fopen("output.txt","a"); fprintf(f,"%lg",d1.b); fclose(f); regs[15]+=1; break;
                case 105: f = fopen("output.txt","a"); fputc(regs[reg]&0xFF,f); fclose(f); regs[15]+=1; break;
            }
        }
        break;
    case 2:
        {
        reg = (c>>20)&(0xF); reg2 = (c>>16)&(0xF);
        op = int_from_16((c)&(0xFFFF));
        regs[reg]+=regs[reg2]+op;} regs[15]+=1; break;
    case 3:
        {reg = (c>>20)&(0xF);
        op = int_from_20((c)&(0xFFFFF));
        regs[reg]+=op;} regs[15]+=1; break;
    case 4:
        {reg = (c>>20)&(0xF); reg2 = (c>>16)&(0xF);
        op = int_from_16((c)&(0xFFFF));
        regs[reg]-=(regs[reg2]+op);} regs[15]+=1; break;
    case 5:
        {reg = (c>>20)&(0xF);
        op =int_from_20(c&0xFFFFF);
        regs[reg]-=op;} regs[15]+=1; break;
    case 6:
        {reg = (c>>20)&(0xF); reg2 = (c>>16)&(0xF);
        op = int_from_16(c&0xFFFF);
        long long int r = (long long)regs[reg]*(regs[reg2]+op);
        regs[reg]=r&(0xFFFFFFFF);
        regs[reg+1]=(r>>32)&0xFFFFFFFF;} regs[15]+=1; break;
    case 7:
        {reg = (c>>20)&(0xF);
        op =int_from_20(c&0xFFFFF);
        long long int r = (long long)regs[reg]*(op);
        regs[reg]=r&(0xFFFFFFFF);
        regs[reg+1]=(r>>32)&(0xFFFFFFFF);} regs[15]+=1; break;
    case 8:
        {reg = (c>>20)&(0xF); reg2 = (c>>16)&(0xF);
        op = int_from_16(c&0xFFFF);

        int q = abs(regs[reg]);
        int p = abs(regs[reg2]+op);

        int t = q/p;
        int r = q-p*t;
            if(regs[reg]>=0 && regs[reg2]>0)
            {
                regs[reg]=t;
                regs[reg+1]=r;
            }
            if(regs[reg]<0 && regs[reg2]>0)
            {
                t=-t;
                t-=1;
                r=p-r;
                regs[reg]=t;
                regs[reg+1]=r;
            }
            if(regs[reg]>0 && regs[reg2]<0)
            {
                t=-t;
                t-=1;
                r=r-p;
                regs[reg]=t;
                regs[reg+1]=r;
            }
            if(regs[reg]<0 && regs[reg2]<0)
            {
                r=-r;
                regs[reg]=t;
                regs[reg+1]=r;
            }
        }

         regs[15]+=1; break;
    case 9:
        {reg = (c>>20)&(0xF);
        op =int_from_20(c&0xFFFFF);
        int r = regs[reg]/(op);
        regs[reg+1]=regs[reg]-r*regs[reg];
        regs[reg]=r&(0xFFFFFFFF); regs[15]+=1; break;
        }
    case 12:
        {reg = (c>>20)&(0xF);
        op =int_from_20(c&0xFFFFF);
        regs[reg]=op;} regs[15]+=1; break;
    case 13:
        {reg = (c>>20)&(0xF); reg2 = (c>>16)&(0xF);
        op = int_from_16(c&0xFFFF);
        regs[reg]=(regs[reg]<<regs[reg2]);} regs[15]+=1; break;
    case 14:
        {reg = (c>>20)&(0xF);
        op =int_from_20(c&0xFFFFF);
        regs[reg]<<=op;} regs[15]+=1; break;
    case 15:
        {reg = (c>>20)&(0xF); reg2 = (c>>16)&(0xF);
        op = int_from_16(c&0xFFFF);
        regs[reg]=(regs[reg]>>regs[reg2]);} regs[15]+=1; break;
    case 16:
        {reg = (c>>20)&(0xF);
        op =int_from_20(c&0xFFFFF);
        regs[reg]>>=op;} regs[15]+=1; break;
    case 17:
        {reg = (c>>20)&(0xF); reg2 = (c>>16)&(0xF);
        op = int_from_16(c&0xFFFF);
        regs[reg]=regs[reg]&regs[reg2];} regs[15]+=1; break;
    case 18:
        {reg = (c>>20)&(0xF);
        op =int_from_20(c&0xFFFFF);
        regs[reg]&=op;} regs[15]+=1; break;
    case 19:
        {reg = (c>>20)&(0xF); reg2 = (c>>16)&(0xF);
        op = int_from_16(c&0xFFFF);
        regs[reg]=regs[reg]|regs[reg2];} regs[15]+=1; break;
    case 20:
        {reg = (c>>20)&(0xF);
        op =int_from_20(c&0xFFFFF);
        regs[reg]|=op;} regs[15]+=1; break;
    case 21:
        {reg = (c>>20)&(0xF); reg2 = (c>>16)&(0xF);
        op = int_from_16(c&0xFFFF);
        regs[reg]=regs[reg]^regs[reg2];} regs[15]+=1; break;
    case 22:
        {reg = (c>>20)&(0xF);
        op =int_from_20(c&0xFFFFF);
        regs[reg]^=op;} regs[15]+=1; break;
    case 23:
        {reg = (c>>20)&(0xF);
        op =int_from_20(c&0xFFFFF);
        regs[reg]^=0xFFFFFFFF;} regs[15]+=1; break;
    case 24:
        {reg = (c>>20)&(0xF); reg2 = (c>>16)&(0xF);
        op = int_from_16(c&0xFFFF);
        regs[reg]=regs[reg2]+op;} regs[15]+=1; break;
    case 32:
        reg = (c>>20)&(0xF); reg2 = (c>>16)&(0xF);
        d1.a[0]=regs[reg];
        d1.a[1]=regs[reg+1];
        d2.a[0]=regs[reg2];
        d2.a[1]=regs[reg2+1];
        d1.b+=d2.b;
        regs[reg]=d1.a[0];
        regs[reg+1]=d1.a[1];
        regs[15]+=1;
        break;
    case 33:
        reg = (c>>20)&(0xF); reg2 = (c>>16)&(0xF);
        d1.a[0]=regs[reg];
        d1.a[1]=regs[reg+1];
        d2.a[0]=regs[reg2];
        d2.a[1]=regs[reg2+1];
        d1.b-=d2.b;
        regs[reg]=d1.a[0];
        regs[reg+1]=d1.a[1];
        regs[15]+=1;
        break;
    case 34:
        reg = (c>>20)&(0xF); reg2 = (c>>16)&(0xF);
        d1.a[0]=regs[reg];
        d1.a[1]=regs[reg+1];
        d2.a[0]=regs[reg2];
        d2.a[1]=regs[reg2+1];
        d1.b*=d2.b;
        regs[reg]=d1.a[0];
        regs[reg+1]=d1.a[1];
        regs[15]+=1;
        break;
    case 35:
        reg = (c>>20)&(0xF); reg2 = (c>>16)&(0xF);
        d1.a[0]=regs[reg];
        d1.a[1]=regs[reg+1];
        d2.a[0]=regs[reg2];
        d2.a[1]=regs[reg2+1];
        d1.b/=d2.b;
        regs[reg]=d1.a[0];
        regs[reg+1]=d1.a[1];
        regs[15]+=1;
        break;
    case 36:
        reg = (c>>20)&(0xF); reg2 = (c>>16)&(0xF);
        d1.b = (double)(regs[reg2]);
        regs[reg]=d1.a[0];
        regs[reg+1]=d1.a[1];
        regs[15]+=1;
        break;
    case 37:
        {
        reg = (c>>20)&(0xF); reg2 = (c>>16)&(0xF);
        int a = (int)(d1.b);
        regs[reg]=a;
        regs[15]+=1;
        break;
        }
    case 38:
        reg = (c>>20)&0xF;
        op =int_from_20(c&0xFFFFF);
        regs[14]-=1;
        mem[regs[14]]=regs[reg]+op;
        regs[15]+=1; break;
    case 39:
        reg = (c>>20)&0xF;
        op =int_from_20(c&0xFFFFF);
        regs[reg]=mem[regs[14]]+op;
        regs[14]+=1;
        regs[15]+=1; break;
    case 40:
        reg = (c>>20)&0xF;
        op =int_from_16(c&0xFFFF);
        regs[14]--;
        mem[regs[14]]=regs[15]+1;
        regs[0]=regs[15]+1;
        regs[15]=regs[reg]+op; break;
    case 41:
        op =int_from_20(c&0xFFFFF);
        regs[14]--;
        mem[regs[14]]=regs[15]+1;
        regs[15]=op;
        break;
    case 42:
        op =int_from_16(c&0xFFFF);
        regs[15]=mem[regs[14]];
        regs[14]+=1+op; break;
    case 43:
        reg = (c>>20)&(0xF); reg2 = (c>>16)&(0xF);
        if(regs[reg]>regs[reg2])
        {
            regs[16]=1;
        }
        else
        {
            if(regs[reg]==regs[reg2])
            {
                regs[16]=2;
            }
            else
                regs[16]=0;
        }
        regs[15]+=1; break;
    case 44:
        reg = (c>>20)&(0xF); op =int_from_20(c&0xFFFFF);
        if(regs[reg]>op)
        {
            regs[16]=1;
        }
        else
        {
            if(regs[reg]==op)
            {
                regs[16]=2;
            }
            else
                regs[16]=0;
        }
        regs[15]+=1; break;
    case 46:
        op =int_from_20(c&0xFFFFF);
        regs[15]=op; break;
    case 47:
        op =int_from_20(c&0xFFFFF);
        if(regs[16]!=2) regs[15]=op; else regs[15]+=1; break;
    case 48:
        op =int_from_20(c&0xFFFFF);
        if(regs[16]==2) regs[15]=op; else regs[15]+=1; break;
    case 49:
        op =int_from_20(c&0xFFFFF);
        if(regs[16]==2 || regs[16]==0) regs[15]=op; else regs[15]+=1; break;
    case 50:
        op =int_from_20(c&0xFFFFF);
        if(regs[16]==0) regs[15]=op; else regs[15]+=1; break;
    case 51:
        op =int_from_20(c&0xFFFFF);
        if(regs[16]==2 || regs[16]==1) regs[15]=op; else regs[15]+=1; break;
    case 52:
        op =int_from_20(c&0xFFFFF);
        if(regs[16]==1) regs[15]=op; else regs[15]+=1; break;
    case 64:
        reg = (c>>20)&(0xF); op =int_from_20(c&0xFFFFF);
        regs[reg]= mem[op];regs[15]+=1;break;
    case 65:
        reg = (c>>20)&(0xF); op =int_from_20(c&0xFFFFF);
        mem[op]=regs[reg];regs[15]+=1;break;
    case 66:
        reg = (c>>20)&(0xF); op =int_from_20(c&0xFFFFF);
        regs[reg]= mem[op]; regs[reg+1]= mem[op+1];regs[15]+=1; break;
    case 67:
        reg = (c>>20)&(0xF); op =int_from_20(c&0xFFFFF);
        mem[op]=regs[reg]; mem[op+1]=regs[reg+1]; regs[15]+=1;break;
    case 68:
        reg = (c>>20)&(0xF); reg2 = (c>>16)&(0xF); op =int_from_16(c&0xFFFF);
        regs[reg] = mem[regs[reg2]+op];regs[15]+=1;break;
    case 69:
        reg = (c>>20)&(0xF); reg2 = (c>>16)&(0xF); op =int_from_16(c&0xFFFF);
        mem[regs[reg2]+op]=regs[reg];regs[15]+=1;break;
    case 70:
        reg = (c>>20)&(0xF); reg2 = (c>>16)&(0xF); op =int_from_16(c&0xFFFF);
        regs[reg]= mem[regs[reg2]+op]; regs[reg+1]= mem[regs[reg2]+op+1]; regs[15]+=1; break;
    case 71:
        reg = (c>>20)&(0xF); reg2 = (c>>16)&(0xF); op =int_from_16(c&0xFFFF);
        mem[regs[reg2]+op]=regs[reg]; mem[regs[reg2]+op+1]=regs[reg+1]; regs[15]+=1;break;
    }
}
int main()
{
    map<string,Instruct> Allinstrcts;
    map<unsigned int,Instruct> AllinstrctsRev;
    map<string,unsigned int> marks;
    FILE *in;
    int registres[17] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    int *memor = new int[1048576];
    string cur;
    fill_with_instructions(Allinstrcts);
    FillReversMap(Allinstrcts,AllinstrctsRev);
    unsigned int length_of_program, start_point;
    in = fopen("input.bin","rb");
    fseek(in, 16, SEEK_SET);
    fread(&length_of_program,sizeof(int),1,in);
    unsigned int addit=0;
    fseek(in, 20, SEEK_SET);
    fread(&addit,sizeof(int),1,in);
    length_of_program+=addit;
    fseek(in, 24, SEEK_SET);
    fread(&addit,sizeof(int),1,in);
    length_of_program+=addit;

    fseek(in, 28, SEEK_SET);
    fread(&registres[15],sizeof(int),1,in);
    registres[14]=1048575;
    for(int i = 0; i < length_of_program; i++)
    {
        fseek(in,512 + i*4, SEEK_SET);
        fread(&memor[i],sizeof(int),1,in);
    }
    fclose(in);
    while(registres[15]<(int)length_of_program)
    {
        DoInstruct(memor[registres[15]],registres,memor);
    }

    return 0;
}
