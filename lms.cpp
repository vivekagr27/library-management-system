#include<bits/stdc++.h>
#include<iostream>
#include<vector>
#include<fstream>
#include<cstring>
using namespace std;

class Book {
    public:
        string title;
        string author;
        int ISBN;
        string publication;
        bool issued;
        // void book_request();
        // void show_duedate();
        bool check_issued(string isbn);
};

bool Book:: check_issued(string isbnn)
{
    fstream bookDataFile;
    bookDataFile.open("books.txt",ios::in);
    if(bookDataFile.is_open())
    {
        string line;
        while(getline(bookDataFile,line))
        {
            stringstream ss(line);
            string title,author,publication,isbn,issued;
            getline(ss,title,',');
            getline(ss,author,',');
            getline(ss,isbn,',');
            getline(ss,publication,',');
            getline(ss,issued,',');
            if(isbnn == isbn){
                bookDataFile.close();
                if(issued == "0") return 0;
                cout << "The book with this isbn number is already issued\n";
                return 1; 
            }
        }
        cout << "The book with this isbn number doesnot exist\n";
        return 1;
        bookDataFile.close();  
    }
};

class Book_db {
    public:
        void add();
        void update();
        void delet();
        void search(string);
        void display();
        void book_issued_to();
        void unissue_book();
        // void check_issue();
};

class User {
    public:
        string name;
        string ID;
        string password;
        string role;
        void see_my_books(string id);
        // int clear_fine(string id);
        void issue_book(string id);
        // void unissue_book(string id);
};

class User_db {
    public:
        void add();
        void update();
        void delet();
        void search(string);
        void display();
        void books_issued_to_user();
};

void User_db:: add(void){
    User new_user;
    cout << "Enter id of the user\n";
    getline(cin,new_user.ID);
    fstream userDataFile;
    userDataFile.open("users.txt",ios::in);
    if(userDataFile.is_open())
    {
        string line;
        while(getline(userDataFile,line))
        {
            stringstream ss(line);
            string name,id,password,role;
            getline(ss,name,',');
            getline(ss,id,',');
            getline(ss,password,',');
            getline(ss,role,',');
            if(new_user.ID == id){
                cout << "User with this ID already exits.\n";
                userDataFile.close();
                return ;
            }
        }
        userDataFile.close();  
    }
    cout << "Enter name of the user\n";
    getline(cin,new_user.name);
    cout << "Enter password of the user\n";
    getline(cin,new_user.password);
    cout << "Enter role of the user\n";
    getline(cin,new_user.role);
    userDataFile.open("users.txt",ios::app);
    if(userDataFile.is_open())
    {
        userDataFile << new_user.name << "," << new_user.ID << "," << new_user.password << "," << new_user.role << "\n";
        userDataFile.close();
    }
    return ;
};

void User_db:: update(void){
    string input_id;
    cout << "Enter the id of user you need to update\n";
    cin >> input_id;
    getchar();
    fstream userDataFile;
    userDataFile.open("users.txt",ios::in);
    fstream updatedFile;
    updatedFile.open("updatedUsers.txt",ios::out);
    if(userDataFile.is_open())
    {
        string line;
        bool updated=0;
        while(getline(userDataFile,line))
        {
            stringstream ss(line);
            string name,id,password,role;
            getline(ss,name,',');
            getline(ss,id,',');
            getline(ss,password,',');
            getline(ss,role,',');
            if(input_id == id){
                updated =1;
                cout << "Enter new name of the user\n";
                getline(cin,name);
                // getchar();
                cout << "Enter new password of the user\n";
                getline(cin,password);
                // getchar();
                updatedFile << name << "," << id << "," << password << "," << role << "\n";
            }else{
                updatedFile << line << endl;
            }
        }
        userDataFile.close();
        updatedFile.close();
        remove("users.txt");
        rename("updatedUsers.txt","users.txt");
        if(!updated){
            cout << "No user corresponding to the input id\n";
        }
    }
    return ;
};

