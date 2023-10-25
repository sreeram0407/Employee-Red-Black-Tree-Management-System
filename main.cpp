//************************************************************************
// Author: Sreeram Kondapalli
// Description: this is the main program that reads input from keyboard,
// it then execute various red-black tree operations which is given in the input.
//**************************************************************************

#include "RedBlackTree.h"

using namespace std;

//This function used to get all info. of an Employee
void getEmployeeInfo(string oneLine, int& id, string& firstName, string& lastName, double& salary);

int main()
{

    int id;
    string firstName, lastName;
    double salary;
    string command, oneLine, token;
    string delimiter = ",";

    int pos = 0;

    //Create a RedBlackTree object here, use it throughout the program
    RedBlackTree* redBlackTree = new RedBlackTree();

    do
    {
        getline(cin, oneLine);
        pos = oneLine.find(delimiter);
        token = oneLine.substr(0, pos);
        command = token;
        oneLine.erase(0, pos + delimiter.length());

        if(command.compare("quit")==0)
        {
            cout << "\nCommand: quit" << endl;
            //call the relevant function on the red black tree
            //----
            redBlackTree->~RedBlackTree();
            break;
        }
        else if(command.compare("tree_preorder")==0)
        {
            cout << "\nCommand: tree_preorder" << endl;

            //call the relevant function on the red black tree
            redBlackTree->treePreorder();
        }
        else if(command.compare("tree_inorder")==0)
        {
            cout << "\nCommand: tree_inorder" << endl;

            //call the relevant function on the red black tree
            redBlackTree->treeInorder();
        }
        else if(command.compare("tree_postorder")==0)
        {
            cout << "\nCommand: tree_postorder" << endl;

            //call the relevant function on the red black tree
            redBlackTree->treePostorder();
        }
        else if(command.compare("tree_minimum")==0)
        {
            cout << "\nCommand: tree_minimum" << endl;

            //call the relevant function on the red black tree
            redBlackTree->treeMinimum();
        }
        else if(command.compare("tree_maximum")==0)
        {
            cout << "\nCommand: tree_maximum" << endl;

            //call the relevant function on the red black tree
            redBlackTree->treeMaximum();
        }
        else if(command.compare("tree_predecessor")==0)
        {
            //call the relevant function to get the Employee key first
            string delimiter = ",";
            int pos = oneLine.find(delimiter);
            string token = oneLine.substr(0, pos);
            id = stoi(token);
            oneLine.erase(0, pos + 1);

            pos = oneLine.find(delimiter);
            token = oneLine.substr(0, pos);
            firstName = token;
            oneLine.erase(0, pos + 1);

            pos = oneLine.find(delimiter);
            token = oneLine.substr(0, pos);
            lastName = token;
            oneLine.erase(0, pos + 1);

            cout << "\nCommand: tree_predecessor" << endl;

            //call the relevant function on the red black tree
            redBlackTree->treePredecessor(id,firstName,lastName);
        }
        else if(command.compare("tree_successor")==0)
        {
            //call the relevant function to get the Employee key first
            string delimiter = ",";
            int pos = oneLine.find(delimiter);
            string token = oneLine.substr(0, pos);
            id = stoi(token);
            oneLine.erase(0, pos + 1);

            pos = oneLine.find(delimiter);
            token = oneLine.substr(0, pos);
            firstName = token;
            oneLine.erase(0, pos + 1);

            pos = oneLine.find(delimiter);
            token = oneLine.substr(0, pos);
            lastName = token;
            oneLine.erase(0, pos + 1);

            cout << "\nCommand: tree_successor" << endl;

            //call the relevant function on the red black tree
            redBlackTree->treeSucessor(id,firstName,lastName);
        }
        else if(command.compare("tree_search")==0)
        {
            //call the relevant function to get the Employee key first
            string delimiter = ",";
            int pos = oneLine.find(delimiter);
            string token = oneLine.substr(0, pos);
            id = stoi(token);
            oneLine.erase(0, pos + 1);

            pos = oneLine.find(delimiter);
            token = oneLine.substr(0, pos);
            firstName = token;
            oneLine.erase(0, pos + 1);

            pos = oneLine.find(delimiter);
            token = oneLine.substr(0, pos);
            lastName = token;
            oneLine.erase(0, pos + 1);

            cout << "\nCommand: tree_search" << endl;

            //call the relevant function on the red black tree
            Node *search = redBlackTree->treeSearch(id,firstName,lastName);

            if(search != nullptr)
            {
                cout << left;
                cout << setw(8)  << id << setw(12) << firstName << setw(12) << lastName << " is found." << endl;
            }
            else
            {
                cout << left;
                cout << setw(8)  << id << setw(12) << firstName << setw(12) << lastName << " is NOT found." << endl;
            }
        }
        else if(command.compare("tree_insert")==0)
        {
            //call the getEmployeeInfo function to get the Employee info
            //----
            getEmployeeInfo(oneLine, id,firstName, lastName, salary);


            cout << "\nCommand: tree_insert" << endl;
            cout << left;
            cout << setw(8)  << id
                 << setw(12) << firstName
                 << setw(12) << lastName
                 << setw(10) << fixed << setprecision(2) << salary << endl;

            //call the relevant function to insert the Employee inside the RBT
            redBlackTree->treeInsert(id, firstName, lastName, salary);
        }
    } while(true);  //continue until 'quit'
    return 0;
}

//************************************************************************************************
//This function from one line, extract tokens and get all info. of an Employee
void getEmployeeInfo(string oneLine, int& id, string& firstName, string& lastName, double& salary) {
    //Design your own code here
    //----
    string delimiter = ",";
    int pos = oneLine.find(delimiter);
    string token = oneLine.substr(0, pos);
    id = stoi(token);
    oneLine.erase(0, pos + 1);

    pos = oneLine.find(delimiter);
    token = oneLine.substr(0, pos);
    firstName = token;
    oneLine.erase(0, pos + 1);

    pos = oneLine.find(delimiter);
    token = oneLine.substr(0, pos);
    lastName = token;
    oneLine.erase(0, pos + 1);

    pos = oneLine.find(delimiter);
    token = oneLine.substr(0, pos);
    salary = stod(token);
    oneLine.erase(0, pos + 1);
}