#ifndef	__HELLOMSG_H__
#define	__HELLOMSG_H__

#include <functional>
#include "rpc/Common.h"
#include "rpc/Protocol.h"
#include "rpc/ClientStub.h"
#include "rpc/ServiceProxy.h"
namespace shuai{

enum SexType
{ 
	male,
	famale,
}; 
extern rpc::EnumMap RpcEnum(SexType);

class role
{ 
public: 
	role();
	virtual ~role();
	static const char* strFingerprint;
	SexType	sexType;
	bool	b;
	rpc::int8	i8;
	rpc::uint8	ui8;
	rpc::int16	i16;
	rpc::uint16	ui16;
	rpc::int32	i32;
	rpc::uint32	ui32;
	rpc::int64	i64;
	std::string	str;

	//serialize
	void serialize(rpc::IProtocol* __P__); 

	//deSerialize
	bool deSerialize(rpc::IProtocol* __P__);
} ;//struct

class user
{ 
public: 
	user();
	virtual ~user();
	static const char* strFingerprint;
	std::map<rpc::int32,role>	roleMap;
	std::vector<rpc::int32> 	items;
	std::vector<role> 	roles;

	//serialize
	void serialize(rpc::IProtocol* __P__); 

	//deSerialize
	bool deSerialize(rpc::IProtocol* __P__);
} ;//struct

class opServiceStub: public rpc::ClientStub
{ 
public: 
	static const char* strFingerprint;
	enum {
		momo_Id,
		xixi_Id,
		lala_Id,
		ping_Id,
	};
	opServiceStub(){}
	virtual ~opServiceStub(){}
	void invokeAsync(const rpc::IProtocol* p);
	virtual bool dispatch(std::shared_ptr<rpc::RpcMsg> msg);
	void momo(rpc::int8  i8,rpc::int64  i64);
	void xixi(user&  u,std::function<int(rpc::int8)> cb);
	void lala(std::map<rpc::int32,role>&  m,std::vector<rpc::int32> &  ai,std::vector<role> &  ar,std::function<int(std::vector<role> )> cb);
	void ping(std::function<int(rpc::int8)> cb);

protected:
	std::function<int(rpc::int8)> xixiCallBack;
	std::function<int(std::vector<role> )> lalaCallBack;
	std::function<int(rpc::int8)> pingCallBack;
};//class

class opServiceProxyIF: public rpc::ServiceProxy 
{ 
public: 
	static const char* strFingerprint;
	opServiceProxyIF(){}
	virtual ~opServiceProxyIF(){}
	virtual std::tuple<int>momo(rpc::int8  i8,rpc::int64  i64)=0;
	virtual std::tuple<int,rpc::int8>xixi(user&  u)=0;
	virtual std::tuple<int,std::vector<role> >lala(std::map<rpc::int32,role>&  m,std::vector<rpc::int32> &  ai,std::vector<role> &  ar)=0;
	virtual std::tuple<int,rpc::int8>ping()=0;
	virtual bool dispatch(std::shared_ptr<rpc::RpcMsg> msg);

};//class

}///namespace
#endif
