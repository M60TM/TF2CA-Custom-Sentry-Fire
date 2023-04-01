/** Double-include prevention */
#if defined _tf2_sentryfirebullet_included_
  #endinput
#endif
#define _tf2_sentryfirebullet_included_

#include <dhooks>

any offs_FireBullets_t_m_iShots = 0;
any offs_FireBullets_t_m_vecSrc = 4;
any offs_FireBullets_t_m_vecDirShooting = 16;
any offs_FireBullets_t_m_vecSpread = 28;
any offs_FireBullets_t_m_flDistance = 40;
any offs_FireBullets_t_m_iAmmoType = 44;
any offs_FireBullets_t_m_iTracerFreq = 48;
any offs_FireBullets_t_m_flDamage = 52;
any offs_FireBullets_t_m_iPlayerDamage = 56;
any offs_FireBullets_t_m_nFlags = 60;
any offs_FireBullets_t_m_flDamageForceScale = 64;
any offs_FireBullets_t_m_pAttacker = 68;
any offs_FireBullets_t_m_pAdditionalIgnoreEnt = 72;
any offs_FireBullets_t_m_bPrimaryAttack = 76;
any offs_FireBullets_t_m_bUseServerRandomSeed = 77;

methodmap IMPL_internal_method_array_float3 {
	property Address Address {
		public get() {
			return view_as<Address>(this);
		}
	}
	public void Get(float value[3]) {
		for (int i; i < 3; i++) {
			value[i] = view_as<float>(LoadFromAddress(this.Address + view_as<Address>(4 * i), NumberType_Int32));
		}
	}
	public void Set(const float value[3]) {
		for (int i; i < 3; i++) {
			StoreToAddress(this.Address + view_as<Address>(4 * i), view_as<any>(value[i]), NumberType_Int32);
		}
	}
	public float GetIndex(int index) {
		if (index < 0 || index >= 3) {
			ThrowError("Index %d is out of bounds (limit 3)", index);
		}
		return view_as<float>(LoadFromAddress(this.Address + view_as<Address>(4 * index), NumberType_Int32));
	}
	public void SetIndex(int index, float value) {
		if (index < 0 || index >= 3) {
			ThrowError("Index %d is out of bounds (limit 3)", index);
		}
		StoreToAddress(this.Address + view_as<Address>(4 * index), view_as<any>(value), NumberType_Int32);
	}
}

