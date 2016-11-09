#ifndef KMEANS.HPP
#define KMEANS.HPP
#include<stdexcept>
#include<numeric>
#include "Center.hpp"

class KMeans
{
public:
    KMeans(int cluster_numbers = 2, double threshold = 1.0):cluster_numbers_(cluster_numbers),threshold_(threshold),centers(vector<Center>{}){}
    double threshold(){return threshold_;}
    void run(vector<Item> &, int, int);
    void initialCenters(vector<Item> &);
    void assignment(vector<Item> &);
    double updateCenters(vector<Item> &);   
    void printItems(vector<Item> &);
    void printCenters();
private:
    int cluster_numbers_;
    double threshold_;
    vector<Center> centers;
};

void KMeans::run(vector<Item> &training_set, int cluster_numbers, int max_iterations)
{
    cluster_numbers_ = cluster_numbers;
    initialCenters(training_set);
    size_t current_iteration = 0;
    while(current_iteration != max_iterations)
    {
        assignment(training_set);
        double errors = updateCenters(training_set); 
        if (errors <= threshold_)
            break;
        current_iteration++;
    } 
}

void KMeans::initialCenters(vector<Item> &training_set)
{
    if(training_set.size() <= cluster_numbers_)
        std::invalid_argument("the size of centers should be smaller than training_set");
    vector<Item>::iterator it = training_set.begin();
    size_t category = 0;
    centers.clear();
    while(category != cluster_numbers_)
    {
        centers.push_back(Center(category, (*it).inputs(), 0, (*it).inputs(),0));
        category++;
        it++;
    }
    printCenters();
}

void KMeans::assignment(vector<Item> &training_set)
{
    if(training_set.size() <= cluster_numbers_)
        std::invalid_argument("the size of centers should be smaller than training_set");
    vector<Item>::iterator it = training_set.begin();    
    for(; it != training_set.end(); it++)
    {
        vector<Center>::iterator centers_it = centers.begin();
        double min_distance = std::numeric_limits<double>::max();
        for(; centers_it != centers.end(); centers_it ++)
        {
            double distance = (*it).distanceWithAnother(*centers_it); 
            if(distance < min_distance)
            {
                min_distance = distance;
                (*it).set_category((*centers_it).category()); 
            } 
        } 
    }
    cout<<"after assignment"<<endl;
    printCenters();
    printItems(training_set);
}

double KMeans::updateCenters(vector<Item> &training_set)
{
    if(training_set.size() <= cluster_numbers_)
        std::invalid_argument("the size of centers should be smaller than training_set");
    vector<Center>::iterator centers_it = centers.begin();
    for(; centers_it != centers.end(); centers_it++)
    {
        (*centers_it).accu_reset();
        vector<Item>::iterator it = training_set.begin();
        for(;it != training_set.end(); it++)
        {
            if((*centers_it).category() == (*it).category())
            {
                (*centers_it).accu_item_numbers();
                (*centers_it).accu_inputs_sum((*it).inputs()); 
            }
        }
    }
    
    double centers_inputs_errors = 0.0;
    centers_it = centers.begin();
    for(;centers_it != centers.end();centers_it++)
    {
        (*centers_it).update();
        centers_inputs_errors += (*centers_it).get_inputs_errors();
    } 
    cout<<"after update"<<endl;
    printCenters();
    printItems(training_set);
    return centers_inputs_errors;
}

void KMeans::printItems(vector<Item> &training_set)
{
    vector<Item>::iterator it = training_set.begin();
    for(; it != training_set.end(); it++)
    {
        (*it).print_Item();
    } 
}
void KMeans::printCenters()
{
    vector<Center>::iterator centers_it = centers.begin();
    for(; centers_it != centers.end(); centers_it++)
    {
        (*centers_it).print_Center();
    }
}
#endif
