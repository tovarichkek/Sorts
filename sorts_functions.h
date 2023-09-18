#pragma once

bool comp_int(const void* x1, const void* x2);
bool comp_str(const void* x1, const void* x2);
int len_of_mass(const int size_of_element, const void* start, const void* finish);
void my_swap(const int size_of_element, void* x1, void* x2);

void bubble_sort(const int size_of_element, void* start, void* finish, bool(comp(const void*, const void*)));
void choice_sort(const int size_of_element, void* start, void* finish, bool(comp(const void*, const void*)));
void quick_sort(const int size_of_element, void* start, void* finish, bool(comp(const void*, const void*)));
