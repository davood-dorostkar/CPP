#ifndef STUDENTS_H
#define STUDENTS_H
#include <iostream>
#include <stdio.h>
class Student
{
    public:
    int grades[10];
    int studentID;
    public:
    void setStudentID(int id);
    void setGrade(int id,int grade);
    void printGrades();
    int getMin();
    int getMax();
    float getAverageGrade();


};

float Student::getAverageGrade()
{
    float avg=0;
    for(int i=0; i<10; i++)
    {
        avg+=grades[i];
    }
    return avg/10;
}

int Student::getMax()
{
    int max=0;
    for(int i=0; i<10; i++)
    {
        if(grades[i]>max) max=grades[i];
    }
    return max;
}

int Student::getMin()
{
    int min=100;
    for(int i=0; i<10; i++)
    {
        if(grades[i]<min) min=grades[i];
    }
    return min;
}

void Student::setStudentID(int id)
{
    studentID=id;
}

void Student::setGrade(int id,int grade)
{
    grades[id]=grade;
}

void Student::printGrades()
{
    for(int i=0; i<10; i++)
    {
        std::cout<<grades[i];
    }
    std::cout<<std::endl;
}
//********************
class CourseEnrollment
{
    public:
    Student students[6];
    int courseMinGrade;
    int courseMaxGrade;
    float courseAvgGrade;
    int grades[60];
    void addStudents(Student* students);
    int* getAllGrades();
    int* sortAllGrades();
    int getMinGrade();
    int getMaxGrade();
    float getAvgGrade();
};

int CourseEnrollment::getMinGrade()
{
    int min=100;
    for(int i=0; i<60; i++)
    {
        if(grades[i]<min) min=grades[i];
    }
    return min;
}
int CourseEnrollment::getMaxGrade()
{
    int max=0;
    for(int i=0; i<60; i++)
    {
        if(grades[i]>max) max=grades[i];
    }
    return max;
}
float CourseEnrollment::getAvgGrade()
{
    float avg=0;
    for(int i=0; i<60; i++)
    {
        avg+=grades[i];
    }
    return avg/60;
}

int* CourseEnrollment::sortAllGrades()
{
    for(int i=0; i<60; i++)
    {
        for(int j=i; j>0; j--)
        {
            if(grades[i]<grades[i-1])
            {
                int temp=grades[i];
                grades[i]=grades[i-1];
                grades[i-1]=temp;
            }
        }
    }
    return grades;
}

int* CourseEnrollment::getAllGrades()
{
    for(int i=0; i<6; i++)
    {
        for(int j=0; j<10; j++)
        {
            grades[10*i+j]=students[i].grades[j];
            // std::cout<<students[i].grades[j];
        }
    }
    return grades;
}

void CourseEnrollment::addStudents(Student* studentsIn)
{
    for(int i=0; i<6; i++)
    {
        students[i]=studentsIn[i];
    }
}
#endif // STUDENTS_H
