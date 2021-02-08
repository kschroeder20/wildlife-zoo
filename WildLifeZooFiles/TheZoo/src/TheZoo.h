#ifndef THE_ZOO_H
#define THE_ZOO_H

#include <string>
#include <memory>

using namespace std;

class Animal // Animal class
{
public: // create setters, getters, and attributes based on diagram
	void setName(string t_name) {
		name = t_name;
	}
	void setTrackNum(int t_trackNum) {
		trackNum = t_trackNum;
	}
    string getName() {
        return name;
    }
    int getTrackNum() {
        return trackNum;
    }

private:
    string name;
    int trackNum;
};

class Mammal : public Animal
{ // Mammal class inherits from Animal
public:
    bool nursing = false;
	void setNursing(bool t_nursing){
		nursing = t_nursing;
	}
	bool getNursing(){
		return nursing;
	};
};

class Oviparous : public Animal
{ // Oviparous class inherits from Animal
public:
    int numberOfEggs = 0;
    void setNumberOfEggs(int t_numEggs){
		numberOfEggs = t_numEggs;
    }
    int getNumberOfEggs() {
    	return numberOfEggs;
    }
};

class MammalSubtype : public Mammal
{ // MammalSubtype (i.e. 'Dog, Cat, etc') will inherit from Mammal class
public:
	MammalSubtype(string t_name = "undefined", int t_trackNum = 0, int t_numberOfEggs = 0){};
    void setSubtype(string t_subtype) {
        subtype = t_subtype;
    };
    string getSubtype() {
    	return subtype;
    }
private:
    string subtype;
};

class OviparousSubtype : public Oviparous
{ // OviparousSubtype (i.e. 'Bird, Bat, Whale, etc.' will inherit from Oviparous class)
public:
	OviparousSubtype(string t_name = "undefined", int t_trackNum = 0, bool t_nursing = false){};
    void setSubtype(string t_subtype) {
        subtype = t_subtype;
    };
    string getSubtype(){
    	return subtype;
    }
private:
    string subtype;
};

#endif
