
#include "MusicPlaylist.hpp"

MusicPlaylist::MusicPlaylist()
{
    // No changes needed
}

/*
 * Purpose: Has to detect if a loop is present in the linkedlist pointed by head
 * @param none
 * @return integer length of loop if one exists. If loop not present return -1
 */
int MusicPlaylist::findLoopInPlaylist(){

    // TODO START =============================================
    Song *fast = head;
    Song *slow = head;
    int counter = 0;

    while(fast != nullptr && slow != nullptr){
        if(fast->next->next == nullptr){
            return -1;
        }
        
        fast = fast->next->next;
        slow = slow->next;

        while(fast != slow){
            if(fast->next == nullptr || slow->next == nullptr){
                counter = -1;
                return counter;
            }
            fast = fast->next->next;
            slow = slow->next;
        }

        do{
            slow = slow->next;
            counter++;
        }while(slow != fast);
        return counter;
    }
    counter = -1;
    return counter;
    // TODO END ==================================================
}

/*
 * Purpose: Has to remove all the Song nodes from [start, end] inclusive.
 * Has to print appropriate messages on cout like below if the linkedlist is empty
 * or if the values of start/ end are improper
 * follow the same order for couts in the writeup - check empty list first, then check wrong start/end values
 * @param integers start and end (1 based indexing not 0 based)
 * @return none
 */
void MusicPlaylist::removeSongs(int start, int end){ 
    int count = 1;
    if(head == nullptr){
        cout << "Playlist is Empty\n";
        return;
    }
    else if (start < 1 || start > end){
        cout << "Invalid start or end values\n";
        return;
    }
    else{
        Song *begin = nullptr;
        Song *newLink = nullptr;
        Song *current = head;

        for(int i = 1; i < start && (current->next != nullptr); i++){ // Walk through the LL to find the node previous to start
            if(i == start-1){
                newLink = current;
            }
            current = current->next;
        }
        begin = current;

        Song *endPoint = nullptr;
        Song *temp = nullptr;
        endPoint = head;

        int endCounter = 1;
        for(int i = 1; i < end; i++){
            if (endPoint->next == nullptr && endCounter < end){ //verify endPoint does not go off the end of the LL
                cout << "Invalid start or end values\n";
                return;
            }
            endPoint = endPoint->next;
            endCounter++; 
        }

        if(start == 1){
            head = endPoint->next;
        }
        else{
            newLink->next = endPoint->next;
        }

        //delete function
        temp = begin;
        while(begin != endPoint->next){
            temp = temp->next;
            delete begin;
            begin = temp;
        }
    }
    

    // TODO END ===================================================
}


/*
 * Purpose: Interweave the webpages alternatively into a new linkedlist 
 * starting with the first webpage in the list one
 * Assign the head of the new interweaved list to the head of this BrowserHistory
 * DO NOT create new nodes and copy the data, just use the same nodes from one and two and change pointers
 * If one of them runs out of length append the remaining of the other one at end
 * @param two linkedlist heads one and two
 * @return none
 */
void MusicPlaylist::mergeTwoPlaylists(Song *headOne, Song * headTwo){

    // TODO START =============================================

    int playlist1Size = 0;
    Song *playlist1 = headOne;
    while(playlist1 != nullptr){
        playlist1 = playlist1->next;
        playlist1Size++;
    }

    int playlist2Size = 0;
    Song *playlist2 = headTwo;
    while(playlist2 != nullptr){
        playlist2 = playlist2->next;
        playlist2Size++;
    }



    if(headOne == nullptr){
        head = headTwo;
    }
    else if(headTwo == nullptr){
        head = headOne;
    }
    else if(playlist1Size >= playlist2Size){
        Song *nextHead1Song = headOne->next;
        Song *nextHead2Song = headTwo;
        int evenOddCounter = 2;
        Song *nextSong = head;
        Song *current = nullptr;
        int playlist1Counter = 1;
        int playlist2Counter = 0;
        
        head = headOne;
        current = head;
            while(playlist2Counter < playlist2Size){

                    if(evenOddCounter % 2 == 0){
                        nextSong = nextHead2Song;
                        nextHead2Song = nextHead2Song->next;
                        playlist2Counter++;
                    }
                    else{
                        nextSong = nextHead1Song;
                        nextHead1Song = nextHead1Song->next;
                        playlist1Counter++;
                    }
                    evenOddCounter++;
                    current->next = nextSong;
                    current = nextSong;
            }
        while(playlist1Counter < playlist1Size){
            nextSong = nextHead1Song;
            current->next = nextSong;
            current = nextSong;
            nextHead1Song = nextHead1Song->next;
            playlist1Counter++;
        }
    }
    else if(playlist2Size > playlist1Size){
        Song *nextHead1Song = headOne->next;
        Song *nextHead2Song = headTwo;
        int evenOddCounter = 2;
        Song *nextSong = head;
        Song *current = nullptr;
        int playlist1Counter = 1;
        int playlist2Counter = 0;
        
        head = headOne;
        current = head;
            while(playlist1Counter < playlist1Size){

                    if(evenOddCounter % 2 == 0){
                        nextSong = nextHead2Song;
                        nextHead2Song = nextHead2Song->next;
                        playlist2Counter++;
                    }
                    else{
                        nextSong = nextHead1Song;
                        nextHead1Song = nextHead1Song->next;
                        playlist1Counter++;
                    }
                    evenOddCounter++;
                    current->next = nextSong;
                    current = nextSong;
            }
        while(playlist2Counter < playlist2Size){
            nextSong = nextHead2Song;
            current->next = nextSong;
            current = nextSong;
            nextHead2Song = nextHead2Song->next;
            playlist2Counter++;
        }
    }

    // TODO END ==================================================
}