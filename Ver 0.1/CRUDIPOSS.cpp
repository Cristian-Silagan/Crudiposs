#include <iostream> // Input Output Library
#include <iomanip>  // Library for Input Output Manipulation
#include <cstdio> // C Standard Input Output Library for GOTO STATEMENT
#include <vector> // STL Standard Temple Library for Data Structure (Arrays)
#include <string> // String Library for String used for .length() and .substr()
#include <fstream> // For File Writing, Reading or Saving Data
#include <ctime> // Time Library for Date and Time
#include <windows.h> // Windows Library for Sleep Function
using namespace std;

// NULL will return the value of time function
time_t timestamp = time(NULL); // The time(NULL) will return the current date and time.
// tm structure for time and date
struct tm datetime = *localtime(&timestamp); // the value of timestamp will become the value of datetime

// THE STORAGE
struct ProductRecord {
        int ID;
        string product;
        string type;
        int quantity;
        double price;
};

// LOGIC SECTION

class POSManager {
    private:
        vector <ProductRecord> product_recorder; // Dynamic Array Version of Product Record
        int idNumber;

    public:
        POSManager () : idNumber(1) {} // Every POSManager created, the idNumber will be initialized to 1



    // ====================================================================================================


        // THE ADD PRODUCT FUNCTION
        // constant string Referenced Name for Product Name | double price for Product Price | int quantity for Product Qtty
    void ADD_PRODUCT (const string& name, const string& typeOfPurchase, double price, int quantity) {
            ProductRecord record; // declare ProductRecord as 'record' and assign it to all the variables ProductRecord.
            record.ID = idNumber++; // access ID using record (.)
            record.product = name; // access product using record (.)
            record.type = typeOfPurchase;
            record.quantity = quantity;
            record.price = price; // access 'price' using record (.)
            product_recorder.push_back(record); // Adds all the contents inputted by the user using PUSH_BACK from the Vector Library through record (Struct)
        }



    // ======================================================================================================



    // THE DISPLAY PRODUCT FUNCTION
    void DISPLAY_PRODUCT() const {
            if (product_recorder.empty()) { // check if the sales vector is empty
                cout << "No products available" << endl; // display a message
                return;
            }

            char date_year[50];
            tm dateTime = *localtime(&timestamp);
            // Converts date and time into STRING
            // %m = month, %d = day, %y = year
            strftime(date_year, 50, "%m/%d/%y", &dateTime);

            cout << endl;
            cout << endl;
            cout << "\t\tID     PRODUCT NAME             TYPE         QUANTITY      PRICE      AMOUNT      DATE" << endl;
            cout << "\t\t----------------------------------------------------------------------------------------" << endl;

            for (const auto& productsDisplay : product_recorder) {
                cout << "\t\t" << setw(1) << productsDisplay.ID << " "

                // Short-hand if...else, checks if the length of the product name is greater than 27 and converts into "..." using substr function

                     << "     " << setw(25) << left << (productsDisplay.product.length() > 27 ? productsDisplay.product.substr(0, 24) + "..." : productsDisplay.product) << right << ""
                     << "" << productsDisplay.type << "   "
                     << "" << setw(9) << productsDisplay.quantity << "     "
                     << "" << setw(11) << fixed << setprecision(2) << productsDisplay.price << ""
                     << "" << setw(5) << fixed << setprecision(2) << "P" <<(productsDisplay.price * productsDisplay.quantity)
                     << "  " <<setw(5) << date_year << endl;
            }
            cout << "\t\t----------------------------------------------------------------------------------------" << endl;
        }


    // ======================================================================================================



    void UPDATE_PRODUCT(int ID, const string& new_name, const string& new_type, double new_price, int new_quantity) {
        for (auto& productsUpdate : product_recorder) { // Foreach Loop for the product_recorder
            if (productsUpdate.ID == ID) {
                productsUpdate.product = new_name;
                productsUpdate.type = new_type;
                productsUpdate.quantity = new_quantity; // Corrected this line
                productsUpdate.price = new_price;
                cout << "Product updated successfully" << endl;
                return;
            }
        }
        cout << "Product not found" << endl;
    }



