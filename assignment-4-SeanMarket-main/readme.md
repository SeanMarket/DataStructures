[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/z7x19nMt)

# CSCI 2270 – Data Structures - Assignment 4: Linked Lists (Part II)

## Objectives
1. Detect the presence of a loop in a linked list and find it's length.
2. Delete all nodes from a sub-section of a linked list.
3. Merge two linked lists such that their nodes alternate.

## Instructions
This assignment is a continuation of HW-3 where you built a music playlist with songs. The only place you have to fill your code to finish HW4 is `MusicPlaylist.cpp`. You'll need to pass the test cases needed to get credit for your code. Use the following steps to test your code as you work on the assignment:

1. Open up your Linux terminal, and navigate to the build directory of this assignment (e.g., `cd build`).
2. Run the `cmake ..` command.
3. Run the `make` command.
4. If there are no compilation errors, two executables will be generated within the build directory: `run_app` and `run_tests`.
5. If you want to run your program, including your app implementation in the `main` function, execute `run_app` from the terminal by typing `./run_app`. 
6. To run the grading tests, execute `run_tests` from the terminal by typing `./run_tests`.

## Overview
Like HW3, you will be implementing functions of a music playlist which is stored as a linked list of songs. You will complete the functions in `MusicPlaylist.cpp`. The linked list will be implemented using the following struct that is already implemented for you:

```
// Song: Node that will be stored in the Playlist linked-list
struct Song
{
  std::string songName;
  std::string artistNames;
  bool liked;
  Song* next;
};
```

> The HW3 functions are available at your disposable in case you want to use them. The details are provided in the `Appendix`.

> **The main function is not being tested in this assignment** but is available for custom debugging. The details are available in the `Custom Debugging` section.

## Requirements
This section enlists the requirements for HW-4. It will provide you with ***everything you need to complete HW-4***. 

### `int findLoopInPlaylist()`
➔ In your music playlist, by making the next pointer of the last song to some intermediate song, you ended up creating a loop. The objective of this function is to return the number of songs that are stuck in the loop. If there is no loop, you return -1.

For example, the image below shows a playlist with the highlighted songs (in green) in a loop. Your function should return 5 in this case, since there are 5 songs stuck in the loop.

![Alt text](images/ListWithLoop.png?raw=true "LinkedList with loop")


#### Hint to solve findLoopInPlaylist():