void User_db:: delet (void){
    string input_id;
    int deleted=0;
    cout << "Enter the id of user you need to delete\n";
    cin >> input_id;
    fstream userDataFile;
    userDataFile.open("users.txt",ios::in);
    fstream updatedFile;
    updatedFile.open("updatedUsers.txt",ios::out);
    if(userDataFile.is_open())
    {
        string line;
        while(getline(userDataFile,line))
        {
            stringstream ss(line);
            string name,id,password,role;
            getline(ss,name,',');
            getline(ss,id,',');
            getline(ss,password,',');
            getline(ss,role,',');
            if(input_id != id){
                updatedFile << line << endl;
            }
            else{
                deleted=1;
            }
        }
        userDataFile.close();
        updatedFile.close();
        remove("users.txt");
        rename("updatedUsers.txt","users.txt");
        if(!deleted){
            cout << "No user corresponding to the input id\n";
        }
    }
    return ;
};

void User_db:: search (string input_id){
    int searched=0;
    fstream userDataFile;
    userDataFile.open("users.txt",ios::in);
    if(userDataFile.is_open())
    {
        string line;
        while(getline(userDataFile,line))
        {
            stringstream ss(line);
            string name,id,password,role;
            getline(ss,name,',');
            getline(ss,id,',');
            getline(ss,password,',');
            getline(ss,role,',');
            if(input_id == id){
                searched=1;
                cout << "\nName - " << name << "\nID - " << id << "\nPassword - " << password << "\nRole - "<<role <<endl;
            }
        }
        userDataFile.close();
        if(!searched){
            cout << "No user corresponding to the input id\n";
        }
    }
    return ;
};

void User_db::display(void){
    fstream userDataFile;
    userDataFile.open("users.txt",ios::in);
    if(userDataFile.is_open())
    {
        string line;
        while(getline(userDataFile,line))
        {
            stringstream ss(line);
            string name,id,password,role;
            getline(ss,name,',');
            getline(ss,id,',');
            getline(ss,password,',');
            getline(ss,role,',');
            cout << "\nName - " << name << "\nID - " << id << "\nPassword - " << password << "\nRole - "<<role << "\n------" <<endl;
        }
        userDataFile.close();
    }
    return ;
}

void User_db::books_issued_to_user(void){
    string input_id;
    int searched=0;
    cout << "Enter the id of user you need to search books\n";
    cin >> input_id;
    fstream userDataFile;
    userDataFile.open("userWithBooks.txt",ios::in);
    if(userDataFile.is_open())
    {
        string line;
        while(getline(userDataFile,line))
        {
            stringstream ss(line);
            string id;
            vector <string> books;
            string book;
            getline(ss,id,',');
            if(input_id == id){
                searched=1;
                cout << "ISBN OF Books issued to this user are as follows\n";
                Book_db curr_db;
                while(getline(ss,book,','))
                {
                    // curr_db.search(book);
                    cout << book << endl;
                    cout << "--------------\n";
                }
            }
        }
        userDataFile.close();
        if(!searched){
            cout << "No user corresponding to the input id\n";
        }
    }
    return ;
}

void Book_db:: add(void){
    Book new_book;
    cout << "Enter isbn of the book\n";
    cin >> new_book.ISBN;
    getchar();
    fstream bookDataFile;
    bookDataFile.open("books.txt",ios::in);
    if(bookDataFile.is_open())
    {
        string line;
        while(getline(bookDataFile,line))
        {
            stringstream ss(line);
            string title,author,publication,isbn,issued;
            getline(ss,title,',');
            getline(ss,author,',');
            getline(ss,isbn,',');
            getline(ss,publication,',');
            getline(ss,issued,',');
            if(new_book.ISBN == stoi(isbn)){
                cout << "Book with this ISBN already exits.\n";
                bookDataFile.close();
                return ;
            }
        }
        bookDataFile.close();  
    }
    cout << "Enter title of the book\n";
    getline(cin,new_book.title);
    cout << "Enter author of the book\n";
    getline(cin,new_book.author);
    cout << "Enter publication of the book\n";
    getline(cin,new_book.publication);
    new_book.issued=0;
    bookDataFile.open("books.txt",ios::app);
    if(bookDataFile.is_open())
    {
        bookDataFile << new_book.title << "," << new_book.author << "," << new_book.ISBN << "," << new_book.publication << "," << new_book.issued << "\n";
        bookDataFile.close();
    }
    return ;
};

