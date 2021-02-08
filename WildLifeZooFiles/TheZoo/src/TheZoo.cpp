#include <iostream>
#include <jni.h>
#include <vector>
#include <fstream>
#include <string>
#include <iomanip>
#include <algorithm>
#include <cctype>
#include <locale>
#include <sstream>



using namespace std;

#include "TheZoo.h"


void GenerateData()               //DO NOT TOUCH CODE IN THIS METHOD
{
     JavaVM *jvm;                      // Pointer to the JVM (Java Virtual Machine)
     JNIEnv *env;                      // Pointer to native interface
                                                              //================== prepare loading of Java VM ============================
     JavaVMInitArgs vm_args;                        // Initialization arguments
     JavaVMOption* options = new JavaVMOption[1];   // JVM invocation options
     options[0].optionString = (char*) "-Djava.class.path=";   // where to find java .class
     vm_args.version = JNI_VERSION_1_6;             // minimum Java version
     vm_args.nOptions = 1;                          // number of options
     vm_args.options = options;
     vm_args.ignoreUnrecognized = false;     // invalid options make the JVM init fail
                                                                          //=============== load and initialize Java VM and JNI interface =============
     jint rc = JNI_CreateJavaVM(&jvm, (void**)&env, &vm_args);  // YES !!
     delete options;    // we then no longer need the initialisation options.
     if (rc != JNI_OK) {
            // TO DO: error processing...
            cin.get();
            exit(EXIT_FAILURE);
     }
     //=============== Display JVM version =======================================
     cout << "JVM load succeeded: Version ";
     jint ver = env->GetVersion();
     cout << ((ver >> 16) & 0x0f) << "." << (ver & 0x0f) << endl;

     jclass cls2 = env->FindClass("ZooFileWriter");  // try to find the class
     if (cls2 == nullptr) {
            cerr << "ERROR: class not found !";
     }
     else {                                  // if class found, continue
            cout << "Class MyTest found" << endl;
            jmethodID mid = env->GetStaticMethodID(cls2, "createZooFile", "()V");  // find method
            if (mid == nullptr)
                   cerr << "ERROR: method void createZooFile() not found !" << endl;
            else {
                   env->CallStaticVoidMethod(cls2, mid);                      // call method
                   cout << endl;
            }
     }


     jvm->DestroyJavaVM();
     cin.get();
}
bool ValidateNursing(string t_nursingString) { // validates nursing value is either a 0 or 1
    if(t_nursingString != "0" && t_nursingString != "1"){ // return true if valid value
        return false;
    }
    else {
        return true;
    }
}
bool ValidateInteger(int t_integer, int t_length) { // validates integer
    if (to_string(t_integer).length() > t_length || to_string(t_integer).length() < 1) { // ensures that the user input is of the right length based on the input field
        return false;
    }
    else {
        return true;
    }
}

bool ValidateStringInput(string t_str) { // validates strings
    if (t_str.length() > 15) { // ensures strings are the right length
        return false;
    }
    else {
        return true;
    }
}

bool ValidateTypeInput(string t_type) { // validates type
    if (!ValidateStringInput(t_type) || (t_type != "mammal" && t_type != "oviparous" && t_type != "Mammal" && t_type != "Oviparous")) { // must be either mammal or oviparous type
        return false;
    }
    else {
    	return true;
    }
}

