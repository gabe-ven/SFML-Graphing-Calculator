#include <iostream>
#include "./includes/animate/animate.h"
#include "./includes/animate/graph_info.h"
using namespace std;

int main()
{
    Graph_info info;

    animate game(&info);

    game.run();

    cout << endl
         << endl
         << "------ MAIN EXITING --------------------------" << endl;
    return 0;
}
