#include "HEADER.h"

using namespace std;


// FUNCTION TO COUNT THE LINES IN THE FILE ON BASIS OF "\n"...
int count_book_lines(string filename){

    int row = 0;
    char a;
    
    fstream line(filename , ios::in);		// OPEN FILE IN READING MODE.
    
    if(!line){
        cerr<<"\n\t\t FILE NOT FOUND . CHECK THE FILE NAME.\n";
        return 0;
    }
    while(line.get(a)){
        if(a=='\n'){
            row++ ;
        }
    }
    
    line.clear();
    line.seekg(0 , ios::beg);		// MOVE THE CURSOR TO THE BEGINING OF THE FILE.
    
    line.close();		// CLOSING THE FILE TO PREVENT DATA CORRUPTION.

return row;
}


//////////////////////////////////////////////////////////////////////////


//** CLASS BOOKS [LIBRARY MANAGEMENT SYSTEM] */
class Books{

    public:
        
        int ID;
        string Title;
        string Author;
        string Genre;
        int Year;
        int Available_Copies;
        string status;

    public:

        // USER DEFINED DEFAULT CONSTRUCTOR.
        Books(int ID=0 , string Title="" , string Author="" , string Genre="" , int Year=0 , int Available_Copies=0 , string status=""){
            this->ID = ID;
            this->Title = Title;
            this->Author = Author;
            this->Genre = Genre;
            this-> Year = Year;
            this-> Available_Copies = Available_Copies;
            this->status = status;
        }

        // PRINT BOOKS.
        void print_books(){
            cout<<"\t -----------------------------\n";
            cout<<"\t |  BOOK_ID      =  "<<ID<<"\n";
            cout<<"\t |  TITLE        =  "<<Title<<"\n";
            cout<<"\t |  AUTHOR       =  "<<Author<<"\n";
            cout<<"\t |  GENRE        =  "<<Genre<<"\n";
            cout<<"\t |  YEAR         =  "<<Year<<"\n";
            cout<<"\t |  AVAILABLE COPIES =  "<<Available_Copies<<"\n";
            cout<<"\t |  STATUS       =  "<<status<<"\n";
            cout<<"\t -----------------------------\n";
        }

        // DESTRUCTOR.
        ~Books(){
            // just roaming around...
        }

};


//** MAKING A NODE CLASS */
class Node{
    public:
        Books data;
        Node* next;

        // CONSTRUCTOR.
        Node(){
            this->next = nullptr;
        }

        // DESTRUCTOR.
        ~Node(){
        }
};


//** CLASS THAT WILL CONTAIN A LIST OF BOOK. */
class Book_List : public Books{
    private:

        Node* head;
        Node* tail;

        int row;            // stores number of lines in file

    public:

        // CONSTRUCTOR.
        Book_List(){
            this->head = NULL;
            this->tail = NULL;
        }

        // FUNCTION TO READ DATA OF BOOKS.
        void read_books(){

            this->row = count_book_lines("Books.txt");
            
            if(this->row == 0){
                cerr<<"\n\t\t NO BOOKS FOUND IN THE FILE.\n";
                return;
            }
            else{

                fstream file("Books.txt", ios::in);
                if(!file){
                    cerr<<"\n\t\t FILE NOT FOUND.\n";
                    return;
                }
                
                while(file>>ID>>Title>>Author>>Genre>>Year>>Available_Copies>>status){
                
                    Books temp_book(ID, Title, Author, Genre, Year, Available_Copies, status);
                    
                    Node* temp_node = new Node();
                    temp_node->data = temp_book;
                    temp_node->next = nullptr;
                    
                    if(this->head == nullptr){
                        this->head = temp_node;
                        this->tail = temp_node;
                    }
                    else{
                        this->tail->next = temp_node;
                        this->tail = temp_node;
                    }
                }
                file.close();
            }
        }


        // ADD NEW BOOK...
        void add_book(){
            int ID, Available_Copies;
            string Title, Author, Genre, status;
            int Year;
            
            cout<<"\n\t\t ADD NEW BOOK.\n";
            cout<<"\t -----------------------------\n";
            cout<<"\t |  BOOK_ID      =  "; cin>>ID;
            while(ID<0){
                cout<<"\n\t\t INVALID BOOK_ID. PLEASE ENTER A POSITIVE INTEGER.\n";
                cout<<"\t |  BOOK_ID      =  "; cin>>ID;
            }
            cin.ignore();
            cout<<"\t |  TITLE        =  "; getline(cin, Title);
            cout<<"\t |  AUTHOR       =  "; getline(cin, Author);
            cout<<"\t |  GENRE        =  "; getline(cin, Genre);
            cout<<"\t |  STATUS       =  "; getline(cin, status);
            cout<<"\t |  YEAR         =  "; cin>>Year;
            cout<<"\t |  AVAILABLE COPIES =  "; cin>>Available_Copies;
            cout<<"\t -----------------------------\n";

            // ADDING NEW BOOK TO FILE...
            fstream file("Books.txt", ios::out | ios::app);    // OPEN IN APPEND MODE.    
            if(!file){
                cerr<<"\n\t\t ERROR OPENING THE FILE.\n";
                return;
            }
            file<<ID<<" "<<Title<<" "<<Author<<" "<<Genre<<" "<<Year<<" "<<Available_Copies<<" "<<status<<"\n";
            file.close();
        }


