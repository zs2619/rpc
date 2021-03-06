#ifndef	__HELLOMSG_H__
#define	__HELLOMSG_H__

#include <functional>
#include "rpc/Common.h"
#include "rpc/Protocol.h"
#include "rpc/ServiceStub.h"
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
	rpc::byte	by;
	rpc::int8	i8;
	rpc::int16	i16;
	rpc::int32	i32;
	rpc::int64	i64;
	float	f;
	std::string	str;
	std::vector<byte>	bin;

	//serialize
	void serialize(rpc::IProtocol* __P__) const ;

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
	void serialize(rpc::IProtocol* __P__) const ;

	//deSerialize
	bool deSerialize(rpc::IProtocol* __P__);
} ;//struct

class opServiceStub: public rpc::ServiceStub
{ 
public: 
	static const char* strFingerprint;
	static const char* getObjName;
	enum {
		login_Id,
		xixi_Id,
		lala_Id,
		ping_Id,
	};
	opServiceStub(const rpc::Connection* conn):ServiceStub(conn){}
	virtual ~opServiceStub(){}
	int invokeAsync(rpc::int16 msgId,const rpc::IProtocol* p,const std::string& functionName);
	virtual bool dispatch(std::shared_ptr<rpc::RpcMsg> msg);
	int login(const std::string&  openid,std::function<int(rpc::int8)> cb);
	int xixi(user&  u,std::function<int(user)> cb);
	int lala(std::map<rpc::int32,role>&  m,std::vector<rpc::int32> &  ai,std::vector<role> &  ar,std::function<int(std::vector<role> )> cb);
	int ping(rpc::int8  i8,std::function<int(rpc::int8)> cb);

protected:
	std::function<int(rpc::int8)> loginCallBack;
	std::function<int(user)> xixiCallBack;
	std::function<int(std::vector<role> )> lalaCallBack;
	std::function<int(rpc::int8)> pingCallBack;
};//class

class opServiceProxyIF: public rpc::ServiceProxy 
{ 
public: 
	static const char* strFingerprint;
	static const char* getObjName;
	opServiceProxyIF(const rpc::Connection* conn):ServiceProxy(conn){}
	virtual ~opServiceProxyIF(){}
	virtual std::tuple<int,rpc::int8>login(const std::string&  openid)=0;
	virtual std::tuple<int,user>xixi(user&  u)=0;
	virtual std::tuple<int,std::vector<role> >lala(std::map<rpc::int32,role>&  m,std::vector<rpc::int32> &  ai,std::vector<role> &  ar)=0;
	virtual std::tuple<int,rpc::int8>ping(rpc::int8  i8)=0;
	virtual bool dispatch(std::shared_ptr<rpc::RpcMsg> msg);

};//class

}///namespace
#endif
