#include <iostream>
#include <vector>
#include <functional>
#include <algorithm>
#include <deque>
#include <string>
#include <fstream>



//-----------------------------------------------------------------------------
// Задание 1
//-----------------------------------------------------------------------------
void Ex1() {
    using type_t = double;
    const std::string IN_FILE_PATH = "in4.txt";
    const std::string OUT_FILE_PATH = "out4.txt";

    std::deque<type_t> container;

    std::ifstream inFile;
    inFile.open( IN_FILE_PATH, std::ios::in );

    if ( !inFile.is_open() ) {
        std::cout << "File does not exist." << std::endl;
        return;
    }

    type_t value = 0;
    while ( inFile >> value ) {
        container.push_front( value );
    }

    inFile.close();

    std::ofstream saveFile;
    saveFile.open( OUT_FILE_PATH, std::ios::out | std::ios::binary );

    if ( !saveFile.is_open() ) {
        std::cout << "Couldnt open save file for some reason =(" << std::endl;
        return;
    }

    std::for_each( container.begin(), container.end(), [&]( type_t& value ) {
        saveFile << value << std::endl;
        } );

    saveFile.close();
};


//-----------------------------------------------------------------------------
// Задание 2 
//-----------------------------------------------------------------------------

void Ex2() {

    struct deque_t {
        std::deque<int> x2, x3, x5;

        void AddAndPrint( int t ) {
            std::cout << " " << t;

            x2.push_back( 2 * t );
            x3.push_back( 3 * t );
            x5.push_back( 5 * t );
        }

        void Clear() {
            x2.clear();
            x3.clear();
            x5.clear();
        }
    };

    int k = 1, n = 0, next = 0;
    deque_t container;

    std::cout << "Enter the number of Hamming numbers to print: ";
    std::cin >> n;

    container.Clear();
    container.AddAndPrint( 1 );

    while ( k < n ) {
        next = std::min( { container.x2.front(), container.x3.front(), container.x5.front() } );

        container.AddAndPrint( next );
        k++;

        if ( next == container.x2.front() ) container.x2.pop_front();
        if ( next == container.x3.front() ) container.x3.pop_front();
        if ( next == container.x5.front() ) container.x5.pop_front();
    }
}

int main() {
    Ex1();
    Ex2();
    return 0;
}