        // EDIT BOOK DETAILS [BASED ON ID]
        void edit_book(){

            int Search_ID;
            cout<<"\n\t\t EDIT BOOK.\n";
            cout<<"\t -----------------------------\n";
            cout<<"\t |  BOOK_ID      =  "; cin>>Search_ID;
            while(Search_ID<0){
                cout<<"\n\t\t INVALID BOOK_ID. PLEASE ENTER A POSITIVE INTEGER.\n";
                cout<<"\t |  BOOK_ID      =  "; cin>>Search_ID;
            }

            string Title, Author, Genre, status;
            int Year, Available_Copies;

            bool yes=false;
            
            Node* temp = this->head;

            while(temp != nullptr){
                if(temp->data.ID == Search_ID){
                    yes = true;
                    cout<<"\n\t\t EDIT BOOK.\n";
                    cout<<"\t -----------------------------\n";
                    cout<<"\t |  BOOK_ID      =  "<<temp->data.ID<<"\n";
                    cout<<"\t |  TITLE        =  "; cin.ignore(); getline(cin, Title);
                    cout<<"\t |  AUTHOR       =  "; getline(cin, Author);
                    cout<<"\t |  GENRE        =  "; getline(cin, Genre);
                    cout<<"\t |  STATUS       =  "; getline(cin, status);
                    cout<<"\t |  YEAR         =  "; cin>>Year;
                    cout<<"\t |  AVAILABLE COPIES =  "; cin>>Available_Copies;
                    cout<<"\t -----------------------------\n";

                    // Update the book details in the list
                    temp->data.Title = Title;
                    temp->data.Author = Author;
                    temp->data.Genre = Genre;
                    temp->data.status = status;
                    temp->data.Year = Year;
                    temp->data.Available_Copies = Available_Copies;
                    break;
                }
                temp = temp->next;
            }

            if(yes){            // UPDATING THE BOOK IN FILE...
                
                fstream file("Books.txt", ios::out | ios::trunc);
                if(!file){
                    cerr<<"\n\t\t ERROR OPENING THE FILE.\n";
                    return;
                }
                temp = this->head;
                while(temp!= NULL){
                    file<<temp->data.ID<<" "<<temp->data.Title<<" "<<temp->data.Author<<" "<<temp->data.Genre<<" "<<temp->data.Year<<" "<<temp->data.Available_Copies<<" "<<temp->data.status<< "\n";
                    temp = temp->next;
                }
                file.close();
                cout<<"\n\t\t BOOK UPDATED SUCCESSFULLY.\n";
            }
            else{
                cout<<"\n\t\t BOOK NOT FOUND.\n";
            }
        }

        // DELETE BOOK FROM START.
        void delete_book_start(){
            if(this->head == nullptr){
                cout<<"\n\t NO BOOKS TO DELETE.\n";
                return;
            }
            Node* temp = this->head;
            this->head = this->head->next;
            delete temp;

            if (this->head == nullptr) {
                this->tail = nullptr;
            }
        }

        // DELETE BOOK FROM END.
        void delete_book_end(){
            if(this->head == nullptr){
                cout<<"\n\t NO BOOKS TO DELETE.\n";
                return;
            }
            
            if (this->head->next == nullptr){
                delete_book_start();
                return;
            }

            Node* temp = this->head;
            while(temp->next->next != nullptr){
                temp = temp->next;
            }
            
            delete temp->next;
            temp->next = nullptr;
            this->tail = temp;
        }

        // DELETE THE BOOK BY ID
        void delete_book() {
            if (this->head == nullptr) {
                cout << "\n\t NO BOOKS TO DELETE.\n";
                return;
            }

            Node* temp = this->head;
            Node* prev = nullptr;

            int Search_ID;
            bool found = false;

            cout << "\n ENTER THE BOOK_ID TO DELETE: ";
            cin >> Search_ID;
            
            while(Search_ID < 0){
                cout << "\n\t\t INVALID BOOK_ID. ENTER A POSITIVE NUMBER: ";
                cin >> Search_ID;
            }

            if (Search_ID == head->data.ID && head->data.status == "AVAILABLE") {
                delete_book_start();
                return;
            }
            
            if (Search_ID == tail->data.ID && tail->data.status == "AVAILABLE") {
                delete_book_end();
                return;
            }

            while (temp != nullptr) {
                if (temp->data.ID == Search_ID && temp->data.status == "AVAILABLE") {
                    found = true;
                    break;
                }
                prev = temp;
                temp = temp->next;
            }

            if (found && prev != nullptr && temp != nullptr) {
                prev->next = temp->next;
                delete temp;
                cout << "\n\t\t BOOK DELETED SUCCESSFULLY.\n";
            } else {
                cout << "\n\t\t BOOK NOT FOUND OR IS NOT AVAILABLE FOR DELETION.\n";
            }

            fstream file("Books.txt", ios::out | ios::trunc);
            if (!file) {
                cerr << "\n\t\t ERROR OPENING THE FILE.\n";
                return;
            }

            temp = this->head;
            while (temp != nullptr) {
                file << temp->data.ID << " " << temp->data.Title << " " << temp->data.Author << " "
                    << temp->data.Genre << " " << temp->data.Year << " " << temp->data.Available_Copies << " "
                    << temp->data.status << "\n";
                temp = temp->next;
            }

            file.close();
            file.clear();
        }



        // FUNCTION TO PRINT THE BOOK LIST.
        void print_book_list(){

            if(this->head == nullptr){
                cerr<<"\n\t\t NO BOOKS FOUND.\n";
                return;
            }
            else{
                Node* temp = this->head;
                while(temp != nullptr){
                    temp->data.print_books();
                    temp = temp->next;
                }
            }
        }


        // SEARCH BOOKS IN THE LIST.
        void search_book(){
            if(this->head == nullptr){
                cerr<<"\n\t\t NO BOOKS FOUND.\n";
                return;
            }

            cout<<"\n ON WHICH BASIS DO YOU WANT TO PERFORM THE SEARCH?\n";
            cout<<"\t [1]. BOOK_ID\n";
            cout<<"\t [2]. TITLE\n";
            cout<<"\t [3]. AUTHOR\n";
            cout<<"\t [4]. GENRE\n";
            cout<<"\t [5]. STATUS [AVAILABLE/BORROWED]\n";
            
            int choice;
            cout<<"\n ENTER YOUR CHOICE: ";
            cin>>choice;
            
            while(choice < 1 || choice > 5){
                cout<<"\n\t\t INVALID CHOICE.\n";
                cout<<"\n ENTER YOUR CHOICE: ";
                cin>>choice;
            }

            Node* temp = this->head;
            bool found = false;

            switch(choice){
                case 1:
                {
                    int ID;
                    cout<<"\n ENTER THE BOOK_ID TO SEARCH: ";
                    cin>>ID;
                    while(temp != nullptr){
                        if(temp->data.ID == ID){
                            found = true;
                            temp->data.print_books();
                            break;
                        }
                        temp = temp->next;
                    }
                
                break;
                }
                case 2:
                {
                    string Title;
                    cout<<"\n ENTER THE TITLE TO SEARCH: ";
                    cin.ignore();
                    getline(cin, Title);
                    while(temp != nullptr){
                        if(temp->data.Title == Title){
                            found = true;
                            temp->data.print_books();
                            break;
                        }
                        temp = temp->next;
                    }
                
                break;
                }
                case 3:
                {
                    string Author;
                    cout<<"\n ENTER THE AUTHOR TO SEARCH: ";
                    cin.ignore();
                    getline(cin, Author);
                    while(temp != nullptr){
                        if(temp->data.Author == Author){
                            found = true;
                            temp->data.print_books();
                            break;
                        }
                        temp = temp->next;
                    }
                
                break;
                }
                case 4:
                {
                    string Genre;
                    cout<<"\n ENTER THE GENRE TO SEARCH: ";
                    cin.ignore();
                    getline(cin, Genre);
                    while(temp != nullptr){
                        if(temp->data.Genre == Genre){
                            found = true;
                            temp->data.print_books();
                            break;
                        }
                        temp = temp->next;
                    }
                
                break;
                }
                case 5:
                {
                    string status;
                    cout<<"\n ENTER THE STATUS TO SEARCH (AVAILABLE/BORROWED): ";
                    cin.ignore();
                    getline(cin, status);
                    while(temp != nullptr){
                        if(temp->data.status == status){
                            found = true;
                            temp->data.print_books();
                        }
                        temp = temp->next;
                    }
                
                break;
                }
            }

            if(!found){
                cerr<<"\n\t\t BOOK NOT FOUND.\n";
            }

        }


