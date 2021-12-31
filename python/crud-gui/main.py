import mysql.connector
from tkinter.ttk import *
from tkinter import *
from tkinter import messagebox


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


# Create UI
root = Tk()
root.title("学生信息管理系统")
root.geometry("560x400")
root.resizable(False, False)

label1 = Label(root, text="学号", width=20, height=2,
               bg="pink").grid(row=0, column=0)
label2 = Label(root, text="姓名", width=20,
               height=2, bg="pink").grid(row=1, column=0)
label3 = Label(root, text="年级", width=20,
               height=2, bg="pink").grid(row=2, column=0)
label4 = Label(root, text="电话号码", width=20,
               height=2, bg="pink").grid(row=3, column=0)
label5 = Label(root, text="籍贯", width=20, height=2,
               bg="pink").grid(row=4, column=0)
label6 = Label(root, text="专业", width=20, height=2,
               bg="pink").grid(row=5, column=0)
label7 = Label(root, text="年龄", width=20, height=2,
               bg="pink").grid(row=6, column=0)

e1 = Entry(root, width=30, borderwidth=8)
e1.grid(row=0, column=1)
e2 = Entry(root, width=30, borderwidth=8)
e2.grid(row=1, column=1)
e3 = Entry(root, width=30, borderwidth=8)
e3.grid(row=2, column=1)
e4 = Entry(root, width=30, borderwidth=8)
e4.grid(row=3, column=1)
e5 = Entry(root, width=30, borderwidth=8)
e5.grid(row=4, column=1)
e6 = Entry(root, width=30, borderwidth=8)
e6.grid(row=5, column=1)
e7 = Entry(root, width=30, borderwidth=8)
e7.grid(row=6, column=1)

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
    messagebox.askokcancel("Error", "数据库连接异常，请检查数据库连接")
    exit(1)


def getInput():
    return StudentInfo(e1.get(), e2.get(), e3.get(), e4.get(), e5.get(), e6.get(), e7.get())


def Clear(clearNo=True):
    if clearNo:
        e1.delete(0, END)
    e2.delete(0, END)
    e3.delete(0, END)
    e4.delete(0, END)
    e5.delete(0, END)
    e6.delete(0, END)
    e7.delete(0, END)


def Register():
    input = getInput()
    if not input.isValid():
        messagebox.askokcancel("Information", "请填写所有表项")
        return

    dbNo = ""
    Select = "select no from student where no='%s'" % (input.no)
    mycursor.execute(Select)
    result = mycursor.fetchall()

    for i in result:
        dbNo = i[0]

    if(input.no == dbNo):
        messagebox.askokcancel("Information", "学号已存在")
    else:
        Insert = "Insert into student(no,name,grade,phone,province,major,age) values(%s,%s,%s,%s,%s,%s,%s)"
        mycursor.execute(Insert, input.values())
        mydb.commit()

        messagebox.askokcancel("Information", "信息已登记")
        Clear()


def ShowRecord():
    input = getInput()
    if input.no.strip() == "":
        messagebox.askokcancel("Information", "请填写学号")
        return

    dbNo = ""
    Select = "select no from student where no='%s'" % (input.no)
    mycursor.execute(Select)
    result1 = mycursor.fetchall()
    for i in result1:
        dbNo = i[0]
    Select1 = "select name,grade,phone,province,major,age from student where no='%s'" % (
        input.no)
    mycursor.execute(Select1)
    result2 = mycursor.fetchall()
    name = ""
    grade = ""
    phone = ""
    province = ""
    major = ""
    age = ""
    if(input.no == dbNo):
        for i in result2:
            name = i[0]
            grade = i[1]
            phone = i[2]
            province = i[3]
            major = i[4]
            age = i[5]
        Clear(False)
        e2.insert(0, name)
        e3.insert(0, grade)
        e4.insert(0, phone)
        e5.insert(0, province)
        e6.insert(0, major)
        e7.insert(0, age)
    else:
        messagebox.askokcancel("Information", "该学号不存在")


def Delete():
    no = e1.get()
    Delete = "delete from student where no='%s'" % (no)
    mycursor.execute(Delete)
    mydb.commit()
    messagebox.showinfo("Information", "记录已删除")
    Clear()


def Update():
    input = getInput()
    if not input.isValid():
        messagebox.askokcancel("Information", "请填写所有表项")
        return

    dbNo = ""
    Select = "select no from student where no='%s'" % (input.no)
    mycursor.execute(Select)
    result = mycursor.fetchall()

    for i in result:
        dbNo = i[0]

    if(input.no == dbNo):
        values = input.values()[1:] + tuple(input.no)
        Update = "Update student set name='%s', grade='%s', phone='%s', province='%s', major='%s', age='%s' where no='%s'" % values
        mycursor.execute(Update)
        mydb.commit()
        messagebox.showinfo("Information", "记录已更新")
    else:
        messagebox.askokcancel("Information", "学号不存在")


def Showall():
    class A(Frame):
        def __init__(self, parent):
            Frame.__init__(self, parent)
            self.CreateUI()
            self.LoadTable()
            self.grid(sticky=(N, S, W, E))
            parent.grid_rowconfigure(0, weight=1)
            parent.grid_columnconfigure(0, weight=1)

        def CreateUI(self):
            tv = Treeview(self)
            tv['columns'] = ('no', 'name', 'grade', 'phone',
                             'province', 'major', 'age')
            tv.heading('#0', text='学号', anchor='center')
            tv.column('#0', anchor='center')
            tv.heading('#1', text='姓名', anchor='center')
            tv.column('#1', anchor='center')
            tv.heading('#2', text='年级', anchor='center')
            tv.column('#2', anchor='center')
            tv.heading('#3', text='电话号码', anchor='center')
            tv.column('#3', anchor='center')
            tv.heading('#4', text='籍贯', anchor='center')
            tv.column('#4', anchor='center')
            tv.heading('#5', text='专业', anchor='center')
            tv.column('#5', anchor='center')
            tv.heading('#6', text='年龄', anchor='center')
            tv.column('#6', anchor='center')
            tv.grid(sticky=(N, S, W, E))
            self.treeview = tv
            self.grid_rowconfigure(0, weight=1)
            self.grid_columnconfigure(0, weight=1)

        def LoadTable(self):
            Select = "Select * from student"
            mycursor.execute(Select)
            result = mycursor.fetchall()
            for i in result:
                info = StudentInfo(i[0], i[1], i[2], i[3], i[4], i[5], i[6])
                self.treeview.insert(
                    "", 'end', text=info.no, values=(info.values()[1:]))

    root = Tk()
    root.title("所有记录")
    A(root)


button1 = Button(root, text="登记", width=10, height=2,
                 command=Register).grid(row=7, column=0)
button4 = Button(root, text="查询", width=10, height=2,
                 command=ShowRecord).grid(row=7, column=1)
button3 = Button(root, text="更新", width=10, height=2,
                 command=Update).grid(row=7, column=2)
button2 = Button(root, text="删除", width=10, height=2,
                 command=Delete).grid(row=8, column=0)
button5 = Button(root, text="查看所有记录", width=10, height=2,
                 command=Showall).grid(row=8, column=1)
button6 = Button(root, text="清除文本框", width=10, height=2,
                 command=Clear).grid(row=8, column=2)

root.mainloop()
