#include <stdio.h>

typedef struct {
	int day;
	int month;
	int year;
} Birthday;

typedef struct {
	int num_courses;
	float gpa;
} Courses;

typedef struct {
	int id;
	int age;
	Birthday birthday;
	Courses courses;
} Student;

int main()
{
	//Cannot declare constant strings because we have not learned them yet
	
	FILE *fp = fopen("input.txt","r");
	
	if(fp==NULL){
		printf("Failed to open file\n");
		return -1;
	}
	
	int num_students;
	fscanf(fp, "%d" , &num_students);

	Student student_records[num_students];
	
	for(int i=0; i<num_students; i++){
		fscanf(fp, "%d", &student_records[i].id);
		fscanf(fp, "%d", &student_records[i].age);
		fscanf(fp, "%d", &student_records[i].birthday.day);
		fscanf(fp, "%d", &student_records[i].birthday.month);
		fscanf(fp, "%d", &student_records[i].birthday.year);
		fscanf(fp, "%d", &student_records[i].courses.num_courses);
		
		float sum = 0;
		for(int j=0; j<student_records[i].courses.num_courses; j++){
			float grade;
			fscanf(fp, "%f", &grade);
			sum +=  grade;
		}
		float average = sum / student_records[i].courses.num_courses;
		student_records[i].courses.gpa = average;
	}

	FILE * fo = fopen("output.txt", "w");
	
	for(int i=0; i<num_students; i++){
		fprintf(fo, "Student #%d:\n\n", i+1);
		fprintf(fo, "ID: %d\n", student_records[i].id);
		fprintf(fo, "Age: %d\n", student_records[i].age);
		fprintf(fo, "Birthday (DD-MM-YYYY): %d-%d-%d\n", student_records[i].birthday.day, student_records[i].birthday.month, student_records[i].birthday.year);
		fprintf(fo, "Number of courses: %d\n", student_records[i].courses.num_courses);
		fprintf(fo, "GPA: %.2f\n\n\n", student_records[i].courses.gpa);
	}

	fclose(fp);
	fclose(fo);
	
	return 0;
}