        // [-1] TO BOOK COPIES IF IT IS BORROWED.
        void decrement_book(int ID){
            if(this->head == nullptr){
                cerr<<"\n\t\t NO BOOKS FOUND.\n";
                return;
            }
            Node* temp = this->head;
            bool found = false;
            while(temp!= nullptr){
                if(temp->data.ID == ID && temp->data.status == "BORROWED"){
                    found = true;
                    break;
                }
                temp = temp->next;
            }
            if(found){
                if(temp->data.Available_Copies > 0){
                    temp->data.Available_Copies--;
                    cout<<"\n\t\t BOOK BORROWED SUCCESSFULLY.\n";
                }
                else{
                    cerr<<"\n\t\t BOOK OUT OF STOCK.\n";
                }

                // RE-WRITE THE UPDATED DATA TO FILE...
                fstream file("Books.txt", ios::out | ios::trunc);
                if(!file){
                    cerr<<"\n\t\t ERROR OPENING THE FILE.\n";
                    return;
                }
                else{
                    Node* temp = this->head;
                    while(temp!= nullptr){
                        file<<temp->data.ID<<" "<<temp->data.Title<<" "<<temp->data.Author<<" "<<temp->data.Genre<<" "<<temp->data.Year<<" "<<temp->data.Available_Copies<<" "<<temp->data.status<<"\n";
                        temp = temp->next;
                    }
                    file.close();
                    cout<<"\n\t\t FILE UPDATED SUCCESSFULLY.\n";
                }

            }
            else{
                cerr<<"\n\t\t BOOK NOT FOUND OR NOT BORROWED.\n";
            }

        }


        // [+1] IF A BOOK IS RETURNED.
        void increment_book(int ID){
            if(this->head == nullptr){
                cerr<<"\n\t\t NO BOOKS FOUND.\n";
                return;
            }
            Node* temp = this->head;
            bool found = false;
            while(temp!= nullptr){
                if(temp->data.ID == ID && temp->data.status == "BORROWED"){
                    found = true;
                    break;
                }
                temp = temp->next;
            }
            if(found){
                temp->data.Available_Copies++;
                cout<<"\n\t\t BOOK RETURNED SUCCESSFULLY.\n";
                
                // RE-WRITE THE UPDATED DATA TO FILE...
                fstream file("Books.txt", ios::out | ios::trunc);
                if(!file){
                    cerr<<"\n\t\t ERROR OPENING THE FILE.\n";
                    return;
                }
                else{
                    Node* temp = this->head;
                    while(temp!= nullptr){
                        file<<temp->data.ID<<" "<<temp->data.Title<<" "<<temp->data.Author<<" "<<temp->data.Genre<<" "<<temp->data.Year<<" "<<temp->data.Available_Copies<<" "<<temp->data.status<<"\n";
                        temp = temp->next;
                    }
                    file.close();
                    cout<<"\n\t\t FILE UPDATED SUCCESSFULLY.\n";
                }
            }
            else{
                cerr<<"\n\t\t BOOK NOT FOUND OR NOT BORROWED.\n";
            }
        }


        // SEE THE BORROWED BOOKS.
        void see_borrowed_books(){
            if(this->head == nullptr){
                cerr<<"\n\t\t NO BOOKS FOUND.\n";
                return;
            }
            cout<<"\n\t\t BORROWED BOOKS LIST:\n";
            bool found=false;
            Node* temp = this->head;
            while(temp!= nullptr){
                if(temp->data.status == "BORROWED"){
                    found = true;
                    temp->data.print_books();
                }
                temp = temp->next;
            }
            if(!found){
                cerr<<"\n\t\t NO BORROWED BOOKS FOUND.\n";
            }

        }
        
        
        
        // LIST OF AVAILABLE BOOKS.
        void see_available_books(){
            if(this->head == nullptr){
                cerr<<"\n\t\t NO BOOKS FOUND.\n";
                return;
            }
            cout<<"\n\t\t AVAILABLE BOOKS LIST:\n";
            bool found=false;
            Node* temp = this->head;
            while(temp!= nullptr){
                if(temp->data.status == "AVAILABLE"){
                    found = true;
                    temp->data.print_books();
                }
                temp = temp->next;
            }
            if(!found){
                cerr<<"\n\t\t NO AVAILABLE BOOKS FOUND.\n";
            }

        }

        
        // DESTRUCTOR.
        ~Book_List(){
            del_Book_List();
        }

        // DELETING FUNCTION.
        void del_Book_List(){
            Node* temp = this->head;
            while(temp!= nullptr){
                Node* next = temp->next;
                delete temp;
                temp = next;
            }
            this->head = nullptr;
        }


};


//////////////////////////////////////////////////////////////////////////


//** MAKING THE PARTON CLASS. */
class Patron{

    public:

        int ID;
        string name;
        string email;
        string address;
        string card_status;
        int books_borrowed;

    public:

        // USER DEFINED DEFAULT CONSTRUCTOR.
        Patron(int ID=0, string name="", string email="" , string address="" , string card_status="" , int books_borrowed=0){
            this->ID = ID;
            this->name = name;
            this->email = email;
            this->address = address;
            this->card_status = card_status;
            this->books_borrowed = books_borrowed;
        }

