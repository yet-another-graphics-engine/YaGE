#ifndef WMP_MINGW_H_
#define WMP_MINGW_H_

#include <windows.h>
#include <Ole2.h>

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

typedef /* [public][helpstring] */
enum WMPPlayState {
    wmppsUndefined = 0,
    wmppsStopped = (wmppsUndefined + 1),
    wmppsPaused = (wmppsStopped + 1),
    wmppsPlaying = (wmppsPaused + 1),
    wmppsScanForward = (wmppsPlaying + 1),
    wmppsScanReverse = (wmppsScanForward + 1),
    wmppsBuffering = (wmppsScanReverse + 1),
    wmppsWaiting = (wmppsBuffering + 1),
    wmppsMediaEnded = (wmppsWaiting + 1),
    wmppsTransitioning = (wmppsMediaEnded + 1),
    wmppsReady = (wmppsTransitioning + 1),
    wmppsReconnecting = (wmppsReady + 1),
    wmppsLast = (wmppsReconnecting + 1)
}     WMPPlayState;

typedef /* [public][helpstring] */
enum WMPOpenState {
    wmposUndefined = 0,
    wmposPlaylistChanging = (wmposUndefined + 1),
    wmposPlaylistLocating = (wmposPlaylistChanging + 1),
    wmposPlaylistConnecting = (wmposPlaylistLocating + 1),
    wmposPlaylistLoading = (wmposPlaylistConnecting + 1),
    wmposPlaylistOpening = (wmposPlaylistLoading + 1),
    wmposPlaylistOpenNoMedia = (wmposPlaylistOpening + 1),
    wmposPlaylistChanged = (wmposPlaylistOpenNoMedia + 1),
    wmposMediaChanging = (wmposPlaylistChanged + 1),
    wmposMediaLocating = (wmposMediaChanging + 1),
    wmposMediaConnecting = (wmposMediaLocating + 1),
    wmposMediaLoading = (wmposMediaConnecting + 1),
    wmposMediaOpening = (wmposMediaLoading + 1),
    wmposMediaOpen = (wmposMediaOpening + 1),
    wmposBeginCodecAcquisition = (wmposMediaOpen + 1),
    wmposEndCodecAcquisition = (wmposBeginCodecAcquisition + 1),
    wmposBeginLicenseAcquisition = (wmposEndCodecAcquisition + 1),
    wmposEndLicenseAcquisition = (wmposBeginLicenseAcquisition + 1),
    wmposBeginIndividualization = (wmposEndLicenseAcquisition + 1),
    wmposEndIndividualization = (wmposBeginIndividualization + 1),
    wmposMediaWaiting = (wmposEndIndividualization + 1),
    wmposOpeningUnknownURL = (wmposMediaWaiting + 1)
}     WMPOpenState;

