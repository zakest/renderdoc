/******************************************************************************
 * The MIT License (MIT)
 * 
 * Copyright (c) 2014 Crytek
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 ******************************************************************************/


#pragma once

#include <stdint.h>
#include <math.h>

#include "basic_types.h"

#ifdef WIN32

#ifdef RENDERDOC_EXPORTS
#define RENDERDOC_API __declspec(dllexport)
#else
#define RENDERDOC_API __declspec(dllimport)
#endif
#define RENDERDOC_CC __cdecl

#elif defined(LINUX)

#ifdef RENDERDOC_EXPORTS
#define RENDERDOC_API __attribute__ ((visibility ("default")))
#else
#define RENDERDOC_API
#endif

#define RENDERDOC_CC

#else

#error "Unknown platform"

#endif

#include "capture_options.h"

#include "replay_enums.h"

#include "shader_types.h"
#include "data_types.h"
#include "control_types.h"

#include "d3d11_pipestate.h"
#include "gl_pipestate.h"

#ifdef RENDERDOC_EXPORTS
struct ReplayOutput;
#else
struct ReplayOutput { };
#endif

extern "C" RENDERDOC_API bool RENDERDOC_CC ReplayOutput_SetOutputConfig(ReplayOutput *output, const OutputConfig &o);
extern "C" RENDERDOC_API bool RENDERDOC_CC ReplayOutput_SetTextureDisplay(ReplayOutput *output, const TextureDisplay &o);
extern "C" RENDERDOC_API bool RENDERDOC_CC ReplayOutput_SetMeshDisplay(ReplayOutput *output, const MeshDisplay &o);

extern "C" RENDERDOC_API bool RENDERDOC_CC ReplayOutput_ClearThumbnails(ReplayOutput *output);
extern "C" RENDERDOC_API bool RENDERDOC_CC ReplayOutput_AddThumbnail(ReplayOutput *output, void *wnd, ResourceId texID);

extern "C" RENDERDOC_API bool RENDERDOC_CC ReplayOutput_Display(ReplayOutput *output);

extern "C" RENDERDOC_API bool RENDERDOC_CC ReplayOutput_SetPixelContext(ReplayOutput *output, void *wnd);
extern "C" RENDERDOC_API bool RENDERDOC_CC ReplayOutput_SetPixelContextLocation(ReplayOutput *output, uint32_t x, uint32_t y);
extern "C" RENDERDOC_API void RENDERDOC_CC ReplayOutput_DisablePixelContext(ReplayOutput *output);

extern "C" RENDERDOC_API bool RENDERDOC_CC ReplayOutput_PickPixel(ReplayOutput *output, ResourceId texID, bool customShader,
														uint32_t x, uint32_t y, uint32_t sliceFace, uint32_t mip, PixelValue *val);

#ifdef RENDERDOC_EXPORTS
struct ReplayRenderer;
#else
struct ReplayRenderer { };
#endif

extern "C" RENDERDOC_API void RENDERDOC_CC ReplayRenderer_GetAPIProperties(ReplayRenderer *rend, APIProperties *props);

extern "C" RENDERDOC_API ReplayOutput* RENDERDOC_CC ReplayRenderer_CreateOutput(ReplayRenderer *rend, void *handle);
extern "C" RENDERDOC_API void RENDERDOC_CC ReplayRenderer_Shutdown(ReplayRenderer *rend);
extern "C" RENDERDOC_API void RENDERDOC_CC ReplayRenderer_ShutdownOutput(ReplayRenderer *rend, ReplayOutput *output);

extern "C" RENDERDOC_API bool RENDERDOC_CC ReplayRenderer_HasCallstacks(ReplayRenderer *rend);
extern "C" RENDERDOC_API bool RENDERDOC_CC ReplayRenderer_InitResolver(ReplayRenderer *rend);
 
extern "C" RENDERDOC_API bool RENDERDOC_CC ReplayRenderer_SetContextFilter(ReplayRenderer *rend, ResourceId id, uint32_t firstDefEv, uint32_t lastDefEv);
extern "C" RENDERDOC_API bool RENDERDOC_CC ReplayRenderer_SetFrameEvent(ReplayRenderer *rend, uint32_t frameID, uint32_t eventID);
extern "C" RENDERDOC_API bool RENDERDOC_CC ReplayRenderer_GetD3D11PipelineState(ReplayRenderer *rend, D3D11PipelineState *state);
extern "C" RENDERDOC_API bool RENDERDOC_CC ReplayRenderer_GetGLPipelineState(ReplayRenderer *rend, GLPipelineState *state);

