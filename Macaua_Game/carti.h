#include <string>
#include <vector>
#include <iostream>
#include <cstdlib>
#include <fstream>
using namespace std;
class Carti{
    private:
    int culoare;
    int semn;
    protected:
    static int NCuloare;
    public:

        Carti(int c,int s){
            culoare=c;
            semn=s;
        }
        int getCuloare(){
            return culoare;
        }
        int getSemn(){
            return semn;
        }
        virtual int getValoare(){}
        virtual void setValoare(int x){}
        virtual bool getValabilitate(){}
        virtual void setValabilitate(bool x){}
//        virtual void afis(){
//            cout<<"clasa de baza";
//        }
        void setCuloareNoua(int c){
            NCuloare=c;
        }
        int getCuloareNoua() {
            return NCuloare;
        }
};
int Carti::NCuloare=0;
class CarteValoare:public Carti{
    int valoare;
    bool valabilitate;
    public:
        CarteValoare(int c,int s):Carti(c,s){
            valoare=0;
            valabilitate=true;
        }
        int getValoare() override{
            return valoare;
        }
        void setValoare (int x) override{
            valoare=x;
        }
        bool getValabilitate() override{
            return valabilitate;
        }
        void setValabilitate(bool x) override{
            valabilitate=x;
        }
//        void afis(){
//            cout<<"clasa valoare";
//        }
};
class CarteActiune:public Carti{
    int actiune;
    bool valabilitate;
    /*
        1. Schimba Culoarea
        2. Stai o tura
    */
    public:
        CarteActiune(int c,int s,int a):Carti(c,s){
            actiune=a;
            valabilitate=true;
        }
//        void afis(){
//            cout<<"clasa actiune";
//        }
        bool getValabilitate() override{
            return valabilitate;
        }
        void setValabilitate(bool x) override{
            valabilitate=x;
        }

};
class Jucator{
    protected:
        int staOTura;
        static int calculStaOTura;
        static int nrUnflaturi;
        string nickname;
        int rundeCastigate;
        vector<shared_ptr<Carti>>CartiJucator;
    public:
        Jucator(string nume){
            nickname=nume;
            rundeCastigate=0;
            staOTura=0;
        }
        string getNume(){
            return nickname;
        }
        int getRundeCastigate(){
            return rundeCastigate;
        }
        void addCarte(shared_ptr<Carti> c){
            CartiJucator.push_back(c);
        }
        shared_ptr<Carti> getCarti(int x){
            return CartiJucator[x];
        }
        int getNrCarti(){
            return CartiJucator.size();
        }
        int getStaOTura(){
            return staOTura;
        }
        void decStaOTura(){
            staOTura--;
        }
        void addStaOTura(int x=1){
            staOTura+=x;
        }
        void incCalculStaOTura(int x=1){
            calculStaOTura+=x;
        }
        int getCalculStaOTura(){
            return calculStaOTura;
        }
        void stergeCarte(shared_ptr<Carti> x){
            for(int i=0;i<CartiJucator.size();i++)
                if(x==CartiJucator[i])
                {
                    CartiJucator.erase(CartiJucator.begin()+i);
                    return;
                }
        }
        int getUnflaturi(){
            return nrUnflaturi;
        }
        void addUnflaturi(int x){
            nrUnflaturi+=x;
        }
        void addUnflaturi(){
            nrUnflaturi=0;
        }
};
int Jucator::nrUnflaturi=0;
int Jucator::calculStaOTura=0;
class HumanPlayer:public Jucator{
    int numarJocuriCastigate;
    public:
        HumanPlayer(string nume):Jucator(nume){
            ifstream fin("highscore.txt");
            fin.close();
        }
        int getNumarJocuriCastigate(){
            return numarJocuriCastigate;
        }
};
int RandomPlayer(int id){
    srand((unsigned) time(NULL));
    return rand()%id+1;
}
int NextPlayer(int id,int n){
    id++;
    if(id==n+1)
        return 1;
    return id;
}

