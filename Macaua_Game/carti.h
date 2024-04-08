#include <string>
#include <memory>
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;
class Carti{
    string culoare;
    string semn;
    public:
        Carti(string c,string s){
            culoare=c;
            semn=s;
        }
        string getCuloare(){
            return culoare;
        }
        string getSemn(){
            return semn;
        }

};
class CarteValoare:public Carti{
    int valoare;
    public:
        int getValoare(){
            return valoare;
        }
        CarteValoare(string c,string s,int v):Carti(c,s){
            valoare=v;
        }

};
class CarteActiune:public Carti{
    int actiune;
    /*
        1. Schimba Culoarea
        2. Stai o tura
    */
    public:
        string getActiune(int x){
            if(x==1)
                return "SCHIMBA CULOAREA";
            return "STAI O TURA";
        }
        CarteActiune(string c,string s,int a):Carti(c,s){
            actiune=a;
        }
};
void GenerareCarti(vector<pair<int,int>>&v){
    for(int i=1;i<=4;i++)
        for(int j=1;j<=13;j++)
            v.push_back(make_pair(i,j));
    /*
        pentru i: 1=inima rosie, 2=inima neagra, 3=caro,4=trefla
        pentru j: 2-10 numare, 1=as, 11=J,12=Q,13=K
    */
    ///amestecare random
    srand(time(nullptr));
    for(int i=1;i<=10000;i++)
    {
        int a1=rand()%52;
        int a2=rand()%52;
        swap(v[a1],v[a2]);
    }
}
void desen(int culoare,int semn,vector<string>&v){
    string c,s;
    if(culoare==1)
        c="INIMA RO";
    else if(culoare==2)
        c="INIMA NE";
    else if(culoare==3)
        c="..CARO..";
    else
        c=".TREFLA.";
    if(semn==1)
        s="AS";
    else if(semn>=2 && semn<=9)
        s=to_string(semn)+".";
    else if(semn==10)
        s="10";
    else if(semn==11)
        s="J.";
    else if(semn==12)
        s="Q.";
    else
        s="K.";
    v.push_back("..........");
    v.push_back("..........");
    v.push_back("...."+s+"....");
    v.push_back("."+c+".");
    v.push_back("..........");
    v.push_back("..........");
}