typedef struct IWMPPlayerVtbl {
        HRESULT(STDMETHODCALLTYPE *QueryInterface)(
        IWMPPlayer * This,
        /* [in] */ REFIID riid,
        /* [annotation][iid_is][out] */
        void **ppvObject);

        ULONG(STDMETHODCALLTYPE *AddRef)(
            IWMPPlayer * This);

        ULONG(STDMETHODCALLTYPE *Release)(
            IWMPPlayer * This);

        HRESULT(STDMETHODCALLTYPE *GetTypeInfoCount)(
            IWMPPlayer * This,
            /* [out] */ UINT *pctinfo);

        HRESULT(STDMETHODCALLTYPE *GetTypeInfo)(
            IWMPPlayer * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);

        HRESULT(STDMETHODCALLTYPE *GetIDsOfNames)(
            IWMPPlayer * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);

        /* [local] */ HRESULT(STDMETHODCALLTYPE *Invoke)(
            IWMPPlayer * This,
            /* [annotation][in] */
            DISPID dispIdMember,
            /* [annotation][in] */
            REFIID riid,
            /* [annotation][in] */
            LCID lcid,
            /* [annotation][in] */
            WORD wFlags,
            /* [annotation][out][in] */
            DISPPARAMS *pDispParams,
            /* [annotation][out] */
            VARIANT *pVarResult,
            /* [annotation][out] */
            EXCEPINFO *pExcepInfo,
            /* [annotation][out] */
            UINT *puArgErr);

        /* [helpstring][id] */ HRESULT(STDMETHODCALLTYPE *close)(
            IWMPPlayer * This);

        /* [helpstring][propget][id] */ HRESULT(STDMETHODCALLTYPE *get_URL)(
            IWMPPlayer * This,
            /* [retval][out] */ BSTR *pbstrURL);

        /* [propput][id] */ HRESULT(STDMETHODCALLTYPE *put_URL)(
            IWMPPlayer * This,
            /* [in] */ BSTR bstrURL);

        /* [helpstring][propget][id] */ HRESULT(STDMETHODCALLTYPE *get_openState)(
            IWMPPlayer * This,
            /* [retval][out] */ WMPOpenState  *pwmpos);

        /* [helpstring][propget][id] */ HRESULT(STDMETHODCALLTYPE *get_playState)(
            IWMPPlayer * This,
            /* [retval][out] */ WMPPlayState *pwmpps);

        /* [helpstring][propget][id] */ HRESULT(STDMETHODCALLTYPE *get_controls)(
            IWMPPlayer * This,
            /* [retval][out] */ IWMPControls **ppControl);

        /* [helpstring][propget][id] */ HRESULT(STDMETHODCALLTYPE *get_settings)(
            IWMPPlayer * This,
            /* [retval][out] */ IWMPSettings **ppSettings);

        /* [helpstring][propget][id] */ HRESULT(STDMETHODCALLTYPE *get_currentMedia)(
            IWMPPlayer * This,
            /* [retval][out] */ IWMPMedia **ppMedia);

        /* [propput][id] */ HRESULT(STDMETHODCALLTYPE *put_currentMedia)(
            IWMPPlayer * This,
            /* [in] */ IWMPMedia *pMedia);

        /* [helpstring][propget][id] */ HRESULT(STDMETHODCALLTYPE *get_mediaCollection)(
            IWMPPlayer * This,
            /* [retval][out] */ IWMPMediaCollection **ppMediaCollection);

        /* [helpstring][propget][id] */ HRESULT(STDMETHODCALLTYPE *get_playlistCollection)(
            IWMPPlayer * This,
            /* [retval][out] */ IWMPPlaylistCollection **ppPlaylistCollection);

        /* [helpstring][propget][id] */ HRESULT(STDMETHODCALLTYPE *get_versionInfo)(
            IWMPPlayer * This,
            /* [retval][out] */ BSTR *pbstrVersionInfo);

        /* [id] */ HRESULT(STDMETHODCALLTYPE *launchURL)(
            IWMPPlayer * This,
            /* [in] */ BSTR bstrURL);

        /* [helpstring][id][propget] */ HRESULT(STDMETHODCALLTYPE *get_network)(
            IWMPPlayer * This,
            /* [retval][out] */ IWMPNetwork **ppQNI);

        /* [helpstring][propget][id] */ HRESULT(STDMETHODCALLTYPE *get_currentPlaylist)(
            IWMPPlayer * This,
            /* [retval][out] */ IWMPPlaylist **ppPL);

        /* [helpstring][propput][id] */ HRESULT(STDMETHODCALLTYPE *put_currentPlaylist)(
            IWMPPlayer * This,
            /* [in] */ IWMPPlaylist *pPL);

        /* [helpstring][propget][id] */ HRESULT(STDMETHODCALLTYPE *get_cdromCollection)(
            IWMPPlayer * This,
            /* [retval][out] */ IWMPCdromCollection **ppCdromCollection);

        /* [helpstring][propget][id] */ HRESULT(STDMETHODCALLTYPE *get_closedCaption)(
            IWMPPlayer * This,
            /* [retval][out] */ IWMPClosedCaption **ppClosedCaption);

        /* [helpstring][propget][id] */ HRESULT(STDMETHODCALLTYPE *get_isOnline)(
            IWMPPlayer * This,
            /* [retval][out] */ VARIANT_BOOL *pfOnline);

        /* [helpstring][propget][id] */ HRESULT(STDMETHODCALLTYPE *get_error)(
            IWMPPlayer * This,
            /* [retval][out] */ IWMPError **ppError);

        /* [helpstring][propget][id] */ HRESULT(STDMETHODCALLTYPE *get_status)(
            IWMPPlayer * This,
            /* [retval][out] */ BSTR *pbstrStatus);

        /* [helpstring][propget][id] */ HRESULT(STDMETHODCALLTYPE *get_enabled)(
            IWMPPlayer * This,
            /* [retval][out] */ VARIANT_BOOL *pbEnabled);

        /* [helpstring][propput][id] */ HRESULT(STDMETHODCALLTYPE *put_enabled)(
            IWMPPlayer * This,
            /* [in] */ VARIANT_BOOL bEnabled);

        /* [helpstring][propget][id] */ HRESULT(STDMETHODCALLTYPE *get_fullScreen)(
            IWMPPlayer * This,
            /* [retval][out] */ VARIANT_BOOL *pbFullScreen);

        /* [helpstring][propput][id] */ HRESULT(STDMETHODCALLTYPE *put_fullScreen)(
            IWMPPlayer * This,
            VARIANT_BOOL bFullScreen);

        /* [helpstring][propget][id] */ HRESULT(STDMETHODCALLTYPE *get_enableContextMenu)(
            IWMPPlayer * This,
            /* [retval][out] */ VARIANT_BOOL *pbEnableContextMenu);

        /* [helpstring][propput][id] */ HRESULT(STDMETHODCALLTYPE *put_enableContextMenu)(
            IWMPPlayer * This,
            VARIANT_BOOL bEnableContextMenu);

        /* [helpstring][propput][id] */ HRESULT(STDMETHODCALLTYPE *put_uiMode)(
            IWMPPlayer * This,
            /* [in] */ BSTR bstrMode);

        /* [helpstring][propget][id] */ HRESULT(STDMETHODCALLTYPE *get_uiMode)(
            IWMPPlayer * This,
            /* [retval][out] */ BSTR *pbstrMode);


} IWMPPlayerVtbl;