string AddAnimal()
{
	int tempTrackNum; // saved to user input
    string tempAnimalName; // saved to user input
    string tempAnimalType; // saved to user input
    string tempAnimalSubtype; // saved to user input
    string tempNursingString; // saved to user input
    bool tempNursing = false; // saved to user input
    int tempNumEggs;          // saved to user input

    bool validTrackNumInput = false; // sets validation to false before running through validation function
    bool validNameInput = false;     // sets validation to false before running through validation function
    bool validTypeInput = false;     // sets validation to false before running through validation function
    bool validSubtypeInput = false;  // sets validation to false before running through validation function
    bool validEggNumInput = false;   // sets validation to false before running through validation function
    bool validNursingInput = false;  // sets validation to false before running through validation function

    string continueInput; // tracks if user wants to save additon or discard

    while(!validTrackNumInput) { // repeat until valid input
	    cout << "Track Number: " << endl; // get user input
	    if (!(cin >> tempTrackNum) || !ValidateInteger(tempTrackNum, 6)) { // runs validation function on user input based on program requirements
            cin.clear(); // reset user input
            cin.ignore(); // reset user input
	        cout << "Invalid number input" << endl; // error message
	        cout << "Please enter a valid number between 1 - 999999" << endl;
	    }
	    else {
	        validTrackNumInput = true; // break out of while loop if validation passes
            cin.clear(); // reset user input
            cin.ignore(); // reset user input
	    }
	}

	while(!validNameInput){ // repeat until valid input
	    cout << "Name: " << endl; // get user input
	    if (!(getline(cin, tempAnimalName)) || !ValidateStringInput(tempAnimalName)) { // runs validation function on user input based on program requirements
            cin.clear(); // reset user input
            cin.ignore(); // reset user input
	        cout << "Invalid name input" << endl; // error message
	        cout << "Please enter a string less than 16 characters long" << endl;
        }
        else {
            validNameInput = true; // break out of while loop if validation passes
        }
	}

	while(!validTypeInput){ // repeat until valid input
        cout << "Type: " << endl;                                                    // get user input
        if (!(getline(cin, tempAnimalType)) || !ValidateTypeInput(tempAnimalType)) { // runs validation function on user input based on program requirements
            cout << "Invalid type input" << endl;
	        cout << "Please enter either mammal or oviparous" << endl;
        }
        else {
            validTypeInput = true; // break out of while loop if validation passes
        }
	}

	while(!validSubtypeInput){ // repeat until valid input
        cout << "Subtype: " << endl;                                                         // get user input
        if ((!getline(cin, tempAnimalSubtype)) || !ValidateStringInput(tempAnimalSubtype)) { // runs validation function on user input based on program requirements
            cin.clear(); // reset user input
            cin.ignore(); // reset user input
	        cout << "Invalid subtype input" << endl;
	        cout << "Please enter a string less than 16 characters long" << endl;
        }
        else {
            validSubtypeInput = true; // break out of while loop if validation passes
        }
	}

	while(!validEggNumInput){ // repeat until valid input
        cout << "Number of Eggs: " << endl;                              // get user input
        if (!(cin >> tempNumEggs) || !ValidateInteger(tempNumEggs, 2)) { // runs validation function on user input based on program requirements
            cin.clear(); // reset user input
            cin.ignore(); // reset user input
	        cout << "Invalid integer input" << endl;
	        cout << "Please enter a valid number between 1 - 99" << endl;
        }
        else {
            validEggNumInput = true; // break out of while loop if validation passes
            cin.clear(); // reset user input
            cin.ignore(); // reset user input
	    }
	}

	while(!validNursingInput){ // repeat until valid input
        cout << "Nursing? (1 for yes, 0 for no): " << endl;                              // get user input
        if (!(getline(cin, tempNursingString)) || !ValidateNursing(tempNursingString)) { // runs validation function on user input based on program requirements
            cout << "Invalid integer input" << endl;
	        cout << "Please either enter 1 for yes or 0 for no" << endl;
            cin.clear(); // reset user input
            cin.ignore(); // reset user input
        }
        else {
	        if(tempNursingString == "1"){
                tempNursing = true; // set to correct boolean value
            }
            validNursingInput = true; // break out of while loop if validation passes
        }
	}
	cout << "Press 'q' to discard changes or any other key to keep changes." << endl; // confirm save with user
	cin >> continueInput;

	if (continueInput != "q"){ // if save was confirm
		string returnString; // gets saved as a string of new animal information to be saved in a vector later
		returnString = to_string(tempTrackNum) + "||" + tempAnimalName + "||" + tempAnimalType + "||" + tempAnimalSubtype + "||" + to_string(tempNumEggs) + "||" + tempNursingString;
		return returnString; // returns new animal information
	}
	else { // if save was not confirmed
		return "quit"; // tell the calling function to quit
	}

}

void RemoveMammal(vector<MammalSubtype*>& mammalList, int mammalId) { // remove mammal from original vector
	for (int i = 0; i < mammalList.size(); i++){
		if (mammalId == mammalList[i]->getTrackNum()){
			mammalList.erase(mammalList.begin() + i);
		}
	}
}

void RemoveOviparous(vector<OviparousSubtype*>& oviparousList, int oviparousId) { // remove oviparous from original vector
    for (int i = 0; i < oviparousList.size(); i++){
		if (oviparousId == oviparousList[i]->getTrackNum()){
			oviparousList.erase(oviparousList.begin() + i);
		}
	}
}

