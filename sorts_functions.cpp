#include <stdio.h>
#include <stdlib.h>
#include "sorts_functions.h"
#include "my_asserts.h"


bool comp_int(const void* x1, const void* x2){
    my_assert(x1 != NULL, printf("pointer to first compared element is NULL\n"); return false);
    my_assert(x2 != NULL, printf("pointer to second compared element is NULL\n"); return false);
    my_assert(x1 != x2, printf("you compare one element with himself\n"); return false);
    if(*((const int*)(x1)) > *((const int*)(x2))){
        return true;
    }
    return false;
}
bool comp_str(const void* x1, const void* x2){
    my_assert(x1 != NULL, printf("pointer to first compared element is NULL\n"); return false);
    my_assert(x2 != NULL, printf("pointer to second compared element is NULL\n"); return false);
    int index = 0;

    while((*((*((const char*const*)x1)) + index) != '\n') && (*((*((const char*const*)x1)) + index) != '\0') && (*((*((const char*const*)x2)) + index) != '\n') && (*((*((const char*const*)x2)) + index) != '\0')){
        if(*((*((const char*const*)x1)) + index) > *((*((const char*const*)x2)) + index)){
            return true;
        }
        if(*((*((const char*const*)x1)) + index) < *((*((const char*const*)x2)) + index)){
            return false;
        }
        index++;
    }
    if(*((*((const char*const*)x1)) + index) == '\n' || *((*((const char*const*)x2)) + index) == '\0'){
        return false;
    }
    return false;
}


int len_of_mass(const int size_of_element, const void* start, const void* finish){
    my_assert(size_of_element > 0, printf("size_of_element in sort smaller than zero\n"); return -1);
    my_assert(start <= finish, printf("start of sort not before the end\n"); return -1);
    my_assert(start != NULL, printf("start of sort is NULL\n"); return -1);
    my_assert(finish != NULL, printf("end of sort is NULL\n"); return -1);

    return  ((int)((const char*)finish - (const char*)start) / size_of_element);
}

void my_swap(const int size_of_element, void* x1, void* x2){
    my_assert(size_of_element > 0, printf("size_of_element in sort smaller than zero\n"); return);
    my_assert(x1 != x2, printf("you swap one element with himself\n"); return);
    my_assert(x1 != NULL, printf("pointer to first swapped element is NULL\n"); return);
    my_assert(x2 != NULL, printf("pointer to second swapped element is NULL\n"); return);

    char ch_buff = '\0';
    for(int i = 0; i < size_of_element; i++){
        ch_buff = *((char*)x1 + i);
        *((char*)x1 + i) = *((char*)x2 + i);
        *((char*)x2 + i) = ch_buff;
    }
}

void bubble_sort(const int size_of_element, void* start, void* finish, bool(comp(const void*, const void*))){
    my_assert(size_of_element > 0, printf("size_of_element in sort smaller than zero\n"); return);
    my_assert(start <= finish, printf("start of sort not before the end\n"); return);
    my_assert(start != NULL, printf("start of sort is NULL\n"); return);
    my_assert(finish != NULL, printf("end of sort is NULL\n"); return);

    bool was_swaps = true;
    int len = len_of_mass(size_of_element, start, finish);

    while(was_swaps){


        was_swaps = false;
        for(int i = 0; i < len - 1; i++){
            my_assert((char*)start + (i + 1) * size_of_element < finish, printf("exit from finish\n"); return);
            if(comp((const char*)start + i * size_of_element, (const char*)start + (i + 1) * size_of_element)){
                my_swap(size_of_element, (char*)start + i * size_of_element, (char*)start + (i + 1) * size_of_element);
                was_swaps = true;
            }

        }
    }
}

void choice_sort(const int size_of_element, void* start, void* finish, bool(comp(const void*, const void*))){
    my_assert(size_of_element > 0, printf("size of element in sort smaller than zero\n"); return);
    my_assert(start <= finish, printf("start of sort not before the end\n"); return);
    my_assert(start != NULL, printf("start of sort is NULL\n"); return);
    my_assert(finish != NULL, printf("end of sort is NULL\n"); return);

    int index_of_min = 0;
    int count_of_elements = len_of_mass(size_of_element, start, finish);

    for(int start_index = 0; start_index < count_of_elements - 1; start_index++){
        for(int i = start_index; i < count_of_elements; i++){
            my_assert((char*)start + index_of_min * size_of_element < finish, printf("exit from finish\n"); return);
            my_assert((char*)start + i * size_of_element < finish, printf("exit from finish\n"); return);
            if(index_of_min != i && comp((char*)start + index_of_min * size_of_element, (char*)start + i * size_of_element)){
                index_of_min = i;
            }
        }
        if(start_index != index_of_min){
            my_swap(size_of_element, (char*)start + start_index * size_of_element, (char*)start + index_of_min * size_of_element);
        }
        index_of_min = start_index + 1;
    }
}

void quick_sort(const int size_of_element, void* start, void* finish, bool(comp(const void*, const void*))){
    int count_of_elements = len_of_mass(size_of_element, start, finish);
    if(count_of_elements < 2){
        return;
    }
    int target = rand() % count_of_elements;
    int left = 0;
    int right = count_of_elements - 1;

    while(left < right){
        while(left < right && (!comp((char*)start + left * size_of_element, (char*)start + target * size_of_element) && (target != left))){
            left++;
        }
        while(left < right && (!comp((char*)start + target * size_of_element, (char*)start + right * size_of_element) && (target != right))){
            right--;
        }
        if(left < right){
            if(target == right){
                target = left;
            }
            else if(target == left){
                target = right;
            }
            my_swap(size_of_element, (char*)start + left * size_of_element, (char*)start + right * size_of_element);
        }
    }
    quick_sort(size_of_element, start, (char*)start + target * size_of_element, comp);
    quick_sort(size_of_element, (char*)start + target * size_of_element, finish, comp);
}