        // PRINT PARTON'S DATA.
        void Help_Print(){
            cout<<"\t -----------------------------\n";
            cout<<"\t |  PARTON_ID      =  "<<ID<<endl;
            cout<<"\t |  NAME           =  "<<name<<endl;
            cout<<"\t |  EMAIL          =  "<<email<<endl;
            cout<<"\t |  ADDRESS        =  "<<address<<endl;
            cout<<"\t |  CARD_STATUS    =  "<<card_status<<endl;
            cout<<"\t |  BOOKS_BORROWED =  "<<books_borrowed<<endl;
            cout<<"\t -----------------------------\n";
        }

        // DESTRUCTOR
        ~Patron(){
            // Nothing to do here.
        }

};



// PARTON_NODES_CLASS
class Patron_Node{
    public:

        Patron data;
        Patron_Node* next;

        // CONSTRUCTOR.
        Patron_Node(Patron& P){
            this->data = P;
            this->next = nullptr;
        }

        // DESTRUCTOR.
        ~Patron_Node(){
        }
};



// PATRON_LIST [A TYPO OF LINKED LIST]
class Patron_List : public Patron{

    private:

        Patron_Node* head;
        Patron_Node* tail;
    
    public:

        // CONSTRUCTOR.
        Patron_List(){
            this->head = NULL;
            this->tail = NULL;
        }


        // READ PATRON'S DATA FROM FILE.
        void read_patrons_data(){

            ifstream file("Patron.txt");
            if(!file){
                cerr << "\n\t\t ERROR OPENING THE FILE.\n";
                return;
            }

            Patron_Node* last = nullptr;

            while(true){
                
                int ID;
                string name, email, address, card_status;
                int books_borrowed;
                
                file>>ID>>name>>email>>address>>card_status>>books_borrowed;
                
                if(file.eof()){
                    break;
                }

                Patron P(ID, name, email, address, card_status, books_borrowed);
                Patron_Node* newNode = new Patron_Node(P);
                
                if(last == nullptr){
                    this->head = newNode;
                }
                else{
                    last->next = newNode;
                }
                last = newNode;
                this->tail = newNode;
            }

        }


        // REGISTER NEW PARTON.
        void register_parton(){
            cout<<"\n ENTER THE NEW PARTON'S DETAILS:\n";
            cout<<"\t -----------------------------\n";
            cout<<"\t |  PARTON_ID      =  "; cin>>ID;
            while(ID<0){
                cout<<"\n\t\t INVALID BOOK_ID. PLEASE ENTER A POSITIVE INTEGER.\n";
                cout<<"\t |  PARTON_ID      =  "; cin>>ID;
            }
            cin.ignore();
            cout<<"\t |  NAME           =  "; getline(cin, name);
            cout<<"\t |  EMAIL          =  "; getline(cin, email);
            cout<<"\t |  ADDRESS        =  "; getline(cin, address);
            cout<<"\t |  CARD_STATUS    =  "; getline(cin, card_status);
            cout<<"\t |  BOOKS_BORROWED =  "; cin>>books_borrowed;
            while(books_borrowed<0){
                cout<<"\n\t\t INVALID BOOKS_BORROWED. PLEASE ENTER A POSITIVE INTEGER.\n";
                cout<<"\t |  BOOKS_BORROWED =  "; cin>>books_borrowed;
            }
            cout<<"\t -----------------------------\n";
            
            // WRITE DATA IN FILE.
            ofstream file("Patron.txt", ios::app);
            file<<ID<<" "<<name<<" "<<email<<" "<<address<<" "<<card_status<<" "<<books_borrowed<<endl;
            file.close();

            cout<<"\n\t\t PARTON REGISTERED SUCCESSFULLY.\n";
        }


        // SEARCH FOR PARTON.  
        void search_parton() {  
            this->read_patrons_data();  

            cout<<"\nON WHAT BASIS DO YOU WANT TO PERFORM SEARCH ..?\n";  
            cout<<"\t [1]. PARTON_ID \n";  
            cout<<"\t [2]. NAME \n";  
            cout<<"\t [3]. EMAIL \n";  
            int choice;  
            cout<<"\n ENTER YOUR CHOICE : ";  
            cin>>choice;  
            while (choice<1 || choice>3) {  
                cout<<"\n\t\t INVALID CHOICE.\n";  
                cout<<"\n ENTER YOUR CHOICE : ";  
                cin>>choice;  
            }  

            switch (choice) {  
            case 1: {  
                int ID;  
                cout<<"\n ENTER THE PARTON_ID TO SEARCH : ";  
                cin>>ID;  
                while (ID<0) {  
                    cout<<"\nINVALID PARTON_ID. PLEASE ENTER A POSITIVE INTEGER.\n";  
                    cin>>ID;  
                }  

                Patron_Node* temp = this->head;  
                bool found = false;  

                while (temp!=nullptr) {  
                    if (temp->data.ID == ID) {  
                        found = true;
                        //call the print
                        temp->data.Help_Print(); 
                        break;  
                    }  
                    temp = temp->next;  
                }  
                if (!found) {  
                    cerr<<"\n\t\t PARTON NOT FOUND.\n";  
                }  
                else {  
                    cout<<"\n PARTON FOUND.\n";  
                }  
                break;  
            }  
            case 2: {  
                string name;  
                cout<<"\n ENTER THE NAME TO SEARCH : ";  
                cin.ignore();  
                getline(cin, name);  
                Patron_Node* temp = this->head;  
                bool found = false;  

                while (temp!=nullptr) {  
                    if (temp->data.name == name) {  
                        found = true;
                        //call the print
                        temp->data.Help_Print();
                        break;  
                    }  
                    temp = temp->next;  
                }  
                if (!found) {  
                    cerr<<"\n\t\t PARTON NOT FOUND.\n";  
                }  
                else {  
                    cout<<"\n PARTON FOUND.\n";  
                }  
                break;  
            }  
            case 3: {  
                string email;  
                cout<<"\n ENTER THE EMAIL TO SEARCH : ";  
                cin.ignore();  
                getline(cin, email);  
                Patron_Node* temp = this->head;  
                bool found = false;  

                while (temp!=nullptr) {  
                    if (temp->data.email == email) {  
                        found = true;
                        //call the print
                        temp->data.Help_Print();
                        break;  
                    }  
                    temp = temp->next;  
                }  
                if (!found) {  
                    cerr<<"\n\t\t PARTON NOT FOUND.\n";  
                }  
                else {  
                    cout<<"\n PARTON FOUND.\n";  
                }  
                break;  
            }  
            default: {  
                cerr<<"\n\t\t INVALID CHOICE.\n";  
                break;  
            }  
            }  
        }


