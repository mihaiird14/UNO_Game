#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include <stdlib.h>
#include <vector>
#include "jucator.h"
#include "carti.h"
using namespace std;
vector<pair<int,int>>ListaCarti;
void AdaugaCarti(int nr,HumanPlayer &N){
    srand(time(nullptr));
    for(int i=1;i<=nr;i++){
        int x=rand()%(ListaCarti.size());
        N.addCarte(ListaCarti[x]);
        ListaCarti.erase(ListaCarti.begin()+x);
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
        vector<string>v;
        for(int i=0;i<5;i++)
        {
            pair<int,int>x=ListaJucatori[0]->getCarti(i);
            desen(x.first,x.second,v);
        }
        for(int i=0;i<6;i++)
        {
            for(int j=i;j<v.size();j+=6)
                cout<<v[j]<<"\t";
            cout<<endl;
        }
    }
    else if(modJoc==2){}
    else if(modJoc==3){}
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
    return 0;
}
