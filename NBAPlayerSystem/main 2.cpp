// Main Test Driver for BST
// Created by Frank M. Carrano and Tim Henry.
// Modified by: Amit Yativ, Alvin Lin
// IDE: Code::Blocks Xcode

// The purpose of this program is to build a Binary Search Tree by reading
// from a file and inserting data. Data inserted can be of any type
// as templates are utilized for the tree files, while actual input data
// and some changes to the main() driver are required. This program provides
// the user a switch-statement-driven Menu, where the user has the option
// of selecting from several choices - In Order, Preorder, Postorder traversal
// of tree, breadth-first traversal of tree, searching the tree, finding the
// smallest and largest values in tree, printing the tree by level with proper
// indentation, displaying a hidden feature, redisplaying the menu, and exiting
// the program. When the user selects a choice, it is checked for validity. If
// valid, the manager function corresponding to that choice is called and the
// task is executed, following with the redisplaying of the menu afterwards.
// This program goes on in a loop until the user selects the exit choice. If
// the user enters an invalid choice, an error is displayed and the menu is redisplayed.
// When the user exits the menu, a goodbye message is shown, the tree is destroyed,
// and the program ends.


#include "BinarySearchTree.h"  // BST ADT
#include "NBAPlayer.h"
#include "Compare.h"           // For compare functions
#include "HashTable.h"
#include <iostream>
#include <vector>
#include <stdlib.h>
#include <fstream>

using namespace std;

// Helper Functions:

// Display data
void displayName   (NBAPlayer & anItem);
void displayTeam (NBAPlayer & anItem);
void displayPosition  (NBAPlayer & anItem);
void displayFGP(NBAPlayer & anItem);
void displayFTP(NBAPlayer & anItem);
void displayTPP(NBAPlayer & anItem);
void displayPTS(NBAPlayer & anItem);

bool checkInput(string userInput);  // Check user input for valid size.
void displayMenu();                 // Display the main menu of the program.
void welcomeMessage();              // Display a welcome message.
void goodbyeMessage();              // Display a goodbye message.

//Manager Functions:

void buildData(string filename, BinarySearchTree<NBAPlayer> *, BinarySearchTree<NBAPlayer> *, BinarySearchTree<NBAPlayer> *,BinarySearchTree<NBAPlayer> *, BinarySearchTree<NBAPlayer> *, BinarySearchTree<NBAPlayer> *, BinarySearchTree<NBAPlayer> *, HashTable<string, NBAPlayer> *);

void depthFirstTraversals(BinarySearchTree<NBAPlayer> *,  BinarySearchTree<NBAPlayer> *);

void depthFirstTraversalsIterative(BinarySearchTree<NBAPlayer> *,  BinarySearchTree<NBAPlayer> *);

void breadthFirstTraversal(BinarySearchTree<NBAPlayer> *,  BinarySearchTree<NBAPlayer> *);

void deleteANode(BinarySearchTree<NBAPlayer> *, BinarySearchTree<NBAPlayer> *, BinarySearchTree<NBAPlayer> *,BinarySearchTree<NBAPlayer> *, BinarySearchTree<NBAPlayer> *, BinarySearchTree<NBAPlayer> *, BinarySearchTree<NBAPlayer> *);

void printIndented(BinarySearchTree<NBAPlayer> *nameTree,  BinarySearchTree<NBAPlayer> *PTSTree);

void menuDriver(char userInputChar, BinarySearchTree<NBAPlayer> *, BinarySearchTree<NBAPlayer> *, BinarySearchTree<NBAPlayer> *,BinarySearchTree<NBAPlayer> *, BinarySearchTree<NBAPlayer> *, BinarySearchTree<NBAPlayer> *, BinarySearchTree<NBAPlayer> *);

void searchNameTree(BinarySearchTree<NBAPlayer> *NameTree);                                                      // Search unique key tree according to user input.

void searchPTSTree(BinarySearchTree<NBAPlayer> *PTSTree);                                                      // Search secondary key tree according to user input.

void findTheSmallest(BinarySearchTree<NBAPlayer> *);                                                      // Find smallest node in tree.

void findTheLargest(BinarySearchTree<NBAPlayer> *);                                                      // Find largest node in tree.

