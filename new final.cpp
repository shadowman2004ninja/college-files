#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <ctime>
#include <cstdlib>

using namespace std;

void readIDs(int &currentBookingID, int &currentCustomerID)
{
    ifstream file("ID's.txt");
    if (!file)
    {
        cout << "File does not exist, initializing IDs to default values." << endl;
        currentBookingID = 100;
        currentCustomerID = 200;
    }
    else
    {
        file >> currentBookingID >> currentCustomerID;
        file.close();
    }
}

void saveIDs(int &currentBookingID, int &currentCustomerID)
{
    ofstream file("ID's.txt");
    if (!file)
    {
        cerr << "Error opening file to save IDs." << endl;
    }
    else
    {
        file << currentBookingID << "\n" << currentCustomerID << "\n";
        file.close();
    }
}

class Tour
{
protected:
    string departuredate, returndate;
    int availability, tourid, d;
    double price;

public:
    Tour()
    {
        availability = 30;
dest:
        cout << "\nThe destination places are\n Enter the following options :\nOoty : enter 1\nKodaikanal : enter 2\nKanyakumari : enter 3\n\n";
        cin >> d;
        if (d == 1)
        {
            cout << "You have selected destination: Ooty\n";
            departuredate = "27-07-2024";
            returndate = "30-07-2024";
            tourid = 1334;
            price = 2000.00;
            cout << "Duration is 3 days and 2 nights \n";
            cout << "The departuredate is   "<<departuredate<<endl;
            cout << "The returndate is      "<<returndate<<endl;
        }
        else if (d == 2)
        {
            cout << "You have selected destination: Kodaikanal\n";
            departuredate = "25-07-2024";
            returndate = "29-07-2024";
            tourid = 1345;
            price = 2500.00;
            cout << "Duration is 4 days and 4 nights \n";
            cout << "The departuredate is   "<<departuredate<<endl;
            cout << "The returndate is       "<<returndate<<endl;
        }
        else if (d == 3)
        {
            cout << "You have selected destination: Kanyakumari\n";
            departuredate = "26-07-2024";
            returndate = "29-07-2024";
            tourid = 1353;
            price = 1750.00;
            cout << "Duration is 3 days and 3 nights \n";
            cout << "The departuredate is    "<<departuredate<<endl;
            cout << "The returndate is       "<<returndate<<endl;
        }
        else
        {
            cout << "The selected destination is not available please Enter the correct destination place\n";
            goto dest;
        }
        cout << endl << endl << endl << endl;
    }
};

class Customer
{
protected:
    int age, customerid;
    long long int phonenumber;
    string gender;
    string name;
    string address, email;

public:
    Customer(int &currentCustomerID)
    {
        customerid = currentCustomerID++;
        cout << setfill(' ');
        cout << setw(60);
        cout << "****PERSONAL DETAILS**** ";
        cout << "\nENTER THE AGE : ";
        cin >> age;
        cout << "\nENTER THE PHONE NUMBER : ";
        cin >> phonenumber;
        cin.ignore();
        cout << "\nENTER THE NAME : ";
        getline(cin, name);
        cout << "\nENTER THE ADDRESS : ";
        getline(cin, address);
        cout << "\nENTER THE EMAIL : ";
        getline(cin, email);
        cout << "\nENTER THE GENDER (male/female): ";
        cin >> gender;
        cin.ignore();
    }
};

class Booking : public Tour, public Customer
{
protected:
    double totalcost;
    int numadults, numchildren, bookingid, a;
    string bookingdate;

public:
    Booking(int &currentBookingID, int &currentCustomerID) : Customer(currentCustomerID)
    {
        char get1;
        cout << endl << endl;
        cout << setw(60);
        cout << "****BOOKING PAGE**** ";
        cout << endl;
        bookingid = currentBookingID++;
        time_t now=time(NULL) ;
        bookingdate=ctime(&now);
        cout << "Booking date is: "<<bookingdate;
        cout << "\nNumber of adults: ";
        cin >> numadults;
        cout << "\nNumber of children: ";
        cin >> numchildren;
        a = numadults + numchildren;
        if(a<=availability)
        {
            generatebook();
        }
        else
        {
            try
            {
                if (a <= availability)
                {
                    cout << "Booking successfully completed \n";
                }
                else
                {
                    throw a;
                }
            }
            catch (int s)
            {
                cerr << "Sorry, the availability is only " << availability << ". Your number is " << a << endl;
                cout << "if you want to book within the given availability ENTER 'u'";
                cin>>get1;
                if(get1=='u'||get1=='U')
                {
                    updatedbookingdetails();
                }
                else
                {
                    cancelbooking();
                }
            }
        }
    }

    void generatebook()
    {
        cout << "\nBooking details are:\n\n";
        cout<<  "Name :              " << name<<endl;
        cout << "Booking id:         " << bookingid << endl;
        cout << "Customer id:        " << customerid << endl;
        cout << "Tour id:            " << tourid << endl;
        cout << "Booking date:       " << bookingdate << endl;
        cout << "Number of adults:   " << numadults << endl;
        cout << "Number of children: " << numchildren << endl;
        totalcost = (numadults * price) + (numchildren * (price * 0.50));
        cout << "Total cost:         " << totalcost << endl;

    }

