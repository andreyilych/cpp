#include <iostream>
#include <fstream>
#include <set>
#include <map>
#include <algorithm>
#include <string>

//-----------------------------------------------------------------------------
// Задание 1 
//-----------------------------------------------------------------------------

std::set<int> ReadNumbers( const std::string& filename ) {
    int num = 0;
    std::set<int> numbers;
    std::ifstream file( filename );

    if ( !file.is_open() ) {
        std::cout << "Couldn't open file for some reason =( " << std::endl;
        return numbers;
    }

    while ( file >> num ) {
        numbers.insert( num );
    }

    return numbers;
}

void Ex1() {
    const std::string IN_FILE_PATH1 = "numbers1.txt";
    const std::string IN_FILE_PATH2 = "numbers2.txt";

    std::set<int> set1, set2;
    int result = 0;

    set1 = ReadNumbers( IN_FILE_PATH1 );
    set2 = ReadNumbers( IN_FILE_PATH2 );

    std::for_each( set2.begin(), set2.end(), [&]( int& value ) {

        if ( set1.find( value ) != set1.end() ) {
            result++;
        }

        } );


    std::cout << "Result: " << result << std::endl;

}

//-----------------------------------------------------------------------------
// Задание 2
//-----------------------------------------------------------------------------

// Функция для приведения слова к нижнему регистру
std::string ToLower( const  std::string& word ) {
    std::string lowerWord;
    for ( char ch : word ) {
        lowerWord += tolower( ch );
    }
    return lowerWord;
}

// Функция для очистки слова от знаков пунктуации
std::string CleanWord( const  std::string& word ) {
    std::string cleaned;
    for ( char ch : word ) {
        if ( isalpha( ch ) || ch == '-' ) {
            cleaned += ch;
        }
    }
    return cleaned;
}

void Ex2() {

    setlocale( LC_ALL, "Russian" );

    std::string text;
    std::cout << "Enter the text:\n";

    // Чтение многострочного текста
    std::string line;
    while ( std::getline( std::cin, line ) && !line.empty() ) {
        text += line + " ";
    }

    std::map<std::string, int> wordCount;
    std::set<std::string> words;
    std::string currentWord;

    // Разбиение текста на слова
    for ( char ch : text ) {
        if ( isalpha( ch ) || ch == '\'' || ch == '-' ) {
            currentWord += ch;
        }
        else if ( !currentWord.empty() ) {
            std::string cleaned = CleanWord( currentWord );
            if ( !cleaned.empty() ) {
                words.insert( ToLower( cleaned ) );
            }
            currentWord.clear();
        }
    }

    // Обработка последнего слова
    if ( !currentWord.empty() ) {
        std::string cleaned = CleanWord( currentWord );
        if ( !cleaned.empty() ) {
            words.insert( ToLower( cleaned ) );
        }
    }

    // Подсчет слов
    for ( const std::string& word : words ) {
        wordCount[word]++;
    }

    // Вывод результатов
    std::cout << "\nResult:\n";
    for ( const auto& pair : wordCount ) {
        if ( pair.second > 1 ) {
            std::cout << pair.first << " - " << pair.second << std::endl;
        }
    }

}

int main() {
    Ex1();
    Ex2();
    return 0;
}