#define IWMPPlayer_QueryInterface(This,riid,ppvObject)    \
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) )

#define IWMPPlayer_AddRef(This)    \
    ( (This)->lpVtbl -> AddRef(This) )

#define IWMPPlayer_Release(This)    \
    ( (This)->lpVtbl -> Release(This) )


#define IWMPPlayer_GetTypeInfoCount(This,pctinfo)    \
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) )

#define IWMPPlayer_GetTypeInfo(This,iTInfo,lcid,ppTInfo)    \
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) )

#define IWMPPlayer_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)    \
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) )

#define IWMPPlayer_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)    \
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) )


#define IWMPPlayer_close(This)    \
    ( (This)->lpVtbl -> close(This) )

#define IWMPPlayer_get_URL(This,pbstrURL)    \
    ( (This)->lpVtbl -> get_URL(This,pbstrURL) )

#define IWMPPlayer_put_URL(This,bstrURL)    \
    ( (This)->lpVtbl -> put_URL(This,bstrURL) )

#define IWMPPlayer_get_openState(This,pwmpos)    \
    ( (This)->lpVtbl -> get_openState(This,pwmpos) )

#define IWMPPlayer_get_playState(This,pwmpps)    \
    ( (This)->lpVtbl -> get_playState(This,pwmpps) )

#define IWMPPlayer_get_controls(This,ppControl)    \
    ( (This)->lpVtbl -> get_controls(This,ppControl) )

#define IWMPPlayer_get_settings(This,ppSettings)    \
    ( (This)->lpVtbl -> get_settings(This,ppSettings) )

#define IWMPPlayer_get_currentMedia(This,ppMedia)    \
    ( (This)->lpVtbl -> get_currentMedia(This,ppMedia) )

#define IWMPPlayer_put_currentMedia(This,pMedia)    \
    ( (This)->lpVtbl -> put_currentMedia(This,pMedia) )

#define IWMPPlayer_get_mediaCollection(This,ppMediaCollection)    \
    ( (This)->lpVtbl -> get_mediaCollection(This,ppMediaCollection) )

#define IWMPPlayer_get_playlistCollection(This,ppPlaylistCollection)    \
    ( (This)->lpVtbl -> get_playlistCollection(This,ppPlaylistCollection) )

#define IWMPPlayer_get_versionInfo(This,pbstrVersionInfo)    \
    ( (This)->lpVtbl -> get_versionInfo(This,pbstrVersionInfo) )

#define IWMPPlayer_launchURL(This,bstrURL)    \
    ( (This)->lpVtbl -> launchURL(This,bstrURL) )

#define IWMPPlayer_get_network(This,ppQNI)    \
    ( (This)->lpVtbl -> get_network(This,ppQNI) )

#define IWMPPlayer_get_currentPlaylist(This,ppPL)    \
    ( (This)->lpVtbl -> get_currentPlaylist(This,ppPL) )

#define IWMPPlayer_put_currentPlaylist(This,pPL)    \
    ( (This)->lpVtbl -> put_currentPlaylist(This,pPL) )

#define IWMPPlayer_get_cdromCollection(This,ppCdromCollection)    \
    ( (This)->lpVtbl -> get_cdromCollection(This,ppCdromCollection) )

#define IWMPPlayer_get_closedCaption(This,ppClosedCaption)    \
    ( (This)->lpVtbl -> get_closedCaption(This,ppClosedCaption) )

