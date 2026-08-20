#include "InerzaNetwork.h"

INetwork::INetwork(uint16_t port) : _port(port) {}

void INetwork::begin() {
    _udp.begin(_port);
}

void INetwork::subscribe(const String& topic, TopicCallback callback) {
    _subscriptions[topic] = callback;
}

void INetwork::publish(const String& topic, const String& payload, IPAddress targetIP) {
    _udp.beginPacket(targetIP, _port);
    String packet = topic + "|" + payload;
    _udp.write((const uint8_t*)packet.c_str(), packet.length());
    _udp.endPacket();
}

void INetwork::update() {
    int packetSize = _udp.parsePacket();
    if (packetSize) {
        char buffer[256];
        int len  = _udp.read(buffer, sizeof(buffer) - 1);
        if(len>0) {
            buffer[len] = '\0';
        }

        String msg = String(buffer);
        int separatorIndex = msg.indexOf('|');
        if (separatorIndex != -1) {
            String topic = msg.substring(0, separatorIndex);
            String payload = msg.substring(separatorIndex + 1);

            if(_subscriptions.count(topic) > 0) {
                _subscriptions[topic](topic, payload);
            }
        }
    }
}