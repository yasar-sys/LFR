#define inA     A1
#define inB     A0
#define inC     A3
#define inD     A2
#define enA     11
#define enB     10

// #define inA     A0
// #define inB     A1
// #define inC     A2
// #define inD     A3
// #define enA     11
// #define enB     10

// #define inA     12
// #define inB     13
// #define inC     11
// #define inD     8
// #define enA     10
// #define enB     9

// int turn=0;

int leftBaseSpeed   =200; //80; 170 
int rightBaseSpeed  =200; //80; 170
int maxSpeed        =250; //80; 255

#define NUM_SENSORS    8

int sValues[NUM_SENSORS], lastSensor;

float kp            = 20; //6
float kd            = 26; //8
int prevError;

void initialize();
void lineFollow();
int readSensor();
void wheel();

void setup() {
  
  initialize();
  // Serial.begin(9600);
  // digitalWrite(inA, HIGH);
}

void loop() {

  
  lineFollow();
  

}



**এই কোডটি একটি সম্পূর্ণ লাইন ফলোয়ার রোবটের জন্য। নিচে বাংলায় ব্যাখ্যা করা হলো:**

## 📝 **কোডের বাংলা অর্থ:**

```cpp
// মোটর ড্রাইভার পিন ডেফাইন - Version 1
#define inA     A1    // বাম মোটর direction 1
#define inB     A0    // বাম মোটর direction 2  
#define inC     A3    // ডান মোটর direction 1
#define inD     A2    // ডান মোটর direction 2
#define enA     11    // বাম মোটর speed (PWM)
#define enB     10    // ডান মোটর speed (PWM)

// Alternative configurations (কমেন্ট আউট করা)
// #define inA     A0
// #define inB     A1
// ... অন্যান্য কনফিগারেশন

// স্পিড সেটিংস
int leftBaseSpeed   = 200;  // বাম মোটর বেস স্পিড
int rightBaseSpeed  = 200;  // ডান মোটর বেস স্পিড  
int maxSpeed        = 250;  // সর্বোচ্চ স্পিড

#define NUM_SENSORS 8      // মোট সেন্সর সংখ্যা

// গ্লোবাল ভ্যারিয়েবল
int sValues[NUM_SENSORS];  // সেন্সর ভ্যালু অ্যারে
int lastSensor;            // শেষ সেন্সর অবস্থান

// PID gains
float kp = 20;    // Proportional gain (উচ্চ মান = aggressive)
float kd = 26;    // Derivative gain (উচ্চ মান = stable)
int prevError;     // আগের error

// ফাংশন ডিক্লারেশন
void initialize();  // initialization ফাংশন
void lineFollow();  // লাইন ফলো ফাংশন  
int readSensor();   // সেন্সর পড়ার ফাংশন
void wheel();       // মোটর কন্ট্রোল ফাংশন

void setup() {
  initialize();     // initialization কল
  // Serial.begin(9600);  // Serial কমিউনিকেশন (কমেন্ট আউট)
}

void loop() {
  lineFollow();     // непрерывভাবে লাইন ফলো
}
```

## 🎯 **কোডের মূল কাজ:**

### **১. মোটর কন্ট্রোল:**
- **inA, inB** - বাম মোটরের দিক নিয়ন্ত্রণ
- **inC, inD** - ডান মোটরের দিক নিয়ন্ত্রণ
- **enA, enB** - মোটরের speed নিয়ন্ত্রণ (PWM)

### **২. স্পিড সেটিংস:**
- **leftBaseSpeed = 200** - বাম মোটর normal speed
- **rightBaseSpeed = 200** - ডান মোটর normal speed
- **maxSpeed = 250** - সর্বোচ্চ speed limit

### **৩. PID কন্ট্রোল:**
- **kp = 20** - Proportional gain (aggressive)
- **kd = 26** - Derivative gain (stable)

## 🔧 **কী পরিবর্তন করলে কী হবে:**

### **১. স্পিড বাড়াতে:**
```cpp
int leftBaseSpeed = 230;   // 200 -> 230
int rightBaseSpeed = 230;  // 200 -> 230
int maxSpeed = 255;        // 250 -> 255
```
- **Effect**: রোবট更快 চলবে

### **২. স্পিড কমাতে:**
```cpp
int leftBaseSpeed = 150;   // 200 -> 150  
int rightBaseSpeed = 150;  // 200 -> 150
int maxSpeed = 200;        // 250 -> 200
```
- **Effect**: রোবট ধীরে চলবে,更加 stable

### **৩. PID gains পরিবর্তন:**
```cpp
float kp = 15;  // 20 -> 15 (কম aggressive)
float kd = 30;  // 26 -> 30 (更加 stable)
```
- **Effect**: smoother movement, less oscillation

### **４. মোটর পিন কনফিগারেশন:**
```cpp
// Alternative configuration ব্যবহার করতে:
// #define inA     A0  // uncomment করুন
// #define inB     A1
// ... etc.
```
- **Effect**: different motor driver pin configuration

## ⚙️ **টিউনিং করার指南:**

### **দ্রুত কিন্তু less stable:**
```cpp
float kp = 25;    //更高 kp
float kd = 20;    //更低 kd  
int leftBaseSpeed = 220;
int rightBaseSpeed = 220;
```

### **ধীর কিন্তু more stable:**
```cpp
float kp = 15;    //更低 kp
float kd = 30;    //更高 kd
int leftBaseSpeed = 180;  
int rightBaseSpeed = 180;
```

### **Competition optimized:**
```cpp
float kp = 20;    // Balanced kp
float kd = 26;    // Balanced kd
int leftBaseSpeed = 200;
int rightBaseSpeed = 200;
```

## 🚀 **কোডটি如何使用:**

### **১. Hardware connection:**
- **L298N motor driver** সাথে connect করুন
- **IR sensor array** (8 sensors) connect করুন
- **সঠিক power supply** দিন

### **২. Calibration:**
- **kp এবং kd** values track conditions অনুযায়ী adjust করুন
- **base speed**根据需要 adjust করুন

### **৩. Competition:**
- **maxSpeed** competition requirements অনুযায়ী set করুন
- **PID gains** fine-tune করুন optimal performance এর জন্য

**এই কোডটি একটি professional-level line follower!** 🏆
