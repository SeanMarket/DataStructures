#include "BookCollection.hpp"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

BookCollection::BookCollection()
{
    root = nullptr;
}

BookCollection::~BookCollection()
{
    deleteCollection(root);
}

void BookCollection::addBook(string bookName, string author, double rating)
{
    //TODO
    Book *newBook = new Book(bookName, author, rating);
    insertBook(root, newBook);
}

void BookCollection::showBookCollection()
{
    //TODO
    //InOrderPrint

    inOrderPrint(root);
}

void BookCollection::showBook(string bookName)
{
    //TODO
    Book *newBook = search(root, bookName);

    if (newBook == nullptr)
    {
        cout << "Book not found.\n";
    }
    else
    {
        cout << "Book:" << endl;
        cout << "==================" << endl;
        cout << "Name :" << newBook->bookName << endl;
        cout << "Author :" << newBook->author << endl;
        cout << "Rating :" << newBook->rating << endl;
    }
}

void BookCollection::showBooksByAuthor(string author)
{
    //TODO
    cout << "Books By: " << author << '\n';
    byAuthorHelper(root, author);
}

void BookCollection::showHighestRatedBooks()
{
    //TODO
    double highestRating = -1.0;

    highestRating = highestRatedHelper(root, highestRating);

    if(highestRating == -1.0){
        cout << "Collection is empty.\n";
        return;
    }

    cout << "Highest Rating: " << highestRating << '\n';

    highestRatedHelperPrint(root, highestRating);
    return;
}

int BookCollection::getHeightOfBookCollection()
{
    //TODO
    return heightHelper(root);
}

void BookCollection::deleteCollection(Book *B)
{
    if (B == 0)
        return;
    else
    {
        deleteCollection(B->left);
        deleteCollection(B->right);
        delete B;
    }
}

void BookCollection::insertBook(Book *&parent, Book *&child)
{
    if (parent == 0)
    {
        parent = child;
        return;
    }
    else
    {
        int comp = child->bookName.compare(parent->bookName);
        if (comp > 0)
        { //the comparison returns > 0 if child->bookName comes before parent->bookName
            insertBook(parent->right, child);
        }
        else
        { //comparison returns < 0 if child->bookName comes after parent->bookname.
            insertBook(parent->left, child);
        }
    }
}

void BookCollection::inOrderPrint(Book *B)
{
    if (root == 0)
    {
        cout << "Collection is empty.\n";
        return;
    }

    if (B == 0)
    {
        return;
    }
    else
    {
        inOrderPrint(B->left);
        cout << "BOOK: " << B->bookName << " BY: " << B->author << " RATING: " << B->rating << '\n';
        inOrderPrint(B->right);
    }
}

Book *BookCollection::search(Book *B, string bookName)
{
    if (B == 0)
        return nullptr;
    else if (bookName == B->bookName)
        return B;
    else if (bookName.compare(B->bookName) < 0)
        return search(B->left, bookName);
    else if (bookName.compare(B->bookName) > 0)
        return search(B->right, bookName);
    else
    {
        return nullptr;
    }
}

void BookCollection::byAuthorHelper(Book *B, string author)
{
    if (B == 0)
    {
        return;
    }
    else{
        byAuthorHelper(B->left, author);

        if(B->author == author){
            cout << B->bookName << " RATING: " << B->rating << endl;
        }

        byAuthorHelper(B->right, author);
    }

}

double BookCollection::highestRatedHelper(Book *B, double &highestRating){

    if(root == 0){
        return -1.0;
    }
    else if(B == 0){
        return 0.0;
    }
    else{ //finds the highest rating
        highestRatedHelper(B->left, highestRating);

        if(B->rating > highestRating){
            highestRating = B->rating;
        }

        highestRatedHelper(B->right, highestRating);
    }


    return highestRating;
}

void BookCollection::highestRatedHelperPrint(Book *B, double highestRating){

    if(B==0){
        return;
    }
    else{
        highestRatedHelperPrint(B->left, highestRating);

        if(B->rating == highestRating){
            cout << B->bookName << " BY: " << B->author << '\n';
        }
        
        highestRatedHelperPrint(B->right, highestRating);

    }

}

int BookCollection::heightHelper(Book *B){
    if(B == 0){
        return 0;
    }

    return 1 + max(heightHelper(B->left), heightHelper(B->right));
}