void Book_db:: update(void){
    string input_isbn;
    cout << "Enter the isbn of book you need to update\n";
    cin >> input_isbn;
    getchar();
    fstream bookDataFile;
    bookDataFile.open("books.txt",ios::in);
    fstream updatedFile;
    updatedFile.open("updatedBooks.txt",ios::out);
    if(bookDataFile.is_open())
    {
        string line;
        bool updated=0;
        while(getline(bookDataFile,line))
        {
            stringstream ss(line);
            string title,author,publication,isbn,issued;
            getline(ss,title,',');
            getline(ss,author,',');
            getline(ss,isbn,',');
            getline(ss,publication,',');
            getline(ss,issued,',');
            if(input_isbn == isbn){
                updated =1;
                cout << "Enter new title of the book\n";
                getline(cin,title);
                cout << "Enter new author of the user\n";
                getline(cin,author);
                cout << "Enter new publication of the user\n";
                getline(cin,publication);
                updatedFile << title << "," << author << "," << isbn << "," << publication << "," << issued << "\n";
            }else{
                updatedFile << line << endl;
            }
        }
        bookDataFile.close();
        updatedFile.close();
        remove("books.txt");
        rename("updatedBooks.txt","books.txt");
        if(!updated){
            cout << "No book corresponding to the input isbn\n";
        }
    }
    return ;
};

void Book_db:: delet(void){
    string input_isbn;
    cout << "Enter the isbn of book you need to delete\n";
    cin >> input_isbn;
    getchar();
    fstream bookDataFile;
    bookDataFile.open("books.txt",ios::in);
    fstream updatedFile;
    updatedFile.open("updatedBooks.txt",ios::out);
    if(bookDataFile.is_open())
    {
        string line;
        bool deleted=0;
        while(getline(bookDataFile,line))
        {
            stringstream ss(line);
            string title,author,publication,isbn,issued;
            getline(ss,title,',');
            getline(ss,author,',');
            getline(ss,isbn,',');
            getline(ss,publication,',');
            getline(ss,issued,',');
            if(input_isbn == isbn){
                deleted =1;
            }else{
                updatedFile << line << endl;
            }
        }
        bookDataFile.close();
        updatedFile.close();
        remove("books.txt");
        rename("updatedBooks.txt","books.txt");
        if(!deleted){
            cout << "No book corresponding to the input isbn\n";
        }
    }
    return ;
};


void Book_db:: search (string input_isbn){
    int searched=0;
    getchar();
    fstream bookDataFile;
    bookDataFile.open("books.txt",ios::in);
    if(bookDataFile.is_open())
    {
        string line;
        while(getline(bookDataFile,line))
        {
            stringstream ss(line);
            string title,author,publication,isbn,issued;
            getline(ss,title,',');
            getline(ss,author,',');
            getline(ss,isbn,',');
            getline(ss,publication,',');
            getline(ss,issued,',');
            if(input_isbn == isbn){
                searched=1;
                cout << "\nTitle - " << title << "\nAuthor - " << author << "\nISBN - " << isbn << "\nPublication - "<<publication << "\nIssued - "<< issued <<endl;
            }
        }
        bookDataFile.close();
        if(!searched){
            cout << "No book corresponding to the input isbn\n";
        }
    }
    return ;
};

void Book_db:: display (void){
    fstream bookDataFile;
    bookDataFile.open("books.txt",ios::in);
    if(bookDataFile.is_open())
    {
        string line;
        while(getline(bookDataFile,line))
        {
            stringstream ss(line);
            string title,author,publication,isbn,issued;
            getline(ss,title,',');
            getline(ss,author,',');
            getline(ss,isbn,',');
            getline(ss,publication,',');
            getline(ss,issued,',');
            cout << "\nTitle - " << title << "\nAuthor - " << author << "\nISBN - " << isbn << "\nPublication - "<<publication << "\nIssued - "<< issued <<"\n------" <<endl;
        }
        bookDataFile.close();
    }
    return ;
};

void Book_db::book_issued_to (void){
    string input_isbn;
    int searched=0;
    cout << "Enter the isbn of book for which you need to search the user\n";
    cin >> input_isbn;
    getchar();
    fstream bookDataFile;
    bookDataFile.open("bookWithUser.txt",ios::in);
    if(bookDataFile.is_open())
    {
        string line;
        while(getline(bookDataFile,line))
        {
            stringstream ss(line);
            string isbn;
            string user;
            getline(ss,isbn,',');
            if(input_isbn == isbn){
                searched=1;
                cout << "User ID to whom the book is issued is -\n ";
                getline(ss,user,',');
                User_db curr_db;
                curr_db.search(user);
            }
        }
        bookDataFile.close();
        if(!searched){
            cout << "Book is not issued to any user\n";
        }
    }
    return ;
};


