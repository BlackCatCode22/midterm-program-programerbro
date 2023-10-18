#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <regex>
#include <unordered_map>
#include <algorithm>

using namespace std;

class Animal;

// Habitat class to represent the living environment of animals
class Habitat {
public:
    // Function to Add an Animal to a Habitat
    void addAnimal(const Animal& animal) {
        animals.push_back(animal);
    }

    // Show Animals in the Habitat
    const vector<Animal>& getAnimals() const {
        return animals;
    }

private:
    vector<Animal> animals;
};

// Animal class to represent individual animals
class Animal {
public:
    // Constructor to initialize the animal with basic information
    Animal(const string& name, const string& species, int age, char sex, const string& color, int weight, const string& birthseason)
        : name(name), species(species), age(age), sex(sex), color(color), weight(weight), birthseason(birthseason) {
        genUniqueAnimalID();
        genBirthday();
        numOfTotalAnimals++;
    }

    // Generate a unique ID for the animal based on species
    void genUniqueAnimalID() {
        if (species.length() >= 2) {
            id = species.substr(0, 2) + to_string(++speciesCount[species]);
        } else {
            id = species + to_string(++speciesCount[species]);
        }
    }

    // Set the birthday to the first day of the corresponding season
    void genBirthday() {
        if (birthseason == "spring") {
            birthday = "March 20";
        } else if (birthseason == "summer") {
            birthday = "June 20";
        } else if (birthseason == "fall") {
            birthday = "September 23";
        } else if (birthseason == "winter") {
            birthday = "December 22";
        }
    }

    // Getters for various animal attributes
    string getName() const {
        return name; }
    string getSpecies() const {
        return species; }
    int getAge() const {
        return age; }
    char getSex() const {
        return sex; }
    string getColor() const {
        return color; }
    int getWeight() const {
        return weight; }
    string getBirthseason() const {
        return birthseason; }
    string getBirthday() const {
        return birthday; }
    string getID() const {
        return id; }

    // Static method to get the total number of animals
    static int getNumOfTotalAnimals() {
        return numOfTotalAnimals;
    }

    // Static method to get the count of each species
    static map<string, int> getSpeciesCount() {
        return speciesCount;
    }

private:
    string name;
    string species;
    int age;
    char sex;
    string color;
    int weight;
    string birthseason;
    string birthday;
    string id;
    static map<string, int> speciesCount; // Count of each species
    static int numOfTotalAnimals; // Total number of animals
};

// Static member variable initialization
map<string, int> Animal::speciesCount;
int Animal::numOfTotalAnimals = 0;

// Derived class for Hyena, inherits from Animal
class Hyena : public Animal {
public:
    // Constructor for Hyena, using predefined names for hyenas
    Hyena(int age, char sex, const string& color, int weight, const string& birthseason)
        : Animal(getHyenaName(), "Hyena", age, sex, color, weight, birthseason) {
        numOfHyenas++;
    }

    // Static method to get a predefined name for a hyena
    static string getHyenaName() {
        static vector<string> hyenaNames = {"Shenzi", "Banzai", "Ed", "Zig", "Bud", "Lou", "Kamari", "Wema", "Nne", "Madoa", "Prince Nevarah"};
        return hyenaNames[numOfHyenas % hyenaNames.size()];
    }

    // Static method to get the total number of hyenas
    static int getNumOfHyenas() {
        return numOfHyenas;
    }

private:
    static int numOfHyenas;
};

// Static member variable initialization for hyenas
int Hyena::numOfHyenas = 0;

// Similar classes for Lion, Bear, and Tiger with their own names and counts
class Lion : public Animal {
public:
    Lion(int age, char sex, const string& color, int weight, const string& birthseason)
        : Animal(getLionName(), "Lion", age, sex, color, weight, birthseason) {
        numOfLions++;
    }

    static string getLionName() {
        static vector<string> lionNames = {"Scar", "Mufasa", "Simba", "Kiara", "King", "Drooper", "Kimba", "Nala", "Leo", "Samson", "Elsa", "Cecil"};
        return lionNames[numOfLions % lionNames.size()];
    }

    static int getNumOfLions() {
        return numOfLions;
    }

private:
    static int numOfLions;
};

int Lion::numOfLions = 0;

class Bear : public Animal {
public:
    Bear(int age, char sex, const string& color, int weight, const string& birthseason)
        : Animal(getBearName(), "Bear", age, sex, color, weight, birthseason) {
        numOfBears++;
    }

    static string getBearName() {
        static vector<string> bearNames = {"Yogi", "Smokey", "Paddington", "Lippy", "Bungle", "Baloo", "Rupert", "Winnie the Pooh", "Snuggles", "Bert"};
        return bearNames[numOfBears % bearNames.size()];
    }

    static int getNumOfBears() {
        return numOfBears;
    }

private:
    static int numOfBears;
};

int Bear::numOfBears = 0;

class Tiger : public Animal {
public:
    Tiger(int age, char sex, const string& color, int weight, const string& birthseason)
        : Animal(getTigerName(), "Tiger", age, sex, color, weight, birthseason) {
        numOfTigers++;
    }

