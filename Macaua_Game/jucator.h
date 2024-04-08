#include <string>
#include <fstream>
#include <cstdlib>
using namespace std;
class Jucator{
    protected:
        string nickname;
        int rundeCastigate;
        int nrInflaturi;
        vector<pair<int,int>>CartiJucator;
    public:
        Jucator(string nume){
            nickname=nume;
            rundeCastigate=0;
            nrInflaturi=0;
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

};
class HumanPlayer:public Jucator{
    int highScore;
    public:
        HumanPlayer(string nume,int id):Jucator(nume){
            ifstream fin("highscore.txt");
            for(int i=1;i<=id;i++)
                fin>>highScore;
            fin.close();
        }
        int getHighScore(){
            return highScore;
        }
};
int RandomPlayer(int id){
    srand((unsigned) time(NULL));
    return rand()%id+1;
}
int NextPlayer(int id,int n){
    id++;
    if(id==n)
        return 1;
    return id;
}
