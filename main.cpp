#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

const int MIN_NR = 10, MAX_NR = 99, MIN_LS = 5, MAX_LS = 20;

class DoublyLinkedList {
private:
    struct Node {
        string data; //switch to string so we can put a nmae in
        Node* prev;
        Node* next;
        Node(string val, Node* p = nullptr, Node* n = nullptr) {
            data = val; 
            prev = p;
            next = n;
        }
    };

    Node* head;
    Node* tail;

public:
    DoublyLinkedList() { head = nullptr; tail = nullptr; }

    //new function to get the name
    string first_name() {
        if (!head) {
            cout << "List is empty!" << endl;
            return " ";
        }
        else {
            return head->data;
        }
    }


    string last_name() {
        if (!tail) {
            cout << "List is empty!" << endl;
            return " ";
        }
        else {
            return tail->data;
        }
    }

    //length of line
    int length() {
        int i = 0;
        Node* current = head;

        while (current) {
            i++;
            current->next;
        }

        return i;
    }

    //get name by position
    string name_by_pos(int pos) {
        if (pos < 0) {
            cout << "Position can't be negative" << endl;
        }

        Node* current = head;
        for (int i = 0; i < pos && current; i++) {
            current = current->next;
        }
        //return name of node
        return current->data;
    }


    void insert_after(string value, int position) {
        if (position < 0) {
            cout << "Position must be >= 0." << endl;
            return;
        }

        Node* newNode = new Node(value);
        if (!head) {
            head = tail = newNode;
            return;
        }

        Node* temp = head;
        for (int i = 0; i < position && temp; ++i)
            temp = temp->next;

        if (!temp) {
            cout << "Position exceeds list size. Node not inserted.\n";
            delete newNode;
            return;
        }

        newNode->next = temp->next;
        newNode->prev = temp;
        if (temp->next)
            temp->next->prev = newNode;
        else
            tail = newNode;
        temp->next = newNode;
    }

    void delete_val(string value) { //change front int to string
        if (!head) return;

        Node* temp = head;
        
        while (temp && temp->data != value)
            temp = temp->next;

        if (!temp) return; 

        if (temp->prev)
            temp->prev->next = temp->next;
        else
            head = temp->next; 

        if (temp->next)
            temp->next->prev = temp->prev;
        else
            tail = temp->prev; 

        delete temp;
    }

    void delete_pos(int pos) {
        if (!head) {
            cout << "List is empty." << endl;
            return;
        }
    
        if (pos == 1) {
            pop_front();
            return;
        }
    
        Node* temp = head;
    
        for (int i = 1; i < pos; i++){
            if (!temp) {
                cout << "Position doesn't exist." << endl;
                return;
            }
            else
                temp = temp->next;
        }
        if (!temp) {
            cout << "Position doesn't exist." << endl;
            return;
        }
    
        if (!temp->next) {
            pop_back();
            return;
        }
    
        Node* tempPrev = temp->prev;
        tempPrev->next = temp->next;
        temp->next->prev = tempPrev;
        delete temp;
    }

    void push_back(string v) {
        Node* newNode = new Node(v);
        if (!tail)
            head = tail = newNode;
        else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }
    
    void push_front(string v) {
        Node* newNode = new Node(v);
        if (!head)
            head = tail = newNode;
        else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
    }
    
    void pop_front() {

        if (!head) {
            cout << "List is empty." << endl;
            return;
        }

        Node * temp = head;

        if (head->next) {
            head = head->next;
            head->prev = nullptr;
        }
        else
            head = tail = nullptr;
        delete temp;
    }

    void pop_back() {
        if (!tail) {
            cout << "List is empty." << endl;
            return;
        }
        Node * temp = tail;

        if (tail->prev) {
            tail = tail->prev;
            tail->next = nullptr;
        }
        else
            head = tail = nullptr;
        delete temp;
    }

    ~DoublyLinkedList() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }
    void print() {
        Node* current = head;
        if (!current) {
            cout << "List is empty." << endl;
            return;
        }
        while (current) {
            cout << "\t\t" << current->data << endl; //switch to endl
            current = current->next;
        }
        cout << endl;
    }

    void print_reverse() {
        Node* current = tail;
        if (!current) { 
            cout << "List is empty." << endl;
            return;
        }
        while (current) {
            cout << current->data << " ";
            current = current->prev;
        }
        cout << endl;
    }
};

int main() {
    cout << MIN_NR + MIN_LS + MAX_NR + MAX_LS;  // dummy statement to avoid compiler warning
    cout << endl;
    srand(time(0)); //random seed i think it lets it so that not repeated same number based on time of day
  
    //vector of names
    ifstream namefile("names.txt");
    vector<string> names;
    string name;
    while (namefile >> name) {
        names.push_back(name);
    }
    
    //make list of line
    DoublyLinkedList line;

    //start sim
    cout << "Store opens:" << endl;
    for (int i = 0; i < 5; i++) {
        string random_name = names[rand() % names.size()];
        line.push_back(random_name);
        cout << "\t" << random_name << " joins the line" << endl;
    }


    for (int i = 2; i < 20; i++) { //19 sims
        cout << "Time step #" << i << ":" << endl;

        //someone being served 40%
        if (rand() % 100 + 1 <= 40) {
            cout << "\t" << line.first_name() << " is served" << endl;
            line.pop_front();
        }

        //new customer joins line (at end) 60%
        if (rand() % 100 + 1 <= 60) {
            string new_customer = names[rand() % names.size()];
            cout << "\t" << new_customer << " joined the line" << endl;
            line.push_back(new_customer);
        }

        //customer at end leaving 20%
        if (rand() % 100 + 1 <= 20) {
            cout << "\t" << line.last_name() << " (at the rear) left the line" << endl;
            line.pop_back();
        }

        //random person leaving 10%
        if (rand() % 100 + 1 <= 10) {
            int leaving_customer = rand() % line.length();
            cout << "\t" << line.name_by_pos(leaving_customer) << " left the line" << endl;
            line.delete_pos(leaving_customer);
        }        


        //vip joing line 10%
        if (rand() % 100 + 1 <= 10) {
            string new_customer = names[rand() % names.size()];
            cout << "\t" << new_customer << " (VIP) joins the front of the line" << endl;
            line.push_front(new_customer);
        }        

        cout << "\tResulting line: " << endl;
        line.

    }

    
    return 0;
}