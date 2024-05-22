#pragma once

#ifdef USE_ADAFRUIT_ILI9341
#define Display_h
#include <Arduino.h>
#include <Adafruit_ILI9341.h>
#include <SPI.h>

class Display {
    private:
        Adafruit_ILI9341 tft;
    public:
        Display(int CS, int DC, int RST, int MOSI, int SCK, int MISO) : tft(CS, DC, MOSI, SCK, RST, MISO) {
        }
        void begin() {
            tft.begin();
        }
        void clear() {
            tft.fillScreen(ILI9341_BLACK);
        }
        void drawPixel(int16_t x, int16_t y, uint16_t color) {
            tft.drawPixel(x, y, color);
        }
        void drawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint16_t color) {
            tft.drawLine(x0, y0, x1, y1, color);
        }
        void drawRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color) {
            tft.drawRect(x, y, w, h, color);
        }
        void fillRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color) {
            tft.fillRect(x, y, w, h, color);
        }
        void drawCircle(int16_t x0, int16_t y0, int16_t r, uint16_t color) {
            tft.drawCircle(x0, y0, r, color);
        }
        void fillCircle(int16_t x0, int16_t y0, int16_t r, uint16_t color) {
            tft.fillCircle(x0, y0, r, color);
        }
        void drawTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t color) {
            tft.drawTriangle(x0, y0, x1, y1, x2, y2, color);
        }
        void fillTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t color) {
            tft.fillTriangle(x0, y0, x1, y1, x2, y2, color);
        }
        void drawRoundRect(int16_t x, int16_t y, int16_t w, int16_t h, int16_t r, uint16_t color) {
            tft.drawRoundRect(x, y, w, h, r, color);
        }
        void fillRoundRect(int16_t x, int16_t y, int16_t w, int16_t h, int16_t r, uint16_t color) {
            tft.fillRoundRect(x, y, w, h, r, color);
        }
        void drawBitmap(int16_t x, int16_t y, uint8_t *bitmap, int16_t w, int16_t h) {
            tft.drawBitmap(x,y,bitmap,w,h,ILI9341_WHITE);
        }
        void drawChar(int16_t x, int16_t y, unsigned char c, uint16_t color, uint16_t bg, uint8_t size) {
            tft.drawChar(x, y, c, color, bg, size);
        }
        void setCursor(int16_t x, int16_t y) {
            tft.setCursor(x, y);
        }
        void setTextColor(uint16_t color) {
            tft.setTextColor(color);
        }
        void setTextColor(uint16_t color, uint16_t bg) {
            tft.setTextColor(color, bg);
        }
        void setTextSize(uint8_t size) {
            tft.setTextSize(size);
        }
        void setTextWrap(boolean wrap) {
            tft.setTextWrap(wrap);
        }
        void print(const char* str) {
            tft.print(str);
        }
        void println(const char* str) {
            tft.println(str);
        }
        void print(int num) {
            tft.print(num);
        }
        void println(int num) {
            tft.println(num);
        }
        void print(float num) {
            tft.print(num);
        }
        void println(float num) {
            tft.println(num);
        }
        void print(double num) {
            tft.print(num);
        }
    };
#endif

#ifdef USE_TFT_eSPI
#define Display_h
#include <TFT_eSPI.h>
#include <SPI.h>

class Display {
    private:
        TFT_eSPI tft;
    public:
        Display(int CS, int DC, int RST) : tft(TFT_eSPI()) {
        }
        void begin() {
            tft.begin();
        }
        void clear() {
            tft.fillScreen(TFT_BLACK);
        }
        void drawPixel(int16_t x, int16_t y, uint16_t color) {
            tft.drawPixel(x, y, color);
        }
        void drawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint16_t color) {
            tft.drawLine(x0, y0, x1, y1, color);
        }
        void drawRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color) {
            tft.drawRect(x, y, w, h, color);
        }
        void fillRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color) {
            tft.fillRect(x, y, w, h, color);
        }
        void drawCircle(int16_t x0, int16_t y0, int16_t r, uint16_t color) {
            tft.drawCircle(x0, y0, r, color);
        }
        void fillCircle(int16_t x0, int16_t y0, int16_t r, uint16_t color) {
            tft.fillCircle(x0, y0, r, color);
        }
        void drawTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t color) {
            tft.drawTriangle(x0, y0, x1, y1, x2, y2, color);
        }
        void fillTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t color) {
            tft.fillTriangle(x0, y0, x1, y1, x2, y2, color);
        }
        void drawRoundRect(int16_t x, int16_t y, int16_t w, int16_t h, int16_t r, uint16_t color) {
            tft.drawRoundRect(x, y, w, h, r, color);
        }
}
#endif

#ifdef USE_DMA_TFT_eSPI
#define Display_h
#include <TFT_eSPI.h>
#include <SPI.h>

