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
    double height;
    double FGP; // field goal percentage
    double FTP; // free throw percentage
    double TPP; // three point percentage
public:
    
    // constructor
    NBAPlayer(){name = ""; team = ""; position = ""; height = FGP = FTP = TPP = 0;}
    NBAPlayer(string n, string t, string p, double h, double fgp, double ftp, double tpp);
    
    // setter
    void setName(string n){name = n;}
    void setTeam(string t){team = t;}
    void setPosition(string p){position = p;}
    void setHeight(double h){height = h;}
    void setFGP(double fgp){FGP = fgp;}
    void setFTP(double ftp){FTP = ftp;}
    void setTPP(double tpp){TPP = tpp;}
    
    // getter
    string getName(){return name;}
    string getTeam(){return team;}
    string getPosition(){return position;}
    double getHeight(){return height;}
    double getFGP(){return FGP;}
    double getFTP(){return FTP;}
    double ssgetTPP(){return TPP;}
    
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
 @param h that is height
 @param fgp that is FGP
 @param ftp that is FTP
 @param tpp that is TPP */
NBAPlayer::NBAPlayer(string n, string t, string p, double h, double fgp, double ftp, double tpp) {
    name = n;
    team = t;
    position = p;
    height = h;
    FGP = fgp;
    FTP = ftp;
    TPP = tpp;
}

/** This function is to print an NBAPlayer
 @param strm that is the cout object
 @param obj that is the toy needed to print out
 @return ostream that needed to printed out */
ostream &operator << (ostream &strm, const NBAPlayer &obj) {
    strm << obj.name << "  " << obj.team << "  " << obj.position << "  " << obj.height << obj.FGP << "  " << obj.FTP << "  " << obj.TPP << endl;
    
    return strm;
}

/** This function is to check if left is smaller than right
 @param right that is the right NBAPlayer
 @return true if left is smaller than right */
bool NBAPlayer::operator <(const NBAPlayer &right) {
    return height < right.height;
}

/** This function is to check if left is bigger than right
 @param right that is the right NBAPlayer
 @return true if left is bigger than right */
bool NBAPlayer::operator >(const NBAPlayer &right) {
    return height > right.height;
}

/** This function is to check if left is equal to right
 @param right that is the right NBAPlayer
 @return true if left is equal to right */
bool NBAPlayer::operator ==(const NBAPlayer &right) {
    return height == right.height;
}
#endif /* NBAPlayer_h */
