/*
Natalie Yam
Final Project Spring 2020
Compiled on macOS
cd desktop/cs110/finalproject
c++ -o email email.cpp
*/

#include <fstream>
#include <iostream>
#include <string>
#include <iomanip>
#include <list>
using namespace std;

void eliminateDuplicate(string emailList[], int listSize, string outputFile){
	int prev = 0; //for previous index
	//eliminating duplicates
	for(int i = 0; i < listSize; i++){
		if(emailList[i] != emailList[prev])
			emailList[++prev] = emailList[i];
	}
	int count = prev + 1;

	//printing emails to ouputfile and console
	ofstream fileToSaveEmails;
	fileToSaveEmails.open(outputFile);
	for (int i = 0; i < count; i++) {
		cout << emailList[i] << "\n";
		if( i == count - 1){ // so that theres no semicolon after the last email
			fileToSaveEmails << emailList[i];
		}
		else{
			fileToSaveEmails << emailList[i] + "; ";
		}

	}//for
	fileToSaveEmails.close();
	cout << "There were " << count << " emails found. " << "\n";
	cout << "Open the output file and copy/paste its contents into the to, cc, or bcc field of any email message.";
	cout << "\n" << "It is best to use the bcc field so that everyone's email address does";
	cout << " not appear in the message, to protect their privacy.";
}

void sort(string emailList[], int listSize){
	for (int i = 0; i < listSize; i++){
    for (int j = i + 1; j < listSize; j++){
      if (emailList[i] > emailList[j]){
        // swap code
        string temp = emailList[i];
        emailList[i] = emailList[j];
        emailList[j] = temp;
      } // if
    } // for
  } // for
}


bool isValidEmailCharacter(char c) {
	bool result = false;
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
	  result = true;
	else if (c >= '0' && c <= '9')
	  result = true;
	else if (c == '_' || c == '+' || c == '-' || c == '.')
	  result = true;
	return result;
}

string getMail(string lineFromFile){
  string email;
	for (int i = 0; i < lineFromFile.length(); i++) {
        if (lineFromFile[i] != '@')//if @ sign not found keep looking through the file
            continue;
        //traveling to the start of the email
        int start;
        for (start = i - 1; start >= 0; --start) {
            if (!isValidEmailCharacter(lineFromFile[start]))
                break;
        }
        ++start;
        //traveling to the end of the email
        int end;
        for (end = i + 1; end < lineFromFile.length(); ++end) {
            if (!isValidEmailCharacter(lineFromFile[end]))
                break;
        }

        email = lineFromFile.substr(start, end-start);//save only the email
    }
    return email;
}

void emailValidation(string emailList[], string outputFile, string email, int listSize) {
	sort(emailList,listSize);// sorts emails, go to sort function for more detail
	eliminateDuplicate(emailList,listSize, outputFile);// eliminates duplicates, go to function for more detail
}

int main() {
	string inputFile;
    cout << "Enter file name containing emails [press enter to use default file]: ";
	getline(cin, inputFile);

  string outputFile;
  cout << "Enter text file to output emails to [press enter to use default file]: ";
  getline(cin,outputFile);

  //checking if user pressed enter to use default file
  if (inputFile == "" && outputFile == ""){
    inputFile = "fileContainingEmails.txt";
    outputFile = "copyPasteMyEmails.txt";
  }
  else if (inputFile != "" && outputFile == ""){
    outputFile = inputFile;
  }

  //open the file containing emails
	ifstream fin;
  fin.open(inputFile);
  //creating list to store emails
	int SIZE = 1000;
	int nEmails = 0;
	string emailList[SIZE];
	// var declaration
	string line;
	string email;

	if (fin.is_open()) {
    while (getline(fin, line)){
      for(int i = 0; i < line.length(); i++){
        if (line[i] == '@'){
    		  email = getMail(line);//if @ sign is found use the fuction getMail()
					if (nEmails < SIZE)
      		emailList[nEmails++] = email;// adding emails to list
        }//if
      }//for
    }//while
  }//if
  fin.close();

	//counting the total amount of emails
	int listSize = 0;
	for (int i = 0; i < nEmails; i++){
		listSize++;
	}
	//if no emails are found exit the program
	if (listSize == 0){
		cout << "No emails found";
		return 0;
	}
	else{
		emailValidation(emailList, outputFile, email, listSize);//go to email validation function
	}
	return 0;
}
