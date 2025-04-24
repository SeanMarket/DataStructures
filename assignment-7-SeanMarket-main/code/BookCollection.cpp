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
    destroybooks(root);
}

void BookCollection::removeBook(string bookName)
{
    removeHelper(root, bookName);
}

Book *BookCollection::removeHelper(Book *node, string bookName)
{
    if (node == nullptr)
    {
        cout << "Book not found!" << endl;
        return nullptr;
    }

    if (bookName < node->bookName)
    {
        node->left = removeHelper(node->left, bookName);
    }
    else if (bookName > node->bookName)
    {
        node->right = removeHelper(node->right, bookName);
    }
    else
    {
        if (node->left == nullptr && node->right == nullptr)
        { //leaf
            delete node;
            return nullptr;
        }

        if (node->left == nullptr)
        { //one child
            Book *temp = node->right;
            delete node;
            return temp;
        }
        if (node->right == nullptr)
        {
            Book *temp = node->left;
            delete node;
            return temp;
        }

        //two children
        Book *temp = findLowest(node->right);
        //Replace the current node's data with the next's data
        node->bookName = temp->bookName;
        node->rating = temp->rating;
        node->author = temp->author;

        //Remove the next node
        node->right = removeHelper(node->right, temp->bookName);
    }

    return node;
}

Book *BookCollection::findLowest(Book *node)
{
    while (node && node->left)
    {
        node = node->left;
    }
    return node;
}

void BookCollection::rotateLeftCollection(string bookName)
{
    root = rotateHelper(root, bookName);
}

Book *BookCollection::rotateHelper(Book *node, string bookName)
{
    if (node == nullptr)
        return node;

    //Find the node to rotate
    if (bookName < node->bookName)
    {
        node->left = rotateHelper(node->left, bookName);
    }
    else if (bookName > node->bookName)
    {
        node->right = rotateHelper(node->right, bookName);
    }
    else
    {
        //Rotate this node to the left
        if (node->right == nullptr)
        {
            return node;
        }

        Book *newParent = node->right;
        node->right = newParent->left;
        newParent->left = node;

        return newParent; //New parent after rotation
    }
    return node;
}

string BookCollection::closestParent(string book1, string book2)
{
    if (search(root, book1) == nullptr || search(root, book2) == nullptr)
    {
        cout << "Book not found!" << endl;
        return "Error - wrong book name";
    }

    //Find the closest parent
    Book *op = findoldparent(root, book1, book2);
    if (op == nullptr)
    {
        cout << "Book not found!" << endl;
        return "Error - wrong book name";
    }
    return op->bookName;
}

Book *BookCollection::findoldparent(Book *node, string book1, string book2)
{
    if (node == nullptr)
    {
        return nullptr;
    }

    if (book1 < node->bookName && book2 < node->bookName)
    {
        return findoldparent(node->left, book1, book2);
    }
    else if (book1 > node->bookName && book2 > node->bookName)
    {
        return findoldparent(node->right, book1, book2);
    }

    return node;
}

//copy and pasted from assignment 6

void BookCollection::addBook(string bookName, string author, double rating)
{
    Book *newBook = new Book(bookName, author, rating);
    insert(root, newBook);
}

void BookCollection::showBookCollection()
{
    inOrdPrint(root);
}

void BookCollection::showBook(string bookName)
{
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
    cout << "Books By: " << author << '\n';

    byAuthor(root, author);
}

void BookCollection::showHighestRatedBooks()
{
    double highest = -1.0;

    highest = highestRated(root, highest);

    if (highest == -1.0)
    {
        cout << "Collection is empty.\n";
        return;
    }

    cout << "Highest Rating: " << highest << '\n';

    highestRatedPrint(root, highest);
    return;
}

int BookCollection::getHeightOfBookCollection()
{
    return height(root);
}

void BookCollection::insert(Book *&parent, Book *&child)
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
        {
            insert(parent->right, child);
        }
        else
        {
            insert(parent->left, child);
        }
    }
}

void BookCollection::inOrdPrint(Book *B)
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
        inOrdPrint(B->left);
        cout << "BOOK: " << B->bookName << " BY: " << B->author << " RATING: " << B->rating << '\n';
        inOrdPrint(B->right);
    }
}

Book *BookCollection::search(Book *B, string bookName)
{
    if (B == nullptr)
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

void BookCollection::byAuthor(Book *B, string author)
{
    if (B == nullptr)
    {
        return;
    }
    else
    {
        byAuthor(B->left, author);

        if (B->author == author)
        {
            cout << B->bookName << " RATING: " << B->rating << endl;
        }

        byAuthor(B->right, author);
    }
}

double BookCollection::highestRated(Book *B, double &highestRating)
{

    if (root == nullptr)
    {
        return -1.0;
    }
    else if (B == 0)
    {
        return 0.0;
    }
    else
    {
        highestRated(B->left, highestRating);

        if (B->rating > highestRating)
        {
            highestRating = B->rating;
        }

        highestRated(B->right, highestRating);
    }

    return highestRating;
}

void BookCollection::highestRatedPrint(Book *B, double highestRating)
{

    if (B == 0)
    {
        return;
    }
    else
    {
        highestRatedPrint(B->left, highestRating);

        if (B->rating == highestRating)
        {
            cout << B->bookName << " BY: " << B->author << '\n';
        }

        highestRatedPrint(B->right, highestRating);
    }
}

int BookCollection::height(Book *B)
{
    if (B == 0)
    {
        return 0;
    }

    return 1 + max(height(B->left), height(B->right));
}

void BookCollection::destroybooks(Book *node)
{
    if (node == nullptr)
    {
        return;
    }
    else
    {
        destroybooks(node->left);
        destroybooks(node->right);
        delete node;
    }

    return;
}