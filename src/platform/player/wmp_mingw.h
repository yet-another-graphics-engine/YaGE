#ifndef WMP_MINGW_H_
#define WMP_MINGW_H_

#include <windows.h>
#include <ole2.h>

struct IWMPPlayer;
struct IWMPSettings;
struct IWMPMedia;
struct IWMPMediaCollection;
struct IWMPPlaylistCollection;
struct IWMPNetwork;
struct IWMPPlaylist;
struct IWMPError;
struct IWMPCdromCollection;
struct IWMPClosedCaption;
struct IWMPControls;

typedef enum WMPPlayState {wmppsUndefined, wmppsStopped, wmppsPaused, wmppsPlaying, wmppsScanForward, wmppsScanReverse, wmppsBuffering, wmppsWaiting, wmppsMediaEnded, wmppsTransitioning, wmppsReady, wmppsReconnecting, wmppsLast} WMPPlayState;
typedef enum WMPOpenState {wmposUndefined, wmposPlaylistChanging, wmposPlaylistLocating, wmposPlaylistConnecting, wmposPlaylistLoading, wmposPlaylistOpening, wmposPlaylistOpenNoMedia, wmposPlaylistChanged, wmposMediaChanging, wmposMediaLocating, wmposMediaConnecting, wmposMediaLoading, wmposMediaOpening, wmposMediaOpen, wmposBeginCodecAcquisition, wmposEndCodecAcquisition, wmposBeginLicenseAcquisition, wmposEndLicenseAcquisition, wmposBeginIndividualization, wmposEndIndividualization, wmposMediaWaiting, wmposOpeningUnknownURL} WMPOpenState;

typedef struct IWMPPlayerVtbl {
    HRESULT(STDMETHODCALLTYPE *QueryInterface)(IWMPPlayer *This, REFIID riid, void **ppvObject);
    ULONG(STDMETHODCALLTYPE *AddRef)(IWMPPlayer *This);
    ULONG(STDMETHODCALLTYPE *Release)(IWMPPlayer *This);
    HRESULT(STDMETHODCALLTYPE *GetTypeInfoCount)(IWMPPlayer *This, UINT *pctinfo);
    HRESULT(STDMETHODCALLTYPE *GetTypeInfo)(IWMPPlayer *This, UINT iTInfo, LCID lcid, ITypeInfo **ppTInfo);
    HRESULT(STDMETHODCALLTYPE *GetIDsOfNames)(IWMPPlayer *This, REFIID riid, LPOLESTR *rgszNames, UINT cNames, LCID lcid, DISPID *rgDispId);
    HRESULT(STDMETHODCALLTYPE *Invoke)(IWMPPlayer *This, DISPID dispIdMember, REFIID riid, LCID lcid, WORD wFlags, DISPPARAMS *pDispParams, VARIANT *pVarResult, EXCEPINFO *pExcepInfo, UINT *puArgErr);
    HRESULT(STDMETHODCALLTYPE *close)(IWMPPlayer *This);
    HRESULT(STDMETHODCALLTYPE *get_URL)(IWMPPlayer *This, BSTR *pbstrURL);
    HRESULT(STDMETHODCALLTYPE *put_URL)(IWMPPlayer *This, BSTR bstrURL);
    HRESULT(STDMETHODCALLTYPE *get_openState)(IWMPPlayer *This, WMPOpenState  *pwmpos);
    HRESULT(STDMETHODCALLTYPE *get_playState)(IWMPPlayer *This, WMPPlayState *pwmpps);
    HRESULT(STDMETHODCALLTYPE *get_controls)(IWMPPlayer *This, IWMPControls **ppControl);
    HRESULT(STDMETHODCALLTYPE *get_settings)(IWMPPlayer *This, IWMPSettings **ppSettings);
    HRESULT(STDMETHODCALLTYPE *get_currentMedia)(IWMPPlayer *This, IWMPMedia **ppMedia);
    HRESULT(STDMETHODCALLTYPE *put_currentMedia)(IWMPPlayer *This, IWMPMedia *pMedia);
    HRESULT(STDMETHODCALLTYPE *get_mediaCollection)(IWMPPlayer *This, IWMPMediaCollection **ppMediaCollection);
    HRESULT(STDMETHODCALLTYPE *get_playlistCollection)(IWMPPlayer *This, IWMPPlaylistCollection **ppPlaylistCollection);
    HRESULT(STDMETHODCALLTYPE *get_versionInfo)(IWMPPlayer *This, BSTR *pbstrVersionInfo);
    HRESULT(STDMETHODCALLTYPE *launchURL)(IWMPPlayer *This, BSTR bstrURL);
    HRESULT(STDMETHODCALLTYPE *get_network)(IWMPPlayer *This, IWMPNetwork **ppQNI);
    HRESULT(STDMETHODCALLTYPE *get_currentPlaylist)(IWMPPlayer *This, IWMPPlaylist **ppPL);
    HRESULT(STDMETHODCALLTYPE *put_currentPlaylist)(IWMPPlayer *This, IWMPPlaylist *pPL);
    HRESULT(STDMETHODCALLTYPE *get_cdromCollection)(IWMPPlayer *This, IWMPCdromCollection **ppCdromCollection);
    HRESULT(STDMETHODCALLTYPE *get_closedCaption)(IWMPPlayer *This, IWMPClosedCaption **ppClosedCaption);
    HRESULT(STDMETHODCALLTYPE *get_isOnline)(IWMPPlayer *This, VARIANT_BOOL *pfOnline);
    HRESULT(STDMETHODCALLTYPE *get_error)(IWMPPlayer *This, IWMPError **ppError);
    HRESULT(STDMETHODCALLTYPE *get_status)(IWMPPlayer *This, BSTR *pbstrStatus);
    HRESULT(STDMETHODCALLTYPE *get_enabled)(IWMPPlayer *This, VARIANT_BOOL *pbEnabled);
    HRESULT(STDMETHODCALLTYPE *put_enabled)(IWMPPlayer *This, VARIANT_BOOL bEnabled);
    HRESULT(STDMETHODCALLTYPE *get_fullScreen)(IWMPPlayer *This, VARIANT_BOOL *pbFullScreen);
    HRESULT(STDMETHODCALLTYPE *put_fullScreen)(IWMPPlayer *This, VARIANT_BOOL bFullScreen);
    HRESULT(STDMETHODCALLTYPE *get_enableContextMenu)(IWMPPlayer *This, VARIANT_BOOL *pbEnableContextMenu);
    HRESULT(STDMETHODCALLTYPE *put_enableContextMenu)(IWMPPlayer *This, VARIANT_BOOL bEnableContextMenu);
    HRESULT(STDMETHODCALLTYPE *put_uiMode)(IWMPPlayer *This, BSTR bstrMode);
    HRESULT(STDMETHODCALLTYPE *get_uiMode)(IWMPPlayer *This, BSTR *pbstrMode);
} IWMPPlayerVtbl;