        // EDIT PARTON INFORMATION [BASED ON ID].  
        void edit_parton_info(){

            cout<<"\nENTER THE PATRON_ID TO EDIT : ";  
            int ID;  
            cin>>ID;  
            while(ID < 0){  
                cout<<"\nINVALID PATRON_ID. PLEASE ENTER A POSITIVE INTEGER.\n";  
                cin>>ID;  
            }  

            Patron_Node* temp = this->head;  
            Patron_Node* target = nullptr;  

            while(temp != nullptr){ 
                if(temp->data.ID == ID){  
                    target = temp;  
                    break;  
                }  
                temp = temp->next;  
            }  
            if(target == nullptr){
                cerr<<"\n\t\t PATRON NOT FOUND.\n";  
                return;  
            }  

            cout<<"\nENTER THE NEW DETAILS FOR PATRON_ID " << ID << ":\n";  
            cout<<"\t-----------------------------\n";  
            cout<<"\t|  NAME           =  ";  
            cin.ignore();  
            getline(cin, target->data.name);  
            cout<<"\t|  EMAIL          =  ";  
            getline(cin, target->data.email);  
            cout<<"\t|  ADDRESS        =  ";  
            getline(cin, target->data.address);  
            cout <<"\t|  CARD_STATUS    =  ";  
            getline(cin, target->data.card_status);  
            cout<<"\t|  BOOKS_BORROWED =  ";  
            cin>>target->data.books_borrowed;  
            while(target->data.books_borrowed < 0) {  
                cout<<"\n\t\t INVALID BOOKS_BORROWED. PLEASE ENTER A POSITIVE INTEGER.\n";  
                cout<<"\t|  BOOKS_BORROWED =  ";  
                cin>>target->data.books_borrowed;  
            }  
            cout<<"\t-----------------------------\n";  

            ofstream file("Patron.txt", ios::out | ios::trunc);  
            if (!file) {  
                cerr << "\n\t\t ERROR OPENING THE FILE.\n";  
                return;  
            }  

            Patron_Node* current = this->head;  
            while (current != nullptr) {  
                file << current->data.ID << ' ' << current->data.name << ' ' << current->data.email << ' '  
                    << current->data.address << ' ' << current->data.card_status << ' '  
                    << current->data.books_borrowed << endl;  
                current = current->next;  
            }  
            file.close();  

            cout << "\n\t\t PATRON INFORMATION UPDATED SUCCESSFULLY.\n";  
        }


        // DELETE PARTON [BASED ON ID].  
        void delete_parton(){

            cout<<"\nENTER THE PARTON_ID TO DELETE : ";  
            int ID;  
            cin>>ID;  
            while(ID < 0) {  
                cout << "\nINVALID PARTON_ID. PLEASE ENTER A POSITIVE INTEGER.\n";  
                cin >> ID;  
            }  
            Patron_Node* temp = this->head;  
            Patron_Node* prev = nullptr;  
            bool found = false;  

            while (temp != nullptr) {  
                if (temp->data.ID == ID) {  
                    found = true;  
                    break;  
                }  
                prev = temp;  
                temp = temp->next;  
            }  
            if (!found) {  
                cerr << "\n\t\t PARTON NOT FOUND.\n";  
                return;  
            }  
            else {  
                if(prev == nullptr){  
                    this->head = temp->next;  
                }  
                else{  
                    prev->next = temp->next;  
                }  
                delete temp;  
            }  

            cout<<"\n\t\t PARTON DELETED SUCCESSFULLY.\n";  

            ofstream file("Patron.txt", ios::out | ios::trunc);  
            if (!file) {  
                cerr << "\n\t\t ERROR OPENING THE FILE.\n";  
                return;  
            }  
            Patron_Node* current = this->head;  
            // WRITE UPDATED DATA IN FILE.  
            while (current != nullptr) {  
                file<<current->data.ID<<" "<<current->data.name<<" "<<current->data.email<<" "<<current->data.address<<" "<<current->data.card_status << " " << current->data.books_borrowed << endl;  
                current = current->next;  
            }  
            file.close();  

        }


        // PRINT FUNCTION.
        void print_partons_data(){

            Patron_Node* temp = this->head;
            while(temp != NULL){
                temp->data.Help_Print();
                temp = temp->next;
            }
            cout<<"\n";
        }


        // DELETE MEMORY FUNCTION.
        void del_patron_list(){

            Patron_Node *temp = this->head;
            while(temp!= NULL){
                Patron_Node* next_node = temp->next;
                delete temp;
                temp = next_node;
            }
            this->head = NULL;
            this->tail = NULL;
        }

        // DESTRUCTOR.
        ~Patron_List(){
            del_patron_list();
        }

};


//////////////////////////////////////////////////////////////////////////


//** CLASS TO ALLOW BORROWING, RETURNING, & TRACKING OVERDUE BOOK. */
class Borrow_Record{

    public:

        int borrow_ID;
        int book_ID;
        int parton_ID;
        int borrow_date;
        int return_date;
        int overdue_days;

    public:
        
        // CONSTRUCTOR.
        Borrow_Record(int A=0 , int B=0 , int C=0 , int D=0 , int E=0 , int F=0 ){
            this->borrow_ID = A;
            this->book_ID = B;
            this->parton_ID = C;
            this->borrow_date = D;
            this->return_date = E;
            this->overdue_days = F;
        }

        // PRINT FUNCTION.
        void Print() const{
            cout<<"\n\t -------------------------------\n";
            cout<<"\t |  BORROW_ID         =   "<<this->borrow_ID<<endl;
            cout<<"\t |  BOOK_ID           =   "<<this->book_ID<<endl;
            cout<<"\t |  PARTON_ID         =   "<<this->parton_ID<<endl;
            cout<<"\t |  BORROW_DATE       =   "<<this->borrow_date<<endl;
            cout<<"\t |  RETURN_DATE       =   "<<this->return_date<<endl;
            cout<<"\t |  OVERDUE_DAYS      =   "<<this->overdue_days<<endl;
            cout<<"\t -------------------------------\n";
        }

        // DESTRUCTOR.
        ~Borrow_Record(){
            //nothing to do.
        }
};



//*NODE CLASS[FOR BORROW_LIST]*//
class Borrow_Node{
    
    public:

        Borrow_Record data;
        Borrow_Node* next;

        // CONSTRUCTOR.
        Borrow_Node(Borrow_Record& B){
            this->data = B;
            this->next = NULL;
        }

        // DESTRUCTOR.
        ~Borrow_Node(){
        }

};


//** BORROW RECORD LIST. */
class Borrow_Record_List{

    private:

