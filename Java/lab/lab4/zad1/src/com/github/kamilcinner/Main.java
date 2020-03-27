package com.github.kamilcinner;

import java.util.ArrayList;
import java.util.Collection;
import java.util.Iterator;

public class Main {
    private static <T> void print(T arg) {
        System.out.println(arg);
    }

    public static void main(String[] args) {
        // ad.1
	    Human h = new Human() {
            @Override
            public String whereDoesTheIncomeComeFrom() {
                return null;
            }
        };
	    print("Human h -> hired: "+h.isHired()+"\n");
        // ad.2
	    Employee e1 = new Employee();
	    Employee e2 = new Employee("Kamil", "Cinner", 21, 'm', "programmer", "Google", 15000);
	    Employee e3 = new Employee("Kornelia", "Brown", 21, 'f', "human resources", "Sii", 5499);
//	    Employee.printEmployeeData(e1); print("");
//	    Employee.printEmployeeData(e2); print("");
//	    Employee.printEmployeeData(e3); print("");
        // ad.3
        ArrayList<Employee> c = new ArrayList<>();
        c.add(e1);
        c.add(e2);
	    c.add(e3);
	    c.add(new Employee("Adam", "Kątek", 23, 'm', "programmer", "Microsoft", 23000));
	    c.add(new Employee("Lilith", "Bonner", 20, 'f', "pharmacist", "Adamed", 7000));
//	    for (Object e : ((Collection<Employee>) c).toArray()) {
//	        print(e.toString());
//        }
        for (Employee e : c) {
            Employee.printEmployeeData(e);
            print("");
        }
//        print("");
        // ad.4
	    Employer assecoEmployer = new Employer("Jerzy", "Grębosz", 32, 'm', "Asseco", "programmer", 27000);
	    // ad.5
        for (Employee e : c) {
            if (assecoEmployer.hireAnEmployee(e)) {
                print("Successfully hired "+e.whatsYourName()+" ("+e.profession+")"+" as "+assecoEmployer.getPreferences());
                Employee.printEmployeeData(e); print("");
            } else print("Cannot hire "+e.whatsYourName()+" ("+e.profession+")"+" as "+assecoEmployer.getPreferences()+"\n");
        }
    }
}
