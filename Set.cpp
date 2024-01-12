#include <iostream>
#include "Set.h"
#include <string>
#include <cstring>

using namespace std;

//add movie to its property
//in case there was not the same one before,
//it sets property in sorted way.
// When it finds correct position
// it moves right part of the array to right by one index 
void Set::add(string property, Movie *movie)
{
    if (capacity >= size)
    {
        increaseArray();
    }

    int index = binarySearch(property, 0, size, false);

    if (index != -1)
    {
        moviesByProperty[index].addMovie(movie);
        return;
    }
    else
    {
        for (int i = 0; i < size; i++)
        {
            if (moviesByProperty[i].getProperty().compare(property) > 0)
            {
                for (int j = size; j > i; j--)
                {
                    moviesByProperty[j].setProperty(moviesByProperty[j - 1].getProperty());
                    moviesByProperty[j].setMovies(moviesByProperty[j - 1].getMovies(), moviesByProperty[j - 1].getSize(), moviesByProperty[j - 1].getCapacity());
                }
                moviesByProperty[i].reset();
                moviesByProperty[i].setProperty(property);
                moviesByProperty[i].addMovie(movie);
                size++;
                return;
            }
        }
    }

    moviesByProperty[size].setProperty(property);
    moviesByProperty[size].addMovie(movie);
    size++;
}

void Set::increaseArray()
{
    capacity = capacity + 10;
    MoviesByProperty *tmp = new MoviesByProperty[capacity];

    for (int i = 0; i < size; i++)
    {
        tmp[i] = moviesByProperty[i];
    }

    delete[] moviesByProperty;
    moviesByProperty = tmp;
}

//finds element using binary search
//then it checks right and left parts of the element
//untill it has same prefix.
string Set::findByPropertyPartial(string prefix)
{
    string result = "";
    string property_from_array;
    int index = binarySearch(prefix, 0, size, true);

    if (index != -1)
    {
        for (int i = index; i >= 0; i--)
        {
            property_from_array = moviesByProperty[i].getProperty();
            property_from_array = property_from_array.substr(0, prefix.size());
            if (property_from_array.compare(prefix) == 0)
                result = result + moviesByProperty[i].getMoviesStr();
            else
                break;
        }

        for (int i = index + 1; i < size; i++)
        {
            property_from_array = moviesByProperty[i].getProperty();
            property_from_array = property_from_array.substr(0, prefix.size());
            if (property_from_array.compare(prefix) == 0)
                result = result + moviesByProperty[i].getMoviesStr();
            else
                break;
        }
    }

    return result;
}

string Set::findByPropertyPartial(string prefix, string suffix)
{
    string result = "";
    string property_tmp;
    string prefix_tmp;
    string suffix_tmp;
    int index = binarySearch(prefix, 0, size, true);

    if (index != -1)
    {
        for (int i = index; i >= 0; i--)
        {
            property_tmp = moviesByProperty[i].getProperty();
            prefix_tmp = property_tmp.substr(0, prefix.size());
            suffix_tmp = property_tmp.substr(property_tmp.size() - suffix.size());
            if (prefix_tmp.compare(prefix) == 0 && suffix_tmp.compare(suffix) == 0)
                result = result + moviesByProperty[i].getMoviesStr();
            else if (prefix_tmp.compare(prefix) != 0)
                break;
        }

        for (int i = index + 1; i < size; i++)
        {
            property_tmp = moviesByProperty[i].getProperty();
            prefix_tmp = property_tmp.substr(0, prefix.size());
            suffix_tmp = property_tmp.substr(property_tmp.size() - suffix.size());
            if (prefix_tmp.compare(prefix) == 0 && suffix_tmp.compare(suffix) == 0)
                result = result + moviesByProperty[i].getMoviesStr();
            else if (prefix_tmp.compare(prefix) != 0)
                break;
        }
    }

    return result;
}

string Set::findByProperty(string property)
{
    int index;
    string prefix;
    string suffix;

    if (property[0] == '*')
    {
        prefix = property.substr(1);
        return findByPropertyPartial(prefix);
    }
    else if (property.find('*') != -1)
    {
        prefix = property.substr(0, property.find('*'));
        suffix = property.substr(property.find('*') + 1);
        return findByPropertyPartial(prefix, suffix);
    }

    index = binarySearch(property, 0, size, false);
    if (index != -1)
    {
        return moviesByProperty[index].getMoviesStr();
    }

    return "NOT_FOUND";
}

int Set::binarySearch(string property, int low, int high, bool is_prefix)
{
    int mid;
    string property_from_array;

    if (low > high)
    {
        return -1;
    }

    else
    {
        mid = (low + high) / 2;
        property_from_array = moviesByProperty[mid].getProperty();
        if (is_prefix)
        {
            property_from_array = property_from_array.substr(0, property.size());
        }

        if (property_from_array.compare(property) == 0)
        {
            return mid;
        }
        else if (property_from_array.compare(property) < 0)
        {
            return binarySearch(property, mid + 1, high, is_prefix);
        }
        else
        {
            return binarySearch(property, low, mid - 1, is_prefix);
        }
    }
}

//takes all movies with the given title
//checks if id is alredy taken
//then it takes first free(in) movies and set it as "out".
string Set::checkOut(string title, string id, string date)
{
    Movie **movie;
    int index = binarySearch(title, 0, size, false);
    if (index != -1)
    {
        movie = moviesByProperty[index].getMovies();
        for (int i = 0; i < moviesByProperty[index].getSize(); i++)
        {
            if (movie[i]->getId() == id)
                return "ALREADY_EXIST";
        }
        for (int i = 0; i < moviesByProperty[index].getSize(); i++)
        {
            if (movie[i]->getStatus() == "in")
            {
                movie[i]->setStatus("out");
                movie[i]->setId(id);
                movie[i]->setDate(date);
                return movie[i]->toString();
            }
        }
    }

    return "NOT_FOUND";
}

string Set::checkIn(string title, string id)
{
    Movie **movie;
    int index = binarySearch(title, 0, size, false);
    if (index != -1)
    {
        movie = moviesByProperty[index].getMovies();
        for (int i = 0; i < moviesByProperty[index].getSize(); i++)
        {
            if (movie[i]->getId() == id)
            {
                movie[i]->setStatus("in");
                movie[i]->setId("");
                movie[i]->setDate("");
                return movie[i]->toString();
            }
        }
    }
    return "NOT_FOUND";
}

int Set::getSize()
{
    return size;
}