extern "C" RENDERDOC_API bool RENDERDOC_CC ReplayRenderer_BuildCustomShader(ReplayRenderer *rend, const wchar_t *entry, const wchar_t *source, const uint32_t compileFlags, ShaderStageType type, ResourceId *shaderID, rdctype::wstr *errors);
extern "C" RENDERDOC_API bool RENDERDOC_CC ReplayRenderer_FreeCustomShader(ReplayRenderer *rend, ResourceId id);

extern "C" RENDERDOC_API bool RENDERDOC_CC ReplayRenderer_BuildTargetShader(ReplayRenderer *rend, const wchar_t *entry, const wchar_t *source, const uint32_t compileFlags, ShaderStageType type, ResourceId *shaderID, rdctype::wstr *errors);
extern "C" RENDERDOC_API bool RENDERDOC_CC ReplayRenderer_ReplaceResource(ReplayRenderer *rend, ResourceId from, ResourceId to);
extern "C" RENDERDOC_API bool RENDERDOC_CC ReplayRenderer_RemoveReplacement(ReplayRenderer *rend, ResourceId id);
extern "C" RENDERDOC_API bool RENDERDOC_CC ReplayRenderer_FreeTargetResource(ReplayRenderer *rend, ResourceId id);

extern "C" RENDERDOC_API bool RENDERDOC_CC ReplayRenderer_GetFrameInfo(ReplayRenderer *rend, rdctype::array<FetchFrameInfo> *frame);
extern "C" RENDERDOC_API bool RENDERDOC_CC ReplayRenderer_GetDrawcalls(ReplayRenderer *rend, uint32_t frameID, bool includeTimes, rdctype::array<FetchDrawcall> *draws);
extern "C" RENDERDOC_API bool RENDERDOC_CC ReplayRenderer_GetTextures(ReplayRenderer *rend, rdctype::array<FetchTexture> *texs);
extern "C" RENDERDOC_API bool RENDERDOC_CC ReplayRenderer_GetBuffers(ReplayRenderer *rend, rdctype::array<FetchBuffer> *bufs);
extern "C" RENDERDOC_API bool RENDERDOC_CC ReplayRenderer_GetResolve(ReplayRenderer *rend, uint64_t *callstack, uint32_t callstackLen, rdctype::array<rdctype::wstr> *trace);
extern "C" RENDERDOC_API ShaderReflection* RENDERDOC_CC ReplayRenderer_GetShaderDetails(ReplayRenderer *rend, ResourceId shader);

extern "C" RENDERDOC_API bool RENDERDOC_CC ReplayRenderer_VSGetDebugStates(ReplayRenderer *rend, uint32_t vertid, uint32_t instid, uint32_t idx, uint32_t instOffset, uint32_t vertOffset, ShaderDebugTrace *trace);
extern "C" RENDERDOC_API bool RENDERDOC_CC ReplayRenderer_PSGetDebugStates(ReplayRenderer *rend, uint32_t x, uint32_t y, ShaderDebugTrace *trace);
extern "C" RENDERDOC_API bool RENDERDOC_CC ReplayRenderer_CSGetDebugStates(ReplayRenderer *rend, uint32_t groupid[3], uint32_t threadid[3], ShaderDebugTrace *trace);

extern "C" RENDERDOC_API bool RENDERDOC_CC ReplayRenderer_GetUsage(ReplayRenderer *rend, ResourceId id, rdctype::array<EventUsage> *usage);

extern "C" RENDERDOC_API bool RENDERDOC_CC ReplayRenderer_GetCBufferVariableContents(ReplayRenderer *rend, ResourceId shader, uint32_t cbufslot, ResourceId buffer, uint32_t offs, rdctype::array<ShaderVariable> *vars);

extern "C" RENDERDOC_API bool RENDERDOC_CC ReplayRenderer_SaveTexture(ReplayRenderer *rend, ResourceId texID, uint32_t mip, const wchar_t *path);

extern "C" RENDERDOC_API bool RENDERDOC_CC ReplayRenderer_GetPostVSData(ReplayRenderer *rend, MeshDataStage stage, PostVSMeshData *data);

extern "C" RENDERDOC_API bool RENDERDOC_CC ReplayRenderer_GetMinMax(ReplayRenderer *rend, ResourceId tex, uint32_t sliceFace, uint32_t mip, PixelValue *minval, PixelValue *maxval);
extern "C" RENDERDOC_API bool RENDERDOC_CC ReplayRenderer_GetHistogram(ReplayRenderer *rend, ResourceId tex, uint32_t sliceFace, uint32_t mip, float minval, float maxval, bool channels[4], rdctype::array<uint32_t> *histogram);

extern "C" RENDERDOC_API bool RENDERDOC_CC ReplayRenderer_GetBufferData(ReplayRenderer *rend, ResourceId buff, uint32_t offset, uint32_t len, rdctype::array<byte> *data);

