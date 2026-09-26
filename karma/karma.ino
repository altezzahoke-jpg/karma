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

LyricLine lyrics[] = {
  { 16170, "Mencari", "Mencari kamu" },
  { 19920, "Hingga saat", "Nafasku berhenti" },
  { 24180, "Kurasa cinta", "Sejati tak ada" },
  { 27840, "Hanya ada di", "Cerita legenda" },
  { 31980, "", "" }, 
  { 39960, "Ah-ah-ah", "" }, 
  { 42670, "", "" }, 
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
  { 112250, "", "" }, 
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

// --- FUNGSI ANIMASI 1: Geser dari Kanan ke Kiri (Slide from Right) ---
void effectSlideRight(const char* t1, const char* t2) {
  for (int x = 128; x >= 10; x -= 14) {
    display.clearDisplay();
    display.drawRect(0, 0, 128, 64, SSD1306_WHITE);
    display.setCursor(x, 22);
    display.println(t1);
    display.setCursor(x, 38);
    display.println(t2);
    display.display();
    delay(10);
  }
}

// --- FUNGSI ANIMASI 2: Efek Ketik (Typewriter Effect) ---
void effectTypewriter(const char* t1, const char* t2) {
  char buffer1[32] = "";
  char buffer2[32] = "";
  int len1 = strlen(t1);
  int len2 = strlen(t2);
  int maxLen = max(len1, len2);

  for (int i = 0; i <= maxLen; i++) {
    display.clearDisplay();
    display.drawRect(0, 0, 128, 64, SSD1306_WHITE);
    
    if (i < len1) { buffer1[i] = t1[i]; buffer1[i+1] = '\0'; }
    if (i < len2) { buffer2[i] = t2[i]; buffer2[i+1] = '\0'; }

    display.setCursor(10, 22);
    display.println(buffer1);
    display.setCursor(10, 38);
    display.println(buffer2);
    display.display();
    delay(20);
  }
}

// --- FUNGSI ANIMASI 3: Efek Kedip Masuk (Blink/Fade In Simulation) ---
void effectBlinkIn(const char* t1, const char* t2) {
  for (int b = 0; b < 3; b++) {
    display.clearDisplay();
    display.display();
    delay(30);
    display.drawRect(0, 0, 128, 64, SSD1306_WHITE);
    display.setCursor(10, 22);
    display.println(t1);
    display.setCursor(10, 38);
    display.println(t2);
    display.display();
    delay(40);
  }
}

// --- FUNGSI ANIMASI 4: Efek Geser dari Atas (Drop Down) ---
void effectDropDown(const char* t1, const char* t2) {
  for (int y = 0; y <= 22; y += 4) {
    display.clearDisplay();
    display.drawRect(0, 0, 128, 64, SSD1306_WHITE);
    display.setCursor(10, y);
    display.println(t1);
    display.setCursor(10, y + 16);
    display.println(t2);
    display.display();
    delay(15);
  }
}

// Fungsi utama pemilih transisi otomatis berdasarkan nomor baris lirik
void playDynamicTransition(int index, const char* t1, const char* t2) {
  int animType = index % 4; // Berputar dari 0 sampai 3 secara otomatis

  switch (animType) {
    case 0:
      effectSlideRight(t1, t2);
      break;
    case 1:
      effectTypewriter(t1, t2);
      break;
    case 2:
      effectBlinkIn(t1, t2);
      break;
    case 3:
      effectDropDown(t1, t2);
      break;
  }
}

void setup() {
  Serial.begin(115200);
  Wire.begin(8, 9); 

  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("OLED Gagal!"));
    for (;;);
  }

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  
  display.drawRect(0, 0, 128, 64, SSD1306_WHITE);
  display.setCursor(18, 20);
  display.println(F("KARMA - DYNAMIC"));
  display.setCursor(28, 36);
  display.println(F("OLED ESP32-C3"));
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
    
    // Panggil efek transisi yang berbeda-beda secara otomatis
    playDynamicTransition(currentLine, lyrics[currentLine].text1, lyrics[currentLine].text2);
  }
}
