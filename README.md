# Řešení semestrálního projektu z předmětu BPC-DE2

## Téma: Sledování parametrů a optimalizace solárního panelu

## Na projektu pracovali: 

* Matěj Matoušek (247142) - PWM
* Vojtěch Larva (246886) - ADC
* Petr Losert (247140) - LCD


## Hardwarové komponenty a schéma zapojení

* Vývojová deska Arduino UNO
* Nabíjecí modul TP4056 se step-up měničem
* LCD displej 2x16 znaků HD44780
* [Servo motory MG90S](#servo)
* Solární panel
* Li-ion baterie
* Elektronické součástky: čtyři fotorezistory, čtyři 1 kOhm rezistory, jeden 10 kOhm potenciometrický trimr


<a name="servo"></a>
### Servo motory MG90S
Výrobce udává délku jedné periody PWM 20 ms, kde servo pracuje v rozsahu 0° až 180°. Úhlu natočení 0° odpovídá pulz o šířce 1 ms, natočení 180° poté šířka pulzu 2 ms. Časové intervaly jsme museli ovšem pro naši aplikaci doladit. Níže jsou časové průběhy PWM udávané výrobcem servo motorů. 
![Natočení serva](Natoceni_serva.png)
Obrázek č. 1: Časové průběhy MG90S udávány výrobcem 

  
### Popis zapojení komponent
Projekt je realizován na na vývojové desce Arduino UNO postavené na 8-bitovém mikrokontroleru ATmega328P z rodiny AVR. Schéma fyzického zapojení je vyobrazeno na obrázku níže. Zapojena jsou dvě serva MG90S, která jsou řízena PWM signálem z digitálních pinů PB1 a PB2. V zapojení je použit nabíjecí modul TP4056 se step-up měničem, který nabíjí Li-ion baterii připojenou na výstupech "BAT+" a "BAT-" modulu. Na vstup nabíjecího modulu je připojen solární panel, který dobíjí baterii. Výstupní napětí je poté přivedeno na Arduino UNO desku. Stav napětí baterie je snímán a zpracováván na pinu PC4. Piny PC0 až PC3 jsou přivedeny na odporový dělič, který se skládá z rezistorů o hodnotě 1 kOhm a fotorezistorů. Na těchto děličích je snímána o zpracovávána intenzita osvětlení fotorezistorů. K výstupnímu zobrazení je použit LCD displej HD44780, na kterém se zobrazují proměnné hodnoty udávající aktuální osvětlení a aktuální napětí baterie.        

  ![Schéma zapojení](Schema_zapojeni.png)
Obrázek č. 2: Schéma zapojení 

## Popis programové části

## Zdrojové a hlavičkové soubory

adc.h: https://github.com/Mgfgtes/DE2_project/blob/main/lib/adc/adc.h
adc.c: https://github.com/Mgfgtes/DE2_project/blob/main/lib/adc/adc.c

pwm.h: https://github.com/Mgfgtes/DE2_project/blob/main/lib/pwm/pwm.h
pwm.c: https://github.com/Mgfgtes/DE2_project/blob/main/lib/pwm/pwm.c

main.c: https://github.com/Mgfgtes/DE2_project/blob/main/src/main.c

### Popis běhu programu 
Ve funkci _int main(void){}_ nejprve nastavujeme piny pro PWM PB1 a PB2 jako výstupní. Poté probíhá inicializace UARTu, LCD displeje a nastavení časovače TIM1 pro PWM (´uart_init(...);´, _lcd_init(...);_,_TIM1_pwm_init();_). Následně nastavíme povolovací vstup LCD displeje E (Enable) na nulu, čímž displej povolíme. Časovač TIM0 je využit pro mechanizmus přerušení, kdy jeho přetečení je nastaveno na 16 ms. Jeho nastavení probíhá v řádcích _TIM0_ovf_enable();_ - povolení časovače, _TIM0_ovf_16ms();_ - přetečení po 16 ms a _sei();_ - globálně povolit přerušení. Dále je zapnut ADC převodník pro výčet vstupních analogových hodnot (_adc_init();_).  

V nekonečné smyčce (_while(1){}_) běží kód, kde jsou při podmínce setované vlajky  _flag_interrupt_ vykonány tři definované funkce: _LCD_print_info();_ - výpis údajů na LCD displej, _battery_voltage_uart();_ - posílání údaje o napětí akumulátoru do sériového monitoru, slouží pro ladění programu a _position_adjust();_ - slouží pro ovládání polohy servo motorů. Na konci podmínkového bloku je vlajka resetována.

Vektor přerušení je volán každých 16 ms při přetečení čítače a obsahuje proměnnou _n_ovs_ a podmínku, která zajišťuje nastavení vlajky za každých 30 x 16 ms, tedy přibližně půl minuty. Po jejím nastavení je splněna podmínka v nekonečné smyčce a jsou opět provedeny funkce pro obsaluhu displeje a ovládání servo motorů. Půlminutový interval slouží pro demo aplikaci, aby bylo vidět otáčení servo motorů, avšak v praxi by dostačoval interval řádově delší z důvodu pomalého pohybu slunce.   

![Vývojový diagram funkce main(void)](Vyvojovy_diagram.png)
Obrázek č. 3: Schéma zapojení

## Fotodokumentace a uživatelské ovládání
 ![Obrázek zapojení](Foto_zapojeni.jpg)
Obrázek č. 4: Fotografie zapojení

 ![Obrázek zapojení](Foto_zapojeni2.jpg)
Obrázek č. 5: Fotografie zapojení


Video ukázka: https://vutbr-my.sharepoint.com/:v:/g/personal/247140_vutbr_cz/EYqT7I-tG9RGnOmlBnk_zzUBDUYlkKBPCUUiMvQzCavR8Q?nav=eyJyZWZlcnJhbEluZm8iOnsicmVmZXJyYWxBcHAiOiJPbmVEcml2ZUZvckJ1c2luZXNzIiwicmVmZXJyYWxBcHBQbGF0Zm9ybSI6IldlYiIsInJlZmVycmFsTW9kZSI6InZpZXciLCJyZWZlcnJhbFZpZXciOiJNeUZpbGVzTGlua0NvcHkifX0&e=KFdceu

## Použité nástroje 
Inkscape - tvorba schémat  
SmartDraw - tvorba vývojových diagramů 




