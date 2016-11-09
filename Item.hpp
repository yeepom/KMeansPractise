#ifndef ITEM.HPP
#define ITEM.HPP
#include<vector>
#include<cmath>
#include<iostream>
#include<algorithm>
using std::vector;
using std::cout;
using std::endl;


class Item
{
public:
    Item(int category, vector<double> inputs):category_(category),inputs_(inputs){}
    vector<double>& inputs(){return inputs_;}
    int category(){return category_;}
    void set_category(double category){category_ = category;} 
    double distanceWithAnother(Item &);
    void print_Item();
protected:
    vector<double> inputs_;
    int category_;
};
double Item::distanceWithAnother(Item & second)
{
    vector<double>::iterator first_it = inputs_.begin();
    vector<double>::iterator second_it = second.inputs().begin();
    double distaceSquare = 0.0;
    for(; first_it != inputs_.end() && second_it != second.inputs().end(); first_it++, second_it++) 
        distaceSquare += (*first_it - *second_it) * (*first_it - *second_it);
    return sqrt(distaceSquare);
}
void Item::print_Item()
{
    cout<<" the inputs of this item is : (";
    std::copy(inputs_.begin(), inputs_.end(), std::ostream_iterator<double>(cout, " ")); 
    cout<<")";
    cout<<",this item belongs to "<<category_<<endl;
}
#endif
