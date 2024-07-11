#include <iostream>
#include <string>
#include <map>
#include <vector>

using namespace std;

// Room structure
struct Room {
    string description;
    map<string, Room*> exits;
    vector<string> items;
};

// Function to create and connect rooms
void createRooms(Room &startRoom, Room &exitRoom) {
    Room room1, room2, room3, room4;

    room1.description = "You are in a small, dimly lit room.";
    room1.items.push_back("Key");

    room2.description = "You are in a large hall with a high ceiling.";
    room2.items.push_back("Torch");

    room3.description = "You are in a narrow corridor. You see light at the end.";
    room3.items.push_back("Map");

    room4.description = "You are in a room with an exit door.";

    room1.exits["north"] = &room2;
    room2.exits["south"] = &room1;
    room2.exits["east"] = &room3;
    room3.exits["west"] = &room2;
    room3.exits["north"] = &room4;
    room4.exits["south"] = &room3;

    startRoom = room1;
    exitRoom = room4;
}

// Function to display the room's description and items
void displayRoom(const Room &room) {
    cout << room.description << endl;
    if (!room.items.empty()) {
        cout << "You see: ";
        for (const string &item : room.items) {
            cout << item << " ";
        }
        cout << endl;
    }
}

// Main game function
void playGame() {
    Room startRoom, exitRoom, *currentRoom;
    createRooms(startRoom, exitRoom);
    currentRoom = &startRoom;

    vector<string> inventory;
    string command;

    cout << "Welcome to the Text Adventure Game!" << endl;

    while (true) {
        displayRoom(*currentRoom);
        cout << "What do you want to do? (move <direction>, take <item>, inventory, exit): ";
        getline(cin, command);

        if (command.find("move") == 0) {
            string direction = command.substr(5);
            if (currentRoom->exits.find(direction) != currentRoom->exits.end()) {
                currentRoom = currentRoom->exits[direction];
                if (currentRoom == &exitRoom) {
                    cout << "Congratulations! You found the exit!" << endl;
                    break;
                }
            } else {
                cout << "You can't go that way." << endl;
            }
        } else if (command.find("take") == 0) {
            string item = command.substr(5);
            auto it = find(currentRoom->items.begin(), currentRoom->items.end(), item);
            if (it != currentRoom->items.end()) {
                inventory.push_back(item);
                currentRoom->items.erase(it);
                cout << "You took the " << item << "." << endl;
            } else {
                cout << "There is no " << item << " here." << endl;
            }
        } else if (command == "inventory") {
            cout << "You have: ";
            for (const string &item : inventory) {
                cout << item << " ";
            }
            cout << endl;
        } else if (command == "exit") {
            cout << "Thanks for playing!" << endl;
            break;
        } else {
            cout << "I don't understand that command." << endl;
        }
    }
}

int main() {
    playGame();
    return 0;
}
