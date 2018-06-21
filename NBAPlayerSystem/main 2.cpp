/***********************************************
 By: Bhag Sandhu/ Amit Yativ
 
 Additional Contributors: Alvin Lin, Peter Pang.
 
 Main Driver Of NBA Database.
 ************************************************/

// The purpose of this program is to build a Binary Search Tree and a hash table
// by reading from a file and inserting data. Data inserted can be of any type
// as templates are utilized for the tree files, while actual input data
// and some changes to the main() driver are required. This program provides
// the user a switch-statement-driven Menu, where the user has the option
// of selecting from several choices regarding their dataset.


#include "BinarySearchTree.h"  // BST ADT
#include "NBAPlayer.h"         // NBAPlayer object header
#include "Compare.h"           // For compare functions
#include "HashTable.h"         // For Hashing
#include "List.h"         // For linked list
#include <iostream>            // For cout
#include <vector>              // For delete
#include <stdlib.h>            // Exit failure
#include <fstream>             // File I/O
#include <limits>              // For getline
#include <ctime>               // For time

using namespace std;

// Helper Functions:

// Display data
void displayPlayer(NBAPlayer  *anItem);
void displayName   (NBAPlayer * anItem);
void displayTeam (NBAPlayer * anItem);
void displayPosition  (NBAPlayer * anItem);
void displayFGP(NBAPlayer * anItem);
void displayFTP(NBAPlayer * anItem);
void displayTPP(NBAPlayer * anItem);
void displayPTS(NBAPlayer * anItem);

bool checkInput(string userInput);  // Check user input for valid size.
void displayMenu();                 // Display the main menu of the program.
void welcomeMessage();              // Display a welcome message.
void goodbyeMessage();              // Display a goodbye message.

//Manager Functions:

void buildData(string filename, BinarySearchTree<NBAPlayer*> *, BinarySearchTree<NBAPlayer*> *, BinarySearchTree<NBAPlayer*> *,BinarySearchTree<NBAPlayer*> *, BinarySearchTree<NBAPlayer*> *, BinarySearchTree<NBAPlayer*> *, BinarySearchTree<NBAPlayer*> *, HashTable<string, NBAPlayer*> *, NBAPlayer **, int &);

void savePlayerToFile(NBAPlayer  *anItem, ofstream &);

void depthFirstTraversals(BinarySearchTree<NBAPlayer*> *,  BinarySearchTree<NBAPlayer*> *);

void depthFirstTraversalsIterative(BinarySearchTree<NBAPlayer*> *,  BinarySearchTree<NBAPlayer*> *);

void breadthFirstTraversal(BinarySearchTree<NBAPlayer*> *,  BinarySearchTree<NBAPlayer*> *);

void updatePlayer(BinarySearchTree<NBAPlayer*> *, BinarySearchTree<NBAPlayer*> *, BinarySearchTree<NBAPlayer*> *,BinarySearchTree<NBAPlayer*> *, BinarySearchTree<NBAPlayer*> *, BinarySearchTree<NBAPlayer*> *, BinarySearchTree<NBAPlayer*> *, HashTable<string, NBAPlayer*> *);

void insertPlayer(BinarySearchTree<NBAPlayer*> *, BinarySearchTree<NBAPlayer*> *, BinarySearchTree<NBAPlayer*> *,BinarySearchTree<NBAPlayer*> *, BinarySearchTree<NBAPlayer*> *, BinarySearchTree<NBAPlayer*> *, BinarySearchTree<NBAPlayer*> *, HashTable<string, NBAPlayer*> *, NBAPlayer **playerArray, int &);

void deleteANode(BinarySearchTree<NBAPlayer*> *, BinarySearchTree<NBAPlayer*> *, BinarySearchTree<NBAPlayer*> *,BinarySearchTree<NBAPlayer*> *, BinarySearchTree<NBAPlayer*> *, BinarySearchTree<NBAPlayer*> *, BinarySearchTree<NBAPlayer*> *, HashTable<string, NBAPlayer*> *, Stack<NBAPlayer*> *stack);

void undoDelete(BinarySearchTree<NBAPlayer*> *, BinarySearchTree<NBAPlayer*> *, BinarySearchTree<NBAPlayer*> *,BinarySearchTree<NBAPlayer*> *, BinarySearchTree<NBAPlayer*> *, BinarySearchTree<NBAPlayer*> *, BinarySearchTree<NBAPlayer*> *, HashTable<string, NBAPlayer*> *, Stack<NBAPlayer*> *stack);

void printIndented(BinarySearchTree<NBAPlayer*> *nameTree,  BinarySearchTree<NBAPlayer*> *PTSTree);

void menuDriver(char userInputChar, BinarySearchTree<NBAPlayer*> *nameTree, BinarySearchTree<NBAPlayer*> *teamTree, BinarySearchTree<NBAPlayer*> *positionTree, BinarySearchTree<NBAPlayer*> *FGPTree, BinarySearchTree<NBAPlayer*> *FTPTree, BinarySearchTree<NBAPlayer*> *TPPTree, BinarySearchTree<NBAPlayer*> *PTSTree, HashTable<string, NBAPlayer*> *hashTable, Stack<NBAPlayer*> * stack, NBAPlayer **playerArray, int &);

void searchNameTree(BinarySearchTree<NBAPlayer*> *NameTree);                                                      // Search unique key tree according to user input.

void searchPTSTree(BinarySearchTree<NBAPlayer*> *PTSTree);
// Search secondary key tree according to user input.

void findTheSmallest(BinarySearchTree<NBAPlayer*> *);
// Find smallest node in tree.

void findTheLargest(BinarySearchTree<NBAPlayer*> *, BinarySearchTree<NBAPlayer*> *, BinarySearchTree<NBAPlayer*> *, BinarySearchTree<NBAPlayer*> *, Stack<NBAPlayer*> *);
// Find largest node in tree.

void reHashingOption(HashTable<string, NBAPlayer*> *);

void showStatistic();

