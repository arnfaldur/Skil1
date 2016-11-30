#include <iostream>
#include <string>
#include <fstream>
#include "consoleui.h"
#include "person.h"

using namespace std;

ConsoleUI::ConsoleUI()
{

}

void ConsoleUI::run()
{
    do
    {
        instructions();
        string command;
        cin >> command;

        if(command == "add")
        {
            add();
        }
        else if(command == "search")
        {
            search();
        }
        else if(command == "list")
        {
            list();
        }
        else if(command == "quit" || command == "q" || command == "exit")
        {
            break;
        }
        else
        {
            /*
             *  Unknown command handeling
             */
            cout << "Unknown command: " << command << endl;
            cout << "please try again." << endl;
        }
    }while(true);
}

void ConsoleUI::instructions()
{
    cout << "=================================================" << endl;
    cout << "|| Please enter one of the following commands: ||" << endl;
    cout << "=================================================" << endl;
    cout << "|| \t add    - to add a new person \t       ||" << endl;
    cout << "|| \t list   - to get a list of persons     ||" << endl;
    cout << "|| \t search - to search list \t       ||" << endl;
    cout << "|| \t quit   - to exit program \t       ||" << endl;
    cout << "=================================================" << endl;
}

void ConsoleUI::add()
{
    string name;
    char gender;
    int birth;
    int death;
    string country;

    cout << "=======================================================" << endl;
    cout << "||Please add the parameters for the scientists       ||" << endl;
    cout << "||if you input invalid data you will be asked again. ||" << endl;
    cout << "=======================================================" << endl;

    /*
     * TODO: debug why you cant enter a name that is more than one word
     */
    do
    {
        cout << "Name: ";
        cin >> name;
    }while(!_Valid.nameCheck(name));
    do
    {
        cout << "Gender: ";
        cin >> gender;
    }while(!_Valid.genderCheck(gender));
    do
    {
        cout << "Year born: ";
        cin >> birth;
    }while(!_Valid.birthCheck(birth));
    do
    {
        cout << "Year of death: ";
        cin >> death;
    }while(!_Valid.deathCheck(death));
    do
    {
        cout << "Country of origin: ";
        cin >> country;
    }while(!_Valid.nameCheck(country));

    Person newPerson(name, gender, birth, death, country);

    bool success = _service.addPerson(newPerson);

    if(success)
        cout << "Success!" << endl;
    else
        cout << "There was an error writing the data!" << endl;
}

void ConsoleUI::search()
{
    cout << "Please enter what you want to search: ";

    string searchList;
    cin >> searchList;
    vector<Person> persons;

    persons = _service.getPersons(0);

    for(size_t i = 0; i < persons.size(); ++i){
        if(persons[i].getName() == searchList)
        {
            displayPerson(persons[i]);
        }
    }
}

void ConsoleUI::list()
{
    cout << "=================================================" << endl;
    cout << "|| Please enter one of the following commands: ||" << endl;
    cout << "=================================================" << endl;
    cout << "|| \t name - sort by name alphabeticaly     ||" << endl;
    cout << "|| \t year - sort by year of birth \t       ||" << endl;
    cout << "|| \t country - sort by country \t       ||" << endl;
    cout << "|| \t unsorted - get unsorted list          ||" << endl;
    cout << "=================================================" << endl;

    string sort;
    cin >> sort;
    vector<Person> persons;

    if (sort == "name")
        persons = _service.getPersons(1);
    else if (sort == "year")
        persons = _service.getPersons(2);
    else if (sort == "country")
        persons = _service.getPersons(3);
    else if (sort == "unsorted")
        persons = _service.getPersons(0);

    displayPersons(persons);
}

void ConsoleUI::displayPerson(Person person)
{
    cout << "Name:" << "\t\t" << "Gender:" << "\t" << "DoB:" << "\t" << "DoD:" << "\t" << "Country:" << endl;
    cout << person.getName() << "\t\t" << person.getGender() << "\t" << person.getBirth() << "\t" << person.getDeath() << "\t" << person.getCountry() << endl;
}

void ConsoleUI::displayPersons(vector<Person> persons)
{
    cout << "Name:" << "\t\t" << "Gender:" << "\t" << "DoB:" << "\t" << "DoD:" << "\t" << "Country:" << endl;
    for (size_t i = 0; i < persons.size(); ++i)
    {
        cout << persons[i].getName() << "\t\t" << persons[i].getGender() << "\t" << persons[i].getBirth() << "\t" << persons[i].getDeath() << "\t" << persons[i].getCountry() << endl;
    }
}
