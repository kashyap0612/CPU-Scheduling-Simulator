class Employee:

    def set_details(self, name, age):
        self.name = name
        self.age = age

        self.department = "Engineering"

    def set_salary(self, salary):
        self.salary = salary

    def get_salary(self):
        return self.salary

    def display(self):
        print("Name:", self.name)
        print("Age:", self.age)
        print("Department:", self.department)
        print("Salary:", self.salary)


emp1 = Employee()

emp1.set_details("a", 25)
emp1.set_salary(2500)
emp1.display()