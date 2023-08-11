#ifndef CLASSROOM_H
#define CLASSROOM_H
#include <iostream>
#include <stdio.h>
#include "students.h"

const int CLASS_SIZE = 6;
class Classroom
{
public:
    Classroom() {}
    void analysis()
    {
        //Use two classes, student and courseEnrollment
        Student studentsInClass[CLASS_SIZE];
        CourseEnrollment course1;

        //there are 100 students to be enrolled
        static int studentNumber = 1000;
        int grade;
//        int userInput;

        //asign student id to each student
        for(int i = 0; i < CLASS_SIZE; i++)
        {
            studentsInClass[i].setStudentID(studentNumber);
            studentNumber++;
        }

        //assign grades to all students
        for(int i = 0; i <CLASS_SIZE; i++)
        {
          for(int j = 0; j <10 ; j++)
            {
                scanf("%d", &grade);
                studentsInClass[i].setGrade(j,grade);
            }
        }

        //print out all students grades
        for(int i = 0; i < CLASS_SIZE; i++)
        {
            studentsInClass[i].printGrades();
            std::cout<<"\nMin grade = "<<studentsInClass[i].getMin()<<"\n";
            std::cout<<"Max grade = "<<studentsInClass[i].getMax()<<"\n";
            std::cout<<"Grade Average = "<<studentsInClass[i].getAverageGrade()<<"\n\n";
        }

        course1.addStudents(studentsInClass);

        int *allGrades;
        allGrades = course1.getAllGrades();
        allGrades = course1.sortAllGrades();
        std::cout<<"\n\nALLGRADES\n";
        std::cout<<allGrades<<std::endl;
        std::cout<<"Lowest grade for entire course = "<<course1.getMinGrade()<<"\n";
        std::cout<<"Highest grade for entire course = "<<course1.getMaxGrade()<<"\n";
        std::cout<<"Avg grade for entire course = "<<course1.getAvgGrade()<<"\n";

    }

};

#endif // CLASSROOM_H
