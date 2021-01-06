#ifndef RPMSG_CHANNEL_HPP
#define RPMSG_CHANNEL_HPP

#include <pru_rpmsg.h>
#include <pru_intc.h>
#include <rsc_types.h>

#include "register_31.hpp"

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
        char            payload_[sizeof(TSharedStruct)];
        TSharedStruct   shared_struct_;
    };

} // namespace detail

/*
 * Bit number CHANNEL_PORT in register __R31 is used to signal an interrupt event
 */
template<typename TSharedStruct, uint8_t TO_ARM_HOST, uint8_t FROM_ARM_HOST, uint8_t CHANNEL_PORT>
class RPMsgChannel
{
public:
    typedef void(*Callback)(TSharedStruct&);

    RPMsgChannel(const char* channel_description, fw_rsc_vdev& rpmsg_vdev, fw_rsc_vdev_vring& rpmsg_vring0, fw_rsc_vdev_vring& rpmsg_vring1)
    {
        rp_msg_ = new detail::RPMsg<TSharedStruct>;

        /*
         * Clear the status of the PRU-ICSS system event that the ARM will
         * use to 'kick' us
         */
        CT_INTC.SICR_bit.STS_CLR_IDX = FROM_ARM_HOST;

        /* Make sure the Linux drivers are ready for RPMsg communication */
        volatile uint8_t* status = &rpmsg_vdev.status;
        while (!(*status & VIRTIO_CONFIG_S_DRIVER_OK)) {
            /* Optional: implement timeout logic */
        };

        /* Initialize the RPMsg transport structure */
        pru_rpmsg_init(&transport_, &rpmsg_vring0, &rpmsg_vring1, TO_ARM_HOST, FROM_ARM_HOST);

        /*
         * Create the RPMsg channel between the PRU and ARM user space using
         * the transport structure.
         */
        while (pru_rpmsg_channel(RPMSG_NS_CREATE, &transport_, const_cast<char*>(CHANNEL_NAME), const_cast<char*>(channel_description), CHANNEL_PORT)
                != PRU_RPMSG_SUCCESS) {
            /* Optional: implement timeout logic */
        };
    }

    ~RPMsgChannel()
    {
        delete rp_msg_;
    }

    // Blocking receive
    void tryHandleMessage(Callback callback)
    {
        /* Check register R31 bit CHANNEL_PORT to see if the ARM has kicked us */
        if (!(__R31 & static_cast<uint32_t>(1 << CHANNEL_PORT))) {
            return;
        }

        /* Clear the event status */
        CT_INTC.SICR_bit.STS_CLR_IDX = FROM_ARM_HOST;

        /*
         * Receive available messages.
         * Multiple messages can be sent per kick.
         */
        while (pru_rpmsg_receive(&transport_, &source_, &destination_, rp_msg_->payload_, &payload_length_)
                == PRU_RPMSG_SUCCESS) {

            callback(rp_msg_->shared_struct_);
            /*
             * Send reply message to the address that sent
             * the initial message
             */
            pru_rpmsg_send(&transport_, destination_, source_, rp_msg_->payload_, sizeof(TSharedStruct));
        }
    }
private:
    detail::RPMsg<TSharedStruct>*   rp_msg_;
    pru_rpmsg_transport             transport_;
    uint16_t                        source_;
    uint16_t                        destination_;
    uint16_t                        payload_length_;
};

} // namespace prucpp

#endif // RPMSG_CHANNEL_HPP
