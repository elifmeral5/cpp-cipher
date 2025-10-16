/*                                                                                                                                                                                                         
  File: Ong.cpp                                                                                                                                                                                         
                                                                                                                                                                                                           
  Project: CMSC 202 Project 4, Spring 2025                                                                                                                                                                 
                                                                                                                                                                                                           
  Author: Elif Meral                                                                                                                                                                                       
                                                                                                                                                                                                           
  Date: 04/14/2025                                                                                                                                                                                         
                                                                                                                                                                                                           
  Section: 10/14                                                                                                                                                                                           
                                                                                                                                                                                                           
  E-mail: elifm1@umbc.edu                                                                                                                                                                                  
                                                                                                                                                                                                           
  Description: This file contains the Ong class function definitions.                                                                                                                                   
                    Which is the child class for Cipher. This uses the Ong cipher to encrypt or decrypt a message.                                                                                      
                                                                                                                                                                                                          
*/

#include "Cipher.h"
#include "Ong.h"
#include <istream>
#include <string>
#include <vector>
using namespace std;

// Ong()
// Default Constructor
Ong::Ong() : Cipher() {}

// Ong(string message, bool isEncrypted)
// Overloaded Constructor
Ong::Ong(string message, bool isEncrypted) : Cipher(message, isEncrypted) {}

// ~Ong()
// Destructor
Ong::~Ong() {}

// IsVowel(char v)
// Helper function - Checks if a character is a vowel
bool Ong::IsVowel(char v) {

  //checks if the character is a vowel
  if (v ==  'A' || v == 'a'){
    return true;
  }
  else if (v == 'E' || v == 'e'){
    return true;
  }
  else if (v == 'I' || v == 'i'){
    return true;
  }
  else if (v == 'O' || v == 'o'){
    return true;
  }
  else if (v == 'U' || v == 'u'){
    return true;
  }
  
  // if the letter is not a vowel
  else{
    return false;
  }
}

// IsPunct(char c)
// Helper function - Checks if a character is a punctuation or a space
bool Ong::IsPunct(char c) {
  // Checks for Vowel
  if (IsVowel(c)){
    return false;
  }

  // Checks for punctuation
  if (c >= 33 && c <= 47){
    return true;
  }
  else if (c >= 58 && c <= 64) {
    return true;
  }
  else if (c >= 91 && c <= 96) {
    return true;
  }
  else if (c >= 123 && c <= 126) {
    return true;
  }

  // Checks for space
  if (c == ' '){return true;}

  // If it is a consonant letter
  return false;
}

// Encrypt function
void Ong::Encrypt() {
  // Only runs if the message is not encrypted                                                                                                                                                        
  if (!GetIsEncrypted()) {
    
    string encryptMes = "";     // Stores the encrypted message
    string oldMessage = GetMessage();     //Stores the message 

    // Iterates through each letter of the message
    for (size_t i = 0; i < oldMessage.length(); i++){

      char character = oldMessage[i];     //Stores the character in the message

      // Adds the letter and  a dash after the vowel
      if (IsVowel(character)){
	encryptMes += character;
	encryptMes += "-";
      }

      // Adds the punctutation
      else if (IsPunct(character)){
	encryptMes += character;
      }

      //Adds the letter, ong, and a dash
      else{
	encryptMes += character;
	encryptMes += ong;
	encryptMes += "-";
      }
    }

    // Sets the message to the encrypted version
    SetMessage(encryptMes);

    //Updates that the message is encrypted
    ToggleEncrypted();
  }
}

// Decrypt()
// Decrypts message - Removes the dashes and "ong" when necessary
void Ong::Decrypt() {
  if (GetIsEncrypted()){
    
    string decryptMes = "";     // Stores the decrypted message
    string oldMessage = GetMessage();     //Stores the message

    // Iterates throught the message
    for (size_t i = 0; i < oldMessage.length(); i++){

      char character = oldMessage[i];     //Stores the character in the message

      // If the character is a punctuation add the character to the decrypted message
      if (IsPunct(character)){
	decryptMes += character;
      }
      // If it is a vowel
      else if (IsVowel(character)){
	    // Checks if there is a dash after the vowel
	    if (i + 1 < oldMessage.length() && oldMessage[i + 1] == '-'){
	      decryptMes += character;
	      //Skips over the dash
	      i++;
	    }
	    //Dont do anything if there is no dash after the vowel
      }
      
      // For consonants
      else{
	decryptMes += character;

	// Check for "ong" and dash
        if (i + 3 < oldMessage.length() && oldMessage[i + 1] == 'o' && oldMessage[i + 2] == 'n' && oldMessage[i + 3] == 'g') {
	  // Skips "ong"
	  i += 3;

	  // Checks to make sure we are not at the end of the message
	  if (i + 1 < oldMessage.length() && oldMessage[i + 1] == '-') {
	    // Skips dash
	    i++;
	  }
	}
      }
      
    }
    // Sets the message to the decrypted version                                                                                                                                                           
    SetMessage(decryptMes);
    
    //Updates that the message is encrypted                                                                                                                                                                
    ToggleEncrypted();
  }
}

// ToString function
string Ong::ToString() {
    return "o";
}

// FormatOutput function
string Ong::FormatOutput() {
    stringstream ss;
    ss << ToString() << DELIMITER
       << GetIsEncrypted() << DELIMITER
       << GetMessage() << DELIMITER;
    return ss.str();
}