#define IWMPPlayer_get_isOnline(This,pfOnline)    \
    ( (This)->lpVtbl -> get_isOnline(This,pfOnline) )

#define IWMPPlayer_get_error(This,ppError)    \
    ( (This)->lpVtbl -> get_error(This,ppError) )

#define IWMPPlayer_get_status(This,pbstrStatus)    \
    ( (This)->lpVtbl -> get_status(This,pbstrStatus) )


#define IWMPPlayer_get_enabled(This,pbEnabled)    \
    ( (This)->lpVtbl -> get_enabled(This,pbEnabled) )

#define IWMPPlayer_put_enabled(This,bEnabled)    \
    ( (This)->lpVtbl -> put_enabled(This,bEnabled) )

#define IWMPPlayer_get_fullScreen(This,pbFullScreen)    \
    ( (This)->lpVtbl -> get_fullScreen(This,pbFullScreen) )

#define IWMPPlayer_put_fullScreen(This,bFullScreen)    \
    ( (This)->lpVtbl -> put_fullScreen(This,bFullScreen) )

#define IWMPPlayer_get_enableContextMenu(This,pbEnableContextMenu)    \
    ( (This)->lpVtbl -> get_enableContextMenu(This,pbEnableContextMenu) )

#define IWMPPlayer_put_enableContextMenu(This,bEnableContextMenu)    \
    ( (This)->lpVtbl -> put_enableContextMenu(This,bEnableContextMenu) )

#define IWMPPlayer_put_uiMode(This,bstrMode)    \
    ( (This)->lpVtbl -> put_uiMode(This,bstrMode) )

#define IWMPPlayer_get_uiMode(This,pbstrMode)    \
    ( (This)->lpVtbl -> get_uiMode(This,pbstrMode) )



struct IWMPPlayer {
    struct IWMPPlayerVtbl *lpVtbl;
};

typedef struct IWMPControlsVtbl {
    BEGIN_INTERFACE

        HRESULT(STDMETHODCALLTYPE *QueryInterface)(
        IWMPControls * This,
        /* [in] */ REFIID riid,
        /* [annotation][iid_is][out] */
        void **ppvObject);

        ULONG(STDMETHODCALLTYPE *AddRef)(
            IWMPControls * This);

        ULONG(STDMETHODCALLTYPE *Release)(
            IWMPControls * This);

        HRESULT(STDMETHODCALLTYPE *GetTypeInfoCount)(
            IWMPControls * This,
            /* [out] */ UINT *pctinfo);

        HRESULT(STDMETHODCALLTYPE *GetTypeInfo)(
            IWMPControls * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);

        HRESULT(STDMETHODCALLTYPE *GetIDsOfNames)(
            IWMPControls * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);

        /* [local] */ HRESULT(STDMETHODCALLTYPE *Invoke)(
            IWMPControls * This,
            /* [annotation][in] */
            DISPID dispIdMember,
            /* [annotation][in] */
            REFIID riid,
            /* [annotation][in] */
            LCID lcid,
            /* [annotation][in] */
            WORD wFlags,
            /* [annotation][out][in] */
            DISPPARAMS *pDispParams,
            /* [annotation][out] */
            VARIANT *pVarResult,
            /* [annotation][out] */
            EXCEPINFO *pExcepInfo,
            /* [annotation][out] */
            UINT *puArgErr);

        /* [helpstring][propget][id] */ HRESULT(STDMETHODCALLTYPE *get_isAvailable)(
            IWMPControls * This,
            /* [in] */ BSTR bstrItem,
            /* [retval][out] */ VARIANT_BOOL *pIsAvailable);

        /* [helpstring][id] */ HRESULT(STDMETHODCALLTYPE *play)(
            IWMPControls * This);

        /* [helpstring][id] */ HRESULT(STDMETHODCALLTYPE *stop)(
            IWMPControls * This);

        /* [helpstring][id] */ HRESULT(STDMETHODCALLTYPE *pause)(
            IWMPControls * This);

        /* [helpstring][id] */ HRESULT(STDMETHODCALLTYPE *fastForward)(
            IWMPControls * This);

        /* [helpstring][id] */ HRESULT(STDMETHODCALLTYPE *fastReverse)(
            IWMPControls * This);

        /* [helpstring][propget][id] */ HRESULT(STDMETHODCALLTYPE *get_currentPosition)(
            IWMPControls * This,
            /* [retval][out] */ double *pdCurrentPosition);

        /* [helpstring][propput][id] */ HRESULT(STDMETHODCALLTYPE *put_currentPosition)(
            IWMPControls * This,
            /* [in] */ double dCurrentPosition);

        /* [helpstring][propget][id] */ HRESULT(STDMETHODCALLTYPE *get_currentPositionString)(
            IWMPControls * This,
            /* [retval][out] */ BSTR *pbstrCurrentPosition);

        /* [helpstring][id] */ HRESULT(STDMETHODCALLTYPE *next)(
            IWMPControls * This);

        /* [helpstring][id] */ HRESULT(STDMETHODCALLTYPE *previous)(
            IWMPControls * This);

        /* [helpstring][propget][id] */ HRESULT(STDMETHODCALLTYPE *get_currentItem)(
            IWMPControls * This,
            /* [retval][out] */ IWMPMedia **ppIWMPMedia);

        /* [propput][id] */ HRESULT(STDMETHODCALLTYPE *put_currentItem)(
            IWMPControls * This,
            /* [in] */ IWMPMedia *pIWMPMedia);

        /* [helpstring][propget][id] */ HRESULT(STDMETHODCALLTYPE *get_currentMarker)(
            IWMPControls * This,
            /* [retval][out] */ long *plMarker);

        /* [helpstring][propput][id] */ HRESULT(STDMETHODCALLTYPE *put_currentMarker)(
            IWMPControls * This,
            /* [in] */ long lMarker);

        /* [helpstring][id] */ HRESULT(STDMETHODCALLTYPE *playItem)(
            IWMPControls * This,
            /* [in] */ IWMPMedia *pIWMPMedia);

    END_INTERFACE
} IWMPControlsVtbl;