int main()
{
    // Dynamically allocate new pointer to tree.
    BinarySearchTree<NBAPlayer*>* nameTree = new BinarySearchTree<NBAPlayer*>(compareByName);
    BinarySearchTree<NBAPlayer*>* teamTree = new BinarySearchTree<NBAPlayer*>(compareByTeam);
    BinarySearchTree<NBAPlayer*>* positionTree = new BinarySearchTree<NBAPlayer*>(compareByPosition);
    BinarySearchTree<NBAPlayer*>* FGPTree = new BinarySearchTree<NBAPlayer*>(compareByFGP);
    BinarySearchTree<NBAPlayer*>* FTPTree = new BinarySearchTree<NBAPlayer*>(compareByFTP);
    BinarySearchTree<NBAPlayer*>* TPPTree = new BinarySearchTree<NBAPlayer*>(compareByTPP);
    BinarySearchTree<NBAPlayer*>* PTSTree = new BinarySearchTree<NBAPlayer*>(compareByPTS);
    
    // hash table
    HashTable<string, NBAPlayer*> *hashtable = new HashTable<string, NBAPlayer*>;
    
    // array
    int count = 0;
    NBAPlayer **playerArray = new NBAPlayer*[4000];
    for (int i = 0; i < 4000; i++) {
        playerArray[i] = NULL;
    }
    
    string filename = "100 Dataset for presentation.txt"; // Store name of input file.
    bool validInput = false;      // Store input validity.
    
    welcomeMessage();             // Display a welcome message.
    buildData(filename, nameTree, teamTree, positionTree, FGPTree, FTPTree, TPPTree, PTSTree, hashtable, playerArray, count);  // Call buildBST function,
    // read from file and insert.
    char userInputChar;     // To convert original input to char for menu switch.
    string userInput = "";       // To hold user input and validate.
    Stack<NBAPlayer*> *stack = new Stack<NBAPlayer*>;
    
    do                            // Main loop of program.
    {
        displayMenu();    // Display the menu.
        getline(cin, userInput); // Take in a user input.
        validInput = checkInput(userInput); // Check if input is one character or not.
        userInputChar = userInput[0];       // Convert input to char.
        userInputChar = toupper(userInputChar); // Make char uppercase.
        cout << endl << endl;
        if(userInputChar != 'E' && validInput == true) // If user input is not 'E' (Exit), and is valid)
            menuDriver(userInputChar, nameTree, teamTree, positionTree, FGPTree, FTPTree, TPPTree, PTSTree, hashtable, stack, playerArray, count); // Call driver to begin actual program.
        cout << endl;
    }
    while (userInputChar != 'E' || validInput == false); // Keep looping until user enters
    
    showStatistic();
    
    // save file from hash table
    hashtable->traverseHashSaveFile(savePlayerToFile, "saveFile.txt");
    
    goodbyeMessage(); // Display goodbye message.
    
    
    // Delete dynamically allocated tree pointers.
    delete nameTree;
    delete teamTree;
    delete positionTree;
    delete FGPTree;
    delete FTPTree;
    delete TPPTree;
    delete PTSTree;
    delete hashtable;
    delete stack;
    
    for (int i = 0; i < 4000; i++) {
        if (playerArray[i] != NULL) {
            delete playerArray[i];
        }
    }
    delete[] playerArray;
    
    return 0;         // End the program.
}
void menuDriver(char userInputChar, BinarySearchTree<NBAPlayer*> *nameTree, BinarySearchTree<NBAPlayer*> *teamTree, BinarySearchTree<NBAPlayer*> *positionTree, BinarySearchTree<NBAPlayer*> *FGPTree, BinarySearchTree<NBAPlayer*> *FTPTree, BinarySearchTree<NBAPlayer*> *TPPTree, BinarySearchTree<NBAPlayer*> *PTSTree, HashTable<string, NBAPlayer*> *hashTable, Stack<NBAPlayer*> *stack, NBAPlayer **playerArray, int &count)
{
    // Driver of program, call manager functions depending on user choice.
    switch (userInputChar)
    {
        case 'L':
            cout << "Unsorted List by Name:\n\n\n";
            cout << setw(15) << left  << "Name"
            << setw(12)  << right << "Team" << "   "
            << setw(7) << left  << "Position" << "  "
            << setw(10) << left  << "Field Goal Percentage" << "  "
            << setw(10) << left  << "Free Throw Percentage" << "    "
            << setw(10) << left  << "Triple Point Percentage" << "  "
            << setw(7) << "Total Points" << endl;
            cout << "===========          ======= ========= ======================= =======================  ======================= ===============\n";
            hashTable->traverseHash(displayPlayer);
            cout << endl << endl;
            break;
        case 'R':
            cout << "RECURSIVE Inorder, Preorder and Postorder Traversals:\n\n\n";
            depthFirstTraversals(nameTree, PTSTree);
            break;
        case 'I':
            cout << "ITERATIVE Inorder, Preorder and Postorder Traversals:\n\n\n";
            depthFirstTraversalsIterative(nameTree, PTSTree);
            break;
        case 'B':
            cout << "Breadth-First traversal by tree level:\n\n\n";
            breadthFirstTraversal(nameTree, PTSTree);
            break;
        case 'S':
            cout << "Please enter a Player Name to be searched in the Player Name Tree:\n\n\n";
            searchNameTree(nameTree);
            break;
        case 'P':
            searchPTSTree(PTSTree);
            break;
        case 'D':
            cout << "Current inOrder NAME Tree:    "     ; nameTree->   inOrder(displayPlayer);
            deleteANode(nameTree, teamTree, positionTree, FGPTree, FTPTree, TPPTree, PTSTree, hashTable, stack);
            break;
        case 'C':
            cout << "Undo delete.\n";
            undoDelete(nameTree, teamTree, positionTree, FGPTree, FTPTree, TPPTree, PTSTree, hashTable, stack);
            break;
        case 'N':
            cout << "Insert a new player: \n\n\n";
            insertPlayer(nameTree, teamTree, positionTree, FGPTree, FTPTree, TPPTree, PTSTree, hashTable, playerArray, count);
            break;
        case 'U':
            cout << "Update info of players: \n\n\n";
            updatePlayer(nameTree, teamTree, positionTree, FGPTree, FTPTree, TPPTree, PTSTree, hashTable);
            break;
        case 'M':
            cout << "Smallest NBAPlayer Node in tree:\n\n\n";
            findTheSmallest(nameTree);
            break;
        case 'X':
            cout << "Largest NBAPlayer Node in tree:\n\n\n";
            findTheLargest(FGPTree, FTPTree, TPPTree, PTSTree, stack);
            break;
        case 'T':
            cout << "Indented tree list:\n\n\n";
            printIndented(nameTree, PTSTree);
            break;
        case 'A':
            cout << "Team 5 Developer names: Alvin Lin, Amit Yativ, Bhagdeep Sandhu, Peter Ping.\n\n"
            << "Some code used by: Frank M. Carrano and Tim Henry.\n\n";
            break;
        case 'H':
            cout << "The menu will be shown again.\n\n";
            break;
            // Default means that the user input was one character, but not part of the menu.
        default:
            cout << userInputChar << " is not a valid menu choice. Please try again.\n\n";
    }
}
//-----------------------------------------------------------------------------------------

// Function to display the BST Menu to user.

void displayMenu()
{
    cout << " BST-based Database Program Menu\n"
    << "=================================================================\n"
    << " I - ITERATIVE Depth-First Traversal of tree: Inorder, Preorder, Postorder.\n"
    << " L - Unsorted list by name.\n"
    << " R - RECURSIVE Depth-First Traversal of tree: Inorder, Preorder, Postorder.\n"
    << " B - Breadth-First Traversal of tree by tree level.\n"
    << " S - Search for an item in the NAME tree   (input: item Name).\n"
    << " P - Search for an item in the PTS tree (input: item PTS).\n"
    << " D - Delete an item (by item Name).\n"
    << " C - Undo delete\n"
    << " N - Insert an item.\n"
    << " U - Update an item.\n"
    << " M - Find the smallest item in tree.\n"
    << " X - Find the largest item in tree.\n"
    << " T - Print the tree as an indented list.\n"
    << " A - Enter me to find out!\n"
    << " H - Help - Re-display the BST-based Database Menu.\n"
    << " E - Exit the program.\n" << endl;
    cout << "=================================================================\n";
    cout << "  \nEnter your choice: ";
}
//-----------------------------------------------------------------------------------------

