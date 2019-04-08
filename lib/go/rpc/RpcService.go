package rpc

import (
	"bytes"
	"net"
)

type IRpcServiecFactroy interface {
	NewRpcService(event *NetEvent, ep endPoint, tcpConn *net.TCPConn) *RpcService
}
type RpcServiecFactroy struct {
	transFactory ITransportFactory
	protoFactory IProtocolFactory
}

func (this *RpcServiecFactroy) NewRpcService(event *NetEvent, ep endPoint, tcpConn *net.TCPConn) *RpcService {
	conn := NewConnection(event, ep, tcpConn, this.protoFactory.NewProtocol(), this.transFactory.NewTransport())
	return &RpcService{connection: conn, proxyMap: make(map[string]*ServiceProxy)}
}

type RpcService struct {
	*connection
	proxyMap map[string]*ServiceProxy
}

func (this *RpcService) handleInput(buff *bytes.Buffer) error {
	requestMsg, err := this.GetTransport().recvRequestMsg(buff)
	if err != nil {
		return nil
	}

	proxy, ok := this.proxyMap[requestMsg.serviceName]
	if ok {
	}
	return nil
}
