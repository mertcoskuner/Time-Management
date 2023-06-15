//
//  main.cpp
//  mertcoskuner-hw3
//
//  Created by Mert Coskuner on 12.11.2022.
// 29120
#include <iostream>
#include <string>
#include <sstream>

#include "activity_bst.h"

using namespace std;
string fill_with_zeros(int num_zeros, const string& input){
    int zeros_to_add = num_zeros - input.length();
    if (zeros_to_add < 0) zeros_to_add = 0;
    return string(zeros_to_add, '0') + input;
}
string number_to_time(int number){
    return fill_with_zeros(2, to_string(number/100))+":"+ fill_with_zeros(2,
    to_string(number%100));
    }
tree_node* smallest_element(tree_node* n){
    while(n-> left != nullptr ){
        n= n-> left ;
    }
    return n;
}
tree_node* biggest_element(tree_node* n){
    if (n == nullptr){
        return n;

    }
    else{
        while(n-> right != nullptr ){
            n= n-> right ;
        }
        return n;
    }
    
}
bool func_for_value_sort(int time,string activity, tree_node* &n,tree_node* temp){
    //using a binary tree so, must check the values of the new nodes and place them according to this
    if(n==nullptr){// if it empty creating new node
        n = new tree_node(time,activity);
        n->parent = temp ;
    }
    else if(n->time>time){// if the value is greater then, go to left because it gets smaller to the left
        temp = n;
        return(func_for_value_sort(time,activity,n->left,temp));
    }
    else if(n->time < time){// if the value is smaller then, go to right because it gets bigger to the left
        temp = n;
        return(func_for_value_sort(time,activity,n->right,temp));
    }
    else if(n-> time == time ) {// there can't be equal values return false
        return false ;
    }
    return true;
}
bool error_check(int time,string activity){
    if(!(0<=time &&time<=2359 && time%100<59)){//checking for the time value
        cout<<"ERROR! Could not add activity "<<activity <<"due to illegal time value"<<endl;
        return false;
    }
    return true;
}

void add_activity(tree_node* &root, int time, const string &activity){
    tree_node* temp = new tree_node(time,activity);

    if (error_check(time,activity)==false){//if the function returns tue it means that, activity added succesfully
    }
    else{
        if(func_for_value_sort(time, activity, root,temp)){
            cout << "Added activity " <<  activity << " at "<< number_to_time(time)<<endl;
        }
    }
}


bool search(int time, tree_node* n, string &activity, int &start_time , int &end_time,tree_node* temp ){// searching the needed value in tree
    tree_node* biggest =biggest_element(temp) ;
    if(n == nullptr){ // if it is empty return false
        return false;
    }
    else if(n == biggest&& time>n->time){
        start_time = n->time;
        end_time = 0;
        activity = n->activity;
        return true;
    }
    else if(n == biggest&& time<n->time){
        start_time = n->parent->time;
        end_time = n->time;
        activity = n->activity;
        return true;
    }
   
    else if(n -> time == time ){ // if it is equal found the value
        if(n->right !=nullptr){
            start_time = n-> time;
            end_time = n->right ->time;
            activity = n-> activity;
            
        }
        else if(n == biggest){
            start_time = n->time;
            end_time = 0;
            activity = n->activity;
        }
        else{
            start_time = n-> time;
            end_time = n->parent ->time;
            activity = n-> activity;
        }
        return n;
    }
    else if(n-> time > time){// if it is greater go to the left side of the tree because value gets smaller trough the left side
        if((n->parent-> time < time) &&( n ->time > time )){// chekcing the time if it is between two values
            start_time = n->parent-> time;
            end_time = n ->time;
            activity = n->parent-> activity;
            return(n->parent);
        }
        return (search(time, n->left,activity, start_time ,end_time,temp));
    }
    else if(n-> time < time){// if it is smaller go to the right side of the tree because value get bigger trough the right side
        if((n->parent-> time > time) &&( n ->time < time )&& n->right == nullptr){// chekcing the time if it is between two values
            //we need to if the right cell is empty if yes it is between parent and current cell
            start_time = n-> time;
            end_time = n-> parent -> time ;
            activity = n-> activity;
            return(n-> time);
        }
        else if((n->parent-> time < time) &&( n ->time < time )&& n->right == nullptr){// chekcing the time if it is between two values
            //we need to if the right cell is empty if yes it is between parent and current cell
            start_time = n-> time;
            end_time = temp -> time ;
            activity = n-> activity;
            return(n);
        }
        else if((n->right-> time > time) &&( n ->time < time )&& n->right !=nullptr) {//if right is not empty it is between right and current cell
            start_time = n-> time;
            end_time = n->right-> time ;
            activity = n-> activity;
            return(n-> time);
            
        }
        return (search(time,n-> right,activity, start_time ,end_time,temp));
    }
   

    else{
        return false;
    }
}
void print_activity(tree_node* root, int time){
    string activity ="";
    int start_time= 0, end_time = 0 ;
    if (error_check(time,activity)==false){//if the function returns true it means that, activity added succesfully
    }
    else{
        if(!search(time,root,activity, start_time ,  end_time,root)){ //if the function returns false this means that, it is free time
            cout<<"Time: "<< number_to_time(time)<< ","<< " Activity: free"<<endl;
            
        }
        else{
            cout<<"Time: "<< number_to_time(time) << ","<< " Activity: "<<activity<<endl;

        }
    }
    
}


