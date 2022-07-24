#include <iostream>
#include <stdlib.h>
#include <ctime>
#include <fstream>
const int gst = 17; // GST is 17% in Pakistan

using namespace std;
int orderNumber = 0;
class medDetails
{
public:
    string medName, customer;
    int quantity, orderQuantity, orderNum, serial;
    float price, orderPrice;

    void getMed()
    {
        system("CLS");
        srand(time(0));
        serial = rand() % 1000 + 1; // This will generate any random number between 1 and 1000
        cin.ignore();
        cout << "\t\t\t\t\t\t\t\t\t\tMedicine Serial Number: " << serial << endl;
        {
            cout << "\t\t\t\t\t\t\t\t\t\tEnter Medicine Name: ";
            getline(cin, medName);
            cout << "\t\t\t\t\t\t\t\t\t\tEnter Price of the Medicine: ";
            cin >> price;
            cout << "\t\t\t\t\t\t\t\t\t\tEnter Quantity: "; // \t\t\t\t\t\t\t\t\t\t  // just for future use
            cin >> quantity;
        }
    }
    void getMed(int s, string mName, float p, int q)
    {
        serial = s;
        medName = mName;
        price = p;
        quantity = q;
    }
};
class med // This is the Node Class
{
public:
    medDetails data;
    med *next;
    med *prev;
};

class admin //
{
public:
    med *head;
    med *tail;

    admin()
    {
        head = NULL;
        tail = NULL;
    }

    // Initializing Functions
    void addMed(medDetails m);
    void create_node(medDetails m);
    int adminMenu(medDetails m);
    void medDisplay();
    void delMed(int serial);
    void delHead();
    void delTail();
    void modMed(int key);
    void searchMed(int key); // Action will be performed based on Serial number.
    void sort();             // Sorting will be performed using Selection Sort Algorithm.
};

class pharmacist
{
public:
    med *head;
    med *tail;

    pharmacist()
    {
        head = NULL;
        tail = NULL;
    }

    /// Function Declaration
    int pharmacistMenu(admin a);
    void buyMed(admin a);
    void orderList();
    void cancelOrder(int serial);  // Action will be performed based on Serial number.
    void printReceipt(int serial); // Action will be performed based on Serial number.
};

///// ADMIM FUNCTIONS /////

void admin ::create_node(medDetails m)
{
    med *newMed = new med();
    newMed->data.serial = m.serial;
    newMed->data.medName = m.medName;
    newMed->data.price = m.price;
    newMed->data.quantity = m.quantity;
    if (head == NULL)
    {

        newMed->next = NULL;
        newMed->prev = NULL;
        head = newMed;
        tail = newMed;
    }
    else
    {

        newMed->next = NULL;
        tail->next = newMed;
        newMed->prev = tail;
        tail = newMed;
    }
    cout << "\t\t\t\t\t\t\t\t\t\tMedicine Added Successfully!" << endl;
}

void admin ::addMed(medDetails m)
{
    m.getMed();
    create_node(m);
}
// Delete Functions
void admin ::delHead()
{
    med *temp = head;
    head = temp->next;
    delete temp;
    head->prev = NULL;
}
void admin ::delTail()
{
    med *temp = tail;
    tail = temp->prev;
    delete temp;
    tail->next = NULL;
}

void admin ::delMed(int key)
{
    bool del = false;
    if (head == NULL)
    {
        cout << "\t\t\t\t\t\t\t\t\t\tNo Medicine Exists. Operation Failed!" << endl;
    }
    else
    {
        med *temp = head;
        while (temp != NULL)
        {
            if (temp->data.serial == key)
            {
                if (temp->prev == NULL)
                {
                    if (head == tail) // only one Node Exist
                    {
                        delete temp;
                        head = NULL;
                        tail = NULL;
                    }
                    else
                    {
                        delHead();
                    }
                    del = true;
                }
                else if (temp == tail)
                {
                    delTail();
                    del = true;
                }
                else
                {
                    temp->next->prev = temp->prev;
                    temp->prev->next = temp->next;
                    delete temp;
                    del = true;
                }
                cout << "\t\t\t\t\t\t\t\t\t\tMedicine Deleted Successfully!" << endl;
            }
            temp = temp->next;
        }
    }
    if (del == false)
        cout << "\t\t\t\t\t\t\t\t\t\tMedicine with Serial Number \" " << key << "\" not Found. Opeartion Failed!" << endl;
}

