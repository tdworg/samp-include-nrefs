/** ======================================================================== **\
	Number References

| Description:

| Version:
	1.0.0

| Dependencies:
	- AMX Assembly (https://github.com/Zeex/amx_assembly)

| License:
	Copyright (c) 2017 Double V

	This software is provided 'as-is', without any express or implied
	warranty. In no event will the authors be held liable for any damages
	arising from the use of this software.

	Permission is granted to anyone to use this software for any purpose,
	including commercial applications, and to alter it and redistribute it
	freely, subject to the following restrictions:

	1.	The origin of this software must not be misrepresented; you must not
		claim that you wrote the original software. If you use this software
		in a product, an acknowledgement in the product documentation would be
		appreciated but is not required.
	2.	Altered source versions must be plainly marked as such, and must not be
		misrepresented as being the original software.
	3.	This notice may not be removed or altered from any source distribution.
\** ======================================================================== **/

#if defined _inc_tdw_nrefs
	#undef _inc_tdw_nrefs
#endif

#if defined _TDW_NREFS
	#endinput
#endif

#define _TDW_NREFS

#include "amx\disasm"
#include "amx\frame_info"

#if !defined addressofex
	#define addressofex(%1) (NRefs_GetNextCallAddress_()?(((%1),TDW_gNRefs@CallAddressRet_)?1:2):(TDW_gNRefs@CallAddressRet_))
#endif

stock
	TDW_gNRefs@CallAddressRet_;

stock NRefs_GetNextCallAddress_()
{
	new
		dctx[DisasmContext];
	DisasmInit(dctx, GetCurrentFrameReturn());
	while (DisasmNext(dctx)) {
		if (DisasmGetOpcode(dctx) == OP_CALL) {
			TDW_gNRefs@CallAddressRet_ = DisasmGetOperandReloc(dctx);
			return false;
		}
	}
	return false;
}

stock NRefs_GetNumRefs(address)
{
	new
		dctx[DisasmContext],
		count = 0;
	DisasmInit(dctx);
	while (DisasmNext(dctx)) {
		if (DisasmGetOpcode(dctx) == OP_CALL && DisasmGetOperandReloc(dctx) == address)
			count++;
	}
	return count;
}