// Почитать про TLV. Преимущества TLV перед нуль-терминацией? Недостатки? Написать поточный десериализатор TLV данных, 
// class Deserializer { ... public: std::optional<std::vector<char» feed(char* bytes, int len) }

// Type-length-value
// Преимущества:
// Преимущества LTV в том, что можно легко добавить новый тип передаваемых данных используя код типа(тега) 
// Не нужно следить за '/0' и легко внести в код обработку нового кода типа(тега)
// Легко найти нужный код типа(тег) за O(n) в массиве байтов
// Всегда знаем какой размер данных типа(тега) нужно читать
// Бинарный формат. Можно упаковать в маленький размер за счет выравнивания полей и битовы полей.

// Недостатки:
// Если не соблюдать формат можно прочитать мусор или данные другого тега
// Нужно следить за обработкой тегов


#include <iostream>
#include <vector>
#include <optional>
#include <string_view>
#include <cstdint>
#include <array>
#include <type_traits>
#include <memory>
#include <cstring>
#include <iomanip>

static constexpr std::size_t kSizeBuffer = 12;

#pragma pack(push, 1)
struct IpClient {
    unsigned char ip[4];
    std::uint16_t port;
};
#pragma pack(pop)

#pragma pack(push, 1)
struct MacHeader {
    unsigned char dest[6];
    unsigned char source[6];
    std::uint16_t ether_type;
};
#pragma pack(pop)

#pragma pack(push, 1)
struct EthernetFrame {
    MacHeader mac_header;
    IpClient ip_client;
    unsigned char payload[kSizeBuffer];
};
#pragma pack(pop)

enum class TypeMessage : std::uint16_t {
    EthernetFrame   = 0xA,
    IpClient        = 0xB,
    MacHeader       = 0xC,
    Buffer          = 0xD,
    Unknown         = 0xF,
};

template <std::size_t N>
struct Message {
    TypeMessage type;
    std::uint16_t length;
    unsigned char buffer[N];
};

void PrintHex(const std::vector<unsigned char>& buffer);

class Tlv {
public: 
    Tlv() = delete;

    template <typename T>
    static auto prepare_tlv_message(T& obj) {
        TypeMessage type_message = TypeMessage::Unknown;

        if constexpr (std::is_same_v<MacHeader, T>) {
            type_message = TypeMessage::MacHeader;
            constexpr std::size_t size_obj = sizeof(obj);
            return CreateMessage<T, size_obj>(obj, type_message);
        } 
        else if constexpr (std::is_same_v<IpClient, T>) {
            type_message = TypeMessage::IpClient;
            constexpr std::size_t size_obj = sizeof(obj);
            return CreateMessage<T, size_obj>(obj, type_message);
        }
        else if constexpr (std::is_same_v<unsigned char, unsigned char>) {
            type_message = TypeMessage::Buffer;
            constexpr std::size_t size_obj = sizeof(obj);
            return CreateMessage<T, size_obj>(obj, type_message);
        }
    }
private:
    template <typename T, std::size_t N>
    static Message<N> CreateMessage(const T& obj, TypeMessage type) {
        Message<N> msg;
        msg.type = type;
        msg.length = static_cast<std::uint16_t>(N);
        
        std::memcpy(msg.buffer, &obj, N);
        return msg;
    }
};

class Serializer {
public:
    Serializer() = default;

    template <typename T>
    void serialize(T& obj_serialized) {
            auto tlv_msg = Tlv::prepare_tlv_message(obj_serialized);
            
            buffers_.push_back(HighByte(static_cast<std::uint16_t>(tlv_msg.type)));
            buffers_.push_back(LowByte(static_cast<std::uint16_t>(tlv_msg.type)));
            
            buffers_.push_back(HighByte(static_cast<std::uint16_t>(tlv_msg.length)));
            buffers_.push_back(LowByte(static_cast<std::uint16_t>(tlv_msg.length)));

            add_raw_data_buffer(buffers_, tlv_msg.buffer, sizeof(tlv_msg.buffer));
        }
    
    const std::vector<unsigned char>& get_buffer() const {
        return buffers_;
    }
    
    std::vector<unsigned char>& get_buffer() {
        return buffers_;
    }

private:
    std::vector<unsigned char> buffers_;
    
    std::uint8_t LowByte(std::uint16_t num) {
        return num & 0xFF;
    }

    std::uint8_t HighByte(std::uint16_t num) {
        return (num >> 8) & 0xFF;
    }

    void add_raw_data_buffer(std::vector<unsigned char>& buffer, unsigned char* payload, std::size_t len) {
        for (std::size_t i = 0; i < len; ++i) {
            buffer.push_back(payload[i]);
        }
    }
};

