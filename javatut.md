# Java tutorial

## Mediul de lucru
 Iti recomand [eclipse](https://eclipse.org/downloads/) pentru ca merge si pe windows si pe linux, are o comunitate
 activa si are si plugin-uri de care vei avea nevoie mai incolo.

## Basics

###Cea mai simpla clasa

O clasa, in sensul cel mai simplu, e un model folosit pentru a descrie mai multi indivizi identici.
O clasa are :
* atribute : variabile, date pe care _fiecare_ obiect le contine individual, si pe care le prelucreaza
* metode  : metode de a utiliza datele respective, intr-un sens sau altul.

>Clasa poate fi main (contine metoda public static void __main__ , care e fix cum e main-ul in C) sau nu.
>Un proiect nu poate sa aiba decat __o singura__ clasa main, fisierul in care se va afla acea clasa trebuie sa ii poarte >numele.
De exemplu:

```
public class HelloWorld {
    public static void main(String[] args) {
        System.out.println("Hello, World");
    }
}
```

Pune clasa asta intr-un fisier numit HelloWorld.java si compileaza. Acum schimba numele fisierului in ceva.java si
incearca sa compilezi din nou. Vezi ce se intampla?



###Constructori
Exceptand-o pe cea de mai sus, orice clasa(care se vrea macar vag utila) are unul sau mai multi constructori.
Constructorii sunt niste metode(functii) speciale, care nu au tip. Ele sunt responsabile pentru a creea un obiect, si pot avea parametri sau nu.

Un constructor initializeaza o variabila de tipul clasei(variabila se numeste obiect) in acelasi mod in care in C
ai fi scris.
```
int *c = (int*) malloc(sizeof(int));
```
Aloca memorie pentru el si eventual ii seteaza unele variabile.

###Obiecte
Un obiect este materializarea unei clase. Sintaxa pentru a crea un obiect este:
nume_clasa nume_obiect = new nume_clasa();
```
class strada {
    public String nume;
    public strada() {
        nume = new String();
    }
    public strada(String s) {
        nume = s;
    }
}

public class Main {
    public static void main(String[] args) {
        strada a = new strada(); //constructor fara parametri, sau implicit.
        strada b = new strada("Exemplu"); //constructor cu parametri.
    }
}
```

## Principii importante

### Encapsularea
>Suna fancy, dar ce e si de ce vrem asta? Encapsularea inseamna ca accesul la datele unei clase sa nu se faca direct,
>ci prin intermediul functionalitatii oferite de clasa.

Sa luam urmatoarea clasa
```
public class salaCinema {
    //numar locuri libere
    public int locuri;
    public salaCinema() {
        this.locuri = 50;
    }
}
```

si clasa, pe care o va face un alt developer, care iti va folosi clasa _salaCinema_ facuta de tine:

Un operator de cinema poate sa dea bilete, caz in care scade numarul locurilor cu 1.

```
public class operatorCinema {
    public salaCinema B42;
    public void taieBilet() {
        B42.locuri--;
    };
    //totul pare ok, dar se poate intampla si asta?
    B42.locuri = 51252; //desi e perfect legal din punctul de vedere al limbajului
    //e un comportament nedorit, care iti da peste cap logica bibliotecii tale.
}
```

Asa ca vom folosi encapsulare!

salaCinema devine:
```
public class salaCinema {
    //numar locuri libere
    private int locuri;
    public salaCinema() {
        this.locuri = 50;
    }
    public voidOcupaLoc() {
        if(this.locuri >= 0)
            this.locuri--;
        else
            System.err.println("Nu mai sunt locuri!");
    }
}
```

in _operatorCinema_ B46.locuri va genera eroare de compilare, iar numarul de locuri nu va mai putea fi modificat
arbitrar.

> In sens larg, vrei sa ai __accesors__ pentru date. Metode get si set pe care sa le poti restrictiona cum vrei tu si
> nu sa lasi la latitudinea celui care foloseste clasa ta.


> Ca best practice, vrei, de cate ori se poate, sa ascunzi implementarea, sa oferi o functionalitate fara sa expui ce se intampla, de fapt, in spate.

#Exercitiu
Implementeaza clasa numar complex, care sa aiba campurile parte reala si parte imaginara. Scrie constructorii pentru ele, metodele de get si set, metode de adunare si inmultire.  Apoi o clasa numita Main, care sa contina metoda public static void main si care sa creeze doua obiecte numarComplex pe care sa le adune si inmulteasca.




## Mostenirea
> Greaua mostenire lasata de ... oops, stai, am gresit cursul; revenind.
#Write once, use everywhere.

Nu vrei sa reinventezi roata  si nici sa rescrii ce-ai mai scris. Vrei doar sa-ti rezolvi problema. Asta implica
sa extinzi ce deja s-a facut, si ai doua metode sa faci asta: __extinzand clase__ si __implementand interfete__

###Clase

Extinzand o clasa preiei toate campurile ei si toate metodele.  Metodele le poti suprascrie.
De exemplu:

```
class person {
    public String name;
    public String lastname;
    public person() {
        this.name = new String();
        this.lastname = new String();
    }
    public person(String n, String l) {
        this.name = n;
        this.lastname = l;
    }
}
```

__super__ e echivalentul a : "fa ce facea si clasa pe care o extind"

__super__ poate fi folosit si pentru metode; Sintaxa e super.metoda()

```
class employee extends person {
    String job;
    public employee() {
        super();
        this.job = new String();
    }
    public employee(String name, String lastname, String job) {
        super(name, lastname);
        this.job = job;
    }
}
```

asa, in employee nu mai scrii o data ce-ai scris deja pentru person.

> A crea un obiect dintr-o clasa se mai numeste a o instantia, obiectul se mai numeste instanta.

O clasa abstracta se poate extinde(la fel ca aia de mai sus, dar __nu se poate instantia__). Ca sa poti instantia o clasa
abstracta trebuie sa ii implementezi toate metodele.

Daca cumva nu e clar,  [clasa abstracta docs pe oracle](http://docs.oracle.com/javase/tutorial/java/IandI/abstract.html)

Daca tot nu e clar, exemplu :

Avem o clasa abstracta instrument:

```
abstract class Instrument {
     protected String name;

     abstract public void play();
}
```


Dupa, ne definim o sub clasa StringedInstrument care extinde Instrument si ii adauga inca un camp. __Sunt ambele abstracte!__
```
abstract class StringedInstrument extends Instrument {
     protected int numberOfStrings;
}
```

Ii mai adaugam doua campuri, si ii implementam metoda abstracta(@Override desemneaza asta, __nu e obligatoriu__, insa)!!

```
public class ElectricGuitar extends StringedInstrument {

     public ElectricGuitar() {
          super();
          this.name = "Guitar";
          this.numberOfStrings = 6;
     }

     public ElectricGuitar(int numberOfStrings) {
          super();
          this.name = "Guitar";
          this.numberOfStrings = numberOfStrings;
     }

     @Override
     public void play() {
          System.out.println("An electric " + numberOfStrings + "-string " + name
				+ " is rocking!");
     }
}
```

### Interfete
In java, diferenta dintre o clasa si o interfata e semnificativa, stufoasa si spinoasa, nu le-am stiut niciodata pe toate.

Le-am adaugat aici, ca lectura.

* All methods in an interface are implicitly abstract. On the other hand, an abstract class may contain both abstract and non-abstract methods.
* A class may implement a number of Interfaces, but can extend only one abstract class.
* In order for a class to implement an interface, it must implement all its declared methods. However, a class may not implement all declared methods of an abstract class. Though, in this case, the sub-class must also be declared as abstract.
* Abstract classes can implement interfaces without even providing the implementation of interface methods.
Variables declared in a Java interface is by default final. An abstract class may contain non-final variables.
* Members of a Java interface are public by default. A member of an abstract class can either be private, protected or public.
* An interface is absolutely abstract and cannot be instantiated. An abstract class also cannot be instantiated, but can be invoked if it contains a main method.

* __Doua__ sunt importante si trebuie sa le retii. O clasa poate implementa(keyword-ul e __implements__ la interfete, si __extends__ la clase) __oricate__ interfete, dar extinde __o singura__ clasa.

* O interfata __Nu__ contine cod.  O clasa (abstracta) poate sa aiba unele metode implementate si altele nu. O clasa non-abstracta trebuie sa aiba toate metodele implementate. O interfata __nu are nicio metoda implementata__.


### Modificatori de acces si keywords.
Campurile unei clase pot avea modificatorii de acces urmatori: public, private, protected

[permisiuni modificatori de acces java] (http://2.bp.blogspot.com/-fHg6rAWuvUg/UMJQryYKGuI/AAAAAAAAAWk/jnVaxjcg_1k/s1600/table-of-Member-level-access-modifiers.png)
