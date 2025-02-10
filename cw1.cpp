// Enhanced Watch and SmartWatch Program with Optional Features
// Author: Abhinay (BCA)
// Program Version: 2.2

#include <iostream>         // For input and output streams
#include <vector>           // For dynamic storage of watches
#include <string>           // For string datatype
#include <ctime>            // For current time functions
#include <thread>           // For sleep functionality
#include <chrono>           // For sleep duration
#include <limits>           // For input validation
#include <windows.h>        // For Sleep function
#include <memory>           // For smart pointers
#include <iomanip>          // For formatted output

// Using ANSI escape codes for colored output (works on most Unix terminals and Windows 10/11 with proper settings)
#define RESET   "\033[0m"
#define RED     "\033[31m"      
#define GREEN   "\033[32m"      
#define YELLOW  "\033[33m"      
#define BLUE    "\033[34m"      
#define MAGENTA "\033[35m"      
#define CYAN    "\033[36m"      
#define WHITE   "\033[37m"      

using namespace std;

// Function to print strings with a delay
void printWithDelay(const string& str, int delay_ms = 10) {
    for (char ch : str) {
        cout << ch;
        Sleep(delay_ms);
    }
    cout << endl;
}

// Base Class: Watch
class Watch {
protected:
    // Attributes
    string brand;
    float price;
    int weight;          // in grams
    string color;
    string dialColor;

public:
    // Constructor
    Watch(string brand, float price, int weight, string color, string dialColor)
        : brand(brand), price(price), weight(weight), color(color), dialColor(dialColor) {}

    // Virtual Destructor
    virtual ~Watch() {}

    // Getters
    string getBrand() const { 
        return brand; 
    }
    float getPrice() const { 
        return price; 
    }
    int getWeight() const { 
        return weight; 
    }
    string getColor() const { 
        return color; 
    }
    string getDialColor() const { 
        return dialColor; 
    }

    // Setters
    void setBrand(const string& newBrand) { 
        brand = newBrand; 
    }
    void setPrice(float newPrice) { 
        price = newPrice; 
    }
    void setWeight(int newWeight) { 
        weight = newWeight;
    }
    void setColor(const string& newColor) { 
        color = newColor; 
    }
    void setDialColor(const string& newDialColor) { 
        dialColor = newDialColor; 
    }

    // Function to display current local time
    void showTime() const {
        time_t current_time = time(nullptr);
        tm* local_time = localtime(&current_time);
        string timeStr = "Current local time: " + string(asctime(local_time));
        printWithDelay(timeStr);
    }

    // Virtual function to display details
    virtual void showDetails() const {
        cout << YELLOW << "----- Watch Details -----" << RESET << endl;
        printWithDelay("Brand            : " + brand);
        printWithDelay("Price            : $" + to_string(price));
        printWithDelay("Weight(in grams) : " + to_string(weight));
        printWithDelay("Color            : " + color);
        printWithDelay("Dial Color       : " + dialColor);
    }

    // Virtual function to identify type
    virtual string getType() const { return "Watch"; }
};

// Derived Class: SmartWatch
class SmartWatch : public Watch {
private:
    int batteryBackup;      // in hours
    short resolutionX;
    short resolutionY;
    int batteryPercentage;  // dynamic battery percentage

public:
    // Constructor
    SmartWatch(string brand, float price, int weight, string color, string dialColor,
               int batteryBackup, short resX, short resY)
        : Watch(brand, price, weight, color, dialColor),
          batteryBackup(batteryBackup), resolutionX(resX), resolutionY(resY), batteryPercentage(100) {}

    // Getters
    int getBatteryBackup() const { 
        return batteryBackup; 
    }
    short getResolutionX() const { 
        return resolutionX; 
    }
    short getResolutionY() const { 
        return resolutionY; 
    }
    int getBatteryPercentage() const { 
        return batteryPercentage; 
    }

    // Setters
    void setBatteryBackup(int newBatteryBackup) { 
        batteryBackup = newBatteryBackup; 
    }
    void setResolution(short newResX, short newResY) { 
        resolutionX = newResX; resolutionY = newResY; 
    }

