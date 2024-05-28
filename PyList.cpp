#include<any> // any class
#include<vector>
#include<stdexcept> // Exception objects
#include<iostream>
#include<string>
#include<algorithm> // imported to use reverse method
using namespace std;

class PyList{
private:
	vector<any> data; // vector 'data' that can store data of any type
public:

	// Append element of any type to list
	void append(const any& value){
		data.push_back(value); //append value at the end of data
	}

	// Insert element of any type to the list at specific position
	void insert(size_t index, const any& value){
		// Check if the index is out of range
		if(index >= data.size()){
			throw out_of_range("Index out of range");
		}
		data.insert(data.begin() + index, value);
	}

	// Remove and return element at specified index
	any pop(size_t index = -1){ // -1 as default index in case parameter is not passed

		if(index == static_cast<size_t>(-1)){
			index = data.size() - 1;
		}
		if(index >= data.size()){  // Check if index out of range
			throw out_of_range("Index out of range");
		}

		any value = data[index];
		data.erase(data.begin() + index);
		return value;
	}

	// Access the element at specified index
	any& operator[](size_t index){
		if(index >= data.size()){
			throw out_of_range("Index out of range");
		}
		return data[index];
	}

	// Get number of elements in the list 
	size_t size() const {
		return data.size();
	}

	// Function to remove all elements from the list
	void clear(){
		data.clear();
	}

	// Helper function to compare values of different types
	bool compareValues(const any& lhs, const any& rhs) {
    	if (lhs.type() == typeid(int) && rhs.type() == typeid(int)) {
        	return any_cast<int>(lhs) == any_cast<int>(rhs);
    	} else if (lhs.type() == typeid(double) && rhs.type() == typeid(double)) {
        	return any_cast<double>(lhs) == any_cast<double>(rhs);
    	} else if (lhs.type() == typeid(string) && rhs.type() == typeid(string)) {
        	return any_cast<string>(lhs) == any_cast<string>(rhs);
    	} else if (lhs.type() == typeid(const char*) && rhs.type() == typeid(const char*)) {
        	return any_cast<const char*>(lhs) == any_cast<const char*>(rhs);
    	} else {
        	return false; // Types are not directly comparable
    	}
	}

	// Function to count the occurences of a value in a list
	size_t count(const any& value){
		size_t num = 0;
		for(const auto& item : data){
			// Check if the item andd value have same type
			if(item.type() == value.type()){
				// Cpmare value with item if the are cmpatible
				if(compareValues(value, item)){
					num++;
				}
			}
		}
		return num;
	}

	// Function to extend the list by adding elements from other list
	void extend(const PyList& other){
		// Insert the elements of other list from start to end at the end of data list
		data.insert(data.begin() + data.size(), other.data.begin(), other.data.end());
	}

	// Function to remove the element from first occurence
	void remove(const std::any& value){
    	for(auto it = data.begin(); it != data.end(); ++it){
        	if(it->type() == value.type()){
            	if(compareValues(value, *it)){
                	data.erase(it);
                	break;
            	}
        	}
    	}
    }


	// Reverse the order of elements in the list
	void reverse(){
		std::reverse(data.begin(), data.end());
	}

	// Function to sort the elements of list
	void sort() {
    	// Define a lambda function for custom sorting
    	auto customLess = [](const std::any& a, const std::any& b) -> bool {
        	if (a.type() == b.type()) {
            	// If types are the same, compare based on type
            	if (a.type() == typeid(int)) {
                	return std::any_cast<int>(a) < std::any_cast<int>(b);
            	} else if (a.type() == typeid(double)) {
                	return std::any_cast<double>(a) < std::any_cast<double>(b);
            	} else if (a.type() == typeid(std::string)) {
                	return std::any_cast<std::string>(a) < std::any_cast<std::string>(b);
            	}
        	} else {
            	// If types are different, compare based on type order
            	return a.type().before(b.type());
        	}
        	return false; // Default: unable to compare or different types
    	};
    	std::sort(data.begin(), data.end(), customLess);
	}


};



// Helper function toprint any value
void print_any(const any& val){
	if(val.type() == typeid(int)){
		cout<< any_cast<int>(val) << '\n';
	}
	else if(val.type() == typeid(double)){
		cout<< any_cast<double>(val) << '\n';
	}
	else if(val.type() == typeid(string)){
		cout<< any_cast<string>(val) << '\n';
	}
	else if (val.type() == typeid(const char*)) {
        cout<< any_cast<const char*>(val) << '\n';
    }
    else{
		cout<<"Unknown type\n";
	}
}

// Example Usage
int main(){
	PyList mylist;
	PyList list2;
	list2.append(500);
	list2.append(600);
	list2.append("Malik");
	list2.append(700);
	mylist.append(10);
	mylist.append(6.28);
	mylist.append("Hello Junaid!");
	mylist.append(100);
	mylist.append("hi");
	mylist.append(10);

	// Printing Original List
	cout<<"== Original List ==\n";
	for(size_t i = 0; i < mylist.size(); i++){
		print_any(mylist[i]);
	}
	
	cout<<"\n== Count Method ==";
	// Calling count method to count the occurence of elements
	cout<<"\nCount of 10 : "<<mylist.count(10)<<"times\n";

	// Calling Pop method to remove element from specific index
	cout<<"\n== Pop Method ==";
	any popped_value = mylist.pop(2);
	cout<<"\nPopped: ";
	print_any(popped_value);

	// Calling extend method to concatenate other list at the end of originnal list
	mylist.extend(list2);
	cout<<"\n== Extended List ==\n";
    for(size_t i = 0; i < mylist.size(); i++){
		print_any(mylist[i]);
	}

	// Calling remove method to remove a specific element
	cout<<"\n== Remove Method ==\nList with Malik removed: \n";
	mylist.remove("Malik");
	for(size_t i = 0; i < mylist.size(); i++){
		print_any(mylist[i]);
	}

	// Calling reverse method to reverse the order of elements in the list
	cout<<"\n== Reverse Method == \nList Order Reversed: \n";
	mylist.reverse();
	for(size_t i = 0; i < mylist.size(); i++){
		print_any(mylist[i]);
	}

	// Sort method to sort the list
	cout<<"\n== Sort Method ==\nSorted List: \n";
	mylist.sort();
	for(size_t i = 0; i < mylist.size(); i++){
		print_any(mylist[i]);
	}
	cout<<"\n== Clear Method ==";
	// Clear method removes all elements from the list
	mylist.clear();
	cout<<"\nAfter clear, List size : "<<mylist.size()<<endl;

	return 0;
} 