int main()
{
    // Dynamically allocate new pointer to tree.
    BinarySearchTree<NBAPlayer>* nameTree = new BinarySearchTree<NBAPlayer>(compareByName);
    BinarySearchTree<NBAPlayer>* teamTree = new BinarySearchTree<NBAPlayer>(compareByTeam);
    BinarySearchTree<NBAPlayer>* positionTree = new BinarySearchTree<NBAPlayer>(compareByPosition);
    BinarySearchTree<NBAPlayer>* FGPTree = new BinarySearchTree<NBAPlayer>(compareByFGP);
    BinarySearchTree<NBAPlayer>* FTPTree = new BinarySearchTree<NBAPlayer>(compareByFTP);
    BinarySearchTree<NBAPlayer>* TPPTree = new BinarySearchTree<NBAPlayer>(compareByTPP);
    BinarySearchTree<NBAPlayer>* PTSTree = new BinarySearchTree<NBAPlayer>(compareByPTS);
    
    // hash table
    HashTable<string, NBAPlayer> *hashtable = new HashTable<string, NBAPlayer>;

    string filename = "NBAPlayerDateset.txt"; // Store name of input file.
    bool validInput = false;      // Store input validity.

    welcomeMessage();             // Display a welcome message.
    buildData(filename, nameTree, teamTree, positionTree, FGPTree, FTPTree, TPPTree, PTSTree, hashtable);  // Call buildBST function,
                                  // read from file and insert.
    string userInput = " ";       // To hold user input and validate.
    char userInputChar = ' ';     // To convert original input to char for menu switch.
    do                            // Main loop of program.
    {
        displayMenu();    // Display the menu.
        cin >> userInput; // Take in a user input.
        validInput = checkInput(userInput); // Check if input is one character or not.
        userInputChar = userInput[0];       // Convert input to char.
        userInputChar = toupper(userInputChar); // Make char uppercase.
        cout << endl << endl;
        if(userInputChar != 'E' && validInput == true) // If user input is not 'E' (Exit), and is valid)
            menuDriver(userInputChar, nameTree, teamTree, positionTree, FGPTree, FTPTree, TPPTree, PTSTree); // Call driver to begin actual program.
        cout << endl;
    }
    while (userInputChar != 'E' || validInput == false); // Keep looping until user enters
                                                         // 'E' (Exit) or invalid input.
    goodbyeMessage(); // Display goodbye message.

    // Delete dynamically allocated tree pointers.
    delete nameTree;
    delete teamTree;
    delete positionTree;
    delete FGPTree;
    delete FTPTree;
    delete TPPTree;
    delete PTSTree;

    return 0;         // End the program.
}
void menuDriver(char userInputChar, BinarySearchTree<NBAPlayer> *nameTree, BinarySearchTree<NBAPlayer> *teamTree, BinarySearchTree<NBAPlayer> *positionTree, BinarySearchTree<NBAPlayer> *FGPTree, BinarySearchTree<NBAPlayer> *FTPTree, BinarySearchTree<NBAPlayer> *TPPTree, BinarySearchTree<NBAPlayer> *PTSTree)
{
    // Driver of program, call manager functions depending on user choice.
    switch (userInputChar)
    {
        case 'R':
            cout << "RECURSIVE Inorder, Preorder and Postorder Toy ID Traversals:\n\n\n";
            depthFirstTraversals(nameTree, PTSTree);
                break;
        case 'I':
            cout << "ITERATIVE Inorder, Preorder and Postorder Toy ID Traversals:\n\n\n";
            depthFirstTraversalsIterative(nameTree, PTSTree);
                break;
        case 'B':
            cout << "Breadth-First Toy ID traversal by level:\n\n\n";
            breadthFirstTraversal(nameTree, PTSTree);
                break;
        case 'S':
            cout << "Please enter a Toy ID to be searched in the ID Tree:\n\n\n";
            searchNameTree(nameTree);
                break;
        case 'P':
            cout << "Please enter a Toy Name to be searched in the NAME Tree:\n\n\n";
            searchPTSTree(nameTree);
                break;
        case 'D':
            cout << "Current inOrder NAME Tree:    "     ; nameTree->   inOrder(displayName);
            cout << "\n\nCurrent inOrder TEAM Tree:  " ; teamTree-> inOrder(displayTeam);
            cout << "\n\nCurrent inOrder POSITION Tree:   " ; positionTree->  inOrder(displayPosition);
            cout << "\n\nCurrent inOrder FGP Tree: " ; FGPTree->inOrder(displayFGP);
            cout << "\n\nCurrent inOrder FTP Tree: " ; FTPTree->inOrder(displayFTP);
            cout << "\n\nCurrent inOrder TPP Tree: " ; TPPTree->inOrder(displayTPP);
            cout << "\n\nCurrent inOrder PTS Tree: " ; PTSTree->inOrder(displayPTS);
            deleteANode(nameTree, teamTree, positionTree, FGPTree, FTPTree, TPPTree, PTSTree);
                break;
        case 'M':
            cout << "Smallest NBAPlayer Node in tree:\n\n\n";
            findTheSmallest(nameTree);
                break;
        case 'X':
            cout << "Largest NBAPlayer Node in tree:\n\n\n";
            findTheLargest(nameTree);
                break;
        case 'T':
            cout << "Indented tree list:\n\n\n";
            printIndented(nameTree, PTSTree);
                break;
        case 'A':
            cout << "Developer names: Frank M. Carrano and Tim Henry.\n\n"
                 << "Edited by: Amit Yativ.\n\n";
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
         << " R - RECURSIVE Depth-First Traversal of tree: Inorder, Preorder, Postorder.\n"
         << " I - ITERATIVE Depth-First Traversal of tree: Inorder, Preorder, Postorder.\n"
         << " B - Breadth-First Traversal of tree by tree level.\n"
         << " S - Search for an item in the ID tree   (input: item ID).\n"
         << " P - Search for an item in the NAME tree (input: item NAME).\n"
         << " D - Delete an item in the tree (by item ID).\n"
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
void buildData(string filename, BinarySearchTree<NBAPlayer> *nameTree, BinarySearchTree<NBAPlayer> *teamTree, BinarySearchTree<NBAPlayer> *positionTree,BinarySearchTree<NBAPlayer> *FGPTree, BinarySearchTree<NBAPlayer> *FTPTree, BinarySearchTree<NBAPlayer> *TTPTree, BinarySearchTree<NBAPlayer> *PTSTree, HashTable<string, NBAPlayer> *hashTable)
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
            hashTable->insertEntry(name, *player);
            nameTree->uniqueKeyTreeInsert(*player);
            //teamTree->secondaryKeyTreeInsert(*player);
            //positionTree->secondaryKeyTreeInsert(*player);
            //FGPTree->secondaryKeyTreeInsert(*player);
            //FTPTree->secondaryKeyTreeInsert(*player);
            //TTPTree->secondaryKeyTreeInsert(*player);
            PTSTree->secondaryKeyTreeInsert(*player);
            
            delete player;
        /*
        // Error handling for duplicates.
        if (duplicateOrNot)
        {
            cout << "Duplicate toy entry detected!" << endl << endl;
        }
         */
        }
    
    // Always close the input file.
    }
    infile.close();
}
//-----------------------------------------------------------------------------------------