    // Function to show battery percentage (dynamic)
    int showBatPer() {
        // For demonstration, decrease battery by 5% each call until 0%, then reset to 100%
        batteryPercentage -= 5;
        if (batteryPercentage < 0)
            batteryPercentage = 100;
        return batteryPercentage;
    }

    // Function to show resolution
    void showResolution() const {
        printWithDelay("Resolution  : " + to_string(resolutionX) + "x" + to_string(resolutionY));
    }

    // Overridden function to display details
    void showDetails() const override {
        cout << CYAN << "----- SmartWatch Details -----" << RESET << endl;
        printWithDelay("Type            : " + getType());
        printWithDelay("Brand           : " + brand);
        printWithDelay("Price           : $" + to_string(price));
        printWithDelay("Weight          : " + to_string(weight) + " grams");
        printWithDelay("Color           : " + color);
        printWithDelay("Dial Color      : " + dialColor);
        printWithDelay("Battery Backup  : " + to_string(batteryBackup) + " hours");
        printWithDelay("Battery Percentage: " + to_string(batteryPercentage) + "%");
        showResolution();
    }

    // Function to identify type
    string getType() const override { 
        return "SmartWatch"; 
    }
};

// Function to greet the user
void greet() {
    cout << GREEN;
    printWithDelay("===========================================", 10);
    printWithDelay("      Welcome to the Watch Program         ", 10);
    printWithDelay("===========================================", 10);
    cout << RESET << endl;
}

// Function to say goodbye to the user
void bye() {
    cout << MAGENTA;
    printWithDelay("------------------------------------------------", 10);
    printWithDelay("Program was Developed by Abhinay (BCA)", 10);
    printWithDelay("------------------------------------------------", 10);
    cout << RESET << endl;
}

// Function to display the menu
void showMenu() {
    cout << BLUE;
    printWithDelay("\n<--------- Watch Menu --------->", 10);
    printWithDelay("1. Show Current Time", 10);
    printWithDelay("2. Show All Watch Details", 10);
    printWithDelay("3. Show SmartWatch Battery Percentage", 10);
    printWithDelay("4. Show SmartWatch Resolution", 10);
    printWithDelay("5. Add a New Watch", 10);
    printWithDelay("6. Add a New SmartWatch", 10);
    printWithDelay("7. Remove a Watch", 10);
    printWithDelay("8. Update a Watch", 10);
    printWithDelay("9. Show All Watches Summary", 10);
    printWithDelay("0. Exit", 10);
    cout << RESET;
}

// Function to display all watches with indices
void listAllWatches(const vector<unique_ptr<Watch>>& watches) {
    if (watches.empty()) {
        cout << RED << "No watches available." << RESET << endl;
        return;
    }

    cout << YELLOW << "\n----- List of Watches -----" << RESET << endl;
    for (size_t i = 0; i < watches.size(); ++i) {
        cout << "[" << i + 1 << "] " << watches[i]->getBrand() << " (" << watches[i]->getType() << ")" << endl;
    }
}

// Function to add a new Watch
void addWatch(vector<unique_ptr<Watch>>& watches) {
    string brand, color, dialColor;
    float price;
    int weight;

    cout << "\nEnter details for the new Watch:" << endl;
    cout << "Brand: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear input buffer
    getline(cin, brand);
    cout << "Price: $";
    while (!(cin >> price) || price < 0) {
        cin.clear(); // Clear the error flag
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore invalid input
        cout << RED << "Invalid input. Please enter a positive number for price: " << RESET;
    }
    cout << "Weight (in grams): ";
    while (!(cin >> weight) || weight <= 0) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << RED << "Invalid input. Please enter a positive integer for weight: " << RESET;
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear input buffer
    cout << "Color: ";
    getline(cin, color);
    cout << "Dial Color: ";
    getline(cin, dialColor);

    watches.push_back(make_unique<Watch>(brand, price, weight, color, dialColor));
    cout << GREEN << "Watch added successfully!" << RESET << endl;
}

