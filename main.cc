#include "KMeans.hpp"

int main()
{
    vector<Item> training_set = {
        Item(0,{1,1}),
        Item(0,{2,2}),
        Item(0,{3,3}),
        Item(0,{4,4}),
        Item(0,{5,5}),
    };  
    KMeans k;
    k.run(training_set, 2, 10);
}
