// Thêm bộ thư viện Nút nhấn.
// Add the Button library.
#include <MKL_OneButton.h>
#include "MKL_LiquidCrystal_I2C.h"
// Chọn chân Digital cho Nút nhấn.
// Select the Digital pin for Button.
#define BUTTON_PIN A3
// Khởi tạo "OneButton" cho Nút nhấn với cấu hình sau.
// Initialize "OneButton" for the Button with the following config.
MKL_OneButton btn = MKL_OneButton(
  BUTTON_PIN,  // Cấu hình đây là chân Digital Input.
  true,        // Nút nhấn kích hoạt LOW.
  false        // Kích hoạt điện trở nội "Pull-Up".
);
//Khởi tạo cho LCD
MKL_LiquidCrystal_I2C lcd(0x27, 16, 2);
// Lưu số lần thực hiện 1 Click vào nút.
// Save the number of times make 1 Click on the Button.
int value = 0;

void setup() {
  // Khởi động kết nối Serial UART ở tốc độ 9600 để truyền dữ liệu lên máy tính.
  // Start the Serial UART connection at 9600 to transfer data to the computer.
  Serial.begin(9600);
  //setup LCD
  lcd.init();
  lcd.backlight();
  lcd.setCursor(2, 0);
  lcd.print("Press Button");
  // Liên kết hàm "count" được gọi trên một sự kiện 1 Click.
  // Link the "count" function to be called on a single click event.
  btn.attachClick(count);
}

void loop() {
  // Tiếp tục theo dõi Nút nhấn.
  // Keep watching the Button.
  btn.tick();
}

void count() {
  // Ghi lại đây là 1 Click.
  // Record this is 1 Click.
  value++;
  //Xóa màn hình
  lcd.clear();
  //Chữ cái đầu tiên nằm ở hàng 1 cột 1 của LCD
  lcd.setCursor(0, 0);
  //In giá trị ra màn hình LCD
  lcd.print("Count: ");
  lcd.print(value);
}