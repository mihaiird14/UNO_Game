#include <string>
#include <fstream>
#include <cstdlib>
using namespace std;
class Jucator{
    protected:
        int staOTura;
        static int nrUnflaturi;
        string nickname;
        int rundeCastigate;
        vector<pair<int,int>>CartiJucator;
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
        void addCarte(pair<int,int>c){
            CartiJucator.push_back(c);
        }
        pair<int,int> getCarti(int x){
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
        void stergeCarte(pair<int,int> x){
            for(int i=0;i<CartiJucator.size();i++)
                if(x==CartiJucator[i])
                {
                    CartiJucator.erase(CartiJucator.begin()+i);
                    return;
                }
        }
};
int Jucator::nrUnflaturi=0;
class HumanPlayer:public Jucator{
    int numarJocuriCastigate;
    public:
        HumanPlayer(string nume,int id):Jucator(nume){
            ifstream fin("highscore.txt");
            for(int i=1;i<=id;i++)
                fin>>numarJocuriCastigate;
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
