#ifndef COMPARE_H_INCLUDED
#define COMPARE_H_INCLUDED
#include "NBAPlayer.h"

// COMPARE FUNCTIONS

// COMPARE BY NAME-------------------------------------------------------------
string compareByName(NBAPlayer left, NBAPlayer right)
{
  if (left.getName() < right.getName())
    return "Smaller";
  else if (left.getName() > right.getName())
    return "Larger";
  else
    return "Neither";
}

// COMPARE BY TEAM-------------------------------------------------------------
string compareByTeam(NBAPlayer left, NBAPlayer right)
{
  if (left.getTeam() < right.getTeam())
    return "Smaller";
  else if (left.getTeam() > right.getTeam())
    return "Larger";
  else
    return "Neither";
}

// COMPARE BY POSITION--------------------------------------------------
string compareByPosition(NBAPlayer left, NBAPlayer right)
{
  if (left.getPosition() < right.getPosition())
    return "Smaller";
  else if (left.getPosition() > right.getPosition())
    return "Larger";
  else
    return "Neither";
}

// COMPARE BY FTP-------------------------------------------------------------
string compareByFTP(NBAPlayer left, NBAPlayer right)
{
  if (left.getFTP() < right.getFTP())
    return "Smaller";
  else if (left.getFTP() > right.getFTP())
    return "Larger";
  else
    return "Neither";
}

// COMPARE BY FGP-------------------------------------------------------------
string compareByFGP(NBAPlayer left, NBAPlayer right)
{
    if (left.getFGP() < right.getFGP())
        return "Smaller";
    else if (left.getFGP() > right.getFGP())
        return "Larger";
    else
        return "Neither";
}

// COMPARE BY TPP-------------------------------------------------------------
string compareByTPP(NBAPlayer left, NBAPlayer right)
{
    if (left.getTPP() < right.getTPP())
        return "Smaller";
    else if (left.getTPP() > right.getTPP())
        return "Larger";
    else
        return "Neither";
}

// COMPARE BY PTS-------------------------------------------------------------
string compareByPTS(NBAPlayer left, NBAPlayer right)
{
    if (left.getPTS() < right.getPTS())
        return "Smaller";
    else if (left.getPTS() > right.getPTS())
        return "Larger";
    else
        return "Neither";
}

#endif // COMPARE_H_INCLUDED
