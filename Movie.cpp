#include <iostream>
#include "Movie.h"
#include <string>
 
using namespace std;


Movie::Movie(string title, string director, string year, int num_of_actors, string *actors, string status)
{
    this->title = title;
    this->director = director;
    this->year = year;
    this->num_of_actors = num_of_actors;
    this->actors = actors;
    this->status = status;
    next = NULL;
}


string Movie::getTitle()
{
    return title;
}

void Movie::setTitle(string title)
{
    this->title = title;
}

string Movie::getDirector()
{
    return director;
}

void Movie::setDirector(string director)
{
    this->director = director;
}

string Movie::getYear()
{
    return year;
}

void Movie::setYear(string year)
{
    this->year = year;
}

string* Movie::getActors()
{
    return actors;
}

void Movie::setActors(string *actors)
{
    this->actors = actors;
}

string Movie::getStatus()
{
    return status;
}

void Movie::setStatus(string status)
{
    this->status = status;
}

string Movie::getId()
{
    return id;
}

void Movie::setId(string id)
{
    this->id = id;
}

string Movie::getDate()
{
    return date;
}

void Movie::setDate(string date)
{
    this->date = date;
}

Movie* Movie::getNext()
{
    return next;
}

void Movie::setNext(Movie *movie)
{
    next = movie;
}

int Movie::getNumOfActors()
{
    return num_of_actors;
}

string Movie::toString()
{
    string actors_str = "";
    for (int i = 0; i < num_of_actors; i++)
    {
        actors_str = actors_str + actors[i] + " ";
    }
    
    return title + " " +
           director + " " +
           year + " " +
           actors_str +
           status + " " +
           id + " " +
           date + " ";
}








          





