#ifndef RPMSG_CHANNEL_HPP
#define RPMSG_CHANNEL_HPP

#include "prucpplib/register_31.hpp"

#include <pru_intc.h>
#include <pru_rpmsg.h>
#include <rsc_types.h>

namespace prucpp {

/*
 * Used to make sure the Linux drivers are ready for RPMsg communication
 * Found at linux-x.y.z/include/uapi/linux/virtio_config.h
 */
#define VIRTIO_CONFIG_S_DRIVER_OK   4

#define CHANNEL_NAME "rpmsg-pru"

namespace detail {

    template<typename TSharedStruct>
    union RPMsg
    {
        char            payload[sizeof(TSharedStruct)];
        TSharedStruct   sharedStruct;
    };

} // namespace detail

/*
 * Bit number CHANNEL_PORT in register __R31 is used to signal an interrupt event
 */
template<typename TSharedStruct, uint8_t TO_ARM_HOST, uint8_t FROM_ARM_HOST, uint8_t CHANNEL_PORT>
class RPMsgChannel
{
public:
    typedef void(*OnMsgReceived)(TSharedStruct&);

    RPMsgChannel(const char* channelDescription, fw_rsc_vdev& rpmsg_vdev, fw_rsc_vdev_vring& rpmsg_vring0, fw_rsc_vdev_vring& rpmsg_vring1)
        : mRPMsg(new detail::RPMsg<TSharedStruct>)
    {
        clearEventStatus();

        // Make sure the Linux drivers are ready for RPMsg communication
        volatile uint8_t* status = &rpmsg_vdev.status;
        while (!(*status & VIRTIO_CONFIG_S_DRIVER_OK)) {};

        // Initialize the RPMsg transport
        pru_rpmsg_init(&mTransport, &rpmsg_vring0, &rpmsg_vring1, TO_ARM_HOST, FROM_ARM_HOST);

        // Create the RPMsg channel between the PRU and ARM user space using the transport structure.
        while (pru_rpmsg_channel(RPMSG_NS_CREATE, &mTransport, const_cast<char*>(CHANNEL_NAME), const_cast<char*>(channelDescription), CHANNEL_PORT) != PRU_RPMSG_SUCCESS) {};
    }

    ~RPMsgChannel()
    {
        delete mRPMsg;
    }

    /*
     * Try and handle the most recent message in the queue
     *
     * Returns false if no message has been received
     */
    bool tryHandleMessage(OnMsgReceived onMsgReceived)
    {
        // Check bit CHANNEL_PORT in register R31 to see if ARM has kicked us
        if (!(__R31 & static_cast<uint32_t>(1 << CHANNEL_PORT))) {
            return false;
        }

        clearEventStatus();

        // Receive available messages.
        // The latest message in the queue will be passed to the callback function onMsgReceived
        uint16_t source, destination, payloadLength;
        while (pru_rpmsg_receive(&mTransport, &source, &destination, mRPMsg->payload, &payloadLength) == PRU_RPMSG_SUCCESS) {

            onMsgReceived(mRPMsg->sharedStruct);

            // Replay to the same destination
            pru_rpmsg_send(&mTransport, destination, source, mRPMsg->payload, sizeof(TSharedStruct));
            return true;
        }

        return false;
    }

private:
    /*
     * Clear the status of the PRU-ICSS system event that the ARM will use to 'kick' us
     */
    void clearEventStatus()
    {
        // Clear the event status
        CT_INTC.SICR_bit.STS_CLR_IDX = FROM_ARM_HOST;
    }

    detail::RPMsg<TSharedStruct>*   mRPMsg;
    pru_rpmsg_transport             mTransport;
};

} // namespace prucpp

#endif // RPMSG_CHANNEL_HPP
