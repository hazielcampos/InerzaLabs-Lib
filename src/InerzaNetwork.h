#ifndef INERZA_NETWORK_H
#define INERZA_NETWORK_H

#include <Arduino.h>
#include <WiFi.h>
#include <WiFiUdp.h>
#include <map>
#include <functional>

using TopicCallback = std::function<void(const String& topic, const String& payload)>;

class INetwork {
    private:
        WiFiUDP _udp;
        uint16_t _port;
        std::map<String, TopicCallback> _subscriptions;
    public:
        INetwork(uint16_t port=8888);
        void begin();
        void subscribe(const String& topic, TopicCallback callback);
        void publish(const String& topic, const String& payload, IPAddress targetIP);
        void update();
};

#endif