#ifndef COMMON_HPP
#define COMMON_HPP

#include <QByteArray>

namespace CHECKSUM
{
    quint32 crc32(const QByteArray &data);
}

#endif // COMMON_HPP