int admin ::adminMenu(medDetails m)
{
    int selection, key;
    while (true)
    {
    adminMainMenu:
        system("cls");
        cout << "\t\t\t\t\t\t\t\t==================================================\n";
        cout << "\t\t\t\t\t\t\t\t\t        PakHealth Management System \n";
        cout << "\t\t\t\t\t\t\t\t==================================================\n";
        cout << "\t\t\t\t\t\t\t\t--------------------------------------------------\n";
        cout << "\t\t\t\t\t\t\t\t||\t\t1. Enter New Medicine\t\t||\n";
        cout << "\t\t\t\t\t\t\t\t||\t\t2. Delte a Medicine\t\t||\n";
        cout << "\t\t\t\t\t\t\t\t||\t\t3. Modify a Medicine\t\t||\n";
        cout << "\t\t\t\t\t\t\t\t||\t\t4. Search a Medicine\t\t||\n";
        cout << "\t\t\t\t\t\t\t\t||\t\t5. sort all Medicine\t\t||\n";
        cout << "\t\t\t\t\t\t\t\t||\t\t6. Display All Medicines\t||\n";
        cout << "\t\t\t\t\t\t\t\t||\t\t7. Logout\t\t\t||\n";
        cout << "\t\t\t\t\t\t\t\t||\t\t8. Exit\t\t\t\t||\n";
        cout << "\t\t\t\t\t\t\t\t--------------------------------------------------\n";
        cout << endl;
        cout << "\t\t\t\t\t\t\t\t\t\tEnter Your Selection: ";
        cin >> selection;
        switch (selection)
        {
        case 1:
            system("CLS");

            addMed(m);
            system("PAUSE");
            break;
        case 2:
        {
            system("CLS");

            medDisplay();
            cout << "\t\t\t\t\t\t\t\t\t\tEnter the Serial Number of Medicine: ";
            cin >> key;
            delMed(key); // function delete
            system("PAUSE");
            break;
        }
        case 3:
        {
            system("CLS");

            medDisplay();
            cout << "\t\t\t\t\t\t\t\t\t\tEnter the Serial Number of Medicine: ";
            cin >> key;
            modMed(key);
            system("PAUSE");
            break;
        }
        case 4:
            system("CLS");

            cout << "\t\t\t\t\t\t\t\t\t\tEnter the Serial Number of Medicine: ";
            cin >> key;
            searchMed(key);
            system("PAUSE");
            break;
        case 5:
            system("CLS");
            sort();
            system("PAUSE");
            break;
        case 6:
            system("CLS");
            medDisplay();
            system("PAUSE");
            break;
        case 7:
            return 1;
            break;
        case 8:
            exit(1);
            break;
        default:
            cout << "\t\t\t\t\t\t\t\t\t\tInvalid option selected. Please try again" << endl;
            system("PAUSE");
            goto adminMainMenu;
            break;
        }
    }
}

void admin ::searchMed(int key) /// Search Funcion for Admin and Pharmacist
{
    system("CLS");
    bool found;
    med *temp = head;
    while (temp != NULL)
    {
        if (temp->data.serial == key)
        {
            found == true;
            cout << "\t\t\t\t\t\t****************************************************************************\n";
            cout << "\t\t\t\t\t\tMedicine ID"
                 << "\t\tMedicine Name"
                 << "\t\tPrice(RS)"
                 << "\t\tQTY"
                 << endl;
            cout << "\t\t\t\t\t\t****************************************************************************\n";
            cout << "\t\t\t\t\t\t" << temp->data.serial << "\t\t\t" << temp->data.medName << "\t\t\t" << temp->data.price << "\t\t\t" << temp->data.quantity << endl;
            found = true;
            break;
        }
        temp = temp->next;
    }
    if (found == false)
    {
        cout << "\t\t\t\t\t\t\t\t\t\tMedicine Not Found!" << endl;
    }
}

void admin ::medDisplay() // Function to Display all medicines created by the Admin
{
    cout << "\t\t\t\t\t\t****************************************************************************\n";
    cout << "\t\t\t\t\t\tMedicine ID"
         << "\t\tMedicine Name"
         << "\t\tPrice(RS)"
         << "\t\tQTY"
         << endl;
    cout << "\t\t\t\t\t\t****************************************************************************\n";
    med *temp;
    temp = head;
    while (temp != NULL)
    {
        cout << "\t\t\t\t\t\t" << temp->data.serial << "\t\t\t" << temp->data.medName << "\t\t\t" << temp->data.price << "\t\t\t" << temp->data.quantity << endl;
        temp = temp->next;
    }
}

