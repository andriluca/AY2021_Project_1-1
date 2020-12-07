# Scaletta

## Accelerometro 

Questo deve scrivere nella FIFO.
è necessario scegliere tra FIFO mode e Stream mode (scegliere una modalità). Stream mode
Watermark o overrun? Watermark FTW.

## Psoc

Lettura dati da FIFO e salvataggio nella EEPROM.
Attenzione alla dimensione del pacchetto da inviare.
Il psoc dovrà "impacchettare" i dati in 4 byte, a cui dobbiamo aggiungere però anche i dati della temperatura (quanti byte?). Mando tutto alla eeprom

## EEPROM (esterna)

Controlla se stessa se è piena o no e manda un'interrupt al psoc.
Tra multiwrite e (multi)read dobbiamo inserire un delay di 5 ms.

## EEPROM (interna)

Registri di configurazione interna. Puntatore alla prima cella disponibile nella EEPROM esterna. Prendere i 6 byte dei registri e li shifto tramite mascheratura nelle rispettive posizioni dell'intero a 32 bit. successivamente questo sarà suddiviso nelle componenti da inviare.
