/*                                                                                                                                                                                                        
  File: Atbash.cpp                                                                                                                                                                                         
                                                                                                                                                                                                           
  Project: CMSC 202 Project 4, Spring 2025                                                                                                                                                                 
                                                                                                                                                                                                          
  Author: Elif Meral                                                                                                                                                                                       
                                                                                                                                                                                                           
  Date: 04/14/2025                                                                                                                                                                                         
                                                                                                                                                                                                           
  Section: 10/14                                                                                                                                                                                           
                                                                                                                                                                                                           
  E-mail: elifm1@umbc.edu                                                                                                                                                                                  
                                                                                                                                                                                                           
  Description: This file contains the Atbash class function definitions.                                                                                                                                   
                    Which is the child class for Cipher. This uses the Atbash cipher to encrypt or decrypt a message.                                                                                     
                                                                                                                                                                                                           
 */

#include "Cipher.h"
#include "Atbash.h"
#include <string>
#include <sstream>
using namespace std;

// Atbash() 
// Default Constructor
Atbash::Atbash() : Cipher() {}

// Atbash(string message, bool isEncrypted) 
// Overloaded Constructor
Atbash::Atbash(string message, bool isEncrypted) : Cipher(message, isEncrypted) {}

// ~Atbash()
// Destructor
Atbash::~Atbash() {}

// Encrypt: Reverses the alphabet (A <-> Z, a <-> z)
void Atbash::Encrypt() {
  // Only runs if the message is not encrypted
  if (!GetIsEncrypted()) {

    string message = GetMessage();   // Holds message that needs to be encrypted

    // Goes through each character in the message
    for (char &ch : message) {

      // Runs if the letter is uppercase
      if (ch >= 'A' && ch <= 'Z') {
	// The distance between the current letter and A is found. Then the letter that is the sane distance from Z is found.
	ch = 'Z' - (ch - 'A');	
      }

      // Runs if the latter is lowercase
      else if (ch >= 'a' && ch <= 'z') {
	// The distance between the current letter and a is found. Then the letter that is the sane distance from z is found.
	ch = 'z' - (ch - 'a');
      }
      
    }
    // Sets the message to the encrypted version
    SetMessage(message);

    //Updates that the message is encrypted
    ToggleEncrypted();
  }
}

// Decrypt()
// Reverses the alphabet (A <-> Z, a <-> z)
void Atbash::Decrypt(){
  
  // Only runs if the message is encrypted                                                                                                                                                             
  if (GetIsEncrypted()) {
    
    string message = GetMessage();   // Holds message that needs to be decrypted

    // Goes through each character in the message    
    for (char &ch : message) {
      
      // Runs if the letter is uppercase                                                                                                                                                                   
      if (ch >= 'A' && ch <= 'Z'){ 
        // The distance between the current letter and A is found. Then the letter that is the sane distance from Z is found.                                                                              
	ch = 'Z' - (ch - 'A');
      }
      
      // Runs if the letter is lowercase                                                                                                                                                                   
      else if (ch >= 'a' && ch <= 'z') 
	// The distance between the current letter and a is found. Then the letter that is the sane distance from z is found.                                                                              
	ch = 'z' - (ch - 'a');
    }
    
    // Sets the message to the encrypted version                                                                                                                                                           
    SetMessage(message);
    
    //Updates that the message is encrypted                                                                                                                                                                
    ToggleEncrypted();
  }
}

// ToString()
// Returns the string of the object type
string Atbash::ToString() {return "a";}

// FormatOutput()
// Returns the formatted output for Output function
string Atbash::FormatOutput() {
    stringstream ss;
    ss << ToString() << DELIMITER;
    ss << GetIsEncrypted() << DELIMITER;
    ss << GetMessage() << DELIMITER;
    return ss.str();
}

