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
  const char* text;          
};

// Menggunakan satu kalimat utuh agar bisa berjalan mulus (marquee)
LyricLine lyrics[] = {
  { 16170, "Mencari, ku tetap mencari kamu" },
  { 19920, "Hingga saat nafasku berhenti" },
  { 24180, "Kurasa cinta sejati tak ada" },
  { 27840, "Hanya ada dalam cerita legenda" },
  { 31980, "..." }, 
  { 39960, "Ah-ah-ah..." }, 
  { 42670, "..." }, 
  { 47880, "Kutulis namamu dalam jantungku" }, 
  { 51530, "Agar engkau memahami aku" }, 
  { 55390, "Dan kugambar wajahmu dalam nadiku" }, 
  { 59380, "Berharap kau takkan pernah tinggalkanku" }, 
  { 63170, "Apa kau tak merasakanku?" }, 
  { 66720, "Kau tak merasakan kasih sayangku" }, 
  { 70600, "Apa kau tak merasakanku?" }, 
  { 74490, "Kau tak merasakan kasih sayangku" }, 
  { 80810, "Oh-oh, dengarkan sebuah lagu untukmu" }, 
  { 86170, "Tercipta dari rintih hatiku" }, 
  { 90250, "Kau nikmati aku dan kau membuangku" }, 
  { 96150, "Oh-oh, dengarkanlah sang Raja Manusia" }, 
  { 102190, "Kupanjatkan doa dan memuja" }, 
  { 105910, "S'moga hukum karma datang membalasnya" }, 
  { 112250, "..." }, 
  { 120670, "Ah-ah-ah..." }, 
  { 128260, "Apa kau tak merasakanku?" }, 
  { 131870, "Kau tak merasakan kasih sayangku" }, 
  { 135460, "Apa kau tak merasakanku?" }, 
  { 139420, "Kau tak merasakan kasih sayangku" }, 
  { 145370, "Oh-oh, dengarkan sebuah lagu untukmu" }, 
  { 151270, "Tercipta dari rintih hatiku" }, 
  { 155170, "Kau nikmati aku dan kau membuangku" }, 
  { 161120, "Oh-oh, dengarkanlah sang Raja Manusia" }, 
  { 167290, "Kupanjatkan doa dan memuja" }, 
  { 170830, "S'moga hukum karma datang membalasnya" }, 
  { 177180, "Oh-oh, dengarkan sebuah lagu untukmu" }, 
  { 182830, "Tercipta dari rintih hatiku" }, 
  { 186620, "Kau nikmati aku dan kau membuangku" }, 
  { 192820, "Oh-oh, dengarkanlah sang Raja Manusia" }, 
  { 198530, "Kupanjatkan doa dan memuja" }, 
  { 202550, "Semoga hukum karma datang membalasnya" }, 
  { 213570, "SELESAI" }
};

const int totalLines = sizeof(lyrics) / sizeof(lyrics[0]);
unsigned long startTime = 0;
int currentLine = -1;

// Fungsi teks berjalan (Scroll Horizontal Mulus) dengan ukuran besar (Size 2)
void drawScrollingText(const char* text) {
  int len = strlen(text);
  int textWidth = len * 12; // Estimasi lebar teks dengan TextSize(2)

  // Jika teks pendek, tampilkan diam di tengah layar
  if (textWidth <= 128) {
    display.clearDisplay();
    display.drawRect(0, 0, 128, 64, SSD1306_WHITE); // Bingkai estetik
    display.setTextSize(2);
    display.setCursor((128 - textWidth) / 2, 24);
    display.print(text);
    display.display();
    return;
  }

  // Jika teks panjang, jalankan animasi berjalan dari kanan ke kiri secara halus
  for (int x = 128; x >= -textWidth; x -= 4) {
    display.clearDisplay();
    display.drawRect(0, 0, 128, 64, SSD1306_WHITE); // Bingkai estetik
    
    display.setTextSize(2);
    display.setCursor(x, 24);
    display.print(text);
    
    display.display();
    delay(25); // Kecepatan gerak teks (semakin kecil angka, semakin cepat)
  }
}

void setup() {
  Serial.begin(115200);
  Wire.begin(8, 9); // SDA: GPIO 8, SCL: GPIO 9 (ESP32-C3 SuperMini)

  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("Gagal menginisialisasi OLED!"));
    for (;;);
  }

  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);
  
  // Tampilan Intro Pembuka
  display.drawRect(0, 0, 128, 64, SSD1306_WHITE);
  display.setTextSize(2);
  display.setCursor(30, 24);
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

  // Update dan jalankan teks berjalan saat lirik berganti
  if (foundIndex != currentLine && foundIndex != -1) {
    currentLine = foundIndex;
    drawScrollingText(lyrics[currentLine].text);
  }
}
