#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>


template<typename T>
void PrintVector( const std::vector<T>& vector, const char* pLabel = "the data in vector" )
{
    std::cout << pLabel << ": ";
    std::for_each( vector.begin(), vector.end(), [ & ]( const int& number )
        {
            std::cout << number << " ";
        } );
    std::cout << std::endl;
}

constexpr int kArrayLen = 10;
constexpr int kMinValue = 0, kMaxValue = 1000;

template<typename T>
void FillVector( std::vector<T>& vector )
{
    vector.clear();
    for ( int i = 0; i < kArrayLen; i++ )
    {
        int randomNumber = ( rand() % kMaxValue ) + kMinValue;
        vector.push_back( randomNumber );
    }

}

void Ex1()
{
    std::cout << std::endl << std::endl << "Ex 1: " << std::endl;

    typedef int valueType;

    // 1-ый способ заполнения
    std::vector<valueType> firstVector = { 15, -3, 166, 35, 90 };

    // 2-ой способ заполнения
    firstVector.push_back( 41 );
    firstVector.push_back( 0 );
    firstVector.push_back( 551 );

    PrintVector<int>( firstVector );

}

void Ex2()
{
    srand( time( NULL ) );

    std::cout << std::endl << std::endl << "Ex 2: " << std::endl;

    std::vector<int> secondVector;

    //...................................................
    // Заменить элементы большие среднего арифметического на минимальное значение контейнера
    std::cout << std::endl << "......................" << std::endl;

    // Заполнение случайными числами
    FillVector<int>( secondVector );
    PrintVector<int>( secondVector );

    int minNumber = *std::min_element( secondVector.begin(), secondVector.end() );
    std::cout << "minNumber: " << minNumber << std::endl;

    int averageNumber = std::accumulate( secondVector.begin(), secondVector.end(), 0.0 ) / secondVector.size();
    std::cout << "averageNumber: " << averageNumber << std::endl;

    std::replace_if( secondVector.begin(), secondVector.end(), [ & ]( int& number )
        {
            return number < averageNumber;
        },
        minNumber );

    PrintVector<int>( secondVector, "result" );

    //...................................................
    // Отсортировать контейнер по убыванию и возрастанию 
    std::cout << std::endl << "......................" << std::endl;

    auto lambdaSortGreater = []( int a, int b )
        {
            return a > b;
        };

    auto lambdaSortSmaller = []( int a, int b )
        {
            return a < b;
        };


    std::cout << "Sort from smallest to greatest. " << std::endl;

    // Заполнение случайными числами
    FillVector<int>( secondVector );
    PrintVector<int>( secondVector );

    std::sort( secondVector.begin(), secondVector.end(), lambdaSortSmaller );
    PrintVector<int>( secondVector, "result" );

    std::cout << "Sort from greatest to smallest. " << std::endl;

    // Заполнение случайными числами
    FillVector<int>( secondVector );
    PrintVector<int>( secondVector );

    std::sort( secondVector.begin(), secondVector.end(), lambdaSortGreater );
    PrintVector<int>( secondVector, "result" );

    //...................................................
    // Найти в контейнере элементы с заданным значением
    std::cout << std::endl << "......................" << std::endl;

    // Заполнение случайными числами
    FillVector<int>( secondVector );
    PrintVector<int>( secondVector );

    int numberToFind = 41;
    std::cout << "Enter the number to find: ";
    std::cin >> numberToFind;

    std::cout << "Searching number " << numberToFind << " in vector " << std::endl;

    std::vector<int>::iterator iterator = std::find( secondVector.begin(), secondVector.end(), numberToFind );
    while ( ( iterator != secondVector.end() ) )
    {
        std::cout << "numberPosition: " << iterator - secondVector.begin() << std::endl;
        iterator = std::find( ++iterator, secondVector.end(), numberToFind );
    }

    //...................................................
    // Удалить минимальный элемент из контейнера
    std::cout << std::endl << "......................" << std::endl;

    // Заполнение случайными числами
    FillVector<int>( secondVector );
    PrintVector<int>( secondVector );

    std::vector<int>::iterator minNumberIterator = std::min_element( secondVector.begin(), secondVector.end() );
    std::cout << "minNumber: " << *minNumberIterator << ", deleting at " << minNumberIterator - secondVector.begin() << std::endl;
    secondVector.erase( minNumberIterator );
    PrintVector<int>( secondVector, "result" );

    //...................................................
    // Каждый элемент разделить на минимальное значение контейнера
    std::cout << std::endl << "......................" << std::endl;

    // Заполнение случайными числами
    FillVector<int>( secondVector );
    PrintVector<int>( secondVector );

    minNumber = *std::min_element( secondVector.begin(), secondVector.end() );
    std::cout << "minNumber: " << minNumber << std::endl;

    std::for_each( secondVector.begin(), secondVector.end(), [ & ]( int& number )
        {
            number = number / minNumber;
        } );

    PrintVector<int>( secondVector, "result" );

}

int main()
{
    Ex1();
    Ex2();
    return 0;
}