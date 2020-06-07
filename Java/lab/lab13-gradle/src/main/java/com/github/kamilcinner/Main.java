package com.github.kamilcinner;

//import potrzebny do mechanizmu refleksji w Javie. W tym przypadku poszukania
//konstruktora klasy i utworzenia instancji klasy na jego podstawie
import java.lang.reflect.InvocationTargetException;
//Interfejs reprezentujący połączenie z bazą danych
import java.sql.Connection;
//Klasa zarządcy sterowników do baz danych , która rejestruje w środowisku Javy sterownik
import java.sql.DriverManager;
//Wyrażenie reprezentujące zapytanie do bazy danych (prepared - parametryzowane)
import java.sql.PreparedStatement;
//Zbiór rezultatów, który otrzymujemy po wykonaniu zapytania do bazy danych (ma formę)
//wirtualnej tabeli z wierszami i kolumnami
import java.sql.ResultSet;
//Wyjątek, który może zostać zgłoszony podczas pracy z bazą danych
import java.sql.SQLException;
//Wyrażenie reprezentujące zapytanie do bazy danych
import java.sql.Statement;
import java.util.ArrayList;
import java.util.Properties;
import java.util.logging.Level;
import java.util.logging.Logger;

public class Main {

    //Nazwa klasy sterownika do bazy danych
    public String driver = "org.apache.derby.jdbc.EmbeddedDriver";
    //Framework - tryb w jakim chcemy mieć dostęp do bazy danych (wbudowany - silnik bazy danych
    //zintegrowany z naszą aplikacją)
    private String framework = "embedded";
    //Nazwa protokołu komunikacyjnego - różna dla różnych silników baz danych, np. MySQL, czy PostgreSQL
    private String protocol = "jdbc:derby:";

    public static void main(String[] args) {
        Main main = new Main();
        main.workWithDB();
    }

