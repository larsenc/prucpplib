#ifndef PRU1_RPMSG_CHANNEL_H
#define PRU1_RPMSG_CHANNEL_H

#include "prucpplib/rpmsg/rpmsg_channel.hpp"

#include <rsc_types.h>

namespace prucpp {

// These could be moved to pru1_resource_table.h
#define PRU1_TO_ARM_HOST    18
#define PRU1_FROM_ARM_HOST  19
#define PRU1_CHANNEL_PORT   31
#define PRU1_DESCRIPTION    "Channel 31"

template <typename TSharedStruct>
struct PRU1RPMsgChannel : RPMsgChannel<TSharedStruct, PRU1_TO_ARM_HOST, PRU1_FROM_ARM_HOST, PRU1_CHANNEL_PORT>
{
    PRU1RPMsgChannel(fw_rsc_vdev& rpmsg_vdev, fw_rsc_vdev_vring& rpmsg_vring0, fw_rsc_vdev_vring& rpmsg_vring1)
        : RPMsgChannel<TSharedStruct, PRU1_TO_ARM_HOST, PRU1_FROM_ARM_HOST, PRU1_CHANNEL_PORT>(
                PRU1_DESCRIPTION,
                rpmsg_vdev,
                rpmsg_vring0,
                rpmsg_vring1)
    {}
};

} // namespace prucpp

#endif // PRU1_RPMSG_CHANNEL_H