struct IWMPControls {
    struct IWMPControlsVtbl *lpVtbl;
};



#define IWMPControls_QueryInterface(This,riid,ppvObject)    \
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) )

#define IWMPControls_AddRef(This)    \
    ( (This)->lpVtbl -> AddRef(This) )

#define IWMPControls_Release(This)    \
    ( (This)->lpVtbl -> Release(This) )


#define IWMPControls_GetTypeInfoCount(This,pctinfo)    \
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) )

#define IWMPControls_GetTypeInfo(This,iTInfo,lcid,ppTInfo)    \
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) )

#define IWMPControls_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)    \
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) )

#define IWMPControls_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)    \
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) )


#define IWMPControls_get_isAvailable(This,bstrItem,pIsAvailable)    \
    ( (This)->lpVtbl -> get_isAvailable(This,bstrItem,pIsAvailable) )

#define IWMPControls_play(This)    \
    ( (This)->lpVtbl -> play(This) )

#define IWMPControls_stop(This)    \
    ( (This)->lpVtbl -> stop(This) )

#define IWMPControls_pause(This)    \
    ( (This)->lpVtbl -> pause(This) )

#define IWMPControls_fastForward(This)    \
    ( (This)->lpVtbl -> fastForward(This) )

#define IWMPControls_fastReverse(This)    \
    ( (This)->lpVtbl -> fastReverse(This) )

#define IWMPControls_get_currentPosition(This,pdCurrentPosition)    \
    ( (This)->lpVtbl -> get_currentPosition(This,pdCurrentPosition) )

#define IWMPControls_put_currentPosition(This,dCurrentPosition)    \
    ( (This)->lpVtbl -> put_currentPosition(This,dCurrentPosition) )

#define IWMPControls_get_currentPositionString(This,pbstrCurrentPosition)    \
    ( (This)->lpVtbl -> get_currentPositionString(This,pbstrCurrentPosition) )

#define IWMPControls_next(This)    \
    ( (This)->lpVtbl -> next(This) )

#define IWMPControls_previous(This)    \
    ( (This)->lpVtbl -> previous(This) )

#define IWMPControls_get_currentItem(This,ppIWMPMedia)    \
    ( (This)->lpVtbl -> get_currentItem(This,ppIWMPMedia) )

#define IWMPControls_put_currentItem(This,pIWMPMedia)    \
    ( (This)->lpVtbl -> put_currentItem(This,pIWMPMedia) )

#define IWMPControls_get_currentMarker(This,plMarker)    \
    ( (This)->lpVtbl -> get_currentMarker(This,plMarker) )

#define IWMPControls_put_currentMarker(This,lMarker)    \
    ( (This)->lpVtbl -> put_currentMarker(This,lMarker) )

#define IWMPControls_playItem(This,pIWMPMedia)    \
    ( (This)->lpVtbl -> playItem(This,pIWMPMedia) )


#endif
