// By Jason Favero
// Modified by: Deziallia Morris
// Date: 4/1/22
//This program demonstrates a simple linked list

#include <iostream>
#include <string>
using namespace std;

//Define the stuct that will be the nodes in the linked list
struct nodeType {
	string name;  //stores a string
	nodeType* next; //pointer to the next link in the node, which is of type nodeType
};


//function prototypes
void insert(string, nodeType*);
void printList(nodeType*);
void wipeList(nodeType*);
int remove(string, nodeType*);
void printMenu();

int main()
{
	string studentName;
	bool cont = true;
	int returnedValue, menuSelection;

	//create the first node and initialize it to an empty string
	nodeType* headNode;
	headNode = new nodeType;
	headNode->name = " ";
	headNode->next = nullptr;

	while (cont) {
		printMenu();

		cin >> menuSelection;

		switch (menuSelection) {
		case 1:
			cin.ignore();
			cout << "Enter the student name" << endl;
			getline(cin, studentName);
			insert(studentName, headNode);
			break;
		case 2:
			cout << "\n\nThe current list contains \n";
			printList(headNode);
			break;
		case 3:
			cin.ignore();
			cout << "\n\nPlease type a name to be remove from the list\n";
			getline(cin, studentName);
			returnedValue = remove(studentName, headNode);
			switch (returnedValue) {
			case 1:
				cout << "\n\nThe node containing " << studentName << " was removed.";
				break;
			case 2:
				cout << "\n\nThe node containing " << studentName << " has been removed. The list is now empty.";
				break;
			case 3:
				cout << "\n\nRemove failed because the list is empty.";
				break;
			case 4:
				cout << "\n\nRemoved failed: a student named " << studentName << " does not exist. ";
				break;
			default:
				cout << "Unknown return type";
			} //end switch
			break;
		case 4:
			cout << "\n\nDeleting the list\n";
			wipeList(headNode);
			break;
		case 5:
			cont = false;
			break;
		default:
			cout << "Invalid Selection";
		} //end switch
	} //end while

	system("pause");
	return 0;
}

//insert() adds a string onto the end of the list
void insert(string studentName, nodeType* head) {
	nodeType* temp, * traverse;

	if (head->name == " ")
	{
		//if the name field in the head of the list is empty then this is the first name entered
		head->name = studentName;
	}
	else
	{
		temp = new nodeType; //allocate the memory
		temp->name = studentName;
		temp->next = nullptr;

		traverse = head;
		while (traverse->next != nullptr)
			traverse = traverse->next;

		traverse->next = temp;
	}
}


//printList() traverses the list and outputs the string in each node to the output device
void printList(nodeType* head) {
	nodeType* traverse;
	traverse = head;

	if (traverse->name == " ")
		cout << "The list is empty" << endl;
	else
	{
		while (true)
		{
			cout << traverse->name << endl;
			if (traverse->next != nullptr)
				traverse = traverse->next;
			else break;
		}
	}
}

//wipeList() will traverse the linked list and delete all items in the list, freeing the memory
//a double linked list would make this much more efficient, but we have a single linked list

//YOU HAVE TO MODIFY THIS CODE. Now it deletes the pointer headNode when it gets down to just 1 node
//So if you run wipeList() then try to add a name to the list, or print the list, then the program crashes.
//This is because the headNode no longer exists. So, you want to just blank out the name.
void wipeList(nodeType* head) {
	nodeType* traverse1, * traverse2;  //pointers used to traverse the linked list

	while (true)
	{
		if (head->next != nullptr)
		{
			traverse1 = head;  //point to head of the linked list
			traverse2 = traverse1->next; //point to the next item in the list
		}
		else
		{
			//if head->next is null then the head is the only node in the list
			cout << "Deleting the head node " << head->name << endl;
			
			// make the name of the node empty and point head node's next to a nullptr
			head->name = " ";
			head->next = nullptr;
			break;
		}

		while (traverse2->next != nullptr)
		{
			//cycle through to the end of the list
			//keep traverse1 one link behind traverse2
			traverse1 = traverse2;
			traverse2 = traverse2->next;
		}

		//now traverse2 is at the end of the list
		cout << "Deleting " << traverse2->name << endl;
		delete traverse2; //delete the item
		traverse1->next = nullptr; //make this is the end of the list now
	}
}


//YOU HAVE TO ADD THIS CODE. The user must be able to remove any name that exists
//in the list if it's the first node, somewhere in the middle, the last node, etc and 
//return the proper int.
//If the name doesn't exist, return the proper int.
int remove(string name, nodeType* node) {
    
    nodeType* previous, *current, *temp;
    
    previous = nullptr;
    current = node;
    
    if (current->name != " "){
	
    while (current->name != " ") {
    	if (current->name == name) {
    		previous = current;
    		current = current->next;
    		
    		temp = previous;
    		temp->name = " ";
    		
    		previous = temp->next;
    		
    		if (current == nullptr){
    			return 1;
			}
			return 2;
		}
		
		previous = current;
		current = current->next;
		
	}
	
	}
	else if (current->name == " ") {
		return 3;
	}
	else {
		return 4;
	}
	return 4;
    
    
	/*
	This function assumes that the fisrt node in the list being empty " " (a blank space)
	means that the list is empty.
	Returns 1 - The node containing <studentName> has been removed
	Returns 2 - The node containing <studentName> has been removed. The list is now empty.
	Returns 3 - Remove failed because the list is empty.
	Returns 4 - Removed failed: a student named <studentName> does not exist.

	*/

}

void printMenu() {
	//prints the menu for the user to choose what to do

	cout << "\n\nPlease choose one of the following:\n";
	cout << "1. Enter a new student.\n";
	cout << "2. Print the list.\n";
	cout << "3. Remove a student.\n";
	cout << "4. Wipe the list.\n";
	cout << "5. Exit.\n";
}