void print_activity_and_duration(tree_node *root, int time){
    string activity ="";
    int start_time= 0, end_time = 0 ;
    if (error_check(time,activity)==false){//if the function returns tue it means that, activity added succesfully
    }
    else{
        if(!search(time,root,activity, start_time ,  end_time,root)){
            if(root == nullptr){
                cout<<"Time period: "<<"[00:00 - 00:00]"<< ","<< " Activity: free"<<endl;

            }
            else{
                cout<<"Time period: "<<"[00:00 -"<< number_to_time(smallest_element(root)->time)<<"]"<< ","<< " Activity: free"<<endl;

            }
            
        }
        else{
            cout<<"Time period: "<<"["<< number_to_time(start_time)<< "-"<< number_to_time(end_time)<<"]"<< ","<< " Activity: " <<activity <<endl;

        }
    }
}

void search_activity( tree_node* n, string activity,tree_node* root){
    int start_time= 0, end_time = 0 ;
    if(root == nullptr){// if it is a null then it is free time
        cout<<"Time period: "<<"[00:00 - 00:00]"<< ","<< " Activity: free"<<endl;

    }
  
    if(n != nullptr) {
        search_activity(n->left,activity,root);// going to the smallest value

        if(n->activity == activity){// if  found the activity that is wanted
            
            if(!search(n->time,n,activity, n->time ,  end_time,root)){

            }
            else{
                cout<<"Time period: "<<"["<< number_to_time(n->time)<< "-"<< number_to_time(end_time)<<"]"<< ","<< " Activity: " <<activity <<endl;

            }
           
        }

        search_activity(n->right,activity,root);
        
        
    }
}

// Print the duration of every occurrence of activity 'activity'
void print_single_activity(tree_node *root, const string &activity){
    search_activity(root, activity,root);

}
void print_helper(tree_node* n, tree_node* root){// help function for printing all values
    int  end_time = 0 ;
    if(n != nullptr) {
        print_helper(n->left,root);//goes trough the smallest value
        if(!search(n->time,n, n->activity,  n->time ,  end_time,root)){
            if(n == nullptr){
                cout<<"[00:00]"<< ","<< " Activity: free"<<endl;

            }
            else{
                cout<<"[00:00 -"<<"]"<< ","<< " Activity: free"<<endl;

            }
            
        }
        else{
            cout<<"["<< number_to_time(n->time)<<"]"<< ","<< " Activity: " <<n->activity <<endl;

        }
        print_helper(n->right,root);
        
        
    }
}
// Print the starting time of every activity
void print_all_activities(tree_node *root){
     print_helper( root, root);
}

// Delete the tree pointed at by `root`
void delete_tree(tree_node *root){ // deleting the tree by traversing it otherwise we will lost the childs
    if (root == NULL){
        return;

    }
       delete_tree(root->left);
       delete_tree(root->right);
         
       delete root;
}
