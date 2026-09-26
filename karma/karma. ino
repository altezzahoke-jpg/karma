#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1
#define SCREEN_ADDRESS 0x3C

// Pin I2C Default ESP32-C3 SuperMini: SDA = GPIO 8, SCL = GPIO 9
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

struct LyricLine {
  unsigned long timestampMs; 
  const char* text;          
};

// Array lirik dengan format string tunggal yang valid.
// Gunakan \n untuk memindah baris di layar OLED tanpa merusak sintaks C++.
LyricLine lyrics[] = {
  { 16170, "Mencari, ku tetap\nmencari kamu" },
  { 19920, "Hingga saat\nnafasku berhenti" },
  { 24180, "Kurasa cinta\nsejati tak ada" },
  { 27840, "Hanya ada dalam\ncerita legenda" },
  { 31980, "" }, // Jeda Kosong
  { 39960, "Ah-ah-ah" }, 
  { 42670, "" }, // Jeda Kosong
  { 47880, "Kutulis namamu\ndalam jantungku" }, 
  { 51530, "Agar engkau\nmemahami aku" }, 
  { 55390, "Dan kugambar wajahmu\ndalam nadiku" }, 
  { 59380, "Berharap kau takkan\npernah tinggalkanku" }, 
  { 63170, "Apa kau tak\nmerasakanku?" }, 
  { 66720, "Kau tak merasakan\nkasih sayangku" }, 
  { 70600, "Apa kau tak\nmerasakanku?" }, 
  { 74490, "Kau tak merasakan\nkasih sayangku" }, 
  { 80810, "Oh-oh, dengarkan\nsebuah lagu untukmu" }, 
  { 86170, "Tercipta dari\nrintih hatiku" }, 
  { 90250, "Kau nikmati aku\ndan kau membuangku" }, 
  { 96150, "Oh-oh, dengarkanlah\nsang Raja Manusia" }, 
  { 102190, "Kupanjatkan doa\ndan memuja" }, 
  { 105910, "S'moga hukum karma\ndatang membalasnya" }, 
  { 112250, "" }, // Jeda Kosong
  { 120670, "Ah-ah-ah" }, 
  { 128260, "Apa kau tak\nmerasakanku?" }, 
  { 131870, "Kau tak merasakan\nkasih sayangku" }, 
  { 135460, "Apa kau tak\nmerasakanku?" }, 
  { 139420, "Kau tak merasakan\nkasih sayangku" }, 
  { 145370, "Oh-oh, dengarkan\nsebuah lagu untukmu" }, 
  { 151270, "Tercipta dari\nrintih hatiku" }, 
  { 155170, "Kau nikmati aku\ndan kau membuangku, oh" }, 
  { 161120, "Oh-oh, dengarkanlah\nsang Raja Manusia" }, 
  { 167290, "Kupanjatkan doa\ndan memuja" }, 
  { 170830, "S'moga hukum karma\ndatang membalasnya" }, 
  { 177180, "Oh-oh, dengarkan\nsebuah lagu untukmu" }, 
  { 182830, "Tercipta dari\nrintih hatiku" }, 
  { 186620, "Kau nikmati aku\ndan kau membuangku" }, 
  { 192820, "Oh-oh, dengarkanlah\nsang Raja Manusia" }, 
  { 198530, "Kupanjatkan doa\ndan memuja" }, 
  { 202550, "Semoga hukum karma\ndatang membalasnya" }, 
  { 213570, "" } // Selesai
};

const int totalLines = sizeof(lyrics) / sizeof(lyrics[0]);
unsigned long startTime = 0;
int currentLine = -1;

void setup() {
  Serial.begin(115200);
  
  // Inisialisasi bus I2C ESP32-C3 (SDA: GPIO 8, SCL: GPIO 9)
  Wire.begin(8, 9); 

  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("Gagal menginisialisasi OLED SSD1306"));
    for (;;); // Berhenti jika OLED tidak merespons
  }

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setTextWrap(true); 
  
  // Tampilan Pembuka
  display.setCursor(10, 25);
  display.println(F("Kangen Band - Karma"));
  display.display();
  
  delay(3000); // Jeda sebelum lagu dimainkan
  startTime = millis(); 
}

void loop() {
  unsigned long elapsed = millis() - startTime;
  int foundIndex = -1;

  // Mencari indeks lirik aktif berdasarkan waktu berjalan
  for (int i = 0; i < totalLines; i++) {
    if (elapsed >= lyrics[i].timestampMs) {
      foundIndex = i;
    } else {
      break;
    }
  }

  // Update tampilan hanya saat lirik berpindah
  if (foundIndex != currentLine && foundIndex != -1) {
    currentLine = foundIndex;
    
    display.clearDisplay();
    
    // Header
    display.setTextSize(1);
    display.setCursor(0, 0);
    display.println(F("--- KARMA ---"));
    display.drawLine(0, 10, 128, 10, SSD1306_WHITE);

    // Area Teks Lirik
    display.setCursor(0, 22);
    display.println(lyrics[currentLine].text);

    display.display();
  }
}