    void updatedbookingdetails()
    {
        int a;
        cout << "\n\nEnter the updated details:\n";
        time_t now=time(NULL) ;
        bookingdate=ctime(&now);
        cout << "Booking date: "<<bookingdate;
        cout << "Number of adults: ";
        cin >> numadults;
        cout << "Number of children: ";
        cin >> numchildren;
        a = numadults + numchildren;
        try
        {
            if (a <= availability)
            {
                cout << "Booking successfully completed \n";
            }
            else
            {
                throw a;
            }
        }
        catch (int s)
        {
            cerr << "Sorry, the availability is only " << availability << ". Your number is " << a << endl;
        }
        generatebook();
    }

    void cancelbooking()
    {
        cout << "Booking id " << bookingid << " is cancelled" << endl;
        exit(0);
    }


};
template<class D>
class Package : public Booking
{
public:
    Package(int &currentBookingID, int &currentCustomerID) : Booking(currentBookingID, currentCustomerID) {}
    D dp;
    void display(D a)
    {
        dp = totalcost - (totalcost * (a / 100.00));
        cout << "Your discounted price for the tour in summer: ";
        cout << fixed << setprecision(2) << dp << endl;
    }

    void display(D a, D b)
    {
        dp = totalcost - (totalcost * ((a + b) / 100.00));
        cout << "Your discounted price for the tour in winter: ";
        cout << fixed << setprecision(2) << dp << endl;
    }
    void saveBook()
    {
        ofstream file2("Bookings.txt", ios::app);
        if (!file2)
        {
            cerr << "Error in opening file to save booking details.";
        }
        else
        {
            file2 << "Name : " << name << "\n";
            file2 << "Booking id: " << bookingid << "\n";
            file2 << "Customer id: " << customerid << "\n";
            file2 << "Tour id: " << tourid << "\n";
            file2 << "Booking date: " << bookingdate << "\n";
            file2 << "Number of adults: " << numadults << "\n";
            file2 << "Number of children: " << numchildren << "\n";
            file2 << "Total cost after discount: " << dp << "\n";
            file2 << "-----------------------------------------\n";
            file2.close();
        }
    }
};

int main()
{
    cout<<setw(64);
    cout<<"****HOME PAGE****";
    cout<<endl;
    string temp;
    int managerid=1234,idm,mid;
    string managerpw="oops",mpw;
    cout<<" If you are"<<endl<<" a customer 1 (or) a Manager Enter 2   :";
    cin>>idm;
    if(idm==2)
    {
error:
        cout<<"Enter the Manager ID.       :";
        cin>>mid;
        cout<<"Enter the password for your page :";
        cin>>mpw;
        if(managerid==mid&&managerpw==mpw)
        {
            cout<<"\nWelcome manager to the SVK"<<endl;
            ifstream file2("bookings.txt",ios::in);
            if(!file2)
            {
                cout<<"\nError opening file"<<endl;
            }
            else
            {
                while(getline(file2,temp))
                {
                    cout<<temp<<endl;
                }
            }
        }
        else
        {
            cout<<"\nPlease Enter the valid manager id and password"<<endl;
            goto error;
        }
    }
    else if(idm==1)
    {
        int currentBookingID, currentCustomerID;
        readIDs(currentBookingID, currentCustomerID);

        char conB;
        do
        {
            cout<<endl<<endl<<endl<<endl;
            cout << setw(60);
            cout << "SVK TOUR BOOKING SYSTEM" << endl;
            cout << "                   ''Travel leaves you speechless and turn you into a storyteller''  " << endl;
            cout << setw(238);
            cout << setfill('*') << endl;

            Package<float>p(currentBookingID, currentCustomerID);

            int month;
            time_t now=time(0);
            tm* time1=localtime(&now);
            month = time1->tm_mon+1;
            cout<<"The current month is "<<month<<endl;

            if (month <= 6)
            {
                p.display(10.00);
            }
            else
            {
                p.display(10.00, 20.00);
            }

            cout << endl << endl;
            char k;
            cout << "DO YOU WANT TO UPDATE DETAILS OR CANCEL SERVICE? (update = u/cancel = c, no need = n): ";
            cin >> k;
            if (k == 'u')
            {
                p.updatedbookingdetails();
                cout << endl << "Updated successfully ";
            }
            else if (k == 'c')
            {
                p.cancelbooking();
                cout << endl << "Cancelled successfully";
            }
            else if (k == 'n')
            {
                cout << "Booking completed ";
            }
            else
            {
                cout << "INVALID ARGUMENT";
            }

            p.saveBook();

            cout << endl << "Do you want to book another tour? (y/n): ";
            cin >> conB;

        }
        while (conB == 'y' || conB == 'Y');

        saveIDs(currentBookingID, currentCustomerID);

        cout << endl << endl << "THANK YOU.......... Visit us next time";

    }
    else
    {
        cout<<" INVALID ARGUMENT ";

    }
}
