#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <algorithm>
//end library calls

using namespace std;

void init(int arr[],int n);
void insert_sort(int arr[],int n);
void quick_sort(int arr[],int start, int ending);//recursive quicksort
int partit (int arr[], int start, int ending);//partition
void construct_heap(int arr[], int n);
void heap_sort(int arr[], int n);
void MERGE(int arr[], int MIN, int center, int MAX);
void merge_sort(int arr[],int MIN,int MAX);
void print_arr(int arr[],int n);
//end function definitions

int main()
{
    FILE *infile;

    //float starting_time,ending_time,elapsed_time;//to measure the time of functions
    int n;//input size of array
    int *arr;
    int initial_starting = 0;//starting point for quick sort
    int initial_ending;
    int lower_index = 0;
    int upper_index;
    clock_t end_time, elapsed_time,start_time;

    string sorting_choice;

    cout<<"Please enter the number of elements: ";
    cin>>n;
    arr = new int[n];
    initial_ending = n;
    upper_index = n;
    init(arr,n);//initializes the array based on weather random or not

    infile = fopen("input.txt","r");
    if (infile == NULL)
    {
       // cout<<"Unable to open file"<<endl;
    }

    cout<<endl<<"Please enter of of the following sorting algorithms acyronyms:"<<endl<<endl;
    cout<<"Insertion Sort: IS"<<endl<<"Quick Sort: QS"<<endl<<"Heap Sort: HS"
        <<endl<<"Merge Sort: MS"<<endl<<endl<<"Choice: ";

    cin>>sorting_choice;
    while(sorting_choice != "IS" && sorting_choice != "QS" && sorting_choice != "HS" && sorting_choice != "MS")
    {
        cout<<"Invalid choice. Choose again."<<endl<<"IS, QS, HS, or MS: ";
        cin>>sorting_choice;
    }//end while

    //print_arr(arr,n);//prints intial unsorted array

    if(sorting_choice == "IS")
    {
        start_time = clock();

        insert_sort(arr,n);

        end_time = clock();
        elapsed_time = end_time - start_time;
    }//end if

    else if(sorting_choice == "QS")
    {
        start_time = clock();

        quick_sort(arr,initial_starting,initial_ending);

        end_time = clock();
        elapsed_time = end_time - start_time;
    }//end else if

    else if(sorting_choice == "HS")
    {
        start_time = clock();

        construct_heap(arr,n);
        heap_sort(arr,n);

        end_time = clock();
        elapsed_time = end_time - start_time;
    }//end else if

    else if(sorting_choice == "MS")
    {
        start_time = clock();

        merge_sort(arr,lower_index,upper_index);

        end_time = clock();
        elapsed_time = end_time - start_time;
    }//end else if

    else
        cout<<"ERROR!!"<<endl<<endl;

    //print_arr(arr,n);

    cout<<"It took "<<elapsed_time<<" miliseconds to complete this sort"<<endl;
   //cout<<clock();
}//end main

void insert_sort(int arr[],int n)
{


    int i,j;//loop itterations
    int check = 0;//initialization
    for(i = 1; i<n; i++)//go through each element
    {
        j = i;//start at the end of the sorted part
        //check = arr[i];//compare check with the numbers
        while(arr[j-1] > arr[j] && j >0)
        {
            check = arr[j];//temporarily saves that value
            arr[j] = arr[j-1];//move the values to the right by one
            arr[j-1] = check;
            j = j - 1;
        }//end while
    }//end for
}

void quick_sort(int arr[],int start,int ending)
{
    int part,temp_part;//partition

    if(start<ending)
    {
        part=partit(arr,start,ending);//finding piviot

        temp_part= part - 1;
        quick_sort(arr,start,temp_part);

        temp_part = part + 1;
        quick_sort(arr,temp_part,ending);

        //the purpose of calling quick sort twice
        //is to divide the sub arrays in to two lists
    }
}

int partit (int arr[], int start, int ending)
{
    int pivot = arr[start];
    int point = start;//point starts at the beginning
    int index = start + 1;//index of the sub array

    while(index<=ending)
    {
        if(pivot>arr[index])//if the pivot is greater than that
                            //element in the sub array
        {
            arr[point] = arr[index];
            arr[index] = arr[point + 1];
            arr[point+ 1] = pivot;

            point++;
        }//end if

        index++;//next index
    }//end while

    return  point;
}

