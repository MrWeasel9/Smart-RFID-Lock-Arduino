# Proiect Sistem de Control Acces RFID

Proiectul constă într-un sistem de control acces prin RFID, afișarea informațiilor pe un display LCD, generarea unui sunet și controlul unui motor servo. Implementarea include următoarele funcționalități:

## Funcționalități

### Detecția și citirea cardurilor RFID
Utilizând biblioteca `MFRC522`, sistemul detectează și citește cardurile RFID pentru a verifica dacă accesul este autorizat sau nu.

### Afișare pe LCD
Informațiile despre starea de acces a ușii sunt afișate pe un display LCD folosind biblioteca `LiquidCrystal_I2C`.

### Controlul motorului servo
Motorul servo este controlat pentru a se roti la 90 de grade (simulând deschiderea ușii), urmând ca după câteva secunde să se întoarcă la starea inițială (pentru a o închide).

### Feedback auditiv
Un buzzer oferă feedback auditiv care indică dacă accesul este autorizat sau neautorizat.

## Motivația Alegerii Bibliotecilor Folosite

### MFRC522
Biblioteca `MFRC522` este esențială pentru interacțiunea cu cititorul RFID. Ea oferă funcții pentru detectarea și citirea cardurilor RFID.

### LiquidCrystal_I2C
Această bibliotecă simplifică interacțiunea cu display-urile LCD I2C, reducând numărul de pini necesari pe Arduino și ușurând procesul de afișare a informațiilor.

### Servo
Biblioteca `Servo` facilitează controlul motorului servo, permițând mișcări precise și ușor de implementat.

## Scheletul Proiectului și Interacțiunea Dintre Funcționalități

Proiectul este structurat în mai multe părți interdependente, fiecare contribuind la funcționarea generală a sistemului de blocare inteligentă RFID.

### Descrierea Funcționalităților

#### Detecția RFID
- **Funcția `card_detection`**: Această funcție verifică prezența unui card RFID nou. Dacă este detectat un card nou, funcția `get_card_id` extrage ID-ul cardului.
- **Funcția `get_card_id`**: Extrage ID-ul cardului și îl compară cu ID-ul autorizat folosind funcția `is_desired_tag`.

#### Feedback pentru Tag-ul RFID
- **Funcția `is_desired_tag`**: Verifică dacă ID-ul citit este cel autorizat.
- **Funcția `effect_desired_tag`**: Dacă ID-ul este autorizat, oferă feedback vizual și auditiv (pe LCD și cu ajutorul buzzer-ului) și sistemul deschide ușa.
- **Funcția `effect_denied_tag`**: Dacă ID-ul nu este autorizat, indică accesul refuzat prin feedback vizual pe LCD și auditiv prin buzzer.

### Diagramă de Interacțiune

1. **Detecția RFID**: 
    - `card_detection()` -> `get_card_id()` -> `is_desired_tag()`
2. **Feedback pentru Tag-ul RFID**:
    - Dacă ID-ul este autorizat: `effect_desired_tag()` -> Deschide ușa -> Afișare pe LCD -> Sunet buzzer
    - Dacă ID-ul nu este autorizat: `effect_denied_tag()` -> Afișare pe LCD -> Sunet buzzer

Prin aceste componente, proiectul asigură un sistem eficient și ușor de utilizat pentru controlul accesului bazat pe RFID, cu feedback vizual și auditiv și control automat al deschiderii ușii.
