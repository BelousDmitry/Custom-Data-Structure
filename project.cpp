#include "Videostore.h"
int main()
{
    Videostore *videostore = new Videostore();
    videostore->run();
    delete videostore;
}