// CASE D: Function to display Inorder, Preorder, and Postprder traversals.

void depthFirstTraversals (BinarySearchTree<NBAPlayer> *nameTree, BinarySearchTree<NBAPlayer> * PTSTree)
{
    // NAME TREE
    cout << "Recur. InOrder   NAME - "; nameTree->inOrder(displayName)  ; cout << endl << endl;
    cout << "Recur. PreOrder  NAME - "; nameTree->preOrder(displayName) ; cout << endl << endl;
    cout << "Recur. PostOrder NAME - "; nameTree->postOrder(displayName); cout << endl << endl;
    // PTS TREE
    cout << "Recur. InOrder   PTS - "; PTSTree->inOrder(displayPTS)  ; cout << endl << endl;
    cout << "Recur. PreOrder  PTS - "; PTSTree->preOrder(displayPTS) ; cout << endl << endl;
    cout << "Recur. PostOrder PTS - "; PTSTree->postOrder(displayPTS); cout << endl << endl;
}
//-----------------------------------------------------------------------------------------


// CASE I: Function to display ITERATIVE Inorder, Preorder, and Postprder traversals.

void depthFirstTraversalsIterative(BinarySearchTree<NBAPlayer> *nameTree, BinarySearchTree<NBAPlayer> * PTSTree)
{
    // NAME TREE
    cout << "Iter. InOrder   NAME    - ";
    nameTree->iterativeInOrder(displayName);
    cout << endl << endl;
    cout << "Iter. PreOrder  NAME    - ";
    nameTree->iterativePreOrder(displayName);
    cout << endl << endl;
    cout << "Iter. PostOrder NAME    - ";
    nameTree->iterativePostOrder(displayName);
    cout << endl << endl;
    
    // PTS TREE
    cout << "Iter. InOrder   PTS  - ";
    PTSTree->iterativeInOrder(displayPTS);
    cout << endl << endl;
    cout << "Iter. PreOrder  PTS  - ";
    PTSTree->iterativePreOrder(displayPTS);
    cout << endl << endl;
    cout << "Iter. PostOrder PTS  - ";
    PTSTree->iterativePostOrder(displayPTS);
    cout << endl << endl;
}
//-----------------------------------------------------------------------------------------


