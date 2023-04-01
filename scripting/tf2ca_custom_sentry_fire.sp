/**
 * Custom Attribute - Sentry Fire Override
 * 
 * referred to nosoop's tf2ca.
 */
#pragma semicolon 1
#include <sourcemod>
#include <sdktools>
#include <dhooks>

#pragma newdecls required

#include <tf_custom_attributes>
#include <tf2ca_sentryfirebullet>
#include <tf2ca_custom_building>
#include <tf2ca_stocks>

#define PLUGIN_VERSION "1.0.0"
public Plugin myinfo = {
	name = "[TF2CA] Sentry Fire Override",
	author = "Sandy",
	description = "Overrides the Sentry Fire.",
	version = PLUGIN_VERSION,
	url = ""
}

#define CUSTOM_SENTRY_FIRE_MAX_NAME_LENGTH 64

StringMap g_SentryFireForwards; // <callback>
StringMap g_SentryFireRocketForwards; // <callback>

Handle g_SDKCallAddGesture;

public APLRes AskPluginLoad2(Handle myself, bool late, char[] error, int err_max) {
	RegPluginLibrary("tf2ca-sentry-fire-override");
	CreateNative("TF2CA_SentryFireBullet_Register", RegisterCustomSentryFire);
	CreateNative("TF2CA_SentryFireRocket_Register", RegisterCustomSentryRocketFire);

	return APLRes_Success;
}

public void OnPluginStart() {
	GameData hGameData = new GameData("tf2.sentry");
	if(hGameData == null)
		SetFailState("[Sentry] missing tf2.sentry gamedata");

	StartPrepSDKCall(SDKCall_Entity);
	PrepSDKCall_SetFromConf(hGameData, SDKConf_Signature, "CBaseAnimatingOverlay::AddGesture");
	PrepSDKCall_AddParameter(SDKType_PlainOldData, SDKPass_Plain);
	PrepSDKCall_AddParameter(SDKType_Bool, SDKPass_Plain); 
	PrepSDKCall_SetReturnInfo(SDKType_PlainOldData, SDKPass_Plain);
	g_SDKCallAddGesture = EndPrepSDKCall();

	Handle DetourSentryFireRocket = DHookCreateFromConf(hGameData, "CObjectSentrygun::FireRocket()");
	DHookEnableDetour(DetourSentryFireRocket, false, OnSentryFireRocketPre);
	DHookEnableDetour(DetourSentryFireRocket, true, OnSentryFireRocketPost);
	
	delete hGameData;

	g_SentryFireForwards = new StringMap();
	g_SentryFireRocketForwards = new StringMap();
}

int RegisterCustomSentryFire(Handle plugin, int argc) {
	char customfireName[CUSTOM_SENTRY_FIRE_MAX_NAME_LENGTH];
	GetNativeString(1, customfireName, sizeof(customfireName));
	if (!customfireName[0]) {
		ThrowNativeError(1, "Cannot have an empty buff name.");
	}
	
	PrivateForward hFwd;
	if (!g_SentryFireForwards.GetValue(customfireName, hFwd)) {
		hFwd = new PrivateForward(ET_Ignore, Param_Cell, Param_Cell, Param_String, Param_Cell);
		g_SentryFireForwards.SetValue(customfireName, hFwd);
	}
	hFwd.AddFunction(plugin, GetNativeFunction(2));

	return 0;
}

int RegisterCustomSentryRocketFire(Handle plugin, int argc) {
	char customfireName[CUSTOM_SENTRY_FIRE_MAX_NAME_LENGTH];
	GetNativeString(1, customfireName, sizeof(customfireName));
	if (!customfireName[0]) {
		ThrowNativeError(1, "Cannot have an empty buff name.");
	}
	
	PrivateForward hFwd;
	if (!g_SentryFireRocketForwards.GetValue(customfireName, hFwd)) {
		hFwd = new PrivateForward(ET_Ignore, Param_Cell, Param_Cell, Param_String);
		g_SentryFireRocketForwards.SetValue(customfireName, hFwd);
	}
	hFwd.AddFunction(plugin, GetNativeFunction(2));

	return 0;
}

MRESReturn OnSentryFireRocketPre(int sentry, DHookReturn hReturn)
{
	if (!IsValidEntity(sentry))
		return MRES_Ignored;

	int builder = GetEntPropEnt(sentry, Prop_Send, "m_hBuilder");
	if (!IsValidClient(builder))
		return MRES_Ignored;

	char customfireName[CUSTOM_SENTRY_FIRE_MAX_NAME_LENGTH];
	if (!TF2CustAttr_ClientHasString(builder, "custom sentry rocket type", customfireName, sizeof(customfireName)))
		return MRES_Ignored;
	
	hReturn.Value = false;

	HandleSentryRocketFire(builder, sentry, customfireName);

	return MRES_Supercede;
}

MRESReturn OnSentryFireRocketPost(int sentry, DHookReturn hReturn)
{
	if (!IsValidEntity(sentry))
		return MRES_Ignored;

	return MRES_Ignored;
}

public MRESReturn TF2CA_SentryFireBullet(int sentry, int builder, FireBullets_t &info)
{
	char customfireName[CUSTOM_SENTRY_FIRE_MAX_NAME_LENGTH];
	if (!TF2CustAttr_ClientHasString(builder, "custom sentry bullet type", customfireName, sizeof(customfireName)))
		return MRES_Ignored;

	HandleSentryFire(builder, sentry, customfireName, info);

	return MRES_Supercede;
}

void HandleSentryFire(int builder, int sentry, const char[] attr, FireBullets_t info)
{
	PrivateForward hFwd;
	if (!g_SentryFireForwards.GetValue(attr, hFwd) || !hFwd.FunctionCount) {
		LogError("Sentry Bullet type '%s' is not associated with a plugin", attr);
		return;
	}

	Call_StartForward(hFwd);
	Call_PushCell(builder);
	Call_PushCell(sentry);
	Call_PushString(attr);
	Call_PushCell(info);
	Call_Finish();
}

void HandleSentryRocketFire(int builder, int sentry, const char[] attr)
{
	PrivateForward hFwd;
	if (!g_SentryFireRocketForwards.GetValue(attr, hFwd) || !hFwd.FunctionCount) {
		LogError("Sentry Rocket type '%s' is not associated with a plugin", attr);
		return;
	}

	Call_StartForward(hFwd);
	Call_PushCell(builder);
	Call_PushCell(sentry);
	Call_PushString(attr);
	Call_Finish();

	// Fix for server_srv.so!ConcatTransforms(matrix3x4_t const&, matrix3x4_t const&, matrix3x4_t&) + 0x36
	// ACT_RANGE_ATTACK2 == 17
	SDKCall(g_SDKCallAddGesture, sentry, 17, true);
}

stock bool IsValidClient(int client, bool replaycheck=true)
{
	if(client<=0 || client>MaxClients)
		return false;

	if(!IsClientInGame(client))
		return false;

	if(GetEntProp(client, Prop_Send, "m_bIsCoaching"))
		return false;

	if(replaycheck && (IsClientSourceTV(client) || IsClientReplay(client)))
		return false;

	return true;
}