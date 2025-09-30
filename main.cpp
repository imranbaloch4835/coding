/*#include <iostream>
using namespace std;

class student_profile
{
private:
 string name;
 int rollnumber;
 string degree;
 string city;
 string tehsil;
 string district;
 string province;
 string home_address;
 string fname;
 string caste;
public:
    student_profile(string )
    {


    }

};

int main()
{

}*/

















#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <stdexcept>

class Address {
private:
    std::string permanentAddress, temporaryAddress;

public:
    Address(std::string permAddr, std::string tempAddr) : permanentAddress(permAddr), temporaryAddress(tempAddr) {}

    void displayAddress() const {
        std::cout << "Permanent Address: " << permanentAddress
                  << "\nTemporary Address: " << temporaryAddress << std::endl;
    }
};

class StudentProfile {
private:
    std::string fullName, degree, city, tehsil, district, province, homeAddress, fatherName, familyCaste;
    int rollNumber;
    std::string* addresses; // Dynamic memory for multiple addresses
    int addressCount;
    static int objectCount; // Static member for tracking objects

public:
    // Constructor
    StudentProfile(std::string name, int roll, std::string deg, std::string ct, std::string th,
                   std::string dis, std::string prov, std::string homeAddr, std::string father,
                   std::string caste, int addrCount)
                   : fullName(name), rollNumber(roll), degree(deg), city(ct), tehsil(th),
                     district(dis), province(prov), homeAddress(homeAddr), fatherName(father),
                     familyCaste(caste), addressCount(addrCount) {

        if (!isAlpha(name) || roll <= 0 || addrCount <= 0) {
            throw std::invalid_argument("Invalid input data!");
        }

        addresses = new std::string[addrCount];
        for (int i = 0; i < addrCount; i++) {
            addresses[i] = "Address_" + std::to_string(i + 1); // Example address initialization
        }

        objectCount++; // Increment object count
    }

    // Destructor
    ~StudentProfile() {
        delete[] addresses;
        objectCount--; // Decrement object count
    }

    // Copy Constructor (Deep Copy)
    StudentProfile(const StudentProfile& other) : fullName(other.fullName), rollNumber(other.rollNumber),
                                                  degree(other.degree), city(other.city),
                                                  tehsil(other.tehsil), district(other.district),
                                                  province(other.province), homeAddress(other.homeAddress),
                                                  fatherName(other.fatherName), familyCaste(other.familyCaste),
                                                  addressCount(other.addressCount) {

        addresses = new std::string[addressCount];
        for (int i = 0; i < addressCount; i++) {
            addresses[i] = other.addresses[i];
        }
    }

    // Assignment Operator Overloading (Deep Copy)
    StudentProfile& operator=(const StudentProfile& other) {
        if (this == &other) return *this; // Self-assignment check

        delete[] addresses; // Free existing memory

        fullName = other.fullName;
        rollNumber = other.rollNumber;
        degree = other.degree;
        city = other.city;
        tehsil = other.tehsil;
        district = other.district;
        province = other.province;
        homeAddress = other.homeAddress;
        fatherName = other.fatherName;
        familyCaste = other.familyCaste;
        addressCount = other.addressCount;

        addresses = new std::string[addressCount];
        for (int i = 0; i < addressCount; i++) {
            addresses[i] = other.addresses[i];
        }

        return *this;
    }

    // Overloaded '==' operator
    bool operator==(const StudentProfile& other) const {
        return rollNumber == other.rollNumber;
    }

    // Getter for roll number
    int getRollNumber() const {
        return rollNumber;
    }

    // Display student information
    void displayInfo() const {
        std::cout << "Name: " << fullName << "\nRoll Number: " << rollNumber
                  << "\nDegree: " << degree << "\nCity: " << city << "\nTehsil: " << tehsil
                  << "\nDistrict: " << district << "\nProvince: " << province
                  << "\nHome Address: " << homeAddress << "\nFather's Name: " << fatherName
                  << "\nFamily Caste: " << familyCaste << std::endl;
    }

    // Static method to get object count
    static int getObjectCount() {
        return objectCount;
    }

private:
    // Helper function to validate alphabetical strings
    bool isAlpha(const std::string& str) const {
        return std::all_of(str.begin(), str.end(), ::isalpha);
    }
};

int StudentProfile::objectCount = 0; // Initialize static member

class StudentDatabase {
private:
    std::vector<StudentProfile> studentRecords; // Collection of student profiles

public:
    // Add a new student
    void addStudent(const StudentProfile& student) {
        studentRecords.push_back(student);
    }

    // Search for a student by roll number
    StudentProfile* searchStudent(int rollNumber) {
        for (auto& student : studentRecords) {
            if (student.getRollNumber() == rollNumber) {
                return &student;
            }
        }
        return nullptr; // Not found
    }

    // Display all registered students
    void displayAll() const {
        for (const auto& student : studentRecords) {
            student.displayInfo();
            std::cout << "----------------------" << std::endl;
        }
    }
};

int main() {
    try {
        // Create a student database
        StudentDatabase database;

        // Add a few students
        StudentProfile student1("John", 101, "CS", "City1", "Tehsil1", "District1", "Province1",
                                "Home1", "Father1", "Caste1", 2);
        StudentProfile student2("Alice", 102, "IT", "City2", "Tehsil2", "District2", "Province2",
                                "Home2", "Father2", "Caste2", 2);

        database.addStudent(student1);
        database.addStudent(student2);

        // Display all students
        database.displayAll();

        // Search for a specific student
        int searchRoll = 101;
        StudentProfile* found = database.searchStudent(searchRoll);
        if (found) {
            std::cout << "Student Found:" << std::endl;
            found->displayInfo();
        } else {
            std::cout << "Student with Roll Number " << searchRoll << " not found." << std::endl;
        }

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}