class Professor: public User {
    private:
        int fine_amount;
        vector<int> mybooks;
    public:
        int calculate_fine(string id);
};

class Student: public User {
    private:
        int fine_amount;
        vector<int> mybooks;
    public:
        int calculate_fine(string id);
};

class Librarian: public User {
    public:
};

void User::see_my_books(string idd){
    fstream userDataFile;
    userDataFile.open("userWithBooks.txt",ios::in);
    if(userDataFile.is_open())
    {
        string line;
        while(getline(userDataFile,line))
        {
            stringstream ss(line);
            string id;
            vector <string> books;
            string book;
            getline(ss,id,',');
            if(idd == id){
                cout << "ISBN OF Books issued by me are as follows\n";
                Book_db curr_db;
                while(getline(ss,book,','))
                {
                    // curr_db.search(book);
                    cout << book << endl;
                    cout << "-------------\n";
                }
            }
        }
        userDataFile.close();
    }
    return ;
};

void User::issue_book(string idd)
{
    cout << "Please Enter the ISBN number of Book you want to issue\n";
    string isbn;
    cin >> isbn;
    Book new_book;
    if(new_book.check_issued(isbn)==1) return ;
    fstream bookDataFile;
    bookDataFile.open("userWithBooks.txt",ios::in);
    fstream updatedFile;
    updatedFile.open("updatedUserWithBooks.txt",ios::out);
    if(bookDataFile.is_open())
    {
        string line;
        while(getline(bookDataFile,line))
        {
            stringstream ss(line);
            string id,book;
            getline(ss,id,',');
            if(idd == id){
                updatedFile << line << "," << isbn << endl;
            }else{
                updatedFile << line << endl;
            }
        }
        bookDataFile.close();
        updatedFile.close();
        remove("userWithBooks.txt");
        rename("updatedUserWithBooks.txt","userWithBooks.txt");
    }
    bookDataFile.open("bookWithUser.txt",ios::in);
    updatedFile.open("updatedBookWithUser.txt",ios::out);
    if(bookDataFile.is_open())
    {
        string line;
        while(getline(bookDataFile,line))
        {
            updatedFile << line << endl;
        }
        updatedFile << isbn << "," << idd << endl;
        bookDataFile.close();
        updatedFile.close();
        remove("bookWithUser.txt");
        rename("updatedBookWithUser.txt","bookWithUser.txt");
    }
    bookDataFile.open("books.txt",ios::in);
    updatedFile.open("updatedBooks.txt",ios::out);
    if(bookDataFile.is_open())
    {
        string line;
        bool updated=0;
        while(getline(bookDataFile,line))
        {
            stringstream ss(line);
            string title,author,publication,isbnn,issued;
            getline(ss,title,',');
            getline(ss,author,',');
            getline(ss,isbnn,',');
            getline(ss,publication,',');
            getline(ss,issued,',');
            if(isbnn == isbn){
                updated =1;
                issued="1";
                updatedFile << title << "," << author << "," << isbn << "," << publication << "," << issued << "\n";
            }else{
                updatedFile << line << endl;
            }
        }
        bookDataFile.close();
        updatedFile.close();
        remove("books.txt");
        rename("updatedBooks.txt","books.txt");
        if(!updated){
            cout << "No book corresponding to the input isbn\n";
        }
    }
    return ;
};

