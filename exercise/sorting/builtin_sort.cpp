#include <iostream>
#include <string>

using namespace std;

struct Student{
    int id;
    float score;

    bool operator<(const Student &other) const{
        return score < other.score;
    }
};

int main(){

    string file_name = "sort-rand-19999999.txt";
    FILE *fp = fopen(file_name.c_str(), "r");
    if(fp == NULL){
        cout << "File not found" << endl;
        return 0;
    }
    // get data
    Student *students = new Student[20000000];

    int id;
    float score;
    int count = 0;
    while(fscanf(fp, "std-%d: %f\n", &id, &score) != EOF){
        students[count].id = id;
        students[count].score = score;
        count++;
    }

    fclose(fp);

    // sort
    sort(students, students + count);
    cout<<"Sorted"<<endl;
}