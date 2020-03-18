package com.github.kamilcinner;

public class Employee extends Human {
    private String workplace;
    private double income;
    
    public Employee() {
        super();
        workplace = "unknown";
        income = 0.0;
    }

    public Employee(String firstname, String lastname, int age, char gender, String profession, String workplace, double income) {
        super(firstname, lastname, age, gender);
        super.hire();
        this.profession = profession;
        this.workplace = workplace;
        this.income = income;
    }

    public void hire(String workplace, double income) {
        super.hire();
        this.workplace = workplace;
        this.income = income;
    }
    
    private static <T> void print(T arg) {
        System.out.println(arg);
    }
    
    @Override
    public String whereDoesTheIncomeComeFrom() {
        if (income == 0.0) {
            return "There is no income";
        } else {
            return "Workplace: "+workplace+" Income: "+income;
        }
    }
    
    public static void printEmployeeData(Employee e) {
        print("Name: "+e.whatsYourName());
        print("Age: "+e.whatsYourAge());
        print("Woman: "+e.areYouWoman());
        print("Profession: "+e.profession);
        print("Hired: "+e.isHired());
        print("Workplace: "+e.workplace);
        print("Income: "+e.income);
    }
}
