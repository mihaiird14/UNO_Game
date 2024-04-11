#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include <stdlib.h>
#include <vector>
#include <stack>
#include <memory>
#include <cstdlib>
#include "carti.h"
#define VERDE   "\033[32m"
#define ROSU   "\033[31m"
#define ALB   "\033[0m"
using namespace std;
vector<shared_ptr<Carti>>ListaCarti;
stack<shared_ptr<Carti>>stiva;
void AdaugaCarti(int nr,shared_ptr<HumanPlayer>&N){
    srand(time(nullptr));
    for(int i=1;i<=nr;i++){
        int x=rand()%(ListaCarti.size());
        N->addCarte(ListaCarti[x]);
        ListaCarti.erase(ListaCarti.begin()+x);
    }
}
void AdaugaCarti(int nr,shared_ptr<Jucator>&N){
    srand(time(nullptr));
    for(int i=1;i<=nr;i++){
        int x=rand()%(ListaCarti.size());
        N->addCarte(ListaCarti[x]);
        ListaCarti.erase(ListaCarti.begin()+x);
    }
}
void winner(shared_ptr<HumanPlayer>N){
    system("CLS");
    cout<<N->getNume()<<" A CASTIGAT!";
    exit(0);
}
void winner(shared_ptr<Jucator>N){
    system("CLS");
    cout<<N->getNume()<<" A CASTIGAT!";
    exit(0);
}
void StartJocLocal(vector<shared_ptr<HumanPlayer>>L,int rand){
    if(L[rand-1]->getStaOTura()==0){
        cout<<"Este Randul lui "<<L[rand-1]->getNume()<<endl<<endl;
        cout<<"----------ULTIMA CARTE JUCATA----------"<<endl<<endl;
        vector<string>s;
        desen(stiva.top(),s);
        for(int i=0;i<6;i++)
            cout<<s[i]<<endl;
        s.clear();
        cout<<endl;
        vector<string>folositoare,nefolositoare;
        vector<shared_ptr<Carti>>f,n;
        if(esteUnflatura(stiva.top())){
            CarteValoare y(stiva.top()->getCuloare(),stiva.top()->getSemn());
            shared_ptr<CarteValoare>x =make_shared<CarteValoare>(y);
            stiva.top()=dynamic_pointer_cast<CarteValoare>(x);
            stiva.top()->setValoare(stiva.top()->getSemn());
            L[rand-1]->addUnflaturi(stiva.top()->getValoare());
            cout<<"----------CARTILE TALE SUNT------------"<<endl<<endl;
            for(int i=0;i<L[rand-1]->getNrCarti();i++){
                shared_ptr<Carti>x=L[rand-1]->getCarti(i);
                desenUnflaturi(x,folositoare,nefolositoare,f,n,stiva.top());
            }
            this_thread::sleep_for(chrono::seconds(1));
            if(f.size()){
                for(int i=0;i<6;i++)
                {
                    for(int j=i;j<folositoare.size();j+=6)
                        cout<<VERDE<<folositoare[j]<<ALB<<"\t";
                    cout<<endl;
                }
                cout<<endl;
            }
            if(n.size()){
                for(int i=0;i<6;i++)
                {
                    for(int j=i;j<nefolositoare.size();j+=6)
                        cout<<nefolositoare[j]<<"\t";
                    cout<<endl;
                }
            }
            cout<<endl<<"-------ACTIUNI POSIBILE-----------"<<endl;
            int i=0;
            for(;i<folositoare.size()/6;i++)
                cout<<i+1<<": Joaca cartea de pe pozitia "<<i+1<<endl;
            cout<<ROSU<<i+1<<" :Trage "<<L[rand-1]->getUnflaturi()<<" carti"<<ALB<<endl;
            int actiune=0;
            while(actiune<1 || actiune>i+1)
            {
                cout<<"ALEGE ACTIUNE: ";
                cin>>actiune;
            }
            if(actiune==i+1){
                ///de inplementat, verifica daca sunt suficiente carti.
                if(L[rand-1]->getUnflaturi()<=ListaCarti.size()){
                    AdaugaCarti(L[rand-1]->getUnflaturi(),L[rand-1]);
                    stiva.top()->setValabilitate(false);
                    ///L[rand-1]->resetUnflaturi();
                }
                else{
                    cout<<"Nu sunt suficiente carti, asa ca numarul de carti extrase a fost redus la "<<ListaCarti.size()<<endl;
                    AdaugaCarti(ListaCarti.size(),L[rand-1]);
                    stiva.top()->setValabilitate(false);
                    ///L[rand-1]->resetUnflaturi();
                    }
            }
            else{
                stiva.push(f[actiune-1]);
                L[rand-1]->stergeCarte(f[actiune-1]);
                if(L[rand-1]->getNrCarti()==0)
                    winner(L[rand-1]);
            }
            cout<<"-----URMATORUL JUCATOR IN 2 SECUNDE---------"<<endl;
            this_thread::sleep_for(chrono::seconds(2));
            system("CLS");
            rand=NextPlayer(rand,(int)L.size());
            StartJocLocal(L,rand);
        }
        else if(esteActiune(stiva.top(),1)){ ///as
                CarteActiune x(stiva.top()->getCuloare(),stiva.top()->getSemn(),1);
                shared_ptr<CarteActiune>y=make_shared<CarteActiune>(x);
                stiva.top()=dynamic_pointer_cast<CarteActiune>(y);
                cout<<endl<<ROSU<<"CULOAREA A FOST SCHIMBATA IN ";
                if(stiva.top()->getCuloareNoua()==1)
                    cout<<"INIMA ROSIE"<<ALB<<endl;
                else if(stiva.top()->getCuloareNoua()==2)
                    cout<<"INIMA NEAGRA"<<ALB<<endl;
                else if(stiva.top()->getCuloareNoua()==3)
                    cout<<"CARO"<<ALB<<endl;
                else
                    cout<<"TREFLA"<<ALB<<endl;
                cout<<endl;
                cout<<"----------CARTILE TALE SUNT------------"<<endl<<endl;
                for(int i=0;i<L[rand-1]->getNrCarti();i++){
                    shared_ptr<Carti>x=L[rand-1]->getCarti(i);
                    desenAs(x,folositoare,nefolositoare,f,n,stiva.top());
                }
                this_thread::sleep_for(chrono::seconds(1));
                if(f.size()){
                for(int i=0;i<6;i++)
                {
                    for(int j=i;j<folositoare.size();j+=6)
                        cout<<VERDE<<folositoare[j]<<ALB<<"\t";
                    cout<<endl;
                }
                cout<<endl;
            }
            if(n.size()){
                for(int i=0;i<6;i++)
                {
                    for(int j=i;j<nefolositoare.size();j+=6)
                        cout<<nefolositoare[j]<<"\t";
                    cout<<endl;
                }
            }
            cout<<endl<<"-------ACTIUNI POSIBILE-----------"<<endl;
            int i=0;
            for(;i<folositoare.size()/6;i++)
                cout<<i+1<<": Joaca cartea de pe pozitia "<<i+1<<endl;
            cout<<ROSU<<i+1<<": Trage o carte"<<ALB<<endl;
            int actiune=0;
            while(actiune<1 || actiune>i+1)
            {
                cout<<"ALEGE ACTIUNE: ";
                cin>>actiune;
            }
            if(actiune==i+1){
                if(ListaCarti.size()>=1){
                    AdaugaCarti(1,L[rand-1]);
                }
                else{
                    cout<<"Nu mai sunt carti disponibile!!!"<<endl;
                }
                cout<<endl;
                cout<<"-------CARTEA EXTRASA ESTE-------------"<<endl<<endl;
                desen(L[rand-1]->getCarti(L[rand-1]->getNrCarti()-1),s);
                for(int j=0;j<6;j++)
                    cout<<s[j]<<endl;
                cout<<endl;
            }
            else{
                stiva.push(f[actiune-1]);
                L[rand-1]->stergeCarte(f[actiune-1]);
                if(L[rand-1]->getNrCarti()==0)
                    winner(L[rand-1]);
            }
            cout<<"-----URMATORUL JUCATOR IN 2 SECUNDE---------"<<endl;
            this_thread::sleep_for(chrono::seconds(2));
            system("CLS");
            rand=NextPlayer(rand,(int)L.size());
            StartJocLocal(L,rand);
        }
        else if(esteActiune(stiva.top(),4)){ ///stai o tura
                CarteActiune x(stiva.top()->getCuloare(),stiva.top()->getSemn(),2);
                shared_ptr<CarteActiune>y=make_shared<CarteActiune>(x);
                stiva.top()=dynamic_pointer_cast<CarteActiune>(y);
                cout<<"----------CARTILE TALE SUNT------------"<<endl<<endl;
                for(int i=0;i<L[rand-1]->getNrCarti();i++){
                    shared_ptr<Carti>x=L[rand-1]->getCarti(i);
                    desenTura(x,folositoare,nefolositoare,f,n,stiva.top());
                }
                this_thread::sleep_for(chrono::seconds(1));
                if(f.size()){
                for(int i=0;i<6;i++)
                {
                    for(int j=i;j<folositoare.size();j+=6)
                        cout<<VERDE<<folositoare[j]<<ALB<<"\t";
                    cout<<endl;
                }
                cout<<endl;
            }
            if(n.size()){
                for(int i=0;i<6;i++)
                {
                    for(int j=i;j<nefolositoare.size();j+=6)
                        cout<<nefolositoare[j]<<"\t";
                    cout<<endl;
                }
            }
            cout<<endl<<"-------ACTIUNI POSIBILE-----------"<<endl;
            int i=0;
            for(;i<folositoare.size()/6;i++)
                cout<<i+1<<": Joaca cartea de pe pozitia "<<i+1<<endl;
            cout<<ROSU<<i+1<<": Stai "<<L[rand-1]->getCalculStaOTura()+1<<" ture"<<ALB<<endl;
            int actiune=0;
            while(actiune<1 || actiune>i+1)
            {
                cout<<"ALEGE ACTIUNE: ";
                cin>>actiune;
            }
            if(actiune==i+1){
                L[rand-1]->addStaOTura(L[rand-1]->getCalculStaOTura());
                L[rand-1]->incCalculStaOTura(-L[rand-1]->getCalculStaOTura());
                stiva.top()->setValabilitate(false);
            }
            else{
                stiva.push(f[actiune-1]);
                L[rand-1]->stergeCarte(f[actiune-1]);
                L[rand-1]->incCalculStaOTura();
                if(L[rand-1]->getNrCarti()==0)
                    winner(L[rand-1]);
            }
            cout<<"-----URMATORUL JUCATOR IN 2 SECUNDE---------"<<endl;
            this_thread::sleep_for(chrono::seconds(2));
            system("CLS");
            rand=NextPlayer(rand,(int)L.size());
            StartJocLocal(L,rand);
        }
        else{
            L[rand-1]->addUnflaturi();
            cout<<"----------CARTILE TALE SUNT------------"<<endl<<endl;
            for(int i=0;i<L[rand-1]->getNrCarti();i++)
            {
                shared_ptr<Carti>x=L[rand-1]->getCarti(i);
                desen(x,folositoare,nefolositoare,f,n,stiva.top());
            }
            this_thread::sleep_for(chrono::seconds(1));
            if(f.size()){
                for(int i=0;i<6;i++)
                {
                    for(int j=i;j<folositoare.size();j+=6)
                        cout<<VERDE<<folositoare[j]<<ALB<<"\t";
                    cout<<endl;
                }
                cout<<endl;
            }
            if(n.size()){
                for(int i=0;i<6;i++)
                {
                    for(int j=i;j<nefolositoare.size();j+=6)
                        cout<<nefolositoare[j]<<"\t";
                    cout<<endl;
                }
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
                if(ListaCarti.size()>=1){
                ///de implementat, verifica daca sunt sufieciente carti ramase
                    AdaugaCarti(1,L[rand-1]);
                }
                else{
                    cout<<"Nu mai sunt carti disponibile!!!"<<endl;
                }
                cout<<endl;
                cout<<"-------CARTEA EXTRASA ESTE-------------"<<endl<<endl;
                desen(L[rand-1]->getCarti(L[rand-1]->getNrCarti()-1),s);
                for(int j=0;j<6;j++)
                    cout<<s[j]<<endl;
                cout<<endl;
            }
            else{
                stiva.push(f[actiune-1]);
                L[rand-1]->stergeCarte(f[actiune-1]);
                if(esteActiune(stiva.top(),1)){
                    cout<<"ALEGE IN CE CULOARE SCHIMBI: "<<endl;
                    cout<<"1. INIMA ROSIE"<<endl;
                    cout<<"2. INIMA NEAGRA"<<endl;
                    cout<<"3. CARO"<<endl;
                    cout<<"4. TREFLA"<<endl;
                    int sc=0;
                    while(sc<1 || sc>4)
                    {
                        cout<<"INTRODU CULOAREA: ";
                        cin>>sc;
                    }
                    CarteActiune x(stiva.top()->getCuloare(),stiva.top()->getSemn(),1);
                    shared_ptr<CarteActiune>y=make_shared<CarteActiune>(x);
                    stiva.top()=dynamic_pointer_cast<CarteActiune>(y);
                    stiva.top()->setCuloareNoua(sc);
                }
                if(L[rand-1]->getNrCarti()==0)
                    winner(L[rand-1]);
            }
            cout<<"-----URMATORUL JUCATOR IN 2 SECUNDE---------"<<endl;
            this_thread::sleep_for(chrono::seconds(2));
            system("CLS");
            rand=NextPlayer(rand,(int)L.size());
            StartJocLocal(L,rand);
        }
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
void startPVP(shared_ptr<HumanPlayer>Player,shared_ptr<Jucator>PC,int rand){
    if(rand==1){
        if(Player->getStaOTura()==0){
            cout<<"Este Randul lui "<<Player->getNume()<<endl<<endl;
            cout<<"----------ULTIMA CARTE JUCATA----------"<<endl<<endl;
            vector<string>s;
            desen(stiva.top(),s);
            for(int i=0;i<6;i++)
                cout<<s[i]<<endl;
            s.clear();
            cout<<endl;
            vector<string>folositoare,nefolositoare;
            vector<shared_ptr<Carti>>f,n;
            if(esteUnflatura(stiva.top())){
                CarteValoare y(stiva.top()->getCuloare(),stiva.top()->getSemn());
                shared_ptr<CarteValoare>x =make_shared<CarteValoare>(y);
                stiva.top()=dynamic_pointer_cast<CarteValoare>(x);
                stiva.top()->setValoare(stiva.top()->getSemn());
                Player->addUnflaturi(stiva.top()->getValoare());
                cout<<"----------CARTILE TALE SUNT------------"<<endl<<endl;
                for(int i=0;i<Player->getNrCarti();i++){
                    shared_ptr<Carti>x=Player->getCarti(i);
                    desenUnflaturi(x,folositoare,nefolositoare,f,n,stiva.top());
                }
                this_thread::sleep_for(chrono::seconds(1));
                if(f.size()){
                    for(int i=0;i<6;i++)
                    {
                        for(int j=i;j<folositoare.size();j+=6)
                            cout<<VERDE<<folositoare[j]<<ALB<<"\t";
                        cout<<endl;
                    }
                    cout<<endl;
                }
                if(n.size()){
                    for(int i=0;i<6;i++)
                    {
                        for(int j=i;j<nefolositoare.size();j+=6)
                            cout<<nefolositoare[j]<<"\t";
                        cout<<endl;
                    }
                }
                cout<<endl<<"-------ACTIUNI POSIBILE-----------"<<endl;
                int i=0;
                for(;i<folositoare.size()/6;i++)
                    cout<<i+1<<": Joaca cartea de pe pozitia "<<i+1<<endl;
                cout<<ROSU<<i+1<<" :Trage "<<Player->getUnflaturi()<<" carti"<<ALB<<endl;
                int actiune=0;
                while(actiune<1 || actiune>i+1)
                {
                    cout<<"ALEGE ACTIUNE: ";
                    cin>>actiune;
                }
                if(actiune==i+1){
                    ///de inplementat, verifica daca sunt suficiente carti.
                    if(Player->getUnflaturi()<=ListaCarti.size()){
                        AdaugaCarti(Player->getUnflaturi(),Player);
                        stiva.top()->setValabilitate(false);
                        ///L[rand-1]->resetUnflaturi();
                    }
                    else{
                        cout<<"Nu sunt suficiente carti, asa ca numarul de carti extrase a fost redus la "<<ListaCarti.size()<<endl;
                        AdaugaCarti(ListaCarti.size(),Player);
                        stiva.top()->setValabilitate(false);
                        ///L[rand-1]->resetUnflaturi();
                        }
                }
                else{
                    stiva.push(f[actiune-1]);
                    Player->stergeCarte(f[actiune-1]);
                    if(Player->getNrCarti()==0)
                        winner(Player);
                }
                cout<<"-----URMATORUL JUCATOR IN 2 SECUNDE---------"<<endl;
                this_thread::sleep_for(chrono::seconds(2));
                system("CLS");
                rand=NextPlayer(rand,2);
                startPVP(Player,PC,rand);
            }
            else if(esteActiune(stiva.top(),1)){ ///as
                    CarteActiune x(stiva.top()->getCuloare(),stiva.top()->getSemn(),1);
                    shared_ptr<CarteActiune>y=make_shared<CarteActiune>(x);
                    stiva.top()=dynamic_pointer_cast<CarteActiune>(y);
                    cout<<endl<<ROSU<<"CULOAREA A FOST SCHIMBATA IN ";
                    if(stiva.top()->getCuloareNoua()==1)
                        cout<<"INIMA ROSIE"<<ALB<<endl;
                    else if(stiva.top()->getCuloareNoua()==2)
                        cout<<"INIMA NEAGRA"<<ALB<<endl;
                    else if(stiva.top()->getCuloareNoua()==3)
                        cout<<"CARO"<<ALB<<endl;
                    else
                        cout<<"TREFLA"<<ALB<<endl;
                    cout<<endl;
                    cout<<"----------CARTILE TALE SUNT------------"<<endl<<endl;
                    for(int i=0;i<Player->getNrCarti();i++){
                        shared_ptr<Carti>x=Player->getCarti(i);
                        desenAs(x,folositoare,nefolositoare,f,n,stiva.top());
                    }
                    this_thread::sleep_for(chrono::seconds(1));
                    if(f.size()){
                    for(int i=0;i<6;i++)
                    {
                        for(int j=i;j<folositoare.size();j+=6)
                            cout<<VERDE<<folositoare[j]<<ALB<<"\t";
                        cout<<endl;
                    }
                    cout<<endl;
                }
                if(n.size()){
                    for(int i=0;i<6;i++)
                    {
                        for(int j=i;j<nefolositoare.size();j+=6)
                            cout<<nefolositoare[j]<<"\t";
                        cout<<endl;
                    }
                }
                cout<<endl<<"-------ACTIUNI POSIBILE-----------"<<endl;
                int i=0;
                for(;i<folositoare.size()/6;i++)
                    cout<<i+1<<": Joaca cartea de pe pozitia "<<i+1<<endl;
                cout<<ROSU<<i+1<<": Trage o carte"<<ALB<<endl;
                int actiune=0;
                while(actiune<1 || actiune>i+1)
                {
                    cout<<"ALEGE ACTIUNE: ";
                    cin>>actiune;
                }
                if(actiune==i+1){
                    if(ListaCarti.size()>=1){
                        AdaugaCarti(1,Player);
                    }
                    else{
                        cout<<"Nu mai sunt carti disponibile!!!"<<endl;
                    }
                    cout<<endl;
                    cout<<"-------CARTEA EXTRASA ESTE-------------"<<endl<<endl;
                    desen(Player->getCarti(Player->getNrCarti()-1),s);
                    for(int j=0;j<6;j++)
                        cout<<s[j]<<endl;
                    cout<<endl;
                }
                else{
                    stiva.push(f[actiune-1]);
                    Player->stergeCarte(f[actiune-1]);
                    if(Player->getNrCarti()==0)
                        winner(Player);
                }
                cout<<"-----URMATORUL JUCATOR IN 2 SECUNDE---------"<<endl;
                this_thread::sleep_for(chrono::seconds(2));
                system("CLS");
                rand=NextPlayer(rand,2);
                startPVP(Player,PC,rand);
            }
            else if(esteActiune(stiva.top(),4)){ ///stai o tura
                    CarteActiune x(stiva.top()->getCuloare(),stiva.top()->getSemn(),2);
                    shared_ptr<CarteActiune>y=make_shared<CarteActiune>(x);
                    stiva.top()=dynamic_pointer_cast<CarteActiune>(y);
                    cout<<"----------CARTILE TALE SUNT------------"<<endl<<endl;
                    for(int i=0;i<Player->getNrCarti();i++){
                        shared_ptr<Carti>x=Player->getCarti(i);
                        desenTura(x,folositoare,nefolositoare,f,n,stiva.top());
                    }
                    this_thread::sleep_for(chrono::seconds(1));
                    if(f.size()){
                    for(int i=0;i<6;i++)
                    {
                        for(int j=i;j<folositoare.size();j+=6)
                            cout<<VERDE<<folositoare[j]<<ALB<<"\t";
                        cout<<endl;
                    }
                    cout<<endl;
                }
                if(n.size()){
                    for(int i=0;i<6;i++)
                    {
                        for(int j=i;j<nefolositoare.size();j+=6)
                            cout<<nefolositoare[j]<<"\t";
                        cout<<endl;
                    }
                }
                cout<<endl<<"-------ACTIUNI POSIBILE-----------"<<endl;
                int i=0;
                for(;i<folositoare.size()/6;i++)
                    cout<<i+1<<": Joaca cartea de pe pozitia "<<i+1<<endl;
                cout<<ROSU<<i+1<<": Stai "<<Player->getCalculStaOTura()+1<<" ture"<<ALB<<endl;
                int actiune=0;
                while(actiune<1 || actiune>i+1)
                {
                    cout<<"ALEGE ACTIUNE: ";
                    cin>>actiune;
                }
                if(actiune==i+1){
                    Player->addStaOTura(Player->getCalculStaOTura());
                    Player->incCalculStaOTura(-Player->getCalculStaOTura());
                    stiva.top()->setValabilitate(false);
                    if(Player->getNrCarti()==0)
                        winner(Player);
                }
                else{
                    stiva.push(f[actiune-1]);
                    Player->stergeCarte(f[actiune-1]);
                    Player->incCalculStaOTura();
                    if(Player->getNrCarti()==0)
                        winner(Player);
                }
                cout<<"-----URMATORUL JUCATOR IN 2 SECUNDE---------"<<endl;
                this_thread::sleep_for(chrono::seconds(2));
                system("CLS");
                rand=NextPlayer(rand,2);
                startPVP(Player,PC,rand);
            }
            else{
                Player->addUnflaturi();
                cout<<"----------CARTILE TALE SUNT------------"<<endl<<endl;
                for(int i=0;i<Player->getNrCarti();i++)
                {
                    shared_ptr<Carti>x=Player->getCarti(i);
                    desen(x,folositoare,nefolositoare,f,n,stiva.top());
                }
                this_thread::sleep_for(chrono::seconds(1));
                if(f.size()){
                    for(int i=0;i<6;i++)
                    {
                        for(int j=i;j<folositoare.size();j+=6)
                            cout<<VERDE<<folositoare[j]<<ALB<<"\t";
                        cout<<endl;
                    }
                    cout<<endl;
                }
                if(n.size()){
                    for(int i=0;i<6;i++)
                    {
                        for(int j=i;j<nefolositoare.size();j+=6)
                            cout<<nefolositoare[j]<<"\t";
                        cout<<endl;
                    }
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
                    if(ListaCarti.size()>=1){
                    ///de implementat, verifica daca sunt sufieciente carti ramase
                        AdaugaCarti(1,Player);
                    }
                    else{
                        cout<<"Nu mai sunt carti disponibile!!!"<<endl;
                    }
                    cout<<endl;
                    cout<<"-------CARTEA EXTRASA ESTE-------------"<<endl<<endl;
                    desen(Player->getCarti(Player->getNrCarti()-1),s);
                    for(int j=0;j<6;j++)
                        cout<<s[j]<<endl;
                    cout<<endl;
                }
                else{
                    stiva.push(f[actiune-1]);
                    Player->stergeCarte(f[actiune-1]);
                    if(esteActiune(stiva.top(),1)){
                        cout<<"ALEGE IN CE CULOARE SCHIMBI: "<<endl;
                        cout<<"1. INIMA ROSIE"<<endl;
                        cout<<"2. INIMA NEAGRA"<<endl;
                        cout<<"3. CARO"<<endl;
                        cout<<"4. TREFLA"<<endl;
                        int sc=0;
                        while(sc<1 || sc>4)
                        {
                            cout<<"INTRODU CULOAREA: ";
                            cin>>sc;
                        }
                        CarteActiune x(stiva.top()->getCuloare(),stiva.top()->getSemn(),1);
                        shared_ptr<CarteActiune>y=make_shared<CarteActiune>(x);
                        stiva.top()=dynamic_pointer_cast<CarteActiune>(y);
                        stiva.top()->setCuloareNoua(sc);
                    }
                    if(Player->getNrCarti()==0)
                        winner(Player);
                }
                cout<<"-----URMATORUL JUCATOR IN 2 SECUNDE---------"<<endl;
                this_thread::sleep_for(chrono::seconds(2));
                system("CLS");
                rand=NextPlayer(rand,2);
                startPVP(Player,PC,rand);
            }
        }
        else{
            cout<<"Jucatorul "<<Player->getNume()<<" mai are de stat "<<Player->getStaOTura()<<" ture\n";
            Player->decStaOTura();
            cout<<"-----URMATORUL JUCATOR IN 2 SECUNDE---------"<<endl;
            this_thread::sleep_for(chrono::seconds(2));
            system("CLS");
            rand=NextPlayer(rand,2);
            startPVP(Player,PC,rand);
        }
    }
    else{
        if(PC->getStaOTura()==0){
            cout<<"Este Randul lui "<<PC->getNume()<<endl<<endl;
            cout<<"----------ULTIMA CARTE JUCATA----------"<<endl<<endl;
            vector<string>s;
            desen(stiva.top(),s);
            for(int i=0;i<6;i++)
                cout<<s[i]<<endl;
            s.clear();
            cout<<endl;
            vector<string>folositoare,nefolositoare;
            vector<shared_ptr<Carti>>f,n;
            if(esteUnflatura(stiva.top())){
                CarteValoare y(stiva.top()->getCuloare(),stiva.top()->getSemn());
                shared_ptr<CarteValoare>x =make_shared<CarteValoare>(y);
                stiva.top()=dynamic_pointer_cast<CarteValoare>(x);
                stiva.top()->setValoare(stiva.top()->getSemn());
                PC->addUnflaturi(stiva.top()->getValoare());
                for(int i=0;i<PC->getNrCarti();i++){
                    shared_ptr<Carti>x=PC->getCarti(i);
                    desenUnflaturi(x,folositoare,nefolositoare,f,n,stiva.top());
                }
                int actiune=RandomActiune(f.size()+1);
                if(actiune==f.size()+1){
                    ///de inplementat, verifica daca sunt suficiente carti.
                    if(PC->getUnflaturi()<=ListaCarti.size()){
                        AdaugaCarti(PC->getUnflaturi(),PC);
                        stiva.top()->setValabilitate(false);
                        ///L[rand-1]->resetUnflaturi();
                        cout<<"Computerul a tras o carte nou!"<<endl;
                    }
                    else{
                        cout<<"Nu sunt suficiente carti, asa ca numarul de carti extrase a fost redus la "<<ListaCarti.size()<<endl;
                        AdaugaCarti(ListaCarti.size(),PC);
                        stiva.top()->setValabilitate(false);
                        ///L[rand-1]->resetUnflaturi();
                        }
                }
                else{
                    cout<<"Computerul a pus jos o carte!"<<endl;
                    stiva.push(f[actiune-1]);
                    PC->stergeCarte(f[actiune-1]);
                    if(PC->getNrCarti()==0)
                        winner(PC);
                }
                cout<<"-----URMATORUL JUCATOR IN 2 SECUNDE---------"<<endl;
                this_thread::sleep_for(chrono::seconds(2));
                system("CLS");
                rand=NextPlayer(rand,2);
                startPVP(Player,PC,rand);
            }
            else if(esteActiune(stiva.top(),1)){ ///as
                    CarteActiune x(stiva.top()->getCuloare(),stiva.top()->getSemn(),1);
                    shared_ptr<CarteActiune>y=make_shared<CarteActiune>(x);
                    stiva.top()=dynamic_pointer_cast<CarteActiune>(y);
                    cout<<endl<<ROSU<<"CULOAREA A FOST SCHIMBATA IN ";
                    if(stiva.top()->getCuloareNoua()==1)
                        cout<<"INIMA ROSIE"<<ALB<<endl;
                    else if(stiva.top()->getCuloareNoua()==2)
                        cout<<"INIMA NEAGRA"<<ALB<<endl;
                    else if(stiva.top()->getCuloareNoua()==3)
                        cout<<"CARO"<<ALB<<endl;
                    else
                        cout<<"TREFLA"<<ALB<<endl;
                    cout<<endl;
                    for(int i=0;i<PC->getNrCarti();i++){
                        shared_ptr<Carti>x=PC->getCarti(i);
                        desenAs(x,folositoare,nefolositoare,f,n,stiva.top());
                    }
                int actiune=RandomActiune(f.size()+1);
                if(actiune==f.size()+1){
                    if(ListaCarti.size()>=1){
                        AdaugaCarti(1,PC);
                        cout<<"Computerul a tras o noua carte!"<<endl;
                    }
                    else{
                        cout<<"Nu mai sunt carti disponibile!!!"<<endl;
                    }
                    cout<<endl;
                }
                else{
                    cout<<"Computerul a pus o carte jos!"<<endl;
                    stiva.push(f[actiune-1]);
                    PC->stergeCarte(f[actiune-1]);
                    if(PC->getNrCarti()==0)
                        winner(PC);
                }
                cout<<"-----URMATORUL JUCATOR IN 2 SECUNDE---------"<<endl;
                this_thread::sleep_for(chrono::seconds(2));
                system("CLS");
                rand=NextPlayer(rand,2);
                startPVP(Player,PC,rand);
            }
            else if(esteActiune(stiva.top(),4)){ ///stai o tura
                    CarteActiune x(stiva.top()->getCuloare(),stiva.top()->getSemn(),2);
                    shared_ptr<CarteActiune>y=make_shared<CarteActiune>(x);
                    stiva.top()=dynamic_pointer_cast<CarteActiune>(y);
                    for(int i=0;i<PC->getNrCarti();i++){
                        shared_ptr<Carti>x=PC->getCarti(i);
                        desenTura(x,folositoare,nefolositoare,f,n,stiva.top());
                    }
                int actiune=RandomActiune(f.size()+1);
                if(actiune==f.size()+1){
                    PC->addStaOTura(PC->getCalculStaOTura());
                    PC->incCalculStaOTura(-PC->getCalculStaOTura());
                    stiva.top()->setValabilitate(false);
                    if(PC->getNrCarti()==0)
                        winner(PC);
                    cout<<"Computerul va sta "<<PC->getStaOTura()+1<<" ture!"<<endl;
                }
                else{
                    cout<<"Computerul a pus o carte jos!"<<endl;
                    stiva.push(f[actiune-1]);
                    PC->stergeCarte(f[actiune-1]);
                    PC->incCalculStaOTura();
                    if(PC->getNrCarti()==0)
                        winner(PC);
                }
                cout<<"-----URMATORUL JUCATOR IN 2 SECUNDE---------"<<endl;
                this_thread::sleep_for(chrono::seconds(2));
                system("CLS");
                rand=NextPlayer(rand,2);
                startPVP(Player,PC,rand);
            }
            else{
                PC->addUnflaturi();
                for(int i=0;i<PC->getNrCarti();i++)
                {
                    shared_ptr<Carti>x=PC->getCarti(i);
                    desen(x,folositoare,nefolositoare,f,n,stiva.top());
                }
                int actiune=RandomActiune(f.size()+1);
                if(actiune==f.size()+1){
                    if(ListaCarti.size()>=1){
                    ///de implementat, verifica daca sunt sufieciente carti ramase
                        AdaugaCarti(1,PC);
                        cout<<"Computerul a tras o noua carte!"<<endl;
                    }
                    else{
                        cout<<"Nu mai sunt carti disponibile!!!"<<endl;
                    }
                    cout<<endl;
                }
                else{
                    cout<<"Computerul a pus o carte jos!"<<endl;
                    stiva.push(f[actiune-1]);
                    PC->stergeCarte(f[actiune-1]);
                    if(esteActiune(stiva.top(),1)){
                        cout<<"ALEGE IN CE CULOARE SCHIMBI: "<<endl;
                        cout<<"1. INIMA ROSIE"<<endl;
                        cout<<"2. INIMA NEAGRA"<<endl;
                        cout<<"3. CARO"<<endl;
                        cout<<"4. TREFLA"<<endl;
                        int sc=RandomActiune(4);
                        CarteActiune x(stiva.top()->getCuloare(),stiva.top()->getSemn(),1);
                        shared_ptr<CarteActiune>y=make_shared<CarteActiune>(x);
                        stiva.top()=dynamic_pointer_cast<CarteActiune>(y);
                        stiva.top()->setCuloareNoua(sc);
                    }
                    if(PC->getNrCarti()==0)
                        winner(PC);
                }
                cout<<"-----URMATORUL JUCATOR IN 2 SECUNDE---------"<<endl;
                this_thread::sleep_for(chrono::seconds(2));
                system("CLS");
                rand=NextPlayer(rand,2);
                startPVP(Player,PC,rand);
            }
        }
        else{
            cout<<"Jucatorul "<<PC->getNume()<<" mai are de stat "<<PC->getStaOTura()<<" ture\n";
            PC->decStaOTura();
            cout<<"-----URMATORUL JUCATOR IN 2 SECUNDE---------"<<endl;
            this_thread::sleep_for(chrono::seconds(2));
            system("CLS");
            rand=NextPlayer(rand,2);
            startPVP(Player,PC,rand);
        }
    }
}
void tipJoc()
{
    cout<<"         -----------------UNO-----------------"<<endl;
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
        vector<shared_ptr<HumanPlayer>>ListaJucatori;
        for(int i=1;i<=nrJucatori;i++)
        {
            cout<<"Nickname Player "<<i<<": ";
            cin>>numePlayer;
            HumanPlayer Player(numePlayer);
            ListaJucatori.push_back(make_shared<HumanPlayer>(Player));
            AdaugaCarti(5,ListaJucatori[ListaJucatori.size()-1]);
        }
        shared_ptr<Carti> CarteStart = alegeCarteStart(ListaCarti);
        stiva.push(CarteStart);
        cout<<"---------JOCUL VA INCEPE IN 2 SECUNDE-------------"<<endl;
        this_thread::sleep_for(chrono::seconds(2));
        system("CLS");
        StartJocLocal(ListaJucatori,Rand);
    }
    else if(modJoc==2){
        GenerareCarti(ListaCarti);
        string numePlayer;
        shared_ptr<HumanPlayer>Player;
        shared_ptr<Jucator>PC;
        cout<<"Nickname Player: ";
        cin>>numePlayer;
        Player=make_shared<HumanPlayer>(numePlayer);
        PC=make_shared<Jucator>("Computer");
        AdaugaCarti(5,Player);
        AdaugaCarti(5,PC);
        shared_ptr<Carti> CarteStart = alegeCarteStart(ListaCarti);
        stiva.push(CarteStart);
        cout<<"---------JOCUL VA INCEPE IN 2 SECUNDE-------------"<<endl;
        this_thread::sleep_for(chrono::seconds(2));
        system("CLS");
        int rand=RandomPlayer(2);
        startPVP(Player,PC,rand);
    }
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
    return 0;
}