        Borrow_Node* head;
        Borrow_Node* tail;


    public:

        // CONSTRUCTOR.
        Borrow_Record_List(){
            this->head = NULL;
            this->tail = NULL;
        }


        // READ BORROWER DATA FROM FILE. 
        void read_borrow_data(){

            int row = count_book_lines("Borrow_Record.txt");
            if(row<0){
                cerr<<"\n\t\t NO DATA FOUND IN BORROW_RECORD.txt.\n";
                return;
            }

            ifstream file("Borrow_Record.txt");
            if(!file){
                cerr<<"\n\t\t ERROR OPENING THE FILE.\n";
                return;
            }

            while(true){

                Borrow_Record record;
                file>>record.borrow_ID>>record.book_ID>>record.parton_ID>>record.borrow_date>>record.return_date>>record.overdue_days;

                if( file.eof() ){
                    return;
                }

                Borrow_Node* new_node = new Borrow_Node(record);

                if(this->head == NULL){
                    this->head = new_node;
                    this->tail = new_node;
                }
                else{
                    this->tail->next = new_node;
                    this->tail = new_node;
                }

            }

            file.clear();
            file.close();
            
        }


        // PRINT THE BORROW RECORDS.
        void print_borrow_records(){
            Borrow_Node* temp = this->head;
            while(temp!= NULL){
                temp->data.Print();
                temp = temp->next;
            }
        }


        // ALLOW BORROWING FOR BOOKS.
        int get_books_borrowed(int Parton_ID){

            Borrow_Node* temp = this->head;
            int count = 0;
            while(temp!= NULL){
                if(temp->data.parton_ID == Parton_ID){
                    count++;
                }
                temp = temp->next;
            }
            return count;
        }


        // BORROW BOOKS [ALLOW PARTON TO BORROW BOOKS <= 3 ]
        void borrow_book(){

            int parton_ID;
            cout<<"\nENTER THE PARTON_ID TO BORROW BOOKS : ";
            cin>>parton_ID;
            while(parton_ID<0){
                cout<<"\nINVALID PARTON_ID. PLEASE ENTER A POSITIVE INTEGER.\n";
                cin>>parton_ID;
            }

            int Book_ID;
            cout<<"\nENTER THE BOOK_ID TO BORROW : ";
            cin>>Book_ID;
            while(Book_ID<0){
                cout<<"\nINVALID BOOK_ID. PLEASE ENTER A POSITIVE INTEGER.\n";
                cin>>Book_ID;
            }

            int Borrow_ID;
            cout<<"\nCHOOSE YOUR BORROWER ID.\n";
            cin>>Borrow_ID;
            while(Borrow_ID<0){
                cout<<"\nINVALID BORROWER ID. PLEASE ENTER A POSITIVE INTEGER.\n";
                cin>>Borrow_ID;
            }

            Borrow_Node* temp = this->head;
            bool found = false;
            while(temp!= NULL){
                if(temp->data.book_ID == Book_ID){
                    found = true;
                    break;
                }
                temp = temp->next;
            }
            if(!found){
                cerr<<"\n\t\t BOOK NOT FOUND.\n";
                return;
            }

            if(this->get_books_borrowed(parton_ID) >= 3){
                cerr<<"\n\t\t PARTON CAN'T BORROW MORE THAN 3 BOOKS.\n";
                return;
            }
            int borrow_day;
            cout<<"\nENTER THE DATE OF BORROWING (1-30) : ";
            cin>>borrow_day;
            while(borrow_day<1 || borrow_day>30){
                cout<<"\nINVALID DATE. PLEASE ENTER A DATE BETWEEN 1-30.\n";
                cin>>borrow_day;
            }
            int return_day = borrow_day + 14;
            int Overdue_day=0;

            // WRITE DATA IN [Borrow_Record.txt]

            ofstream file("Borrow_Record.txt", ios::out | ios::app);
            if(!file){
                cerr<<"\n\t ERROR OPENING THE FILE.\n";
                return;
            }
            file<<Borrow_ID<<" "<<parton_ID<<" "<<Book_ID<<" "<<borrow_day<<" "<<return_day<<" "<<Overdue_day<<endl;
            file.close();

            // CALL THE DECRIMENT FUNCTION IN BOOKS CLASS.
            Book_List book_list;
            book_list.read_books();
            book_list.decrement_book(Book_ID);

        }


        // RETURN BOOKS [UPDATE BOOK COUNT & REMOVE THE BORROW RECORD]
        void return_book(){

            int Borrow_ID;
            cout<<"\nENTER THE BORROW_ID TO RETURN BOOKS : ";
            cin>>Borrow_ID;
            while(Borrow_ID<0){
                cout<<"\nINVALID BORROW_ID. PLEASE ENTER A POSITIVE INTEGER.\n";
                cin>>Borrow_ID;
            }
            
            Borrow_Node* temp = this->head;
            
            bool found = false;
            while(temp!= NULL){
                if(temp->data.borrow_ID == Borrow_ID){
                    found = true;
                    break;
                }
                temp = temp->next;
            }
            
            if(!found){
                cerr<<"\n\t\t BORROW RECORD NOT FOUND.\n";
                return;
            }
            
            int Book_ID = temp->data.book_ID;
            int return_day;
            cout<<"\nENTER THE DATE OF RETURN (1-30) : ";
            cin>>return_day;
            
            while(return_day<1 || return_day>30){
                cout<<"\nINVALID DATE. PLEASE ENTER A DATE BETWEEN 1-30.\n";
                cin>>return_day;
            }
            int overdue_days = return_day - temp->data.return_date;
            if(overdue_days > 0){
                cerr<<"\n\t\t OVERDUE BOOK. PAY FINE : "<<overdue_days*500<<endl;
            }
            
            Borrow_Node* prev = NULL;
            temp = this->head;
            while(temp!= NULL){
                if(temp->data.borrow_ID == Borrow_ID){
                    if(prev == NULL){
                        this->head = temp->next;
                        if(this->head == NULL)
                            this->tail = NULL;
                    }
                    else{
                        prev->next = temp->next;
                        if(temp->next == NULL)
                            this->tail = prev;
                    }
                    delete temp;
                    break;
                }
                prev = temp;
                temp = temp->next;
            }
            // UPDATE DATA IN [Borrow_Record.txt]
            ofstream file("Borrow_Record.txt", ios::out | ios::trunc);
            if(!file){
                cerr<<"\n\t ERROR OPENING THE FILE.\n";
                return;
            }
            
            Borrow_Node* temp2 = this->head;

            while(this->head!= NULL){
                file<<this->head->data.borrow_ID<<" "<<this->head->data.parton_ID<<" "<<this->head->data.book_ID<<" "<<this->head->data.borrow_date<<" "
                <<this->head->data.return_date<<" "<<this->head->data.overdue_days<<endl;

                this->head = this->head->next;
            }

            file.close();

            // CALL THE INCREMENT FUNCTION IN BOOKS CLASS.
            Book_List book_list;
            book_list.read_books();
            book_list.increment_book(Book_ID);
        }


