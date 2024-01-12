#ifndef SET_H
#define SET_H
#include <string>
#include "MoviesByProperty.h"

using  namespace std;

class Set
{
private:
    int size = 0;
    int capacity = 10;
    MoviesByProperty *moviesByProperty = new MoviesByProperty[capacity];

    void increaseArray();
    int binarySearch(string property, int low, int high, bool is_prefix);
    string findByPropertyPartial(string prefix, string suffix);
    string findByPropertyPartial(string prefix);
public:
    void add(string property, Movie *movie);
    string findByProperty(string property);
    int getSize();
    string checkIn(string title, string id);
    string checkOut(string title, string id, string date);
};

#endif