class Deserializer {
public:
    Deserializer() = delete;
    static EthernetFrame feed(unsigned char* bytes, int len) {
        std::uint16_t type = 0;
        std::uint16_t length = 0;
        std::size_t idx = 0;
        
        EthernetFrame eth_frame;

        while (idx < static_cast<std::size_t>(len)) {
            for (std::size_t i = idx; i < idx + 2; ++i) {
                type |= bytes[i];
            }
            idx += 2;

            for (std::size_t i = idx; i < idx + 2; ++i) {
                length |= bytes[i];
            }
            idx += 2;

            switch (static_cast<TypeMessage>(type)) {
                case TypeMessage::MacHeader:
                    eth_frame.mac_header = make_mac_header(&bytes[idx], length);
                    idx += length;
                    break;
                case TypeMessage::IpClient:
                    eth_frame.ip_client = make_ip_client(&bytes[idx], length);
                    idx += length;
                    break;
                case TypeMessage::Buffer:
                    std::memcpy(eth_frame.payload, &bytes[idx], length);
                    idx += length;
                    break;
                case TypeMessage::Unknown:
                    break;
                case TypeMessage::EthernetFrame:
                    break;
            }
            length = 0;
            type = 0;
        }
        return eth_frame;
    }
private:
    static MacHeader make_mac_header(unsigned char* bytes, int len) {
        MacHeader mac; 
        std::memcpy(&mac, bytes, len);
        return mac;
    }

    static IpClient make_ip_client(unsigned char* bytes, int len) {
        IpClient ip;
        std::memcpy(&ip, bytes, len);
        return ip;
    }
};

void PrintEthFrame(const EthernetFrame& frame) {
    std::cout << "Print ethernet frame" << '\n';
    std::cout << std::setw(10) << "Mac header: " << '\n';
    std::cout << std::setw(4) << "dest mac: ";

    auto& dest_mac = frame.mac_header.dest;
    for (std::size_t i = 0; i < sizeof(dest_mac); ++i) {
        std::cout << std::hex << std::showbase << static_cast<unsigned>(dest_mac[i]) << ' '; 
    }

    std::cout << '\n';
    std::cout << std::setw(4) << "source mac: ";

    auto& source_mac = frame.mac_header.source;
    for (std::size_t i = 0; i < sizeof(source_mac); ++i) {
        std::cout << std::hex << std::showbase << static_cast<unsigned>(source_mac[i]) << ' ';
    }

    std::cout << '\n' << std::setw(4) << "ether type: " 
        << std::hex << std::showbase << frame.mac_header.ether_type << '\n';

    std::cout << std::setw(4) << "Ip client: " << '\n';
    std::cout << std::setw(4) << "ip: ";
    
    auto& ip = frame.ip_client.ip;
    for (std::size_t i = 0; i < sizeof(ip); ++i) {
        std::cout << std::dec << static_cast<unsigned>(ip[i]) << ' ';
    }

    std::cout << '\n';
    std::cout << std::setw(4) << "port: " << frame.ip_client.port << '\n';
    std::cout << "buffer: ";

    auto& buffer = frame.payload;
    for (std::size_t i = 0; i < sizeof(buffer); ++i) {
        std::cout << std::hex << std::showbase << static_cast<unsigned>(buffer[i]) << ' ';
    }

    std::cout << '\n';
}

int main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[]) {
    // hello world = 68 65 6C 6C 6F 20 77 6F 72 6C 64 21
    EthernetFrame eth_frame{
        .mac_header = {
            .dest = {0x10, 0xFF, 0xE0, 0xC5, 0x29, 0xA9},
            .source = {0x32, 0x91, 0xF3, 0x35, 0x64, 0x2A},
            .ether_type = 0x0800
        },
        .ip_client = {
            .ip = {192, 168, 0, 1},
            .port = 8000
        },
        .payload = {0x68, 0x65, 0x6C, 0x6C, 0x6F, 0x20, 0x77, 0x6F, 0x72, 0x6C, 0x64, 0x21}
    };

    std::cout << "Before seriliazation EthernetFrame struct to TLV format.";
    PrintEthFrame(eth_frame);
    std::cout << '\n';

    Serializer serializer;
    serializer.serialize(eth_frame.mac_header);
    serializer.serialize(eth_frame.ip_client);
    serializer.serialize(eth_frame.payload);

    auto& res_serialize = serializer.get_buffer();
    PrintHex(res_serialize);
    std::cout << '\n';

    auto frame_des = Deserializer::feed(res_serialize.data(), res_serialize.size());

    std::cout << "Deserializating struct EthernetFrame from TLV format. ";
    PrintEthFrame(frame_des);

    return EXIT_SUCCESS;
}

void PrintHex(const std::vector<unsigned char>& buffer) {
    std::cout << "Ethernet frame encode to binary: ";
    for (const auto& el : buffer) {
        std::cout << std::hex << std::showbase << static_cast<unsigned>(el) << ' ';
    }
    std::cout << '\n';
}