        // BORROW HISTORY BASED ON ID.
        void borrow_history(int Parton_ID){

            Borrow_Node* temp = this->head;
            
            int count=0;
            while(temp!= NULL){
                if(temp->data.parton_ID == Parton_ID){
                    count++;
                    cout<<"\n\t\t BORROW ID : "<<temp->data.borrow_ID<<"\t BOOK ID : "<<temp->data.book_ID
                    <<"\t DATE OF BORROWING : "<<temp->data.borrow_date<<"\t RETURN DATE : "
                    <<temp->data.return_date<<"\t OVERDUE DAYS : "<<temp->data.overdue_days<<endl;
                }
                temp = temp->next;
            }
            if(count == 0){
                cerr<<"\n\t\t NO BORROW HISTORY FOUND.\n";
            }
        }


        // LIST OF OVERDUE BOOKS.
        void overdue_books(){

            Borrow_Node* temp = this->head;

            bool yes=false;
            
            while(temp!= NULL){
                if(temp->data.overdue_days > 0){
                    yes = true;
                    cout<<"\n\t\t BORROW ID : "<<temp->data.borrow_ID<<"\t BOOK ID : "<<temp->data.book_ID<<"\t DATE OF BORROWING : "<<temp->data.borrow_date<<"\t RETURN DATE : "<<temp->data.return_date<<"\t OVERDUE DAYS : "<<temp->data.overdue_days<<endl;
                }
                temp = temp->next;
            }
            if(!yes){
                cerr<<"\n\t\t NO OVERDUE BOOKS FOUND.\n";
            }
        }

        // DELETING FUNCTION.
        void del_borrow_records(){

            Borrow_Node* temp = this->head;
            Borrow_Node* prev = NULL;
            
            while(temp!= NULL){
                prev = temp;
                temp = temp->next;
                delete prev;
            }
            this->head = NULL;
            this->tail = NULL;
        }


        // DESTRUCTOR.
        ~Borrow_Record_List(){
            del_borrow_records();
        }

};


// LOCAL MAIN FOR BOOK FUNCTIONS.
void Book_Menue();

// LOCAL MAIN FOR PARTON FUNCTIONS.
void Parton_Menue();

//** BORROW RECORD ANALYSIS. */
void Borrow_Record_Menue();

//** REPORTS MENUE. */
void Report_Menue();


//** MAIN FUNCTION. */
int main(){

    LMS();

    int choice;
    while(true){

        LOADING_LINE();

        cout<<ANSI_COLOR_RED<<"\n\t *[ LIBRARY MANAGEMENT SYSTEM ]* \n"<<ANSI_COLOR_RESET;
        cout<<ANSI_COLOR_YELLOW<<"\t -----------------------------------\n";
        cout<<"\t [1]. BOOKS\n";
        cout<<"\t [2]. PARTONS\n";
        cout<<"\t [3]. BORROW RECORD\n";
        cout<<"\t [4]. REPORTS\n";
        cout<<"\t [5]. EXIT\n";
        cout<<"\t -----------------------------------\n"<<ANSI_COLOR_RESET;
        cout<<ANSI_COLOR_RED<<"\n ENTER YOUR CHOICE : "<<ANSI_COLOR_RESET<<endl;

        buttons();
        
        cin>>choice;
        while(choice<1 || choice>5){
            cout<<"\n\t\t INVALID CHOICE.\n";
            cin>>choice;
        }
        
        cout<< "\n\t\t--------------------------------------------------"; 
        cout<< "\n\t\t|    ** [ THANKS FOR YOUR COOPERATION ] **       |";
        cout<< "\n\t\t| GRANTING YOU ACCESS ACCORDING TO YOUR CHOICE > |";
        cout<< "\n\t\t--------------------------------------------------\n\n";
        
        Sleep(2000);

        LOADING_LINE();

        switch(choice){
            case 1:
            {
                Book_Menue();
                break;
            }
            case 2:
            {
                Parton_Menue();
                break;
            }
            case 3:
            {
                Borrow_Record_Menue();
                break;
            }
            case 4:
            {
                Report_Menue();
                break;
            }
            case 5:
            {
                cout<<ANSI_COLOR_BLUE<<"\n\t\t-------------------------------------------------"<<ANSI_COLOR_RESET; 
                cout<<ANSI_COLOR_ORANGE<<"\n\t\t|    ** [ THANKS FOR USING OUR SYSTEM] **       |"<<ANSI_COLOR_RESET;
                cout<<ANSI_COLOR_BLUE<<"\n\t\t-------------------------------------------------\n\n"<<ANSI_COLOR_RESET;
                return 0;
            }
            default:
            {
                cout<<"\n\t\t INVALID CHOICE.\n";
            }

        }

    }

return 0;
}


//** BOOK MENUE. */
void Book_Menue(){

    while(true){
        
        Book_List b;

        cout<<ANSI_COLOR_ORANGE<<"\n\t *[ BOOK MENUE ]* \n"<<ANSI_COLOR_RESET;
        cout<<ANSI_COLOR_GREEN<<"\t -----------------------------\n";
        cout<<"\t [1]. ADD NEW BOOK\n";
        cout<<"\t [2]. LIST ALL BOOKS\n";
        cout<<"\t [3]. SEARCH FOR BOOK\n";
        cout<<"\t [4]. EDIT BOOK INFORMATION\n";
        cout<<"\t [5]. DELETE BOOK\n";
        cout<<"\t [6]. EXIT\n";
        cout<<"\t -----------------------------\n"<<ANSI_COLOR_RESET;
        cout<<ANSI_COLOR_ORANGE<<"\n ENTER YOUR CHOICE : "<<ANSI_COLOR_RESET;
        
        buttons();
        
        int choice;
        cin>>choice;
        while(choice<1 || choice>6){
            cout<<"\n\t\t INVALID CHOICE.\n";
            cin>>choice;
        }

        b.read_books();      // READ DATA FROM FILE.

        switch(choice){
            case 1:
            {
                b.add_book();
                break;
            }
            case 2:
            {
                b.print_book_list();
                break;
            }
            case 3:
            {
                b.search_book();
                break;
            }
            case 4:
            {
                b.edit_book();
                break;
            }
            case 5:
            {
                b.delete_book();
                break;
            }
            case 6:
            {
                cout<<"\n\t\t EXITING...\n";
                return;
            }
            default:
            {
                cerr<<"\n\t\t INVALID CHOICE.\n";
                break;
            }
    
        }// switch ki

        b.del_Book_List();
    
    }// while ki braces

}