// Function to add a new SmartWatch
void addSmartWatch(vector<unique_ptr<Watch>>& watches) {
    string brand, color, dialColor;
    float price;
    int weight, batteryBackup;
    short resX, resY;

    cout << "\nEnter details for the new SmartWatch:" << endl;
    cout << "Brand: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear input buffer
    getline(cin, brand);
    cout << "Price: $";
    while (!(cin >> price) || price < 0) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << RED << "Invalid input. Please enter a positive number for price: " << RESET;
    }
    cout << "Weight (in grams): ";
    while (!(cin >> weight) || weight <= 0) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << RED << "Invalid input. Please enter a positive integer for weight: " << RESET;
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear input buffer
    cout << "Color: ";
    getline(cin, color);
    cout << "Dial Color: ";
    getline(cin, dialColor);
    cout << "Battery Backup (in hours): ";
    while (!(cin >> batteryBackup) || batteryBackup <= 0) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << RED << "Invalid input. Please enter a positive integer for battery backup: " << RESET;
    }
    cout << "Resolution X: ";
    while (!(cin >> resX) || resX <= 0) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << RED << "Invalid input. Please enter a positive integer for Resolution X: " << RESET;
    }
    cout << "Resolution Y: ";
    while (!(cin >> resY) || resY <= 0) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << RED << "Invalid input. Please enter a positive integer for Resolution Y: " << RESET;
    }

    watches.push_back(make_unique<SmartWatch>(brand, price, weight, color, dialColor, batteryBackup, resX, resY));
    cout << GREEN << "SmartWatch added successfully!" << RESET << endl;
}

// Function to remove a Watch
void removeWatch(vector<unique_ptr<Watch>>& watches) {
    if (watches.empty()) {
        cout << RED << "No watches to remove." << RESET << endl;
        return;
    }

    listAllWatches(watches);
    int index;
    cout << "\nEnter the number of the watch to remove: ";
    while (!(cin >> index) || index < 1 || index > static_cast<int>(watches.size())) {
        cin.clear(); // Clear the error flag
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore invalid input
        cout << RED << "Invalid selection. Please enter a number between 1 and " << watches.size() << ": " << RESET;
    }

    // Remove the selected watch
    watches.erase(watches.begin() + (index - 1));
    cout << GREEN << "Watch removed successfully!" << RESET << endl;
}