// CASE B: Function to display tree traversal by level, using queue.

void breadthFirstTraversal(BinarySearchTree<NBAPlayer> *nameTree, BinarySearchTree<NBAPlayer> *PTSTree)
{
    // Display breadth-first traversal
    cout << "BF. NAME    Tree  - ";
    nameTree->breadthFirst(displayName);
    cout << endl << endl;
    cout << "BF. PTS  Tree  - ";
    PTSTree->breadthFirst(displayPTS);
    cout << endl << endl;
}
//-----------------------------------------------------------------------------------------


// CASE S: Function to search for a user-inputted target in the tree and display its data.

void searchNameTree(BinarySearchTree<NBAPlayer>* nameTree)
{
    NBAPlayer *targetIDObject = new NBAPlayer; // Dynamically allocate Toy object to
                                   // store Toy ID(Unique Key) entered by user.
    NBAPlayer *returnedItem = new NBAPlayer;   // Dynamically allocate Toy object to
                                   // display data if user input is found.

    string targetName;  // Store user input (Toy ID(Unique Key)).

    bool foundOrNot = false; // To store result of search.

    cin >> targetName;         // Take in user input.

    targetIDObject->setName(targetName); // Set inputted Toy ID(Unique Key) in Toy object.

    cout << endl << endl;

    // Call the getEntry function, that calls the findNode (search) function.
    foundOrNot = nameTree->getEntryUniqueTree(*targetIDObject, *returnedItem);

    // If search was successful, display found item data.
    if (foundOrNot == true)
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
    delete returnedItem;

}
//-----------------------------------------------------------------------------------------


// CASE Z: Function to search for a user-inputted target in the tree and display its data.