#ifdef RENDERDOC_EXPORTS
struct RemoteAccess;
#else
struct RemoteAccess { };
#endif

extern "C" RENDERDOC_API void RENDERDOC_CC RemoteAccess_Shutdown(RemoteAccess *access);
 
extern "C" RENDERDOC_API const wchar_t* RENDERDOC_CC RemoteAccess_GetTarget(RemoteAccess *access);
extern "C" RENDERDOC_API const wchar_t* RENDERDOC_CC RemoteAccess_GetAPI(RemoteAccess *access);
extern "C" RENDERDOC_API const wchar_t* RENDERDOC_CC RemoteAccess_GetBusyClient(RemoteAccess *access);

extern "C" RENDERDOC_API void RENDERDOC_CC RemoteAccess_TriggerCapture(RemoteAccess *access);
extern "C" RENDERDOC_API void RENDERDOC_CC RemoteAccess_QueueCapture(RemoteAccess *access, uint32_t frameNumber);
extern "C" RENDERDOC_API void RENDERDOC_CC RemoteAccess_CopyCapture(RemoteAccess *access, uint32_t remoteID, const wchar_t *localpath);

extern "C" RENDERDOC_API void RENDERDOC_CC RemoteAccess_ReceiveMessage(RemoteAccess *access, RemoteMessage *msg);

#ifdef RENDERDOC_EXPORTS
struct RemoteRenderer;
#else
struct RemoteRenderer { };
#endif

extern "C" RENDERDOC_API void RENDERDOC_CC RemoteRenderer_Shutdown(RemoteRenderer *remote);
 
extern "C" RENDERDOC_API bool RENDERDOC_CC RemoteRenderer_LocalProxies(RemoteRenderer *remote, rdctype::array<rdctype::wstr> *out);
extern "C" RENDERDOC_API bool RENDERDOC_CC RemoteRenderer_RemoteSupportedReplays(RemoteRenderer *remote, rdctype::array<rdctype::wstr> *out);

extern "C" RENDERDOC_API ReplayCreateStatus RENDERDOC_CC RemoteRenderer_CreateProxyRenderer(RemoteRenderer *remote, uint32_t proxyid, const wchar_t *logfile, float *progress, ReplayRenderer **rend);

//////////////////////////////////////////////////////////////////////////
// Maths/format related exports
//////////////////////////////////////////////////////////////////////////

extern "C" RENDERDOC_API float RENDERDOC_CC Maths_HalfToFloat(uint16_t half);
extern "C" RENDERDOC_API uint16_t RENDERDOC_CC Maths_FloatToHalf(float f);

extern "C" RENDERDOC_API void RENDERDOC_CC Maths_CameraArcball(float dist, const FloatVector &rot, FloatVector *pos, FloatVector *fwd, FloatVector *right);
extern "C" RENDERDOC_API void RENDERDOC_CC Maths_CameraFPSLook(const FloatVector &lookpos, const FloatVector &rot, FloatVector *pos, FloatVector *fwd, FloatVector *right);

//////////////////////////////////////////////////////////////////////////
// Create a replay renderer, for playback and analysis.
//
// Takes the filename of the log. Returns NULL in the case of any error.
//////////////////////////////////////////////////////////////////////////

extern "C" RENDERDOC_API bool RENDERDOC_CC RENDERDOC_SupportLocalReplay(const wchar_t *logfile, rdctype::wstr *driverName);
typedef bool (RENDERDOC_CC *pRENDERDOC_SupportLocalReplay)(const wchar_t *logfile, rdctype::wstr *driverName);

extern "C" RENDERDOC_API ReplayCreateStatus RENDERDOC_CC RENDERDOC_CreateReplayRenderer(const wchar_t *logfile, float *progress, ReplayRenderer **rend);
typedef ReplayCreateStatus (RENDERDOC_CC *pRENDERDOC_CreateReplayRenderer)(const wchar_t *logfile, float *progress, ReplayRenderer **rend);

//////////////////////////////////////////////////////////////////////////
// Injection/voluntary capture functions.
//
// InjectAndExecute takes an exe path, destination filename and capture options.
// It will launch the exe and then call...
//
// InjectIntoProcess will inject RenderDoc and its dependent dlls into the target process
// if it's able to, and pass in the given options. NOTE: RenderDoc automatically hooks
// any app the dll is loaded into, except where explicitly disallowed or disabled.
//
// SetLogfile and SetCaptureOptions will set the destination filename of any capture
// and the configuration options, respectively.
//
// Takes the filename of the log. Returns NULL in the case of any error.
//////////////////////////////////////////////////////////////////////////

extern "C" RENDERDOC_API void RENDERDOC_CC RENDERDOC_SetLogFile(const wchar_t *logfile);
typedef void (RENDERDOC_CC *pRENDERDOC_SetLogFile)(const wchar_t *logfile);