int SearchMammals(vector<MammalSubtype*> mammalList, int userInput) { // searches mammal vector for user input
	int foundAnimal = 0;
	for (int i = 0; i < mammalList.size(); i++){ // loop through vector
		if (userInput == mammalList[i]->getTrackNum()) { // if user input equals animal tracking num,
			foundAnimal = mammalList[i]->getTrackNum(); // save locally
		}
	}
	return foundAnimal; // return tracking number of animal
}

int SearchOviparous(vector<OviparousSubtype*> oviparousList, int userInput) { // searches oviparous vector for user input
    int foundAnimal = 0;
	for (int i = 0; i < oviparousList.size(); i++){// loop through vector
		if (userInput == oviparousList[i]->getTrackNum()){// if user input equals animal tracking num,
            foundAnimal = oviparousList[i]->getTrackNum(); // save locally
        }
	}
    return foundAnimal; // return tracking number of animal
}

string LoadDataFromFile(string t_fileName) { // opens txt file and save content to string
    string fileData;
    ifstream in(t_fileName.c_str());

    if(!in) {
        cerr << "Cannot open the File : "<<t_fileName<<endl; // catche errors where we can't open the file
    }

    string str;

    while (getline(in, str)) { // loop through each line
        // Line contains string of length > 0 then save it in vector
        if(str.size() > 0)
        	fileData = fileData + "||" + str; // format as a string that will be parsed later
    }
    return fileData;

}

string Trim(const string& str, const string& whitespace = " \t") { // used to remove extra whitespace from strings
    const auto strBegin = str.find_first_not_of(whitespace);
    if (strBegin == string::npos)
        return ""; // no content

    const auto strEnd = str.find_last_not_of(whitespace); // find index of last element
    const auto strRange = strEnd - strBegin + 1; // find begining of whitespace

    return str.substr(strBegin, strRange); // return Trimmed string
}

void SaveDataToFile(vector<OviparousSubtype*> oviparousList, vector<MammalSubtype*> mammalList) { // save both vectors of subtypes back to txt file
	ofstream ofs;
	ofs.open("zoodata.txt", ofstream::out | ofstream::trunc); // open txt file and delete contents
	for (int i = 0; i < oviparousList.size(); i++) { // loop over oviparous list and write contents to txt file
		ofs << right << setfill('0') << setw(6) << Trim(to_string(oviparousList[i]->getTrackNum()));
		ofs << left << setfill(' ') << setw(15) << Trim(oviparousList[i]->getName());
		ofs << left << setfill(' ') << setw(15) << "Oviparous";
		ofs << left << setfill(' ') << setw(15) << Trim(oviparousList[i]->getSubtype());
		ofs << left << setfill(' ') << setw(2) << Trim(to_string(oviparousList[i]->getNumberOfEggs()));
		ofs << right << "0 " << endl;
	}
	for (int i = 0; i < mammalList.size(); i++) { // loop over mammal list and write contents to txt file
        ofs << right << setfill('0') << setw(6) << Trim(to_string(mammalList[i]->getTrackNum()));
		ofs << left << setfill(' ') << setw(15) << Trim(mammalList[i]->getName());
		ofs << left << setfill(' ') << setw(15) << "Mammal";
		ofs << left << setfill(' ') << setw(15) << Trim(mammalList[i]->getSubtype());
		ofs << "0 ";
		if (mammalList[i]->getNursing() == false ){
			ofs << "0 " << endl;
		}
		else {
			ofs << "1 " << endl;
		}
    }
    ofs.close(); // close file
}

void DisplayMenu() { // display menu options
	cout << "Please press a number 1-6 to execute a menu item: " << endl;
	cout << "[1] Load Animal Data" << endl;
	cout << "[2] Generate Data" << endl;
	cout << "[3] Display Animal Data" << endl;
	cout << "[4] Add Record" << endl;
	cout << "[5] Delete Record" << endl;
	cout << "[6] Save Animal Data" << endl;
}

vector<string> Split(string str, string token) { // function that Splits string based on token parameter
    vector<string>result;
    while(str.size()) {
        int index = str.find(token); // find where the token is in the string
        if(index!=string::npos){ // if the token exsists in the string, find each index and add the content to the result vector
            result.push_back(str.substr(0,index));
            str = str.substr(index+token.size());
            if(str.size()==0)result.push_back(str);
        }else{
            result.push_back(str); // if the token doesn't exsist in the string, the vector will just be the string
            str = "";
        }
    }
    return result;
}

