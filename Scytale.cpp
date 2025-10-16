/*                                                                                                                                                                                                         
  File: Scytale.cpp                                                                                                                                                                                        
                                                                                                                                                                                                           
  Project: CMSC 202 Project 4, Spring 2025                                                                                                                                                                 
                                                                                                                                                                                                           
  Author: Elif Meral                                                                                                                                                                                       
                                                                                                                                                                                                           
  Date: 04/14/2025                                                                                                                                                                                         
                                                                                                                                                                                                           
  Section: 10/14                                                                                                                                                                                           
                                                                                                                                                                                                           
  E-mail: elifm1@umbc.edu                                                                                                                                                                                  
                                                                                                                                                                                                           
  Description: This file contains the Syctale class function definitions.                                                                                                                                  
                    Which is the parent class for each cipher and holds a message that will be encrypted or decrypted.                                                                                     
                                                                                                                                                                                                           
 */

#include "Cipher.h"
#include "Scytale.h"
#include <istream>
#include <sstream>
#include <string>
#include <vector>
#include <cmath>
using namespace std;

// Scytale()  
// Default Constructor
Scytale::Scytale() : Cipher(), m_key(0) {}

// Scytale(string message, bool isEncrypted, int key)
// Overloaded Constructor
Scytale::Scytale(string message, bool isEncrypted, int key) : Cipher(message, isEncrypted), m_key(key) {}

// ~Scytale()
// Destructor
Scytale::~Scytale() {}

// Encrypt()
// Encrypts the message using the Scytale cipher
void Scytale::Encrypt() {

  if (!GetIsEncrypted()){
    
    string encrypted = "";                                     // Encrypted message
    string oldMessage = GetMessage();                          // Old message
    int length = oldMessage.length();                          // Number of characters in the message
    int numCols = m_key;                                       // Number of Columns
    int numRows = ceil((double)length) / numCols); // Number of Rows
    
    // 2D List to hold characters
    vector<vector<char>> grid(numRows, vector<char>(numCols, ' '));
    
    // Filling the grid row by row
    int index = 0;  // Holds the place for the current character
    
    //Goes through columns
    for (int i = 0; i < numRows; i++) {
      
      //Goes through rows
      for (int j = 0; j < numCols; j++) {
	
	// Makes sure index is in range
	if (index < length) {
	  grid[i][j] = oldMessage[index];
	  index++;
	}
      }
    }

    int index2 = 0;
    // Goes through grid for encryption
    // Goes through the Rows
    for (int j = 0; j < numCols; j++) {
      for (int i = 0; i < numRows; i++) {
	if (index2 < length){
	  encrypted += grid[i][j];
	  index2++;
	}
      }
    }
    
    // Sets the message to the encrypted version
    SetMessage(encrypted);

    //Updates that the message is encrypted
    ToggleEncrypted();
  }
}

// Decrypt()
// Decrypts the message back to the original using the Scytale cipher
void Scytale::Decrypt(){                                                                                                                                                                   
  if (GetIsEncrypted()){
    string decrypted = "";                                     // decrypted message                                                                                                                        
    string oldMessage = GetMessage();                          // Old message                                                                                                                              
    int length = oldMessage.length();                          // Number of characters in the message                                                                                                    
    int numCols = m_key;                                       // Number of Columns                                                                                                                        
    int numRows = ceil((double)length) / numCols); // Number of Rows                                                                                                                          

    // 2D List to hold characters                                                                                                                                                                          
    vector<vector<char>> grid(numRows, vector<char>(numCols, ' '));
    
    int index = 0;  // Holds the place for the current character
    
    // Filling the grid
    // Going column by column
    for (int j = 0; j < numCols; j++) {
      //Going row by row
      for (int i = 0; i < numRows; i++) {
	// Checking the index
        if (index < length) {
          grid[i][j] = oldMessage[index];
          index++;
        }
      }
    }
    
    int index2 = 0;
    // Decrypting the grid row by row
    for (int i = 0; i < numRows; i++) {
      for (int j = 0; j < numCols; j++) {

        if (index2 < length) {  
          decrypted += grid[i][j];
          index2++;
        }
      }
    }

    SetMessage(decrypted);
    ToggleEncrypted();
  }
}

// ToString()
// Returns the name of the cipher type
string Scytale::ToString() {
  return "s";
}

// FormatOutput()
// Returns a formatted string for file output
string Scytale::FormatOutput() {
  stringstream ss;
  ss << ToString() << DELIMITER
     << GetIsEncrypted() << DELIMITER
     << GetMessage() << DELIMITER
     << m_key;
  return ss.str();
}

