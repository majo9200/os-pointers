// compile: g++ -std=c++14 -o pointers pointers.cpp
#include <iostream>
#include <string>
#include <sstream>
#include <cmath>
#include <cstring>

typedef struct Student {
    int id;
    char *f_name;
    char *l_name;
    int n_assignments;
    double *grades;
} Student;

int promptInt(std::string message, int min, int max);
double promptDouble(std::string message, double min, double max);
void calculateStudentAverage(void *object, double *avg);

int main(int argc, char **argv)
{
    Student student;
    double average;

    // Sequence of user input -> store in fields of `student`
    student.id = promptInt("Please enter the student's id number: ", 0, 999999999);

    
    std::string temp_name;
    while(true)
    {
        std::cout << "Please enter the student's first name: ";
        getline(std::cin, temp_name);
        if(temp_name.empty())
        {
            std::cout << "Sorry, I cannot understand your answer" << std::endl;
        }
        else 
        {
            student.f_name = new char[temp_name.size() + 1];
            std::strcpy(student.f_name, temp_name.c_str());
            break;
        }
    }

    while(true)
    {
        std::cout << "Please enter the student's last name: ";
        getline(std::cin, temp_name);
        if(temp_name.empty())
        {
            std::cout << "Sorry, I cannot understand your answer" << std::endl;
        }
        else 
        {
            student.l_name = new char[temp_name.size() + 1];
            std::strcpy(student.l_name, temp_name.c_str());
            break;
        }
    }

    student.n_assignments = promptInt("Please enter how many assignments were graded: ", 0, 134217728);
    std::cout << std::endl;

    student.grades = new double[student.n_assignments];
    for(int i = 0; i < student.n_assignments; i++)
    {
        student.grades[i] = promptDouble("Please enter grade for assignment " + std::to_string(i) + ": " , 0, 1000);
    }
    std::cout << std::endl;

    // Call `CalculateStudentAverage(???, ???)`
    // Output `average`
    calculateStudentAverage(&student, &average);
    std::cout << "Student: " << student.f_name << " " << student.l_name
            << " [" << student.id << "]" << std::endl;
    std::cout << "  Average grade: " << std::round(10*average)/10 << std::endl;

    return 0;
}

/*
   message: text to output as the prompt
   min: minimum value to accept as a valid int
   max: maximum value to accept as a valid int
*/
int promptInt(std::string message, int min, int max)
{
    int num;
    std::stringstream ss;
    std::string input;
    while(true)
    {
        //print prompt
        std::cout << message;

        //get input and send into stream
        getline(std::cin, input);
        ss << input;

        //if stream has an int, check if stream is empty and num is valid
        if((ss >> num) && !(ss >> input) && !(num < min) && !(num > max))
        {
            return num;
        }

        //print message and reset stream
        std::cout << "Sorry, I cannot understand your answer" << std::endl;
        ss.str("");
        ss.clear();
    }
}

/*
   message: text to output as the prompt
   min: minimum value to accept as a valid double
   max: maximum value to accept as a valid double
*/
double promptDouble(std::string message, double min, double max)
{
    double num;
    std::stringstream ss;
    std::string input;
    while(true)
    {
        //print prompt, send input to stream
        std::cout << message;
        getline(std::cin, input);
        ss << input;

        //if stream has a double, check if stream is empty and num is valid
        if((ss >> num) && !(ss >> input) && !(num < min) && !(num > max))
        {
            return num;
        }

        std::cout << "Sorry, I cannot understand your answer" << std::endl;
        ss.str("");
        ss.clear();
    }
}

/*
   object: pointer to anything - your choice! (but choose something that will be helpful)
   avg: pointer to a double (can store a value here)
*/
void calculateStudentAverage(void *object, double *avg)
{
    Student *student = (Student *) object;
    *avg = 0;
    int num = student->n_assignments;
    for(int i = 0; i < num; i++)
    {
        *avg += student->grades[i];
    }
    *avg /= num;
}
