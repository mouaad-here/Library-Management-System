#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Book {
    private:
        string title;
        string author;
        bool Available;
    public:
        Book(string title_c, string author_c, bool Available_c = true): title(title_c), author(author_c),Available(Available_c){}
        // Getters
        string getTitle() const {
            return title;
        }
        string getAuthor() const {
            return author;
        }
        bool isAvailable()  {
            return Available;
        }
        //setters
        void setAvailable(bool available) {
            Available = available;
        }
        void setAuthor(const string& A) { author = A; }
        void setTitle(const string& T) { title = T; }
        void getDetails() {
            cout << "Title: " << title << "\n"
                << "Author: " << author << "\n"
                << (Available ? "Available" : "Not available") << endl;
        }





};

class Personne {
    protected:
        string name;
        int id;
    public:
        Personne(string name_c, int id_c) : name(name_c), id(id_c) {}
        // why const ? --> check video, answer : becuase we want to not change the value of name and if 
        // that happen considly we'll have an error.
        // Getters
        string getName() const {
            return name;
        }
        int getId() const {
            return id;
        }
        // Setters
        // in the first implimentation I take by copy and it's not recommand it 
        // i should use by refrence, and when I take something by refrence I can change it so that  why 
        // I take as const.
        // example : int a = 0; int& b = a; b =5; than also a will change .

        void setName(const string& s_name) {
            name = s_name;
        }
        void setId(const int& s_id) {
            id = s_id;
        }
        // is it I need destroctore 
    
};

class Admin: public Personne {

    public: 
        Admin(string name_c, int id_c): Personne(name_c, id_c) {}
        void manageBooks() {
            cout << "Managing books :" << endl;
        }
        void manageMembers() {
            cout << "Managing Members :" << endl;
        }
};

class Member: public Personne {

    public:
        Member(string name_c, int id_c): Personne(name_c, id_c) {}
        void borrowBook(Book &book) {
            if(book.isAvailable()){
                cout << name << "browwed the book :" 
                << book.getTitle() << endl;
                book.setAvailable(false);
            }else {
                cout << "the book :" 
                << book.getTitle() << " is not available" << endl;
            }
        }
        void returnBook(Book &book) {
            cout << name << "returned the book" << book.getTitle() << endl;
            book.setAvailable(true);
        }
};

class Library {
    private:
        vector<Book> books;
        vector<Member> members;
    public:
        void addBook(const Book& book) {
            books.push_back(book);
            cout << "book added  to library " << book.getTitle() << endl;
        }
        void removeBook(const string& title) {
            bool exist = false;
            int i;
            for(i = 0; i < books.size(); i++){
                if (books[i].getTitle() == title){
                    exist = true;
                    break;
                }
            }
            
            if(exist){
                books.erase(books.begin() + i);
                cout << "the book is removed" << endl;
            }else {
                cout << "the book is not exist" << endl;
            }

        }
        void addMember(const Member& newMember) {
            members.push_back(newMember);
            cout << newMember.getName() << " added seccssfully to members" << endl;
        }
        void issueBook(const string& title,Member& member){
            int i;
            for(i = 0; i < books.size(); ++i) {
                if(books[i].getTitle() == title && books[i].isAvailable()){
                    member.borrowBook(books[i]);
                    return;
                }
            }
            cout << "the book is not available or not found " << endl;
        }

        void returnBook(const string& title, Member& member){
            int i;
            for(i = 0; i < books.size(); ++i) {
                if(books[i].getTitle() == title && !books[i].isAvailable()){
                    member.returnBook(books[i]);
                    return;
                }
            }
            cout << "the book is not in the list" << endl;
        }
        void Display() {
            cout << "The books in the labrary :" << endl;
            for(int i = 0; i < books.size(); ++i) {
                books[i].getDetails();
            }
        }
};

int main() {
    Library library;
    Book book1("thi is me","mouaad");
    Book book2("C++ programming", "bjarne boustrap");
    Admin admin1("ali", 100), admin2("mo7a", 101);
    library.addBook(book1);
    library.addBook(book2);

    library.Display();
    Member member1("ayman", 1);

    library.addMember(member1);
    library.issueBook("C++ programming", member1);
    library.Display();

    library.returnBook("C++ programming", member1);
    library.Display();


    return 0;
}