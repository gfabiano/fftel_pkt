#include "fftel_pkt.h"
#include <hmac_sha256.h>

fftel_pkt::fftel_pkt(){}

void fftel_pkt::set_pkt_type(const fftel_pkt_type t_type)
{
    m_pkt_header.pkt_type = t_type;
}



void fftel_pkt::encapsulate(uint8_t t_seq_num, const uint8_t *t_src, uint16_t t_src_len, uint8_t *t_dest, uint16_t t_dest_len)
{
    if (t_src_len + sizeof (m_pkt_header) > t_dest_len) {
        goto restore;
    }

    m_pkt_header.seq_num = t_seq_num;

    hmac_sha256(
        "abcd",
        4,
        t_src,
        t_src_len,
        m_pkt_header.hmac,
        sizeof(m_pkt_header.hmac)
    );

    std::memcpy(
        t_dest,
        &m_pkt_header,
        sizeof(pkt_header)
    );

restore:
    return;
}