#define IWMPPlayer_QueryInterface(This,riid,ppvObject) ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 
#define IWMPPlayer_AddRef(This) ( (This)->lpVtbl -> AddRef(This) ) 
#define IWMPPlayer_Release(This) ( (This)->lpVtbl -> Release(This) )
#define IWMPPlayer_GetTypeInfoCount(This,pctinfo) ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 
#define IWMPPlayer_GetTypeInfo(This,iTInfo,lcid,ppTInfo) ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 
#define IWMPPlayer_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 
#define IWMPPlayer_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) )
#define IWMPPlayer_close(This) ( (This)->lpVtbl -> close(This) )
#define IWMPPlayer_get_URL(This,pbstrURL) ( (This)->lpVtbl -> get_URL(This,pbstrURL) ) 
#define IWMPPlayer_put_URL(This,bstrURL) ( (This)->lpVtbl -> put_URL(This,bstrURL) ) 
#define IWMPPlayer_get_openState(This,pwmpos) ( (This)->lpVtbl -> get_openState(This,pwmpos) ) 
#define IWMPPlayer_get_playState(This,pwmpps) ( (This)->lpVtbl -> get_playState(This,pwmpps) ) 
#define IWMPPlayer_get_controls(This,ppControl) ( (This)->lpVtbl -> get_controls(This,ppControl) ) 
#define IWMPPlayer_get_settings(This,ppSettings) ( (This)->lpVtbl -> get_settings(This,ppSettings) ) 
#define IWMPPlayer_get_currentMedia(This,ppMedia) ( (This)->lpVtbl -> get_currentMedia(This,ppMedia) ) 
#define IWMPPlayer_put_currentMedia(This,pMedia) ( (This)->lpVtbl -> put_currentMedia(This,pMedia) ) 
#define IWMPPlayer_get_mediaCollection(This,ppMediaCollection) ( (This)->lpVtbl -> get_mediaCollection(This,ppMediaCollection) ) 
#define IWMPPlayer_get_playlistCollection(This,ppPlaylistCollection) ( (This)->lpVtbl -> get_playlistCollection(This,ppPlaylistCollection) ) 
#define IWMPPlayer_get_versionInfo(This,pbstrVersionInfo) ( (This)->lpVtbl -> get_versionInfo(This,pbstrVersionInfo) ) 
#define IWMPPlayer_launchURL(This,bstrURL) ( (This)->lpVtbl -> launchURL(This,bstrURL) ) 
#define IWMPPlayer_get_network(This,ppQNI) ( (This)->lpVtbl -> get_network(This,ppQNI) ) 
#define IWMPPlayer_get_currentPlaylist(This,ppPL) ( (This)->lpVtbl -> get_currentPlaylist(This,ppPL) ) 
#define IWMPPlayer_put_currentPlaylist(This,pPL) ( (This)->lpVtbl -> put_currentPlaylist(This,pPL) ) 
#define IWMPPlayer_get_cdromCollection(This,ppCdromCollection) ( (This)->lpVtbl -> get_cdromCollection(This,ppCdromCollection) ) 
#define IWMPPlayer_get_closedCaption(This,ppClosedCaption) ( (This)->lpVtbl -> get_closedCaption(This,ppClosedCaption) ) 
#define IWMPPlayer_get_isOnline(This,pfOnline) ( (This)->lpVtbl -> get_isOnline(This,pfOnline) ) 
#define IWMPPlayer_get_error(This,ppError) ( (This)->lpVtbl -> get_error(This,ppError) ) 
#define IWMPPlayer_get_status(This,pbstrStatus) ( (This)->lpVtbl -> get_status(This,pbstrStatus) )
#define IWMPPlayer_get_enabled(This,pbEnabled) ( (This)->lpVtbl -> get_enabled(This,pbEnabled) )
#define IWMPPlayer_put_enabled(This,bEnabled) ( (This)->lpVtbl -> put_enabled(This,bEnabled) ) 
#define IWMPPlayer_get_fullScreen(This,pbFullScreen) ( (This)->lpVtbl -> get_fullScreen(This,pbFullScreen) ) 
#define IWMPPlayer_put_fullScreen(This,bFullScreen) ( (This)->lpVtbl -> put_fullScreen(This,bFullScreen) ) 
#define IWMPPlayer_get_enableContextMenu(This,pbEnableContextMenu) ( (This)->lpVtbl -> get_enableContextMenu(This,pbEnableContextMenu) ) 
#define IWMPPlayer_put_enableContextMenu(This,bEnableContextMenu) ( (This)->lpVtbl -> put_enableContextMenu(This,bEnableContextMenu) ) 
#define IWMPPlayer_put_uiMode(This,bstrMode) ( (This)->lpVtbl -> put_uiMode(This,bstrMode) ) 
#define IWMPPlayer_get_uiMode(This,pbstrMode) ( (This)->lpVtbl -> get_uiMode(This,pbstrMode) )


