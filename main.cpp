#include <iostream>
#include "PlayList.h"
#include "Song.h"

using std::cout;
using std::endl;
using std::cin;
using std::getline;
using std::string;

/* Big O Notation

PlayList Methods:

1. Default constructor- O(1):
    - We only need to initialize numSongs = 0 and head = NULL and both operations are constant time

2. Destructor- O(N) where N = number of nodes in list:
    - Iterate through each node in list and start deleting from head to tail
    - Iterating through each node for deletion takes lenth of list operations so we let N = length of list

3. Copy Constructor- O(N) where N = number of nodes in list:
    - We are copying every node to a newly create list so we have to iterate
      through every node and copy it over so it takes O(N) where N is the number of
      nodes in the list

4. Overloaded Assignment Operator- O(N) where N = number of nodes in list:
    - We are calling the copy constructor in the overloaded assignment operator
      so it has the same running time as the copy constructor

5. Insert- O(N) where N = number of nodes in list:
    - Iterating until position and if position is the last index, then it will iterate the
      entire list, thus having an O(N) running time as worse case scenario
    - All other operations beside the while loop iteration is constant time so does not affect running time

6. Remove- O(N) where N = number of nodes in list:
    - Iterating until position and if position is the last index, then it will iterate the
      entire list, thus having an O(N) running time as worse case scenario
    - All other operations beside the while loop iteration is constant time so does not affect running time

7. Get- O(N) where N = number of nodes in list:
    - Iterating until position and if position is the last index, then it will iterate the
      entire list, thus having an O(N) running time as worse case scenario 
    - All other operations beside the while loop iteration is constant time so does not affect running time

8. Swap- O(N) where N = number of nodes in list:
    - We use two while loops and in the worse-case, it will iterate through the entire list thus
      having a running time oftry{
         O(2N) and that simplifies to O(N)
    - All other operations beside the while loop iteration is constant time so does not affect running time

9. Size -O(1)
    - Just returns numSongs which is already stored as a private member in the playlist class
    - No loops or anything so just O(1)

Main Function Commands:

1. Enter a song- O(N) where N = number of nodes in list:
    - Everything in "enter a song" (option 1) is constant time besides calling the insert
      function.
    - The while loops are for invalid user input so it should not matter 
    - The insert function's worse-case scenario is O(N) as it has to iterate through entire
      list so "Enter a song" command would just be O(N) 

2. Remove a song- O(N) where N = number of nodes in list:
    - Everything in "remove a song" (option 2) is constant time except calling the remove function
    - The remove function is O(N) because worse case scenario, it has to iterate through every node 
    - The while loops are for invalid user input so it should not matter 

3. Swap two songs- O(N) Where N = number of nodes in list:
    - Everything in "swap two songs" (option 3) is constant time except the swap function call
    - The swap fucntion call takes O(N) because worse case secnario, it has to iterate through every node
    - The while loops are for invalid user input so it should not matter 

4. Print all songs- O(N)- where N = number of nodes in list;
    - We iterate through every node and print it out
    - Iterating through list takes O(N) and printing out takes O(1) and so it takes
      O(N) running time
    - The while loops are for invalid user input so it should not matter 
*/

// g++ -Wall -std=c++11 -o x a1main.cpp PlayList.cpp Song.cpp

// Helper function for printing songs in playlist
void print(const PlayList& pl){

    for (unsigned int i=0;i < pl.size();i++){
        cout << "  " << (i+1) << ". " << pl.get(i).getName() << " (" <<  pl.get(i).getArtist() << ") " << pl.get(i).getLength() << "s" << endl;
    }
    cout << "There are " << pl.size() << " songs in the play list." << endl << endl;
}

