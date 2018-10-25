
Synchronizacja procesów z wykorzystaniem semaforów

Wyobraźmy sobie fabrykę, w której produkowany jest przedmiot
składający się z dwóch elementów Y oraz Z. W fabryce pracują N + M + P
robotów (procesów):

 N robotów specjalizuje się w produkcji elementów Y i po
wyprodukowaniu elementu kładzie go na taśmie produkcyjnej
(buforze) BY,

 M robotów specjalizuje się w produkcji elementów Z i po
wyprodukowaniu elementu kładzie go na taśmie produkcyjnej
(buforze) BZ,

 P robotów pobiera i paruje elementy z taśm produkcyjnych BY i BZ –
tak powstały przedmiot YZ jest produktem końcowym.

Przyjmijmy, że elementy Y i Z to liczby naturalne mniejsze od 10, a
parowanie Y i Z to operacja polegająca na stworzenie liczby postaci YZ (lub
inaczej: liczby o wartości Y*10+Z) 1 .

Należy przyjąć że taśmy produkcyjne mogą jednocześnie pomieścić
najwyżej 5 elementów.

Produkcja powinna zostać zakończona po zbudowaniu 10 przedmiotów YZ.

Dla uproszczenia można przyjąć, że każdy z robotów parujących
pobiera najpierw element z kolejki Y, następnie z kolejki Z i sparowany
przedmiot drukuje na standardowe wyjście. Jeśli któraś z tych kolejek jest
pusta, robot oczekuje na pojawienie się elementu.

W ramach zadania należy stworzyć program symulujący pracę
fabryki przy pomocy N + M + P procesów (roboty) i 2 buforów (taśmy
produkcyjne). Aby zapobiec przepełnieniu buforów i jednoczesnemu
wykonywaniu operacji na buforze należy wykorzystać mechanizm
semaforów. Należy zwrócić szczególną uwagę, aby żaden z elementów nie
został „zdublowany” albo zagubiony.

Dodatkowo należy zasymulować czas pracy robotów przez uśpienie
procesów na losową wartość z zakresu:

 <1, R> dla procesów produkujących element Y,

 <1, S> dla procesów produkujących element Z,


Np. Jeśli Y=2 a Z=9 to końcowy produkt to 29 <1, T> dla procesów parujących elementy Y i Z.
Podczas implementacji, należy skorzystać z semaforów oferowanych
przez system Linux. Należy pamiętać o usunięciu semaforów po
zakończeniu działania programu.

Bufor można zaimplementować jako tablicę bądź listę. Pobieranie
elementów ma być zgodne z zasadą FIFO.

Wartości M, N, P, R, S i T powinny być konfigurowalne przy uruchomieniu.