// Function to update a Watch
void updateWatch(vector<unique_ptr<Watch>>& watches) {
    if (watches.empty()) {
        cout << RED << "No watches to update." << RESET << endl;
        return;
    }

    listAllWatches(watches);
    int index;
    cout << "\nEnter the number of the watch to update: ";
    while (!(cin >> index) || index < 1 || index > static_cast<int>(watches.size())) {
        cin.clear(); // Clear the error flag
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore invalid input
        cout << RED << "Invalid selection. Please enter a number between 1 and " << watches.size() << ": " << RESET;
    }

    Watch* selectedWatch = watches[index - 1].get();

    string newBrand, newColor, newDialColor;
    string priceInput, weightInput;

    cout << "\nEnter new details (leave blank to keep current value):" << endl;

    // Update Brand
    cout << "Current Brand: " << selectedWatch->getBrand() << "\nNew Brand: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear input buffer
    getline(cin, newBrand);
    if (!newBrand.empty()) {
        selectedWatch->setBrand(newBrand);
    }

    // Update Price
    cout << "Current Price: $" << selectedWatch->getPrice() << "\nNew Price: $";
    getline(cin, priceInput);
    if (!priceInput.empty()) {
        try {
            float newPrice = stof(priceInput);
            if (newPrice >= 0) {
                selectedWatch->setPrice(newPrice);
            } else {
                cout << RED << "Price cannot be negative. Skipping price update." << RESET << endl;
            }
        } catch (...) {
            cout << RED << "Invalid price input. Skipping price update." << RESET << endl;
        }
    }

    // Update Weight
    cout << "Current Weight: " << selectedWatch->getWeight() << " grams\nNew Weight: ";
    getline(cin, weightInput);
    if (!weightInput.empty()) {
        try {
            int newWeight = stoi(weightInput);
            if (newWeight > 0) {
                selectedWatch->setWeight(newWeight);
            } else {
                cout << RED << "Weight must be positive. Skipping weight update." << RESET << endl;
            }
        } catch (...) {
            cout << RED << "Invalid weight input. Skipping weight update." << RESET << endl;
        }
    }

    // Update Color
    cout << "Current Color: " << selectedWatch->getColor() << "\nNew Color: ";
    getline(cin, newColor);
    if (!newColor.empty()) {
        selectedWatch->setColor(newColor);
    }

    // Update Dial Color
    cout << "Current Dial Color: " << selectedWatch->getDialColor() << "\nNew Dial Color: ";
    getline(cin, newDialColor);
    if (!newDialColor.empty()) {
        selectedWatch->setDialColor(newDialColor);
    }

    // If SmartWatch, allow updating additional attributes
    SmartWatch* smartWatchPtr = dynamic_cast<SmartWatch*>(selectedWatch);
    if (smartWatchPtr) {
        string batteryInput, resXInput, resYInput;

        // Update Battery Backup
        cout << "Current Battery Backup: " << smartWatchPtr->getBatteryBackup() << " hours\nNew Battery Backup: ";
        getline(cin, batteryInput);
        if (!batteryInput.empty()) {
            try {
                int newBatteryBackup = stoi(batteryInput);
                if (newBatteryBackup > 0) {
                    smartWatchPtr->setBatteryBackup(newBatteryBackup);
                } else {
                    cout << RED << "Battery backup must be positive. Skipping update." << RESET << endl;
                }
            } catch (...) {
                cout << RED << "Invalid battery backup input. Skipping update." << RESET << endl;
            }
        }

        // Update Resolution X
        cout << "Current Resolution: " << smartWatchPtr->getResolutionX() << "x" << smartWatchPtr->getResolutionY() << "\nNew Resolution X: ";
        getline(cin, resXInput);
        short newResX = smartWatchPtr->getResolutionX();
        if (!resXInput.empty()) {
            try {
                int temp = stoi(resXInput);
                if (temp > 0 && temp < 10000) { // Arbitrary upper limit
                    newResX = static_cast<short>(temp);
                } else {
                    cout << RED << "Resolution X must be positive and reasonable. Skipping update." << RESET << endl;
                }
            } catch (...) {
                cout << RED << "Invalid Resolution X input. Skipping update." << RESET << endl;
            }
        }

        // Update Resolution Y
        cout << "New Resolution Y: ";
        getline(cin, resYInput);
        short newResY = smartWatchPtr->getResolutionY();
        if (!resYInput.empty()) {
            try {
                int temp = stoi(resYInput);
                if (temp > 0 && temp < 10000) { // Arbitrary upper limit
                    newResY = static_cast<short>(temp);
                } else {
                    cout << RED << "Resolution Y must be positive and reasonable. Skipping update." << RESET << endl;
                }
            } catch (...) {
                cout << RED << "Invalid Resolution Y input. Skipping update." << RESET << endl;
            }
        }

        smartWatchPtr->setResolution(newResX, newResY);
    }

    cout << GREEN << "Watch updated successfully!" << RESET << endl;
}

// Function to show SmartWatch Battery Percentages
void showSmartWatchBattery(const vector<unique_ptr<Watch>>& watches) {
    bool found = false;
    for (const auto& watch : watches) {
        SmartWatch* smartWatchPtr = dynamic_cast<SmartWatch*>(watch.get());
        if (smartWatchPtr) {
            found = true;
            cout << CYAN << "SmartWatch: " << smartWatchPtr->getBrand() << RESET << endl;
            cout << "Battery Percentage: " << smartWatchPtr->showBatPer() << "%" << endl;
        }
    }
    if (!found) {
        cout << RED << "No SmartWatches available." << RESET << endl;
    }
}

// Function to show SmartWatch Resolutions
void showSmartWatchResolution(const vector<unique_ptr<Watch>>& watches) {
    bool found = false;
    for (const auto& watch : watches) {
        SmartWatch* smartWatchPtr = dynamic_cast<SmartWatch*>(watch.get());
        if (smartWatchPtr) {
            found = true;
            cout << CYAN << "SmartWatch: " << smartWatchPtr->getBrand() << RESET << endl;
            smartWatchPtr->showResolution();
        }
    }
    if (!found) {
        cout << RED << "No SmartWatches available." << RESET << endl;
    }
}

