#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <sstream>
#include "code_1/musicPlaylist.hpp"

using namespace std;

int main(){
    Song *YourMom = new Song;
    YourMom->songName="Momma";
    YourMom->artistNames = "Mom";
    YourMom->liked = false;
    YourMom->next = nullptr;

    Song YourMom2;
    YourMom2.songName="Momma";
    YourMom2.artistNames = "Mom2";
    YourMom2.liked = false;
    YourMom2.next = nullptr;

    Song YourMom3;
    YourMom3.songName="Momma";
    YourMom3.artistNames = "Mom3";
    YourMom3.liked = false;
    YourMom3.next = nullptr;

    Song YourDad;
    YourDad.songName="Papa";
    YourDad.artistNames = "Dad";
    YourDad.liked = true;
    YourDad.next = nullptr;

    Song YourBrother;
    YourBrother.songName="Brotha";
    YourBrother.artistNames = "Brother";
    YourBrother.liked = false;
    YourBrother.next = nullptr;

    MusicPlaylist playlist;

    playlist.addSong(nullptr, YourMom);
    playlist.addSong(YourMom, &YourDad);
    playlist.addSong(YourMom, &YourBrother);
    playlist.displayPlaylist();
    return 0;
}