struct IWMPPlayer {
    struct IWMPPlayerVtbl *lpVtbl;
};

typedef struct IWMPControlsVtbl {
    HRESULT(STDMETHODCALLTYPE *QueryInterface)(IWMPControls *This, REFIID riid, void **ppvObject);
    ULONG(STDMETHODCALLTYPE *AddRef)(IWMPControls *This);
    ULONG(STDMETHODCALLTYPE *Release)(IWMPControls *This);
    HRESULT(STDMETHODCALLTYPE *GetTypeInfoCount)(IWMPControls *This, UINT *pctinfo);
    HRESULT(STDMETHODCALLTYPE *GetTypeInfo)(IWMPControls *This, UINT iTInfo, LCID lcid, ITypeInfo **ppTInfo);
    HRESULT(STDMETHODCALLTYPE *GetIDsOfNames)(IWMPControls *This, REFIID riid, LPOLESTR *rgszNames, UINT cNames, LCID lcid, DISPID *rgDispId);
    HRESULT(STDMETHODCALLTYPE *Invoke)(IWMPControls *This, DISPID dispIdMember, REFIID riid, LCID lcid, WORD wFlags, DISPPARAMS *pDispParams, VARIANT *pVarResult, EXCEPINFO *pExcepInfo, UINT *puArgErr);
    HRESULT(STDMETHODCALLTYPE *get_isAvailable)(IWMPControls *This, BSTR bstrItem, VARIANT_BOOL *pIsAvailable);
    HRESULT(STDMETHODCALLTYPE *play)(IWMPControls *This);
    HRESULT(STDMETHODCALLTYPE *stop)(IWMPControls *This);
    HRESULT(STDMETHODCALLTYPE *pause)(IWMPControls *This);
    HRESULT(STDMETHODCALLTYPE *fastForward)(IWMPControls *This);
    HRESULT(STDMETHODCALLTYPE *fastReverse)(IWMPControls *This);
    HRESULT(STDMETHODCALLTYPE *get_currentPosition)(IWMPControls *This, double *pdCurrentPosition);
    HRESULT(STDMETHODCALLTYPE *put_currentPosition)(IWMPControls *This, double dCurrentPosition);
    HRESULT(STDMETHODCALLTYPE *get_currentPositionString)(IWMPControls *This, BSTR *pbstrCurrentPosition);
    HRESULT(STDMETHODCALLTYPE *next)(IWMPControls *This);
    HRESULT(STDMETHODCALLTYPE *previous)(IWMPControls *This);
    HRESULT(STDMETHODCALLTYPE *get_currentItem)(IWMPControls *This, IWMPMedia **ppIWMPMedia);
    HRESULT(STDMETHODCALLTYPE *put_currentItem)(IWMPControls *This, IWMPMedia *pIWMPMedia);
    HRESULT(STDMETHODCALLTYPE *get_currentMarker)(IWMPControls *This, long *plMarker);
    HRESULT(STDMETHODCALLTYPE *put_currentMarker)(IWMPControls *This, long lMarker);
    HRESULT(STDMETHODCALLTYPE *playItem)(IWMPControls *This, IWMPMedia *pIWMPMedia);
} IWMPControlsVtbl;

