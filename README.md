# TF2CA-Custom-Sentry-Fire
The plugin allows you to override sentry gun's bullet fire and rocket fire.

## Dependency
* sourcemod 1.11+
* [TFCustAttr](https://github.com/nosoop/SM-TFCustAttr)
* [TF2-Sentry-Fire-Bullet](https://github.com/M60TM/TF2-Sentry-Fire-Bullet)
* [tf2ca_stock (compile only)](https://github.com/M60TM/TF2CA-Custom-Building/blob/master/scripting/include/tf2ca_stocks.inc)
* [stocksoup (compile only)](https://github.com/nosoop/stocksoup)

## Usage
```
typedef SentryFireBulletCallback = function void(int builder, int sentry, const char[] attrName, FireBullets_t info);

/**
 * Registers a custom sentry bullet fire.
 */
native bool TF2CA_SentryFireBullet_Register(const char[] attrName, SentryFireBulletCallback callback);

typedef SentryFireRocketCallback = function void(int builder, int sentry, const char[] attrName);

/**
 * Registers a custom sentry rocket fire.
 */
native bool TF2CA_SentryFireRocket_Register(const char[] attrName, SentryFireRocketCallback callback);
```

`"custom sentry bullet type"  "double_laser"`

----

## Building

This project is configured for building via [Ninja][]; see `BUILD.md` for detailed
instructions on how to build it.

If you'd like to use the build system for your own projects,
[the template is available here](https://github.com/nosoop/NinjaBuild-SMPlugin).

[Ninja]: https://ninja-build.org/
