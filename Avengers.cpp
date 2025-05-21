#include<bits/stdc++.h>
using namespace std;
class Avenger;
class Battle;
class QNS{
    private:
    int P,D,E,H;
    public:
    QNS(int p1,int d1,int e1,int h1){
        P=min(5000,p1);
        D=d1;
        E=e1;
        H=max(0,h1);                                         //parametrised constructor
    }
    QNS(){
                                                        //default constructor
         P=1000;
         D=500;
         E=300;
         H=0;
    }
    QNS(const QNS& q1){
                                                        //copy constructor
        P=q1.P;
        D=q1.D;
        E=q1.E;
        H=q1.H;
    } 
    QNS& operator+(QNS& q1){
        P+=q1.E;
        D+=q1.D;
        E+=q1.P;
        P=min(P,5000);
        return *this;                                       //+ operator overloading for suit upgradation
    }
    QNS& operator-(int X){
        D-=X;
        E+=X;
        H+=X;
        return *this;                                       //- operator overloading for suit degradation in attack
        
    }
    QNS& operator*(int X){
        P+=(P*X)/100;
        E+=5*X;
        H+=X;
        P=min(P,5000);
         return *this;                                       //* operator overloading for amplifying attack strength
    }
    QNS& operator/(int X){
        D+=X;
        H-=X;
        if(H<0){
            H=0;
        }
        return *this;                                        // operator/ overloading for reducing heat
    }

    //function overloading
    void boostPower(int factor);
    void boostPower(QNS& otherSuit);

    //comparison overloading
    bool operator==(QNS& q1){
        if(P==q1.P&&D==q1.D){
            return true;
        }else{
            return false;
        }
                                                            //== operator overloading
    }
    bool operator<( QNS& q1){
                                                            //<operator overloading
        if(P+D<q1.P+q1.D){
                return true;
            }else{
                return false;
            }
    }

    //getters for QNS class private elements

    int get_powerlevel();
    int get_durability();
    int get_energystorage();
    int get_heatlevel();

    //setters for QNS class private elements

    void set_powerlevel(int p1);
    void set_durability(int d1);
    void set_energystorage(int e1);
    void set_heatlevel(int h1);

    //for checking if the suit is destroyed
    bool validsuit(){
        if(D>0){
            return true;
        }else{
            return false;
        }
    }

    //for checking if the suit is overheated
    bool overheated(){
        if(H>500){
            return true;
        }else{
            return false;
        }
    }

