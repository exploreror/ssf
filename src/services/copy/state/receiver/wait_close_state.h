#ifndef SSF_SERVICES_COPY_STATE_RECEIVER_WAIT_CLOSE_STATE_H_
#define SSF_SERVICES_COPY_STATE_RECEIVER_WAIT_CLOSE_STATE_H_

#include <ssf/log/log.h>

#include "common/error/error.h"

#include "services/copy/i_copy_state.h"

namespace ssf {
namespace services {
namespace copy {

class WaitCloseState : ICopyState {
 public:
  template <typename... Args>
  static ICopyStateUPtr Create(Args&&... args) {
    return ICopyStateUPtr(new WaitCloseState(std::forward<Args>(args)...));
  }

 public:
  // ICopyState
  void Enter(CopyContext* context, boost::system::error_code& ec) override {
    SSF_LOG("microservice", trace, "[copy][wait_close] enter");
  }

  bool FillOutboundPacket(CopyContext* context, Packet* packet,
                          boost::system::error_code& ec) override {
    return false;
  }
  void ProcessInboundPacket(CopyContext* context, const Packet& packet,
                            boost::system::error_code& ec) override {
    if (packet.type() == PacketType::kAbort) {
      return OnReceiverAbortPacket(context, packet, ec);
    }

    // noop
  }

  bool IsClosed(CopyContext* context) override { return false; }

  bool IsTerminal(CopyContext* context) override { return true; }
};

}  // copy
}  // services
}  // ssf

#endif  // SSF_SERVICES_COPY_STATE_RECEIVER_WAIT_CLOSE_STATE_H_