    void workWithDB(){

        //Deklaracja niezbędnych zmiennych
        //Połączenie do bazy danych (analogia: tory kolejowe do stacji docelowej)
        Connection conn = null;
        //Pomocnicza kolekcja na zapytania do bazy danych
        ArrayList<Statement> statements = new ArrayList<Statement>(); // lista Statements i PreparedStatements

        //Zmienne reprezentujące wyrażenia - zapytania do bazy danych parametryzowane
        PreparedStatement psInsert;
        PreparedStatement psUpdate;
        //zwykłe
        Statement s;
        //Zbiór rezultatów zapytania
        ResultSet rs = null;
        try
        {
            //Załadowanie i rejestracja w menadżerze sterowników sterownika (klasy tłumaczącej zapytania na
            //wywołania API silnika bazy danych) do DBMS Derby
            Class.forName(driver).getDeclaredConstructor().newInstance();

            Properties props = new Properties(); // właściwości połączenia
            // podawanie użytkownika i hasła jest opcjonalne dla frameworków embedded i derbyclient
            props.put("user", "user1");
            props.put("password", "user1");
            //W bazie danych mogą być schematy - podzbiory bazy danych posiadające własne nazwy i np. różne
            //prawa dostępu
            /* Domyślnie używany jest schemat APP jeśli nie podamy żadnej nazwy użytkownika
             * W innym wypadku zakładany jest schemat odpowiadający nazwie użytkownika (w tym przypadku
             * "user1" lub USER1.)
             *
             * Uwaga. Uwierzytelnianie użytkownika jest domyślnie wyłączone, co oznacza, że do bazy może
             * podłączyć się dowolny użytkownik z dowolnym hasłem.
             */
            String dbName = "derbyDB"; // nazwa bazy danych - dowolna
            /*
             * Połączenie zawiera element create=true in the connection URL to
             * spowoduje, że baza danych zostanie utworzona przy pierwszym połączeniu.
             * Żeby usunąc bazę danych należy usunąć katalog derbyDB (nazwa taka jak bazy) i jego zawartość.
             *
             * Katalog odpowiadający nazwie bazy danych derbyDB będzie utworzony jako podkatalog katalogu
             * na który wskazuje zmienna systemowa derby.system.home lub katalogu bieżącego
             * (user.dir) jeśli derby.system.home jest nie ustawiona..
             */
            conn = DriverManager.getConnection(protocol + dbName
                    + ";create=true", props);
            System.out.println("Connected to and created database " + dbName);
            // W bazach danych stosowane są transakcje. Zbiór akcji (dodawania, modyfikacji, usuwania danych),
            //które wykonują się wszystkie lub żadna.
            // Prawidłowo wykonana transakcja kończy się utrwaleniem zmian w bazie danych (commit),
            // a jakikolwiek błąd podczas wykonywania zbioru akcji wycofuje transakcję (rollback). Baza wraca do
            // stanu z przed transakcji. Chcemy zarządzać transakcjami (zapisem) ręcznie - ustawiamy autocommit na
            // „false”. Domyślnie autocommit przez sterownik JDBC jest ustawiony na „true”.
            conn.setAutoCommit(false);
            //Tworzymy obiekt wyrażenia, który będzie stosowany do różnych zapytań w języku SQL do bazy danych
            s = conn.createStatement();
            //Dodajemy wyrażenie do pomocniczej kolekcji
            statements.add(s);
            // Relacyjne bazy danych to zbiory danych zgromadzonych w tabelach (kolumny to różne właściwości, np.
            // dla tabeli studentów mogą to być: id - numeryczny identyfikator - dane zwykle go posiadają - unikalny
            // klucz główny
            // dla danych umożliwiający zapewnienie unikalności oraz odnajdywanie danych na podstawie relacji
            // pomiędzy tabelami) powiązanych relacjami, nazwisko - typu tekstowego (varchar), numer indeksu, data
            // urodzenia, status, itd. Wiersze w tabeli to różni studenci zapisani do bazy danych.
            // (zależnościami między danymi, np. relacja studenta i jego grupy dziekańskiej - student należy do grupy,
            // a grupa składa się ze studentów. Od strony studentów jest to relacja wiele do jednego, a od strony
            // grupy jeden do wielu). Fizycznie w tabeli studenta jest kolumna zawierająca klucz obcy czyli id grupy,
            // do której należy.
            // Tworzymy tabelę z dwoma kolumnami… Używając polecenia języka DDL (Data Definition Language)
            s.execute("create table location(num int, addr varchar(40))");
            System.out.println("Created table location");
            // i dodajemy kilka wierszy danych...
            /* Zaleca się użycia PreparedStatement kiedy chcemy wykonywać zapytania SQL cyklicznie.
             * PreparedStatement pozwala także parametryzacja zapytań. W ten sposób można zwiększyć wydajność
             * ponieważ silnik Derby engine nie musi rekompilować wyrażeń SQL z każdym razem gdy są
             * wykonywane. PreparedStatement poprawia też bezpieczeństwo (dzięki weryfikacji typów Javy).
             */
            // parametr 1 to num (typu int), parametr 2 to addr (typu znakowego varchar)
            psInsert = conn.prepareStatement(
                    "insert into location values (?, ?)"); //znaki zapytania to parametry, pod które podstawione zostaną
                    //wartosci
                    //Zapis do kolekcji pomocniczej zapytań
                    statements.add(psInsert);
            //Ustawienie wartości pierwszego parametru pod „?”.
            psInsert.setInt(1, 1956);
            //Ustawienie wartości drugiego parametru
            psInsert.setString(2, "Webster St.");
                    // Wykonanie zapytania do bazy danych. JDBC posługuje się metodą executeUpdate() dla insert, update i
                    // delete danych (wszelkich modyfikacji) oraz executeQuery() dla zapytań w celu odczytu danych z bazy.
                    psInsert.executeUpdate();
            System.out.println("Inserted 1956 Webster");
            psInsert.setInt(1, 1910);
            psInsert.setString(2, "Union St.");
            psInsert.executeUpdate();
            System.out.println("Inserted 1910 Union");
            // Zmodyfikujmy dane… numer i adres dla wierszy wybranych na podstawie warunku zdefiniowanego
            // po „where”.
            // parametr 1 i 3 to num (int), a parameter 2 to addr (varchar)
            psUpdate = conn.prepareStatement(
                    "update location set num=?, addr=? where num=?");
            statements.add(psUpdate);
            psUpdate.setInt(1, 180);
            psUpdate.setString(2, "Grand Ave.");
            psUpdate.setInt(3, 1956);
            psUpdate.executeUpdate();
            System.out.println("Updated 1956 Webster to 180 Grand");
            psUpdate.setInt(1, 300);
            psUpdate.setString(2, "Lakeshore Ave.");
            psUpdate.setInt(3, 180);
            psUpdate.executeUpdate();
            System.out.println("Updated 180 Grand to 300 Lakeshore");
 /*
 Pobranie danych z bazy i weryfikacja rezultatu powyższych działań. Wskazujemy jakie kolumny danych
 nas interesują z jakiej tabeli i jak mają być posortowane (sortowanie jest opcjonalne)
 */
            rs = s.executeQuery(
                    "SELECT num, addr FROM location ORDER BY num");

            /* oczekujemy pierwszej kolumny zwróconej jako integer (num),
             * i drugiej jako String (addr). Wiersze są sortowane po numerze (num).
             *
             * Normalnie, najlepiej jest użyć następującego wzorca do odczytu ze zbioru wyników ResultSet
             * while(rs.next()) {
             * // robimy coś z wierszem danych odczytanym z ResultSet
             * }
             * ale w naszym przypadku są tylko dwa wiersze danych
             */
            int number; // numer domu pobrany z bazy danych
            boolean failure = false;
            //Jak metoda next() przesuwająca kursor w zbiorze rezultatów zwróci false oznacza to, że nie ma danych,
            // albo doszliśmy do końca zbioru rezultatów
            if (!rs.next()) {
                failure = true;
                //pomocnicza metoda do ładnego formatowania komunikatów o błędach
                reportFailure("No rows in ResultSet");
            }
            // Pobieramy wartość ze wskazanej kolumny (za pomocą numeru kolumny lub jej nazwy) z aktywnego
            // wiersza zbioru rezultatów
            if ((number = rs.getInt(1)) != 300){
                failure = true;
                reportFailure(
                        "Wrong row returned, expected num=300, got " + number);
            }
            if (!rs.next())
            {
                failure = true;
                reportFailure("Too few rows");
            }
            if ((number = rs.getInt(1)) != 1910)
            {
                failure = true;
                reportFailure(
                        "Wrong row returned, expected num=1910, got " + number);
            }
            if (rs.next())
            {
                failure = true;
                reportFailure("Too many rows");
            }
            if (!failure) {
                System.out.println("Verified the rows");
            }
            // usunięcie tabeli z bazy danych - Uwaga - nieodwołalne! Tracimy tabelę i wstawione do niej dane.
            s.execute("drop table location");
            System.out.println("Dropped table location");
 /*
 Zatwierdzamy transakcję. Dopiero teraz wszystkie dane zostaną utrwalone w bazie danych bo
 autocommit=false. Wszelkie inserty, update-y i dropy zajdą dopiero teraz.
 */
            conn.commit();
            System.out.println("Committed the transaction");
            /*
             * W trybie embedded, aplikacja powinna wyłączyć bazę danych.
             * Jeśli aplikacji nie uda się zamknąć bazy danych,
             * Derby nie wykona checkpointa kiedy maszyna wirtualna Javy się zamknie.
             * To oznacza, że następne uruchomienie bazy (połączenie się z bazą danych) będzie dłuższe
             * ponieważ Derby będzie przeprowadzać operację przywracania bazy danych.
             *
             * Możliwe jest także wyłączenie silnika Derby, który automatycznie zamknie wszystkie wystartowane bazy
             * danych.
             *
             * Zalecane jest jawne wyłączenie bazy danych lub silnika Derby za pomocą URL połączenia.
             * Ten sposób zamknięcia zawsze wyzwala SQLException.
             *
             */
            if (framework.equals("embedded"))
            {
                try
                {
                    // atrybut shutdown=true wyłącza Derby
                    DriverManager.getConnection("jdbc:derby:;shutdown=true");
                    // W celu zamknięcia określonej bazy, bez wyłączania działającego silnika Derby
                    // (np. żeby połączyć się z inną bazą), podajemy bazę danych w URL:
                    //DriverManager.getConnection("jdbc:derby:" + dbName + ";shutdown=true");
                }
                catch (SQLException se)
                {
                    if (( (se.getErrorCode() == 50000)
                            && ("XJ015".equals(se.getSQLState()) ))) {
                        // dostajemy oczekiwany wyjątek
                        System.out.println("Derby shut down normally");
                        // Uwaga. Oczekiwany wyjątek przy zamykaniu jednej bazy danych to:
                        // SQL state = „08006” i kod błędu 45000.
                    } else {
                        // jeśli kod błędu lub SQL state jest inny, mamy nieoczekiwany wyjątek (błąd zamykania)
                        System.err.println("Derby did not shut down normally");
                        printSQLException(se);
                    }
                }
            }
        }
        catch (SQLException sqle)
        {
            // Metoda pomocnicza do wyświetlania błędów
            printSQLException(sqle);
        } catch (ClassNotFoundException ex) {
            Logger.getLogger(Main.class.getName()).log(Level.SEVERE, null, ex);
        } catch (InstantiationException ex) {
            Logger.getLogger(Main.class.getName()).log(Level.SEVERE, null, ex);
        } catch (IllegalAccessException ex) {
            Logger.getLogger(Main.class.getName()).log(Level.SEVERE, null, ex);
        } catch (NoSuchMethodException ex) {
            Logger.getLogger(Main.class.getName()).log(Level.SEVERE, null, ex);
        } catch (SecurityException ex) {
            Logger.getLogger(Main.class.getName()).log(Level.SEVERE, null, ex);
        } catch (IllegalArgumentException ex) {
            Logger.getLogger(Main.class.getName()).log(Level.SEVERE, null, ex);
        } catch (InvocationTargetException ex) {
            Logger.getLogger(Main.class.getName()).log(Level.SEVERE, null, ex);
        } finally {
            // zwolnienie wszystkich otwartych zasobów w celu uniknięcia niechcianego zajęcia pamięci
            // ResultSet
            try {
                if (rs != null) {
                    rs.close();
                    rs = null;
                }
            } catch (SQLException sqle) {
                printSQLException(sqle);
            }
            // Statements i PreparedStatements
            int i = 0;
            while (!statements.isEmpty()) {
                // PreparedStatement dziedziczy po Statement
                Statement st = (Statement)statements.remove(i);
                try {
                    if (st != null) {
                        st.close();
                        st = null;
                    }
                } catch (SQLException sqle) {
                    printSQLException(sqle);
                }
            }
            //Connection
            try {
                if (conn != null) {
                    conn.close();
                    conn = null;
                }
            } catch (SQLException sqle) {
                printSQLException(sqle);
            }
        }
    }

    private void reportFailure(String message) {
        System.err.println("\nData verification failed:");
        System.err.println('\t' + message);
    }

    /**
     * Drukuje szczegóły łańcucha SQLException <code>System.err</code>.
     * Szczegółami zawartymi są SQL State, Error code i Exception message.
     *
     * @param e wyjątek SQLException z którego drukować szczegóły.
     */
    public static void printSQLException(SQLException e)
    {
        // Rozpakowuje łańcuch wyjątków, w celu określenia rzeczywistego powodu wystąpienia wyjątku.
        while (e != null){
            System.err.println("\n----- SQLException -----");
            System.err.println(" SQL State: " + e.getSQLState());
            System.err.println(" Error Code: " + e.getErrorCode());
            System.err.println(" Message: " + e.getMessage());
            // w celu sprawdzenia stosu, można sprawdzić derby.log albo odkomentować to:
            //e.printStackTrace(System.err);
            e = e.getNextException();
        }
    }
}
