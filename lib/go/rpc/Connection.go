package rpc

import (
	"bytes"
	"encoding/binary"
	"io"
	"net"
	"sync"
)

type connection struct {
	proto    IProtocol
	trans    ITransport
	conn     *net.TCPConn
	sendCh   chan *bytes.Buffer
	IsValid  bool
	exitSync sync.WaitGroup
}

func NewConnection(event *NetEvent, ep endPoint, proto IProtocol, trans ITransport) *connection {
	return nil
}

func (this *connection) GetProtocol() IProtocol {
	return this.proto
}
func (this *connection) GetTransport() ITransport {
	return this.trans
}

func (this *connection) start() error {

	(*(this.conn)).SetNoDelay(true)
	(*(this.conn)).SetKeepAlive(true)

	//同步退出 goroutine
	this.exitSync.Add(2)

	//开启读写 goroutine
	go this.recvMsgLoop()
	go this.sendMsgLoop()

	return nil
}

func (this *connection) sendMsgLoop() {

	for msg := range this.sendCh {
		if msg == nil || this.conn == nil {
			break
		}

		buf := make([]byte, 2)
		_, err := this.conn.Write(buf)
		if err != nil {
			//关闭socket 从读操作退出
			this.shutDown()
			break
		}
	}
	this.exitSync.Done()
}

func (this *connection) recvMsgLoop() {
	var err error
	var msgLen int
	msgHeader := make([]byte, 2) //前2字节存msgLen
	for {
		_, err = io.ReadFull(this.conn, msgHeader)
		if err != nil {
			break
		}
		msgLen = int(binary.LittleEndian.Uint16(msgHeader))
		if msgLen <= 0 || msgLen > 65535 {
			break
		}

		msgBody := make([]byte, msgLen)
		_, err = io.ReadFull(this.conn, msgBody)
		if err != nil {
			break
		}

	}
	this.exitSync.Done()
}

func (this *connection) shutDown() {
	// 关闭连接
	if this.conn != nil {
		this.conn.Close()
		this.conn = nil
	}
}
