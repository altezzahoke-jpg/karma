#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1
#define SCREEN_ADDRESS 0x3C

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

struct LyricLine {
  unsigned long timestampMs; 
  const char* text1;          
  const char* text2;          
};

// Menggunakan format 2 baris agar stabil dan pas di layar OLED 128x64
LyricLine lyrics[] = {
  { 16170, "Mencari", "Mencari kamu" },
  { 19920, "Hingga saat", "Nafasku berhenti" },
  { 24180, "Kurasa cinta", "Sejati tak ada" },
  { 27840, "Hanya ada di", "Cerita legenda" },
  { 31980, "...", "" }, 
  { 39960, "Ah-ah-ah", "" }, 
  { 42670, "...", "" }, 
  { 47880, "Kutulis nama", "Dalam jantungku" }, 
  { 51530, "Agar engkau", "Memahami aku" }, 
  { 55390, "Dan kugambar", "Dalam nadiku" }, 
  { 59380, "Berharap kau", "Takkan pergi" }, 
  { 63170, "Apa kau tak", "Merasakanku?" }, 
  { 66720, "Kau tak rasa", "Kasih sayangku" }, 
  { 70600, "Apa kau tak", "Merasakanku?" }, 
  { 74490, "Kau tak rasa", "Kasih sayangku" }, 
  { 80810, "Dengarkanlah", "Lagu untukmu" }, 
  { 86170, "Tercipta dari", "Rintih hatiku" }, 
  { 90250, "Kau nikmati aku", "Lalu membuangku" }, 
  { 96150, "Dengarkanlah", "Raja Manusia" }, 
  { 102190, "Kupanjatkan", "Doa & memuja" }, 
  { 105910, "S'moga karma", "Datang membalas" }, 
  { 112250, "...", "" }, 
  { 120670, "Ah-ah-ah", "" }, 
  { 128260, "Apa kau tak", "Merasakanku?" }, 
  { 131870, "Kau tak rasa", "Kasih sayangku" }, 
  { 135460, "Apa kau tak", "Merasakanku?" }, 
  { 139420, "Kau tak rasa", "Kasih sayangku" }, 
  { 145370, "Dengarkan", "Lagu untukmu" }, 
  { 151270, "Tercipta dari", "Rintih hatiku" }, 
  { 155170, "Kau nikmati aku", "Dan membuangku" }, 
  { 161120, "Dengarkanlah", "Raja Manusia" }, 
  { 167290, "Kupanjatkan", "Doa & memuja" }, 
  { 170830, "S'moga karma", "Datang membalas" }, 
  { 177180, "Dengarkan", "Lagu untukmu" }, 
  { 182830, "Tercipta dari", "Rintih hatiku" }, 
  { 186620, "Kau nikmati aku", "Dan membuangku" }, 
  { 192820, "Dengarkanlah", "Raja Manusia" }, 
  { 198530, "Kupanjatkan", "Doa & memuja" }, 
  { 202550, "Semoga karma", "Datang membalas" }, 
  { 213570, "SELESAI", "" }
};

const int totalLines = sizeof(lyrics) / sizeof(lyrics[0]);
unsigned long startTime = 0;
int currentLine = -1;

// Fungsi tampil stabil dengan ukuran teks besar (Size 2) dan efek transisi aman
void displayLyric(const char* t1, const char* t2) {
  display.clearDisplay();
  
  // Bingkai luar estetik
  display.drawRect(0, 0, 128, 64, SSD1306_WHITE);
  
  // Baris Teks 1 (Ukuran 2 agar besar dan jelas)
  display.setTextSize(2);
  display.setCursor(8, 16);
  display.println(t1);

  // Baris Teks 2 (Ukuran 2)
  display.setCursor(8, 38);
  display.println(t2);

  display.display();
}

void setup() {
  Serial.begin(115200);
  Wire.begin(8, 9); // SDA: 8, SCL: 9 untuk ESP32-C3 SuperMini

  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("Gagal menginisialisasi OLED!"));
    for (;;);
  }

  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);
  
  // Tampilan Intro
  display.setTextSize(2);
  display.setCursor(20, 24);
  display.println(F("KARMA"));
  display.display();
  
  delay(3000);
  startTime = millis(); 
}

void loop() {
  unsigned long elapsed = millis() - startTime;
  int foundIndex = -1;

  for (int i = 0; i < totalLines; i++) {
    if (elapsed >= lyrics[i].timestampMs) {
      foundIndex = i;
    } else {
      break;
    }
  }

  if (foundIndex != currentLine && foundIndex != -1) {
    currentLine = foundIndex;
    displayLyric(lyrics[currentLine].text1, lyrics[currentLine].text2);
  }
}
