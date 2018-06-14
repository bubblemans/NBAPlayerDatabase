/** This file contains a class of NBAPlayer object
    @file NBAPlayer.h
    @author Alvin Lin */

#ifndef NBAPlayer_h
#define NBAPlayer_h

#include <string>
#include <iostream>
using namespace std;

class NBAPlayer {
private:
    string name;
    string team;
    string position;
    string FGP; // field goal percentage
    string FTP; // free throw percentage
    string TPP; // three point percentage
    string PTS; // total points
public:
    
    // constructor
    NBAPlayer(){name = team = position = FGP = FTP = TPP = PTS = "";}
    NBAPlayer(string n, string t, string p, string fgp, string ftp, string tpp, string pts);
    
    // setter
    void setName(string n){name = n;}
    void setTeam(string t){team = t;}
    void setPosition(string p){position = p;}
    void setFGP(string fgp){FGP = fgp;}
    void setFTP(string ftp){FTP = ftp;}
    void setTPP(string tpp){TPP = tpp;}
    void setPTS(string pts){PTS = pts;}
    
    // getter
    string getName(){return name;}
    string getTeam(){return team;}
    string getPosition(){return position;}
    string getFGP(){return FGP;}
    string getFTP(){return FTP;}
    string getTPP(){return TPP;}
    string getPTS(){return PTS;}
    
    // overloaded operators
    bool operator >(const NBAPlayer &);
    bool operator ==(const NBAPlayer &);
    bool operator <(const NBAPlayer &);
    friend ostream &operator <<(ostream &, const NBAPlayer &);
};

/** This function is a constructor
     @param n that is name
     @param t that is team
     @param p that is position
     @param fgp that is FGP
     @param ftp that is FTP
     @param tpp that is TPP
     @param pts that is PTS */
NBAPlayer::NBAPlayer(string n, string t, string p, string fgp, string ftp, string tpp, string pts) {
    name = n;
    team = t;
    position = p;
    FGP = fgp;
    FTP = ftp;
    TPP = tpp;
    PTS = pts;
}

/** This function is to print an NBAPlayer
     @param strm that is the cout object
     @param obj that is the toy needed to print out
     @return ostream that needed to printed out */
ostream &operator << (ostream &strm, const NBAPlayer &obj) {
    strm << obj.name << "  " << obj.team << "  " << obj.position << "  " << obj.FGP << "  " << obj.FTP << "  " << obj.TPP << obj.PTS<< endl;
    
    return strm;
}

/** This function is to check if left is smaller than right
     @param right that is the right NBAPlayer
     @return true if left is smaller than right */
bool NBAPlayer::operator <(const NBAPlayer &right) {
    return name < right.name;
}

/** This function is to check if left is bigger than right
     @param right that is the right NBAPlayer
     @return true if left is bigger than right */
bool NBAPlayer::operator >(const NBAPlayer &right) {
    return name > right.name;
}

/** This function is to check if left is equal to right
     @param right that is the right NBAPlayer
     @return true if left is equal to right */
bool NBAPlayer::operator ==(const NBAPlayer &right) {
    return name == right.name;
}
#endif /* NBAPlayer_h */
