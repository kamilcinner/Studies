package com.github.kamilcinner;

public class Employer extends Human {
    private String companyName, preferences;
    private double employeeSalary;

    public Employer() {
        super();
        companyName = preferences = "unknown";
        employeeSalary = 0.0;
    }

    public Employer(String firstname, String lastname, int age, char gender, String companyName, String preferences, double employeeSalary) {
        super(firstname, lastname, age, gender);
        this.companyName = companyName;
        this.preferences = preferences;
        this.employeeSalary = employeeSalary;
    }

    public boolean hireAnEmployee(Employee e) {
        if (preferences.equals(e.profession)) {
            e.hire(companyName, employeeSalary);
            return true;
        } else return false;
    }

    @Override
    public String whereDoesTheIncomeComeFrom() {
        return null;
    }

    public String getPreferences() {
        return preferences;
    }
}
