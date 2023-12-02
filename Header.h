#pragma once

#ifndef HEADER_H
#define HEADER_H

#include <iostream>
#include <string>
#include <sstream>
#include <cmath>
#include <cstdlib>
#include <functional>
#include <ctime>

using namespace std;

// dynamic array class template
template<typename T>
class dynamic_array {
public:
    T* array;
    int size;
    int capacity;

    // destructor of "dynamic_array" class for memory allocated by the "object_gen" method in the "random_data_gen" class
    ~dynamic_array() {
        for (int i = 0; i < size; i++) {
            delete array[i];
        }
        delete[] array;
    }

    // add at the end ofthe dynamic array
    void add(const T& element) {
        if (size == capacity) {
            resize_array();
        }

        array[size++] = element;
    }
    
    // resize the dynamic array
    void resize_array() {
        int new_capacity = (capacity == 0) ? 1 : capacity * 2;
        T* new_array = new T[new_capacity];

        for (int i = 0; i < size; i++) {
            new_array[i] = array[i];
        }

        if (array) {
            delete[] array;
        }

        array = new_array;
        capacity = new_capacity;
    }

    // converting dynamic array elements to a string - all elements
    string to_string_full() {
        string result = "";

        for (int i = 0; i < size; i++) {
            stringstream ss;
            ss << array[i]; // converting the elements to a string
            result += ss.str();

            if (i < size - 1) {
                result += " ";
            }
        }

        return result;
    }

    // to_string_short - printing only the first and last 2 elements of the dynamic array
    string to_string_short() {
        string result = "";
        const int maxElements = 2; // max number of elements to print from either the beginning or end of the dynamic array
        int sizeLeft = size; // remaining number of elements of the dynamic array

        for (int i = 0; i < size; i++) {
            if (i >= maxElements && sizeLeft > maxElements) {
                if (i >= size - maxElements) {
                    stringstream ss;
                    ss << array[i];
                    result += ss.str();

                    if (i < size - 1) {
                        result += " ";
                    }
                }
                // the middle of the array
                else if (i == maxElements) {
                    result += " . . . ";
                }
            }
            // when the maximum number of elements at the beginning can't be reached or it's the end of the array
            else {
                stringstream ss;
                ss << array[i];
                result += ss.str();

                if (i < size - 1) {
                    result += " ";
                }
            }

            sizeLeft--;

            if (i >= size - 1) {
                break;
            }
        }

        return result;
    }

    // returning the i-th element of the dynamic array
    T get_element(int index) {
        if (index >= 0 && index < size) {
            return array[index];
        }
        else {
            throw out_of_range("index value is out of range.");
        }
    }

    // replace the i-th element of the dynamic array
    void set_element_at_index(int index, const T& new_element) {
        if (index >= 0 && index <= size) {
            array[index] = new_element;
        }
        else {
            throw out_of_range("index value is out of range.");
        }
    }

    // in-place bubble sorting the dynamic array
    // a comparator to compare elements and determine their order
    // "compare = less<T>()" - sorting in ascending order
    void bubble_sort(function<bool(const T&, const T&)> compare = less<T>()) {
        for (int i = 0; i < size - 1; i++) {
            for (int j = 0; j < size - i - 1; j++) {
                if (compare(array[j + 1], array[j])) {
                    // swapping array[j] and array[j + 1]
                    T temp = array[j];
                    array[j] = array[j + 1];
                    array[j + 1] = temp;
                }
            }
        }
    }   

    // delete the entire dynamic array
    void clear() {
        for (int i = 0; i < size; i++) {
            delete array[i];
        }
        delete[] array;
        array = nullptr;
        size = 0;
        capacity = 0;
    }
};


// class data type
class object {
public:
    int field_1;
    string field_2;
};

// overloading the << operator to print an "object" instance
std::ostream& operator<<(std::ostream& os, const object& obj) {
    os << obj.field_1 << " " << obj.field_2; // output values from both data fields of the "object" instance
    return os;
}

// overloading the << operator to print an "object" pointer
std::ostream& operator<<(std::ostream& os, const object* obj) {
    os << obj->field_1 << " " << obj->field_2; // output values from both data fields of the "object" pointer
    return os;
}

// a lambda function for "object" class instances comparison for the bubble sort
// comparing two "object" class pointers on the basis of their "field_1" values
auto lambdaCompare = [](const object* a, const object* b) {
    return a->field_1 < b->field_1;
    };

// generating data for different data types
class random_data_gen {
public:
    // char
    char char_gen() {
        char chars[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
        return chars[rand() % 26];
    }

    // int
    static int int_gen() {
        return rand() % 100;
    }

    // string
    string string_gen() {
        static const string imie[] = {
            "Piotr",
            "Joanna",
            "Marta",
            "Anna",
            "Aleksander",
        };
        int random_index = rand() % 5;
        return imie[random_index];
    }

    // class*
    object* object_gen() {
        object* obj = new object;
        obj->field_1 = int_gen();
        obj->field_2 = string_gen();
        return obj;
    }
};
#endif
