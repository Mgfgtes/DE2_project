# Řešení semestrálního projektu z předmětu BPC-DE2

## Téma: Sledování parametrů a optimalizace solárního panelu

## Na projektu pracovali: 

* Matěj Matoušek (247142)
* Vojtěch Larva ()
* Petr Losert (247140)


## Hardwarové komponenty a schéma zapojení

* Vývojová deska Arduino UNO
* [Nabíjecí modul TP4056 se step-up měničem](#nmodul)
* [LCD displej 2x16 znaků HD44780](#display)
* [Servo motory MG90S](#servo)
* [Solární panel](#solarpanel)
* [Li-ion baterie](#battery)
* [Elektronické součástky: čtyři fotorezistory, čtyři 1 kOhm rezistory, jeden 10 kOhm potenciometrický trimr](#elcomponents)

  
### Popis zapojení komponent
Projekt je realizován na na vývojové desce Arduino UNO postavené na 8-bitovém mikrokontroleru ATmega328P z rodiny AVR. Schéma fyzického zapojení je vyobrazeno na obrázku níže. Zapojena jsou dvě serva MG90S, která jsou řízena PWM signálem z digitálních pinů PB1 a PB2. V zapojení je použit nabíjecí modul TP4056 se step-up měničem, který nabíjí Li-ion baterii připojenou na výstupech "BAT+" a "BAT-" modulu. Na vstup nabíjecího modulu je připojen solární panel, který dobíjí baterii. Výstupní napětí je poté přivedeno na Arduino UNO desku. Stav napětí baterie je snímán a zpracováván na pinu PC4. Piny PC0 až PC3 jsou přivedeny na odporový dělič, který se skládá z rezistorů o hodnotě 1 kOhm a fotorezistorů. Na těchto děličích je snímána o zpracovávána intenzita osvětlení fotorezistorů. K výstupnímu zobrazení je použit LCD displej HD44780, na kterém se zobrazují proměnné hodnoty udávající aktuální osvětlení a aktuální napětí baterie.        

  ![Schéma zapojení](Schema_zapojeni.png)


## Popis programové části

## Použité nástroje 





