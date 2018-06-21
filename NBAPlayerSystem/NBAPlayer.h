/** This file contains a class of NBAPlayer object
 @file NBAPlayer.h
 @author Alvin Lin, Bhag Sandhu, Amit Yativ */

#ifndef NBAPlayer_h
#define NBAPlayer_h

#include <string>
#include <iostream>
#include <iomanip>
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
    
    // Input Validity
    bool cannotBeNumbers(string playerOrTeamOrPosition);  // These cannot be numbers or punctuation.
    bool cannotBeLetters(string percentagesAndPoints);    // These cannot be letters or punctuation.
    void firstLetterCaps(string &playerName);              // Make first letter capital and the rest lowercase.
    void allCaps        (string &teamAndPosition);         // Make all letters capital.
    
    // overloaded operators
    void operator =(const NBAPlayer &);
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
    strm << setw(18) << left  << obj.name
    << setw(7)  << right << obj.team << "       "
    << setw(10) << left  << obj.position << "  "
    << setw(20) << left  << obj.FGP << "  "
    << setw(25) << left  << obj.FTP << "  "
    << setw(18) << left  << obj.TPP << "  "
    << setw(7) << obj.PTS << endl;
    
    return strm;
}


void NBAPlayer::operator =(const NBAPlayer &right) {
    name = right.name;
    team = right.team;
    position = right.position;
    FGP = right.FGP;
    FTP = right.FTP;
    TPP = right.TPP;
    PTS = right.PTS;
}

/**THESE FUNCTIONS VALIDATE INPUT**/

bool NBAPlayer::cannotBeNumbers(string playerOrTeamOrPosition)
{
    // If entry is blank
    if(playerOrTeamOrPosition.length() == 0)
    {
        cout << "\n\n\nInvalid input - Empty value. Please try "
        << "again. " << endl << endl << endl;
        return false;
    }
    // Check for numbers in the input
    for (unsigned int i = 0; i < playerOrTeamOrPosition.length(); i++)
    {
        if((playerOrTeamOrPosition[i] >= '0' && playerOrTeamOrPosition[i] <= '9')
           || (playerOrTeamOrPosition[i] != '-' && ispunct(playerOrTeamOrPosition[i])))
        {
            cout << "\n\nInvalid input - No numbers or punctuation (except dashes) allowed for this input."
            << " Please try again." << endl << endl;
            return false;
        }
    }
    return true;
}
bool NBAPlayer::cannotBeLetters(string percentagesAndPoints)
{
    for (unsigned int i = 0; i < percentagesAndPoints.length(); i++)
    {
        if (isalpha(percentagesAndPoints[i])
            || (percentagesAndPoints[i] != '.' && ispunct(percentagesAndPoints[i])))
        {
            cout << "\n\nInvalid input - No letters or punctuation (except periods) allowed for this input."
            << " Please try again." << endl << endl;
            return false;
        }
    }
    cin.clear();
    return true;
}
void NBAPlayer::firstLetterCaps(string &playerName)
{
    // Capitalize first letter of NBAPlayer
    playerName[0] = toupper(playerName[0]);
    for (unsigned i = 0 ; i < playerName.size() - 1; i++)
    {
        if ((isspace(playerName[i])))
            playerName[i+1] = toupper(playerName[i+1]);
        else
            playerName[i+1] = tolower(playerName[i+1]);
    }
}
void NBAPlayer::allCaps(string &teamAndPosition)
{
    for (unsigned int i = 0 ; i < teamAndPosition.size(); i++)
    {
        teamAndPosition[i] = toupper(teamAndPosition[i]);
    }
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