    // ======================================================================================================




void DELETE_PRODUCT(int ID) {
// CHECKS THE BEGINNING OF THE STRUCT AND END OF THE STRUCT
    for (auto it = product_recorder.begin(); it != product_recorder.end(); ++it) {
        if (it->ID == ID) { // Accessing ID using IT variable
            product_recorder.erase(it); // Erase Element or Data
            cout << "Product deleted successfully" << endl;
            reassignIDs();
            idNumber = product_recorder.size() + 1; // Reset idNumber
            return;
        }
    }
    cout << "Product not found" << endl;
}

    void reassignIDs() {
            int newID = 1;
            for (auto& product : product_recorder) {
                product.ID = newID++;
            }
        }



    // ======================================================================================================



void SAVE_PRODUCTS () {
            // Open a file named "inventory.txt" for writing
            ofstream outFile("inventory.txt");

            // Check if the file was opened successfully
            if (!outFile) {
                cout << "Error opening file for saving." << endl;
                return;
            }
            char date_year[50];
            tm dateTime = *localtime(&timestamp);

            //Converting date and time into STRING
            strftime(date_year, 50, "%m/%d/%y", &dateTime); // strftime is a function that formats the date and time

     outFile << endl;
     outFile << "\t\tID     PRODUCT NAME             TYPE         QUANTITY      PRICE      AMOUNT      DATE" << endl;
     outFile << "\t\t----------------------------------------------------------------------------------------" << endl;

            for (const auto& productsDisplay : product_recorder) {
                outFile << "\t\t" << setw(1) << productsDisplay.ID << " "
                        << "     " << setw(25) << left << (productsDisplay.product.length() > 27 ? productsDisplay.product.substr(0, 24) + ".." : productsDisplay.product) << right << ""
                        << "" << productsDisplay.type << "   "
                        << "" << setw(9) << productsDisplay.quantity << "     "
                        << "" << setw(11) << fixed << setprecision(2) << productsDisplay.price << ""
                        << "" << setw(5) << fixed << setprecision(2) << "P" << (productsDisplay.price * productsDisplay.quantity)
                        << "  " << setw(5) << date_year << endl;
            }

    outFile << "\t\t----------------------------------------------------------------------------------------" << endl;
    outFile.close();
  }
};



    // ======================================================================================================



    // INTERFACE SECTION

    void printTitle (){
        cout << endl;
        cout << "\t\t\t   CREATE, READ, UPDATE, AND DELETE, INTEGRATED POINT OF SALE SYSTEM" << endl;
        cout << endl;

        // ASCII

        const char* asciiArt =
            "\t\t$$$$$$\\  $$$$$$$\\  $$\\   $$\\ $$$$$$$\\  $$$$$$\\ $$$$$$$\\   $$$$$$\\   $$$$$$\\   $$$$$$\\  \n"
            "\t\t$$  __$$\\ $$  __$$\\ $$ |  $$ |$$  __$$\\ \\_$$  _|$$  __$$\\ $$  __$$\\ $$  __$$\\ $$  __$$\\ \n"
            "\t\t$$ /  \\__|$$ |  $$ |$$ |  $$ |$$ |  $$ |  $$ |  $$ |  $$ |$$ /  $$ |$$ /  \\__|$$ /  \\__|\n"
            "\t\t$$ |      $$$$$$$  |$$ |  $$ |$$ |  $$ |  $$ |  $$$$$$$  |$$ |  $$ |\\$$$$$$\\  \\$$$$$$\\  \n"
            "\t\t$$ |      $$  __$$< $$ |  $$ |$$ |  $$ |  $$ |  $$  ____/ $$ |  $$ | \\____$$\\  \\____$$\\ \n"
            "\t\t$$ |  $$\\ $$ |  $$ |$$ |  $$ |$$ |  $$ |  $$ |  $$ |      $$ |  $$ |$$\\   $$ |$$\\   $$ |\n"
            "\t\t\\$$$$$$  |$$ |  $$ |\\$$$$$$  |$$$$$$$  |$$$$$$\\ $$ |       $$$$$$  |\\$$$$$$  |\\$$$$$$  |\n"
            "\t\t \\______/ \\__|  \\__| \\______/ \\_______/ \\______|\\__|       \\______/  \\______/  \\______|\n";

        cout << asciiArt << endl;
    }


    void printMenu(int &choice) {
        printTitle();

        char horizontal = 196;
        char vertical = 179;
        cout << setw(35);
        for (int i = 0; i < 50; i++) {
            cout << horizontal;
        }
        cout << endl;
        cout << setw(35) << vertical << "\t  1. CREATE                                " << vertical << '\n';
        cout << setw(35) << vertical << "\t  2. READ                                  " << vertical << '\n';
        cout << setw(35) << vertical << "\t  3. UPDATE                                " << vertical << '\n';
        cout << setw(35) << vertical << "\t  4. DELETE                                " << vertical << '\n';
        cout << setw(35) << vertical << "\t  5. SAVE AND EXIT                         " << vertical << '\n';
        cout << setw(35);

        for (int i = 0; i < 50; i++) {
            cout << horizontal;
        }
        cout << endl;
        cin >> choice;
    }


    // ======================================================================================================



    // POSManager& POS_SYSTEM is a reference to the POSManager object
    void addProductInterface(POSManager& POS_SYSTEM) {
        char horizontal = 196;
        string nameInput, purchaseType;
        int quantity_input;
        double price_input;

        cout << '\n';
        cout << '\n';
        cout << '\n';
        cout << setw(35);
        for (int i = 0; i < 50; i++) {
            cout << horizontal;
        }
        cout << endl;

        cout << setw(35) << "\t\t  PRODUCT NAME: ";
        cin.ignore();
        getline(cin, nameInput);

        while (true) {
            cout << setw(35) << "\t\t\t\t  TYPE OF PURCHASE (CASH, CARD, EPAY / MUST BE UPPERCASE): ";
            getline(cin, purchaseType);

            if (purchaseType == "CASH" || purchaseType == "CARD" || purchaseType == "EPAY") {
                break;
            } else {
                cout << "Error, must be uppercase (CASH, CARD, EPAY)." << endl;
            }
        }

        cout << setw(35) << "\t\t  QUANTITY: ";
        cin >> quantity_input;

        while (quantity_input < 0) {
            cout << "Error, quantity cannot be negative. Please enter again: ";
            cin >> quantity_input;
        }

        cout << setw(35) << "\t\t  PRICE (P): ";
        cin >> price_input;

        while (price_input < 0) {
            cout << "Error, price cannot be negative. Please enter again: ";
            cin >> price_input;
        }

        cout << setw(35);
        for (int i = 0; i < 50; i++) {
            cout << horizontal;
        }
        cout << endl;
        POS_SYSTEM.ADD_PRODUCT(nameInput, purchaseType, price_input, quantity_input);
    }



    // ======================================================================================================



    void updateProductInterface(POSManager& POS_SYSTEM, int update_idnumber) {

        char horizontal = 196;
        string newName, newType;
        int newQuantity;
        double newPrice;

        cout << '\n';
        cout << '\n';
        cout << '\n';
        cout << setw(35);


        for (int i = 0; i < 50; i++) {
            cout << horizontal;
        }
        cout << endl;

        cout << setw(35) << "\t\t  PRODUCT NAME: ";
        cin.ignore();
        getline(cin, newName);

        while (true) {
            cout << setw(35) << "\t\t\t\t  TYPE OF PURCHASE (CASH, CARD, EPAY / MUST BE UPPERCASE): ";
            getline(cin, newType);

            if (newType == "CASH" || newType == "CARD" || newType == "EPAY") {
                break;
            } else {
                cout << "Error, must be uppercase (CASH, CARD, EPAY)." << endl;
            }
        }

        cout << setw(35) << "\t\t  QUANTITY: ";
        cin >> newQuantity;

        while (newQuantity < 0) {
            cout << "Error, quantity cannot be negative. Please enter again: ";
            cin >> newQuantity;
        }

        cout << setw(35) << "\t\t  PRICE: P";
        cin >> newPrice;

        while (newPrice < 0) {
            cout << "Error, price cannot be negative. Please enter again: ";
            cin >> newPrice;
        }

        cout << setw(35);
        for (int i = 0; i < 50; i++) {
            cout << horizontal;
        }
        cout << endl;
        POS_SYSTEM.UPDATE_PRODUCT(update_idnumber, newName, newType, newPrice, newQuantity);
    }



 // MAIN FUNCTION AREA



    int main() {
        int choice;
        int ID_Number;
        POSManager POS_SYSTEM;
        MAINMENU:
        do {
            system("CLS");
            printMenu(choice);
            switch (choice) {
                case 1:
                    ADDPRODUCT:
                        system("CLS");
                addProductInterface(POS_SYSTEM);
                do {
                    cout << "\t\t\t\t  1. ADD ANOTHER PRODUCT      2. RETURN TO MAIN MENU" << endl;
                    cin >> choice;

                    switch (choice) {
                        case 1:
                            goto ADDPRODUCT;
                        break;

                        case 2:
                            goto MAINMENU;
                        break;
                        default:
                            cout << "Error, Please try again." << endl;
                    }
                } while (choice != 1 && choice != 2);
                break;
                case 2:
                    DISPLAYPRODUCT:
                        system("CLS");
                POS_SYSTEM.DISPLAY_PRODUCT();

                do {
                    cout << endl;
                    cout << "\t\t1. ADD ANOTHER PRODUCT  2. UPDATE A PRODUCT  3. DELETE A PRODUCT  4. RETURN TO MAIN MENU" << endl;
                    cin >> choice;

                    switch (choice) {
                        case 1:
                            addProductInterface(POS_SYSTEM);
                            goto DISPLAYPRODUCT;
                        break;

                        case 2:
                            cout << "Enter the ID of the product you want to update: ";
                        cin >> ID_Number;
                        updateProductInterface(POS_SYSTEM, ID_Number);
                        goto DISPLAYPRODUCT;

                        case 3:

                            cout << "Enter the ID of the product you want to delete: ";
                        cin >> ID_Number;
                        POS_SYSTEM.DELETE_PRODUCT(ID_Number);
                        goto DISPLAYPRODUCT;;
                        case 4:

                            goto MAINMENU;
                        break;

                        default:
                            cout << "Error, Please try again." << endl;
                    }
                } while (choice != 1 && choice != 2);

                break;

                case 3:
                    system ("CLS");
                int choice1;
                POS_SYSTEM.DISPLAY_PRODUCT();
                cout << endl;
                cout << "ENTER '0' TO LEAVE THE UPDATE MENU | ENTER '1' IF YOU WANT TO UPDATE: ";
                cin >> choice1;
                if (choice1 == 0) {
                    goto MAINMENU;
                } else {
                    cout << "Enter the ID of the product you want to update: ";
                    cin >> ID_Number;
                    updateProductInterface(POS_SYSTEM, ID_Number);
                    goto DISPLAYPRODUCT;
                }
                case 4:
                    system ("CLS");
                POS_SYSTEM.DISPLAY_PRODUCT();
                cout << endl;
                cout << "ENTER '0' TO LEAVE THE UPDATE MENU | ENTER '1' IF YOU WANT TO DELETE: ";
                cin >> choice1;
                if (choice1 == 0) {
                    goto MAINMENU;
                } else {
                    cout << "Enter the ID of the product you want to delete: ";
                    cin >> ID_Number;
                    POS_SYSTEM.DELETE_PRODUCT(ID_Number);
                    goto DISPLAYPRODUCT;
                    break;
                }
                case 5:
                    system("CLS");
                char loadingScreen = 219;
                cout << "\t\t\tSaving Products..." << endl;
                cout << setw (50);
                for (int j = 0; j < 50; j++) {
                    Sleep (50);
                    cout  << loadingScreen;
                }
                cout << endl;

                POS_SYSTEM.SAVE_PRODUCTS();
                cout << "Thank you for using CRUDIPOSSYSTEM. Goodbye!" << endl;
                break;
            }
        } while (choice != 5);
        return 0;
    }



