#if defined __tf2ca_sentry_fire_override_included
	#endinput
#endif

#define __tf2ca_sentry_fire_override_included

#include <tf2ca_sentryfirebullet>

typedef SentryFireBulletCallback = function void(int builder, int sentry, const char[] attrName, FireBullets_t info);

/**
 * Registers a custom sentry bullet fire
 */
native bool TF2CA_SentryFireBullet_Register(const char[] attrName, SentryFireBulletCallback callback);

typedef SentryFireRocketCallback = function void(int builder, int sentry, const char[] attrName);

/**
 * Registers a custom sentry rocket fire
 */
native bool TF2CA_SentryFireRocket_Register(const char[] attrName, SentryFireRocketCallback callback);

public SharedPlugin __tf2ca_sentry_fire_override = {
	name = "tf2ca-sentry-fire-override",
	file = "tf2ca_custom_sentry_fire.smx",
#if defined REQUIRE_PLUGIN
	required = 1,
#else
	required = 0,
#endif
};
