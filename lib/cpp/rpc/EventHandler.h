
#ifndef __RPC_EVENTHANDLER_H__
#define __RPC_EVENTHANDLER_H__

#include "RpcMessage.h"
#include "NetEvent.h"

namespace rpc {
class EventHandler{
 public:
    EventHandler(){}
    virtual ~EventHandler(){
        trans_=nullptr;
        proto_=nullptr;
        bev_=nullptr;
    }

    int init(Transport* trans,Protocol* proto,struct bufferevent *bev){
        trans_=trans;
        proto_=proto;
        bev_=bev;
    }

 protected:

	virtual void dispatch(const RpcMsg& m)=0;
    virtual int invoke(const RpcMsg* msg)=0;

    virtual int handleInput()=0;
    virtual int handleOutput()=0;
    virtual int handleClose()=0;

    Protocol* getProtocol(){return nullptr;}
    Transport* getTransport(){return nullptr;}

private:
    Transport*   trans_;
    Protocol*    proto_;
    struct bufferevent *bev_;

 protected:
    static void conn_eventcb(struct bufferevent *bev, short events, void *userData) {
        EventHandler* handler=(EventHandler*) userData;
         handler->handleClose();
    }

    static void conn_readcb(struct bufferevent *bev, void *userData) { 
        EventHandler* handler=(EventHandler*) userData;
         handler->handleInput();
    }

    static void conn_writecb(struct bufferevent *bev, void *userData) { 
        EventHandler* handler=(EventHandler*) userData;
         handler->handleOutput();
    }


};
}
#endif