int PromptUser(){
    int userInput;
	bool validDataType = false;

	while (!validDataType) { // ask the user to input a value until we validate the datatype with the code following
	    try {
	        DisplayMenu();
	        if (!(cin >> userInput)) { // if the user enters a value that isn't an integer
	            cin.clear(); // reset user input
	            cin.ignore(); // reset user input
	            throw(validDataType);                                // throw error
	        }
	        else {
	            validDataType = true; // tell program that the user entered correct data type
	        }
	    }
	    catch (bool t_validDataType) { // catch error
	        cout << "Please enter a number 1-6" << endl; // tell user what they did wrong
	    }
	}
    return userInput;
}

bool AskToQuit() { // asks user if they want to end program
    char tempChar;

    cout << "Press 'q' to quit or any other key to continue" << endl;
    cin >> tempChar;
    if (tempChar == 'q'){
    	cout << "Goodbye"; // goodbye message
        return true;
    }
    else { // give some space and re-show user menu
        cout << endl;
        cout << endl;
        return false;
    }

}

int main() {
	MammalSubtype* mammalPtr = nullptr;
	OviparousSubtype* oviparousPtr = nullptr;
	vector<MammalSubtype*> mammalList; // saves all Mammal instances
    vector<OviparousSubtype *> oviparousList; // saves all Oviparous instances
    string fileData; // saves file data as string
    vector<string> fileDataVector; // saves file data after file data string has been parsed
	int userInput; // tracks user input
	bool quit = false; // tracks user intention to continue

while (!quit) { // loop until user wants to quit
    userInput = PromptUser(); // displays menu
    if (userInput == 1) {
    	int invalidSubtypes = 0; // keeps track of invalid lines in txt file

        fileData = LoadDataFromFile("zoodata.txt"); // load txt file as string
        fileDataVector = Split(fileData, "||"); // parse string to vector
        for (string& line : fileDataVector) { // loop through vector
        	if (line[21] == 'o' || line[21] == 'O') { // if animal is oviparous, use Oviparous methods to save data
        		oviparousPtr = new OviparousSubtype;
        		oviparousPtr->setName(line.substr(6, 15));
        		oviparousPtr->setTrackNum(stoi(line.substr(0, 6)));
        		oviparousPtr->setNumberOfEggs(stoi(line.substr(51,2)));
                oviparousPtr->setSubtype(line.substr(36, 15));
                oviparousList.push_back(oviparousPtr); // add new instance to the back of our master Oviparous list
        	}
        	else if (line[21] == 'm' || line[21] == 'M'){// if animal is mammal, use Mammal methods to save data
        	    mammalPtr = new MammalSubtype;
        		mammalPtr->setName(line.substr(6, 15));
        		mammalPtr->setTrackNum(stoi(line.substr(0, 6)));
                if (line.back() == '0'){
                	mammalPtr->setNursing(false);
                }
                else {
                	mammalPtr->setNursing(true);
                };
                mammalPtr->setSubtype(line.substr(36, 15));
                mammalList.push_back(mammalPtr); // add new instance to the back of our master Mammal list
            }
        	else {
        		invalidSubtypes = invalidSubtypes + 1; // keep track of invalid data
        	};
        }
    	cout << "Your animals have successfully been loaded" << endl; // success message
    	if (invalidSubtypes > 1) { // warn user if there were invalid subtypes
    		cout << "Warning: there were " << invalidSubtypes << " invalid entries in the text file. Please make sure that the animal subtype is either a mammal or oviparous.";
    	};
        quit = AskToQuit(); // asks user if they want to end program
    }
    else if (userInput == 2) { // call Java code to generate data to txt file
        GenerateData();
    }
    else if (userInput == 3) { // display data
        if (mammalList.empty() && oviparousList.empty()) { // if data hasn't been loaded, tell user and give instructions
            cout << "The animals have not been loaded." << endl;
			cout << "Try Pressing '1' at the original menu to load the animals." << endl;
			cout << endl;
			cout << endl;
        }
        else { // display columns headers
			cout << left << setw(10) << "Track #";
			cout << left << setw(10) << "||";
			cout << left << setw(10) << "Name";
			cout << left << setw(10) << "||";
			cout << left << setw(10) << "Type";
			cout << left << setw(10) << "||";
			cout << left << setw(10) << "Subtype";
			cout << left << setw(10) << "||";
			cout << left << setw(10) << "Eggs";
			cout << left << setw(10) << "||";
			cout << left << setw(10) << "Nursing";
			cout << left << setw(10) << "||" << endl;

			for (int i = 0; i < mammalList.size(); i++) { // loop through mammalList and display data in appropriate columns
				string nursing = "1";
				if (!mammalList[i]->getNursing()) {
					nursing = "0";
				}
				cout << left << setw(10) << to_string(mammalList[i]->getTrackNum());
				cout << left << setw(10) << "||";
				cout << left << setw(10) << Trim(mammalList[i]->getName());
				cout << left << setw(10) << "||";
				cout << left << setw(10) << "Mammal";
				cout << left << setw(10) << "||";
				cout << left << setw(10) << Trim(mammalList[i]->getSubtype());
				cout << left << setw(10) << "||";
				cout << left << setw(10) << "0";
				cout << left << setw(10) << "||";
				cout << left << setw(10) << nursing;
				cout << left << setw(10) << "||" << endl;
			}

			for (int i = 0; i < oviparousList.size(); i++) { // loop through oviparousList and display data in appropriate columns
                cout << left << setw(10) << to_string(oviparousList[i]->getTrackNum());
				cout << left << setw(10) << "||";
				cout << left << setw(10) << Trim(oviparousList[i]->getName());
				cout << left << setw(10) << "||";
				cout << left << setw(10) << "Mammal";
				cout << left << setw(10) << "||";
				cout << left << setw(10) << Trim(oviparousList[i]->getSubtype());
				cout << left << setw(10) << "||";
				cout << left << setw(10) << oviparousList[i]->getNumberOfEggs();
				cout << left << setw(10) << "||";
				cout << left << setw(10) << "0";
				cout << left << setw(10) << "||" << endl;
            }
        }
    	quit = AskToQuit(); // asks user if they want to end program
    }
    else if (userInput == 4) { // add new animal
    	string newAnimalString;
    	vector<string> newAnimalVector;

    	newAnimalString = AddAnimal(); // prompt user for input
    	if (newAnimalString != "quit") {
    		newAnimalVector = Split(newAnimalString, "||"); // split result string to vector
    		if (newAnimalVector[2] == "mammal" || newAnimalVector[2] == "Mammal"){ // save new MammalSubtype instance according to vector data
        	    mammalPtr = new MammalSubtype;
        		mammalPtr->setName(newAnimalVector[1]);
        		mammalPtr->setTrackNum(stoi(newAnimalVector[0]));
                if (newAnimalVector[5] == "0"){
                	mammalPtr->setNursing(false);
                }
                else {
                	mammalPtr->setNursing(true);
                };
                mammalPtr->setSubtype(newAnimalVector[3]);
                mammalList.push_back(mammalPtr);
    		}
    		else { // save new OviparousSubtype instance according to vector data
        	    oviparousPtr = new OviparousSubtype;
        		oviparousPtr->setName(newAnimalVector[1]);
        		oviparousPtr->setTrackNum(stoi(newAnimalVector[0]));
                oviparousPtr->setNumberOfEggs(stoi(newAnimalVector[5]));
                oviparousPtr->setSubtype(newAnimalVector[4]);
                oviparousList.push_back(oviparousPtr);
    		}
    		cout << "Your new animal has successfully been saved." << endl;
    	}
    	quit = AskToQuit(); // asks user if they want to end program
    }
    else if (userInput == 5) { // removes animal
    	int mammalFound = 0;
    	int oviparousFound = 0;
    	int userInput;

    	cout << "Add the tracking number of the animal that you want to remove: " << endl; // gather user input
    	cin >> userInput;
    	mammalFound = SearchMammals(mammalList, userInput); // see if there is a mammal in our list that has the user-generated tracking num
        oviparousFound = SearchOviparous(oviparousList, userInput); // see if there is a oviparous in our list that has the user-generated tracking num
        if (mammalFound == 0 && oviparousFound == 0) { // let the user know if the animal they entered doesn't exsist
    		cout << "The tracking number that you entered does not exist." << endl;
    	}
    	if (mammalFound != 0 && oviparousFound == 0) {
    		RemoveMammal(mammalList, mammalFound); // removes found mammal from vector
    		cout << "The animal was successfully removed" << endl; // let user know
    	};
    	if (mammalFound == 0 && oviparousFound != 0) {
    		RemoveOviparous(oviparousList, oviparousFound); // removes found oviparous from vector
    		cout << "The animal was successfully removed" << endl; // lets user know
    	};

    }
    else if (userInput == 6) {
    	SaveDataToFile(oviparousList, mammalList); // saves data in our two vectors to the txt file
    	cout << "Your animal data has been saved." << endl;
    }

}
	return 1;

}
