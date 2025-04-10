#include <iostream>
#include <vector>
#include <functional>
#include <algorithm>
#include <list>
#include <string>
#include <fstream>

//-----------------------------------------------------------------------------
// Класс для работы с базой данных
//-----------------------------------------------------------------------------
class CDatabase
{
public:
    void Save();
    void Restore();

public:
    struct DatabaseElement_t
    {
        // Вариант 3. База данных маршрутов троллейбусов
        std::string m_routeName;
        int         m_routeNumber;

        friend std::ostream& operator <<( std::ostream& s, const DatabaseElement_t& el )
        {
            s << el.m_routeName << std::endl;
            s << el.m_routeNumber << std::endl;
            return s;
        }

        friend std::istream& operator >>( std::istream& s, DatabaseElement_t& el )
        {
            s >> el.m_routeName;
            s >> el.m_routeNumber;
            return s;
        }
    };

public:
    const std::string kDatabaseFile = "database.txt";
    std::list<DatabaseElement_t> m_storage;
};

void CDatabase::Save()
{
    std::ofstream saveFile;
    saveFile.open( kDatabaseFile, std::ios::out | std::ios::binary );

    if ( !saveFile.is_open() )
    {
        std::cout << "Couldnt open save file for some reason =(" << std::endl;
        return;
    }

    // Сохраним кол-во записей в БД для корректного чтения
    saveFile << m_storage.size() << std::endl;

    std::for_each( m_storage.begin(), m_storage.end(),
        [ & ]( CDatabase::DatabaseElement_t& el )
        {
            saveFile << el;
        } );

    std::cout << "Database file just saved" << std::endl;
}

void CDatabase::Restore()
{
    std::ifstream restoreFile;
    restoreFile.open( kDatabaseFile, std::ios::in | std::ios::binary );

    if ( !restoreFile.is_open() )
    {
        std::cout << "Database file does not exist." << std::endl;
        return;
    }

    int cEntries = 0;
    restoreFile >> cEntries;

    for ( int i = 0; i < cEntries; i++ )
    {
        DatabaseElement_t entry;
        restoreFile >> entry;
        m_storage.push_back( entry );
    }

    std::cout << "Database file just read, count of entries: " << cEntries << std::endl;
}

bool IsElementEqual( const CDatabase::DatabaseElement_t& el, const int& routeNumber )
{
    return el.m_routeNumber == routeNumber;
}

bool ElementSort( const CDatabase::DatabaseElement_t& a, const CDatabase::DatabaseElement_t& b )
{
    return a.m_routeNumber < b.m_routeNumber;
}

int main()
{
    CDatabase   database;
    bool        bRunning = true;

    // Восстановить базу данных из файла
    database.Restore();

    int routeNumber = 0;
    CDatabase::DatabaseElement_t el;

    std::cout << "q - quit, l - list, d - delete, i - insert" << std::endl;

    while ( bRunning )
    {
        char ch;
        std::cin >> ch;

        switch ( ch )
        {
        case 'd':
            std::cout << "Enter route number to delete: ";
            std::cin >> routeNumber;
            database.m_storage.remove_if( std::bind( IsElementEqual, std::placeholders::_1, routeNumber ) );
            std::cout << "Done." << std::endl;
            break;

        case 'l':
            std::cout << "Database: " << std::endl;
            database.m_storage.sort( ElementSort );
            std::copy( database.m_storage.begin(), database.m_storage.end(), std::ostream_iterator<CDatabase::DatabaseElement_t>( std::cout, "\n" ) );
            break;

        case 'i':
            std::cout << "Enter new route number: ";
            std::cin >> el.m_routeNumber;

            std::cout << "Enter new route name: ";
            std::cin >> el.m_routeName;

            database.m_storage.push_back( el );
            std::cout << "Done." << std::endl;
            break;
        case 'q':
            bRunning = false;
            break;

        default:
            std::cout << "Unknown command key: " << ch << std::endl;
            break;
        }
    }

    // Сохранить базу данных
    database.Save();

    return 0;
};