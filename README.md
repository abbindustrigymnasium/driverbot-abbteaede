# Driverbot
Bilen är byggd i lego med 3d printade delar för servo och motor. Styrningen sker på en hemsida som har en av och på knapp. Om knappen är i tryckt kan värden skickas genom mqtt till arduino som sedan ändrar bilens styrning. 

För att ändra styrningen finns det en joystick på hemsidan som kan snurra 360 grader och sedan ändrar koden värdena för att se om bilen ska åka bakåt/framåt, hur snabbt och hur hjulen ska svänga.

Motorn som används är en TT-motor och servot är ett SG90.

Joysticken är ifrån - https://github.com/yoannmoinet/nipplejs

## Hur det fungerar
![Diagram!](https://github.com/abbindustrigymnasium/driverbot-abbteaede/blob/master/DriverBotFl%C3%B6desDiagram.png)

### Hemsidan
Hemsidan går ut på att endast ha en joystick gjord för roboten för att enkelt kunna styra genom internet. På hemsidan finns en checkbox för att kunna köra bilen och sedan kan man trycka vart som helst på skrämen för att aktivera en joystick som hämtar värdena där man släpper joysticken. När joysticken släpps skickas värdena och bilen ändrar till de nya inställningarna snabbt. Värdena som skickas är farten, fram eller bak och hur mycket den ska svänga.

### Styrningen
Eftersom jag använder mig av en färdig joystick från nipplejs så tar jag distansen från radien genom radien multiplicerat med 1023 för att få farten min motor ska ha. Om man drar längst ut på joysticken kommer roboten därför åka i 1023. Eftersom joysticken är 360 grader och servot bara 180 grader, så har jag läst av värdena jag fått och fått fram att om det är över 180 grader ska den åka bakåt. Annars åker den framåt och graderna görs om för att det ska bli rätt för om den åker framåt eller bakåt. Det finns även ett max värde för hur mycket servot kan svänga vilket gör att den inte kan svänga 180 grader.

### MQTT brokern
För att skicka över värdena använder jag mig av https://www.maqiatto.com/ som tillåter dig att subscribea vilket jag gör i arduino och publisha vilket jag gör på hemsidan. Det finns även olika topics som gör att jag kan skicka i olika topics för olika ärenden, som fart eller hur mycket servot ska svänga. Eftersom maqiatto inte loggar värdena någonstans kan bilen inte hämta gamla värden utan det går bara att hämta värden som skickas när man är subscribad.

## Extra

### Problem under vägen
- Jag hade väldigt svårt att få till rätt värden till servot eftersom det endast svängar 180 grader medans joysticken svänger 360 grader. Det tog lång tid innan jag fattade vad som blev fel och det var att den hela tiden svängde åt motsatta hål utom när den skulle svänga vänster. Med lite hjälp fixade jag sedan problemet.
### Loggbok för projektet driverbot
23/3-2020
- Jag började med min kod i arduino så att den kopplade upp till mqtt och kunde göra enkla styrningar med mqtt

24/3-2020
- Skapade hemsidan
- Lade till en joystick från nipplejs
- Gjorde små design ändringar som en titel 

27/3-2020
- Testade igenom värdena jag fick från joysticken 
- Skickade värdena för att åka fram eller bakåt och hur snabbt

31/3-2020
- Började med servot i arduino genom att koppla ihop det med mikrokontrollen och gjorde små ändringar i koden
- Läste av värdena jag fick av joysticken för att kunna skicka rätt värden till servot, jag hade många problem med det och det tog lång tid
- Började med att kunna styra med en ps4 kontroll men fick sedan reda på att man inte längre behöver en extra sak

20/4-2020
- Åkte in till skolan för att bygga klart min bil
- Fixade styrningen helt och det skickade nu rätt värden för svängningen

21/4-2020
- Ändrare lite i koden och tog bort onödigt saker
- Kommenterade all kod i arduino och på hemsidan
