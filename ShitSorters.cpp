#include <iostream>
#include <ctime>
#include <chrono>
#define MIN_RANGE 0
#define MAX_RANGE 10

using namespace std;

typedef unsigned int uint;

class ArrayController {
private:
    int* arr;
    uint size;

    long long unsigned int iteration = 0;
    
    void shuffle()
    {
        for (uint i = 0; i < size; i++)
            arr[i] = rand() % MAX_RANGE + MIN_RANGE;
    }

    void shufflePosition()
    {        
        for (uint i = 0; i < size; i++)
        {
            uint new_pos = rand() % size;
            int element = arr[new_pos];
            arr[new_pos] = arr[i];
            arr[i] = element;
        }
    }

    bool validate()
    {
        for (uint i = 0; i < size - 1; i++)
            if (arr[i] > arr[i + 1])
                return false;
        return true;
    }
public:
    ArrayController() : arr(nullptr), size(0) {}

    ArrayController(uint size) : arr(new int[size]), size(size)
    {
        shuffle();
    }
    
    ~ArrayController() { delete[] arr; }
    
    uint Size() const { return size; }
    int Element(uint index) const { return arr[index]; }
    uint It() { return iteration; }
    float BogoSort()
    {
        if (!arr) return -1.f;

        auto timestamp_start = chrono::high_resolution_clock::now();

        while (!validate())
        {
            iteration++;
            shufflePosition();
        }

        auto timestamp_end = chrono::high_resolution_clock::now();
        return chrono::duration_cast<chrono::milliseconds>(timestamp_end - timestamp_start).count();
    }
    
    friend ostream& operator<< (ostream& str, ArrayController& controller)
    {
        for (uint i = 0; i < controller.size; i++)
            str << controller.Element(i) << " ";
        str << endl;
        return str;
    }
};

int main()
{
    uint size;
    cout << "SIZE: ";
    cin >> size;
    
    ArrayController arr(size);
    cout << "START: " << arr << endl;
    cout << "TIME PASSED: " << arr.BogoSort() << '\a' << endl;
    cout << "ITERATIONS:  " << arr.It() << endl;
    cout << "RESULT: " << arr << endl;

    return 0;
}