//** PARTONS MENUE. */
void Parton_Menue(){

    Patron_List p;

    while(true){

        cout<<ANSI_COLOR_ORANGE<<"\n\t {*{ PARTON MENUE }*}\n"<<ANSI_COLOR_RESET;
        cout<<ANSI_COLOR_PINK<<"\t -----------------------------------\n";
        cout<<"\t [1]. REGISTER NEW PARTON\n";
        cout<<"\t [2]. LIST ALL PARTONS\n";
        cout<<"\t [3]. SEARCH FOR PARTON\n";
        cout<<"\t [4]. EDIT PARTON INFORMATION\n";
        cout<<"\t [5]. DELETE PARTON\n";
        cout<<"\t [6]. EXIT\n";
        cout<<"\t -----------------------------------\n"<<ANSI_COLOR_RESET;
        cout<<ANSI_COLOR_ORANGE<<"\n ENTER YOUR CHOICE : "<<ANSI_COLOR_RESET;

        buttons();
        
        int choice;
        cin>>choice;
        while(choice<1 || choice>6){
            cout<<"\n\t\t INVALID CHOICE.\n";
            cin>>choice;
        }

        p.read_patrons_data();      // READ DATA FROM FILE.

        switch(choice){
            case 1:
            {
                p.register_parton();
                break;
            }
            case 2:
            {
                p.print_partons_data();
                break;
            }
            case 3:
            {
                p.search_parton();
                break;
            }
            case 4:
            {
                p.edit_parton_info();
                break;
            }
            case 5:
            {
                p.delete_parton();
                break;
            }
            case 6:
            {
                cout<<"\n\t\t THANK YOU FOR USING THE LIBRARY MANAGEMENT SYSTEM.\n";
                return;
            }
            default:
            {
                cerr<<"\n\t\t INVALID CHOICE.\n";
                break;
            }

        }//switch ki
    
    }//loop ki

}


//** BORROW RECORD ANALYSIS. */
void Borrow_Record_Menue(){
    
    Borrow_Record_List br;
    br.read_borrow_data();

    while(true){
        
        cout<<ANSI_COLOR_ORANGE<<"\n\t *[ BORROW RECORD MENUE ]*\n"<<ANSI_COLOR_RESET;
        cout<<ANSI_COLOR_YELLOW<<"\t -----------------------------\n";
        cout<<"\t [1]. BORROW NEW BOOKS. \n";
        cout<<"\t [2]. RETURN BORROWED BOOKS.\n";
        cout<<"\t [3]. SEE BORROW HISTORY\n";
        cout<<"\t [4]. LIST OVERDUE BOOKS\n";
        cout<<"\t [5]. EXIT\n";
        cout<<"\t -----------------------------\n"<<ANSI_COLOR_RESET;
        cout<<ANSI_COLOR_ORANGE<<"\n ENTER YOUR CHOICE : "<<ANSI_COLOR_RESET<<endl;

        buttons();
        
        int choice;
        cin>>choice;
        while(choice<1 || choice>5){
            cout<<"\n\t\t INVALID CHOICE.\n";
            cin>>choice;
        }


        switch(choice){
            case 1:
            {
                br.borrow_book();
                break;
            }
            case 2:
            {
                br.return_book();
                break;
            }
            case 3:
            {
                br.print_borrow_records();
                break;
            }
            case 4:
            {
                br.overdue_books();
                break;
            }
            case 5:
            {
                cout<<"\n\t\t THANK YOU FOR USING THE LIBRARY MANAGEMENT SYSTEM.\n";
                return;
            }
            default:
            {
                cerr<<"\n\t\t INVALID CHOICE.\n";
                break;
            }

        }//switch ki

    }// loop ki

}


//** REPORTS MENUE. */
void Report_Menue(){

    while(true){

        cout<<ANSI_COLOR_ORANGE<<"\n\t { REPORTS MANAGEMENT PORTAL } \n"<<ANSI_COLOR_RESET;
        cout<<ANSI_COLOR_RED<<"\t ---------------------------------\n";
        cout<<"\t [1]. SEE THE BOOKS CURRENTLY BORROWED.\n";
        cout<<"\t [2]. SEE THE BOOKS CURRENTLY AVAILABLE.\n";
        cout<<"\t [3]. SEE THE OVERDUE BOOKS.\n";
        cout<<"\t [4]. BROWSE HISTORY OF INDIVIDUAL PARTONS [ID].\n";
        cout<<"\t [5]. EXIT. \n";
        cout<<"\t ---------------------------------\n"<<ANSI_COLOR_RESET;
        cout<<ANSI_COLOR_ORANGE<<"\n ENTER YOUR CHOICE : "<<ANSI_COLOR_RESET<<endl;

        buttons();
        
        int choice;
        cin>>choice;
        while(choice<1 || choice>5){
            cout<<"\n\t\t INVALID CHOICE.\n";
            cin>>choice;
        }

        switch(choice){
            case 1:
            {
                Book_List b1;
                b1.read_books();
                b1.see_borrowed_books();
                b1.del_Book_List();
            break;
            }
            case 2:
            {
                Book_List b2;
                b2.read_books();
                b2.see_available_books();
                b2.del_Book_List();
            break;
            }
            case 3:
            {
                Borrow_Record_List br;
                br.read_borrow_data();
                br.overdue_books();
                br.del_borrow_records();
            break;
            }
            case 4:
            {
                Borrow_Record_List p1;
                p1.read_borrow_data();
                cout<<"\n ENTER THE PARTON'S ID : ";
                int id;
                cin>>id;
                p1.borrow_history(id);
                p1.del_borrow_records();
            break;
            }
            case 5:
            {
                cout<<"\n\t\t THANK YOU FOR USING THE REPORTS MANAGEMENT PORTAL.\n";
                return;
            }
            default:
            {
                cerr<<"\n\t\t INVALID CHOICE.\n";
                break;
            }

        } //switc ki

    }//loop ki

}