methodmap FireBullets_t {
	/**
	 * Returns the address casted to a FireBullets_t methodmap instance.
	 */
	public static FireBullets_t FromAddress(Address pInstance) {
		return view_as<FireBullets_t>(pInstance);
	}
	
	property Address Address {
		public get() {
			return view_as<Address>(this);
		}
	}
	
	property int m_iShots {
		public get() {
			return view_as<int>(LoadFromAddress(this.Address + view_as<Address>(offs_FireBullets_t_m_iShots), NumberType_Int32));
		}
		public set(int value) {
			StoreToAddress(this.Address + view_as<Address>(offs_FireBullets_t_m_iShots), view_as<any>(value), NumberType_Int32);
		}
	}
	
	property IMPL_internal_method_array_float3 m_vecSrc {
		public get() {
			return view_as<IMPL_internal_method_array_float3>(this.Address + view_as<Address>(offs_FireBullets_t_m_vecSrc));
		}
	}
	
	property IMPL_internal_method_array_float3 m_vecDirShooting {
		public get() {
			return view_as<IMPL_internal_method_array_float3>(this.Address + view_as<Address>(offs_FireBullets_t_m_vecDirShooting));
		}
	}
	
	property IMPL_internal_method_array_float3 m_vecSpread {
		public get() {
			return view_as<IMPL_internal_method_array_float3>(this.Address + view_as<Address>(offs_FireBullets_t_m_vecSpread));
		}
	}
	
	property float m_flDistance {
		public get() {
			return view_as<float>(LoadFromAddress(this.Address + view_as<Address>(offs_FireBullets_t_m_flDistance), NumberType_Int32));
		}
		public set(float value) {
			StoreToAddress(this.Address + view_as<Address>(offs_FireBullets_t_m_flDistance), view_as<any>(value), NumberType_Int32);
		}
	}
	
	property int m_iAmmoType {
		public get() {
			return view_as<int>(LoadFromAddress(this.Address + view_as<Address>(offs_FireBullets_t_m_iAmmoType), NumberType_Int32));
		}
		public set(int value) {
			StoreToAddress(this.Address + view_as<Address>(offs_FireBullets_t_m_iAmmoType), view_as<any>(value), NumberType_Int32);
		}
	}
	
	property int m_iTracerFreq {
		public get() {
			return view_as<int>(LoadFromAddress(this.Address + view_as<Address>(offs_FireBullets_t_m_iTracerFreq), NumberType_Int32));
		}
		public set(int value) {
			StoreToAddress(this.Address + view_as<Address>(offs_FireBullets_t_m_iTracerFreq), view_as<any>(value), NumberType_Int32);
		}
	}
	
	property float m_flDamage {
		public get() {
			return view_as<float>(LoadFromAddress(this.Address + view_as<Address>(offs_FireBullets_t_m_flDamage), NumberType_Int32));
		}
		public set(float value) {
			StoreToAddress(this.Address + view_as<Address>(offs_FireBullets_t_m_flDamage), view_as<any>(value), NumberType_Int32);
		}
	}
	
	property int m_iPlayerDamage {
		public get() {
			return view_as<int>(LoadFromAddress(this.Address + view_as<Address>(offs_FireBullets_t_m_iPlayerDamage), NumberType_Int32));
		}
		public set(int value) {
			StoreToAddress(this.Address + view_as<Address>(offs_FireBullets_t_m_iPlayerDamage), view_as<any>(value), NumberType_Int32);
		}
	}
	
	property int m_nFlags {
		public get() {
			return view_as<int>(LoadFromAddress(this.Address + view_as<Address>(offs_FireBullets_t_m_nFlags), NumberType_Int32));
		}
		public set(int value) {
			StoreToAddress(this.Address + view_as<Address>(offs_FireBullets_t_m_nFlags), view_as<any>(value), NumberType_Int32);
		}
	}
	
	property float m_flDamageForceScale {
		public get() {
			return view_as<float>(LoadFromAddress(this.Address + view_as<Address>(offs_FireBullets_t_m_flDamageForceScale), NumberType_Int32));
		}
		public set(float value) {
			StoreToAddress(this.Address + view_as<Address>(offs_FireBullets_t_m_flDamageForceScale), view_as<any>(value), NumberType_Int32);
		}
	}
	
	property int m_pAttacker {
		public get() {
			return view_as<int>(LoadFromAddress(this.Address + view_as<Address>(offs_FireBullets_t_m_pAttacker), NumberType_Int32));
		}
		public set(int value) {
			StoreToAddress(this.Address + view_as<Address>(offs_FireBullets_t_m_pAttacker), view_as<any>(value), NumberType_Int32);
		}
	}
	
	property int m_pAdditionalIgnoreEnt {
		public get() {
			return view_as<int>(LoadFromAddress(this.Address + view_as<Address>(offs_FireBullets_t_m_pAdditionalIgnoreEnt), NumberType_Int32));
		}
		public set(int value) {
			StoreToAddress(this.Address + view_as<Address>(offs_FireBullets_t_m_pAdditionalIgnoreEnt), view_as<any>(value), NumberType_Int32);
		}
	}
	
	property bool m_bPrimaryAttack {
		public get() {
			return view_as<bool>(LoadFromAddress(this.Address + view_as<Address>(offs_FireBullets_t_m_bPrimaryAttack), NumberType_Int8));
		}
		public set(bool value) {
			StoreToAddress(this.Address + view_as<Address>(offs_FireBullets_t_m_bPrimaryAttack), view_as<any>(value), NumberType_Int8);
		}
	}
	
	property bool m_bUseServerRandomSeed {
		public get() {
			return view_as<bool>(LoadFromAddress(this.Address + view_as<Address>(offs_FireBullets_t_m_bUseServerRandomSeed), NumberType_Int8));
		}
		public set(bool value) {
			StoreToAddress(this.Address + view_as<Address>(offs_FireBullets_t_m_bUseServerRandomSeed), view_as<any>(value), NumberType_Int8);
		}
	}
	
	public static int GetClassSize() {
		return 81;
	}
}

forward MRESReturn TF2_SentryFireBullet(int sentry, int builder, FireBullets_t &info);

forward void TF2_SentryFireBulletPost(int sentry, int builder, FireBullets_t info);

public SharedPlugin __pl_tf2_sentryfirebullet = {
	name = "tf2_sentryfirebullet",
	file = "tf2_sentryfirebullet.smx",
#if defined REQUIRE_PLUGIN
	required = 1,
#else
	required = 0,
#endif
};