void admin ::modMed(int key) // Function to Modify a Medicine. Admin has to enter the Serial number of the Medicine
{
    med *temp = head;
    bool mod = false;
    while (temp != NULL)
    {
        if (temp->data.serial == key)
        {
            cout << "\t\t\t\t\t\t\t\t\t\tEnter Medicine Name: ";
            cin >> temp->data.medName;
            cout << "\t\t\t\t\t\t\t\t\t\tEnter Price of the Medicine: ";
            cin >> temp->data.price;
            cout << "\t\t\t\t\t\t\t\t\t\tEnter Quantity: ";
            cin >> temp->data.quantity;
            mod = true;
        }
        temp = temp->next;
    }
    if (mod == false)
        cout << "\t\t\t\t\t\t\t\tMedicine with Serial Number \" " << key << "\" not Found. Opeartion Failed!" << endl;
}

void admin ::sort() // Data part of all nodes is being interchanged based on Seral Number Sorting. (Ascending Order)
{
    med *temp = head;
    while (temp)
    {
        med *min = temp;
        med *r = temp->next;
        while (r)
        {
            if (min->data.serial > r->data.serial)
            {
                min = r;
            }
            r = r->next;
        }
        int medSer = temp->data.serial;
        string medN = temp->data.medName;
        int medqty = temp->data.quantity;
        float medprice = temp->data.price;
        temp->data.serial = min->data.serial;
        min->data.serial = medSer;
        temp->data.medName = min->data.medName;
        min->data.medName = medN;
        temp->data.price = min->data.price;
        min->data.price = medprice;
        temp->data.quantity = min->data.quantity;
        min->data.quantity = medqty;
        temp = temp->next;
    }
}

///// PHARMACIST FUNCTIONS //////

int pharmacist ::pharmacistMenu(admin a)
{
    int selection, key;
    while (true)
    {
    pharmacistMainMenu:
        system("cls");
        cout << "\t\t\t\t\t\t\t\t==================================================\n";
        cout << "\t\t\t\t\t\t\t\t\t        PakHealth Management System \n";
        cout << "\t\t\t\t\t\t\t\t==================================================\n";
        cout << "\t\t\t\t\t\t\t\t--------------------------------------------------\n";
        cout << "\t\t\t\t\t\t\t\t||\t\t1. Buy Medicine\t\t\t||\n";
        cout << "\t\t\t\t\t\t\t\t||\t\t2. Show Order List\t\t||\n";
        cout << "\t\t\t\t\t\t\t\t||\t\t3. Cancel Order\t\t\t||\n";
        cout << "\t\t\t\t\t\t\t\t||\t\t4. Generate Bill\t\t||\n";
        cout << "\t\t\t\t\t\t\t\t||\t\t5. Logout\t\t\t||\n";
        cout << "\t\t\t\t\t\t\t\t||\t\t6. Exit\t\t\t\t||\n";
        cout << "\t\t\t\t\t\t\t\t--------------------------------------------------\n";
        cout << endl;
        cout << "\t\t\t\t\t\t\t\t\t\tEnter Your Selection: ";
        cin >> selection;
        switch (selection)
        {
        case 1:
            system("CLS");
            buyMed(a);
            system("PAUSE");
            break;
        case 2:
            system("CLS");
            {
                orderList();
                system("PAUSE");
                break;
            }
        case 3:
            system("CLS");
            {
                orderList();
                cout << endl;
                cout << "\t\t\t\t\t\t\t\t\t\tEnter the Serial Number of Medicine: ";
                cin >> key;
                cancelOrder(key);
                system("PAUSE");
                break;
            }
        case 4:
            system("CLS");
            orderList();
            cout << endl;
            cout << "\t\t\t\t\t\t\t\t\t\tEnter the Serial Number of Medicine: ";
            cin >> key;
            printReceipt(key);
            system("PAUSE");
            break;
        case 5:
            return 1;
            system("PAUSE");
            break;
        case 6:
            exit(1);
            break;
        default:
            cout << "\t\t\t\t\t\t\t\t\t\tInvalid option selected. Please try again" << endl;
            system("PAUSE");
            goto pharmacistMainMenu;
            break;
        }
    }
}