// Function to read data from file and build BST and hash table.
void buildData(string filename, BinarySearchTree<NBAPlayer*> *nameTree, BinarySearchTree<NBAPlayer*> *teamTree, BinarySearchTree<NBAPlayer*> *positionTree,BinarySearchTree<NBAPlayer*> *FGPTree, BinarySearchTree<NBAPlayer*> *FTPTree, BinarySearchTree<NBAPlayer*> *TTPTree, BinarySearchTree<NBAPlayer*> *PTSTree, HashTable<string, NBAPlayer*> *hashTable, NBAPlayer **playerArray, int &count)
{
    //bool duplicateOrNot = false; // To store duplicate test.
    ifstream infile;
    infile.open(filename);
    
    // Input file validation
    if(infile.fail())
    {
        cout << "Failed to open input file. Program will terminate. " << endl;
        exit(EXIT_FAILURE);
    }
    
    // Different data members in each NBAPlayer object.
    string name;
    string team;
    string position;
    string FGP;
    string FTP;
    string TPP;
    string PTS;
    int index = 0;
    
    // get rid of the row title
    getline(infile, name, ',');
    getline(infile, team, ',');
    getline(infile, position, ',');
    getline(infile, FGP, ',');
    getline(infile, FTP, ',');
    getline(infile, TPP, ',');
    getline(infile, PTS);
    
    // read line by line
    while (getline(infile, name, ',')) {
        getline(infile, team, ',');
        getline(infile, position, ',');
        getline(infile, FGP, ',');
        getline(infile, FTP, ',');
        getline(infile, TPP, ',');
        getline(infile, PTS);
        
        if (name != "") {
            NBAPlayer *player = new NBAPlayer(name, team, position, FGP, FTP, TPP, PTS);
            
            // Error handling for duplicates.
            if (hashTable->searchEntry(name, player))
            {
                cout << "Duplicate NBAPlayer entry detected! Program will terminate." << endl << endl;
                exit(EXIT_FAILURE);
            }
            else {
                playerArray[index] = player;
                
                hashTable->insertEntry(name, player);
                nameTree->uniqueKeyTreeInsert(player);
                teamTree->secondaryKeyTreeInsert(player);
                positionTree->secondaryKeyTreeInsert(player);
                FGPTree->secondaryKeyTreeInsert(player);
                FTPTree->secondaryKeyTreeInsert(player);
                TTPTree->secondaryKeyTreeInsert(player);
                PTSTree->secondaryKeyTreeInsert(player);
                count++;
            }
        }
        index++;
    }
    
    cout << endl;
    infile.close();
}

/** This function is togive the user option whether to rehash
 @param hashTable that is a hash table */
void reHashingOption(HashTable<string, NBAPlayer*> *hashTable) {
    if (hashTable->getLoadFactor() > 75) {
        string option;
        cout << "Now, your load factor is " << hashTable->getLoadFactor() << "% ! Do you want to rehash the hash table? (Y or N)\n";
        getline(cin, option);
        if (option == "Y" || option == "y") {
            hashTable->reHash();
        }
    }
}

/** This function is to show the statistic of the hash table
 and the efficiency between linked list, BST, andd hashtable */
void showStatistic() {
    
    ifstream infile;
    infile.open("NBAPlayerSta.txt");
    
    // demonstrate the bad hash function
    HashTable<string, NBAPlayer*> *badHashTable = new HashTable<string, NBAPlayer*>;
    
    HashTable<string, NBAPlayer*> *hashTable = new HashTable<string, NBAPlayer*>;
    BinarySearchTree<NBAPlayer*> *nameTree = new BinarySearchTree<NBAPlayer*>(compareByName);
    List<NBAPlayer*> *list = new List<NBAPlayer*>(compareByName);
    
    NBAPlayer **playerArray = new NBAPlayer*[4000];
    for (int i = 0; i < 4000; i++) {
        playerArray[i] = NULL;
    }
    
    string name;
    string team;
    string position;
    string FGP;
    string FTP;
    string TPP;
    string PTS;
    int index = 0;
    
    getline(infile, team, ',');
    getline(infile, position, ',');
    getline(infile, FGP, ',');
    getline(infile, FTP, ',');
    getline(infile, TPP, ',');
    getline(infile, PTS);
    
    while (getline(infile, name, ',')) {
        getline(infile, team, ',');
        getline(infile, position, ',');
        getline(infile, FGP, ',');
        getline(infile, FTP, ',');
        getline(infile, TPP, ',');
        getline(infile, PTS);
        
        if (name != "") {
            NBAPlayer playerObj(name, team, position, FGP, FTP, TPP, PTS);
            NBAPlayer *player = new NBAPlayer;
            *player = playerObj;
            
            playerArray[index] = player;
            
            badHashTable->badInsertEntry(name, player);
            hashTable->insertEntry(name, player);
            nameTree->uniqueKeyTreeInsert(player);
            list->insertNode(player);
            index++;
        }
    }
    
    // statistic of the current hash table
    cout << "\n\nStatistic of the regular hash table\n";
    cout << "-------------------------------------\n";
    cout << "Count: " << hashTable->getCount() << endl;
    cout << "Load Factor: " << hashTable->getLoadFactor() << "%\n";
    cout << "Collision: " << hashTable->getCollision() << endl ;
    cout << "Collision Rate: " << hashTable->getCollisionRate() << endl << endl;
    
    // statistic of the bad hash table
    cout << "\n\nStatistic of a bad hash table\n";
    cout << "-------------------------------------\n";
    cout << "Count: " << badHashTable->getCount() << endl;
    cout << "Load Factor: " << badHashTable->getLoadFactor() << "%\n";
    cout << "Collision: " << badHashTable->getCollision() << endl;
    cout << "Collision Rate: " << badHashTable->getCollisionRate() << endl << endl;
    delete badHashTable;
    
    infile.close();
    
    // demonstrate the effect of rehashing
    cout << "How does the rehashing works\n";
    cout << "-------------------------------------\n";
    
    // 1000 dataset
    infile.open("1000Dataset.txt");
    
    HashTable<string, NBAPlayer*> *newHashTable = new HashTable<string, NBAPlayer*>;
    newHashTable->determineHashSize(1000);
    int count = 0;
    while (getline(infile, name, ',')) {
        getline(infile, team, ',');
        getline(infile, position, ',');
        getline(infile, FGP, ',');
        getline(infile, FTP, ',');
        getline(infile, TPP, ',');
        getline(infile, PTS);
        
        if (name != "") {
            NBAPlayer playerObj(name, team, position, FGP, FTP, TPP, PTS);
            NBAPlayer *player;
            player = &playerObj;
            newHashTable->insertEntry(name, player);
            count++;
        }
    }
    //cout << count << endl;
    infile.close();
    
    //hashTable->traverseHash(displayName);
    cout << endl;
    cout << "\t\t1000 Dataset\n";
    cout << "-------------------------------------\n";
    cout << "Count: " << newHashTable->getCount() << endl;
    cout << "Load Factor: " << newHashTable->getLoadFactor() << "%\n";
    cout << "Collision: " << newHashTable->getCollision() << endl;
    cout << "Collision Rate: " << newHashTable->getCollisionRate() << endl << endl;
    
    // 3000 dataset
    infile.open("3000Dataset.txt");
    
    while (getline(infile, name, ',')) {
        getline(infile, team, ',');
        getline(infile, position, ',');
        getline(infile, FGP, ',');
        getline(infile, FTP, ',');
        getline(infile, TPP, ',');
        getline(infile, PTS);
        
        if (name != "") {
            NBAPlayer playerObj(name, team, position, FGP, FTP, TPP, PTS);
            NBAPlayer *player;
            player = &playerObj;
            
            newHashTable->insertEntry(name, player);
        }
    }
    
    infile.close();
    
    cout << "\t\t3000 Dataset\n";
    cout << "-------------------------------------\n";
    cout << "Count: " << newHashTable->getCount() << endl;
    cout << "Load Factor: " << newHashTable->getLoadFactor() << "%\n";
    cout << "Collision: " << newHashTable->getCollision() << endl;
    cout << "Collision Rate: " << newHashTable->getCollisionRate() << endl << endl;
    
    newHashTable->reHash();
    
    cout << "\t\tAfter rehashing\n";
    cout << "-------------------------------------\n";
    cout << "Count: " << newHashTable->getCount() << endl;
    cout << "Load Factor: " << newHashTable->getLoadFactor() << "%\n";
    cout << "Collision: " << newHashTable->getCollision() << endl;
    cout << "Collision Rate: " << newHashTable->getCollisionRate() << endl << endl;
    
    cout << "Algorithm efficiency\n";
    cout << "-------------------------------------\n";
    
    string testPlayer[10] = {"Lebron James", "Michael Jordan", "Stephen Curry", "Dwyane Wade", "Ray Allen", "Kyrie Irving", "James Harden", "Russell Westbrook", "Derrick Rose", "JaVale McGee"};
    time_t time1, time2;
    
    NBAPlayer playerObj;
    NBAPlayer *player;
    player = &playerObj;
    
    // estimate the time by using linked list
    time(&time1);
    for (int k = 0; k < 5000; k++) {
        for (int i = 0; i < 10; i++) {
            player->setName(testPlayer[i]);
            list->searchNode(player);
        }
    }
    time(&time2);
    double listTimeInterval = difftime(time2, time1);
    cout << "The time of Linked List: " << listTimeInterval << endl;
    
    // estimate the time by using BST search
    time(&time1);
    for (int k = 0; k < 50000; k++) {
        for (int i = 0; i < 10; i++) {
            player->setName(testPlayer[i]);
            nameTree->getEntryUniqueTree(player, player);
        }
    }
    time(&time2);
    double bstTimeInterval = difftime(time2, time1);
    cout << "The time of BST: " << bstTimeInterval << endl;
    
    // estimate the time by using hash table search
    time(&time1);
    for (int k = 0; k < 500000; k++) {
        for (int i = 0; i < 10; i++) {
            player->setName(testPlayer[i]);
            hashTable->searchEntry(testPlayer[i], player);
        }
    }
    time(&time2);
    double hashTimeInterval = difftime(time2, time1);
    cout << "The time of Hash table: " << hashTimeInterval << endl;
    
    delete hashTable;
    delete nameTree;
    delete list;
    for (int i = 0; i < 4000; i++) {
        if (playerArray[i] != NULL) {
            delete playerArray[i];
        }
    }
    delete[] playerArray;
    
}

