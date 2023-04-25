
## Tentang Project

Hi, selamat datang di halaman project Saya. Project ini buat untuk bersenang senang dan untuk meluapkan yang ada di kepala Saya. Untuk kedepanya Saya akan rutin update fitur tambahan agar bisa digunakan sebaik mungkin. 

## Komponen 

- esp32
- Magnet sensor

## Library

- [Universal-Arduino-Telegram-Bot](https://github.com/witnessmenow/Universal-Arduino-Telegram-Bot)
- WiFiClientSecure (default install)


## Cara Kerja

Pertama, esp akan connect ke wifi. Kedua, data dari sensor magnet akan di baca microcontroller yaitu esp32. Ketiga, jika microcontroller mendapatkan data dari sensor kemudian microcontroller akan mengirimkan data ke telegram melalui API. Poin penting dalam project ini adalah pembacaan sensor, kemudian microcontroller/esp32 akan mengrimkan data ke telegram melalui API.Atau, Jika sensor mendapatkan data maka telegram akan mendapatkan notifikasi pesan.

## Schematic

**Gambar Menyusul**

Note: Sensor magnet di hubungkan ke pin GPIO02


