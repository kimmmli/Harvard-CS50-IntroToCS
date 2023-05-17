import csv
from cs50 import SQL

db=SQL("sqlite:///roster.db")

def create_student(name, students):
    students.append(students)

def create_house(head,house,houses):
    count=0
    for i in houses:
        if i["house"]==house:
            count+=1
    if count==0:
        houses.append({"house":house,"head":head})

def create_relation(house, name,relation):
    relation.append({"house":house,"student_name":name})



students=[]
houses=[]
relation=[]
with open('students.csv',"r") as csvfile:
    reader=csv.DictReader(csvfile)
    for row in reader:
        name=row["student_name"]
        house=row["house"]
        head=row["head"]
        create_student(name,students)
        create_house(head,house,houses)
        create_relation(house,name,relation)

for student in students:
    db.execute("INSERT INTO new_students(student_name) VALUES (student); ")

