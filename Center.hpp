#ifndef CENTER.HPP
#define CENTER.HPP 
#include<functional>
#include "Item.hpp"
using std::transform;

class Center : public Item
{
public:
    Center(int category, vector<double> inputs, int item_numbers, vector<double> inputs_sum, double inputs_errors):Item(category, inputs),item_numbers_(item_numbers),inputs_sum_(inputs_sum), inputs_errors_(inputs_errors){}
    void accu_item_numbers() ;
    void accu_inputs_sum(vector<double>) ;
    void accu_reset();
    void update() ;
    double get_inputs_errors() const {return inputs_errors_;}
    void print_Center();
private:
    double inputs_errors_;
    int item_numbers_;
    vector<double> inputs_sum_; 
};

void Center::update()
{
    vector<double>::iterator old_inputs_it = inputs_.begin();
    vector<double>::iterator inputs_sum_it = inputs_sum_.begin();
    double errors = 0.0;
    for(; old_inputs_it != inputs_.end() && inputs_sum_it != inputs_sum_.end(); old_inputs_it++, inputs_sum_it++)
    {
        errors += (*old_inputs_it - (*inputs_sum_it) / item_numbers_) * (*old_inputs_it - (*inputs_sum_it) / item_numbers_);       
    } 
    inputs_errors_ = sqrt(errors); 
    transform(inputs_sum_.begin(), inputs_sum_.end(), inputs_.begin(), [this](double input){return input / (*this).item_numbers_;}); 
}
void Center::accu_item_numbers()
{
    item_numbers_++;
}
void Center::accu_inputs_sum(vector<double> another_inputs)
{
   transform(inputs_sum_.begin(), inputs_sum_.end(), another_inputs.begin(), inputs_sum_.begin(), std::plus<double>()); 
}
void Center::accu_reset()
{
    item_numbers_ = 0;
    inputs_sum_.assign(inputs_sum_.size(),0.0);
}
void Center::print_Center()
{
    cout<<" the center's inputs is (";
    std::copy(inputs_.begin(), inputs_.end(), std::ostream_iterator<double>(cout, " "));
    cout<<"),";
    cout<<" the category it represents is "<<category_<<". ";
    cout<<"the center's inputs sum is (";
    std::copy(inputs_sum_.begin(), inputs_sum_.end(), std::ostream_iterator<double>(cout, " "));
    cout<<"),";
    cout<<" the number of items is "<<item_numbers_<<endl; 
}
#endif
