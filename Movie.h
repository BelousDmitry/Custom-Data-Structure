#ifndef MOVIE_H
#define MOVIE_H
#include <string>

using  namespace std;

class Movie
{
private:
    string title;
    string director;
    string year;
    string *actors;
    string status;
    string id;
    string date;
    int num_of_actors;
    Movie *next;

public:
    Movie(string title, string director, string year, int num_of_actors, string *actors, string status);
    string getTitle();
    void setTitle(string title);
    string getDirector();
    void setDirector(string director);
    string getYear();
    void setYear(string year);
    string* getActors();
    void setActors(string *actors);
    string getStatus();
    void setStatus(string status);
    string getId();
    void setId(string id);
    string getDate();
    void setDate(string date);
    Movie* getNext();
    void setNext(Movie *movie);
    int getNumOfActors();
    string toString();
};

#endif