void GenerareCarti(vector<shared_ptr<Carti>>&v){
    for(int i=1;i<=4;i++)
        for(int j=1;j<=13;j++)
        {
            Carti nou(i,j);
            v.push_back(make_shared<Carti>(nou));
        }
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
void desen(shared_ptr<Carti>x,vector<string>&f,vector<string>&n,vector<shared_ptr<Carti>>&fo,vector<shared_ptr<Carti>>&ne,shared_ptr<Carti>deVerificat){
    string c,s;
    if(x->getCuloare()==1)
        c="INIMA RO";
    else if(x->getCuloare()==2)
        c="INIMA NE";
    else if(x->getCuloare()==3)
        c="..CARO..";
    else
        c=".TREFLA.";
    if(x->getSemn()==1)
        s="AS";
    else if(x->getSemn()>=2 && x->getSemn()<=9)
        s=to_string(x->getSemn())+".";
    else if(x->getSemn()==10)
        s="10";
    else if(x->getSemn()==11)
        s="J.";
    else if(x->getSemn()==12)
        s="Q.";
    else
        s="K.";
    if(x->getCuloare()==deVerificat->getCuloare() || x->getSemn()==deVerificat->getSemn()){
        fo.push_back(x);
        f.push_back("..........");
        f.push_back("..........");
        f.push_back("...."+s+"....");
        f.push_back("."+c+".");
        f.push_back("..........");
        f.push_back("..........");
    }
    else{
        ne.push_back(x);
        n.push_back("..........");
        n.push_back("..........");
        n.push_back("...."+s+"....");
        n.push_back("."+c+".");
        n.push_back("..........");
        n.push_back("..........");
    }
}
void desenUnflaturi(shared_ptr<Carti>x,vector<string>&f,vector<string>&n,vector<shared_ptr<Carti>>&fo,vector<shared_ptr<Carti>>&ne,shared_ptr<Carti>deVerificat){
    string c,s;
    if(x->getCuloare()==1)
        c="INIMA RO";
    else if(x->getCuloare()==2)
        c="INIMA NE";
    else if(x->getCuloare()==3)
        c="..CARO..";
    else
        c=".TREFLA.";
    if(x->getSemn()==1)
        s="AS";
    else if(x->getSemn()>=2 && x->getSemn()<=9)
        s=to_string(x->getSemn())+".";
    else if(x->getSemn()==10)
        s="10";
    else if(x->getSemn()==11)
        s="J.";
    else if(x->getSemn()==12)
        s="Q.";
    else
        s="K.";
    if(x->getSemn()==deVerificat->getSemn() || (x->getCuloare()==deVerificat->getCuloare() && (x->getSemn()==2 || x->getSemn()==3))){
        fo.push_back(x);
        f.push_back("..........");
        f.push_back("..........");
        f.push_back("...."+s+"....");
        f.push_back("."+c+".");
        f.push_back("..........");
        f.push_back("..........");
    }
    else{
        ne.push_back(x);
        n.push_back("..........");
        n.push_back("..........");
        n.push_back("...."+s+"....");
        n.push_back("."+c+".");
        n.push_back("..........");
        n.push_back("..........");
    }
}
void desenTura(shared_ptr<Carti>x,vector<string>&f,vector<string>&n,vector<shared_ptr<Carti>>&fo,vector<shared_ptr<Carti>>&ne,shared_ptr<Carti>deVerificat){
    string c,s;
    if(x->getCuloare()==1)
        c="INIMA RO";
    else if(x->getCuloare()==2)
        c="INIMA NE";
    else if(x->getCuloare()==3)
        c="..CARO..";
    else
        c=".TREFLA.";
    if(x->getSemn()==1)
        s="AS";
    else if(x->getSemn()>=2 && x->getSemn()<=9)
        s=to_string(x->getSemn())+".";
    else if(x->getSemn()==10)
        s="10";
    else if(x->getSemn()==11)
        s="J.";
    else if(x->getSemn()==12)
        s="Q.";
    else
        s="K.";
    if(x->getSemn()==deVerificat->getSemn()){
        fo.push_back(x);
        f.push_back("..........");
        f.push_back("..........");
        f.push_back("...."+s+"....");
        f.push_back("."+c+".");
        f.push_back("..........");
        f.push_back("..........");
    }
    else{
        ne.push_back(x);
        n.push_back("..........");
        n.push_back("..........");
        n.push_back("...."+s+"....");
        n.push_back("."+c+".");
        n.push_back("..........");
        n.push_back("..........");
    }
}
void desenAs(shared_ptr<Carti>x,vector<string>&f,vector<string>&n,vector<shared_ptr<Carti>>&fo,vector<shared_ptr<Carti>>&ne,shared_ptr<Carti>deVerificat){
    string c,s;
    if(x->getCuloare()==1)
        c="INIMA RO";
    else if(x->getCuloare()==2)
        c="INIMA NE";
    else if(x->getCuloare()==3)
        c="..CARO..";
    else
        c=".TREFLA.";
    if(x->getSemn()==1)
        s="AS";
    else if(x->getSemn()>=2 && x->getSemn()<=9)
        s=to_string(x->getSemn())+".";
    else if(x->getSemn()==10)
        s="10";
    else if(x->getSemn()==11)
        s="J.";
    else if(x->getSemn()==12)
        s="Q.";
    else
        s="K.";
    if(x->getSemn()==deVerificat->getSemn() || x->getCuloare()==deVerificat->getCuloareNoua()){
        fo.push_back(x);
        f.push_back("..........");
        f.push_back("..........");
        f.push_back("...."+s+"....");
        f.push_back("."+c+".");
        f.push_back("..........");
        f.push_back("..........");
    }
    else{
        ne.push_back(x);
        n.push_back("..........");
        n.push_back("..........");
        n.push_back("...."+s+"....");
        n.push_back("."+c+".");
        n.push_back("..........");
        n.push_back("..........");
    }
}
void desen(shared_ptr<Carti>x,vector<string>&v){
    string c,s;
    if(x->getCuloare()==1)
        c="INIMA RO";
    else if(x->getCuloare()==2)
        c="INIMA NE";
    else if(x->getCuloare()==3)
        c="..CARO..";
    else
        c=".TREFLA.";
    if(x->getSemn()==1)
        s="AS";
    else if(x->getSemn()>=2 && x->getSemn()<=9)
        s=to_string(x->getSemn())+".";
    else if(x->getSemn()==10)
        s="10";
    else if(x->getSemn()==11)
        s="J.";
    else if(x->getSemn()==12)
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
shared_ptr<Carti> alegeCarteStart(vector<shared_ptr<Carti>> &ListaCarti){
    srand(time(nullptr));
    int poz=rand()%(ListaCarti.size());
    while(ListaCarti[poz]->getSemn()==1 || ListaCarti[poz]->getSemn()==2 || ListaCarti[poz]->getSemn()==3 || ListaCarti[poz]->getSemn()==4)
        poz=rand()%(ListaCarti.size());
    shared_ptr<Carti> x=ListaCarti[poz];
    ListaCarti.erase(ListaCarti.begin()+poz);
    return x;
}
bool esteUnflatura(shared_ptr<Carti>x,shared_ptr<HumanPlayer>L){
    if((x->getSemn()==2 || x->getSemn()==3))
    {
            return x->getValabilitate();
    }
    return false;
}
bool esteActiune(shared_ptr<Carti>x,int a){
    return x->getSemn()==a && x->getValabilitate()==true;
}