struct IWMPControls {
    struct IWMPControlsVtbl *lpVtbl;
};
 
#define IWMPControls_QueryInterface(This,riid,ppvObject) ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 
#define IWMPControls_AddRef(This) ( (This)->lpVtbl -> AddRef(This) ) 
#define IWMPControls_Release(This) ( (This)->lpVtbl -> Release(This) )
#define IWMPControls_GetTypeInfoCount(This,pctinfo) ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 
#define IWMPControls_GetTypeInfo(This,iTInfo,lcid,ppTInfo) ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 
#define IWMPControls_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 
#define IWMPControls_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) )
#define IWMPControls_get_isAvailable(This,bstrItem,pIsAvailable) ( (This)->lpVtbl -> get_isAvailable(This,bstrItem,pIsAvailable) ) 
#define IWMPControls_play(This) ( (This)->lpVtbl -> play(This) ) 
#define IWMPControls_stop(This) ( (This)->lpVtbl -> stop(This) ) 
#define IWMPControls_pause(This) ( (This)->lpVtbl -> pause(This) ) 
#define IWMPControls_fastForward(This) ( (This)->lpVtbl -> fastForward(This) ) 
#define IWMPControls_fastReverse(This) ( (This)->lpVtbl -> fastReverse(This) ) 
#define IWMPControls_get_currentPosition(This,pdCurrentPosition) ( (This)->lpVtbl -> get_currentPosition(This,pdCurrentPosition) ) 
#define IWMPControls_put_currentPosition(This,dCurrentPosition) ( (This)->lpVtbl -> put_currentPosition(This,dCurrentPosition) ) 
#define IWMPControls_get_currentPositionString(This,pbstrCurrentPosition) ( (This)->lpVtbl -> get_currentPositionString(This,pbstrCurrentPosition) ) 
#define IWMPControls_next(This) ( (This)->lpVtbl -> next(This) ) 
#define IWMPControls_previous(This) ( (This)->lpVtbl -> previous(This) ) 
#define IWMPControls_get_currentItem(This,ppIWMPMedia) ( (This)->lpVtbl -> get_currentItem(This,ppIWMPMedia) ) 
#define IWMPControls_put_currentItem(This,pIWMPMedia) ( (This)->lpVtbl -> put_currentItem(This,pIWMPMedia) ) 
#define IWMPControls_get_currentMarker(This,plMarker) ( (This)->lpVtbl -> get_currentMarker(This,plMarker) ) 
#define IWMPControls_put_currentMarker(This,lMarker) ( (This)->lpVtbl -> put_currentMarker(This,lMarker) ) 
#define IWMPControls_playItem(This,pIWMPMedia) ( (This)->lpVtbl -> playItem(This,pIWMPMedia) )

#endif
