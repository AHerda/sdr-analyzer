# Projekt Analizy Radiowej w C++
    Autor: Adrian Herda
    Data: 10.12.2024 r.
Ten projekt to aplikacja napisana w C++, służąca do analizy sygnałów radiowych. Jest zbudowana przy użyciu CMake i wymaga dwóch zewnętrznych bibliotek: libairspy oraz libusb-1.0. <br>
Napisany został również skrypt w języku Python do wizualizacji wyników.<br>
Projekt ten zsotał stworzony jako implementacja oprogramowania do pracy inżynierskiej pt. **<i>Analiza i wizualizacja ruchu radiowaego w paśmie ISM</i>**

## Aplikacja
### Wymagania
Przed zbudowaniem projektu upewnij się, że masz zainstalowane następujące biblioteki:

1. [libairspy](https://github.com/airspy/airspyone_host)
2. [libusb-1.0](https://libusb.info)

### Instalacja na Linuxie (Ubuntu/Debian):
```bash
sudo apt-get install libairspy-dev libusb-1.0-0-dev
```
W razie problemów z biblioteką *libairspy* podążaj za instrukcją instalacji na [stronie autorów](https://github.com/airspy/airspyone_host).<br>
Na systemach macOS i Windows zapoznaj się z dokumentacją odpowiednich bibliotek, aby je poprawnie zainstalować.

### Budowanie projektu
1. Utwórz katalog build i skonfiguruj projekt za pomocą CMake:

```bash
mkdir build
cd build
cmake ..
```

2. Skompiluj projekt:
```bash
make
```

3. Plik wykonywalny zostanie zapisany w katalogu build.

### Uruchamianie aplikacji
Aplikacja obsługuje następujące flagi wiersza poleceń:

Flaga | Alias | Opis
--- | --- | ---
--frequency | -f | Ustawia częstotliwość (w kHz) do analizy.
--description | -d | Dodaje opis do sesji analizy.
--output | -o | Określa plik wynikowy do zapisu wyników.
--time | -t | Ustawia czas trwania analizy (w sekundach).
--repeat | -r | Powtarza analizę określoną liczbę razy.
--append | -a | Dopisuje wyniki do istniejącego pliku.


### Przykłady użycia
1. Podstawowe uzycie:
```bash
./sdr-analyzer
```

Analiza z wartościami domyślnymi.
* Pasmo: 433,92 MHz,
* Opis: "",
* Plik wynikowy: ../data/output.csv
* Czas trwania jednego testu: 60s,
* Ilość powtórzeń: 1
* Nadpisywanie pliku

2. Zmiana podstawowych wartości:

```bash
./sdr-analyzer -f 433000 -t 60 -o results.csv
```
Analiza pasma 433 MHz przez 60 sekund, zapis wyników do results.csv.

3. Powtarzanie analizy:

```bash
./sdr-analyzer -f 869000 -t 120 -o results.csv -r 3
```
Analiza pasma 869 MHz trzykrotnie, każde uruchomienie trwa 120 sekund. Wyniki zapisywane są do results.csv.

4. Dopisanie wyników:

```bash
./sdr-analyzer -f 915000 -t 90 -o data.csv -a
```
Dopisanie wyników analizy pasma 915 MHz przez 90 sekund do pliku data.csv.

### Funkcjonalności
* Analiza częstotliwości radiowych i rejestracja danych.
* Powtarzanie testów z przerwami między iteracjami.
* Dopisywanie wyników do istniejących plików.
* Pełna konfiguracja za pomocą flag wiersza poleceń.

### Uwagi
* Aplikacja wprowadza 15-sekundową przerwę między powtórzeniami testów, aby umożliwić stabilizację środowiska.
* Przed uruchomieniem aplikacji upewnij się, że wymagany sprzęt (np. urządzenie Airspy) jest poprawnie podłączony i rozpoznawany przez system.

## Skrypt do wizualizacji

Przed włączeniem skryptu do wizualizacji upewnij się że w środowisku zainstalowane są biblioteki:
1. pandas
2. numpy
3. matplotlib

### Uruchamianie
Domyślnie skrypt będzie pobierał dane z folderu *data/* oraz zapisywał wykresy do folderu *plots/*
Jako argumenty można podać ścieżkę do folderu z danymi oraz ścieżkę docelowego folderu do zapisywania wykresów.

1. Podstawowe wywołanie:
```bash
python python/plot.py
```

2. Przykładowe wywołanie z zmeinionymi folderami
```bash
python python/plot.py dane wykresy
```

#
W przypadku pytań lub problemów skontaktuj się z opiekunem projektu.
