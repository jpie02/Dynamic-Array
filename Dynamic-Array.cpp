//ALGO2 IS1 220A LAB02
//JAGODA PIETRUSEWICZ
//pj53823@zut.edu.pl

#include "Header.h"

int main()
{
    srand(123); // seeding the random number generator

    // creating an instance of dynamic_array class
    dynamic_array<object*>* dynamic_array_inst = new dynamic_array<object*>();

    random_data_gen generator; // generating random data

    const int order = 5; // order of magnitude for the size of added data
    const int n = pow(10, order); // size of data
   
    // to_string -------------------------------------------------------------------------------
  
    //// to_string_full - printing the entire dynamic array
    //string array_string_full = dynamic_array_inst->to_string_full();
    //cout << array_string_full << endl;

    //// to_string_short - printing only the first 2 and last 2 elements of the dynamic array
    //string array_string_short = dynamic_array_inst->to_string_short();
    //cout << array_string_short << endl;

    // adding at the end of the array -----------------------------------------------------------
    clock_t t1 = clock(); // start of the timer for total time

    double max_time_per_element = 0.0;
    int worst_element_index = -1; // "-1" because no worst element has been observed yet

    for (int i = 0; i < n; i++) {
        object* new_object = generator.object_gen();
        clock_t t1_element = clock(); // start of the timer for single operation time
        dynamic_array_inst->add(new_object);
        clock_t t2_element = clock(); // end of the timer for single operation time

        // calculating the single operation time in milliseconds
        double time_per_element = static_cast<double>(t2_element - t1_element) / CLOCKS_PER_SEC * 1000.0;

        // setting the worst time for adding a single element
        if (time_per_element > max_time_per_element) {
            max_time_per_element = time_per_element;
            worst_element_index = i;
        }
    }

    clock_t t2 = clock(); // end of the timer for total time

    // to_string_short - printing only the first and last 2 elements of the dynamic array
    string array_string_short1 = dynamic_array_inst->to_string_short();
    cout << array_string_short1 << endl;

    cout << " " << endl;

    // calculating the total time in milliseconds
    double total_time = static_cast<double>(t2 - t1) / CLOCKS_PER_SEC * 1000.0;

    // calculating the average time per operation in seconds
    double average_time_per_operation = total_time / n;

    cout << "Total time: " << total_time << " ms" << endl;
    cout << "Average time per operation: " << average_time_per_operation << " ms" << endl;

    cout << " " << endl;

    if (worst_element_index >= 0) {
        cout << "The worst time for a single operation: " << max_time_per_element << " ms" << endl;
        cout << "Index of the element with the worst time: " << worst_element_index << endl;
    }

    cout << " " << endl;

    // returning the i-th element of the dynamic array ------------------------------------------
    int get_index = 5;

    try {
        object* searched_for_element = dynamic_array_inst->get_element(get_index);
        cout << "Element at index " << get_index << ": " << *searched_for_element << endl;
    }
    catch (const std::out_of_range& e) {
        cout << "Error: " << e.what() << endl; // what() - returns a description of the exception
    }

    string array_string_short2 = dynamic_array_inst->to_string_short();
    cout << array_string_short2 << endl;

    cout << " " << endl;

    // replace the i-th element of the dynamic array --------------------------------------------
    int replace_index = 9;
    object* new_element = generator.object_gen(); // generate new data for the replacement

    try {
        dynamic_array_inst->set_element_at_index(replace_index, new_element);
        cout << "Element at index " << replace_index << " replaced successfully." << endl;
    }
    catch (const std::out_of_range& e) {
        cout << "Error: " << e.what() << endl; // what() - returns a description of the exception
    }

    string array_string_short3 = dynamic_array_inst->to_string_short();
    cout << array_string_short3 << endl;

    cout << " " << endl;

    // in-place bubble sorting the dynamic array -------------------------------------------------
    dynamic_array_inst->bubble_sort(lambdaCompare);

    string array_string_short4 = dynamic_array_inst->to_string_short();
    cout << array_string_short4 << endl;

    cout << " " << endl;
    
    // deallocate used memory and delete the dynamic array ---------------------------------------
    //delete dynamic_array_inst;
    dynamic_array_inst->clear();

    return 0;
}