void construct_heap(int arr[], int n)//building a heap from an array
{
    int i,j,middle_i, check;
    for(i = 1; i<n;i++)
    {
        j = i;
        middle_i = (i-1);
        middle_i /=2;//look at the middle term
        check = arr[i];//value to be compared

        while(arr[middle_i] <= check -1 && j>=1)
        {
            arr[j]=arr[middle_i];
            j = middle_i;
            middle_i = (j-1)/2;
        }//end while

        arr[j] = check;
    }//end for
}

void heap_sort(int arr[], int n)
{
    int buffer;
    int trace_back=n-1;//to stay within the array bounds

    while(trace_back>0)
    {
        buffer = arr[trace_back];//temporarily saves the value
        arr[trace_back] = arr[0];
        arr[0] = buffer;

        construct_heap(arr,trace_back);
        trace_back-=1;//tracing backwards
    }//end for
}

void MERGE(int arr[], int MIN, int center, int MAX)//
{
    int counter = 0;
    int median = MAX - MIN +1;//finds the median
    int *sub_arr = new int[median];
    int MIN_i=MIN;//minimum index of the array
    int center_i=center+1;
    bool keepgoing = (center_i < MAX + 1 && MIN_i < center + 1);//a cehck

    while(keepgoing)
    {
        if (arr[center_i] > arr[MIN_i])
        {
            sub_arr[counter++] = arr[MIN_i++];
            //counter++;
            //MIN_i++;
        }
        else if(arr[center_i] < arr[MIN_i])
        {
            sub_arr[counter++] = arr[center_i++];
            //center_i++;
            //counter++;
        }
        else
            cout<<"error!!!!!!"<<endl;

        keepgoing = (center_i < MAX + 1 && MIN_i < center + 1);
    }

    if (MIN_i <= center)
    {
        while(MIN_i <= center)
        {
            sub_arr[counter++] = arr[MIN_i++];
        }
    }

    if (center_i <= MAX)
    {
        while(center_i <= MAX)
        {
            sub_arr[counter++] = arr[center_i++];
        }
    }

    for (counter = MIN; counter <= MAX; ++counter)
        arr[counter] = sub_arr[counter-MIN];

    delete[] sub_arr;//frees the dynamically created sub array
    return;
}

void merge_sort(int arr[],int MIN,int MAX)
{
    bool check = MIN < MAX;
    int center;
    if(check)
    {
        center = (MIN + MAX)/2;//gets the center value of the array
        merge_sort(arr,MIN,center);
        merge_sort(arr,center + 1,MAX);
        MERGE(arr,MIN,center,MAX);//combines all values and puts it into an arrau
    }
    return;
}

void init(int arr[],int n)
{
    string choice;//yes or no choice
    int temp;//temporary random value
    bool keepgoing = true;
    bool flag;//a flag for a repeated random
    bool not_unique_rand=true;//checks to see if there is a repeated random variable

    srand(time(NULL));//multiple random numbers every start up

    cout<<"Would you like a sorted array? yes/no: ";

    while(keepgoing)
    {
        cin>>choice;

        if(choice == "yes")
        {
            for(int i = 0;i<n;i++)
                arr[i] = i;

            keepgoing = false;
        }//end if
        else if(choice == "no")
        {
            for(int i = 0;i<n;i++)
            {
                not_unique_rand = true;//resets the boolean
                while(not_unique_rand)//keeps checking until a unique random number has been made;
                {
                  flag = false;//reset the flag
                  temp = rand()%20000;//random values from 1 to n and assigns it to a temporary variable
                    for(int j = 0; j<=i-1;j++)//a forloop to check every element for repeated numbers
                    {
                        if(temp == arr[j])
                          flag = true;//flag has been raised
                    }//end nested for

                    if(flag == true)//flag has been raised
                        not_unique_rand = true;

                    else if(flag == false)//flag has not been raised
                        not_unique_rand = false;
                }//end nested while

                arr[i]=temp;
            }//end for
            keepgoing = false;
        }//end else if
        else
        {
            cout<<"Not a valid choice"<<endl<<endl;
            cout<<"yes or no: ";
        }//end else
    }//end while
}

void print_arr(int arr[],int n)
{
    cout<<endl;
    for(int i = 0; i<n;i++)
        cout<<"arr["<<i<<"] = "<<arr[i]<<endl;
}
