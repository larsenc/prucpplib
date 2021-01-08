#ifndef PRU0_RPMSG_CHANNEL_H
#define PRU0_RPMSG_CHANNEL_H

#include <rsc_types.h>

#include "rpmsg_channel.hpp"

namespace prucpp {

// These could be moved to pru0_resource_table.h
#define PRU0_TO_ARM_HOST    16
#define PRU0_FROM_ARM_HOST  17
#define PRU0_CHANNEL_PORT   30
#define PRU0_DESCRIPTION    "Channel 30"

template <typename TSharedStruct>
struct PRU0RPMsgChannel : RPMsgChannel<TSharedStruct, PRU0_TO_ARM_HOST, PRU0_FROM_ARM_HOST, PRU0_CHANNEL_PORT>
{
    PRU0RPMsgChannel(fw_rsc_vdev& rpmsg_vdev, fw_rsc_vdev_vring& rpmsg_vring0, fw_rsc_vdev_vring& rpmsg_vring1)
        : RPMsgChannel<TSharedStruct, PRU0_TO_ARM_HOST, PRU0_FROM_ARM_HOST, PRU0_CHANNEL_PORT>(
                PRU0_DESCRIPTION,
                rpmsg_vdev,
                rpmsg_vring0,
                rpmsg_vring1)
    {}
};

} // namespace prucpp

#endif // PRU0_RPMSG_CHANNEL_H