//-----------------------------------------------------------------------------------------

// CASE D: Function to display Inorder, Preorder, and Postprder traversals.

void depthFirstTraversals (BinarySearchTree<NBAPlayer*> *nameTree, BinarySearchTree<NBAPlayer*> * PTSTree)
{
    // NAME TREE
    cout << "Recur. InOrder   NAME - \n";
    cout << setw(15) << left  << "Name"
    << setw(12)  << right << "Team" << "   "
    << setw(7) << left  << "Position" << "  "
    << setw(10) << left  << "Field Goal Percentage" << "  "
    << setw(10) << left  << "Free Throw Percentage" << "    "
    << setw(10) << left  << "Triple Point Percentage" << "  "
    << setw(7) << "Total Points" << endl;
    cout << "===========          ======= ========= ======================= =======================  ======================= ===============\n";
    nameTree->inOrder(displayPlayer)  ; cout << endl << endl;
    
    cout << "Recur. PreOrder  NAME - \n";
    cout << setw(15) << left  << "Name"
    << setw(12)  << right << "Team" << "   "
    << setw(7) << left  << "Position" << "  "
    << setw(10) << left  << "Field Goal Percentage" << "  "
    << setw(10) << left  << "Free Throw Percentage" << "    "
    << setw(10) << left  << "Triple Point Percentage" << "  "
    << setw(7) << "Total Points" << endl;
    cout << "===========          ======= ========= ======================= =======================  ======================= ===============\n";
    nameTree->preOrder(displayPlayer) ; cout << endl << endl;
    
    cout << "Recur. PostOrder NAME - \n";
    cout << setw(15) << left  << "Name"
    << setw(12)  << right << "Team" << "   "
    << setw(7) << left  << "Position" << "  "
    << setw(10) << left  << "Field Goal Percentage" << "  "
    << setw(10) << left  << "Free Throw Percentage" << "    "
    << setw(10) << left  << "Triple Point Percentage" << "  "
    << setw(7) << "Total Points" << endl;
    cout << "===========          ======= ========= ======================= =======================  ======================= ===============\n";
    nameTree->postOrder(displayPlayer); cout << endl << endl;
    
    // PTS TREE
    cout << "Recur. InOrder   PTS - \n";
    cout << setw(15) << left  << "Name"
    << setw(12)  << right << "Team" << "   "
    << setw(7) << left  << "Position" << "  "
    << setw(10) << left  << "Field Goal Percentage" << "  "
    << setw(10) << left  << "Free Throw Percentage" << "    "
    << setw(10) << left  << "Triple Point Percentage" << "  "
    << setw(7) << "Total Points" << endl;
    cout << "===========          ======= ========= ======================= =======================  ======================= ===============\n";
    PTSTree->inOrder(displayPlayer)  ; cout << endl << endl;
    
    cout << "Recur. PreOrder  PTS - \n";
    cout << setw(15) << left  << "Name"
    << setw(12)  << right << "Team" << "   "
    << setw(7) << left  << "Position" << "  "
    << setw(10) << left  << "Field Goal Percentage" << "  "
    << setw(10) << left  << "Free Throw Percentage" << "    "
    << setw(10) << left  << "Triple Point Percentage" << "  "
    << setw(7) << "Total Points" << endl;
    cout << "===========          ======= ========= ======================= =======================  ======================= ===============\n";
    PTSTree->preOrder(displayPlayer) ; cout << endl << endl;
    
    cout << "Recur. PostOrder PTS - \n";
    cout << setw(15) << left  << "Name"
    << setw(12)  << right << "Team" << "   "
    << setw(7) << left  << "Position" << "  "
    << setw(10) << left  << "Field Goal Percentage" << "  "
    << setw(10) << left  << "Free Throw Percentage" << "    "
    << setw(10) << left  << "Triple Point Percentage" << "  "
    << setw(7) << "Total Points" << endl;
    cout << "===========          ======= ========= ======================= =======================  ======================= ===============\n";
    PTSTree->postOrder(displayPlayer); cout << endl << endl;
}
//-----------------------------------------------------------------------------------------


