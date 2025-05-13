# Modifying-Values

This project is designed for the **FRDM-KL05Z microcontroller** and demonstrates how to modify numerical values displayed on a screen using buttons and a touch panel.  
🎓 This project was created as part of a university course.

## 🛠️ Hardware Requirements

- **FRDM-KL05Z microcontroller**
- Buttons connected to S2 and S4
- Capacitive touch panel
- Display compatible with FRDM-KL05Z

## 🗂️ Project Files

modify-values-lcd/  
├── frdm_bsp.h # Board support package header  
├── i2c.c / i2c.h # I2C communication handling  
├── klaw.c / klaw.h # Button (S2/S4) management with debouncing and interrupts  
├── lcd1602.c / lcd1602.h # LCD 1602 display driver  
├── main.c # Main program logic  
└── tsi.c / tsi.h # Touch Sensing Input (TSI) for capacitive panel

## ✨ Features

- **🎛️ Button Navigation (S2 and S4):**
  - Pressing S2 or S4 moves the cursor between fields.
  - The program uses **interrupt-based button handling** with **debouncing** to minimize false triggers due to contact bounce.
  - Each press moves the cursor by **one position**, regardless of how long the button is held.
  - The cursor **wraps around** when reaching the end (left or right).

- **📲 Value Modification via Touch Panel:**
  - The touch panel is divided into **10 equal regions**, representing digits **0 through 9**.
  - Touching closer to the **left side** selects a **lower digit**, and touching near the **right side** selects a **higher digit**.
  - The touched region sets the digit for the **currently selected field**.

## 🧑‍💻 How It Works

1. ▶️ **Start the program** – The display shows initial values with one field selected.
2. ⬅️➡️ **Navigate between fields** – Use S2/S4 buttons to choose the digit you want to edit.
3. 👆 **Change values** – Tap the appropriate section of the touch panel to update the digit.

![11](https://github.com/user-attachments/assets/39df3fa9-7823-4166-a332-896fc26c3838)
![22](https://github.com/user-attachments/assets/dedaf881-7d01-465a-8717-ec63f5288f5d)
