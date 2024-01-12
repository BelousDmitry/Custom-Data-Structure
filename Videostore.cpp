#include <iostream>
#include "Videostore.h"
#include <string>
#include <fstream>

using namespace std;



void Videostore::run()
{
    int filter;
    string input;
    string token;
    string movies;

    string id;
    string title;
    string date;

    loadFile("VideoDB1.txt");
    cout << "Welcome, for detail instructions type 'help'" << endl;

    while (true)
    {
        cout << ">> ";
        getline(cin, input);
        token = getWord(input);

        if (token == "find")
        {
            cout << "choose category: title-1 director-2 year-3 actor-4: ";
            cin >> filter;
            cout << "Search key: ";
            cin >> input;
            movies = findMovies(input, filter);
            show(movies);
            cin.ignore();
        }

        else if (token == "check")
        {
            token = getWord(input);
            if (token == "in")
            {
                title = getWord(input);
                id = getWord(input);
                token = movies_by_title.checkIn(title,id);
                cout << token << " was set as in." << endl;
            }
            else if (token == "out")
            {
                title = getWord(input);
                id = getWord(input);
                date = getWord(input);
                token = movies_by_title.checkOut(title, id, date);
                cout << token << " was set as out." << endl;
            }
            else
            {
                cout << "WRONG_INPUT" << endl;
            }
            
        }
        else if (token == "clear")
        {
            clearScreen();
        }
        else if (token == "help")
        {
            showInstructions();
        }
        else if (token == "size")
        {
            token = getWord(input);
            if (token == "=")
            {
                token = getWord(input);
                list_size = atoi(token.c_str());
            }
            else
            {
                cout << "WRONG_INPUT" << endl;
            }
        }
        else if (token == "kill")
        {
            break;
        }
        else
        {
           cout << "WRONG_INPUT" << endl; 
        }
    }
}

string Videostore::findMovies(string input, int filter)
{
    string result = "NOT_FOUND";

    switch (filter)
    {
    case 1:
        result = movies_by_title.findByProperty(input);
        break;
    case 2:
        result = movies_by_director.findByProperty(input);
        break;
    case 3:
        result = movies_by_year.findByProperty(input);
        break;
    case 4:
        result = movies_by_actor.findByProperty(input);
        break;
    }

    return result;
}

void Videostore::loadFile(string file_name)
{
    fstream file;
    int num_of_rows;
    Movie *movie;
    string title;
    string director;
    string year;
    string *actors;
    string status;
    string id;
    string date;
    int num_of_actors;

    file.open(file_name.c_str());
    file >> num_of_rows;

    for (int i = 0; i < num_of_rows; i++)
    {
        file >> title;
        file >> director;
        file >> year;
        file >> num_of_actors;

        actors = new string[num_of_actors];

        for (int j = 0; j < num_of_actors; j++)
        {
            file >> actors[j];
        }

        file >> status;

        movie = new Movie(title, director, year, num_of_actors, actors, status);

        if (status == "out")
        {
            file >> id;
            file >> date;
            movie->setId(id);
            movie->setDate(date);
        }

        movie->setNext(head);
        head = movie;

        movies_by_title.add(title, movie);
        movies_by_director.add(director, movie);
        movies_by_year.add(year, movie);

        for (int j = 0; j < num_of_actors; j++)
        {
            movies_by_actor.add(actors[j], movie);
        }
    }

    file.close();
}


void Videostore::show(string movies)
{
    string token;
    int i = 1;
    int id = movies.find('\n');

    while (id != -1)
    {
        token = movies.substr(0, id);
        cout << i << ": " << token << endl;
        movies = movies.substr(id + 1);
        id = movies.find('\n');
        if (i % list_size == 0)
        {
            cout << "Type any letter to keep scroling or 'exit' to stop: ";
            cin >> token;
            if (token == "exit")
                break;
            clearScreen();
        }
        i++;
    }
}

string Videostore::getWord(string &sentence)
{
    string word;
    int space_id;

    space_id = sentence.find(" ");
    if (space_id == -1)
    {
        word = sentence;
        sentence = "";
    }
    else
    {
        word = sentence.substr(0, space_id);
        sentence = sentence.substr(space_id + 1);
    }

    return word;
}

void Videostore::clearScreen()
{
    if (system("clear") != 0 && system("cls") != 0)
    {
        cout << string(100, '\n');
    }
}


void Videostore::showInstructions()
{
    cout << "find - " << "find movies by their peoperties." << endl;
    cout << " - You will have to type a number according to peoperty you will use to find the movies" << endl;
    cout << " - There are 4 peoperties: title-1 director-2 year-3 actor-4" << endl;
    cout << " - You can use prefix search '*prefix' or combined with suffix 'prefix*suffix'" << endl;
    cout << "size = 'number' - " << "Set size of the list. Current size is " << list_size << endl;
    cout << "clear - " << "clear the terminal." << endl;
    cout << "check in 'title' 'id' - " << "Check in the movie."<< endl;
    cout << "check out 'title' 'id' 'date' - " << "Check out the movie." << endl;
    cout << "kill - " << "exit the program." << endl;
    cout << "help - " << "get command instructions." << endl;
}