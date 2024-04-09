#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include <stdlib.h>
#include <vector>
#include <stack>
#include <memory>
#include "jucator.h"
#include "carti.h"
#define VERDE   "\033[32m"
#define ROSU   "\033[31m"
#define ALB   "\033[0m"
using namespace std;
stack<pair<int,int>>stiva;
vector<pair<int,int>>ListaCarti;
void AdaugaCarti(int nr,HumanPlayer &N){
    srand(time(nullptr));
    for(int i=1;i<=nr;i++){
        int x=rand()%(ListaCarti.size());
        N.addCarte(ListaCarti[x]);
        ListaCarti.erase(ListaCarti.begin()+x);
    }
}
void verificaCartiRamase(){
    if(ListaCarti.size()!=0)
        return;
    else{
        pair<int,int>VarfStiva=stiva.top();
        stiva.pop();
        while(!stiva.empty()){
            ListaCarti.push_back(stiva.top());
            stiva.pop();
        }
        GenerareCarti(ListaCarti);
        stiva.push(VarfStiva);
    }
}
void StartJocLocal(vector<HumanPlayer*>L,int rand){
    if(L[rand-1]->getStaOTura()==0){
        cout<<"Este Randul lui "<<L[rand-1]->getNume()<<endl<<endl;
        cout<<"----------ULTIMA CARTE JUCATA----------"<<endl<<endl;
        vector<string>s;
        desen(stiva.top().first,stiva.top().second,s);
        for(int i=0;i<6;i++)
            cout<<s[i]<<endl;
        s.clear();
        cout<<endl;
        cout<<"----------CARTILE TALE SUNT------------"<<endl<<endl;
        vector<string>folositoare,nefolositoare;
        vector<pair<int,int>>f,n;
        for(int i=0;i<L[rand-1]->getNrCarti();i++)
        {
            pair<int,int>x=L[rand-1]->getCarti(i);
            desen(x.first,x.second,folositoare,nefolositoare,f,n,stiva.top());
        }
        this_thread::sleep_for(chrono::seconds(1));
        for(int i=0;i<6;i++)
        {
            for(int j=i;j<folositoare.size();j+=6)
                cout<<VERDE<<folositoare[j]<<ALB<<"\t";
            cout<<endl;
        }
        cout<<endl;
        for(int i=0;i<6;i++)
        {
            for(int j=i;j<nefolositoare.size();j+=6)
                cout<<nefolositoare[j]<<"\t";
            cout<<endl;
        }
        cout<<endl<<"-------ACTIUNI POSIBILE-----------"<<endl;
        int i=0;
        for(;i<folositoare.size()/6;i++)
            cout<<i+1<<": Joaca cartea de pe pozitia "<<i+1<<endl;
        cout<<ROSU<<i+1<<" :Trage o noua carte"<<ALB<<endl;
        int actiune=0;
        while(actiune<1 || actiune>i+1)
        {
            cout<<"ALEGE ACTIUNE: ";
            cin>>actiune;
        }
        if(actiune==i+1){
            AdaugaCarti(1,*L[rand-1]);
            verificaCartiRamase();
            cout<<endl;
            cout<<"-------CARTEA EXTRASA ESTE-------------"<<endl<<endl;
            desen(L[rand-1]->getCarti(L[rand-1]->getNrCarti()-1).first,L[rand-1]->getCarti(L[rand-1]->getNrCarti()-1).second,s);
            for(int j=0;j<6;j++)
                cout<<s[j]<<endl;
            cout<<endl;
        }
        else{
            stiva.push(f[i-1]);
            L[rand-1]->stergeCarte(f[i-1]);
        }
        cout<<"-----URMATORUL JUCATOR IN 2 SECUNDE---------"<<endl;
        this_thread::sleep_for(chrono::seconds(2));
        system("CLS");
        rand=NextPlayer(rand,(int)L.size());
        StartJocLocal(L,rand);
    }
    else{
        cout<<"Jucatorul "<<L[rand-1]->getNume()<<" mai are de stat "<<L[rand-1]->getStaOTura()<<" ture\n";
        L[rand-1]->decStaOTura();
        cout<<"-----URMATORUL JUCATOR IN 2 SECUNDE---------"<<endl;
        this_thread::sleep_for(chrono::seconds(2));
        system("CLS");
        rand=NextPlayer(rand,(int)L.size());
        StartJocLocal(L,rand);
    }
}
void tipJoc()
{
    cout<<"         -----------------MACAUA-----------------"<<endl;
    cout<<"Alege Modul de joc: \n";
    cout<<"1. Local\n";
    cout<<"2. Player Vs. Calculator\n";
    cout<<"3. Regulament\n";
    int modJoc;
    cout<<"Introduceti Modul de Joc: ";
    cin>>modJoc;
    if(modJoc==1)
    {
        int nrJucatori=0;
        while(nrJucatori!=2 && nrJucatori!=4){
            cout<<"Introduceti numarul de jucatori (2 sau 4): ";
            cin>>nrJucatori;
        }
        int Rand=RandomPlayer(nrJucatori);
        GenerareCarti(ListaCarti);
        string numePlayer;
        vector<HumanPlayer*>ListaJucatori;
        for(int i=1;i<=nrJucatori;i++)
        {
            cout<<"Nickname Player "<<i<<": ";
            cin>>numePlayer;
            HumanPlayer *Player=new HumanPlayer(numePlayer,i);
            ListaJucatori.push_back(Player);
            AdaugaCarti(5,*Player);
        }
        pair<int,int> CarteStart = alegeCarteStart(ListaCarti);
        stiva.push(CarteStart);
        cout<<"---------JOCUL VA INCEPE IN 2 SECUNDE-------------"<<endl;
        this_thread::sleep_for(chrono::seconds(2));
        system("CLS");
        StartJocLocal(ListaJucatori,Rand);
    }
    else if(modJoc==2){}
    else if(modJoc==3){
        cout<<"1. Fiecare Jucator trebuie sa plaseze o carte care are aceasi culoare sau acelasi simbol ca prima carte"<<endl;
        cout<<"2. Fiecare Jucator va putea vedea ce carti poate sa puna (desenate cu verde) sau obtiunea de extrage o noua carte (rosu)"<<endl;
        cout<<"3. Nu pot fi puse mai multe carti in acelasi timp"<<endl;
        cout<<"4. Exista 2 tipuri de carti speciale: "<<endl;
        cout<<"\t a) Unflaturi (2 si 3) care il forteaza pe urmatorul jucator sa traga 2/3 carti noi. (Exceptie: Daca urmatorul jucator are si el o unflatura de aceeasi culoare, poate sa o plaseze si se aduna la numarul de carti care trebuie extrase de urmatorul jucator)"<<endl;
        cout<<"\t b) Carti Actiune (4 si AS)"<<endl;
        cout<<"\t\t -> 4 sare peste randul unui jucator. Poate fi combatuta numai de o alta carte 4"<<endl;
        cout<<"\t\t -> AS schimba culoarea cartii care trebuie pusa de urmatorul jucator. Culoare este aleasa de cel care a pus-o"<<endl;
        cout<<"5. Castiga cel care ramane primul fara carti"<<endl;
        char x;
        cout<<endl<<"APASA ORICE LITERA+ENTER PENTRU A REVENI LA MENIUL PRINCIPAL!";
        cin>>x;
        system("CLS");
        tipJoc();
    }
    else
    {
        cout<<"Modul de joc nu este valid!";
        this_thread::sleep_for(chrono::seconds(2));
        system("CLS");
        tipJoc();
    }
}
int main()
{
    tipJoc();
    ///de implementat: maxim 5 carti pe rand
    return 0;
}
