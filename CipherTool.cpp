/*
  File: Cipher.cpp                                                                                             
                                                                                                                                                                                                           
  Project: CMSC 202 Project 4, Spring 2025                                                                                                                                                                 
                                                                                                                                                                                                           
  Author: Elif Meral                                                                                                                                                                                       
                                                                                                                                                                                                           
  Date: 04/14/2025                                                                                                                                                                                         
                                                                                                                                                                                                           
  Section: 10/14                                                                                                                                                                                          
                                                                                                                                                                                                           
  E-mail: elifm1@umbc.edu                                                                                                                                                                                  
                                                                                                                                                                                                           
  Description: This file contains the CipherTool class function definitions.
 */

#include "Cipher.h"
#include "Atbash.h"
#include "Scytale.h"
#include "Ong.h"
#include "CipherTool.h"
#include <fstream>
#include <vector>
#include <iostream>
#include <string>

using namespace std;

// CipherTool(string filename)
// Constructor - Creates a new CipherTool and sets m_filename based on string passed 
CipherTool::CipherTool(string filename) {
    m_filename = filename;
    LoadFile();  
}

// ~CipherTool()
// Destructor
CipherTool::~CipherTool() {
  //Deallocates dynamically crerated pointers
  for (size_t i = 0; i < m_ciphers.size(); i++) {
    delete m_ciphers[i];
  }
}

// LoadFile()
// Opens file and reads in each Cipher.
void CipherTool::LoadFile() {
  //Opens file
  ifstream file(m_filename); 
  string line; //Empty string for line to insert sentences
  
  while (getline(file, line)) {
    string type = "";           // Holds Cipher type
    string isEncrypted = "";    // Holds whether encrypted or not
    bool encrypted;             // Boolean for encryption
    string message = "";        // Holds message
    int key = 0;                // Holds key for Scytale ciphers
    // Finds the cipher type
    // Finds the first delimiter 
    size_t pos1 = line.find('|');
    // Gets the cipher type
    type = line.substr(0, pos1);  

    // Find if encrypted or not
    // Find the second delimiter   
    size_t pos2 = line.find('|', pos1 + 1); 
    // Get the encrypted status
     isEncrypted = line.substr(pos1 + 1, pos2 - pos1 - 1);
    // Turn encryption into bool
    if (isEncrypted == "0"){
      encrypted = 0;
    }
    else{
      encrypted = 1;
    }
    
    // Find the message
    // Find the third delimiter
    size_t pos3 = line.find('|', pos2 + 1);
    // Get the message 
    message = line.substr(pos2 + 1, pos3 - pos2 - 1);
    
    
    Cipher* newCipher = nullptr;
    // Dynamically creates Atbash cipher
    if (type == "a") {
      
      newCipher = new Atbash(message, encrypted);
    }
    // Dynamically creates Scytale cipher
    else if (type == "s") {
      // Finds key
      string keyString = line.substr(pos3 + 1);
      // Convert key from string to int 
      key = stoi(keyString);
      
      newCipher = new Scytale(message, encrypted, key);
    }
    // Dynamically creates Ong cipher
    else if (type == "o") {
      newCipher = new Ong(message, encrypted);
    }
    
    // Add the cipher to m_ciphers
    if (newCipher) {
      m_ciphers.push_back(newCipher);
    }
  }
  // Close the file    
  file.close();  
}

// StringToBoolean(string input)
// Converts a string to a boolean for reading in file
bool CipherTool::StringToBoolean(string input) {
  //Turns string 0 or 1 into a boolean 0 or 1
  if (input == "0"){
    return false;
  }
  else{
    return true;
  }
}