class Display {
    private:
        TFT_eSPI tft;
    public:
        Display(int CS, int DC, int RST) : tft(TFT_eSPI()) {
        }
        void begin() {
            tft.begin();
        }
        void clear() {
            tft.fillScreen(TFT_BLACK);
        }
        void drawPixel(int16_t x, int16_t y, uint16_t color) {
            tft.drawPixel(x, y, color);
        }
        void drawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint16_t color) {
            tft.drawLine(x0, y0, x1, y1, color);
        }
        void drawRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color) {
            tft.drawRect(x, y, w, h, color);
        }
        void fillRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color) {
            tft.fillRect(x, y, w, h, color);
        }
        void drawCircle(int16_t x0, int16_t y0, int16_t r, uint16_t color) {
            tft.drawCircle(x0, y0, r, color);
        }
        void fillCircle(int16_t x0, int16_t y0, int16_t r, uint16_t color) {
            tft.fillCircle(x0, y0, r, color);
        }
        void drawTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t color) {
            tft.drawTriangle(x0, y0, x1, y1, x2, y2, color);
        }
        void fillTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t color) {
            tft.fillTriangle(x0, y0, x1, y1, x2, y2, color);
        }
        void drawRoundRect(int16_t x, int16_t y, int16_t w, int16_t h, int16_t r, uint16_t color) {
            tft.drawRoundRect(x, y, w, h, r, color);
        }   
}
#endif

#ifdef USE_ADAFRUIT_ILI9341_BUFFERED
#define Display_h
#include <Arduino.h>
#include <Adafruit_ILI9341.h>
#include <SPI.h>

class Display {
    private:
        Adafruit_ILI9341 tft;
        uint8_t* buffer;
        uint8_t* oldBuffer;
    public:
        Display(int CS, int DC, int RST, int MOSI, int SCK, int MISO) : tft(CS, DC, MOSI, SCK, RST, MISO) {
            buffer = new uint8_t[320 * 240];
            oldBuffer = new uint8_t[320 * 240];
        }
        void pushBuffer() {
            for (int i = 0; i < 320 * 240; i++) {
                if (buffer[i] != oldBuffer[i]) {
                    int x = i % 320;
                    int y = i / 320;
                    tft.drawPixel(x, y, buffer[i]);
                    oldBuffer[i] = buffer[i];
                }
            }
            for (int i = 0; i < 320 * 240; i++) {
                buffer[i] = 0;
            }
        }
        void begin() {
            tft.begin();
        }
        void drawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint8_t color) {

        }

};
#endif

#ifndef Display_h
#define Display_h
#include <Arduino.h>
#include <Adafruit_ILI9341.h>
#include <SPI.h>

class Display {
    private:
        Adafruit_ILI9341 tft;
    public:
        Display(int CS, int DC, int RST, int MOSI, int SCK, int MISO) : tft(CS, DC, MOSI, SCK, RST, MISO) {
        }
        void begin() {
            tft.begin();
        }
        void clear() {
            tft.fillScreen(ILI9341_BLACK);
        }
        void drawPixel(int16_t x, int16_t y, uint16_t color) {
            tft.drawPixel(x, y, color);
        }
        void drawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint16_t color) {
            tft.drawLine(x0, y0, x1, y1, color);
        }
        void drawRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color) {
            tft.drawRect(x, y, w, h, color);
        }
        void fillRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color) {
            tft.fillRect(x, y, w, h, color);
        }
        void drawCircle(int16_t x0, int16_t y0, int16_t r, uint16_t color) {
            tft.drawCircle(x0, y0, r, color);
        }
        void fillCircle(int16_t x0, int16_t y0, int16_t r, uint16_t color) {
            tft.fillCircle(x0, y0, r, color);
        }
        void drawTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t color) {
            tft.drawTriangle(x0, y0, x1, y1, x2, y2, color);
        }
        void fillTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t color) {
            tft.fillTriangle(x0, y0, x1, y1, x2, y2, color);
        }
        void drawRoundRect(int16_t x, int16_t y, int16_t w, int16_t h, int16_t r, uint16_t color) {
            tft.drawRoundRect(x, y, w, h, r, color);
        }
        void fillRoundRect(int16_t x, int16_t y, int16_t w, int16_t h, int16_t r, uint16_t color) {
            tft.fillRoundRect(x, y, w, h, r, color);
        }
        void drawBitmap(int16_t x, int16_t y, uint8_t *bitmap, int16_t w, int16_t h) {
            tft.drawBitmap(x,y,bitmap,w,h,ILI9341_WHITE);
        }
        void drawChar(int16_t x, int16_t y, unsigned char c, uint16_t color, uint16_t bg, uint8_t size) {
            tft.drawChar(x, y, c, color, bg, size);
        }
        void setCursor(int16_t x, int16_t y) {
            tft.setCursor(x, y);
        }
        void setTextColor(uint16_t color) {
            tft.setTextColor(color);
        }
        void setTextColor(uint16_t color, uint16_t bg) {
            tft.setTextColor(color, bg);
        }
        void setTextSize(uint8_t size) {
            tft.setTextSize(size);
        }
        void setTextWrap(boolean wrap) {
            tft.setTextWrap(wrap);
        }
        void print(const char* str) {
            tft.print(str);
        }
        void println(const char* str) {
            tft.println(str);
        }
        void print(int num) {
            tft.print(num);
        }
        void println(int num) {
            tft.println(num);
        }
        void print(float num) {
            tft.print(num);
        }
        void println(float num) {
            tft.println(num);
        }
        void print(double num) {
            tft.print(num);
        }
    };
#endif