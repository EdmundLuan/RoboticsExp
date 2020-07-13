

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 8.00.0603 */
/* at Mon Aug 28 21:24:18 2017
 */
/* Compiler settings for qkmlinklib.idl:
    Oicf, W1, Zp8, env=Win32 (32b run), target_arch=X86 8.00.0603 
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
/* @@MIDL_FILE_HEADING(  ) */

#pragma warning( disable: 4049 )  /* more than 64k source lines */


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 475
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif // __RPCNDR_H_VERSION__

#ifndef COM_NO_WINDOWS_H
#include "windows.h"
#include "ole2.h"
#endif /*COM_NO_WINDOWS_H*/

#ifndef __qkmlinklib_i_h__
#define __qkmlinklib_i_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IQKMLink_FWD_DEFINED__
#define __IQKMLink_FWD_DEFINED__
typedef interface IQKMLink IQKMLink;

#endif 	/* __IQKMLink_FWD_DEFINED__ */


#ifndef __IQKMLinkResult_FWD_DEFINED__
#define __IQKMLinkResult_FWD_DEFINED__
typedef interface IQKMLinkResult IQKMLinkResult;

#endif 	/* __IQKMLinkResult_FWD_DEFINED__ */


#ifndef __IQKMLinkServer_FWD_DEFINED__
#define __IQKMLinkServer_FWD_DEFINED__
typedef interface IQKMLinkServer IQKMLinkServer;

#endif 	/* __IQKMLinkServer_FWD_DEFINED__ */


#ifndef __IQKMLinkClient_FWD_DEFINED__
#define __IQKMLinkClient_FWD_DEFINED__
typedef interface IQKMLinkClient IQKMLinkClient;

#endif 	/* __IQKMLinkClient_FWD_DEFINED__ */


#ifndef __IQKMLinkBroad_FWD_DEFINED__
#define __IQKMLinkBroad_FWD_DEFINED__
typedef interface IQKMLinkBroad IQKMLinkBroad;

#endif 	/* __IQKMLinkBroad_FWD_DEFINED__ */


#ifndef __IQKMLinkConfig_FWD_DEFINED__
#define __IQKMLinkConfig_FWD_DEFINED__
typedef interface IQKMLinkConfig IQKMLinkConfig;

#endif 	/* __IQKMLinkConfig_FWD_DEFINED__ */


#ifndef ___IQKMLinkServerEvents_FWD_DEFINED__
#define ___IQKMLinkServerEvents_FWD_DEFINED__
typedef interface _IQKMLinkServerEvents _IQKMLinkServerEvents;

#endif 	/* ___IQKMLinkServerEvents_FWD_DEFINED__ */


#ifndef __QKMLinkServer_FWD_DEFINED__
#define __QKMLinkServer_FWD_DEFINED__

#ifdef __cplusplus
typedef class QKMLinkServer QKMLinkServer;
#else
typedef struct QKMLinkServer QKMLinkServer;
#endif /* __cplusplus */

#endif 	/* __QKMLinkServer_FWD_DEFINED__ */


#ifndef ___IQKMLinkClientEvents_FWD_DEFINED__
#define ___IQKMLinkClientEvents_FWD_DEFINED__
typedef interface _IQKMLinkClientEvents _IQKMLinkClientEvents;

#endif 	/* ___IQKMLinkClientEvents_FWD_DEFINED__ */


#ifndef __QKMLinkClient_FWD_DEFINED__
#define __QKMLinkClient_FWD_DEFINED__

#ifdef __cplusplus
typedef class QKMLinkClient QKMLinkClient;
#else
typedef struct QKMLinkClient QKMLinkClient;
#endif /* __cplusplus */

#endif 	/* __QKMLinkClient_FWD_DEFINED__ */


#ifndef ___IQKMLinkBroadEvents_FWD_DEFINED__
#define ___IQKMLinkBroadEvents_FWD_DEFINED__
typedef interface _IQKMLinkBroadEvents _IQKMLinkBroadEvents;

#endif 	/* ___IQKMLinkBroadEvents_FWD_DEFINED__ */


#ifndef __QKMLinkBroad_FWD_DEFINED__
#define __QKMLinkBroad_FWD_DEFINED__

#ifdef __cplusplus
typedef class QKMLinkBroad QKMLinkBroad;
#else
typedef struct QKMLinkBroad QKMLinkBroad;
#endif /* __cplusplus */

#endif 	/* __QKMLinkBroad_FWD_DEFINED__ */


#ifndef ___IQKMLinkResultEvents_FWD_DEFINED__
#define ___IQKMLinkResultEvents_FWD_DEFINED__
typedef interface _IQKMLinkResultEvents _IQKMLinkResultEvents;

#endif 	/* ___IQKMLinkResultEvents_FWD_DEFINED__ */


#ifndef __QKMLinkResult_FWD_DEFINED__
#define __QKMLinkResult_FWD_DEFINED__

#ifdef __cplusplus
typedef class QKMLinkResult QKMLinkResult;
#else
typedef struct QKMLinkResult QKMLinkResult;
#endif /* __cplusplus */

#endif 	/* __QKMLinkResult_FWD_DEFINED__ */


#ifndef ___IQKMLinkEvents_FWD_DEFINED__
#define ___IQKMLinkEvents_FWD_DEFINED__
typedef interface _IQKMLinkEvents _IQKMLinkEvents;

#endif 	/* ___IQKMLinkEvents_FWD_DEFINED__ */


#ifndef __QKMLink_FWD_DEFINED__
#define __QKMLink_FWD_DEFINED__

#ifdef __cplusplus
typedef class QKMLink QKMLink;
#else
typedef struct QKMLink QKMLink;
#endif /* __cplusplus */

#endif 	/* __QKMLink_FWD_DEFINED__ */


#ifndef ___IQKMLinkConfigEvents_FWD_DEFINED__
#define ___IQKMLinkConfigEvents_FWD_DEFINED__
typedef interface _IQKMLinkConfigEvents _IQKMLinkConfigEvents;

#endif 	/* ___IQKMLinkConfigEvents_FWD_DEFINED__ */


#ifndef __QKMLinkConfig_FWD_DEFINED__
#define __QKMLinkConfig_FWD_DEFINED__

#ifdef __cplusplus
typedef class QKMLinkConfig QKMLinkConfig;
#else
typedef struct QKMLinkConfig QKMLinkConfig;
#endif /* __cplusplus */

#endif 	/* __QKMLinkConfig_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

