#ifndef MENU_H
#define MENU_H

#include <vector>
#include "config.h"
#include "Input.h"
#include <TFT_eSPI.h>

extern TFT_eSPI tft;
extern Input input;

// Menu States
enum CurrentMenu {
    MAIN_MENU,
    WIFI_MENU,
    BT_MENU,
    ATTACK_MENU,
    SNIFF_MENU
};

struct MenuItem {
    String title;
    void (*action)(); // Callback function
};

class Menu {
public:
    void begin() {
        populateMenus();
        drawMenu();
    }

    void update() {
        if (input.isDownPressed()) {
            selectedIndex++;
            if (selectedIndex >= currentItems.size()) selectedIndex = 0;
            drawMenu();
        }
        if (input.isUpPressed()) {
            selectedIndex--;
            if (selectedIndex < 0) selectedIndex = currentItems.size() - 1;
            drawMenu();
        }
        if (input.isSelectPressed()) {
            executeItem();
        }
    }

    // Helper to switch menus
    void setMenu(CurrentMenu menu) {
        state = menu;
        populateMenus();
        selectedIndex = 0;
        drawMenu();
    }

    CurrentMenu getState() { return state; }

private:
    CurrentMenu state = MAIN_MENU;
    int selectedIndex = 0;
    std::vector<MenuItem> currentItems;

    void populateMenus();
    void executeItem();
    
    void drawMenu() {
        tft.fillScreen(TFT_BLACK);
        
        // Header
        tft.fillRect(0, 0, SCREEN_WIDTH, 40, 0x03AF); // Dark Blue Header (RGB565)
        tft.setTextColor(TFT_WHITE, 0x03AF);
        tft.setTextSize(2);
        
        String title = "TechBot4Code";
        if (state == WIFI_MENU) title = "WiFi Audits";
        else if (state == BT_MENU) title = "BT Audits";
        else if (state == ATTACK_MENU) title = "Pentest";
        else if (state == SNIFF_MENU) title = "Special Tools";
        
        // Center Title
        int titleWidth = title.length() * 12;
        tft.setCursor((SCREEN_WIDTH - titleWidth) / 2, 12);
        tft.print(title);
        
        // Status Bar (Top Line - Fake for now, but placeholder for "Cool")
        tft.setTextSize(1);
        tft.setCursor(5, 2);
        tft.print("CPU:240MHz");
        tft.setCursor(240, 2);
        tft.print("BAT:100%"); // Placeholder

        // Items
        tft.setTextSize(2);
        int startY = 50;
        int maxItemsPerScreen = 7;
        int startIdx = 0;
        
        // Simple scrolling logic if needed, but for now just fit on screen
        if(selectedIndex >= maxItemsPerScreen) startIdx = selectedIndex - maxItemsPerScreen + 1;
        
        for (int i = startIdx; i < currentItems.size() && i < startIdx + maxItemsPerScreen; i++) {
            int yPos = startY + ((i - startIdx) * 26);
            if (i == selectedIndex) {
                 // Highlight Bar
                 tft.fillRect(10, yPos - 2, 300, 24, TFT_WHITE);
                 tft.setTextColor(TFT_BLACK, TFT_WHITE);
                 tft.setCursor(15, yPos);
                 tft.print("> " + currentItems[i].title);
            } else {
                 tft.setTextColor(0xCE79, TFT_BLACK); // Light Grey
                 tft.setCursor(15, yPos);
                 tft.print("  " + currentItems[i].title);
            }
        }
    }
};

extern Menu menu;

#endif