###### _*Logic*_
So how do you detect if your playlist has a loop? There is a very interesting way to solve this. Imagine you and Usain Bolt (World's fastest sprinter) are running on a circular race track. If you both start together and continue to run, there will be a point when he will overtake you from behind because he is just faster and completes his loop faster than you. If you find it hard to imagine, this scene from The Avengers will help you: https://www.youtube.com/watch?v=7UGu2sRmSHI

###### *Algorithm: To find the loop*
Create two pointers `fast` and `slow` that initially point to `head`. The `slow` pointer moves one song at a time. The `fast` pointer moves two songs at a time.

`Case 1`: If the playlist has no loop, your `fast` pointer will become `nullptr` in which case your function can return `-1`.  

`Case 2`: If there is a loop, at some point, your `fast` and `slow` pointers will point to the same song.

Let us simulate the algorithm on the example above.

* Step 1: `fast`->Despacito ; `slow`->Despacito (both pointers start at the first song)
* Step 2: `fast`->Mockingbird ; `slow`->Get Lucky (notice how we the fast pointer moved two songs in the same step)
* Step 3: `fast`->Hey Jude ; `slow`->Mockingbird
* Step 4: `fast`->Levitating ; `slow`->Yellow
* Step 5: `fast`->Yellow ; `slow`->Hey Jude
* Step 6: `fast`->Sugar ; `slow`->Sugar

We can see that the `fast` pointer has looped through the playlist twice as fast and is able to catch up to the `slow` pointer (from behind).

###### *Algorithm: To find the length of the loop*
As soon as we find out that the 2 pointers met, we can stop traversing `fast` keeping it at the same song, and traverse `slow` one song at a time until it meets `fast` again. We can keep a counter during this process and get the loop length.


> ***When writing the code for functions below this point, assume that there will be no loop in the playlist.***

### `void removeSongs(int start, int end)`
➔ This function removes all the songs in the inclusive range [`start`, `end`]. The songs in the playlist are numbered 1, 2, 3 ... starting from the `head`. 
> Note: the playlist uses one-based indexing, i.e., the first song is numbered 1 and not 0.

Check for the below conditions **in the same order** and print the given messages when the conditions are satisfied.

* (a) If the playlist is empty (when the head is `nullptr`), then `cout << "Playlist is Empty" << endl;` and return. 
* (b) If `start` is less than 1 OR `end` is greater than the length of the linked list OR `start` is greater than `end`, then use `cout << "Invalid start or end values" << endl;` and return.
* (c) If the above two conditions are not true, it means, we have a valid case for removing. Traverse the playlist and remove all songs that lie within the deletion window. An example is shown below.

> Note: Merely reassigning the pointers will not pass the tests. Ensure you actually **free the memory using the `delete` keyword for all such songs.**

![Alt text](images/removeSongs.png?raw=true "Playlist remove songs")

### `void mergeTwoPlaylists(Song* headOne, Song* headTwo)`
➔ This function interweaves (i.e. merges) the songs from two playlists _alternately_ starting with the first node in `headOne`. Finally, the `head` pointer of your playlist (which can be accessed by the variable `this->head`) should point to the resultant merged playlists from `headOne` and `headTwo`. 

An example is shown below:

![Alt text](images/LinkedListsMerge.png?raw=true "LinkedList merge")

You need to explicitly handle the following cases.
* Case 1: One playlist is smaller than the other
If `headOne` is `1➔2➔3➔4➔nullptr` and `headTwo` is `10➔20➔nullptr` then the resultant playlist will look like `1➔10➔2➔20➔3➔4➔nullptr`. 
* Case 2: If either of `headOne` or `headTwo` is a `nullptr`, the resultant playlist would just be the non-null playlist which can directly be assigned to `head`.

> Note: You are not allowed to create new nodes and simply copy the data. You are supposed to manipulate the next pointers of the given nodes. 

----

## Custom Debugging

The main file in this assignment is not being tested. Feel free to skip this section, if you do not want to perform any custom debugging. main.cpp is already complete and allows you to perform the following operations using custom input files.

```
+=====Main Menu=========+
 1. Produce loop and find loop length in the playlist 
 2. Remove part of music playlist 
 3. Merge music playlists 
+-----------------------+
```
You may execute any custom file (named custom.txt) using `./run_app custom.txt`

### Option 1: Testing findLoopInPlaylist()
`find_loop.txt` is an example of how to test the find loop function. `expected_find_loop.txt` is what the output looks after executing `./run_app ../app/find_loop.txt`

The following lines describes your input file when testing findLoopInPlaylist()
* First line indicates the menu option. For findLoopInPlaylist() it will be 1.
* Second line indicates the number of songs you want in your playlist. For `find_loop.txt`, it is 5.
* The next 5 lines (or the number of songs you input in the second line), will be used for adding songs to a playlist.
* Each song is in the following format: `Song;Artist;1` (1 at the end means the song is liked, 0 would mean it is not)
> Note: The song, artists and liked boolean are semicolon (;) separated.
* The final line, indicates which index your loop should be added. For `find_loop.txt`, we want a loop at 2nd song. (1 indexed or first song has index 1)

> Once the input is complete, the main executes the findLoop function and displays the returned loop length. You may find the same in `expected_find_loop.txt` which shows a loop length of 4.

### Option 2: Testing removeSongs()
`remove_node.txt` is an example of how to test the remove songs function. `expected_remove_node.txt` is what the output looks after executing `./run_app ../app/remove_node.txt`


The following lines describe the `remove_node.txt` file used for testing removeSongs() function.
* First line indicates the menu option. For removeSongs() it will be 2.
* Second line indicates the number of songs you want in your playlist. For `remove_node.txt`, it is 5.
* The next 5 lines (or the number of songs you input in the second line), will be used for adding songs to a playlist.
* Each song is in the following format: `Song;Artist;1` (1 at the end means the song is liked, 0 would mean it is not)
> Note: The song, artists and liked boolean are semicolon (;) separated.
* The final line 2 lines indicate the range of songs to remove. For `remove_node`, we remove songs from index-2 to index-4

> Once the input is complete, the main executes the removeSongs function and displays the updated playlist.

### Option 3: Testing mergePlaylist()
`merge_playlist.txt` is an example of how to test the merge playlist function. `expected_merge_playlist.txt` is what the output looks after executing `./run_app ../app/merge_playlist.txt`

The following points describe the `merge_playlist.txt` file used for testing mergePlaylist() function.
* First line indicates the menu option. For mergePlaylist() it will be 3.
* Second line indicates the number of songs you want in your *first playlist*. For `merge_playlist.txt`, it is 2.
* The next 2 lines (or the number of songs you input in the second line), will be used for adding songs to the first playlist.
* Each song is in the following format: `Song;Artist;1` (1 at the end means the song is liked, 0 would mean it is not)
> Note: The song, artists and liked boolean are semicolon (;) separated.
* After the songs are added to the first playlist, the next line indicates the number of songs in the second playlist. For `merge_playlist.txt`, it is 3 songs.
* In the next 3 lines(or number of songs in indicated by you for the second playlist), we take input of the 3 songs in the same format as above.

> Once the input is complete, the main executes the mergePlaylist function and displays the merged playlist.

## Appendix
This section contains the functions of HW-3. These functions are already complete but the implementation has been abstracted. Feel free to use these functions for HW-4.

`bool isEmpty()`
➔ Return true if the head is nullptr, false otherwise.

`void displaySong()`
➔ Print name, artists, and whether or not the song is liked. Follow the below example.
```
[ Hotline Bling, Drake, </3 ]
```

> Note: This song is not part of MusicPlaylist class but the Song class, so can only be used with a song.

`void displayPlaylist()`
➔ Print the names of each song in the playlist and whether or not it is liked. Below is an example of the output using the default setup. 

```
Displaying songs
==================
[ Hotline Bling, Drake, </3 ] -> [ God's Plan, Drake, <3 ] -> NULL
==================
```

`void addSong ( Song* previousSong, Song* newSong )`
➔ Insert a new song with the properties of `newSong` struct in the playlist as the song played by the playlist after `previousSong`.  
1. If `previousSong` is nullptr, the new song is added to the beginning (head) of the list. 
2. If the `previousSong` is not a nullptr, new song is added after the previousSong.

`Song* searchSongByName( std::string name )`
➔ Searches the `MusicPlaylist` for the specified song by the `name` provided as input and return a pointer to that node. Returns `nullptr` if it is not found.

`void likeSong( std::string name )` ➔ Search for the song with `name` and then flips the liked boolean (true becomes false, false becomes true). 

If the song is found, prints the below message: 
`cout << "Song: " << current->songName << " liked!" << endl;`

If song is not found, `cout << "Song not found." << endl;`

`void displayAllSongsByArtist std::string name )`
➔ Finds all songs with artistName = name. Calls displaySong on each one, putting each song on a new line.
If no songs are found by the artist prints `"No songs found."`