#ifdef __cplusplus
extern "C"{
#endif 


#ifndef __IQKMLink_INTERFACE_DEFINED__
#define __IQKMLink_INTERFACE_DEFINED__

/* interface IQKMLink */
/* [unique][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_IQKMLink;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("976A5CB9-D42E-44F6-9A85-7DC1E2ACEABA")
    IQKMLink : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Version( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ReceiveEventDrive( 
            /* [in] */ BSTR message,
            /* [in] */ BSTR params) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IQKMLinkVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IQKMLink * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IQKMLink * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IQKMLink * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IQKMLink * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IQKMLink * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IQKMLink * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IQKMLink * This,
            /* [annotation][in] */ 
            _In_  DISPID dispIdMember,
            /* [annotation][in] */ 
            _In_  REFIID riid,
            /* [annotation][in] */ 
            _In_  LCID lcid,
            /* [annotation][in] */ 
            _In_  WORD wFlags,
            /* [annotation][out][in] */ 
            _In_  DISPPARAMS *pDispParams,
            /* [annotation][out] */ 
            _Out_opt_  VARIANT *pVarResult,
            /* [annotation][out] */ 
            _Out_opt_  EXCEPINFO *pExcepInfo,
            /* [annotation][out] */ 
            _Out_opt_  UINT *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Version )( 
            IQKMLink * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *ReceiveEventDrive )( 
            IQKMLink * This,
            /* [in] */ BSTR message,
            /* [in] */ BSTR params);
        
        END_INTERFACE
    } IQKMLinkVtbl;

    interface IQKMLink
    {
        CONST_VTBL struct IQKMLinkVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IQKMLink_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IQKMLink_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IQKMLink_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IQKMLink_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IQKMLink_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IQKMLink_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IQKMLink_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define IQKMLink_get_Version(This,pVal)	\
    ( (This)->lpVtbl -> get_Version(This,pVal) ) 

#define IQKMLink_ReceiveEventDrive(This,message,params)	\
    ( (This)->lpVtbl -> ReceiveEventDrive(This,message,params) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IQKMLink_INTERFACE_DEFINED__ */


#ifndef __IQKMLinkResult_INTERFACE_DEFINED__
#define __IQKMLinkResult_INTERFACE_DEFINED__

/* interface IQKMLinkResult */
/* [unique][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_IQKMLinkResult;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("EFE5143F-A333-4158-A69C-80C666023600")
    IQKMLinkResult : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_SourceID( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_SourceID( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_DestinationID( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_DestinationID( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_PacketID( 
            /* [retval][out] */ LONG *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_PacketID( 
            /* [in] */ LONG newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_SequenceNum( 
            /* [retval][out] */ LONG *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_SequenceNum( 
            /* [in] */ LONG newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Command( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Command( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_State( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_State( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Timeout( 
            /* [retval][out] */ LONG *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Timeout( 
            /* [in] */ LONG newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Code( 
            /* [retval][out] */ LONG *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Code( 
            /* [in] */ LONG newVal) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IQKMLinkResultVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IQKMLinkResult * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IQKMLinkResult * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IQKMLinkResult * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IQKMLinkResult * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IQKMLinkResult * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IQKMLinkResult * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IQKMLinkResult * This,
            /* [annotation][in] */ 
            _In_  DISPID dispIdMember,
            /* [annotation][in] */ 
            _In_  REFIID riid,
            /* [annotation][in] */ 
            _In_  LCID lcid,
            /* [annotation][in] */ 
            _In_  WORD wFlags,
            /* [annotation][out][in] */ 
            _In_  DISPPARAMS *pDispParams,
            /* [annotation][out] */ 
            _Out_opt_  VARIANT *pVarResult,
            /* [annotation][out] */ 
            _Out_opt_  EXCEPINFO *pExcepInfo,
            /* [annotation][out] */ 
            _Out_opt_  UINT *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_SourceID )( 
            IQKMLinkResult * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_SourceID )( 
            IQKMLinkResult * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_DestinationID )( 
            IQKMLinkResult * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_DestinationID )( 
            IQKMLinkResult * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_PacketID )( 
            IQKMLinkResult * This,
            /* [retval][out] */ LONG *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_PacketID )( 
            IQKMLinkResult * This,
            /* [in] */ LONG newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_SequenceNum )( 
            IQKMLinkResult * This,
            /* [retval][out] */ LONG *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_SequenceNum )( 
            IQKMLinkResult * This,
            /* [in] */ LONG newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Command )( 
            IQKMLinkResult * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Command )( 
            IQKMLinkResult * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_State )( 
            IQKMLinkResult * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_State )( 
            IQKMLinkResult * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Timeout )( 
            IQKMLinkResult * This,
            /* [retval][out] */ LONG *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Timeout )( 
            IQKMLinkResult * This,
            /* [in] */ LONG newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Code )( 
            IQKMLinkResult * This,
            /* [retval][out] */ LONG *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Code )( 
            IQKMLinkResult * This,
            /* [in] */ LONG newVal);
        
        END_INTERFACE
    } IQKMLinkResultVtbl;

    interface IQKMLinkResult
    {
        CONST_VTBL struct IQKMLinkResultVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IQKMLinkResult_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IQKMLinkResult_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IQKMLinkResult_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IQKMLinkResult_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IQKMLinkResult_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IQKMLinkResult_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IQKMLinkResult_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define IQKMLinkResult_get_SourceID(This,pVal)	\
    ( (This)->lpVtbl -> get_SourceID(This,pVal) ) 

#define IQKMLinkResult_put_SourceID(This,newVal)	\
    ( (This)->lpVtbl -> put_SourceID(This,newVal) ) 

#define IQKMLinkResult_get_DestinationID(This,pVal)	\
    ( (This)->lpVtbl -> get_DestinationID(This,pVal) ) 

#define IQKMLinkResult_put_DestinationID(This,newVal)	\
    ( (This)->lpVtbl -> put_DestinationID(This,newVal) ) 

#define IQKMLinkResult_get_PacketID(This,pVal)	\
    ( (This)->lpVtbl -> get_PacketID(This,pVal) ) 

#define IQKMLinkResult_put_PacketID(This,newVal)	\
    ( (This)->lpVtbl -> put_PacketID(This,newVal) ) 

#define IQKMLinkResult_get_SequenceNum(This,pVal)	\
    ( (This)->lpVtbl -> get_SequenceNum(This,pVal) ) 

#define IQKMLinkResult_put_SequenceNum(This,newVal)	\
    ( (This)->lpVtbl -> put_SequenceNum(This,newVal) ) 

#define IQKMLinkResult_get_Command(This,pVal)	\
    ( (This)->lpVtbl -> get_Command(This,pVal) ) 

#define IQKMLinkResult_put_Command(This,newVal)	\
    ( (This)->lpVtbl -> put_Command(This,newVal) ) 

#define IQKMLinkResult_get_State(This,pVal)	\
    ( (This)->lpVtbl -> get_State(This,pVal) ) 

#define IQKMLinkResult_put_State(This,newVal)	\
    ( (This)->lpVtbl -> put_State(This,newVal) ) 

#define IQKMLinkResult_get_Timeout(This,pVal)	\
    ( (This)->lpVtbl -> get_Timeout(This,pVal) ) 

#define IQKMLinkResult_put_Timeout(This,newVal)	\
    ( (This)->lpVtbl -> put_Timeout(This,newVal) ) 

#define IQKMLinkResult_get_Code(This,pVal)	\
    ( (This)->lpVtbl -> get_Code(This,pVal) ) 

#define IQKMLinkResult_put_Code(This,newVal)	\
    ( (This)->lpVtbl -> put_Code(This,newVal) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IQKMLinkResult_INTERFACE_DEFINED__ */


#ifndef __IQKMLinkServer_INTERFACE_DEFINED__
#define __IQKMLinkServer_INTERFACE_DEFINED__

/* interface IQKMLinkServer */
/* [unique][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_IQKMLinkServer;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("F48622B1-A9FF-4D18-B0EF-E716EFA8C045")
    IQKMLinkServer : public IQKMLink
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ServerPort( 
            /* [retval][out] */ LONG *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_ServerPort( 
            /* [in] */ LONG newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_SourceID( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_SourceID( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_DebugMode( 
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_DebugMode( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_NoticeMode( 
            /* [retval][out] */ LONG *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_NoticeMode( 
            /* [in] */ LONG newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ProtocolVersion( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_ProtocolVersion( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Accept( 
            /* [retval][out] */ LONG *result) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Close( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Send( 
            /* [in] */ BSTR destinationID,
            /* [in] */ BSTR message,
            /* [in] */ BSTR mode,
            /* [in] */ LONG timeout,
            /* [retval][out] */ IQKMLinkResult **result) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GoOn( 
            /* [in] */ BSTR destinationID,
            /* [in] */ IQKMLinkResult *oldResult,
            /* [in] */ BSTR message,
            /* [retval][out] */ IQKMLinkResult **newResult) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE CloseDevice( 
            /* [in] */ BSTR destinationID,
            /* [retval][out] */ LONG *result) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Receive( 
            /* [in] */ BSTR destinationID,
            /* [out] */ BSTR *message,
            /* [out] */ IQKMLinkResult **result,
            /* [retval][out] */ LONG *error) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Stop( 
            /* [in] */ BSTR destinationID,
            /* [in] */ IQKMLinkResult *oldResult,
            /* [retval][out] */ LONG *error) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE CurrentState( 
            /* [in] */ BSTR destinationID,
            /* [retval][out] */ LONG *state) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IQKMLinkServerVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IQKMLinkServer * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IQKMLinkServer * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IQKMLinkServer * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IQKMLinkServer * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IQKMLinkServer * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IQKMLinkServer * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IQKMLinkServer * This,
            /* [annotation][in] */ 
            _In_  DISPID dispIdMember,
            /* [annotation][in] */ 
            _In_  REFIID riid,
            /* [annotation][in] */ 
            _In_  LCID lcid,
            /* [annotation][in] */ 
            _In_  WORD wFlags,
            /* [annotation][out][in] */ 
            _In_  DISPPARAMS *pDispParams,
            /* [annotation][out] */ 
            _Out_opt_  VARIANT *pVarResult,
            /* [annotation][out] */ 
            _Out_opt_  EXCEPINFO *pExcepInfo,
            /* [annotation][out] */ 
            _Out_opt_  UINT *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Version )( 
            IQKMLinkServer * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *ReceiveEventDrive )( 
            IQKMLinkServer * This,
            /* [in] */ BSTR message,
            /* [in] */ BSTR params);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ServerPort )( 
            IQKMLinkServer * This,
            /* [retval][out] */ LONG *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_ServerPort )( 
            IQKMLinkServer * This,
            /* [in] */ LONG newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_SourceID )( 
            IQKMLinkServer * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_SourceID )( 
            IQKMLinkServer * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_DebugMode )( 
            IQKMLinkServer * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_DebugMode )( 
            IQKMLinkServer * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_NoticeMode )( 
            IQKMLinkServer * This,
            /* [retval][out] */ LONG *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_NoticeMode )( 
            IQKMLinkServer * This,
            /* [in] */ LONG newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ProtocolVersion )( 
            IQKMLinkServer * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_ProtocolVersion )( 
            IQKMLinkServer * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Accept )( 
            IQKMLinkServer * This,
            /* [retval][out] */ LONG *result);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Close )( 
            IQKMLinkServer * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Send )( 
            IQKMLinkServer * This,
            /* [in] */ BSTR destinationID,
            /* [in] */ BSTR message,
            /* [in] */ BSTR mode,
            /* [in] */ LONG timeout,
            /* [retval][out] */ IQKMLinkResult **result);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GoOn )( 
            IQKMLinkServer * This,
            /* [in] */ BSTR destinationID,
            /* [in] */ IQKMLinkResult *oldResult,
            /* [in] */ BSTR message,
            /* [retval][out] */ IQKMLinkResult **newResult);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *CloseDevice )( 
            IQKMLinkServer * This,
            /* [in] */ BSTR destinationID,
            /* [retval][out] */ LONG *result);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Receive )( 
            IQKMLinkServer * This,
            /* [in] */ BSTR destinationID,
            /* [out] */ BSTR *message,
            /* [out] */ IQKMLinkResult **result,
            /* [retval][out] */ LONG *error);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Stop )( 
            IQKMLinkServer * This,
            /* [in] */ BSTR destinationID,
            /* [in] */ IQKMLinkResult *oldResult,
            /* [retval][out] */ LONG *error);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *CurrentState )( 
            IQKMLinkServer * This,
            /* [in] */ BSTR destinationID,
            /* [retval][out] */ LONG *state);
        
        END_INTERFACE
    } IQKMLinkServerVtbl;

    interface IQKMLinkServer
    {
        CONST_VTBL struct IQKMLinkServerVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IQKMLinkServer_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IQKMLinkServer_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IQKMLinkServer_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IQKMLinkServer_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IQKMLinkServer_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IQKMLinkServer_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IQKMLinkServer_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define IQKMLinkServer_get_Version(This,pVal)	\
    ( (This)->lpVtbl -> get_Version(This,pVal) ) 

#define IQKMLinkServer_ReceiveEventDrive(This,message,params)	\
    ( (This)->lpVtbl -> ReceiveEventDrive(This,message,params) ) 


#define IQKMLinkServer_get_ServerPort(This,pVal)	\
    ( (This)->lpVtbl -> get_ServerPort(This,pVal) ) 

#define IQKMLinkServer_put_ServerPort(This,newVal)	\
    ( (This)->lpVtbl -> put_ServerPort(This,newVal) ) 

#define IQKMLinkServer_get_SourceID(This,pVal)	\
    ( (This)->lpVtbl -> get_SourceID(This,pVal) ) 

#define IQKMLinkServer_put_SourceID(This,newVal)	\
    ( (This)->lpVtbl -> put_SourceID(This,newVal) ) 

#define IQKMLinkServer_get_DebugMode(This,pVal)	\
    ( (This)->lpVtbl -> get_DebugMode(This,pVal) ) 

#define IQKMLinkServer_put_DebugMode(This,newVal)	\
    ( (This)->lpVtbl -> put_DebugMode(This,newVal) ) 

#define IQKMLinkServer_get_NoticeMode(This,pVal)	\
    ( (This)->lpVtbl -> get_NoticeMode(This,pVal) ) 

#define IQKMLinkServer_put_NoticeMode(This,newVal)	\
    ( (This)->lpVtbl -> put_NoticeMode(This,newVal) ) 

#define IQKMLinkServer_get_ProtocolVersion(This,pVal)	\
    ( (This)->lpVtbl -> get_ProtocolVersion(This,pVal) ) 

#define IQKMLinkServer_put_ProtocolVersion(This,newVal)	\
    ( (This)->lpVtbl -> put_ProtocolVersion(This,newVal) ) 

#define IQKMLinkServer_Accept(This,result)	\
    ( (This)->lpVtbl -> Accept(This,result) ) 

#define IQKMLinkServer_Close(This)	\
    ( (This)->lpVtbl -> Close(This) ) 

#define IQKMLinkServer_Send(This,destinationID,message,mode,timeout,result)	\
    ( (This)->lpVtbl -> Send(This,destinationID,message,mode,timeout,result) ) 

#define IQKMLinkServer_GoOn(This,destinationID,oldResult,message,newResult)	\
    ( (This)->lpVtbl -> GoOn(This,destinationID,oldResult,message,newResult) ) 

#define IQKMLinkServer_CloseDevice(This,destinationID,result)	\
    ( (This)->lpVtbl -> CloseDevice(This,destinationID,result) ) 

#define IQKMLinkServer_Receive(This,destinationID,message,result,error)	\
    ( (This)->lpVtbl -> Receive(This,destinationID,message,result,error) ) 

#define IQKMLinkServer_Stop(This,destinationID,oldResult,error)	\
    ( (This)->lpVtbl -> Stop(This,destinationID,oldResult,error) ) 

#define IQKMLinkServer_CurrentState(This,destinationID,state)	\
    ( (This)->lpVtbl -> CurrentState(This,destinationID,state) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IQKMLinkServer_INTERFACE_DEFINED__ */


#ifndef __IQKMLinkClient_INTERFACE_DEFINED__
#define __IQKMLinkClient_INTERFACE_DEFINED__

/* interface IQKMLinkClient */
/* [unique][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_IQKMLinkClient;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("2BB5C1B6-F268-4E87-8914-FE1BD3EA094E")
    IQKMLinkClient : public IQKMLink
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ServerAddress( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_ServerAddress( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ServerPort( 
            /* [retval][out] */ LONG *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_ServerPort( 
            /* [in] */ LONG newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_SourceID( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_SourceID( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_DebugMode( 
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_DebugMode( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_NoticeMode( 
            /* [retval][out] */ LONG *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_NoticeMode( 
            /* [in] */ LONG newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ProtocolVersion( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_ProtocolVersion( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Send( 
            /* [in] */ BSTR message,
            /* [in] */ BSTR mode,
            /* [in] */ LONG timeout,
            /* [retval][out] */ IQKMLinkResult **result) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GoOn( 
            /* [in] */ IQKMLinkResult *oldResult,
            /* [in] */ BSTR message,
            /* [retval][out] */ IQKMLinkResult **newResult) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Stop( 
            /* [in] */ IQKMLinkResult *result,
            /* [retval][out] */ LONG *error) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Connect( 
            /* [retval][out] */ LONG *result) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Close( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Receive( 
            /* [out] */ BSTR *message,
            /* [out] */ IQKMLinkResult **result,
            /* [retval][out] */ LONG *error) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE CurrentState( 
            /* [retval][out] */ LONG *state) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IQKMLinkClientVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IQKMLinkClient * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IQKMLinkClient * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IQKMLinkClient * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IQKMLinkClient * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IQKMLinkClient * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IQKMLinkClient * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IQKMLinkClient * This,
            /* [annotation][in] */ 
            _In_  DISPID dispIdMember,
            /* [annotation][in] */ 
            _In_  REFIID riid,
            /* [annotation][in] */ 
            _In_  LCID lcid,
            /* [annotation][in] */ 
            _In_  WORD wFlags,
            /* [annotation][out][in] */ 
            _In_  DISPPARAMS *pDispParams,
            /* [annotation][out] */ 
            _Out_opt_  VARIANT *pVarResult,
            /* [annotation][out] */ 
            _Out_opt_  EXCEPINFO *pExcepInfo,
            /* [annotation][out] */ 
            _Out_opt_  UINT *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Version )( 
            IQKMLinkClient * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *ReceiveEventDrive )( 
            IQKMLinkClient * This,
            /* [in] */ BSTR message,
            /* [in] */ BSTR params);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ServerAddress )( 
            IQKMLinkClient * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_ServerAddress )( 
            IQKMLinkClient * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ServerPort )( 
            IQKMLinkClient * This,
            /* [retval][out] */ LONG *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_ServerPort )( 
            IQKMLinkClient * This,
            /* [in] */ LONG newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_SourceID )( 
            IQKMLinkClient * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_SourceID )( 
            IQKMLinkClient * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_DebugMode )( 
            IQKMLinkClient * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_DebugMode )( 
            IQKMLinkClient * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_NoticeMode )( 
            IQKMLinkClient * This,
            /* [retval][out] */ LONG *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_NoticeMode )( 
            IQKMLinkClient * This,
            /* [in] */ LONG newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ProtocolVersion )( 
            IQKMLinkClient * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_ProtocolVersion )( 
            IQKMLinkClient * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Send )( 
            IQKMLinkClient * This,
            /* [in] */ BSTR message,
            /* [in] */ BSTR mode,
            /* [in] */ LONG timeout,
            /* [retval][out] */ IQKMLinkResult **result);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GoOn )( 
            IQKMLinkClient * This,
            /* [in] */ IQKMLinkResult *oldResult,
            /* [in] */ BSTR message,
            /* [retval][out] */ IQKMLinkResult **newResult);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Stop )( 
            IQKMLinkClient * This,
            /* [in] */ IQKMLinkResult *result,
            /* [retval][out] */ LONG *error);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Connect )( 
            IQKMLinkClient * This,
            /* [retval][out] */ LONG *result);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Close )( 
            IQKMLinkClient * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Receive )( 
            IQKMLinkClient * This,
            /* [out] */ BSTR *message,
            /* [out] */ IQKMLinkResult **result,
            /* [retval][out] */ LONG *error);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *CurrentState )( 
            IQKMLinkClient * This,
            /* [retval][out] */ LONG *state);
        
        END_INTERFACE
    } IQKMLinkClientVtbl;

    interface IQKMLinkClient
    {
        CONST_VTBL struct IQKMLinkClientVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IQKMLinkClient_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IQKMLinkClient_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IQKMLinkClient_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IQKMLinkClient_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IQKMLinkClient_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IQKMLinkClient_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IQKMLinkClient_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define IQKMLinkClient_get_Version(This,pVal)	\
    ( (This)->lpVtbl -> get_Version(This,pVal) ) 

#define IQKMLinkClient_ReceiveEventDrive(This,message,params)	\
    ( (This)->lpVtbl -> ReceiveEventDrive(This,message,params) ) 


#define IQKMLinkClient_get_ServerAddress(This,pVal)	\
    ( (This)->lpVtbl -> get_ServerAddress(This,pVal) ) 

#define IQKMLinkClient_put_ServerAddress(This,newVal)	\
    ( (This)->lpVtbl -> put_ServerAddress(This,newVal) ) 

#define IQKMLinkClient_get_ServerPort(This,pVal)	\
    ( (This)->lpVtbl -> get_ServerPort(This,pVal) ) 

#define IQKMLinkClient_put_ServerPort(This,newVal)	\
    ( (This)->lpVtbl -> put_ServerPort(This,newVal) ) 

#define IQKMLinkClient_get_SourceID(This,pVal)	\
    ( (This)->lpVtbl -> get_SourceID(This,pVal) ) 

#define IQKMLinkClient_put_SourceID(This,newVal)	\
    ( (This)->lpVtbl -> put_SourceID(This,newVal) ) 

#define IQKMLinkClient_get_DebugMode(This,pVal)	\
    ( (This)->lpVtbl -> get_DebugMode(This,pVal) ) 

#define IQKMLinkClient_put_DebugMode(This,newVal)	\
    ( (This)->lpVtbl -> put_DebugMode(This,newVal) ) 

#define IQKMLinkClient_get_NoticeMode(This,pVal)	\
    ( (This)->lpVtbl -> get_NoticeMode(This,pVal) ) 

#define IQKMLinkClient_put_NoticeMode(This,newVal)	\
    ( (This)->lpVtbl -> put_NoticeMode(This,newVal) ) 

#define IQKMLinkClient_get_ProtocolVersion(This,pVal)	\
    ( (This)->lpVtbl -> get_ProtocolVersion(This,pVal) ) 

#define IQKMLinkClient_put_ProtocolVersion(This,newVal)	\
    ( (This)->lpVtbl -> put_ProtocolVersion(This,newVal) ) 

#define IQKMLinkClient_Send(This,message,mode,timeout,result)	\
    ( (This)->lpVtbl -> Send(This,message,mode,timeout,result) ) 

#define IQKMLinkClient_GoOn(This,oldResult,message,newResult)	\
    ( (This)->lpVtbl -> GoOn(This,oldResult,message,newResult) ) 

#define IQKMLinkClient_Stop(This,result,error)	\
    ( (This)->lpVtbl -> Stop(This,result,error) ) 

#define IQKMLinkClient_Connect(This,result)	\
    ( (This)->lpVtbl -> Connect(This,result) ) 

#define IQKMLinkClient_Close(This)	\
    ( (This)->lpVtbl -> Close(This) ) 

#define IQKMLinkClient_Receive(This,message,result,error)	\
    ( (This)->lpVtbl -> Receive(This,message,result,error) ) 

#define IQKMLinkClient_CurrentState(This,state)	\
    ( (This)->lpVtbl -> CurrentState(This,state) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IQKMLinkClient_INTERFACE_DEFINED__ */


#ifndef __IQKMLinkBroad_INTERFACE_DEFINED__
#define __IQKMLinkBroad_INTERFACE_DEFINED__

/* interface IQKMLinkBroad */
/* [unique][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_IQKMLinkBroad;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("B2B35512-2FC9-4ED4-9A93-0F7C811809B4")
    IQKMLinkBroad : public IQKMLink
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_SourceID( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_SourceID( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_LocalPort( 
            /* [retval][out] */ LONG *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_LocalPort( 
            /* [in] */ LONG newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_RemotePort( 
            /* [retval][out] */ LONG *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_RemotePort( 
            /* [in] */ LONG newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_DebugMode( 
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_DebugMode( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ProtocolVersion( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_ProtocolVersion( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Broadcast( 
            /* [in] */ BSTR message,
            /* [retval][out] */ IQKMLinkResult **result) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Create( 
            /* [retval][out] */ LONG *result) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Close( void) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IQKMLinkBroadVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IQKMLinkBroad * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IQKMLinkBroad * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IQKMLinkBroad * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IQKMLinkBroad * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IQKMLinkBroad * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IQKMLinkBroad * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IQKMLinkBroad * This,
            /* [annotation][in] */ 
            _In_  DISPID dispIdMember,
            /* [annotation][in] */ 
            _In_  REFIID riid,
            /* [annotation][in] */ 
            _In_  LCID lcid,
            /* [annotation][in] */ 
            _In_  WORD wFlags,
            /* [annotation][out][in] */ 
            _In_  DISPPARAMS *pDispParams,
            /* [annotation][out] */ 
            _Out_opt_  VARIANT *pVarResult,
            /* [annotation][out] */ 
            _Out_opt_  EXCEPINFO *pExcepInfo,
            /* [annotation][out] */ 
            _Out_opt_  UINT *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Version )( 
            IQKMLinkBroad * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *ReceiveEventDrive )( 
            IQKMLinkBroad * This,
            /* [in] */ BSTR message,
            /* [in] */ BSTR params);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_SourceID )( 
            IQKMLinkBroad * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_SourceID )( 
            IQKMLinkBroad * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_LocalPort )( 
            IQKMLinkBroad * This,
            /* [retval][out] */ LONG *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_LocalPort )( 
            IQKMLinkBroad * This,
            /* [in] */ LONG newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_RemotePort )( 
            IQKMLinkBroad * This,
            /* [retval][out] */ LONG *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_RemotePort )( 
            IQKMLinkBroad * This,
            /* [in] */ LONG newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_DebugMode )( 
            IQKMLinkBroad * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_DebugMode )( 
            IQKMLinkBroad * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ProtocolVersion )( 
            IQKMLinkBroad * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_ProtocolVersion )( 
            IQKMLinkBroad * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Broadcast )( 
            IQKMLinkBroad * This,
            /* [in] */ BSTR message,
            /* [retval][out] */ IQKMLinkResult **result);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Create )( 
            IQKMLinkBroad * This,
            /* [retval][out] */ LONG *result);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Close )( 
            IQKMLinkBroad * This);
        
        END_INTERFACE
    } IQKMLinkBroadVtbl;

    interface IQKMLinkBroad
    {
        CONST_VTBL struct IQKMLinkBroadVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IQKMLinkBroad_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IQKMLinkBroad_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IQKMLinkBroad_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IQKMLinkBroad_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IQKMLinkBroad_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IQKMLinkBroad_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IQKMLinkBroad_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define IQKMLinkBroad_get_Version(This,pVal)	\
    ( (This)->lpVtbl -> get_Version(This,pVal) ) 

#define IQKMLinkBroad_ReceiveEventDrive(This,message,params)	\
    ( (This)->lpVtbl -> ReceiveEventDrive(This,message,params) ) 


#define IQKMLinkBroad_get_SourceID(This,pVal)	\
    ( (This)->lpVtbl -> get_SourceID(This,pVal) ) 

#define IQKMLinkBroad_put_SourceID(This,newVal)	\
    ( (This)->lpVtbl -> put_SourceID(This,newVal) ) 

#define IQKMLinkBroad_get_LocalPort(This,pVal)	\
    ( (This)->lpVtbl -> get_LocalPort(This,pVal) ) 

#define IQKMLinkBroad_put_LocalPort(This,newVal)	\
    ( (This)->lpVtbl -> put_LocalPort(This,newVal) ) 

#define IQKMLinkBroad_get_RemotePort(This,pVal)	\
    ( (This)->lpVtbl -> get_RemotePort(This,pVal) ) 

#define IQKMLinkBroad_put_RemotePort(This,newVal)	\
    ( (This)->lpVtbl -> put_RemotePort(This,newVal) ) 

#define IQKMLinkBroad_get_DebugMode(This,pVal)	\
    ( (This)->lpVtbl -> get_DebugMode(This,pVal) ) 

#define IQKMLinkBroad_put_DebugMode(This,newVal)	\
    ( (This)->lpVtbl -> put_DebugMode(This,newVal) ) 

#define IQKMLinkBroad_get_ProtocolVersion(This,pVal)	\
    ( (This)->lpVtbl -> get_ProtocolVersion(This,pVal) ) 

#define IQKMLinkBroad_put_ProtocolVersion(This,newVal)	\
    ( (This)->lpVtbl -> put_ProtocolVersion(This,newVal) ) 

#define IQKMLinkBroad_Broadcast(This,message,result)	\
    ( (This)->lpVtbl -> Broadcast(This,message,result) ) 

#define IQKMLinkBroad_Create(This,result)	\
    ( (This)->lpVtbl -> Create(This,result) ) 

#define IQKMLinkBroad_Close(This)	\
    ( (This)->lpVtbl -> Close(This) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IQKMLinkBroad_INTERFACE_DEFINED__ */


#ifndef __IQKMLinkConfig_INTERFACE_DEFINED__
#define __IQKMLinkConfig_INTERFACE_DEFINED__

/* interface IQKMLinkConfig */
/* [unique][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_IQKMLinkConfig;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("CC1D164A-8D78-4362-9B40-572E03ADF1A5")
    IQKMLinkConfig : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_BootFileName( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_BootFileName( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Read( 
            /* [retval][out] */ LONG *result) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Write( 
            /* [retval][out] */ LONG *result) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ReadIO( 
            /* [in] */ LONG opcode,
            /* [in] */ LONG index,
            /* [out] */ BSTR *comment,
            /* [out] */ BSTR *value,
            /* [retval][out] */ LONG *result) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE WriteIO( 
            /* [in] */ LONG opcode,
            /* [in] */ LONG index,
            /* [in] */ BSTR comment,
            /* [in] */ BSTR value,
            /* [retval][out] */ LONG *result) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IQKMLinkConfigVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IQKMLinkConfig * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IQKMLinkConfig * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IQKMLinkConfig * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IQKMLinkConfig * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IQKMLinkConfig * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IQKMLinkConfig * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IQKMLinkConfig * This,
            /* [annotation][in] */ 
            _In_  DISPID dispIdMember,
            /* [annotation][in] */ 
            _In_  REFIID riid,
            /* [annotation][in] */ 
            _In_  LCID lcid,
            /* [annotation][in] */ 
            _In_  WORD wFlags,
            /* [annotation][out][in] */ 
            _In_  DISPPARAMS *pDispParams,
            /* [annotation][out] */ 
            _Out_opt_  VARIANT *pVarResult,
            /* [annotation][out] */ 
            _Out_opt_  EXCEPINFO *pExcepInfo,
            /* [annotation][out] */ 
            _Out_opt_  UINT *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_BootFileName )( 
            IQKMLinkConfig * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_BootFileName )( 
            IQKMLinkConfig * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Read )( 
            IQKMLinkConfig * This,
            /* [retval][out] */ LONG *result);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Write )( 
            IQKMLinkConfig * This,
            /* [retval][out] */ LONG *result);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *ReadIO )( 
            IQKMLinkConfig * This,
            /* [in] */ LONG opcode,
            /* [in] */ LONG index,
            /* [out] */ BSTR *comment,
            /* [out] */ BSTR *value,
            /* [retval][out] */ LONG *result);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *WriteIO )( 
            IQKMLinkConfig * This,
            /* [in] */ LONG opcode,
            /* [in] */ LONG index,
            /* [in] */ BSTR comment,
            /* [in] */ BSTR value,
            /* [retval][out] */ LONG *result);
        
        END_INTERFACE
    } IQKMLinkConfigVtbl;

    interface IQKMLinkConfig
    {
        CONST_VTBL struct IQKMLinkConfigVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IQKMLinkConfig_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IQKMLinkConfig_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IQKMLinkConfig_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IQKMLinkConfig_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IQKMLinkConfig_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IQKMLinkConfig_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IQKMLinkConfig_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define IQKMLinkConfig_get_BootFileName(This,pVal)	\
    ( (This)->lpVtbl -> get_BootFileName(This,pVal) ) 

#define IQKMLinkConfig_put_BootFileName(This,newVal)	\
    ( (This)->lpVtbl -> put_BootFileName(This,newVal) ) 

#define IQKMLinkConfig_Read(This,result)	\
    ( (This)->lpVtbl -> Read(This,result) ) 

#define IQKMLinkConfig_Write(This,result)	\
    ( (This)->lpVtbl -> Write(This,result) ) 

#define IQKMLinkConfig_ReadIO(This,opcode,index,comment,value,result)	\
    ( (This)->lpVtbl -> ReadIO(This,opcode,index,comment,value,result) ) 

#define IQKMLinkConfig_WriteIO(This,opcode,index,comment,value,result)	\
    ( (This)->lpVtbl -> WriteIO(This,opcode,index,comment,value,result) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IQKMLinkConfig_INTERFACE_DEFINED__ */



#ifndef __QKMLinkLib_LIBRARY_DEFINED__
#define __QKMLinkLib_LIBRARY_DEFINED__

/* library QKMLinkLib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_QKMLinkLib;

#ifndef ___IQKMLinkServerEvents_DISPINTERFACE_DEFINED__
#define ___IQKMLinkServerEvents_DISPINTERFACE_DEFINED__

/* dispinterface _IQKMLinkServerEvents */
/* [uuid] */ 


EXTERN_C const IID DIID__IQKMLinkServerEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("697AC829-F42B-46A5-83CE-4F8FAA532193")
    _IQKMLinkServerEvents : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _IQKMLinkServerEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _IQKMLinkServerEvents * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _IQKMLinkServerEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _IQKMLinkServerEvents * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _IQKMLinkServerEvents * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _IQKMLinkServerEvents * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _IQKMLinkServerEvents * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _IQKMLinkServerEvents * This,
            /* [annotation][in] */ 
            _In_  DISPID dispIdMember,
            /* [annotation][in] */ 
            _In_  REFIID riid,
            /* [annotation][in] */ 
            _In_  LCID lcid,
            /* [annotation][in] */ 
            _In_  WORD wFlags,
            /* [annotation][out][in] */ 
            _In_  DISPPARAMS *pDispParams,
            /* [annotation][out] */ 
            _Out_opt_  VARIANT *pVarResult,
            /* [annotation][out] */ 
            _Out_opt_  EXCEPINFO *pExcepInfo,
            /* [annotation][out] */ 
            _Out_opt_  UINT *puArgErr);
        
        END_INTERFACE
    } _IQKMLinkServerEventsVtbl;

    interface _IQKMLinkServerEvents
    {
        CONST_VTBL struct _IQKMLinkServerEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _IQKMLinkServerEvents_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define _IQKMLinkServerEvents_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define _IQKMLinkServerEvents_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define _IQKMLinkServerEvents_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define _IQKMLinkServerEvents_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define _IQKMLinkServerEvents_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define _IQKMLinkServerEvents_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___IQKMLinkServerEvents_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_QKMLinkServer;

#ifdef __cplusplus

class DECLSPEC_UUID("151BC794-3DD3-4578-99ED-95170E8890EE")
QKMLinkServer;
#endif

#ifndef ___IQKMLinkClientEvents_DISPINTERFACE_DEFINED__
#define ___IQKMLinkClientEvents_DISPINTERFACE_DEFINED__

/* dispinterface _IQKMLinkClientEvents */
/* [uuid] */ 


EXTERN_C const IID DIID__IQKMLinkClientEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("4BDDB91E-E5D2-41AC-9F49-66957A2E87B5")
    _IQKMLinkClientEvents : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _IQKMLinkClientEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _IQKMLinkClientEvents * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _IQKMLinkClientEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _IQKMLinkClientEvents * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _IQKMLinkClientEvents * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _IQKMLinkClientEvents * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _IQKMLinkClientEvents * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _IQKMLinkClientEvents * This,
            /* [annotation][in] */ 
            _In_  DISPID dispIdMember,
            /* [annotation][in] */ 
            _In_  REFIID riid,
            /* [annotation][in] */ 
            _In_  LCID lcid,
            /* [annotation][in] */ 
            _In_  WORD wFlags,
            /* [annotation][out][in] */ 
            _In_  DISPPARAMS *pDispParams,
            /* [annotation][out] */ 
            _Out_opt_  VARIANT *pVarResult,
            /* [annotation][out] */ 
            _Out_opt_  EXCEPINFO *pExcepInfo,
            /* [annotation][out] */ 
            _Out_opt_  UINT *puArgErr);
        
        END_INTERFACE
    } _IQKMLinkClientEventsVtbl;

    interface _IQKMLinkClientEvents
    {
        CONST_VTBL struct _IQKMLinkClientEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _IQKMLinkClientEvents_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define _IQKMLinkClientEvents_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define _IQKMLinkClientEvents_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define _IQKMLinkClientEvents_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define _IQKMLinkClientEvents_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define _IQKMLinkClientEvents_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define _IQKMLinkClientEvents_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___IQKMLinkClientEvents_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_QKMLinkClient;

#ifdef __cplusplus

class DECLSPEC_UUID("662E9227-73A3-4DA4-B22E-99F8E4C143DD")
QKMLinkClient;
#endif

#ifndef ___IQKMLinkBroadEvents_DISPINTERFACE_DEFINED__
#define ___IQKMLinkBroadEvents_DISPINTERFACE_DEFINED__

/* dispinterface _IQKMLinkBroadEvents */
/* [uuid] */ 


EXTERN_C const IID DIID__IQKMLinkBroadEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("D2683FCA-A916-4EBD-949B-68F1DB4B8540")
    _IQKMLinkBroadEvents : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _IQKMLinkBroadEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _IQKMLinkBroadEvents * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _IQKMLinkBroadEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _IQKMLinkBroadEvents * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _IQKMLinkBroadEvents * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _IQKMLinkBroadEvents * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _IQKMLinkBroadEvents * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _IQKMLinkBroadEvents * This,
            /* [annotation][in] */ 
            _In_  DISPID dispIdMember,
            /* [annotation][in] */ 
            _In_  REFIID riid,
            /* [annotation][in] */ 
            _In_  LCID lcid,
            /* [annotation][in] */ 
            _In_  WORD wFlags,
            /* [annotation][out][in] */ 
            _In_  DISPPARAMS *pDispParams,
            /* [annotation][out] */ 
            _Out_opt_  VARIANT *pVarResult,
            /* [annotation][out] */ 
            _Out_opt_  EXCEPINFO *pExcepInfo,
            /* [annotation][out] */ 
            _Out_opt_  UINT *puArgErr);
        
        END_INTERFACE
    } _IQKMLinkBroadEventsVtbl;

    interface _IQKMLinkBroadEvents
    {
        CONST_VTBL struct _IQKMLinkBroadEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _IQKMLinkBroadEvents_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define _IQKMLinkBroadEvents_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define _IQKMLinkBroadEvents_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define _IQKMLinkBroadEvents_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define _IQKMLinkBroadEvents_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define _IQKMLinkBroadEvents_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define _IQKMLinkBroadEvents_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___IQKMLinkBroadEvents_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_QKMLinkBroad;

#ifdef __cplusplus

class DECLSPEC_UUID("854313C0-83FC-4E3F-BF15-1DCBD584E089")
QKMLinkBroad;
#endif

#ifndef ___IQKMLinkResultEvents_DISPINTERFACE_DEFINED__
#define ___IQKMLinkResultEvents_DISPINTERFACE_DEFINED__

/* dispinterface _IQKMLinkResultEvents */
/* [uuid] */ 


EXTERN_C const IID DIID__IQKMLinkResultEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("6810B76E-643A-455C-974F-27F668139938")
    _IQKMLinkResultEvents : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _IQKMLinkResultEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _IQKMLinkResultEvents * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _IQKMLinkResultEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _IQKMLinkResultEvents * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _IQKMLinkResultEvents * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _IQKMLinkResultEvents * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _IQKMLinkResultEvents * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _IQKMLinkResultEvents * This,
            /* [annotation][in] */ 
            _In_  DISPID dispIdMember,
            /* [annotation][in] */ 
            _In_  REFIID riid,
            /* [annotation][in] */ 
            _In_  LCID lcid,
            /* [annotation][in] */ 
            _In_  WORD wFlags,
            /* [annotation][out][in] */ 
            _In_  DISPPARAMS *pDispParams,
            /* [annotation][out] */ 
            _Out_opt_  VARIANT *pVarResult,
            /* [annotation][out] */ 
            _Out_opt_  EXCEPINFO *pExcepInfo,
            /* [annotation][out] */ 
            _Out_opt_  UINT *puArgErr);
        
        END_INTERFACE
    } _IQKMLinkResultEventsVtbl;

    interface _IQKMLinkResultEvents
    {
        CONST_VTBL struct _IQKMLinkResultEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _IQKMLinkResultEvents_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define _IQKMLinkResultEvents_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define _IQKMLinkResultEvents_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define _IQKMLinkResultEvents_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define _IQKMLinkResultEvents_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define _IQKMLinkResultEvents_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define _IQKMLinkResultEvents_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___IQKMLinkResultEvents_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_QKMLinkResult;

#ifdef __cplusplus

class DECLSPEC_UUID("B38EB8B1-EC17-4FD7-877B-522D677A878A")
QKMLinkResult;
#endif

#ifndef ___IQKMLinkEvents_DISPINTERFACE_DEFINED__
#define ___IQKMLinkEvents_DISPINTERFACE_DEFINED__

/* dispinterface _IQKMLinkEvents */
/* [uuid] */ 


EXTERN_C const IID DIID__IQKMLinkEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("0CCCCAC2-38D3-4D49-9757-4719A44275C7")
    _IQKMLinkEvents : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _IQKMLinkEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _IQKMLinkEvents * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _IQKMLinkEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _IQKMLinkEvents * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _IQKMLinkEvents * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _IQKMLinkEvents * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _IQKMLinkEvents * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _IQKMLinkEvents * This,
            /* [annotation][in] */ 
            _In_  DISPID dispIdMember,
            /* [annotation][in] */ 
            _In_  REFIID riid,
            /* [annotation][in] */ 
            _In_  LCID lcid,
            /* [annotation][in] */ 
            _In_  WORD wFlags,
            /* [annotation][out][in] */ 
            _In_  DISPPARAMS *pDispParams,
            /* [annotation][out] */ 
            _Out_opt_  VARIANT *pVarResult,
            /* [annotation][out] */ 
            _Out_opt_  EXCEPINFO *pExcepInfo,
            /* [annotation][out] */ 
            _Out_opt_  UINT *puArgErr);
        
        END_INTERFACE
    } _IQKMLinkEventsVtbl;

    interface _IQKMLinkEvents
    {
        CONST_VTBL struct _IQKMLinkEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _IQKMLinkEvents_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define _IQKMLinkEvents_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define _IQKMLinkEvents_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define _IQKMLinkEvents_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define _IQKMLinkEvents_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define _IQKMLinkEvents_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define _IQKMLinkEvents_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___IQKMLinkEvents_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_QKMLink;

#ifdef __cplusplus

class DECLSPEC_UUID("14A09443-0767-49EF-A652-AC02DEECAAF5")
QKMLink;
#endif

#ifndef ___IQKMLinkConfigEvents_DISPINTERFACE_DEFINED__
#define ___IQKMLinkConfigEvents_DISPINTERFACE_DEFINED__

/* dispinterface _IQKMLinkConfigEvents */
/* [uuid] */ 


EXTERN_C const IID DIID__IQKMLinkConfigEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("69B649BF-747F-46C5-AC84-A546ED5A3146")
    _IQKMLinkConfigEvents : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _IQKMLinkConfigEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _IQKMLinkConfigEvents * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _IQKMLinkConfigEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _IQKMLinkConfigEvents * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _IQKMLinkConfigEvents * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _IQKMLinkConfigEvents * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _IQKMLinkConfigEvents * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _IQKMLinkConfigEvents * This,
            /* [annotation][in] */ 
            _In_  DISPID dispIdMember,
            /* [annotation][in] */ 
            _In_  REFIID riid,
            /* [annotation][in] */ 
            _In_  LCID lcid,
            /* [annotation][in] */ 
            _In_  WORD wFlags,
            /* [annotation][out][in] */ 
            _In_  DISPPARAMS *pDispParams,
            /* [annotation][out] */ 
            _Out_opt_  VARIANT *pVarResult,
            /* [annotation][out] */ 
            _Out_opt_  EXCEPINFO *pExcepInfo,
            /* [annotation][out] */ 
            _Out_opt_  UINT *puArgErr);
        
        END_INTERFACE
    } _IQKMLinkConfigEventsVtbl;

    interface _IQKMLinkConfigEvents
    {
        CONST_VTBL struct _IQKMLinkConfigEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _IQKMLinkConfigEvents_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define _IQKMLinkConfigEvents_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define _IQKMLinkConfigEvents_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define _IQKMLinkConfigEvents_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define _IQKMLinkConfigEvents_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define _IQKMLinkConfigEvents_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define _IQKMLinkConfigEvents_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___IQKMLinkConfigEvents_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_QKMLinkConfig;

#ifdef __cplusplus

class DECLSPEC_UUID("AAEB94F9-9675-4049-8055-37205F40CC20")
QKMLinkConfig;
#endif
#endif /* __QKMLinkLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

unsigned long             __RPC_USER  BSTR_UserSize(     unsigned long *, unsigned long            , BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserMarshal(  unsigned long *, unsigned char *, BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserUnmarshal(unsigned long *, unsigned char *, BSTR * ); 
void                      __RPC_USER  BSTR_UserFree(     unsigned long *, BSTR * ); 

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


