/*************************************************************/
/*                MusicPlaylist Definition                   */
/*************************************************************/
/* TODO: Implement the member functions of a MusicPLaylist   */
/*     This class uses a linked-list of Song structs to      */
/*     represent a playlist structure                        */
/*************************************************************/

#include "musicPlaylist.hpp"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>

using namespace std;

/*
 * Purpose: Constructor for empty linked list
 * @param none
 * @return none
 */
MusicPlaylist::MusicPlaylist() {
    /*
    DO NOT MODIFY THIS
    This constructor is already complete. 
    */
    head = nullptr;
}

MusicPlaylist::MusicPlaylist(Song* song) {
    /*
    DO NOT MODIFY THIS
    This constructor is already complete. 
    */
    head = song;
}

Song* MusicPlaylist::getFirstSong(){
    //DO NOT MODIFY THIS
    return this->head;
}
/*======================== ALL FUNCTIONS BELOW ARE #TODO ======================= */

/**
 * Display the song object
 * 
 * @param song The song object to display
 * @return No output returned. Should write to cout
 */
void Song::displaySong(){
    cout << "[ " << this->songName << ", " << this->artistNames << ", ";
    if(this->liked){
        cout << "<3 ]";
    }
    else{
        cout << "</3 ]";
    }
}

/**
 * Checks whether the music playlist is empty or not
 * 
 * @return True/False if the playlist is empty or not
 */
bool MusicPlaylist::isEmpty(){
    if(head == nullptr){
        return true;
    }
    else{
        return false;
    }
    //TODO
}


/**
 * Walk through all songs in a playlist and display each one based on readme specs.
 * 
 * @return No output returned. Should write to cout using displaySong
 */
void MusicPlaylist::displayPlaylist(){
    Song *temp = head;

    if(isEmpty()){
        cout << "Playlist is empty\n";
        return;
    }
    else if(temp->next == nullptr && !isEmpty()){
        cout << "Displaying songs\n";
        cout << "==================\n";
        temp->displaySong();
        cout << " -> NULL\n";
        cout << "==================\n";
        return;
    }
    else{
        cout << "Displaying songs\n";
        cout << "==================\n";
        while(temp){

            temp->displaySong();
            cout << " -> ";
            temp = temp->next;
        }
            cout << "NULL\n";
        cout << "==================\n";
        return;
    }

    // TODO
}


/**
 * Adds a song to the playlist after the passed song. 
 * @param previousSong The song object to which the newSong should be added to.
 * @param newSong The newSong to be added to the playlist. It should be added after the previousSong (if previousSong is nullptr, song gets added to the beginning)
 * @return No output returned. Should modify the MusicPlaylist 
 */
void MusicPlaylist::addSong(Song* previousSong, Song* newSong){
    Song *temp = head;
    if(previousSong == nullptr){
        // cout << "in the if!\n";
        if(isEmpty()){
            head = newSong;
            // cout << "head: " << head << endl;
            // cout << "new song: " << newSong << endl;
            newSong->next = nullptr;
            // cout << "Head->next->artistNames: " << head->next->artistNames << '\n';
            return;
        }
        else{
            // cout << "in the else!\n";
            // cout << "head next: " << head->next << '\n';
            newSong->next = head;
            // cout << "newSong next: " << newSong->next << '\n';
            head = newSong;


            return;
        }
    }
    else{
        if(previousSong->next == nullptr){
            previousSong->next = newSong;
            newSong->next = nullptr;
            return;
        }
        else{
            temp = previousSong->next;
            newSong->next = temp; 
            previousSong->next = newSong;
            return;
        }

    }
}

/**
 * Search through the music playlist until you find the song by name.
 * 
 * @param name The name of the song being looked for
 * @return Should return a song object. If no song is found, should return nullptr.
 */
Song* MusicPlaylist::searchSongByName(std::string name){
    Song *temp = head;

    if(isEmpty()){
        return nullptr;
    }
    else if(temp->next == nullptr && temp->songName != name){
        return nullptr;

    }
    else{
        while(true){
            if(temp->songName == name){
                return temp;
            }
            else if (temp->next == nullptr){
                return nullptr;
            }
            else{
                temp = temp->next;
            }
        }
    }
}

/**
 * Like the song. Change the boolean (*liked*) from false->true or true->false
 * 
 * @param name The name of the song to like
 * @return No output returned. Should modify the Song and print according to readme specifications.
 */
void MusicPlaylist::likeSong(std::string name){
    // TODO
    Song *temp = searchSongByName(name);
    if(temp == nullptr){
        cout << "Song not found." << endl;
    }
    else{
        if(temp->liked){
            temp->liked = false;
        }
        else{
            temp->liked = true;
        }
        cout << "Song: " << temp->songName << " liked!" << endl;
    }
}

/**
 * Traverse the playlist and display all songs that match the given artistName
 * 
 * @param name The name of the artist that we should search for
 * @return No output returned. Should write to cout each song that matches the artist.
 */  
void MusicPlaylist::displayAllSongsbyArtist(std::string name){
    // TODO
    bool artistFound = false;
    Song *temp = head;
    while(temp){
        if (temp->artistNames == name){
            temp->displaySong();
            cout << '\n';
            artistFound = true;
        }

        temp = temp->next;
    }

    if (artistFound == false){
        cout << "No songs found.\n";
    }
}