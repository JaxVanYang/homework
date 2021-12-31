import mysql.connector
from random import *


first_names = ("张", "李", "王", "杨", "谢", "孔", "云", "汪")
second_names = ("一", "二", "三", "四", "五", "六", "七", "八", "九", "十", "花", "石", "霞", "球")
grades = ("大一", "大二", "大三", "大四")
provinces = ("京", "沪", "粤", "湘")
majors = ("计算机", "软件工程", "计算机科学与技术", "软件工程")
ages = (18, 19, 20, 21)

class StudentInfo:
    def __init__(self, no="", name="", grade="", phone="", province="", major="", age=""):
        self.no = no
        self.name = name
        self.grade = grade
        self.phone = phone
        self.province = province
        self.major = major
        self.age = age

    def isValid(self):
        return self.no != "" and self.name != "" and self.grade != "" and self.phone != "" and self.province != "" and self.major != "" and self.age != ""

    def values(self):
        return (self.no, self.name, self.grade, self.phone, self.province, self.major, self.age)

def getInput():
    return StudentInfo(
        name = choice(first_names) + choice(second_names),
        grade = choice(grades),
        phone = randint(13000000000, 18999999999),
        province = choice(provinces),
        major = choice(majors),
        age = choice(ages)
    )

# Connect to database
mydb = None
mycursor = None
try:
    mydb = mysql.connector.connect(
        host="localhost",
        user="root",
        password="123456",
        database="school"
    )
    mycursor = mydb.cursor()
except Exception as e:
    print(e)
    exit(1)


def Register(no):
    input = getInput()
    input.no = no
    if not input.isValid():
        return

    dbNo = ""
    Select = "select no from student where no='%s'" % (input.no)
    mycursor.execute(Select)
    result = mycursor.fetchall()

    for i in result:
        dbNo = i[0]

    if(input.no == dbNo):
        print("学号已存在")
    else:
        Insert = "Insert into student(no,name,grade,phone,province,major,age) values(%s,%s,%s,%s,%s,%s,%s)"
        mycursor.execute(Insert, input.values())
        mydb.commit()

for no in range(1, 100):
    Register(str(no))
