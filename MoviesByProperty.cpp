#include <iostream>
#include "MoviesByProperty.h"
#include <string>
 
using namespace std;


string MoviesByProperty::getProperty()
{
    return property;
}

void MoviesByProperty::setProperty(string property)
{
    this->property = property;
}

Movie** MoviesByProperty::getMovies()
{
    return movies;
}

void MoviesByProperty::setMovies(Movie** movies, int size, int capacity)
{
    this->movies = movies;
    this->size = size;
    this->capacity = capacity;
}

int MoviesByProperty::getCapacity()
{
    return capacity;
}

int MoviesByProperty::getSize()
{
    return size;
}

string MoviesByProperty::getMoviesStr()
{
    string str_movies = "";
    for (int i = 0; i < size; i++)
    {    
        str_movies = str_movies + movies[i]->toString() + '\n';
    }
    return str_movies;
}

void MoviesByProperty::addMovie(Movie *movie)
{
    if (capacity == size)
    {
        increaseArray();
    }
    movies[size] = movie;
    size++;
}


void MoviesByProperty::increaseArray()
{
    capacity = capacity + 10;
    Movie** tmp = new Movie*[capacity];

    for (int i = 0; i < size; i++)
    {
        tmp[i] = movies[i];
    }
    
    delete[] movies;
    movies = tmp;
}


void MoviesByProperty::reset()
{
    size = 0;
    capacity = 10;
    movies = new Movie*[capacity];
}