// Function to display all watch details
void showAllWatchDetails(const vector<unique_ptr<Watch>>& watches) {
    if (watches.empty()) {
        cout << RED << "No watches available to display." << RESET << endl;
        return;
    }

    for (const auto& watch : watches) {
        watch->showDetails();
        cout << endl;
    }
}

// Function to show a summary of all watches
void showAllWatchesSummary(const vector<unique_ptr<Watch>>& watches) {
    if (watches.empty()) {
        cout << RED << "No watches available." << RESET << endl;
        return;
    }

    cout << YELLOW << "\n----- Watches Summary -----" << RESET << endl;
    for (size_t i = 0; i < watches.size(); ++i) {
        Sleep(500);
        cout << "[" << i + 1 << "] " << watches[i]->getBrand() << " (" << watches[i]->getType() << ")" << endl;
        Sleep(500);
    }
}

// Main Function
int main() {

    system("cls"); // Clear screen (Windows-specific)

    // Greeting the user
    greet();

    // Vector to store Watch and SmartWatch objects using smart pointers for automatic memory management
    vector<unique_ptr<Watch>> watches;

    // Adding initial Watches
    watches.push_back(make_unique<Watch>("Rolex", 20000.0f, 200, "Chrome", "Green Dial"));
    watches.push_back(make_unique<Watch>("Patek", 50000.0f, 150, "Chrome", "Green Dial"));
    watches.push_back(make_unique<Watch>("Timex", 10000.0f, 90, "Chrome", "Green Dial"));
    watches.push_back(make_unique<Watch>("Casio", 2000.0f, 120, "Chrome", "Green Dial"));
    watches.push_back(make_unique<Watch>("Titan", 5000.0f, 100, "Chrome", "Green Dial"));

    // Adding initial SmartWatches
    watches.push_back(make_unique<SmartWatch>("Apple", 25000.0f, 150, "Black", "Black Dial", 18, 320, 320));
    watches.push_back(make_unique<SmartWatch>("Samsung", 20000.0f, 150, "Black", "Black Dial", 18, 320, 320));

    int choice;
    bool exitMenu = false;

    // Menu Loop
    while (!exitMenu) {
        showMenu();
        cout << "\nEnter your choice: ";
        cin >> choice;

        // Input validation
        if (cin.fail()) {
            cin.clear(); // Clear the error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore invalid input
            cout << RED << "Invalid input. Please enter a number corresponding to the menu options." << RESET << endl;
            continue;
        }

        switch (choice) {
            case 1:
                // Show Current Time
                cout << "\n";
                printWithDelay("Displaying Current Local Time:", 10);
                // Show time using the first watch (arbitrary choice)
                if (!watches.empty()) {
                    watches[0]->showTime();
                } else {
                    cout << RED << "No watches available to show time." << RESET << endl;
                }
                break;

            case 2:
                // Show All Watch Details
                showAllWatchDetails(watches);
                break;

            case 3:
                // Show SmartWatch Battery Percentage
                showSmartWatchBattery(watches);
                break;

            case 4:
                // Show SmartWatch Resolution
                showSmartWatchResolution(watches);
                break;

            case 5:
                // Add a New Watch
                addWatch(watches);
                break;

            case 6:
                // Add a New SmartWatch
                addSmartWatch(watches);
                break;

            case 7:
                // Remove a Watch
                removeWatch(watches);
                break;

            case 8:
                // Update a Watch
                updateWatch(watches);
                break;

            case 9:
                // Show All Watches Summary
                showAllWatchesSummary(watches);
                break;

            case 0:
                // Exit
                exitMenu = true;
                Sleep(700);
                cout << YELLOW << "\nExiting menu..." << RESET << endl;
                // Countdown before exiting
                for (int i = 3; i > 0; --i) {
                    cout << YELLOW << i << RESET << endl;
                    Sleep(700);
                }
                cout << GREEN << "Boom!" << RESET << endl;
                cout << endl;
                bye();
                break;

            default:
                cout << RED << "Invalid Choice. Please try again!" << RESET << endl;
        }
    }

    // Program ends here. Smart pointers automatically clean up.
    return 0;
}