// CASE I: Function to display ITERATIVE Inorder, Preorder, and Postprder traversals.

void depthFirstTraversalsIterative(BinarySearchTree<NBAPlayer*> *nameTree, BinarySearchTree<NBAPlayer*> * PTSTree)
{
    // NAME TREE
    cout << "Iter. InOrder   NAME  -  \n ";
    cout << setw(15) << left  << "Name"
    << setw(12)  << right << "Team" << "   "
    << setw(7) << left  << "Position" << "  "
    << setw(10) << left  << "Field Goal Percentage" << "  "
    << setw(10) << left  << "Free Throw Percentage" << "    "
    << setw(10) << left  << "Triple Point Percentage" << "  "
    << setw(7) << "Total Points" << endl;
    cout << "===========          ======= ========= ======================= =======================  ======================= ===============\n";
    nameTree->iterativeInOrder(displayPlayer);
    cout << endl << endl;
    
    cout << "Iter. PreOrder  NAME  -  \n ";
    cout << setw(15) << left  << "Name"
    << setw(12)  << right << "Team" << "   "
    << setw(7) << left  << "Position" << "  "
    << setw(10) << left  << "Field Goal Percentage" << "  "
    << setw(10) << left  << "Free Throw Percentage" << "    "
    << setw(10) << left  << "Triple Point Percentage" << "  "
    << setw(7) << "Total Points" << endl;
    cout << "===========          ======= ========= ======================= =======================  ======================= ===============\n";
    nameTree->iterativePreOrder(displayPlayer);
    cout << endl << endl;
    
    cout << "Iter. PostOrder NAME  -  \n ";
    cout << setw(15) << left  << "Name"
    << setw(12)  << right << "Team" << "   "
    << setw(7) << left  << "Position" << "  "
    << setw(10) << left  << "Field Goal Percentage" << "  "
    << setw(10) << left  << "Free Throw Percentage" << "    "
    << setw(10) << left  << "Triple Point Percentage" << "  "
    << setw(7) << "Total Points" << endl;
    cout << "===========          ======= ========= ======================= =======================  ======================= ===============\n";
    nameTree->iterativePostOrder(displayPlayer);
    cout << endl << endl;
    
    // PTS TREE
    cout << "Iter. InOrder   PTS  - \n";
    cout << setw(15) << left  << "Name"
    << setw(12)  << right << "Team" << "   "
    << setw(7) << left  << "Position" << "  "
    << setw(10) << left  << "Field Goal Percentage" << "  "
    << setw(10) << left  << "Free Throw Percentage" << "    "
    << setw(10) << left  << "Triple Point Percentage" << "  "
    << setw(7) << "Total Points" << endl;
    cout << "===========          ======= ========= ======================= =======================  ======================= ===============\n";
    PTSTree->iterativeInOrder(displayPlayer);
    cout << endl << endl;
    
    cout << "Iter. PreOrder  PTS  - \n";
    cout << setw(15) << left  << "Name"
    << setw(12)  << right << "Team" << "   "
    << setw(7) << left  << "Position" << "  "
    << setw(10) << left  << "Field Goal Percentage" << "  "
    << setw(10) << left  << "Free Throw Percentage" << "    "
    << setw(10) << left  << "Triple Point Percentage" << "  "
    << setw(7) << "Total Points" << endl;
    cout << "===========          ======= ========= ======================= =======================  ======================= ===============\n";
    PTSTree->iterativePreOrder(displayPlayer);
    cout << endl << endl;
    
    cout << "Iter. PostOrder PTS  - \n";
    cout << setw(15) << left  << "Name"
    << setw(12)  << right << "Team" << "   "
    << setw(7) << left  << "Position" << "  "
    << setw(10) << left  << "Field Goal Percentage" << "  "
    << setw(10) << left  << "Free Throw Percentage" << "    "
    << setw(10) << left  << "Triple Point Percentage" << "  "
    << setw(7) << "Total Points" << endl;
    cout << "===========          ======= ========= ======================= =======================  ======================= ===============\n";
    PTSTree->iterativePostOrder(displayPlayer);
    cout << endl << endl;
}
//-----------------------------------------------------------------------------------------


// CASE B: Function to display tree traversal by level, using queue.

void breadthFirstTraversal(BinarySearchTree<NBAPlayer*> *nameTree, BinarySearchTree<NBAPlayer*> *PTSTree)
{
    // Display breadth-first traversal
    cout << "BF. NAME    Tree  - \n";
    cout << setw(15) << left  << "Name"
    << setw(12)  << right << "Team" << "   "
    << setw(7) << left  << "Position" << "  "
    << setw(10) << left  << "Field Goal Percentage" << "  "
    << setw(10) << left  << "Free Throw Percentage" << "    "
    << setw(10) << left  << "Triple Point Percentage" << "  "
    << setw(7) << "Total Points" << endl;
    cout << "===========          ======= ========= ======================= =======================  ======================= ===============\n";
    nameTree->breadthFirst(displayPlayer);
    cout << endl << endl;
    
    cout << "BF. PTS  Tree  - \n";
    cout << setw(15) << left  << "Name"
    << setw(12)  << right << "Team" << "   "
    << setw(7) << left  << "Position" << "  "
    << setw(10) << left  << "Field Goal Percentage" << "  "
    << setw(10) << left  << "Free Throw Percentage" << "    "
    << setw(10) << left  << "Triple Point Percentage" << "  "
    << setw(7) << "Total Points" << endl;
    cout << "===========          ======= ========= ======================= =======================  ======================= ===============\n";
    PTSTree->breadthFirst(displayPlayer);
    cout << endl << endl;
}
//-----------------------------------------------------------------------------------------


// CASE S: Function to search for a user-inputted target in the tree and display its data.

void searchNameTree(BinarySearchTree<NBAPlayer*>* nameTree)
{
    NBAPlayer *targetIDObject = new NBAPlayer;
    
    NBAPlayer *returnedItem;
    
    
    string targetName;
    
    getline(cin, targetName);         // Take in user input.
    targetIDObject->firstLetterCaps(targetName);
    targetIDObject->setName(targetName);
    
    cout << endl << endl;
    
    // If search was successful, display found item data.
    if (nameTree->getEntryUniqueTree(targetIDObject, returnedItem))
    {
        cout << "Item found: " << targetName << endl << endl;
        cout << *returnedItem;
    }
    
    // Search failed - display failure to user.
    else
    {
        cout << "Item not found. " << endl << endl;
    }
    
    // Delete dynamically allocated objects.
    delete targetIDObject;
}
//-----------------------------------------------------------------------------------------


// CASE Z: Function to search for a user-inputted target in the tree and display its data.