int main(){

    // Interface 
    cout << "Menu:" << endl;
    cout << "1 - Enter a song in the play list at a given position" << endl;
    cout << "2 - Remove a song form the play list at a given position" << endl;
    cout << "3 - Swap two songs in the play list" << endl;
    cout << "4 - Print all the songs in the play list" << endl;
    cout << "5 - Quit" << endl << endl; 

    PlayList pl;

    while (true){

        string option;
        
        // Get user input
        cout << "Enter 1 (insert), 2 (remove), 3 (swap), 4 (print) or 5 (quit): ";
        cin >> option;

        cin.ignore();

        string name;
        string artist;
        unsigned len, pos;
       
        // Insert
        if (option == "1"){

            // Print interface
            cout << "Song name: ";
            getline(cin,name);

            cout << "Artist: ";
            getline(cin,artist);
            
            cout << "Length: ";
            cin >> len;

            // If user does not input a valid length
            while (cin.fail()){
                cin.clear();
                cin.ignore(100,'\n');
                cout << "Please enter a valid length: ";
                cin >> len;
            }

            // Cases for if playlist is empty and not empty
            if (pl.size()  == 0) {
                cout << "Position (1) (numbers out of range are treated as last index): ";
                cin >> pos;

                // If user does not input a valid number
                while (cin.fail() || pos != 1){
                    cin.clear();
                    cin.ignore(100,'\n');
                    cout << "Please enter a valid position (1): ";
                    cin >> pos;
                }
            }

            else {
                cout << "Position (1 to " << (pl.size()+1) << "): ";
                cin >> pos;
                
                while (cin.fail() || pos > pl.size()+1 || pos < 0){
                    cin.clear();
                    cin.ignore(100,'\n');
                    cout << "Please enter valid position (1 to " << (pl.size()+1) << "): ";
                    cin >> pos;
                }
                 
            }

            cout << "You entered " << name << " at position " << pos << " in the play list" << endl;

            // Insert song into playlist
            pos -=1;
            Song song(name,artist,len);
            pl.insert(song,pos);     
            cout << endl;
        }

        // Remove 
        else if (option == "2"){
            
            // Edge case: If no songs in playlist
            if (pl.size() == 0){
                cout << "Please enter some songs first" << endl;
            }

            else{
                // Consider which position to output
                if (pl.size()  <= 1) {
                    cout << "Position (1): ";
                    cin >> pos;

                    // If user does not input a valid number
                    while (cin.fail() || pos != 1){
                        cin.clear();
                        cin.ignore(100,'\n');
                        cout << "Please enter a valid position (1): ";
                        cin >> pos;
                    }
                }
                else {
                    cout << "Position (1 to " << pl.size() << "): ";
                    cin >>pos; 

                    // If user does not input a valid number
                    while (cin.fail() || pos > pl.size() || pos < 0){
                        cin.clear();
                        cin.ignore(100,'\n');
                        cout << "Please enter valid position (1 to " << (pl.size()) << "): ";
                        cin >> pos;
                    }
                }


                // Remove song from playlist
                pos -=1;
                string ret = pl.get(pos).getName();
                pl.remove(pos);
                cout << "You removed " << ret << " from the play list" << endl << endl;
            }
        }

        // Swap
        else if (option == "3"){
            // Edge case: If less than 2 songs
            if (pl.size() <= 1){
                cout << "Please enter at least 2 songs first" << endl;
            }
            else{
                
                // Get input for 2 positions
                unsigned pos1, pos2;

                cout << "Swap song at position (1 to " << pl.size() << "): ";
                cin >> pos1;

                // If user does not input a valid number
                while (cin.fail() || pos1 > pl.size()){
                    cin.clear();
                    cin.ignore(100,'\n');
                    cout << "Please enter valid position for first song (1 to " << pl.size() << "): ";
                    cin >> pos1;
                }

                cout << "with the song at position (1 to " << pl.size() << "): ";
                cin >> pos2;

                // If user does not input a valid number
                while (cin.fail() || pos1 == pos2 || pos2 > pl.size()){
                    cin.clear();
                    cin.ignore(100,'\n');
                    cout << "Please enter valid position for second song (1 to " << pl.size() << "): ";
                    cin >> pos2;
                }

                cout << "You swapped the songs at positions " << pos1 << " and " << pos2 << endl << endl; 
                
                // Swap positions
                pl.swap( (pos1-=1) , (pos2-=1) );
            }
        }

        // Print 
        else if (option == "4"){
            // Call print helper function
            print(pl);
        }
        
        // Quit
        else if (option == "5"){
            cout << "You have chosen to quit the program." << endl << endl;
            break;
        }

        // Edge case: If input is not valid
        else{
            cout << "Please enter a valid number" << endl;
        }
        
    }

    return 0;
}   


