main.ino

void lineFollow(){

  int error, delSpeed;
  float P, D;
  error= readSensor();

  if(error== 420){

    // if(turn == 1){
    //   lastSensor=2;
    //   turn=0;
    // }

    if(lastSensor == 1) wheel(-leftBaseSpeed, rightBaseSpeed);

    else if(lastSensor == 2) wheel(leftBaseSpeed, -rightBaseSpeed);
  }

  else{

    P= kp * error;
    D= kd * (error -  prevError);

    delSpeed = P + D;

    wheel((leftBaseSpeed + delSpeed), (rightBaseSpeed - delSpeed));

    prevError = error;
    
  }

}


**এই লাইন ফলোয়ার কোডটির বাংলা ব্যাখ্যা এবং কী পরিবর্তন করলে কী হবে:**

## 📝 **কোডের বাংলা অর্থ:**

```cpp
void lineFollow() {
  int error, delSpeed;       // ভ্যারিয়েবল ডিক্লেয়ার
  float P, D;                // PID এর P এবং D অংশ
  
  error = readSensor();      // সেন্সর থেকে error পড়া
  
  if(error == 420) {         // যদি error 420 হয় (লাইন হারিয়ে গেছে)
    
    // যদি turn == 1 হয় (কমেন্ট আউট করা)
    // lastSensor = 2 সেট করো
    // turn = 0 সেট করো
    
    if(lastSensor == 1) 
      wheel(-leftBaseSpeed, rightBaseSpeed);  // বাম দিকে ঘুরো
    
    else if(lastSensor == 2) 
      wheel(leftBaseSpeed, -rightBaseSpeed);  // ডান দিকে ঘুরো
  }
  
  else {  // লাইন পাওয়া গেছে
    P = kp * error;          // Proportional অংশ
    D = kd * (error - prevError); // Derivative অংশ
    
    delSpeed = P + D;        // মোট correction
    
    // মোটর নিয়ন্ত্রণ
    wheel((leftBaseSpeed + delSpeed), (rightBaseSpeed - delSpeed));
    
    prevError = error;       // আগের error সেভ করো
  }
}
```

## 🔧 **কী পরিবর্তন করলে কী হবে:**

### **১. Error value পরিবর্তন:**
```cpp
if(error == 420) {  // বর্তমান
if(error == 300) {  // বেশি sensitive
if(error == 500) {  // কম sensitive
```
- **কম value** = বেশি sensitive (দ্রুত recovery)
- **বেশি value** = কম sensitive (ধীর recovery)

### **২. Recovery speed পরিবর্তন:**
```cpp
// বর্তমান:
wheel(-leftBaseSpeed, rightBaseSpeed);

// পরিবর্তন:
wheel(-leftBaseSpeed*1.5, rightBaseSpeed*1.5);  //更快 recovery
wheel(-leftBaseSpeed*0.8, rightBaseSpeed*0.8);  //ধীর recovery
```

### **৩. PID gains পরিবর্তন:**
```cpp
// Proportional gain (kp)
P = kp * error;  // kp বাড়ালে বেশি aggressive

// Derivative gain (kd)  
D = kd * (error - prevError);  // kd বাড়ালে বেশি stable
```

### **৪. Base speed পরিবর্তন:**
```cpp
// বর্তমান:
wheel((leftBaseSpeed + delSpeed), (rightBaseSpeed - delSpeed));

// পরিবর্তন:
wheel((leftBaseSpeed*1.2 + delSpeed), (rightBaseSpeed*1.2 - delSpeed)); //更快
wheel((leftBaseSpeed*0.8 + delSpeed), (rightBaseSpeed*0.8 - delSpeed)); //ধীর
```

## 🎯 **কোডের কাজ কী:**

### **১. লাইন পাওয়া গেলে:**
- **PID control** ব্যবহার করে স্মুথভাবে চলবে
- **Error অনুযায়ী** speed adjust করবে
- **সোজা থাকার** চেষ্টা করবে

### **২. লাইন হারালে:**
- **শেষ known direction** অনুযায়ী ঘুরবে
- **লাইন খুঁজবে**
- **Recovery করার** চেষ্টা করবে

## ⚙️ **টিউনিং করার উপায়:**

### **দ্রুত করতে চাইলে:**
```cpp
float kp = 0.30;    // বাড়ানো
float kd = 6.0;     // বাড়ানো  
int leftBaseSpeed = 200;  // বাড়ানো
int rightBaseSpeed = 200; // বাড়ানো
```

### **স্থির করতে চাইলে:**
```cpp
float kp = 0.20;    // কমানো
float kd = 3.0;     // কমানো
int leftBaseSpeed = 150;  // কমানো
int rightBaseSpeed = 150; // কমানো
```

### **Recoivery improve করতে:**
```cpp
if(error == 300) {  //更低 error threshold
wheel(-leftBaseSpeed*1.3, rightBaseSpeed*1.3);  //更快 recovery
```

## 📊 **Example Scenario:**

### **লাইন center এ থাকলে:**
```
error = 0
delSpeed = 0
wheel(200, 200)  // সোজা চলো
```

### **লাইন বামে থাকলে:**
```
error = -1000 (বাম দিকে error)
delSpeed = -30 (বাম মোটর slow, ডান মোটর fast)
wheel(170, 230)  // ডান দিকে ঘুরো
```

### **লাইন হারালে:**
```
error = 420
lastSensor = 1 (শেষে বামে ছিল)
wheel(-200, 200)  // বাম দিকে ঘুরো
```

initialization.ino





