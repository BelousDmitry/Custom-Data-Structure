#ifndef VIDEOSTORE_H
#define VIDEOSTORE_H
#include <string>
#include "Movie.h"
#include "Set.h"

using  namespace std;

class Videostore
{
private:
    Movie *head = NULL;
    Set movies_by_title;
    Set movies_by_director;
    Set movies_by_year;
    Set movies_by_actor;
    int list_size = 5;
    void show(string movies);
    void loadFile(string file_name);
    string findMovies(string input, int filter);
    string getWord(string &sentence);
    void clearScreen();
    void showInstructions();

public:
    void run();


    
};

#endif