void pharmacist ::buyMed(admin a)
{
    orderNumber = orderNumber + 1;
tryagain: // If the Pharmacist enters wrong serial number, he/she can try again
    cin.ignore();
    med *temp;
    a.medDisplay();
    temp = a.head;
    string customer;
    int userQty, selection, tryagain;
    float orderP;
    cout << endl;
    cout << "\t\t\t\t\t\t\t\t\t\tEnter Customer Name: ";
    getline(cin, customer);
buyMoreMed:
    bool found = false;
    temp = a.head; // Pointing Back to head
    cout << "\t\t\t\t\t\t\t\tEnter Serail Number of the Medicine you want to Buy: ";
    cin >> selection;
    system("CLS"); 
    while (temp != NULL)
    {
        if (temp->data.serial == selection)
        {
            found == true;
            cout << "\t\t\t\t\t\t****************************************************************************\n";
            cout << "\t\t\t\t\t\tMedicine ID"
                 << "\t\tMedicine Name"
                 << "\t\tPrice(RS)"
                 << "\t\tQTY"
                 << endl;
            cout << "\t\t\t\t\t\t****************************************************************************\n";
            cout << "\t\t\t\t\t\t" << temp->data.serial << "\t\t\t" << temp->data.medName << "\t\t" << temp->data.price << "\t\t   " << temp->data.quantity << endl;
            found = true;
            break;
        }
        temp = temp->next;
    }
    if (found == true)
    {
    enterQty:
        cout << endl;
        cout << "\t\t\t\t\t\t\t\tEnter Quantity (chose less than or Equal to " << temp->data.quantity << " ): ";
        cin >> userQty;
        if (userQty <= temp->data.quantity)
        {
            orderP = userQty * temp->data.price; // solve serial numebr problem
        }
        else
        {
            cout << "\t\t\t\t\t\tPlease chose less than or Equal to (" << temp->data.quantity << " )" << endl;
            system("PAUSE");
            goto enterQty;
        }
        // Creating Order Nodes
        med *newOrder = new med();
        newOrder->data.serial = temp->data.serial;
        newOrder->data.medName = temp->data.medName;
        newOrder->data.price = temp->data.price;
        newOrder->data.orderQuantity = userQty;
        temp->data.quantity = temp->data.quantity - userQty;
        newOrder->data.orderNum = orderNumber;
        newOrder->data.customer = customer;
        newOrder->data.orderPrice = orderP;
        if (head == NULL)
        {

            newOrder->next = NULL;
            newOrder->prev = NULL;
            head = newOrder;
            tail = newOrder;
        }
        else
        {

            newOrder->next = NULL;
            tail->next = newOrder;
            newOrder->prev = tail;
            tail = newOrder;
        }
        int buyMore;
        cout << "\t\t\t\t\t\t\t\t\t\tOrder Placed Successfully!" << endl;
        system("PAUSE");
        system("cls");
        cout << "\t\t\t\t\t\t\t\t==================================================\n";
        cout << "\t\t\t\t\t\t\t\t\t        PakHealth Management System \n";
        cout << "\t\t\t\t\t\t\t\t==================================================\n";
        cout << "\t\t\t\t\t\t\t\t---------------------------------------------------\n";
        cout << "\t\t\t\t\t\t\t\t||\t\t1. Buy Medicine for same Customer||\n";
        cout << "\t\t\t\t\t\t\t\t||\t\t2. Buy Medicine for New Customer ||\n";
        cout << "\t\t\t\t\t\t\t\t||\t\t3. Exit\t\t\t\t ||\n";
        cout << "\t\t\t\t\t\t\t\t---------------------------------------------------\n";
        cout << endl;
        cout << "\t\t\t\t\t\t\t\t\t\tEnter Your Selection: ";
        cin >> buyMore;
        switch (buyMore)
        {
        case 1:
            system("CLS");
            a.medDisplay();
            goto buyMoreMed;
            system("PAUSE");
            break;
        case 2:
            system("CLS");
            buyMed(a);
            system("PAUSE");
            break;
        case 3:
            pharmacistMenu(a);
            system("PAUSE");
            break;

        default:
            break;
        }
    }
    else
    {
        cout << "\t\t\t\t\t\t\tMedicine with Serial Number " << selection << " donsn't exist" << endl;
        cout << endl;
        cout << "\t\t\t\t\t\t\tEnter 1 to Try Again Or Press any other key to return to Main Menu: ";
        cin >> tryagain;
        if (tryagain == 1)
        {
            system("CLS");
            goto tryagain;
        }
        else
            pharmacistMenu(a);
    }
}