void searchPTSTree(BinarySearchTree<NBAPlayer*>* totalPointTree)
{
    vector<NBAPlayer*> storeAllFound;
    
    NBAPlayer *targetNBAPlayerObject = new NBAPlayer; // Dynamically allocate NBAPlayer object to
    
    bool flag = false;
    // store Total Points entered by user.
    string totalPoints;  // Store user input (Total Points).
    
    do
    {
        cout << "Please enter a total number of points to be searched in the Total Point Tree:\n\n\n";
        getline(cin, totalPoints);
        if (cin.fail())
        {
            cout << "\n\nInput is not an integer. Please try again." << endl << endl << endl;
            flag = false;
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        else
        {
            flag = true;
        }
    }
    while(flag == false);
    
    targetNBAPlayerObject->setPTS(totalPoints); // Set total points
    
    cout << endl << endl;
    
    // If search was successful, display found item data.
    if (totalPointTree->getEntrySecondaryTree(targetNBAPlayerObject, storeAllFound))
    {
        cout << "Item found: " << totalPoints << endl << endl << endl;
        
        for (unsigned int i = 0; i < storeAllFound.size(); i++)
        {
            cout << *storeAllFound[i] << endl << endl;
        }
    }
    // Search failed - display failure to user.
    else
    {
        cout << "Item not found. " << endl << endl;
    }
    
    // Delete dynamically allocated objects.
    delete targetNBAPlayerObject;
}
//-----------------------------------------------------------------------------------------


// CASE D: Function to delete a user-inputted node in the tree.

void deleteANode(BinarySearchTree<NBAPlayer*> *nameTree, BinarySearchTree<NBAPlayer*> *teamTree, BinarySearchTree<NBAPlayer*> *positionTree,BinarySearchTree<NBAPlayer*> *FGPTree,BinarySearchTree<NBAPlayer*> *FTPTree,BinarySearchTree<NBAPlayer*> *TPPTree,BinarySearchTree<NBAPlayer*> *PTSTree, HashTable<string, NBAPlayer*> *hashTable, Stack<NBAPlayer*> *stack)
{
    NBAPlayer *targetPlayerObject;
    NBAPlayer player;
    targetPlayerObject = &player;
    
    cout << "\n\n\nPlease enter a Player Name to delete from all Trees:\n\n\n"; // Prompt user to enter Player Name.
    
    string deleteTarget;                   // To store user input.
    
    getline(cin, deleteTarget);            // Get user input.
    targetPlayerObject->firstLetterCaps(deleteTarget);
    targetPlayerObject->setName(deleteTarget); // Set inputted Player Name.
    
    cout << endl << endl;
    
    if (nameTree->deleteUniqueKey(targetPlayerObject))
    {
        
        cout << "\nNBA Player successfully deleted.\n\n";
        teamTree->deleteOtherKeys(targetPlayerObject, targetPlayerObject->getName());
        PTSTree->deleteOtherKeys(targetPlayerObject, targetPlayerObject->getName());
        positionTree->deleteOtherKeys(targetPlayerObject, targetPlayerObject->getName());
        FGPTree->deleteOtherKeys(targetPlayerObject, targetPlayerObject->getName());
        FTPTree->deleteOtherKeys(targetPlayerObject, targetPlayerObject->getName());
        TPPTree->deleteOtherKeys(targetPlayerObject, targetPlayerObject->getName());
        
        hashTable->removeEntry(targetPlayerObject->getName());
        stack->push(targetPlayerObject);
        reHashingOption(hashTable);
    }
    else
    {
        cout << "Deletion failed. " << endl << endl;
    }
}

//-----------------------------------------------------------------------------------------

// CASE C: Undo delete
void undoDelete(BinarySearchTree<NBAPlayer*> *nameTree, BinarySearchTree<NBAPlayer*> *teamTree, BinarySearchTree<NBAPlayer*> *positionTree,BinarySearchTree<NBAPlayer*> *FGPTree,BinarySearchTree<NBAPlayer*> *FTPTree,BinarySearchTree<NBAPlayer*> *TPPTree,BinarySearchTree<NBAPlayer*> *PTSTree, HashTable<string, NBAPlayer*> *hashTable, Stack<NBAPlayer*> *stack) {
    
    if (stack->isEmpty()) {
        cout << "No delete to undo.\n";
        cout << "=================================================================\n";
        return ;
    }
    NBAPlayer player;
    NBAPlayer *playerPtr;
    playerPtr = &player;
    
    stack->pop(playerPtr);
    
    nameTree->uniqueKeyTreeInsert(playerPtr);
    teamTree->secondaryKeyTreeInsert(playerPtr);
    positionTree->secondaryKeyTreeInsert(playerPtr);
    FGPTree->secondaryKeyTreeInsert(playerPtr);
    FTPTree->secondaryKeyTreeInsert(playerPtr);
    TPPTree->secondaryKeyTreeInsert(playerPtr);
    PTSTree->secondaryKeyTreeInsert(playerPtr);
    hashTable->insertEntry(playerPtr->getName(), playerPtr);
    
    cout << playerPtr->getName() << " has been put back.\n";
    cout << *playerPtr;
}

//-----------------------------------------------------------------------------------------

// CASE N: Function to insert a new player.

void insertPlayer(BinarySearchTree<NBAPlayer*> *nameTree, BinarySearchTree<NBAPlayer*> *teamTree, BinarySearchTree<NBAPlayer*> *positionTree,BinarySearchTree<NBAPlayer*> *FGPTree,BinarySearchTree<NBAPlayer*> *FTPTree,BinarySearchTree<NBAPlayer*> *TPPTree,BinarySearchTree<NBAPlayer*> *PTSTree, HashTable<string, NBAPlayer*> *hashTable, NBAPlayer *playerArray[4000], int &count) {
    
    bool flag = false;
    string name;
    string FGP;
    string team;
    string position;
    string FTP;
    string TPP;
    string PTS;
    string option;
    
    do
    {
        NBAPlayer *aPlayer = new NBAPlayer;
        //-----------------------------------------------------------------------------------
        // NBAPlayer Name Input.
        do
        {
            cout << "Enter a Player Name (Ex. Michael Jordan): " << endl << endl << endl;
            getline(cin, name);
            flag = aPlayer->cannotBeNumbers(name);
        }
        while (flag == false);
        aPlayer->firstLetterCaps(name);
        
        //-----------------------------------------------------------------------------------
        // Field Goal Percentage Input.
        do
        {
            cout << "\n\nEnter a Field Goal Percentage (Ex. 0.246): " << endl << endl << endl;
            getline(cin, FGP);
            flag = aPlayer->cannotBeLetters(FGP);
        }
        while (flag == false);
        
        //-----------------------------------------------------------------------------------
        // Team Input.
        do
        {
            cout << "\n\nEnter a Team in abbreviation form (Ex. INO (Indianapolis Olympians)): " << endl << endl << endl;
            getline(cin, team);
            flag = aPlayer->cannotBeNumbers(team);
        }
        while (flag == false);
        aPlayer->allCaps(team);
        
        //-----------------------------------------------------------------------------------
        // Position Input.
        do
        {
            cout << "\n\nEnter a Position in abbreviation form (Ex. GF (Guard-Forward)): " << endl << endl << endl;
            getline(cin, position);
            flag = aPlayer->cannotBeNumbers(position);
        }
        while (flag == false);
        aPlayer->allCaps(position);
        
        //-----------------------------------------------------------------------------------
        // Free Throw Percentage Input.
        do
        {
            cout << "\n\nEnter a Free Throw Percentage (Ex. 0.55): " << endl << endl << endl;
            getline(cin, FTP);
            flag = aPlayer->cannotBeLetters(FTP);
        }
        while (flag == false);
        
        //-----------------------------------------------------------------------------------
        // Three Pointer Percentage Input.
        do
        {
            cout << "\n\nEnter a Three Pointer Percentage (Ex. 0.473): " << endl << endl << endl;
            getline(cin, TPP);
            flag = aPlayer->cannotBeLetters(TPP);
        }
        while (flag == false);
        
        //-----------------------------------------------------------------------------------
        // Total Points Input.
        do
        {
            cout << "\n\nEnter Total Points Scored (Ex. 217): " << endl << endl << endl;
            getline(cin, PTS);
            flag = aPlayer->cannotBeLetters(PTS);
        }
        while (flag == false);
        
        //-----------------------------------------------------------------------------------
        aPlayer->setName(name);
        aPlayer->setTeam(team);
        aPlayer->setPosition(position);
        aPlayer->setFGP(FGP);
        aPlayer->setFTP(FTP);
        aPlayer->setTPP(TPP);
        aPlayer->setPTS(PTS);
        
        if (hashTable->searchEntry(name, aPlayer))
        {
            cout << "Duplicate NBAPlayer entry detected! Player not inserted. \n";
        }
        else
        {
            // Insert it to database
            nameTree->uniqueKeyTreeInsert(aPlayer);
            teamTree->secondaryKeyTreeInsert(aPlayer);
            positionTree->secondaryKeyTreeInsert(aPlayer);
            FGPTree->secondaryKeyTreeInsert(aPlayer);
            FTPTree->secondaryKeyTreeInsert(aPlayer);
            TPPTree->secondaryKeyTreeInsert(aPlayer);
            PTSTree->secondaryKeyTreeInsert(aPlayer);
            hashTable->insertEntry(aPlayer->getName(), aPlayer);
            playerArray[count] = aPlayer;
            count++;
            cout << "The insertion is completed.\n";
        }
        
        reHashingOption(hashTable);
        
        cout << "Would you like to insert more? (Y for Yes, N for No):" << endl << endl << endl;
        getline(cin, option);
        cout << "\n\n-------------------------------------------------------------" << endl << endl;
        
    } while (option == "Y" || option == "y");
}

//-----------------------------------------------------------------------------------------

// CASE U: Function to update some info in the database.
void updatePlayer(BinarySearchTree<NBAPlayer*> *nameTree, BinarySearchTree<NBAPlayer*> *teamTree, BinarySearchTree<NBAPlayer*> *positionTree,BinarySearchTree<NBAPlayer*> *FGPTree,BinarySearchTree<NBAPlayer*> *FTPTree,BinarySearchTree<NBAPlayer*> *TPPTree,BinarySearchTree<NBAPlayer*> *PTSTree, HashTable<string, NBAPlayer*> *hashTable) {
    
    string option;
    bool flag = false;
    do {
        string name;
        NBAPlayer *player;
        cout << "Please enter the player's name that you want to update: \n\n";
        getline(cin, name);
        NBAPlayer temp;
        temp.firstLetterCaps(name);
        
        // check if we have target in hash table
        if (hashTable->searchEntry(name, player)) {
            
            string team;
            string position;
            string FGP;
            string FTP;
            string TPP;
            string PTS;
            string updateoption;
            
            do {
                cout << "\nN - name\n";
                cout << "T - team\n";
                cout << "P - position\n";
                cout << "FGP - field goal percentage\n";
                cout << "FTP - free throw percentage\n";
                cout << "TPP - three point percentage\n";
                cout << "PTS - total points\n";
                cout << "D - done\n";
                cout << "\nWhich field you would like to update: \n\n";
                getline(cin, updateoption);
                player->allCaps(updateoption);
                cout << endl;
                
                if (updateoption == "N")
                {
                    NBAPlayer *newPlayer = new NBAPlayer;
                    do
                    {
                        cout << "Please enter the new name: ";
                        getline(cin, name);
                        flag = newPlayer->cannotBeNumbers(name);
                    }
                    while (flag == false);
                    newPlayer->firstLetterCaps(name);
                    *newPlayer = *player;
                    newPlayer->setName(name);
                    *player = *newPlayer;
                    displayPlayer(player);
                    delete newPlayer;
                }
                else if (updateoption == "T")
                {
                    NBAPlayer *newPlayer = new NBAPlayer;
                    do
                    {
                        cout << "Please enter the new team: ";
                        getline(cin, team);
                        flag = newPlayer->cannotBeNumbers(team);
                    }
                    while (flag == false);
                    newPlayer->allCaps(team);
                    *newPlayer = *player;
                    newPlayer->setTeam(team);
                    *player = *newPlayer;
                    displayPlayer(player);
                    delete newPlayer;
                }
                else if (updateoption == "P")
                {
                    NBAPlayer *newPlayer = new NBAPlayer;
                    do
                    {
                        cout << "Please enter the new position: ";
                        getline(cin, position);
                        flag = newPlayer->cannotBeNumbers(position);
                    }
                    while (flag == false);
                    newPlayer->allCaps(position);
                    *newPlayer = *player;
                    newPlayer->setPosition(position);
                    *player = *newPlayer;
                    displayPlayer(player);
                    delete newPlayer;
                }
                else if (updateoption == "FGP")
                {
                    NBAPlayer *newPlayer = new NBAPlayer;
                    do
                    {
                        cout << "Please enter the new field goal percentage: ";
                        getline(cin, FGP);
                        flag = newPlayer->cannotBeLetters(FGP);
                    }
                    while (flag == false);
                    *newPlayer = *player;
                    newPlayer->setFGP(FGP);
                    *player = *newPlayer;
                    displayPlayer(player);
                    delete newPlayer;
                }
                else if (updateoption == "FTP")
                {
                    NBAPlayer *newPlayer = new NBAPlayer;
                    do
                    {
                        cout << "Please enter the new free throw percentage: ";
                        getline(cin, FTP);
                        flag = newPlayer->cannotBeLetters(FTP);
                    }
                    while (flag == false);
                    *newPlayer = *player;
                    newPlayer->setFTP(FTP);
                    *player = *newPlayer;
                    displayPlayer(player);
                    delete newPlayer;
                }
                else if (updateoption == "TPP")
                {
                    NBAPlayer *newPlayer = new NBAPlayer;
                    do
                    {
                        cout << "Please enter the new three pointer percentage: ";
                        getline(cin, TPP);
                        flag = newPlayer->cannotBeLetters(TPP);
                    }
                    while (flag == false);
                    *newPlayer = *player;
                    newPlayer->setTPP(TPP);
                    *player = *newPlayer;
                    displayPlayer(player);
                    delete newPlayer;
                }
                else if (updateoption == "PTS")
                {
                    NBAPlayer *newPlayer = new NBAPlayer;
                    do
                    {
                        cout << "Please enter the new total points: ";
                        getline(cin, PTS);
                        flag = newPlayer->cannotBeLetters(PTS);
                    }
                    while (flag == false);
                    *newPlayer = *player;
                    newPlayer->setPTS(PTS);
                    *player = *newPlayer;
                    displayPlayer(player);
                    delete newPlayer;
                }
                else if (updateoption == "D") {
                    break;
                }
                else
                {
                    cout << "SElECTION NOT VALID\n";
                }
            } while (updateoption != "D");
        }
        
        // not in the hash table
        else {
            cout << "Sorry, " << name << " can't be found.\n";
        }
        
        cout << "Would you like to update more? (Y for Yes, N for No):" << endl << endl << endl;
        getline(cin, option);
        cout << endl << endl;
    } while (option == "Y" || option == "y");
}

//-----------------------------------------------------------------------------------------

// CASE M: Function to find the smallest item in the tree and display its data.

void findTheSmallest(BinarySearchTree<NBAPlayer*> *playerNameTree)
{
    NBAPlayer *playerPtr;
    NBAPlayer player;
    playerPtr = &player;
    
    playerNameTree->findSmallest(playerPtr);
    
    cout << "The first player in alphabatical order: ";
    cout << *playerPtr;
}

//-----------------------------------------------------------------------------------------

// CASE X: Function to find the largest item in the tree and display its data.

void findTheLargest(BinarySearchTree<NBAPlayer*> *FGPTree, BinarySearchTree<NBAPlayer*> *FTPTree, BinarySearchTree<NBAPlayer*> *TPPTree, BinarySearchTree<NBAPlayer*> *PTSTree, Stack<NBAPlayer*> *stack)
{
    NBAPlayer *playerPtr[10];
    NBAPlayer player[10];
    for (int i = 0; i <10; i++) {
        playerPtr[i] = &(player[i]);
    }
    
    // field goal percentage
    cout << "\n\nThe top ten basketball players by field goal percentage:\n\n";
    for (int i = 0; i < 10; i++) {
        FGPTree->findLargest(playerPtr[i]);
        FGPTree->deleteOtherKeys(playerPtr[i], playerPtr[i]->getName());
        stack->push(playerPtr[i]);
        cout << i+1 << ". " << *playerPtr[i];
    }
    
    for (int i = 0; i < 10; i++) {
        stack->pop(playerPtr[i]);
        FGPTree->secondaryKeyTreeInsert(playerPtr[i]);
    }
    
    // free throw percentage
    cout << "\n\nThe top ten basketball players by free throw percentage:\n\n";
    for (int i = 0; i < 10; i++) {
        FTPTree->findLargest(playerPtr[i]);
        FTPTree->deleteOtherKeys(playerPtr[i], playerPtr[i]->getName());
        stack->push(playerPtr[i]);
        cout << i+1 << ". " << *playerPtr[i];
    }
    
    for (int i = 0; i < 10; i++) {
        stack->pop(playerPtr[i]);
        FTPTree->secondaryKeyTreeInsert(playerPtr[i]);
    }
    
    // three points percentage
    cout << "\n\nThe top ten basketball players by three points percentage:\n\n";
    for (int i = 0; i < 10; i++) {
        TPPTree->findLargest(playerPtr[i]);
        TPPTree->deleteOtherKeys(playerPtr[i],playerPtr[i]->getName());
        stack->push(playerPtr[i]);
        cout << i+1 << ". " << *playerPtr[i];
    }
    
    for (int i = 0; i < 10; i++) {
        stack->pop(playerPtr[i]);
        TPPTree->secondaryKeyTreeInsert(playerPtr[i]);
    }
    
    // total points
    cout << "\n\nThe top ten basketball players by total points:\n\n";
    for (int i = 0; i < 10; i++) {
        PTSTree->findLargest(playerPtr[i]);
        PTSTree->deleteOtherKeys(playerPtr[i], playerPtr[i]->getName());
        stack->push(playerPtr[i]);
        cout << i+1 << ". " << *playerPtr[i];
    }
    
    for (int i = 0; i < 10; i++) {
        stack->pop(playerPtr[i]);
        PTSTree->secondaryKeyTreeInsert(playerPtr[i]);
    }
}

//-----------------------------------------------------------------------------------------

// CASE T: Function to print the tree in an indented structure.

void printIndented(BinarySearchTree<NBAPlayer*> *nameTree,  BinarySearchTree<NBAPlayer*> *PTSTree)
{
    int keepTrack = 0;
    
    cout << "\t\t\t\t\t\t\t\t<---- NAME TREE: " << endl << endl;
    nameTree->printIndented   (displayName, keepTrack); cout << endl;    // Call printIndented function - ID.
    cout << "\t\t\t\t\t\t\t\t<---- PTS TREE: " << endl << endl;
    PTSTree->printIndented (displayPTS, keepTrack); cout << endl;  // Call printIndented function - NAME.
}
//-----------------------------------------------------------------------------------------

// Display functions to pass to BST traverse functions

void displayPlayer(NBAPlayer *anItem) {
    cout << *anItem;
}

void displayName(NBAPlayer*  anItem) {
    cout << anItem->getName() << "\n";
}
void displayTeam(NBAPlayer*  anItem) {
    cout << anItem->getTeam() << "\n";
}
void displayPosition(NBAPlayer*  anItem) {
    cout << anItem->getPosition() << "\n";
}
void displayFGP(NBAPlayer*  anItem) {
    cout << anItem->getFGP() << "\n";
}

void displayFTP(NBAPlayer*  anItem) {
    cout << anItem->getFTP() << " ";
}

void displayTPP(NBAPlayer*  anItem) {
    cout << anItem->getTPP() << " ";
}

void displayPTS(NBAPlayer*  anItem) {
    cout << anItem->getPTS() << " ";
}

void savePlayerToFile(NBAPlayer *anItem, ofstream &outfile) {
    outfile << anItem->getName() << " ";
    outfile << anItem->getTeam() << " ";
    outfile << anItem->getPosition() << " ";
    outfile << anItem->getFGP() << " ";
    outfile << anItem->getFTP() << " ";
    outfile << anItem->getTPP() << " ";
    outfile << anItem->getPTS() << endl;
}


//-----------------------------------------------------------------------------------------

// Validate if user input is valid input size (one character).

bool checkInput(string userInput)
{
    if (userInput.size() > 1)
    {
        cout << userInput << endl;
        cout << "\n\nInput cannot be more than one character.";
        return false;
    }
    return true;
}
//-----------------------------------------------------------------------------------------

// Function to display welcome message to user.

void welcomeMessage()
{
    cout << "WELCOME TO THE BINARY SEARCH TREE DATABASE PROGRAM." << endl << endl;
}
//-----------------------------------------------------------------------------------------

// Function to display goodbye message to user.

void goodbyeMessage()
{
    cout << "THANK YOU FOR USING THE BINARY SEARCH TREE PROGRAM." << endl << endl;
}
//-----------------------------------------------------------------------------------------