// DisplayCiphers()
// Displays each of the ciphers in the m_ciphers
void CipherTool::DisplayCiphers() {
  int list = 1;     // List number
  
 // Loop through each cipher in the m_ciphers vector
  for (int i = 0; i < (int)m_ciphers.size(); i++) {

    // Access the Cipher pointer from the vector 
    Cipher* cipher = m_ciphers[i];  

    // Holdds Cipher Type
    string cipherType = "" ;
    
    // Sets the sentences' cipher type
    if (cipher->ToString() == "a") {
      cipherType = " (Atbash)";
    } else if (cipher->ToString() == "s") {
      cipherType = " (Scytale)";
    } else if (cipher->ToString() == "o") {
      cipherType = " (Ong)";
    } else {
      cipherType = "Unknown";
    }
    
    cout << list << ". " << cipher->GetMessage() << cipherType  << endl << endl;
    list++;
  }
  
}

// EncryptDecrypt(bool encrypt)
// Encrypts or decrypts each of the ciphers in the m_ciphers
void CipherTool::EncryptDecrypt(bool encrypt) {
  //Keeps track of changed ciphers
  int changedCiphers = 0;
  
  // Loop through each cipher in the m_ciphers vector
  for (int i = 0; i < (int)m_ciphers.size(); i++) {
    // Access the Cipher pointer from the vector
    Cipher* cipher = m_ciphers[i];

    // Encrypt the cipher if requested
    if (encrypt && !cipher->GetIsEncrypted()) {
      cipher->Encrypt();
      changedCiphers++;
    }
    
    // Decrypt the cipher if requested
    else if (!encrypt && cipher->GetIsEncrypted()){
      cipher->Decrypt();
      changedCiphers++;
    }
  }

  // Print result to the user
  if (encrypt) {
    cout << changedCiphers << " ciphers encrypted." << endl;
  }
  else {
    cout << changedCiphers << " ciphers decrypted." << endl;
  }
}

// Exportt()
// Exports each of the ciphers in the m_ciphers (so they can be reused)
void CipherTool::Export() {
  string fileName = "";    //Users chosen file name
  int count = 0;
  // Asks user for file name
  cout << "What would you like to call the export file? " << endl;
  getline(cin, fileName);

  // Open file for writing
  ofstream file(fileName);

  //Checks to make sure file is opened
  if (!file.is_open()) {
    cout << "Error: Could not open file " << fileName << " for writing." << endl;
    return;
  }

  for (int i = 0; i < (int)m_ciphers.size(); i++) {
    // Access the Cipher pointer from the vector
    Cipher* cipher = m_ciphers[i];
    
    // Write the output using the cipher's FormatOutput function
    file << cipher->FormatOutput() << endl;
    count++;
  }
  // Close the output file
  file.close();

  cout << count << " ciphers exported" << endl;
}

// Menu()
// Displays menu and returns choice
int CipherTool::Menu() {
  int choice = 0;     // Users choice on what to do
  
  // Asks menu as long as the choice is valid
  while (choice < 1 || choice > 5){
    cout << "What would you like to do?" << endl;
    cout << "1. Display All Ciphers" << endl;
    cout << "2. Encrypt All Ciphers" << endl;
    cout << "3. Decrypt All Ciphers" << endl;
    cout << "4. Export All Ciphers" << endl;
    cout << "5. Quit" << endl;

    // Sets users choice
    cin >> choice;

    //ignores any leftover input
    cin.ignore();
  }
    return choice;
}

// Start()
// Loads input file, allows user to choose what to do
void CipherTool::Start() {
  //Users choice
  int choice = 0;
  
  // Runs until user chooses to quit
  while (choice != 5) {
    
    //choice is set by the Menu function
    choice = Menu(); 

    switch (choice) {

      // Display the ciphers 
    case 1:
      DisplayCiphers();  
      break;

      // Encrypt Ciphers
    case 2: {
      EncryptDecrypt(true);
	break;
    }
      // Decrypt Ciphers
    case 3:
      EncryptDecrypt(false);
      break;

      // Export the ciphers to the file 
    case 4:
      Export();
      break;

      // Thanks and Exits
    case 5:
      cout << "Thanks for using UMBC Encryption" << endl;
      break;
    default:
      //Incase of an invalid choice lets the user know
      cout << "Invalid choice. Please try again.\n";
    }
  }
}