void pharmacist ::orderList() // Function to Display all medicines created by the Admin
{
    med *temp;
    temp = head;
    cout << "\t\t\t**************************************************************************************************************************************\n"; // \t\t\t\t\t\t // for future use
    cout << "\t\t\tOrder Number"
         << "\t\tCustomer Name"
         << "\t\tMedicine ID"
         << "\tMedicine Name"
         << "\t\tPrice(RS)"
         << "\tQuantity"
         << "\tOrder Cost(RS)"
         << endl;
    cout << "\t\t\t**************************************************************************************************************************************" << endl;
    while (temp != NULL)
    {
        cout << "\t\t\t" << temp->data.orderNum << "\t\t\t" << temp->data.customer << "\t\t" << temp->data.serial << "\t\t" << temp->data.medName << "\t\t\t" << temp->data.price << "\t\t"
             << temp->data.orderQuantity << "\t\t" << temp->data.orderPrice << endl;
        temp = temp->next;
    }
}

void pharmacist ::cancelOrder(int key)
{
    bool cancel = false;
    if (head == NULL)
    {
        cout << "\t\t\t\t\t\t\t\t\t\tNo Order Placed Yet. Operation Failed!" << endl;
    }
    else
    {
        med *temp = head;
        while (temp != NULL)
        {
            if (temp->data.orderNum == key)
            {
                if (temp->prev == NULL) // if selected node is 1st node
                {
                    if (head == tail) // only one Node Exist
                    {
                        delete temp;
                        head = NULL;
                        tail = NULL;
                    }
                    else
                    {
                        head = temp->next;
                        delete temp;
                        head->prev = NULL;
                    }
                    cancel = true;
                }
                else if (temp == tail) // if last node is selected
                {
                    tail = temp->prev;
                    delete temp;
                    tail->next = NULL;
                    cancel = true;
                }
                else // if node exist somewhere in between
                {
                    temp->next->prev = temp->prev;
                    temp->prev->next = temp->next;
                    delete temp;
                    cancel = true;
                }
                cout << "\t\t\t\t\t\t\t\t\t\tOrder Cancled Successfully!" << endl;
            }
            temp = temp->next;
        }
    }
    if (cancel == false)
        cout << "\t\t\t\t\t\t\t\t\t\tMedicine with Serial Number \" " << key << "\" not Found. Opeartion Failed!" << endl;
}