    static string getTigerName() {
        static vector<string> tigerNames = {"Tony", "Tigger", "Amber", "Cosimia", "Cuddles", "Dave", "Jiba", "Rajah", "Rayas", "Ryker"};
        return tigerNames[numOfTigers % tigerNames.size()];
    }

    static int getNumOfTigers() {
        return numOfTigers;
    }

private:
    static int numOfTigers;
};

int Tiger::numOfTigers = 0;

// AnimalCounter class to manage and organize animals
class AnimalCounter {
public:
    AnimalCounter() {}

    // Add an animal to the list and update species count
    void addAnimal(const Animal& animal) {
        animals.push_back(animal);
        speciesCount[animal.getSpecies()]++;
    }

    // Organize animals into their respective habitats
    void organizeAnimals() {
        for (const auto& animal : animals) {
            habitats[animal.getSpecies()].addAnimal(animal);
        }
    }

    // Print available habitats
    void printAvailableHabitats() const {
        cout << "Available habitats:" << endl;
        for (const auto& habitat : habitats) {
            cout << habitat.first << endl;
        }
    }

    // Print animals in a specific habitat
    void printHabitatAnimals(const string& habitatName) const {
        auto it = habitats.find(habitatName);
        if (it != habitats.end()) {
            const vector<Animal>& animalsInHabitat = it->second.getAnimals();
            cout << "Animals in " << habitatName << " habitat:" << endl;
            for (const Animal& animal : animalsInHabitat) {
                cout << animal.getName() << endl;
            }
        } else {
            cout << "Habitat not found." << endl;
        }
    }

    // Print detailed information about a specific animal
    void printAnimalInfo(const string& animalName) const {
        for (const auto& habitat : habitats) {
            const vector<Animal>& animalsInHabitat = habitat.second.getAnimals();
            for (const Animal& animal : animalsInHabitat) {
                if (animal.getName() == animalName) {
                    cout << "Animal Info:" << endl;
                    cout << "Name: " << animal.getName() << endl;
                    cout << "Species: " << animal.getSpecies() << endl;
                    cout << "ID: " << animal.getID() << endl;
                    cout << "Age: " << animal.getAge() << " years" << endl;
                    cout << "Sex: " << animal.getSex() << endl;
                    cout << "Birthday: " << animal.getBirthday() << endl;
                    cout << "Color: " << animal.getColor() << endl;
                    cout << "Weight: " << animal.getWeight() << " pounds" << endl << endl;
                    return;
                }
            }
        }
        cout << "Animal not found." << endl;
    }

private:
    vector<Animal> animals;
    map<string, int> speciesCount;
    unordered_map<string, Habitat> habitats;
};

int main() {
    // Import ArrivingAnimals from a text file
    ifstream inputFile("C:\\C++\\Midterm\\arrivingAnimals.txt");
    if (!inputFile.is_open()) {
        cerr << "Failed to open the file." << endl;
        return 1;
    }

    string line;
    AnimalCounter animalCounter;
    //R = Rawstring, (\d+) = Grab Digits, (female|male) = grab either, (.*) grab word
    regex animalPattern(R"((\d+) year old (female|male) (.*), born in (.*), (.*), (\d+) pounds)");

    // Read Arriving Animals, Scan & Extract Data
    while (getline(inputFile, line)) {
        smatch match;
        //Search with regex, search the line gotten to match animalPattern
        if (regex_search(line, match, animalPattern)) {
            int age = stoi(match[1]);
            char sex = match[2].str()[0];
            string speciesInfo = match[3];
            string birthseason = match[4];
            string color = match[5];
            int weight = stoi(match[6]);

            Animal* animal = nullptr;

            // Read Species, Assign to Class based on species, Include Information Given
            if (speciesInfo == "hyena") {
                animal = new Hyena(age, sex, color, weight, birthseason);
            } else if (speciesInfo == "lion") {
                animal = new Lion(age, sex, color, weight, birthseason);
            } else if (speciesInfo == "bear") {
                animal = new Bear(age, sex, color, weight, birthseason);
            } else if (speciesInfo == "tiger") {
                animal = new Tiger(age, sex, color, weight, birthseason);
            }

            if (animal) {
                animalCounter.addAnimal(*animal);
                delete animal;
            }
        }
    }

    inputFile.close();

    // Print total number of animals
    cout << "Total number of animals: " << Animal::getNumOfTotalAnimals() << endl;

    // Print number of each species
    map<string, int> speciesCounts = Animal::getSpeciesCount();
    for (const auto& entry : speciesCounts) {
        cout << "Number of " << entry.first << "s: " << entry.second << endl;
    }

    // Organize animals into habitats
    animalCounter.organizeAnimals();

    // Print available habitats
    animalCounter.printAvailableHabitats();

    // Prompt user to enter the name of the habitat to view animals
    string habitatName;
    cout << "Enter the name of the habitat to view animals: ";
    cin >> habitatName;

    // Print animals in the specified habitat
    animalCounter.printHabitatAnimals(habitatName);

    // Prompt user to enter the name of the animal to get information
    string animalName;
    cout << "Enter the name of the animal to get information: ";
    cin >> animalName;

    // Print detailed information about the specified animal
    animalCounter.printAnimalInfo(animalName);

    return 0;
}
