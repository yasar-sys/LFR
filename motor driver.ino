void wheel(int leftSpeed, int rightSpeed){
  

  if(leftSpeed == 0){

    digitalWrite(inC, LOW);
    digitalWrite(inD, LOW);

  }

  if(leftSpeed > 0){

    digitalWrite(inC, HIGH);
    digitalWrite(inD, LOW);

  }

  else if(leftSpeed < 0){

    digitalWrite(inC, LOW);
    digitalWrite(inD, HIGH);

  }

  if(rightSpeed == 0){

    digitalWrite(inA, LOW);
    digitalWrite(inB, LOW);

  }

  if(rightSpeed > 0){

    digitalWrite(inB, HIGH);
    digitalWrite(inA, LOW);

  }

  else if(rightSpeed < 0){

    digitalWrite(inB, LOW);
    digitalWrite(inA, HIGH);

  }

  // digitalWrite(inB, HIGH);
  // digitalWrite(inC, HIGH);

  if(abs(leftSpeed)> maxSpeed) leftSpeed= maxSpeed;
  if(abs(rightSpeed)> maxSpeed) rightSpeed= maxSpeed;

  analogWrite(enA, abs(rightSpeed));
  analogWrite(enB, abs(leftSpeed));
  
}



**এই `wheel()` ফাংশনটির বাংলা ব্যাখ্যা এবং কী পরিবর্তন করলে কী হবে:**

## 📝 **কোডের বাংলা অর্থ:**

```cpp
void wheel(int leftSpeed, int rightSpeed){
  
  // বাম মোটর কন্ট্রোল
  if(leftSpeed == 0){               // যদি বাম মোটর স্পিড 0 হয়
    digitalWrite(inC, LOW);         // both pins LOW (stop)
    digitalWrite(inD, LOW);
  }

  if(leftSpeed > 0){                // যদি বাম মোটর positive স্পিড
    digitalWrite(inC, HIGH);        // forward direction
    digitalWrite(inD, LOW);
  }

  else if(leftSpeed < 0){           // যদি বাম মোটর negative স্পিড
    digitalWrite(inC, LOW);         // reverse direction  
    digitalWrite(inD, HIGH);
  }

  // ডান মোটর কন্ট্রোল
  if(rightSpeed == 0){              // যদি ডান মোটর স্পিড 0 হয়
    digitalWrite(inA, LOW);         // both pins LOW (stop)
    digitalWrite(inB, LOW);
  }

  if(rightSpeed > 0){               // যদি ডান মোটর positive স্পিড
    digitalWrite(inB, HIGH);        // forward direction
    digitalWrite(inA, LOW);
  }

  else if(rightSpeed < 0){          // যদি ডান মোটর negative স্পিড
    digitalWrite(inB, LOW);         // reverse direction
    digitalWrite(inA, HIGH);
  }

  // স্পিড লিমিটিং
  if(abs(leftSpeed) > maxSpeed) leftSpeed = maxSpeed;     // বাম মোটর স্পিড লিমিট
  if(abs(rightSpeed) > maxSpeed) rightSpeed = maxSpeed;   // ডান মোটর স্পিড লিমিট

  // PWM দিয়ে স্পিড সেট
  analogWrite(enA, abs(rightSpeed));  // ডান মোটর স্পিড
  analogWrite(enB, abs(leftSpeed));   // বাম মোটর স্পিড
}
```

## 🎯 **ফাংশনটির কাজ:**

### **১. মোটর দিক নিয়ন্ত্রণ:**
- **Positive speed** → সামনের দিকে চলা
- **Negative speed** → পিছনের দিকে চলা  
- **Zero speed** → থেমে যাওয়া

### **২. স্পিড লিমিটিং:**
- **maxSpeed** এর বেশি স্পিড allow করে না
- **Safety feature** হিসেবে কাজ করে

### **৩. PWM স্পিড কন্ট্রোল:**
- **analogWrite()** দিয়ে smooth speed control

## 🔧 **কী পরিবর্তন করলে কী হবে:**

