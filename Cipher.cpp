/*
  File: Cipher.cpp

  Project: CMSC 202 Project 4, Spring 2025

  Author: Elif Meral

  Date: 04/14/2025

  Section: 10/14

  E-mail: elifm1@umbc.edu

  Description: This file contains the Cipher class function definitions.
                    Which is the parent class for each cipher and holds a message that will be encrypted or decrypted.

 */

#include "Cipher.h"
#include <iostream>
#include <string>
#include <sstream>
using namespace std;

// Constructors

// Cipher()
// Default Constructor - Stores a message and if it is encrypted (or not)
Cipher::Cipher() {
    m_message = "";
    m_isEncrypted = false;
}

// Cipher(string message, bool isEncrypted)
// Overloaded Constructor - Passed a message and if it is encrypted (or not)
Cipher::Cipher(string message, bool isEncrypted) {
    m_message = message;
    m_isEncrypted = isEncrypted;
}

// ~Cipher()
// Virtual Destructor
Cipher::~Cipher() {}

// GetMessage()
// returns the message
string Cipher::GetMessage() {return m_message;}

// GetIsEncrypted()
//  Returns isEncrypted (0 is not encrypted and 1 is encrypted)
bool Cipher::GetIsEncrypted() {return m_isEncrypted;}

// SetMessage(string message)
// Updates a message
void Cipher::SetMessage(string message) {m_message = message;}

// ToggleEncrypted()
// Turns (true to false) or (false to true)
void Cipher::ToggleEncrypted() {m_isEncrypted = !m_isEncrypted;}

// Overloaded << operator
// Outputs the message
ostream &operator<<(ostream &output, Cipher &C) {
    output << C.GetMessage();
    return output;
}
