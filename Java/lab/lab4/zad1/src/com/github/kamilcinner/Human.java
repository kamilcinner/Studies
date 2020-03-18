package com.github.kamilcinner;

public abstract class Human {
    private String firstname, lastname;
    protected String profession;
    private int age;
    private char gender;
    private boolean hired = false;

    public Human() {
        firstname = lastname = profession = "unknown";
        age = 0;
        gender = 'u'; // u - unknown
    }

    public Human(String firstname, String lastname) {
        this();
        this.firstname = firstname;
        this.lastname = lastname;
    }

    public Human(String firstname, String lastname, int age, char gender) {
        this(firstname, lastname);
        this.age = age;
        this.gender = gender;
    }

    public String whatsYourName() {
        return firstname+" "+lastname;
    }

    public String areYouWoman() {
        switch (gender) {
            case 'm': return "no"; // m - male
            case 'f': return "yes"; // f - female
            default: return "unknown";
        }
    }

    public int whatsYourAge() {
        return age;
    }

    protected void hire() {
        hired = true;
    }

    public boolean isHired() {
        return hired;
    }

    public abstract String whereDoesTheIncomeComeFrom();
}