void searchPTSTree(BinarySearchTree<NBAPlayer>* PTSTree)
{
    vector<NBAPlayer> storeAllFound;

    NBAPlayer *targetIDObject = new NBAPlayer; // Dynamically allocate Toy object to
                                   // store Toy ID(Unique Key) entered by user.

    string targetName;  // Store user input (Toy ID(Unique Key)).

    bool foundOrNot = false; // To store result of search.

    cin.ignore();
    cin.clear();

    getline(cin, targetName);         // Take in user input.

    // Handle capital letters.

    targetName[0] = toupper(targetName[0]);
    for (unsigned i = 0 ; i < targetName.size() - 1; i++)
    {
        if ((isspace(targetName[i])))
            targetName[i+1] = toupper(targetName[i+1]);
        else
            targetName[i+1] = tolower(targetName[i+1]);
    }

    targetIDObject->setName(targetName); // Set inputted NBAPlayer ID(Unique Key) in NBAPlayer object.

    cout << endl << endl;

    // Call the getEntry function, that calls the findNode (search) function.
    foundOrNot = PTSTree->getEntrySecondaryTree(*targetIDObject, storeAllFound);

    // If search was successful, display found item data.
    if (foundOrNot == true)
    {
        cout << "Item found: " << targetName << endl << endl;

        for (unsigned int i = 0; i < storeAllFound.size(); i++)
        {
            cout << storeAllFound[i];
        }
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


// CASE D: Function to delete a user-inputted node in the tree.

void deleteANode(BinarySearchTree<NBAPlayer> *nameTree, BinarySearchTree<NBAPlayer> *teamTree, BinarySearchTree<NBAPlayer> *positionTree,BinarySearchTree<NBAPlayer> *FGPTree,BinarySearchTree<NBAPlayer> *FTPTree,BinarySearchTree<NBAPlayer> *TPPTree,BinarySearchTree<NBAPlayer> *PTSTree)
{
    NBAPlayer *targetIDObject = new NBAPlayer; // Dynamically allocate Toy object to
                                   // store Toy ID(Unique Key) entered by user.

    cout << "\n\n\nPlease enter a Toy ID to delete the Toy from all Trees:\n\n\n"; // Prompt user to enter ID.

    string deleteTargetID;           // Store user input (Toy ID(Unique Key)).

    cin >> deleteTargetID;           // Take in user input.

    targetIDObject->setName(deleteTargetID); // Set inputted Toy ID(Unique Key) in Toy object.

    cout << endl << endl;
    
    if (nameTree->deleteUniqueKey(*targetIDObject)) {
        cout << "Successfully deleted\n";
        teamTree->deleteOtherKeys(*targetIDObject);
        positionTree->deleteOtherKeys(*targetIDObject);
        FGPTree->deleteOtherKeys(*targetIDObject);
        FTPTree->deleteOtherKeys(*targetIDObject);
        TPPTree->deleteOtherKeys(*targetIDObject);
        PTSTree->deleteOtherKeys(*targetIDObject);
    }
/*
    if (nameTree->deleteUniqueKey(*targetIDObject))                            // If search was successful, display found item data.
    {
        cout << "Updated inOrder Name Tree:    ";
        nameTree->inOrder(displayName);
        cout << endl << endl;
    }
    else
        cout << "Item failed to be deleted. " << endl << endl;

    if (PTSTree->deleteOtherKeys(*targetIDObject))                          // If search was successful, display found item data.
    {
        cout << "Updated inOrder PTS Tree:  "; nameTree->inOrder(displayName);   cout << endl << endl;
    }
    else
        cout << "Item failed to be deleted. " << endl << endl;

    if (teamTree->deleteOtherKeys(*targetIDObject))                           // If search was successful, display found item data.
    {
        cout << "Updated inOrder AGE Tree:   "; ageTree->inOrder(displayTeam);     cout << endl << endl;
    }
    else
        cout << "Item failed to be deleted. " << endl << endl;

    if (priceTree->deleteOtherKeys(*targetIDObject))                         // If search was successful, display found item data.
    {
        cout << "Updated inOrder PRICE Tree: "; priceTree->inOrder(displayID); cout << endl << endl;
    }
    else
        cout << "Item failed to be deleted. " << endl << endl;
*/
    // Delete dynamically allocated objects.
    delete targetIDObject;
}
//-----------------------------------------------------------------------------------------

// CASE M: Function to find the smallest item in the tree and display its data.

void findTheSmallest(BinarySearchTree<NBAPlayer> *IDTree)
{
    NBAPlayer *returnedItem = new NBAPlayer;          // Dynamically allocate Toy object.
    IDTree->findSmallest(*returnedItem); // Call findSmallest function.
    cout << *returnedItem;                // Display data of smalled Toy.
    delete returnedItem;                  // Delete dynamically allocated Toy object.
}
//-----------------------------------------------------------------------------------------

// CASE X: Function to find the largest item in the tree and display its data.

void findTheLargest(BinarySearchTree<NBAPlayer> *IDTree)
{
    NBAPlayer *returnedItem = new NBAPlayer;         // Dynamically allocate Toy object.
    IDTree->findLargest(*returnedItem); // Call findLargest function.
    cout << *returnedItem;               // Display data of smalled Toy.
    delete returnedItem;                 // Delete dynamically allocated Toy object.
}
//-----------------------------------------------------------------------------------------

// CASE T: Function to print the tree in an indented structure.

void printIndented(BinarySearchTree<NBAPlayer> *nameTree,  BinarySearchTree<NBAPlayer> *PTSTree)
{
    int *keepTrack = new int;  // Dynamically allocate integer for recursion.
    *keepTrack = 0;                               // Set it to 0.
    
    cout << "\t\t\t\t\t\t\t\t<---- NAME TREE: " << endl << endl;
    nameTree->printIndented   (displayName, *keepTrack); cout << endl;    // Call printIndented function - ID.
    cout << "\t\t\t\t\t\t\t\t<---- PTS TREE: " << endl << endl;
    PTSTree->printIndented (displayPTS, *keepTrack); cout << endl;  // Call printIndented function - NAME.
    delete keepTrack;             // Delete dynamically allocated integer.

}
//-----------------------------------------------------------------------------------------

// Display functions to pass to BST traverse functions

void displayName(NBAPlayer & anItem) {
   cout << anItem.getName() << " ";
}
void displayTeam(NBAPlayer & anItem) {
   cout << anItem.getTeam() << " ";
}
void displayPosition(NBAPlayer & anItem) {
    cout << anItem.getPosition() << " ";
}
void displayFGP(NBAPlayer & anItem) {
   cout << anItem.getFGP() << " ";
}

void displayFTP(NBAPlayer & anItem) {
    cout << anItem.getFTP() << " ";
}

void displayTPP(NBAPlayer & anItem) {
    cout << anItem.getTPP() << " ";
}

void displayPTS(NBAPlayer & anItem) {
    cout << anItem.getPTS() << " ";
}


//-----------------------------------------------------------------------------------------

// Validate if user input is valid input size (one character).

bool checkInput(string userInput)
{
    if (userInput.size() > 1)
    {
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