extern "C" RENDERDOC_API void RENDERDOC_CC RENDERDOC_SetCaptureOptions(const CaptureOptions *opts);
typedef void (RENDERDOC_CC *pRENDERDOC_SetCaptureOptions)(const CaptureOptions *opts);

extern "C" RENDERDOC_API uint32_t RENDERDOC_CC RENDERDOC_ExecuteAndInject(const wchar_t *app, const wchar_t *workingDir, const wchar_t *cmdLine,
																	const wchar_t *logfile, const CaptureOptions *opts, bool waitForExit);
typedef uint32_t (RENDERDOC_CC *pRENDERDOC_ExecuteAndInject)(const wchar_t *app, const wchar_t *workingDir, const wchar_t *cmdLine,
														 const wchar_t *logfile, const CaptureOptions *opts, bool waitForExit);
     
extern "C" RENDERDOC_API uint32_t RENDERDOC_CC RENDERDOC_InjectIntoProcess(uint32_t pid, const wchar_t *logfile, const CaptureOptions *opts, bool waitForExit);
typedef uint32_t (RENDERDOC_CC *pRENDERDOC_InjectIntoProcess)(uint32_t pid, const wchar_t *logfile, const CaptureOptions *opts, bool waitForExit);

extern "C" RENDERDOC_API void RENDERDOC_CC RENDERDOC_TriggerCapture();
typedef void (RENDERDOC_CC *pRENDERDOC_TriggerCapture)();

//////////////////////////////////////////////////////////////////////////
// Remote access and control
//////////////////////////////////////////////////////////////////////////

extern "C" RENDERDOC_API void RENDERDOC_CC RENDERDOC_InitRemoteAccess(uint32_t *ident);
typedef void (RENDERDOC_CC *pRENDERDOC_InitRemoteAccess)(uint32_t *ident);

extern "C" RENDERDOC_API RemoteAccess* RENDERDOC_CC RENDERDOC_CreateRemoteAccessConnection(const wchar_t *host, uint32_t ident, const wchar_t *clientName, bool forceConnection);
typedef RemoteAccess* (RENDERDOC_CC *pRENDERDOC_CreateRemoteAccessConnection)(const wchar_t *host, uint32_t ident, const wchar_t *clientName, bool forceConnection);

extern "C" RENDERDOC_API uint32_t RENDERDOC_CC RENDERDOC_EnumerateRemoteConnections(const wchar_t *host, uint32_t *idents);
typedef uint32_t (RENDERDOC_CC *pRENDERDOC_EnumerateRemoteConnections)(const wchar_t *host, uint32_t *idents);

extern "C" RENDERDOC_API ReplayCreateStatus RENDERDOC_CC RENDERDOC_CreateRemoteReplayConnection(const wchar_t *host, RemoteRenderer **rend);
typedef ReplayCreateStatus (RENDERDOC_CC *pRENDERDOC_CreateRemoteReplayConnection)(const wchar_t *host, RemoteRenderer **rend);

extern "C" RENDERDOC_API void RENDERDOC_CC RENDERDOC_SpawnReplayHost(volatile bool *killReplay);
typedef void (RENDERDOC_CC *pRENDERDOC_SpawnReplayHost)(volatile bool *killReplay);

//////////////////////////////////////////////////////////////////////////
// Miscellaneous!
//////////////////////////////////////////////////////////////////////////

extern "C" RENDERDOC_API void RENDERDOC_CC RENDERDOC_TriggerExceptionHandler(void *exceptionPtrs, bool crashed);
typedef void (RENDERDOC_CC *pRENDERDOC_TriggerExceptionHandler)(void *exceptionPtrs, bool crashed);

extern "C" RENDERDOC_API void RENDERDOC_CC RENDERDOC_LogText(const wchar_t *text);
typedef void (RENDERDOC_CC *pRENDERDOC_LogText)(const wchar_t *text);

extern "C" RENDERDOC_API const wchar_t* RENDERDOC_CC RENDERDOC_GetLogFilename();
typedef const wchar_t* (RENDERDOC_CC *pRENDERDOC_GetLogFilename)();

extern "C" RENDERDOC_API bool RENDERDOC_CC RENDERDOC_GetThumbnail(const wchar_t *filename, byte *buf, uint32_t &len);
typedef bool (RENDERDOC_CC *pRENDERDOC_GetThumbnail)(const wchar_t *filename, byte *buf, uint32_t &len);

extern "C" RENDERDOC_API void RENDERDOC_CC RENDERDOC_FreeArrayMem(const void *mem);
typedef void (RENDERDOC_CC *pRENDERDOC_FreeArrayMem)(const void *mem);
