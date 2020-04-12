# AI_TSP_SA

### Utazóügynök feladat szimulált hűtéssel

Megírt függvények:
- simulatedAnnealing: új állapotot generál, ami ha jobb, mint a jelenlegi, elfogadja, ha nem, akkor egy adott valószínűséggel fogadja el
- randomNeighbor: szomszédok random cseréje
- temperature: hőmérséklet i-dik iterációbeli értékének a kiszámítása
- f: városok közötti távolság kiszámítása a szomszédsági mátrix alapján
- probability: ha a paraméterként kapott érték kisebb mint egy [0,1] random szám, igazat, máskülönben hamisat térít vissza
- shuffle: kezdőállapot generálásához, és új, random állapot létrehozásához
- fillMatrix: mátrix feltöltése random értékekkel
- printMtrx