### **১. মোটর দিক উল্টানো:**
```cpp
// বর্তমান ফরওয়ার্ড:
digitalWrite(inC, HIGH);
digitalWrite(inD, LOW);

// উল্টানো ফরওয়ার্ড:  
digitalWrite(inC, LOW);
digitalWrite(inD, HIGH);
```
- **Effect**: মোটর দিক উল্টে যাবে

### **২. স্পিড লিমিট পরিবর্তন:**
```cpp
// বর্তমান:
if(abs(leftSpeed) > maxSpeed) leftSpeed = maxSpeed;

// পরিবর্তন:
if(abs(leftSpeed) > maxSpeed) leftSpeed = maxSpeed * 0.9;  // 90% limit
```
- **Effect**:更加 conservative speed limiting

### **৩. Deadzone compensation:**
```cpp
// যোগ করতে পারেন:
if(abs(leftSpeed) < 50) leftSpeed = 0;  // Low speed ignore
if(abs(rightSpeed) < 50) rightSpeed = 0;
```
- **Effect**: Low speed এ motor chatter কমবে

### **৪. Acceleration limiting:**
```cpp
// যোগ করতে পারেন:
static int lastLeftSpeed = 0;
static int lastRightSpeed = 0;

leftSpeed = constrain(leftSpeed, lastLeftSpeed-20, lastLeftSpeed+20);
rightSpeed = constrain(rightSpeed, lastRightSpeed-20, lastRightSpeed+20);

lastLeftSpeed = leftSpeed;
lastRightSpeed = rightSpeed;
```
- **Effect**: Smooth acceleration/deceleration

## ⚙️ **Motor Driver Truth Table:**

### **বাম মোটর:**
| inC | inD | Result       |
|-----|-----|-------------|
| LOW | LOW | Brake/Stop  |
| HIGH| LOW | Forward     |
| LOW | HIGH| Reverse     |
| HIGH| HIGH| Short circuit (bad) |

### **ডান মোটর:**
| inA | inB | Result       |
|-----|-----|-------------|
| LOW | LOW | Brake/Stop  |
| LOW | HIGH| Forward     |
| HIGH| LOW | Reverse     |
| HIGH| HIGH| Short circuit (bad) |

## 🚀 **Usage Examples:**

### **সামনে যাওয়া:**
```cpp
wheel(200, 200);  // Both motors forward
```

### **পিছনে যাওয়া:**
```cpp
wheel(-200, -200); // Both motors reverse
```

### **বামে ঘোরা:**
```cpp
wheel(-150, 150);  // Left reverse, Right forward
```

### **ডানে ঘোরা:**
```cpp
wheel(150, -150);  // Left forward, Right reverse
```

### **থেমে যাওয়া:**
```cpp
wheel(0, 0);       // Both motors stop
```

## 🔧 **Improved Version:**

```cpp
void wheel(int leftSpeed, int rightSpeed){
  // Left motor direction
  if(leftSpeed == 0){
    digitalWrite(inC, LOW);
    digitalWrite(inD, LOW);
  }
  else if(leftSpeed > 0){
    digitalWrite(inC, HIGH);
    digitalWrite(inD, LOW);
  }
  else {
    digitalWrite(inC, LOW);
    digitalWrite(inD, HIGH);
  }

  // Right motor direction
  if(rightSpeed == 0){
    digitalWrite(inA, LOW);
    digitalWrite(inB, LOW);
  }
  else if(rightSpeed > 0){
    digitalWrite(inB, HIGH);
    digitalWrite(inA, LOW);
  }
  else {
    digitalWrite(inB, LOW);
    digitalWrite(inA, HIGH);
  }

  // Speed limiting with deadzone compensation
  leftSpeed = constrain(leftSpeed, -maxSpeed, maxSpeed);
  rightSpeed = constrain(rightSpeed, -maxSpeed, maxSpeed);
  
  // Apply minimum speed threshold
  if(abs(leftSpeed) < 30) leftSpeed = 0;
  if(abs(rightSpeed) < 30) rightSpeed = 0;

  analogWrite(enA, abs(rightSpeed));
  analogWrite(enB, abs(leftSpeed));
}
```

**এই ফাংশনটি非常重要** কারণ এটি directly মোটরগুলিকে control করে! 🚗💨
