#ifndef FFTEL_PKT_H
#define FFTEL_PKT_H

#include <cstdint>
#include <cstring>

// TODO: made another library to handle byteorder without using fftel_pkt
namespace byteorder {

    // (n)etwork (to) (h)ost (l)ong
    inline uint32_t ntohl(uint32_t t_val)
    {
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
        return __builtin_bswap32(t_val);
#elif __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
        return t_val;
#endif
    }

    constexpr auto htonl = ntohl; // (h)ost (to) (n)etwork (l)ong
    constexpr auto ctohl = ntohl; // (c)an-bus (to) (h)ost (l)ong
    constexpr auto htocl = ntohl; // (h)ost (to) (c)an-bus (l)ong

    inline uint16_t ntohs(uint16_t t_val)
    {
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
        return __builtin_bswap16(t_val);
#elif __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
        return t_val;
#endif
    }

    constexpr auto htons = ntohs; // (h)ost (to) (n)etwork (s)hort
    constexpr auto ctohs = ntohs; // (c)an-bus (to) (h)ost (s)hort
    constexpr auto htocs = ntohs; // (h)ost (to) (c)an-bus (s)hort
}

class fftel_pkt
{
public:
    enum fftel_pkt_type: uint8_t {hz3, hz25};

    fftel_pkt(fftel_pkt_type t_type) {m_pkt_header.pkt_type = t_type;};


    struct __attribute__((packed)) pkt_header {
        explicit pkt_header(): pkt_type(hz3), seq_num(0) {
            std::memset(hmac, 0, 32);
        }

        fftel_pkt_type  pkt_type;
        uint32_t seq_num;
        uint8_t hmac[32];
    };

    void set_pkt_type(const fftel_pkt_type t_type);
    void encapsulate(uint8_t t_seq_num, const uint8_t *t_src, uint16_t t_src_len, uint8_t * t_dest, uint16_t t_dest_len);



private:
    fftel_pkt();

    pkt_header m_pkt_header{};
};

#endif // FFTEL_PKT_H
