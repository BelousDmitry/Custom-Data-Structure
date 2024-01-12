#ifndef MOVIESBYPROPERTY_H
#define MOVIESBYPROPERTY_H
#include <string>
#include "Movie.h"

using  namespace std;

class MoviesByProperty
{
private:
    int size = 0;
    int capacity = 10;
    string property;
    Movie** movies = new Movie*[capacity];
    void increaseArray();

public:
    string getProperty();
    void setProperty(string property);
    Movie** getMovies();
    void setMovies(Movie** movies, int size, int capacity);
    int getSize();
    int getCapacity();
    void addMovie(Movie *movie);
    string getMoviesStr();
    void reset();
    
};

#endif