void pharmacist ::printReceipt(int key)
{
    float grossBill = 0.00;
    float netBill = 0.00;
    string customerName;
    bool found = false;
    med *bill = head;
    while (bill != NULL)
    {
        if (bill->data.orderNum == key)
        {
            found = true;
            system("CLS");
            cout << "\t\t\t\t\t\t\t\t===============================================================\n";
            cout << "\t\t\t\t\t\t\t\t"
                 << "|"
                 << "\t\t\t     PakHealth\t\t\t      |\n";
            cout << "\t\t\t\t\t\t\t\t===============================================================\n";
            cout << "\t\t\t\t\t\t\t\t"
                 << "*"
                 << "\tProduct"
                 << "\t\t"
                 << "Price"
                 << "\t\t"
                 << "QTY"
                 << "\t"
                 << "Total\t      *" << endl;
            cout << "\t\t\t\t\t\t\t\t---------------------------------------------------------------\n";
            cout << "\t\t\t\t\t\t\t\t"
                 << "*\t" << bill->data.medName << "\t\t" << bill->data.price << "\t\t" << bill->data.orderQuantity << "\t"
                 << bill->data.orderPrice << "\t      *\n";
            grossBill += bill->data.orderPrice;
            customerName = bill->data.customer;
            netBill = grossBill + (gst * grossBill) / 100;
            bill = bill->next;
        }
        else
            bill = bill->next;
    }
    if (found == true)
    {

        cout << "\t\t\t\t\t\t\t\t---------------------------------------------------------------\n";
        cout << "\t\t\t\t\t\t\t\t\t\t\t\t\tGorss Total: " << grossBill << "\t\n";
        cout << "\t\t\t\t\t\t\t\t---------------------------------------------------------------\n";
        cout << "\t\t\t\t\t\t\t\t\t\t\t\t\tNet Total: " << netBill << "\t\n";
        cout << "\t\t\t\t\t\t\t\t---------------------------------------------------------------\n";
        cout << "\t\t\t\t\t\t\t\t\t\t\t\t\tCustomer: " << customerName << "\t\n";
        cout << "\t\t\t\t\t\t\t\t---------------------------------------------------------------\n";
    }
    else
        cout << "\t\t\t\t\t\t\t\t\t\tOrder with given Order Number doesn't Exist!" << endl;
    system("PAUSE");
}
int main()
{
    system("color 0B");
    admin adm;
    medDetails m;
    pharmacist p;
    m.getMed(2, "Nebrol", 78.25, 50);
    adm.create_node(m);
    m.getMed(8, "Regix", 75.00, 14);
    adm.create_node(m);
    m.getMed(3, "Panadol", 12.45, 45);
    adm.create_node(m);
    int selection, key, login;
    string username, pass;
log:
    int logAttempt = 3;
tryagain:
    logAttempt--;

    while (true)
    {

        if (logAttempt >= 0)
        {
            system("cls");
            cout << "\t\t\t\t\t\t\t\t==================================================\n";
            cout << "\t\t\t\t\t\t\t\t\t        PakHealth Management System \n";
            cout << "\t\t\t\t\t\t\t\t==================================================\n";
            cout << "\t\t\t\t\t\t\t\t---------------------------------------------------\n";
            cout << "\t\t\t\t\t\t\t\t||\t\t1. Login as Admin\t\t ||\n";
            cout << "\t\t\t\t\t\t\t\t||\t\t2. Login as Pharmacist\t\t ||\n";
            cout << "\t\t\t\t\t\t\t\t||\t\t3. Exit\t\t\t\t ||\n";
            cout << "\t\t\t\t\t\t\t\t---------------------------------------------------\n";
            cout << endl;
            cout << "\t\t\t\t\t\t\t\t\t\tEnter Your Selection: ";
            cin >> selection;
            switch (selection)
            {
            case 1:
            {
                string userF, passF;
                cout << "\t\t\t\t\t\t\t\t\t\tEnter Username: ";
                cin >> username;
                cout << "\t\t\t\t\t\t\t\t\t\tEnter Password: ";
                cin >> pass;
                ifstream myfile("loginAdmin.txt"); // Accessing File Named LoginPharm.txt
                getline(myfile, userF);            // Reading username from file
                getline(myfile, passF);            // Rediing password from file
                myfile.close();
                if (username == userF && pass == passF)
                {
                    login = adm.adminMenu(m);
                    if (login == 1)
                        goto log;
                }
                else
                {
                    cout << "\t\t\t\t\t\t\t\t\tCredentials Did not Match. Attemps Left: " << logAttempt << endl;
                    system("PAUSE");
                    goto tryagain;
                }
                system("PAUSE");
                system("CLS");
                break;
            }
            case 2:
            {
                string userF, passF;
                cout << "\t\t\t\t\t\t\t\t\t\tEnter Username: ";
                cin >> username;
                cout << "\t\t\t\t\t\t\t\t\t\tEnter Password: ";
                cin >> pass;
                ifstream myfile2("loginPharm.txt"); // Accessing File Named LoginPharm.txt
                getline(myfile2, userF);            // reading username from file
                getline(myfile2, passF);            // rediing password from file
                myfile2.close();
                if (username == userF && pass == passF)
                {
                    login = p.pharmacistMenu(adm);
                    if (login == 1)
                        goto log;
                }
                else
                {
                    cout << "\t\t\t\t\t\t\t\t\tCredentials Did not Match. Attemps Left: " << logAttempt << endl;
                    system("PAUSE");
                    goto tryagain;
                }
                system("PAUSE");
                system("CLS");
                break;
            }
            case 3:
                exit(1);
                system("PAUSE");
                break;
            default:
                cout << "\t\t\t\t\t\t\t\t\tYour Selection is Invalid, Please Try Again" << endl;
                goto log;
                system("PAUSE");
                break;
            }
        }
        cout << "\t\t\t\t\t\t\t\t\tProgram Terminated. Due to Suspecious Attempt of Login." << endl;
        break;
    }
    system("PAUSE");
    return 0;
}