    friend class Avenger;
    friend class Battle;
};
void QNS::boostPower(int factor){
     (*this)*factor;
}
void QNS::boostPower(QNS& otherSuit){
     (*this)+otherSuit;
}
int QNS::get_powerlevel(){
    return P;
}
int QNS::get_durability(){
    return D;
}
int QNS::get_energystorage(){
    return E;
}
int QNS::get_heatlevel(){
    return H;
}
void QNS::set_powerlevel(int p1){
     P=p1;
}
void QNS::set_durability(int d1){
    D=d1;
}
void QNS::set_energystorage(int e1){
    E=e1;
}
void QNS::set_heatlevel(int h1){
    H=h1;
}
class Avenger{
    private:
    string name;
    QNS suit;
    int attackStrength;
    public:
    Avenger()=default;                                     //default constructor
    Avenger(string avName, QNS avSuit, int strength){
            name=avName;
            suit=avSuit;
            attackStrength=strength;
    };                                                      //parametrised constructor for Avenger class
    void attack(Avenger& enemy);
    void upgradeSuit(QNS& q1);
    void boost_suit(int y);
    void boost_suit(QNS& q1);
    void repair(int x);
    void printStatus();
    bool avengersuit_valid();
    bool avengersuit_overheated();
    friend class Battle;
};
void Avenger::attack(Avenger& enemy){
     enemy.suit-attackStrength;
    
}
void Avenger::upgradeSuit(QNS& q1){
     suit+q1;
}
void Avenger::boost_suit(int y){
     suit.boostPower(y);
}
void Avenger::boost_suit(QNS& q1){
     suit.boostPower(q1);
}
void Avenger::repair(int x){
     suit/x;
}
void Avenger::printStatus(){
    cout<<name<<" "<<suit.P<<" "<<suit.D<<" "<<suit.E<<" "<<suit.H<<endl;
}
bool Avenger::avengersuit_valid(){
    return suit.validsuit();
}
bool Avenger::avengersuit_overheated(){
    return suit.overheated();
}
class Battle{
     private:
     unordered_map<string,Avenger> heroes;
     unordered_map<string,Avenger> enemies;
     vector<string> battleLog;
     public:
     bool started_battle;                      //whether the battle stated or not if it doesnt i should ignore the battle statements until it becomes true
     Battle(){
        started_battle=false;                  //started_battle when battle obj is declared initialised to false
     }
     void startBattle();                       //this updates the default bool started_battle(false) to true
     void printBattleLog();
     int Result();
     void addAvenger_hero(Avenger& av1);  
     void addAvenger_enemy(Avenger& av1);  
     void Attack1_on2(string n1,string n2);
     void Repair(string n1,int y);
     void Boostpowerbyfactor(string n1,int y);
     void Boostpower(string n1,QNS& q1);
     void print_suit_status1(string n1);
     void Upgrade_avenger_suit(string n1,queue<QNS>& qu1);
     Avenger& give_details(string n1);

};
void Battle::addAvenger_hero(Avenger& av1){
     string n1=av1.name;
     heroes[n1]=av1;
}
void Battle::addAvenger_enemy(Avenger& av1){
     string n1=av1.name;
     enemies[n1]=av1;
}
void Battle::startBattle(){
     started_battle=true;
}   
Avenger& Battle::give_details(string n1){
     auto itr1=heroes.find(n1);
     auto itr2=enemies.find(n1);
     if(itr1!=heroes.end()){
        return itr1->second;
     }else{
        return itr2->second;
     }
}
void Battle::Attack1_on2(string n1,string n2){
     Avenger &av1=give_details(n1);
     Avenger &av2=give_details(n2);
     if(av1.suit.validsuit()&&!av1.suit.overheated()&&av2.suit.validsuit()){
        av1.attack(av2);
        string statement=n1;
        statement=statement+" attacks "+n2;
        battleLog.push_back(statement);
        if(!av2.suit.validsuit()){
            string statement=n2;
            statement=statement+" suit destroyed";
            battleLog.push_back(statement);
         }else{
         if(av2.suit.overheated()){
            string statement=n2;
            statement=statement+" suit overheated";
            battleLog.push_back(statement);
         }
        }
     }
}
void Battle::Repair(string n1,int y){
    give_details(n1).repair(y);
    string statement=n1;
    statement=statement+" repaired ";
    battleLog.push_back(statement);
}
void Battle::Boostpowerbyfactor(string n1,int y){
     give_details(n1).boost_suit(y);
     string statement=n1;
     statement=statement+" boosted ";
     battleLog.push_back(statement);
     if(give_details(n1).avengersuit_overheated()){
        statement=n1;
        statement=statement+" suit overheated";
        battleLog.push_back(statement);
     }
}
void Battle::Boostpower(string n1,QNS& q1){
      give_details(n1).boost_suit(q1);
      string statement=n1;
     statement=statement+" boosted ";
     battleLog.push_back(statement);
     if(give_details(n1).avengersuit_overheated()){
        statement=n1;
        statement=statement+" suit overheated";
        battleLog.push_back(statement);
     }
}
void Battle::print_suit_status1(string n1){
     give_details(n1).printStatus();
}
void Battle::Upgrade_avenger_suit(string n1,queue<QNS>& qu1){
     if(!qu1.empty()){
        QNS q1=qu1.front();
        give_details(n1).upgradeSuit(q1);
        string statement=n1;
        statement=statement+" upgraded";
        battleLog.push_back(statement);
        qu1.pop();
     }else{
        string statement=n1;
        statement=statement+" upgrade Fail";
        battleLog.push_back(statement);
     }
}
void Battle::printBattleLog(){
     int len_log=battleLog.size();
     for(int i=0;i<len_log;i++){
        cout<<battleLog[i]<<endl;
     }
}
int Battle::Result(){
    int sum_heroes=0,sum_enemies=0;
    for(auto& i:heroes){
        if(i.second.suit.D>0)
        sum_heroes=sum_heroes+i.second.suit.P+i.second.suit.D;
    }
    for(auto& i:enemies){
        if(i.second.suit.D>0)
        sum_enemies=sum_enemies+i.second.suit.P+i.second.suit.D;
    }
    if(sum_heroes>sum_enemies){
        return 1;
    }else if(sum_heroes<sum_enemies){
        return -1;
    }
    return 0;
}
int main(){
    int k,n,m;
    cin>>k>>n>>m;
    queue<QNS> Q;   
    for(int i=0;i<k;i++){
          int p1,d1,e1,h1;
          cin>>p1>>d1>>e1>>h1;
          QNS qi(p1,d1,e1,h1);
          Q.push(qi);
    }
    Battle battle1;
    for(int i=0;i<n;i++){
        string n1;
        int as1;                           //as1 for inputting attackstrength
        cin>>n1>>as1;
        if(!Q.empty()){
            QNS ave_suit=Q.front();
            Q.pop();
            Avenger avi(n1,ave_suit,as1);
            battle1.addAvenger_hero(avi);
        }else{
           cout<<n1<<" is out of fight"<<endl;
        }
    }
    for(int i=0;i<m;i++){
        string n1;
        int as1;                           //as1 for inputting attackstrength
        cin>>n1>>as1;
        if(!Q.empty()){
            QNS ave_suit=Q.front();
            Q.pop();
            Avenger avi(n1,ave_suit,as1);
            battle1.addAvenger_enemy(avi);
        }else{
           cout<<n1<<" is out of fight"<<endl;
        }
    }
    string s;
    while(cin>>s){
        if(s=="BattleBegin"){
            battle1.startBattle();
        }else if(s=="Attack"){
            string n1,n2;
            cin>>n1>>n2;
            if(battle1.started_battle){
            battle1.Attack1_on2(n1,n2);
            }
        }else if(s=="Repair"){
            string n1;
            int y;
            cin>>n1>>y;
            battle1.Repair(n1,y);
        }else if(s=="BoostPowerByFactor"){
            string n1;
            int y;
            cin>>n1>>y;
            battle1.Boostpowerbyfactor(n1,y);
        }else if(s=="AvengerStatus"){
            string n1;
            cin>>n1;
            battle1.print_suit_status1(n1);
        }else if(s=="Upgrade"){
            string n1;
            cin>>n1;
            battle1.Upgrade_avenger_suit(n1,Q);
        }else if(s=="PrintBattleLog"){
            battle1.printBattleLog();
        }else if(s=="BattleStatus"){
            int res_val= battle1.Result();
            if(res_val==1){
                cout<<"heroes are winning"<<endl;
            }else if(res_val==-1){
                cout<<"enemies are winning"<<endl;
            }else{
                cout<<"tie"<<endl;
            }
        }else if(s=="BoostPower"){
            string n1;
            int p1,d1,e1,h1;
            cin>>p1>>d1>>e1>>h1;
            QNS q1(p1,d1,e1,h1);
            battle1.Boostpower(n1,q1);
        }
    }

}