int main()
{
    User_db users;
    Book_db books;
    while(true)
    {
        int loggedIn = false;
        string role, id, password;
        if(!loggedIn)
        {
            begin:
            cout << "Enter your id\n";
            getline(cin,id);
            cout << "Enter your password\n";
            getline(cin,password);
            // cout << "----" << id << "----" << password << endl;
            fstream userDataFile;
            userDataFile.open("users.txt",ios::in);
            if(userDataFile.is_open())
            {
                string line,userName,userId,userPassword,userRole;
                while(getline(userDataFile,line))
                {
                    stringstream ss(line);
                    getline(ss,userName,',');
                    getline(ss,userId,',');
                    getline(ss,userPassword,',');
                    getline(ss,userRole,',');
                    if(userId==id && userPassword==password)
                    {
                        loggedIn = true;
                        role = userRole;
                        goto next;
                    }
                }
            }
            cout << "Invalid username or password. Please enter the correct credentials.\n";
            goto begin ;
        }
        next:
        if(role == "lib"){
            label1:
            cout << "What you want to do ?\n"
            << "1. Add user\n" << "2. Update user\n" << "3. Delete  user\n" << "4. Search user\n"
            << "5. Add book\n" << "6. Update book\n" << "7. Delete  book\n" << "8. Search book\n"
            << "9. See list of all users\n" << "10. See list of all books\n"
            << "11. Check which all books are issued to the input user\n"
            << "12. Check the user to whom input book is issued\n"
            << "13. Logout\n";
            int code;
            cin >> code;
            getchar();
            string input_isbn;
            string input_id;
            switch (code)
            {
                case 1:
                    users.add();
                    goto label1;

                case 2:
                    users.update();
                    goto label1;

                case 3:
                    users.delet();
                    goto label1;
                
                case 4:
                    cout << "Enter the id of user you need to search\n";
                    cin >> input_id;
                    users.search(input_id);
                    goto label1;

                case 5:
                    books.add();
                    goto label1;

                case 6:
                    books.update();
                    goto label1;

                case 7:
                    books.delet();
                    goto label1;

                case 8:
                    cout << "Enter the isbn of book you need to search\n";
                    cin >> input_isbn;
                    books.search(input_isbn);
                    goto label1;

                case 9:
                    users.display();
                    goto label1;

                case 10:
                    books.display();
                    goto label1;

                case 11:
                    users.books_issued_to_user();
                    goto label1;

                case 12:
                    books.book_issued_to();
                    goto label1;

                case 13:
                    loggedIn = false;
                    continue;
            
                default:
                    cout << "Invalid entry. Please enter one from above. \n";
                    goto label1;
            }
        }
        else if(role == "prof"){
           label2:
            Professor prof;
            cout << "What you want to do ?\n"
            << "1. See my books\n"
            << "2. See all books\n"
            << "3. See my fine\n"
            << "4. Clear my fine\n"
            << "5. Issue Book\n"
            << "6. Unissue Book\n"
            << "7. logout\n";
            int code;
            cin >> code;
            getchar();
            switch (code)
            {
                case 1:
                    prof.see_my_books(id);
                    goto label2;
                case 2:
                    books.display();
                    goto label2;

                case 3:
                    // prof.calculate_fine(id);
                    cout << "!!!!---not implemented yet---!!!!\n";
                    goto label2;
                
                case 4:
                    // prof.clear_fine(id);
                    cout << "!!!!---not implemented yet---!!!!\n";
                    goto label2;

                case 5:
                    prof.issue_book(id);
                    goto label2;

                case 6:
                    // prof.unissue_book(id);
                    cout << "!!!!---not implemented yet---!!!!\n";
                    goto label2;

                case 7:
                    loggedIn = false;
                    continue;
            
                default:
                    cout << "Invalid entry. Please enter one from above. \n";
                    goto label2;
            }
        }
        else{
            label3:
            Student stu;
            cout << "What you want to do ?\n"
            << "1. See my books\n"
            << "2. See all books\n"
            << "3. See my fine\n"
            << "4. Clear my fine\n"
            << "5. Issue Book\n"
            << "6. Unissue Book\n"
            << "7. logout\n";
            int code;
            cin >> code;
            getchar();
            switch (code)
            {
                case 1:
                    stu.see_my_books(id);
                    goto label3;
                case 2:
                    books.display();
                    goto label3;

                case 3:
                    // stu.calculate_fine(id);
                    cout << "!!!!---not implemented yet---!!!!\n";
                    goto label3;
                
                case 4:
                    // stu.clear_fine(id);
                    cout << "!!!!---not implemented yet---!!!!\n";
                    goto label3;
                
                case 5:
                    stu.issue_book(id);
                    goto label2;

                case 6:
                    // stu.unissue_book(id);
                    cout << "!!!!---not implemented yet---!!!!\n";
                    goto label2;

                case 7:
                    loggedIn = false;
                    continue;
            
                default:
                    cout << "Invalid entry. Please enter one from above. \n";
                    goto label3;
            }
        }
    }
    return 0;
}