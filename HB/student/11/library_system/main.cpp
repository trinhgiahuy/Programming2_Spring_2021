/* Main.cpp
 * --------
 * Creates the library object, uses the file_reader module to init the obj and
 * starts the cli module.
 *
 * TIE-0220x S2019
 * */

 // Library Project!
 // In this project, I 
 //		+ modify Library class 
 //		+ add new Loan class
 //     + fix the date input format in 	cli.cpp
 //  which implemented a database using map structure 
 // with key as string, and key's data as a vector of Loan
 //
 // Student's name: Anh Huy Bui
 // Student's number: 293257

#include "file_reader.hh"
#include "cli.hh"
#include <iostream>

using namespace std;

int main()
{
    // Create the library and store it in a shared pointer.
    std::shared_ptr<Library> lib(new Library);
    // If we can't read the files, return error.
    if ( !read_file_to_lib(lib) ){
        return EXIT_FAILURE;
    }
    // Otherwise, start the cli.
    Cli cli(lib);
    while( cli.exec_prompt() ){}
    return EXIT_SUCCESS;
}
